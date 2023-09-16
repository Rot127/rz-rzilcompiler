# SPDX-FileCopyrightText: 2022 Rot127 <unisono@quyllur.org>
# SPDX-License-Identifier: LGPL-3.0-only

from rzil_compiler.Transformer.Pures.LetVar import LetVar
from rzil_compiler.Transformer.Pures.Pure import ValueType


class Number(LetVar):
    def __init__(self, name: str, val: int, v_type: ValueType):
        self.name = name
        self.v_type: ValueType = v_type
        self.inlined = True
        LetVar.__init__(self, name, val, v_type)
