# SPDX-FileCopyrightText: 2022 Rot127 <unisono@quyllur.org>
# SPDX-License-Identifier: LGPL-3.0-only

from lark import Transformer, Token

from ArchEnum import ArchEnum
from Transformer.Effects.Jump import Jump
from Transformer.Effects.MemStore import MemStore
from Transformer.Effects.NOP import NOP
from Transformer.HexagonExtension import HexagonExtension
from Transformer.ILOpsHolder import ILOpsHolder
from Transformer.Pures.BitOp import BitOperationType, BitOp
from Transformer.Pures.BooleanOp import BooleanOpType, BooleanOp
from Transformer.Pures.CCode import CCall
from Transformer.Pures.Cast import Cast
from Transformer.Pures.CompareOp import CompareOp, CompareOpType
from Transformer.Pures.LocalVar import LocalVar
from Transformer.Pures.MemLoad import MemAccessType, MemLoad
from Transformer.Pures.Number import Number
from Transformer.Pures.Pure import Pure, ValueType
from Transformer.Effects.Assignment import Assignment, AssignmentType
from Transformer.Pures.ArithmeticOp import ArithmeticOp, ArithmeticType
from Transformer.Pures.Ternary import Ternary
from Transformer.helper import exc_if_types_not_match
from Transformer.helper_hexagon import get_value_type_by_c_number, get_num_base_by_token, get_c_type_by_value_type


