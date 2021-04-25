#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAXLEN 256
#define MAXREG 6
#define MAXVAR 64
#define VARSIZE 4
#define PRINTERR 1
#define DEBUG 1
#define error(errorNum) { \
    if (PRINTERR) \
        fprintf(stderr, "error() called at %s: %d: ", __FILE__, __LINE__); \
    err(errorNum); \
}

/* ------------------------ struct ------------------------ */
typedef enum {
    UNKNOWN, INT, ID, INCDEC,
    ADDSUB, MULDIV, OR, XOR, AND,
    ASSIGN, LPAREN, RPAREN,
    END, ENDFILE
} TokenSet;

typedef struct {
    char vName[MAXLEN];
    int vData;
} Variable;   // 變數和他的值, 變數有可能是字串(最長256)

typedef struct _Node {
    TokenSet tokenType;
    char token[MAXLEN];
    int nData;
    struct _Node *left; 
    struct _Node *right;
} BTNode;   // 內含token類型、token資料 (存lexeme) data不知道在幹嘛

typedef struct {
    char rName[3];  // r0, r1, r2
    int rData;
    int isUsed;
} Register;

typedef enum {
    UNDEFINED, MISPAREN, NOTNUMID, NOTFOUND, RUNOUT, NOTLVAL, DIVZERO, SYNTAXERR
} ErrorType;

/* ------------------------ Declaration ------------------------ */
int variableCnt = 0;   // 現在有幾個變數
char curToken[MAXLEN];
TokenSet curTokenType = UNKNOWN;   // 當前字元的Token
Variable variables[MAXVAR];   // 目前有的變數和值
Register registers[MAXREG];

void initVariable();    // 設定xyz一開始為0
int getval(char *);   // 取值或新增並設成0
int setval(char *, int);  // 設定已有變數的值，或新增變數並設值
int queue[MAXVAR], front, rear;
int varOnRight = 0;
int getVariableAddr(char *);
BTNode *newNode(TokenSet, const char *);   // Make a new node according to tokenType and curToken
BTNode *newIncreDecreTree(char);
void freeTree(BTNode *);

void assignment(BTNode *);
// parser support
TokenSet getTokenType();  // 回傳現在的Token類型 + 把當前Token放進lexeme
void changeCurToNext();  // 用getToken回傳下一個的Token類型 + 把下一個Token放進lexeme
int match(TokenSet);  // current token是不是和指定token相同，不存在則繼續抓下一個(adv -> getToken輸入)
char *getCurToken();  // 拿當前這個token的資料

// parser
BTNode *Root;
BTNode *factor();
BTNode *term();
BTNode *term_tail(BTNode *);
BTNode *expr();
BTNode *expr_tail(BTNode *);
BTNode *and_expr();
BTNode *and_tail(BTNode *);
BTNode *xor_expr();
BTNode *xor_tail(BTNode *);
BTNode *or_expr();
BTNode *or_tail(BTNode *);
void statement();

void initRegister();
Register *getEmptyRegister();
void resetRegister(Register *);
void GeneratorCaller(BTNode *);
Register *assemblyCode(BTNode *);

void Mov_RegReg(Register *, Register *);
void Mov_RegInt(Register *, int);
void Mov_RegAddr(Register *, int);
void Mov_AddrReg(int, Register *);
void Add(Register *, Register *);
void Sub(Register *, Register *);
void Mul(Register *, Register *);
void Div(Register *, Register *);
void And(Register *, Register *);
void Or(Register *, Register *);
void Xor(Register *, Register *);

// result
int evaluateTree(BTNode *);   // Evaluate the syntax tree
void printPrefix(BTNode *);   // Print the syntax tree in prefix
void err(ErrorType errorNum);

/* ------------------------ Implement ------------------------ */
int done;
int main() {
    // freopen("input.txt", "w", stdout);
    initVariable();
    initRegister();
    if (PRINTERR) printf(">> ");
    while (!done)
        statement();
    return 0;
}

void initVariable() {
    strcpy(variables[0].vName, "x");
    variables[0].vData = 0;
    strcpy(variables[1].vName, "y");
    variables[1].vData = 0;
    strcpy(variables[2].vName, "z");
    variables[2].vData = 0;
    variableCnt = 3;
}

// 從table中根據變數名字取值
// 沒有的話就新增變數並設成0
int getval(char *str) {
    for (int i = 0; i < variableCnt; i++)
        if (strcmp(str, variables[i].vName) == 0)
            return variables[i].vData;
    error(NOTFOUND);
    return 0;
}

