# SPDX-FileCopyrightText: 2022 Rot127 <unisono@quyllur.org>
# SPDX-License-Identifier: LGPL-3.0-only

from rzil_compiler.Transformer.Pures.LocalVar import LocalVar
from rzil_compiler.Transformer.ValueType import ValueType


class Variable(LocalVar):
    """This class represents a C variable."""

    def __init__(self, name: str, val_type: ValueType):
        LocalVar.__init__(self, name, value_type=val_type)

    def il_init_var(self):
        # Local vars are not initialized like global vars. They are initialized when an assignment to them happens.
        code = f"// Declare: {self.value_type} {self.get_name()};"
        return code

    def __str__(self):
        return f"{self.get_name()}"
