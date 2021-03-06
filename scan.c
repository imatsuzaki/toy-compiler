#include "defs.h"
#include "data.h"
#include "decl.h"

// cのstringとしての文字の位置を返す。
// もし見つからない場合は -1 を返す
static int chrpos(char *s, int c)
{
    char *p;

    p = strchr(s, c);
    return (p ? p - s : -1);
}

// ファイルから次の文字をとってくる
static int next()
{
    int c;

    if (Putback)
    {
        c = Putback;
        Putback = 0;
        return c;
    }

    c = fgetc(Infile);
    if ('\n' == c)
    {
        Line++;
    }
    return c;
}

// スペース、タブ、改行などをスキップする
static int skip(void)
{
    int c;

    c = next();
    while (' ' == c || '\t' == c || '\n' == c || '\r' == c || '\f' == c)
    {
        c = next();
    }
    return c;
}

static void putback(int c)
{
    Putback = c;
}

static int scanint(int c)
{
    int k, val = 0;

    while ((k = chrpos("0123456789", c)) >= 0)
    {
        val = val * 10 + k;
        c = next();
    }

    putback(c);
    return val;
}

// 空白の場合はスキップ
// +, *, -, /の場合はtokenを返す
// 数字の場合はtokenを返しその中にint valueが入ってる
int scan(struct token *t)
{
    int c;

    // 空白をスキップしつつ、最初の文字を確保
    c = skip();

    switch (c)
    {
    case EOF:
        t->token = T_EOF;
        return 0;
    case '+':
        t->token = T_PLUS;
        break;
    case '-':
        t->token = T_MINUS;
        break;
    case '*':
        t->token = T_STAR;
        break;
    case '/':
        t->token = T_SLASH;
        break;
    default:
        if (isdigit(c))
        {
            t->intvalue = scanint(c);
            t->token = T_INTLIT;
            break;
        }

        printf("Unrecognised character %c on line %d\n", c, Line);
        exit(1);
    }

    // tokenが無事に見つかったことを知らせるsignal
    return 1;
}