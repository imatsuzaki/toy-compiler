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

struct ASTnode *additive_expr();

struct ASTnode *multiplicative_expr() {
    struct ASTnode *left, *right;
    int tokentype;

    // First letter must be a integer
    left = primary();

    // Go next char.
    tokentype = Token.token;
    if (tokentype == T_EOF)
        return left;

    // if next char is * or / in loop
    while ((tokentype == T_STAR) || (tokentype == T_SLASH))
    {
        scan(&Token);
        right = primary();

        left = mkastnode(arithop(tokentype), left, right, 0);
        tokentype = Token.token;
        if (tokentype == T_EOF)
            break;
    }
    
    return left;
}

// inputを multiplicativeの塊と思って、ひたすらそれで解析する
struct ASTnode *additive_expr() {
    struct ASTnode *left, *right;
    int tokentype;

    left = multiplicative_expr();

    tokentype = Token.token;
    if (tokentype == T_EOF)
        return left;

    while (1)
    {
        scan(&Token);

        right = multiplicative_expr();

        left = mkastnode(arithop(tokentype), left, right, 0);
        tokentype = Token.token;
        if (tokentype == T_EOF)
            break;
    }

    return left;
}

struct ASTnode *binexpr()
{
    return additive_expr();
}