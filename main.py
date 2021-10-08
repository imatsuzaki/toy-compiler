import sys

from compiler import scan
from pathlib import Path


def main():
    args = sys.argv
    if len(args) != 2:
        raise Exception(f"Number of input args are wrong: {len(args)}")

    tokens = scan.scan(Path(args[1]))
    for t in tokens:
        print(t)


if __name__ == "__main__":
    main()