// 從已有變數中設定值，或是新增變數並設定指定值
int setval(char *str, int val) {
    for (int i = 0; i < variableCnt; i++) {
        if (strcmp(str, variables[i].vName) == 0) {
            variables[i].vData = val;
            return val;
        }
    }

    if (variableCnt >= MAXVAR)
        error(RUNOUT);
    
    // new variables
    strcpy(variables[variableCnt].vName, str);
    variables[variableCnt].vData = val;
    variableCnt++;
    if (DEBUG)
        printf("setval | newVar %s in [%d]\n", str, variableCnt - 1);
    return val;
}

BTNode *newNode(TokenSet tok, const char *lexe) {
    BTNode *node = (BTNode *)malloc(sizeof(BTNode));
    strcpy(node->token, lexe);   // 存這個token單位資料 (運算元或運算子)
    node->tokenType = tok;   // token種類
    node->nData = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}

BTNode *newIncreDecreTree(char sign) {
    BTNode *root = newNode(ASSIGN, "=");
    changeCurToNext();
    if (match(ID)) {
        root->left = newNode(ID, curToken);
        root->right = sign == '+' ? newNode(ADDSUB, "+") : newNode(ADDSUB, "-");
        root->right->left = newNode(ID, curToken);
        root->right->right = newNode(INT, "1");
    } else
        error(SYNTAXERR);  // ++-- 一定要接ID
    return root;
}

