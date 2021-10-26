#include "defs.h"
#include "data.h"
#include "decl.h"

// 最初のtokenは数値であることを前提としてnodeを作り次のtokenを読み込む　
static struct ASTnode *primary()
{
    struct ASTnode *n;

    switch (Token.token)
    {
    case T_INTLIT:
        n = mkastleaf(A_INTLIT, Token.intvalue);
        scan(&Token);
        return n;
    default:
        fprintf(stderr, "syntax error on line %d\n", Line);
        exit(1);
    }
}

int arithop(int tok)
{
    switch (tok)
    {
    case T_PLUS:
        return A_ADD;
    case T_MINUS:
        return A_SUBSTRACT;
    case T_STAR:
        return A_MULTIPLY;
    case T_SLASH:
        return A_DIVIDE;
    default:
        fprintf(stderr, "unknown token in aritop() on line %d, %d\n", Line, tok);
        exit(1);
    }
}

struct ASTnode *binexpr()
{
    struct ASTnode *n, *left, *right;
    int nodetype;

    left = primary(); // 最初の1tokenは読み込まれている前提で解析

    if (Token.token == T_EOF)
    {
        return left;
    }

    nodetype = arithop(Token.token);

    scan(&Token);
    right = binexpr();
    n = mkastnode(nodetype, left, right, 0);
    return n;
}