# SPDX-FileCopyrightText: 2022 Rot127 <unisono@quyllur.org>
# SPDX-License-Identifier: LGPL-3.0-only

from Transformer.Pures.LetVar import LetVar
from Transformer.Pures.Pure import ValueType


class Number(LetVar):
    def __init__(self, name: str, val: int, v_type: ValueType):
        self.name = name
        self.v_type: ValueType = v_type
        LetVar.__init__(self, name, val, v_type)

    def il_init_var(self):
        return f""

    def il_read(self):
        """Returns the code to read the let variable for the VM."""
        return f"{'SN' if self.v_type.signed else 'UN'}({self.v_type.bit_width}, {self.get_val()})"
