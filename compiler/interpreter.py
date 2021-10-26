from .ast_node import AstNode, AstNodeType


def interpreter(ast_node: AstNode) -> int:
    if ast_node.left:
        left_val = interpreter(ast_node.left)
    if ast_node.right:
        right_val = interpreter(ast_node.right)

    print(ast_node.op, left_val)

    if ast_node.op == AstNodeType.ADD:
        return left_val + right_val
    elif ast_node.op == AstNodeType.SUBTRACT:
        return left_val - right_val
    elif ast_node.op == AstNodeType.MULTIPLY:
        return left_val * right_val
    elif ast_node.op == AstNodeType.DIVIDE:
        return left_val / right_val
    elif ast_node.op == AstNodeType.INT_VALUE:
        return ast_node.value
    else:
        raise Exception(f"Unknown ast type {ast_node}")
