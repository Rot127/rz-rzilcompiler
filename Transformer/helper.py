# SPDX-FileCopyrightText: 2022 Rot127 <unisono@quyllur.org>
# SPDX-License-Identifier: LGPL-3.0-only
import re
from copy import deepcopy

from rzil_compiler.Transformer.Pures.Cast import Cast
from rzil_compiler.Transformer.Pures.Pure import ValueType, Pure


def get_smalles_val_type_for_number(num: int) -> int:
    if num & 0xFFFFFFFFFFFFFF00 == 0:
        size = 8
    elif num & 0xFFFFFFFFFFFF0000 == 0:
        size = 16
    elif num & 0xFFFFFFFF00000000 == 0:
        size = 32
    else:
        size = 64
    return size


def exc_if_types_not_match(a: ValueType, b: ValueType):
    if a != b:
        raise ValueError(
            "Value types don't match.\n"
            f"a size: {a.bit_width} signed: {a.signed}\n"
            f"b size: {b.bit_width} signed: {b.signed}"
        )


def c11_cast(a: ValueType, b: ValueType) -> tuple[ValueType, ValueType]:
    """Compares both value types against each other and converts them according to
    Chapter 6.3.1.8 of ISO/IEC 9899:201x (C11 Standard).
    Please note that we do not follow the rank definition from the standard.
    Here: Rank = width of type. Which should be close enough.
    """

    sign_match = a.signed == b.signed
    rank_match = a.bit_width == b.bit_width
    if sign_match and rank_match:
        return a, b
    va = deepcopy(a)
    vb = deepcopy(b)

    if sign_match:
        if va.bit_width < vb.bit_width:
            va.bit_width = vb.bit_width
        else:
            vb.bit_width = va.bit_width
        return va, vb

    a_is_signed = va.signed
    unsigned = vb if a_is_signed else va
    signed = va if a_is_signed else vb

    if unsigned.bit_width >= signed.bit_width:
        signed.bit_width = unsigned.bit_width
        signed.signed = False
    else:
        unsigned.bit_width = signed.bit_width
        unsigned.signed = True
    return (signed, unsigned) if a_is_signed else (unsigned, signed)


def flatten_list(ls: list) -> list:
    if not hasattr(ls, "__iter__") or isinstance(ls, str):
        return [ls]
    result = []
    for el in ls:
        if hasattr(el, "__iter__") and not isinstance(el, str):
            result.extend(flatten_list(el))
        else:
            result.append(el)
    return result


def drain_list(l: list) -> list:
    """Returns the content of a list and clears it."""
    result, l[:] = l[:], []
    return result


def get_value_type_by_c_type(type_id: str) -> ValueType:
    """
    Returns a value type for C type identifiers.

    :param type_id: The type identifier.
    :return: The Value type it correspond.
    """
    if type_id == "int":
        return ValueType(True, 32)
    elif type_id == "unsigned":
        return ValueType(False, 32)

    if type_id.startswith("size"):
        type_match = re.search(r"size(?P<width>\d+)(?P<sign>[us])_t", type_id)
    else:
        type_match = re.search(r"(?P<sign>u?)int(?P<width>\d+)_t", type_id)
    if len(type_match.groups()) != 2:
        raise ValueError(f"Types of the form {type_id} can't be parsed yet.")

    is_signed = False if type_match["sign"] == "u" else True
    width = int(type_match["width"])
    return ValueType(is_signed, width)
