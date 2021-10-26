import sys
from pathlib import Path

from compiler import scan
from compiler.expr import binary_expr
from compiler.interpreter import interpreter


def main():
    args = sys.argv
    if len(args) != 2:
        raise Exception(f"Number of input args are wrong: {len(args)}")

    tokens = scan.scan(Path(args[1]))
    node = binary_expr(tokens)
    print(interpreter(node))


if __name__ == "__main__":
    main()
