from pathlib import Path
from re import T
from .token import Token, TokenType


def scan(filepath: Path) -> list[Token]:
    token_list: list[Token] = []
    with filepath.open(mode="r") as f:
        s = f.read()

        idx = 0
        while idx < len(s):
            c = s[idx]

            if c.isspace() or c == "\n" or c == "\t":
                idx += 1
                continue
            elif c == "+":
                idx += 1
                token_list.append(Token(token_type=TokenType.PLUS))
                continue
            elif c == "-":
                idx += 1
                token_list.append(Token(token_type=TokenType.MINUS))
                continue
            elif c == "*":
                idx += 1
                token_list.append(Token(token_type=TokenType.STAR))
                continue
            elif c == "/":
                idx += 1
                token_list.append(Token(token_type=TokenType.SLASH))
                continue
            else:
                idx += 1
                if c.isdigit():
                    token_list.append(
                        Token(token_type=TokenType.INT_VALUE, value=int(c))
                    )
                    continue
                raise Exception(f"{c} cannot be parsed.")
    return token_list
