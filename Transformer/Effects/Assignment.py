# SPDX-FileCopyrightText: 2022 Rot127 <unisono@quyllur.org>
# SPDX-License-Identifier: LGPL-3.0-only

from Transformer.Effects.Effect import Effect, EffectType
from Transformer.Pures.BitOp import BitOp, BitOperationType
from Transformer.Pures.Pure import Pure, PureType
from enum import StrEnum

from Transformer.Pures.ArithmeticOp import ArithmeticOp, ArithmeticType


class AssignmentType(StrEnum):
    ASSIGN = '='
    ASSIGN_ADD = '+='
    ASSIGN_SUB = '-='
    ASSIGN_MUL = '*='
    ASSIGN_DIV = '/='
    ASSIGN_RIGHT = '>>='
    ASSIGN_LEFT = '<<='
    ASSIGN_MOD = '%='
    ASSIGN_AND = '&='
    ASSIGN_XOR = '^='
    ASSIGN_OR = '|='


class Assignment(Effect):
    name = ''
    type = None
    dest = None
    src = None

    def __init__(self, name: str, assign_type: AssignmentType, dest: Pure, src: Pure):
        self.assign_type = assign_type
        self.dest = dest
        self.src = src

        if dest.type == PureType.LOCAL:
            super().__init__(name, EffectType.SETL)
        elif dest.type == PureType.GLOBAL:
            super().__init__(name, EffectType.SETG)
        else:
            raise NotImplementedError(f'Dest type {self.dest.type} not handled.')
        self.set_src()

    def set_src(self):
        """ Update the src in case of +=, -= and similar assignments. """
        if self.assign_type == AssignmentType.ASSIGN:
            return
        elif self.assign_type == AssignmentType.ASSIGN_ADD:
            self.src = ArithmeticOp(f'add{self.src.get_isa_name()}{self.dest.get_isa_name()}',
                                    self.src, self.dest, ArithmeticType.ADD)
        elif self.assign_type == AssignmentType.ASSIGN_SUB:
            self.src = ArithmeticOp(f'sub{self.src.get_isa_name()}{self.dest.get_isa_name()}',
                                    self.src, self.dest, ArithmeticType.SUB)
        elif self.assign_type == AssignmentType.ASSIGN_MUL:
            self.src = ArithmeticOp(f'mul{self.src.get_isa_name()}{self.dest.get_isa_name()}',
                                    self.src, self.dest, ArithmeticType.MUL)
        elif self.assign_type == AssignmentType.ASSIGN_MOD:
            self.src = ArithmeticOp(f'mod{self.src.get_isa_name()}{self.dest.get_isa_name()}',
                                    self.src, self.dest, ArithmeticType.MOD)
        elif self.assign_type == AssignmentType.ASSIGN_DIV:
            self.src = ArithmeticOp(f'div{self.src.get_isa_name()}{self.dest.get_isa_name()}',
                                    self.src, self.dest, ArithmeticType.DIV)
        elif self.assign_type == AssignmentType.ASSIGN_RIGHT:
            self.src = BitOp(f'shiftr{self.src.get_isa_name()}{self.dest.get_isa_name()}',
                                    self.src, self.dest, BitOperationType.RSHIFT)
        elif self.assign_type == AssignmentType.ASSIGN_LEFT:
            self.src = BitOp(f'shiftl{self.src.get_isa_name()}{self.dest.get_isa_name()}',
                             self.src, self.dest, BitOperationType.LSHIFT)
        elif self.assign_type == AssignmentType.ASSIGN_AND:
            self.src = BitOp(f'and{self.src.get_isa_name()}{self.dest.get_isa_name()}',
                             self.src, self.dest, BitOperationType.AND)
        elif self.assign_type == AssignmentType.ASSIGN_OR:
            self.src = BitOp(f'or{self.src.get_isa_name()}{self.dest.get_isa_name()}',
                             self.src, self.dest, BitOperationType.OR)
        elif self.assign_type == AssignmentType.ASSIGN_XOR:
            self.src = BitOp(f'xor{self.src.get_isa_name()}{self.dest.get_isa_name()}',
                             self.src, self.dest, BitOperationType.XOR)
        else:
            raise NotImplementedError(f'Assign type {self.assign_type} not handled.')

    def il_write(self):
        """ Returns the RZIL ops to write the variable value.
        :return: RZIL ops to write the pure value.
        """
        if self.type == EffectType.SETG:
            return f'SETG({self.dest.get_assoc_name()}, {self.src.get_isa_name()})'
        elif self.type == EffectType.SETL:
            return f'SETL("{self.dest.get_isa_name()}", {self.src.get_isa_name()})'
        else:
            raise NotImplementedError(f'Effect ype {self.type} not handled.')