void freeTree(BTNode *root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

TokenSet getTokenType() {
    char ch;

    // ch 在這裡被輸入
    while ((ch = fgetc(stdin)) == ' ' || ch == '\t');   // ignore space or tab

    if (isdigit(ch)) {   // ch 屬於 '1' ~ '9'
        curToken[0] = ch;
        ch = fgetc(stdin);
        int i = 1;
        // 持續輸入直到不是數字或超過長度
        while (isdigit(ch) && i < MAXLEN) {
            curToken[i] = ch;
            ++i;
            ch = fgetc(stdin);
        }
        ungetc(ch, stdin);
        curToken[i] = '\0';
        return INT;
    }
    
    else if (ch == '+' || ch == '-') {
        // TODO: INC
        curToken[0] = ch;
        ch = fgetc(stdin);  // 第一個+後面的東西
        if (ch == curToken[0]) {
            curToken[1] = ch;
            curToken[2] = '\0';
            return INCDEC;
        } else {
            curToken[1] = '\0';
            ungetc(ch, stdin);
            return ADDSUB;
        }
    }
    // TODO
    else if (ch == '|') {
        curToken[0] = ch;
        curToken[1] = '\0';
        return OR;
    }
    else if (ch == '^') {
        curToken[0] = ch;
        curToken[1] = '\0';
        return XOR;
    }
    else if (ch == '&') {
        curToken[0] = ch;
        curToken[1] = '\0';
        return AND;
    }
    else if (ch == '*' || ch == '/') {
        curToken[0] = ch;
        curToken[1] = '\0';
        return MULDIV;
    } else if (ch == '\n') {
        curToken[0] = '\0';
        return END;
    } else if (ch == '=') {
        strcpy(curToken, "=");
        return ASSIGN;
    } else if (ch == '(') {
        strcpy(curToken, "(");
        return LPAREN;
    } else if (ch == ')') {
        strcpy(curToken, ")");
        return RPAREN;
    } else if (isalpha(ch) || ch == '_') {
        curToken[0] = ch;
        ch = fgetc(stdin);
        int i = 1;
        while (isalpha(ch) || isdigit(ch) || ch == '_') {
            curToken[i] = ch;
            ++i;
            ch = fgetc(stdin);
        }
        ungetc(ch, stdin);
        curToken[i] = '\0';
        return ID;
    } else if (ch == EOF) {
        return ENDFILE;
    } else {
        return UNKNOWN;
    }
}

// 用getToken回傳下一個的Token類型 + 把下一個Token放進lexeme
void changeCurToNext() {
    curTokenType = getTokenType();
}

// current token是不是和指定token相同
// 不存在則繼續抓下一個(adv -> getToken輸入)
int match(TokenSet tokenType) {
    if (curTokenType == UNKNOWN) {
        changeCurToNext();
    }
    return tokenType == curTokenType;   // boolean
}

char *getCurToken() {
    return curToken;   // 拿當前這個token的資料
}

// factor := INT | ID | ID ASSIGN expr | INCDEC ID | LPAREN assign_expr RPAREN
BTNode *factor() {
    BTNode *retNode = NULL, *left = NULL;

    if (match(INT)) {
        retNode = newNode(INT, getCurToken());
        changeCurToNext();
    } else if (match(ID)) {
        left = newNode(ID, getCurToken());
        changeCurToNext();
        if (match(ASSIGN)) {   // 如果不是 '=' (assign)，那這個變數就是單個node
            retNode = newNode(ASSIGN, getCurToken());   // root是等號
            changeCurToNext();
            retNode->left = left;   // 變數放等號左邊
            retNode->right = or_expr();   // 右邊運算式去遞迴
        }
        else {   // 如果是給值式，則回傳一個小樹
            retNode = left;
        }
    } else if (match(ADDSUB)) {
        retNode = newNode(ADDSUB, getCurToken());   // 運算子
        retNode->left = newNode(INT, "0");   // 左邊放0
        changeCurToNext();

        if (match(INT)) {
            retNode->right = newNode(INT, getCurToken());
            changeCurToNext();
        } else if (match(ID)) {
            retNode->right = newNode(ID, getCurToken());
            changeCurToNext();
        } else if (match(LPAREN)) {   // 和下面處理括號一樣
            changeCurToNext();
            retNode->right = or_expr();
            if (match(RPAREN))
                changeCurToNext();
            else
                error(MISPAREN);
        } else {
            error(NOTNUMID);   // 不是數字也不是變數的error
        }
    }
    // TODO: INC
    else if (match(INCDEC)) {
        retNode = newIncreDecreTree(curToken[0]);
        changeCurToNext();
    }

    // TODO: 有處理遇到邏輯運算符，會throw error
    else if (match(LPAREN)) {
        changeCurToNext();
        retNode = or_expr();
        if (match(RPAREN)) // 正常執行應該遇到右括號
            changeCurToNext();
        else
            error(MISPAREN);
    } else {
        error(NOTNUMID);   // 不是數字也不是變數
    }
    return retNode;
}



// term := factor term_tail 處理乘除
// 取出最小單位作為左子樹
BTNode *term() {
    BTNode *node = factor();
    return term_tail(node);
}

// 參數為左子樹
BTNode *term_tail(BTNode *left) {
    BTNode *node = NULL;
    if (match(MULDIV)) {    // 乘除當成root
        node = newNode(MULDIV, getCurToken());
        changeCurToNext();
        node->left = left;  // 參數的left裝上去
        node->right = factor();   // 對這個 乘除 來說的右邊運算元
        return term_tail(node);   // 整個小樹當成左子樹在去遞迴找下一個乘除
    } else
        return left;
}   // 沒有乘除了，則回傳一顆root為乘除的樹(上面可能還有+-，上一層單位的事情)

BTNode *expr() {
    BTNode *node = term();
    return expr_tail(node);
}

BTNode *expr_tail(BTNode *left) {
    BTNode *node;
    if (match(ADDSUB)) {   // 加減順序 > 邏輯
        node = newNode(ADDSUB, getCurToken());
        changeCurToNext();
        node->left = left;
        node->right = term();
        return expr_tail(node);
    }
    else
        return left;
    // else if (match(ORXORAND)) {
    //     node = newNode(ORXORAND, getCurToken());
    //     changeCurToNext();
    //     node->left = left;
    //     node->right = term();
    //     return expr_tail(node);
    // }
    
    
}

BTNode *and_expr() {
    BTNode *node = expr();
    return and_tail(node);
}

BTNode *and_tail(BTNode *left) {
    BTNode *node = NULL;
    if (match(AND)) {
        node = newNode(AND, getCurToken());
        changeCurToNext();
        node->left = left;
        node->right = expr();
        return and_tail(node);
    } else
        return left;
}

BTNode *xor_expr() {
    BTNode *node = and_expr();
    return xor_tail(node);
}

BTNode *xor_tail(BTNode *left) {
    BTNode *node = NULL;
    if (match(XOR)) {
        node = newNode(XOR, getCurToken());
        changeCurToNext();
        node->left = left;
        node->right = and_expr();
        return xor_tail(node);
    } else
        return left;
}

BTNode *or_expr() {
    BTNode *node = xor_expr();
    return or_tail(node);
}

BTNode *or_tail(BTNode *left) {
    BTNode *node;
    if (match(OR)) {
        node = newNode(OR, getCurToken());
        changeCurToNext();
        node->left = left;
        node->right = xor_expr();
        return or_tail(node);
    } else
        return left;
}

// statement := END | assign_expr END
void statement() {
    if (match(END))   // 第一行一直輸入newline
        changeCurToNext();
    else if (match(ENDFILE)) {
        for (int i = 0; i < 3; i++) {
            Mov_RegAddr(registers + i, i * VARSIZE);
            registers[i].rData = variables[i].vData;
        }
        printf("EXIT 0\n");
        done = 1;

        if (DEBUG)
        {
            printf("ENDFILE! ------------------------- \n");
            printf("Register Set:\n");
            for (int i = 0; i < MAXREG; i++) {
                printf("%s: %d\n",registers[i].rName, registers[i].rData);
            }
            printf("Variable Set:\n");
            for (int i = 0; i < variableCnt; i++) {
                printf("%s: %d\n", variables[i].vName , variables[i].vData);
            }
        }
        
    } else {
        Root = or_expr();
        if (match(END)) {
            assignment(Root);   // 用當前的樹做assign
            GeneratorCaller(Root);   // 印出當前的樹的指令
            // if (DEBUG) 
            // {
            //     printf("Evaluate: %d\n", evaluateTree(Root));
            //     printf("Prefix traversal: ");
            //     printPrefix(Root);
            //     printf("\n");

            //     printf("Variable Set:\n");
            //     for (int i = 0; i < 10; i++) {
            //         printf("%s: %d\n", variables[i].vName , variables[i].vData);
            //     }
            // }
            if (PRINTERR) printf(">> ");
            changeCurToNext();
        } else {
            error(SYNTAXERR);
        }
    }
}

void initRegister() {
    for (int i = 0; i < MAXREG; i++) {
        memset(registers[i].rName, '\0', sizeof(registers[i].rName));
        registers[i].isUsed = 0;
        registers[i].rName[0] = 'r';
        registers[i].rName[1] = i + '0';
    }
}

int getVariableAddr(char *varName) {
    for (int i = 0; i < variableCnt; i++) {
        if (strcmp(variables[i].vName, varName) == 0) {
            queue[rear++] = i * VARSIZE;
            return i * VARSIZE;
        }
    }
    return -1; // this var dne
}

Register *getEmptyRegister() {
    Register *ret = NULL;
    for (int i = 0; i < MAXREG; i++) {
        if (!registers[i].isUsed) {
            ret = registers + i;
            ret->isUsed = 1;
            break;
        }
    }
    if (ret == NULL)
        error(RUNOUT);
    return ret;
}

void resetRegister(Register *reg) {
    reg->isUsed = 0;
    reg->rData = 0;
}

void GeneratorCaller(BTNode *Root) {
    initRegister();
    for (int i = 0; i < MAXVAR; i++)
        queue[i] = 0;
    front = rear = varOnRight = 0;
    if (Root->tokenType == ASSIGN) {
        Register *ret = assemblyCode(Root);
    } else {
        if (DEBUG) printf("No Assignment!\n");
        error(SYNTAXERR);
    }
}

Register *assemblyCode(BTNode *root) {
    Register *retRegister = NULL, *left, *right;
    if (root != NULL) {
        switch (root->tokenType) {
            case ID: {
                int address = getVariableAddr(root->token);
                retRegister = getEmptyRegister();
                Mov_RegAddr(retRegister, address);
                break;
            }
            case INT:
                retRegister = getEmptyRegister();
                Mov_RegInt(retRegister, atoi(root->token));
                break;
            case ASSIGN: {
                right = assemblyCode(root->right);   // 右邊先做完
                if (right == NULL) {
                    right = getEmptyRegister();
                    Mov_RegAddr(right, queue[front++]);
                }
                if (root->left->left != NULL || root->left->right != NULL)
                    error(SYNTAXERR);
                int address = getVariableAddr(root->left->token);   // 等號左邊的位址
                Mov_AddrReg(address, right);   // 右邊最後的reg
                resetRegister(right);
                break;
            }
            case ADDSUB:
            case MULDIV:
            case OR:
            case XOR:
            case AND:
                left = assemblyCode(root->left);
                if (left == NULL) {
                    left = getEmptyRegister();
                    Mov_RegAddr(left, queue[front++]);
                }
                right = assemblyCode(root->right);
                if (right == NULL) {
                    right = getEmptyRegister();
                    Mov_RegAddr(right, queue[front++]);
                }
                if (root->token[0] == '+')
                    Add(left, right);
                else if (root->token[0] == '-')
                    Sub(left, right);
                else if (root->token[0] == '*')
                    Mul(left, right);
                else if (root->token[0] == '/')
                    Div(left, right);
                else if (root->token[0] == '|')
                    Or(left, right);
                else if (root->token[0] == '^')
                    Xor(left, right);    
                else if (root->token[0] == '&')
                    And(left, right);

                resetRegister(right);
                retRegister = left;
                break;
            default:
                break;
        }
    }
    return retRegister;
}

void Mov_RegReg(Register *x, Register *y) {
    printf("MOV %s %s\n", x->rName, y->rName);
}
void Mov_RegInt(Register *x, int y) {
    printf("MOV %s %d\n", x->rName, y);
}
void Mov_RegAddr(Register *x, int y) {
    printf("MOV %s [%d]\n", x->rName, y);
}
void Mov_AddrReg(int x, Register *y) {
    printf("MOV [%d] %s\n", x, y->rName);
}
void Add(Register *x, Register *y) {
    printf("ADD %s %s\n", x->rName, y->rName);
}
void Sub(Register *x, Register *y) {
    printf("SUB %s %s\n", x->rName, y->rName);
}
void Mul(Register *x, Register *y) {
    printf("MUL %s %s\n", x->rName, y->rName);
}
void Div(Register *x, Register *y) {
    printf("DIV %s %s\n", x->rName, y->rName);
}
void And(Register *x, Register *y) {
    printf("AND %s %s\n", x->rName, y->rName);
}
void Or(Register *x, Register *y) {
    printf("OR %s %s\n", x->rName, y->rName);
}
void Xor(Register *x, Register *y) {
    printf("XOR %s %s\n", x->rName, y->rName);
}

void assignment(BTNode *Root) {
    int result = evaluateTree(Root);
}


int evaluateTree(BTNode *root) {
    int retValue = 0, leftValue = 0, rightValue = 0;

    if (root != NULL) {
        switch (root->tokenType) {
            case ID:
                retValue = getval(root->token);
                if (varOnRight)
                    varOnRight = 2;
                break;
            case INT:
                retValue = atoi(root->token);   // str to int
                break;
            case ASSIGN:
                rightValue = evaluateTree(root->right);
                retValue = setval(root->left->token, rightValue);
                break;
            case ADDSUB:
            case MULDIV:
            case OR:
            case XOR:
            case AND: {
                if (strcmp(root->token, "/") == 0)
                    varOnRight = 1;

                leftValue = evaluateTree(root->left);
                rightValue = evaluateTree(root->right);
                if (strcmp(root->token, "+") == 0)
                    retValue = leftValue + rightValue;
                else if (strcmp(root->token, "-") == 0)
                    retValue = leftValue - rightValue;
                else if (strcmp(root->token, "*") == 0)
                    retValue = leftValue * rightValue;
                else if (strcmp(root->token, "/") == 0) {
                    if (rightValue == 0 && varOnRight == 1) {
                        error(DIVZERO);
                    } else if (rightValue == 0 && varOnRight == 2) {
                        retValue = 0;
                    } else {
                        retValue = leftValue / rightValue;
                    }
                } else if (strcmp(root->token, "|") == 0)
                    retValue = leftValue | rightValue;
                else if (strcmp(root->token, "&") == 0)
                    retValue = leftValue & rightValue;
                else if (strcmp(root->token, "^") == 0)
                    retValue = leftValue ^ rightValue;
                break;
            } 
            default:
                retValue = 0;
        }
    }
    return retValue;
}

void printPrefix(BTNode *root) {
    if (root != NULL) {
        printf("%s ", root->token);
        printPrefix(root->left);
        printPrefix(root->right);
    }
}

void err(ErrorType errorNum) {
    if (PRINTERR) {
        fprintf(stderr, "error: ");
        switch (errorNum) {
            case MISPAREN:
                fprintf(stderr, "mismatched parenthesis\n");
                break;
            case NOTNUMID:
                fprintf(stderr, "number or identifier expected\n");
                break;
            case NOTFOUND:
                fprintf(stderr, "variables not defined\n");
                break;
            case RUNOUT:
                fprintf(stderr, "out of memory\n");
                break;
            case NOTLVAL:
                fprintf(stderr, "lvalue required as an operand\n");
                break;
            case DIVZERO:
                fprintf(stderr, "divide by constant zero\n");
                break;
            case SYNTAXERR:
                fprintf(stderr, "syntax error\n");
                break;
            default:
                fprintf(stderr, "undefined error\n");
                break;
        }
    }
    printf("EXIT 1\n");
    exit(0);
}