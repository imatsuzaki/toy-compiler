from dataclasses import dataclass
from enum import Enum
from typing import Optional


class TokenType(Enum):
    PLUS = 0
    MINUS = 1
    STAR = 2
    SLASH = 3
    INT_VALUE = 4


@dataclass
class Token:
    token_type: TokenType
    value: Optional[int] = None