class RZILTransformer(Transformer):
    """
    Transforms the tree into Pures and Effects.
    The classes do the actual code generation.
    """
    op_count = 0

    def __init__(self, arch: ArchEnum):

        self.arch = arch

        if self.arch == ArchEnum.HEXAGON:
            self.ext = HexagonExtension()
        else:
            raise NotImplementedError(f'Architecture {self.arch} has not Transformer extension.')
        super().__init__()

    def get_op_id(self):
        op_id = self.op_count
        self.op_count += 1
        return op_id

    def fbody(self, items):
        self.ext.set_token_meta_data('fbody')

        holder = ILOpsHolder()
        res = ''
        # We are at the top. Generate code.
        res += "\n// READ\n"
        for op in holder.read_ops.values():
            res += op.il_init_var() + '\n'
        res += '\n// EXEC\n'
        for op in holder.exec_ops.values():
            res += op.il_init_var() + '\n'
        res += "\n// WRITE\n"
        for op in holder.write_ops.values():
            res += op.il_init_var() + '\n'
        res += f'\nreturn SEQN({", ".join([op.get_name() for op in holder.write_ops.values()])});'
        return res

    def relational_expr(self, items):
        return self.compare_op(items)

    def equality_expr_expr(self, items):
        return self.compare_op(items)

    def reg_alias(self, items):
        self.ext.set_token_meta_data('reg')

        return self.ext.reg_alias(items)

    # SPECIFIC FOR: Hexagon
    def new_reg(self, items):
        self.ext.set_token_meta_data('new_reg')

        return self.ext.hex_reg(items, True)

    def explicit_reg(self, items):
        self.ext.set_token_meta_data('explicit_reg')
        name = items[0]
        new = items[1] is not None
        if name == 'R31':
            # We don't know whether R31 is used as dest or src. Hence: SRC_DEST_REG.
            return self.ext.hex_reg([Token('REG_TYPE', 'R'), Token('SRC_DEST_REG', '31'), name], is_new=new)
        elif name[0] == 'P':
            return self.ext.hex_reg([Token('REG_TYPE', 'P'), Token('SRC_DEST_REG', str(name[1])), name], is_new=new)
        else:
            raise NotImplementedError(f'Explicit register {items} not handled.')

    def reg(self, items):
        self.ext.set_token_meta_data('reg')

        return self.ext.reg(items)

    def imm(self, items):
        self.ext.set_token_meta_data('imm')

        return self.ext.imm(items)

    def jump(self, items):
        self.ext.set_token_meta_data('jump')
        ta: Pure = items[1]
        return Jump(f'jump_{ta.get_name()}', ta)

    def data_type(self, items):
        self.ext.set_token_meta_data('data_type')
        return self.ext.get_value_type_by_resource_type(items)

    def cast_expr(self, items):
        self.ext.set_token_meta_data('cast_expr')
        val_type = items[0]
        data = items[1]
        return Cast(f'cast_{val_type}_{self.get_op_id()}', val_type, data)

    def number(self, items):
        # Numbers of the form -10ULL
        self.ext.set_token_meta_data('number')

        v_type = get_value_type_by_c_number(items)
        num_str = (str(items[0]) if items[0] else '') + str(items[1])
        name = f'const_{"neg" if items[0] == "-" else "pos"}{items[1]}{items[2] if items[2] else ""}'
        return Number(name, int(num_str, get_num_base_by_token(items[1])), v_type)

    def declaration(self, items):
        self.ext.set_token_meta_data('declaration')

        if len(items) != 2:
            raise NotImplementedError(f'Declaration without exactly two tokens are not supported.')
        t: ValueType = items[0]
        if isinstance(items[1], Assignment):
            assg: Assignment = items[1]
            assg.dest.set_value_type(t)
        elif isinstance(items[1], str):
            return LocalVar(items[1], t)
        return

    def init_declarator(self, items):
        self.ext.set_token_meta_data('init_declarator')

        if len(items) != 2:
            raise NotImplementedError(f'Can not initialize an Init declarator with {len(items)} tokens.')
        dest = LocalVar(items[0], None)  # Size is updated in declaration handler.
        op_type = AssignmentType.ASSIGN
        src: Pure = items[1]
        name = f'op_{op_type.name}_{self.get_op_id()}'
        v = Assignment(name, op_type, dest, src)
        return v

    def conditional_expr(self, items):
        return Ternary(f'cond_{self.get_op_id()}', items[0], items[1], items[2])

    def assignment_expr(self, items):
        self.ext.set_token_meta_data('assignment_expr')

        dest: Pure = items[0]
        op_type = AssignmentType(items[1])
        src: Pure = items[2]
        name = f'op_{op_type.name}_{self.get_op_id()}'
        v = Assignment(name, op_type, dest, src)
        return v

    def additive_expr(self, items):
        self.ext.set_token_meta_data('additive_expr')

        a = items[0]
        b = items[2]
        op_type = ArithmeticType(items[1])
        name = f'op_{op_type.name}_{self.get_op_id()}'
        v = ArithmeticOp(name, a, b, op_type)
        return v

    def multiplicative_expr(self, items):
        self.ext.set_token_meta_data('additive_expr')

        a = items[0]
        b = items[2]
        op_type = ArithmeticType(items[1])
        name = f'op_{op_type.name}_{self.get_op_id()}'
        v = ArithmeticOp(name, a, b, op_type)
        return v

    def and_expr(self, items):
        self.ext.set_token_meta_data('and_expr')

        return self.bit_operations(items, BitOperationType.AND)

    def inclusive_or_expr(self, items):
        self.ext.set_token_meta_data('inclusive_or_expr')

        return self.bit_operations(items, BitOperationType.OR)

    def exclusive_or_expr(self, items):
        self.ext.set_token_meta_data('exclusive_or_expr')

        return self.bit_operations(items, BitOperationType.XOR)

    def logical_and_expr(self, items):
        self.ext.set_token_meta_data('logical_and_expr')
        return self.boolean_expr(items)

    def logical_or_expr(self, items):
        self.ext.set_token_meta_data('logical_or_expr')
        return self.boolean_expr(items)

    def logical_not_expr(self, items):
        self.ext.set_token_meta_data('logical_not_expr')
        return self.boolean_expr(items)

    def boolean_expr(self, items):
        a = items[0]
        t = BooleanOpType(items[1])
        b = items[2] if len(items) == 3 else None
        name = f'op_{t}_{self.get_op_id()}'
        v = BooleanOp(name, a, b, t)
        return v

    def shift_expr(self, items):
        self.ext.set_token_meta_data('shift_expr')
        return self.bit_operations(items, BitOperationType(items[1]))

    def unary_expr(self, items):
        self.ext.set_token_meta_data('unary_expr')

        if items[0] == '~':
            return self.bit_operations(items, BitOperationType.NOT)
        elif items[0] == '-':
            return self.bit_operations(items, BitOperationType.NEG)
        else:
            raise NotImplementedError(f'Unary expression {items[0]} not handler.')

    def bit_operations(self, items: list, op_type: BitOperationType):
        self.ext.set_token_meta_data('bit_operations')

        if len(items) < 3:
            # Single operand bit operation e.g. ~
            a = items[1]
            name = f'op_{op_type.name}_{self.get_op_id()}'
            v = BitOp(name, a, None, op_type)
            return v
        a = items[0]
        b = items[2]
        name = f'op_{op_type.name}_{self.get_op_id()}'
        v = BitOp(name, a, b, op_type)
        return v

    def mem_store(self, items):
        self.ext.set_token_meta_data('mem_store')
        va = items[3]
        data: Pure = items[4]
        operation_value_type = ValueType(items[1] != 'u', int(items[2]))
        exc_if_types_not_match(operation_value_type, data.value_type)
        return MemStore(f'ms_{data.get_name()}', va, data)

    # SPECIFIC FOR: Hexagon
    def mem_load(self, items):
        self.ext.set_token_meta_data('mem_load')
        vt = ValueType(items[1] != 'u', int(items[2]))
        mem_acc_type = MemAccessType(vt, True)
        va = items[3]
        if not isinstance(va, Pure):
            va = ILOpsHolder().get_op_by_name(va.value)

        return MemLoad(f'ml_{va.get_name()}', va, mem_acc_type)

    def c_call(self, items):
        self.ext.set_token_meta_data('c_call')
        prefix = items[0]
        val_type = self.ext.get_val_type_by_fcn(prefix)
        return CCall(f'c_call_{self.get_op_id()}', val_type, items)

    def identifier(self, items):
        # Hexagon shortcode can initialize certain variables without type.
        # Those are converted to a local var here.
        identifier = items[0].value
        holder = ILOpsHolder()
        if identifier in holder.read_ops:
            return holder.read_ops[identifier]
        if identifier in self.ext.special_identifiers.values():
            return self.ext.special_identifier_to_local_var(identifier)
        # Return string
        return identifier

    def compare_op(self, items):
        op_type = CompareOpType(items[1])
        return CompareOp(f'op_{op_type.name}', items[0], items[2], op_type)

    def cancel_slot_expr(self, items):
        return NOP(f'nop_{self.get_op_id()}')
