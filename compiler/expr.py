from typing import Optional

from .ast_node import AstNode, AstNodeType
from .token import Token, TokenType


def primary(token: Token) -> AstNode:
    if token.token_type == TokenType.INT_VALUE:
        return AstNode(op=AstNodeType.INT_VALUE, value=token.value)
    else:
        raise Exception(f"Syntax error on {token}")


def binary_expr(tokens: list[Token]) -> Optional[AstNode]:
    if len(tokens) == 0:
        return None

    first_token = tokens.pop(0)
    left_node = primary(first_token)

    if len(tokens) == 0:
        return left_node

    next_token = tokens.pop(0)
    if next_token.token_type == TokenType.PLUS:
        ast_node = AstNode(op=AstNodeType.ADD)
    elif next_token.token_type == TokenType.MINUS:
        ast_node = AstNode(op=AstNodeType.SUBTRACT)
    elif next_token.token_type == TokenType.STAR:
        ast_node = AstNode(op=AstNodeType.MULTIPLY)
    elif next_token.token_type == TokenType.SLASH:
        ast_node = AstNode(op=AstNodeType.DIVIDE)
    else:
        raise Exception(f"{next_token} is not valid token")

    right_node = binary_expr(tokens)
    ast_node.left = left_node
    ast_node.right = right_node

    return ast_node
