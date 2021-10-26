from __future__ import annotations

from dataclasses import dataclass
from enum import Enum
from typing import Optional


class AstNodeType(Enum):
    ADD = 0
    SUBTRACT = 1
    MULTIPLY = 2
    DIVIDE = 3
    INT_VALUE = 4


@dataclass
class AstNode:
    op: AstNodeType
    left: Optional[AstNode] = None
    right: Optional[AstNode] = None
    value: Optional[int] = None
