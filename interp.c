#include "decl.h"
#include "defs.h"
#include "data.h"

static char *ASTop[] = {"+", "-", "*", "/"};

int interpretAST(struct ASTnode *n)
{
    int lefval, rightval;

    // child nodeがないところまでまずもぐる。潜り切った後で値の評価。
    if (n->left)
        lefval = interpretAST(n->left);
    if (n->right)
        rightval = interpretAST(n->right);

    // ただのdebug print
    // if (n->op == A_INTLIT)
    //     printf("int %d\n", n->intvalue);
    // else
    //     printf("%d %s %d\n", lefval, ASTop[n->op], rightval);

    switch (n->op)
    {
    case A_ADD:
        return (lefval + rightval);
    case A_SUBSTRACT:
        return (lefval - rightval);
    case A_MULTIPLY:
        return (lefval * rightval);
    case A_DIVIDE:
        return (lefval / rightval);
    case A_INTLIT:
        return (n->intvalue);
    default:
        fprintf(stderr, "Unknown AST operator%d\n", n->op);
        exit(1);
    }
}