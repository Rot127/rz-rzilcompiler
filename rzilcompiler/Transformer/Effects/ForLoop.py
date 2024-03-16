# SPDX-FileCopyrightText: 2022 Rot127 <unisono@quyllur.org>
# SPDX-License-Identifier: LGPL-3.0-only

from rzilcompiler.Transformer.Effects.Effect import Effect, EffectType
from rzilcompiler.Transformer.Effects.Sequence import Sequence
from rzilcompiler.Transformer.Pures.Pure import Pure
from rzilcompiler.Transformer.Pures.BooleanOp import BooleanOp
from rzilcompiler.Transformer.Pures.CompareOp import CompareOp


class ForLoop(Effect):
    """
    for (init ; control ; after_cycle) { compound }
    """

    def __init__(self, name: str, control: Pure, compound: Sequence):
        self.control = control  # Condition
        self.compound = compound
        self.effect_ops = [self.control, self.compound]
        Effect.__init__(self, name, EffectType.LOOP)

    def il_write(self):
        """Returns the RZIL ops to write the variable value.
        :return: RZIL ops to write the pure value.
        """

        if isinstance(self.control, BooleanOp) or isinstance(self.control, CompareOp):
            control = self.control.il_read()
        else:
            control = f"NON_ZERO({self.control.il_read()})"

        return f"REPEAT({control}, " f"{self.compound.effect_var()})"

    def __str__(self):
        return f"while ({self.control}) {{ {self.compound} }}"
