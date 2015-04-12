 #include <stdio.h>
# include<stdlib.h>

int POINTER_SIZE = 4;

int examine = 1;

char __stdio__printf__[100] = {
"void __printf__(char * str, int * argu) {}\n"};
//
//ERROR
void ERROR() {
	printf("//////////////  ////////////    ////////////       ////////     ////////////\n");
	printf("//              //         //   //         //     //      //    //         //\n");
	printf("//              //          //  //          //   //        //   //          //\n");
	printf("//              //          //  //          //   //        //   //          //\n");
	printf("//              //         //   //         //   //          //  //         //\n");
	printf("//////////      ///////////     ///////////     //          //  ///////////\n");
	printf("//              //     //       //     //       //          //  //     //\n");
	printf("//              //      //      //      //      //          //  //      //\n");
	printf("//              //       //     //       //      //        //   //       //\n");
	printf("//              //        //    //        //     //        //   //        //\n");
	printf("//              //         //   //         //     //      //    //         //\n");
	printf("//////////////  //          //  //          //     ////////     //          //\n");
	printf("\a\a\a");
	exit(0);
}

int strcmp(char * a, char * b) {
	int i = 0;
	for( ; a[i] != 0 || b[i] != 0; i++) {
		if(a[i] != b[i]) {
			return 1;
		}
	}
	return 0;
}

//vector of char
void push_back(char ** a, int * length, int * capacity, char c) {
	if(*length == *capacity) {
		*capacity *= 2;
		char * tmp = (char*)malloc(*capacity);
		int i;
		for(i = 0; i < *length; i++) {
			tmp[i] = (*a)[i];
		}
		//free(*a);
		*a = tmp;
	}
	
	(*a)[(*length)++] = c;
	//(*a)[*length] = 0;
	//printf("%d\n", *length);
}

int max(int a, int b) {
	if(a > b) {
		return a;
	}else {
		return b;
	}
}

//COMMENT TYPE
int NO_COMMENT = 0, ONE_LINE_COMMENT = 1, MULTI_LINE_COMMENT = 2, INCLUDE = 3, IN_STR = 4, IN_CHR = 5;//ignore #include<...>

int nKeywords = 14;

char keyword[14][9] = {//code: 300+
"typedef",//300
"void",//301
"char",//302
"int",//303
"struct",//304
"union",//305
"if",//306
"else",//307
"while",//308
"for",//309
"continue",//310
"break",//311
"return",//312
"sizeof"//313
};

int nOpers = 43;

char oper[43][4] = {//code 500+
"(",//500
")",//501
";",//502
",",//503
"=",//504
"{",//505
"}",//506
"[",//507
"]",//508
"*",//509
"|",//510
"^",//511
"&",//512
"<",//513
">",//514
"+",//515
"-",//516
//"*",//517
"/",//517
"%",//518
"~",//519
"!",//520
".",//521
"||",//522
"&&",//523
"==",//524
"!=",//525
"<=",//526
">=",//527
"<<",//528
">>",//529
"++",//530
"--",//531
"*=",//532
"/=",//533
"%=",//534
"+=",//535
"-=",//536
"<<=",//537
">>=",//538
"&=",//539
"^=",//540
"|=",//541
"->"//542
};

//TOKEN TYPE
int NO_TOKEN = 0, IDENTIFIER = 400, INT_CONSTANT = 401, CHR_CONSTANT = 402, STR_CONSTANT = 403;

char * program;

int isNewLine(char c) {
	return c == '\n' || c == '\r';
}

int isLetter(char c) {
	return c == '_' || c == '$' || c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z';
}

int isDigit(char c) {
	return c >= '0' && c <= '9';
}

int isOp() {
	int i = 0;
	for( ; i < nOpers; i++) {
		int j = 0;
		int flag = 1;
		for( ; oper[i][j]; j++) {
			if(program[j] != oper[i][j]) {
				flag = 0;
				break;
			}
		}
		if(flag) {
			return 1;
		}
	}
	return 0;
}

int op() {
	int i = 0;
	int ans = 0;
	int res = 0;
	for( ; i < nOpers; i++) {
		int j = 0;
		int flag = 1;
		for( ; oper[i][j]; j++) {
			if(program[j] != oper[i][j]) {
				flag = 0;
				break;
			}
		}
		if(flag && j > ans) {
			res = i;
			ans = j;
		}
	}
	program += ans;
	return res + 500;
}

int hex(char c) {
	if('0' <= c && c <= '9') {
		return c - '0';
	}else if('a' <= c && c <= 'f') {
		return c - 'a' + 10;
	}else if('A' <= c && c <= 'F') {
		return c - 'A' + 10;
	}else {
		return -1;
	}
}

int isHex(char c) {
	return hex(c) != -1;
}

int oct(char c) {
	if('0' <= c && c <= '7') {
		return c - '0';
	}else {
		return -1;
	}
}

int isOct(char c) {
	return oct(c) != -1;
}

int nextChar() {
	if(*program == '\\') {
		program++;
		int res;
		if(*program == 'a') {
			res = 7;
		}else if(*program == 'b') {
			res = 8;
		}else if(*program == 'f') {
			res = 12;
		}else if(*program == 'n') {
			res = 10;
		}else if(*program == 'r') {
			res = 13;
		}else if(*program == 't') {
			res = 9;
		}else if(*program == 'v') {
			res = 11;
		}else if(*program == 'x') {
			if(isHex(program[1])) {
				if(isHex(program[2])) {
					res = hex(program[1]) * 16 + hex(program[2]);
					program++;
				}else {
					res = hex(program[1]);
				}
				program++;
			}else {
				ERROR();
			}
		}else if(isOct(*program)) {
			if(isOct(program[1])) {
				if(isOct(program[2])) {
					if(oct(*program) >= 4) {
						ERROR();
					}else {
						res = oct(program[0]) * 64 + oct(program[1]) * 8 + oct(program[2]);
						program++;
					}
					program++;
				}else {
					res = oct(program[0]) * 8 + oct(program[1]);
				}
			}else {
				res = oct(program[0]);
			}
		}else {
			res = *program;
		}
		program++;
		return res;
	}else {
		if(isNewLine(*program)) {
			ERROR();
		}
		return *(program++);
	}
}

struct Token {
	int type;
	char * name;
	int value;
};

void print(struct Token x) {
	if(x.type == NO_TOKEN) {
		printf("NO_TOKEN\n");
	}else if(x.type == INT_CONSTANT) {
		printf("INT_CONSTANT %d\n", x.value);
	}else if(x.type == CHR_CONSTANT) {
		printf("CHR_CONSTANT %c\n", x.value);
	}else if(x.type == STR_CONSTANT) {
		printf("STR_CONSTANT %s\n", x.name);
	}else if(x.type == IDENTIFIER) {
		printf("IDENTIFIER %s\n", x.name);
	}else if(x.type >= 300 && x.type < 400) {
		if(x.type >= 300 + nKeywords) {
			printf("???token???\n");
		}
		printf("KEYWORD %s\n", keyword[x.type - 300]);
	}else if(x.type >= 500) {
		if(x.type >= 500 + nOpers) {
			printf("???token???\n");
		}
		printf("OPERATOR %s\n", oper[x.type - 500]);
	}
}

int beginOfLine;

struct Token nextToken() {
	struct Token res;
	res.name = 0;
	for(;;) {
		int flag = 1;
		while(*program != 0 && isNewLine(*program)) {
			program++;
			beginOfLine = 1;
			flag = 0;
		}
		if(*program == 0) {
			break;
		}
		while(*program != 0 && (*program == ' ' || *program == '\t')) {
			program++;
			flag = 0;
		}
		if(*program == 0) {
			break;
		}
		if(*program == '#') {
			while(*program != 0 && !isNewLine(*program)) {
				program++;
			}
			if(*program == 0) {
				break;
			}
			flag = 0;
		}
		beginOfLine = 0;
		if(*program == '/' && program[1] == '/') {
			program += 2;
			while(*program != 0 && !isNewLine(*program)) {
				program++;
			}
			if(*program == 0) {
				break;
			}
			program++;
			flag = 0;
		}
		if(*program == '/' && program[1] == '*') {
			program += 2;
			int prev = -1;
			while(*program != 0 && !(prev == '*' && *program == '/')) {
				prev = *program;
				program++;
			}
			if(*program == 0) {
				break;
			}
			program++;
			flag = 0;
		}
		if(flag) {
			break;
		}
	}
	if(*program == 0) {
		res.type = NO_TOKEN;
		return res;
	}
	if(isLetter(*program)) {
		char * bak = program;
		while(isLetter(*program) || isDigit(*program)) {
			program++;
		}
		int i;
		res.type = IDENTIFIER;
		for(i = 0; i < nKeywords; i++) {
			int eq = 1;
			int j = 0;
			for( ; keyword[i][j]; j++) {
				if(bak[j] != keyword[i][j]) {
					eq = 0;
					break;
				}
			}
			if(eq && bak + j == program) {
				res.type = 300 + i;
				break;
			}
		}
		if(res.type == IDENTIFIER) {
			res.name = (char*)malloc(program - bak + 1);
			int i = 0;
			for( ; i < program - bak; i++) {
				res.name[i] = bak[i];
			}
			res.name[program - bak] = 0;
		}
		return res;
	}else if(isDigit(*program)) {
		int base = 10;
		int x = 0;
		if(program[0] == '0' && program[1] == 'x') {
			program += 2;
			base = 16;
		}else if(program[0] == '0') {
			program += 1;
			base = 8;
		}
		while(isHex(*program)) {
			if(isOct(*program)) {
				x = x * base + *program - '0';
			}else if(base == 8) {
				ERROR();
			}else if(isDigit(*program)) {
				x = x * base + *program - '0';
			}else if(base == 10) {
				ERROR();
			}else if(isHex(*program)) {
				x = x * base + hex(*program);
			}else {
				ERROR();
			}
			program++;
		}
		if(isLetter(*program)) {
			ERROR();//etc. 123aa
		}
		res.type = INT_CONSTANT;
		res.value = x;
		return res;
	}else if(*program == '\'') {
		program++;
		if(*program == '\'') {
			ERROR();
		}
		res.value = nextChar();
		if(res.value != 0 && *program == '\'') {
			program++;
			res.type = CHR_CONSTANT;
			return res;
		}else {
			ERROR();
		}
	}else if(*program == '"') {
		program++;
		char * bak = program;
		int cnt = 0;
		for(;;) {
			if(*program == '"') {
				res.name = (char*)malloc(cnt + 1);
				char * bak2 = program;
				program = bak;
				int index = 0;
				while(program != bak2) {
					res.name[index++] = nextChar();
				}
				program++;
				res.name[cnt] = 0;
				res.type = STR_CONSTANT;
				return res;
			}else if(*program == '\n' || *program == '\r' || *program == 0) {
				ERROR();
			}else {
				cnt++;
				int x = nextChar();
				if(x == 0) {
					ERROR();
				}
			}
		}
	}else if(isOp()) {
		res.type = op();
		return res;
	}else {
		ERROR();
	}

}

void printTokens() {
	struct Token x;
	while((x = nextToken()).type != NO_TOKEN) {
		print(x);
	}
}

struct List {
	int value;
	int mul, tmp;
	struct List * next, * prev;
} TMP;

struct Type;

struct Variable {
	char * name;
	int level;//count of '*'
	struct Type * type;//basic type
	struct List * list;//dimensions of array
	struct Variable * next;
};

struct Variable * newVariable() {
	struct Variable * res = (struct Variable *)malloc(sizeof(struct Variable));
	res->name = 0;
	res->level = 0;
	res->type = 0;
	res->list = 0;
	res->next = 0;
	return res;
}

struct Function {
	char * name;
	struct Variable * rtn;//return type
	struct Variable * argu;//arguments type
	struct Instruction * insts;
	struct Function * next;
} * funcs, * chief, * calculator;

struct Type {
	char * name;
	int type;//0 int, 1 char, 2 struct, 3 union, 4 void, 5 function
	struct Type * next;//used for SymbolList
	struct Variable * vars;//members
	int size;
} CHAR_TYPE, INT_TYPE, VOID_TYPE, FUNC_TYPE;

void initBasicTypeName() {
	CHAR_TYPE.name = 0;
	CHAR_TYPE.type = 1;
	CHAR_TYPE.next = 0;
	CHAR_TYPE.vars = 0;
	CHAR_TYPE.size = 1;
	INT_TYPE.name = 0;
	INT_TYPE.type = 0;
	INT_TYPE.next = 0;
	INT_TYPE.vars = 0;
	INT_TYPE.size = 4;
	VOID_TYPE.name = 0;
	VOID_TYPE.type = 4;
	VOID_TYPE.next = 0;
	VOID_TYPE.vars = 0;
	VOID_TYPE.size = 1;//!!!
	FUNC_TYPE.name = 0;
	FUNC_TYPE.type = 5;
	FUNC_TYPE.next = 0;
	FUNC_TYPE.vars = 0;
	FUNC_TYPE.size = 0;//!!!
}

struct Token look;

void move() {
	look = nextToken();
}

void match(int type) {
	if(look.type == type) {
		move();
	}else {
		ERROR();
	}
}

struct SymbolList {
	struct SymbolList * prev;
	struct Variable * vars;
	struct Type * QaQ;//structs & unions
};

struct SymbolList * top, * base;

void clear() {
	top = (struct SymbolList *)malloc(sizeof(struct SymbolList));
	top->prev = 0;
	top->vars = 0;
	top->QaQ = 0;
}

int nLabel = 0;

struct Operand {
	int constant;//编译时常数?
	int value;//如果是编译时常数, 值?
	int type;//0 直接左值, 1 解引用左值, 2 右值
	struct Variable * var;//操作数和变量类型
};

int label = 0;

int newLabel() {
	return label++;
}

struct Instruction {
	int type;//
	int n;
	struct Operand * a;
	struct Operand * b;
	struct Operand * c;
	struct Instruction * next;
	struct Function * f;
};

int isAssignmentOperator(int x) {
	return x == 504 || (x >= 532 && x <= 541);
}

int notExpression(int x) {
	return x == 501 || x == 502 || x == 505 || x == 506 || x == 508;
	//        ')'      ';'          '{'          '}'            ']'
}

struct Operand * constIntOrChar(int i) {
	struct Operand * res = (struct Operand *)malloc(sizeof(struct Operand));
	res->type = 2;
	res->constant = 1;
	res->value = i;
	res->var = (struct Variable *)malloc(sizeof(struct Variable));
	res->var->level = 0;
	res->var->name = 0;
	res->var->next = 0;
	res->var->list = 0;
	return res;
}

struct Operand * constInt(int i) {//返回一个常量i
	struct Operand * res = constIntOrChar(i);
	res->var->type = &INT_TYPE;
	return res;
}

struct Operand * constChar(int i) {//返回一个常量i
	struct Operand * res = constIntOrChar(i);
	res->var->type = &CHAR_TYPE;
	return res;
}

struct Type * find(char * );

struct Variable * findVariable(char * );

struct Operand * parseAssignmentExpression(struct Function * );

struct Operand * parseExpression(struct Function * env);

int
GET_ARGU = 0,
DECL_POINTER = 1,
DECL_CHAR = 2,
DECL_INT = 3,
MALLOC = 4,
GETCHAR = 5,
PUTCHAR = 6,
NOP = 7,
ASSIGN_ADD = 8,
GOTO = 9,
LABEL = 10,
IF_GOTO = 11,
IF_FALSE_GOTO = 12,
ASSIGN_LOGICAL_NOT = 13,
ASSIGN_NOT = 14,
ASSIGN_NEGATE = 15,
ASSIGN = 16,
ASSIGN_CHAR = 17,
ASSIGN_ADDRESS = 18,
ASSIGN_INCLUSIVE_OR = 19,
ASSIGN_EXCLUSIVE_OR = 20,
ASSIGN_AND = 21,
ASSIGN_SHR = 22,
ASSIGN_SHL = 23,
ASSIGN_SUB = 24,
CALL = 25,
ASSIGN_MOD = 26,
ASSIGN_DEV = 27,
ASSIGN_MUL = 28,
ASSIGN_NOT_EQUAL_TO = 29,
ASSIGN_EQUAL_TO = 30,
ASSIGN_GREATER_THAN_OR_EQUAL_TO = 31,
ASSIGN_LESS_THAN_OR_EQUAL_TO = 32,
ASSIGN_GREATER_THAN = 33,
ASSIGN_LESS_THAN = 34,
ASSIGN_LOGIC_OR = 35,
ASSIGN_LOGIC_AND = 36,
ASSIGN_DEREF = 37,
CAST_TO_CHAR = 38,
CAST_TO_INT = 39,
DEREF_ASSIGN_ADDRESS = 40,
DEREF_ASSIGN = 41,
DEREF_ASSIGN_CHAR = 42,
RETURN = 43,
ASSIGN_ADDRESS_OF = 44,
ARGU = 45,
EXIT = 46,
VOID_RETURN = 47;

void printOperand(struct Operand * ope) {
	printf("%d", ope->var);
	if(ope->constant) {
		printf("(constant ");
		if(ope->var->type == &CHAR_TYPE && ope->var->level == 0 && ope->var->list == 0) {
			printf("'%c'", ope->value);
		}else {
			printf("%d", ope->value);
		}
		printf(")");
	}
}

void printIntermediateCode(struct Instruction * inst) {
	if(inst->type == GET_ARGU) {
		printf("get_argument "), printOperand(inst->a), printf("\n");
	}else if(inst->type == DECL_POINTER) {
		printf("declarate pointer "), printOperand(inst->a), printf("\n");
	}else if(inst->type == DECL_CHAR) {
		printf("declarate char "), printOperand(inst->a), printf("\n");
	}else if(inst->type == DECL_INT) {
		printf("declarate int "), printOperand(inst->a), printf("\n");
	}else if(inst->type == MALLOC) {
		printOperand(inst->a), printf(" = malloc "), printOperand(inst->b), printf("\n");
	}else if(inst->type == GETCHAR) {
		printOperand(inst->a), printf(" = getchar\n");
	}else if(inst->type == PUTCHAR) {
		printf("putchar "), printOperand(inst->a), printf("\n");
	}else if(inst->type == NOP) {
		printf("nop\n");
	}else if(inst->type == ASSIGN_ADD) {
		printOperand(inst->a), printf(" = "), printOperand(inst->b), printf(" + "), printOperand(inst->c), printf("\n");
	}else if(inst->type == GOTO) {
		printf("goto L%d\n", inst->n);
	}else if(inst->type == LABEL) {
		printf("L%d: ", inst->n);
	}else if(inst->type == IF_GOTO) {
		printf("if "), printOperand(inst->a), printf(" goto %d\n", inst->n);
	}else if(inst->type == IF_FALSE_GOTO) {
		printf("if false "), printOperand(inst->a), printf(" goto %d\n", inst->n);
	}else if(inst->type == ASSIGN_LOGICAL_NOT) {
		printOperand(inst->a), printf(" = !"), printOperand(inst->b), printf("\n");
	}else if(inst->type == ASSIGN_NOT) {
		printOperand(inst->a), printf(" = ~"), printOperand(inst->b), printf("\n");
	}else if(inst->type == ASSIGN_NEGATE) {
		printOperand(inst->a), printf(" = -"), printOperand(inst->b), printf("\n");
	}else if(inst->type == ASSIGN) {
		printOperand(inst->a), printf(" = "), printOperand(inst->b), printf("\n");
	}else if(inst->type == ASSIGN_CHAR) {
		printf("char assign "), printOperand(inst->a), printf(" = "), printOperand(inst->b), printf("\n");
	}else if(inst->type == ASSIGN_ADDRESS) {
		printf("address assign "), printOperand(inst->a), printf(" = "), printOperand(inst->b), printf("\n");
	}else if(inst->type == ASSIGN_INCLUSIVE_OR) {
		printOperand(inst->a), printf(" = "), printOperand(inst->b), printf(" | "), printOperand(inst->c), printf("\n");
	}else if(inst->type == ASSIGN_EXCLUSIVE_OR) {
		printOperand(inst->a), printf(" = "), printOperand(inst->b), printf(" ^ "), printOperand(inst->c), printf("\n");
	}else if(inst->type == ASSIGN_AND) {
		printOperand(inst->a), printf(" = "), printOperand(inst->b), printf(" & "), printOperand(inst->c), printf("\n");
	}else if(inst->type == ASSIGN_SHR) {
		printOperand(inst->a), printf(" = "), printOperand(inst->b), printf(" >> "), printOperand(inst->c), printf("\n");
	}else if(inst->type == ASSIGN_SHL) {
		printOperand(inst->a), printf(" = "), printOperand(inst->b), printf(" << "), printOperand(inst->c), printf("\n");
	}else if(inst->type == ASSIGN_SUB) {
		printOperand(inst->a), printf(" = "), printOperand(inst->b), printf(" - "), printOperand(inst->c), printf("\n");
	}else if(inst->type == ASSIGN_MOD) {
		printOperand(inst->a), printf(" = "), printOperand(inst->b), printf(" %% "), printOperand(inst->c), printf("\n");
	}else if(inst->type == ASSIGN_DEV) {
		printOperand(inst->a), printf(" = "), printOperand(inst->b), printf(" / "), printOperand(inst->c), printf("\n");
	}else if(inst->type == ASSIGN_MUL) {
		printOperand(inst->a), printf(" = "), printOperand(inst->b), printf(" * "), printOperand(inst->c), printf("\n");
	}else if(inst->type == ASSIGN_NOT_EQUAL_TO) {
		printOperand(inst->a), printf(" = "), printOperand(inst->b), printf(" != "), printOperand(inst->c), printf("\n");
	}else if(inst->type == ASSIGN_EQUAL_TO) {
		printOperand(inst->a), printf(" = "), printOperand(inst->b), printf(" == "), printOperand(inst->c), printf("\n");
	}else if(inst->type == ASSIGN_GREATER_THAN_OR_EQUAL_TO) {
		printOperand(inst->a), printf(" = "), printOperand(inst->b), printf(" >= "), printOperand(inst->c), printf("\n");
	}else if(inst->type == ASSIGN_GREATER_THAN) {
		printOperand(inst->a), printf(" = "), printOperand(inst->b), printf(" > "), printOperand(inst->c), printf("\n");
	}else if(inst->type == ASSIGN_LESS_THAN) {
		printOperand(inst->a), printf(" = "), printOperand(inst->b), printf(" < "), printOperand(inst->c), printf("\n");
	}else if(inst->type == ASSIGN_LOGIC_OR) {
		printOperand(inst->a), printf(" = "), printOperand(inst->b), printf(" || "), printOperand(inst->c), printf("\n");
	}else if(inst->type == ASSIGN_LOGIC_AND) {
		printOperand(inst->a), printf(" = "), printOperand(inst->b), printf(" && "), printOperand(inst->c), printf("\n");
	}else if(inst->type == ASSIGN_LESS_THAN_OR_EQUAL_TO) {
		printOperand(inst->a), printf(" = "), printOperand(inst->b), printf(" <= "), printOperand(inst->c), printf("\n");
	}else if(inst->type == ASSIGN_DEREF) {
		printOperand(inst->a), printf(" = *"),  printOperand(inst->b), printf("\n");
	}else if(inst->type == CAST_TO_CHAR) {
		printOperand(inst->a), printf(" = (char)"),  printOperand(inst->b), printf("\n");
	}else if(inst->type == CAST_TO_INT) {
		printOperand(inst->a), printf(" = (int)"),  printOperand(inst->b), printf("\n");
	}else if(inst->type == DEREF_ASSIGN_ADDRESS) {
		printf("address assign *"), printOperand(inst->a), printf(" = "), printOperand(inst->b), printf("\n");
	}else if(inst->type == DEREF_ASSIGN) {
		printf("*"), printOperand(inst->a), printf(" = "), printOperand(inst->b), printf("\n");
	}else if(inst->type == DEREF_ASSIGN_CHAR) {
		printf("char assign *"), printOperand(inst->a), printf(" = "), printOperand(inst->b), printf("\n");
	}else if(inst->type == RETURN) {
		printf("return "), printOperand(inst->a), printf("\n");
	}else if(inst->type == VOID_RETURN) {
		printf("return (void)\n");
	}else if(inst->type == EXIT) {
		printf("exit "), printOperand(inst->a), printf("\n");
	}else if(inst->type == ASSIGN_ADDRESS_OF) {
		printOperand(inst->a), printf(" = &"), printOperand(inst->b), printf("\n");
	}else if(inst->type == CALL) {
		printOperand(inst->a), printf(" = call %s %d\n", inst->f->name, inst->n);
	}else if(inst->type == ARGU) {
		printf("argu %d"), printOperand(inst->a), printf("\n");
	}else {
		printf("\n\n???instruction???%d\n\n", inst->type);
	}
	//printf("%d\n", inst->a);
	//if(inst->a) {
	//	printf("%d %d\n", inst->a->type, inst->a->constant);
	//}
	//if(inst->a && inst->a->constant) {
	//	printf("constant %d\n", inst->a->value);
	//}
}
//print命令中, 只有赋值提供全部操作数, 其他运算都省去左边操作数作为临时操作数新建并返回.

struct Operand * newOperand() {
	struct Operand * res = (struct Operand *)malloc(sizeof(struct Operand));
	res->constant = 0;
	res->type = 2;
	res->var = newVariable();
	return res;
}

struct Instruction * newInstruction() {
	struct Instruction * inst = (struct Instruction *)malloc(sizeof(struct Instruction));
	inst->f = 0;
	inst->a = 0;
	inst->b = 0;
	inst->c = 0;
	return inst;
}

void push(struct Function * env, struct Instruction * inst) {
	inst->next = env->insts;
	env->insts = inst;
}

struct Operand * printCast(struct Function * env, struct Variable * a, struct Operand * b);

int isStruct(struct Variable * v) {
	return v->level == 0 && (v->type->type == 2 || v->type->type == 3);
}

struct Operand * getValue(struct Function * env, struct Operand * a) {
	if(a->type == 1) {
		struct Instruction * inst = newInstruction();
		inst->type = ASSIGN_DEREF;
		inst->a = newOperand();
		*inst->a->var = *a->var;
		inst->b = a;
		push(env, inst);
		return inst->a;
	}else {
		return a;
	}
}

struct Operand * printMemberAccess(struct Function * env, struct Operand * a, char * name);

int calcElementSize(struct Variable * var) {
	if(var->level == 0) {
		return var->type->size;
	}else {
		return POINTER_SIZE;
	}
}

int calcSize(struct Variable * var) {
	if(var->list == 0) {
		return calcElementSize(var);
	}else {
		//printf("calcsize %d\n", var->list->mul);
		return calcElementSize(var) * var->list->mul;
	}
}

void printAssign(struct Function * env, struct Operand * a, struct Operand * b) {//要处理是普通左值还是解引用左值
	if(a->var->list) {
		ERROR();
	}
	if(b->var->list) {
		struct Operand * c = printCast(env, a->var, b);
		struct Instruction * inst = newInstruction();
		inst->type = ASSIGN_ADDRESS;
		inst->a = a;
		inst->b = c;
		push(env, inst);
	} else if(a->type == 0) {
		b = getValue(env, b);
		struct Operand * c = printCast(env, a->var, b);
		struct Instruction * inst = newInstruction();
		if(a->var->level) {
			inst->type = ASSIGN_ADDRESS;
		}else if(a->var->type == &INT_TYPE) {
			inst->type = ASSIGN;//a = b;
		}else if(a->var->type == &CHAR_TYPE) {
			inst->type = ASSIGN_CHAR;
		}
		inst->a = a;
		inst->b = c;
		push(env, inst);
	}else if(a->type == 1) {
		if(isStruct(a->var)) {
			struct Operand * c = printCast(env, a->var, b);
			struct Variable * p = a->var->type->vars;
			int i = 0, s = calcSize(a->var);
			for( ; i < s; i++) {
				struct Instruction * inst = newInstruction();
				inst->type = ASSIGN_ADD;
				inst->a = newOperand();
				inst->a->var->type = &CHAR_TYPE;
				inst->a->type = 1;
				inst->b = a;
				inst->c = constInt(i);
				push(env, inst);
				struct Instruction * inst1 = newInstruction();
				inst1->type = ASSIGN_ADD;
				inst1->a = newOperand();
				inst1->a->var->type = &CHAR_TYPE;
				inst1->a->type = 1;
				inst1->b = b;
				inst1->c = constInt(i);
				push(env, inst1);
				printAssign(env, inst->a, inst1->a);
			}
		}else { 
			b = getValue(env, b);
			struct Operand * c = printCast(env, a->var, b);
			struct Instruction * inst = newInstruction();
			if(a->var->level) {
				inst->type = DEREF_ASSIGN_ADDRESS;
			}else if(a->var->type == &INT_TYPE) {
				inst->type = DEREF_ASSIGN;//*a = b;
			}else if(a->var->type == &CHAR_TYPE) {
				inst->type = DEREF_ASSIGN_CHAR;
			}
			inst->a = a;
			inst->b = c;
			push(env, inst);
		}
	}else {
		ERROR();
	}
}

int isIntOrChar(struct Variable * var) {
	return (var->type == &INT_TYPE || var->type == &CHAR_TYPE) && var->level == 0 && var->list == 0;
}

struct Operand * printAssignOp(struct Function * env, struct Operand * b, struct Operand * c, int op);

struct Operand * printAccess(struct Function * env, struct Operand * a, struct Operand * b) {
	if(!isIntOrChar(b->var)) {
		ERROR();
	}
	if(a->var->list || a->var->level) {
		struct Operand * res = newOperand();
		*res->var = *a->var;
		if(a->var->list) {
			res->var->list = a->var->list->next;
		}else {
			res->var->level = a->var->level - 1;
		}
		res->type = 1;
		res->constant = 0;
		struct Instruction * inst = newInstruction();
		inst->type = ASSIGN_ADD;
		inst->a = res;
		inst->b = a;
		inst->c = printAssignOp(env, b, constInt(calcSize(res->var)), 532);
		push(env, inst);
		return res;
	}else {
		ERROR();
	}
}

void printArgu(struct Function * env, struct Operand * a) {
	struct Instruction * inst = newInstruction();
	inst->type = ARGU;
	inst->a = getValue(env, a);
	push(env, inst);
}

int compArray(struct List * p, struct List * q) {//比较数组维度
	if(!p && !q) {//维数相同, 范围对应相同
		return 1;
	}
	if(!p || !q) {
		return 0;
	}
	if(p->value != q->value) {
		return 0;
	}
	return compArray(p->next, q->next);
}

int compType(struct Variable * a, struct Variable * b) {//比较类型
	if(a->level != b->level) {//比较指针阶数
		return 0;
	}
	if(a->type != b->type) {//比较基本类型
		return 0;
	}
	if(!compArray(a->list, b->list)) {//比较数组维度
		return 0;
	}
	return 1;
}

int calcDepth(struct List * p) {
	int res = 0;
	while(p) {
		p = p->next;
		res++;
	}
	return res;
}

struct Operand * printCast(struct Function * env, struct Variable * b, struct Operand * a) {
	printf("%d %d\n", b->level, &INT_TYPE);
	if(compType(b, a->var)) {
		return a;
	}else {
		if(b->list == 0 && a->var->list == 0) {
			if(b->level == a->var->level) {
				if(b->level == 0) {
					if(a->var->type == b->type) {
						return a;
					}else if(a->var->type == &INT_TYPE && b->type == &CHAR_TYPE) {
						struct Instruction * inst = newInstruction();
						inst->type = CAST_TO_CHAR;
						inst->a = newOperand();
						inst->a->constant = a->constant;
						inst->a->value = a->value;
						inst->a->type = 2;
						inst->a->var->type = &CHAR_TYPE;
						inst->b = a;
						push(env, inst);
						return inst->a;
					}else if(a->var->type == &CHAR_TYPE && b->type == &INT_TYPE) {
						struct Instruction * inst = newInstruction();
						inst->type = CAST_TO_INT;
						inst->a = newOperand();
						inst->a->constant = a->constant;
						inst->a->value = a->value;
						inst->a->type = 2;
						inst->a->var->type = &INT_TYPE;
						inst->b = a;
						push(env, inst);
						return inst->a;
					}
				}else {
					return a;//地址不用转换
				}
			}else {
				if(isIntOrChar(b) || isIntOrChar(a->var)) {
					return a;//指针和int可以直接转换
				}else {
					ERROR();
				}
			}
		}else {
			int n1 = calcDepth(b->list), n2 = calcDepth(a->var->list);
			//printf("printCast %d %d %d %d\n", n1, n2, b->level, a->var->level);
			if(a->var->type == b->type && n1 == 0 && n2 == 1 && b->level == a->var->level + 1) {
				struct Instruction * inst = newInstruction();
				inst->type = ASSIGN_ADDRESS;
				inst->a = newOperand();
				*inst->a->var  = *b;
				inst->b = a;
				push(env, inst);
				return inst->a;//xxx [2] --> xxx *
			}else {
				ERROR();
			}
		}
	}
}

struct Operand * printCall(struct Function * env, struct Function * f, int n) {
	struct Instruction * inst = newInstruction();
	struct Operand * ope = newOperand();
	ope->constant = 0;
	ope->type = 2;
	*ope->var = *f->rtn;
	inst->a = ope;
	inst->type = CALL;
	inst->f = f;
	inst->n = n;
	push(env, inst);
	return ope;
}

struct Variable * findMem(struct Variable * vars, char * name) ;

struct Operand * printMemberAccess(struct Function * env, struct Operand * a, char * name) {
	//printf("%s %d\n", a->var->type->name, a->var->level);
	if(!isStruct(a->var)) {
		ERROR();
	}else {
		if(a->var->type->type == 3) {
			struct Instruction * inst = newInstruction();
			inst->type = ASSIGN_ADDRESS;
			inst->a = newOperand();
			*inst->a->var = *findMem(a->var->type->vars, name);
			if(a->type == 1) {
				inst->a->type = 1;
			}else {
				inst->a->type = 2;
			}
			inst->a->constant = 0;
			inst->b = a;
			push(env, inst);
			return inst->a;
		}else if(a->var->type->type == 2) {
			struct Variable * p = a->var->type->vars;
			int cnt = 0;
			while(p) {
				printf("printMemberAccess %s %s\n", p->name, name);
				if(!strcmp(p->name, name)) {
					struct Instruction * inst = newInstruction();
					inst->type = ASSIGN_ADD;
					inst->a = newOperand();
					*inst->a->var = *p;
					if(a->type == 1) {
						inst->a->type = 1;
					}else {
						inst->a->type = 2;
					}
					inst->a->constant = 0;
					inst->b = a;
					inst->c = constInt(cnt);
					push(env, inst);
					return inst->a;
				}
				cnt += calcSize(p);
				p = p->next;
			}
		}else {
			ERROR();
		}
	}
}

struct Operand * printDeref(struct Function * env, struct Operand * a) {
	struct Instruction * inst = newInstruction();
	inst->type = ASSIGN_ADDRESS;
	inst->a = newOperand();
	inst->a->type = 1;
	inst->a->constant = 0;
	*inst->a->var = *a->var;
	inst->b = getValue(env, a);
	if(a->var->list || a->var->level == 0) {
		ERROR();
	}
	inst->a->var->level--;
	push(env, inst);
	return inst->a;
}

struct Operand * printCopy(struct Function * env, struct Operand * a) {//只在后缀自增和自减里面用到了.
	if(isStruct(a->var) || a->var->list) {
		ERROR();
	}
	a = getValue(env, a);
	struct Instruction * inst = newInstruction();
	inst->a = newOperand();
	*inst->a->var = *a->var;
	inst->a->constant = 0;
	inst->a->type = 2;
	if(a->var->level) {
		inst->type = ASSIGN_ADDRESS;
	}else if(a->var->type == &INT_TYPE) {
		inst->type = ASSIGN;
	}else {
		inst->type = ASSIGN_CHAR;
	}
	inst->b = a;
	push(env, inst);
	return inst->a;
}

int isPointer(struct Variable * v) {
	return v->list == 0 && v->level >= 1;
}

//下面还没检查
struct Operand * printAssignOp(struct Function * env, struct Operand * b, struct Operand * c, int op) {
	if(b->var->list || c->var->list || isStruct(b->var) || isStruct(c->var)) {
		ERROR();
	}
	if(b->var->type == &VOID_TYPE && b->var->level == 1 || c->var->type == &VOID_TYPE && c->var->level == 1) {
		ERROR();
	}
	struct Instruction * inst = newInstruction();
	b = getValue(env, b);
	c = getValue(env, c);
	//printf("printAssignOp\n");
	if(op == 535 || op == 536) {
		if(isIntOrChar(b->var) && isIntOrChar(c->var)) {
			if(op == 535) {
				inst->type = ASSIGN_ADD;
			}else {
				inst->type = ASSIGN_SUB;
			}
			inst->a = newOperand();
			inst->a->var->type = &INT_TYPE;
			inst->b = printCast(env, inst->a->var, b);
			inst->c = printCast(env, inst->a->var, c);
			if(inst->b->constant && inst->c->constant) {
				inst->a->constant = 1;
				if(op == 535) {
					inst->a->value = inst->b->value + inst->c->value;
				}else {
					inst->a->value = inst->b->value - inst->c->value;
				}
			}
			push(env, inst);
			return inst->a;
		}else if(isPointer(b->var) || isPointer(c->var)) {
			if(isPointer(b->var) && isPointer(c->var) && compType(b->var, c->var) && op == 536) {
				inst->type = ASSIGN_SUB;//指针相减
				inst->a = newOperand();
				inst->a->var->type = &INT_TYPE;
				inst->b = b;
				inst->c = c;
				push(env, inst);
				b->var->level--;
				struct Operand * ope = constInt(calcSize(b->var));
				b->var->level++;
				return printAssignOp(env, inst->a, ope, 533);
			}else {

				if(op == 535) {
					inst->type = ASSIGN_ADD;
				}else {
					inst->type = ASSIGN_SUB;
				}
				if(isPointer(c->var)) {
					if(op == 536) {
						ERROR();
					}
					struct Operand * tmp = b;
					b = c;
					c = tmp;
				}
				if(isPointer(c->var) || b->var->type == &VOID_TYPE && b->var->level == 1) {
					ERROR();
				}
				inst->a = newOperand();
				*inst->a->var = *b->var;
				inst->b = b;
				b->var->level--;
				inst->c = printAssignOp(env, constInt(calcSize(b->var)), c, 532);
				b->var->level++;
				push(env, inst);
				return inst->a;
			}
		}else {
			ERROR();
		}
	}else {
		inst->a = newOperand();
		inst->a->var->type = &INT_TYPE;
		inst->b = printCast(env, inst->a->var, b);
		inst->c = printCast(env, inst->a->var, c);
		if((isPointer(b->var) || isPointer(c->var)) && op != 524 && op != 525 && op != 523 && op != 522 && op != 513 && op != 514 && op != 526 && op != 527) {
			ERROR();
		}
		if(op == 523) {
			inst->type = ASSIGN_LOGIC_AND;
			if(inst->b->constant && inst->c->constant) {
				inst->a->constant = 1;
				inst->a->value = inst->b->value && inst->c->value;
			}
		}else if(op == 522) {
			inst->type = ASSIGN_LOGIC_OR;
			if(inst->b->constant && inst->c->constant) {
				inst->a->constant = 1;
				inst->a->value = inst->b->value || inst->c->value;
			}
		}else if(op == 513) {
			inst->type = ASSIGN_LESS_THAN;
			if(inst->b->constant && inst->c->constant) {
				inst->a->constant = 1;
				inst->a->value = inst->b->value < inst->c->value;
			}
		}else if(op == 514) {
			inst->type = ASSIGN_GREATER_THAN;
			if(inst->b->constant && inst->c->constant) {
				inst->a->constant = 1;
				inst->a->value = inst->b->value > inst->c->value;
			}
		}else if(op == 526) {
			inst->type = ASSIGN_LESS_THAN_OR_EQUAL_TO;
			if(inst->b->constant && inst->c->constant) {
				inst->a->constant = 1;
				inst->a->value = inst->b->value <= inst->c->value;
			}
		}else if(op == 527) {
			inst->type = ASSIGN_GREATER_THAN_OR_EQUAL_TO;
			if(inst->b->constant && inst->c->constant) {
				inst->a->constant = 1;
				inst->a->value = inst->b->value >= inst->c->value;
			}
		}else if(op == 524) {
			inst->type = ASSIGN_EQUAL_TO;
			if(inst->b->constant && inst->c->constant) {
				inst->a->constant = 1;
				inst->a->value = inst->b->value == inst->c->value;
			}
		}else if(op == 525) {
			inst->type = ASSIGN_NOT_EQUAL_TO;
			if(inst->b->constant && inst->c->constant) {
				inst->a->constant = 1;
				inst->a->value = inst->b->value != inst->c->value;
			}
		}else if(op == 532) {
			inst->type = ASSIGN_MUL;
			if(inst->b->constant && inst->c->constant) {
				inst->a->constant = 1;
				inst->a->value = inst->b->value * inst->c->value;
			}
		}else if(op == 533) {
			inst->type = ASSIGN_DEV;
			if(inst->b->constant && inst->c->constant) {
				inst->a->constant = 1;
				inst->a->value = inst->b->value / inst->c->value;
			}
		}else if(op == 534) {
			inst->type = ASSIGN_MOD;
			if(inst->b->constant && inst->c->constant) {
				inst->a->constant = 1;
				inst->a->value = inst->b->value % inst->c->value;
			}
		}else if(op == 535) {
			inst->type = ASSIGN_ADD;
			if(inst->b->constant && inst->c->constant) {
				inst->a->constant = 1;
				inst->a->value = inst->b->value + inst->c->value;
			}
		}else if(op == 536) {
			inst->type = ASSIGN_SUB;
			if(inst->b->constant && inst->c->constant) {
				inst->a->constant = 1;
				inst->a->value = inst->b->value - inst->c->value;
			}
		}else if(op == 537) {
			inst->type = ASSIGN_SHL;
			if(inst->b->constant && inst->c->constant) {
				inst->a->constant = 1;
				inst->a->value = inst->b->value << inst->c->value;
			}
		}else if(op == 538) {
			inst->type = ASSIGN_SHR;
			if(inst->b->constant && inst->c->constant) {
				inst->a->constant = 1;
				inst->a->value = inst->b->value >> inst->c->value;
			}
		}else if(op == 539) {
			inst->type = ASSIGN_AND;
			if(inst->b->constant && inst->c->constant) {
				inst->a->constant = 1;
				inst->a->value = inst->b->value & inst->c->value;
			}
		}else if(op == 540) {
			inst->type = ASSIGN_EXCLUSIVE_OR;
			if(inst->b->constant && inst->c->constant) {
				inst->a->constant = 1;
				inst->a->value = inst->b->value ^ inst->c->value;
			}
		}else if(op == 541) {
			inst->type = ASSIGN_INCLUSIVE_OR;
			if(inst->b->constant && inst->c->constant) {
				inst->a->constant = 1;
				inst->a->value = inst->b->value | inst->c->value;
			}
		}
		push(env, inst);
		return inst->a;
	}
}

struct Operand * printAddressOf(struct Function * env, struct Operand * a) {
	if(a->var->list) {//只能对直接左值取地址. 因为直接左值才是用DeclXXXX声明的.
		ERROR();//阉割版,不允许对数组取地址, 保证处理的变量全都是基本类型的指针的数组.
	}
	struct Instruction * inst = newInstruction();
	if(a->type == 0) {
		inst->type = ASSIGN_ADDRESS_OF;
	}else if(a->type == 1) {
		inst->type = ASSIGN_ADDRESS;
	}else {
		ERROR();
	}
	inst->a = newOperand();
	inst->b = a;
	*inst->a->var = *a->var;
	inst->a->var->level++;
	inst->a->constant = 0;
	inst->a->type = 2;
	push(env, inst);
	return inst->a;
}

struct Operand * printPosite(struct Function * env, struct Operand * a) {
	if(!isIntOrChar(a->var)) {
		ERROR();
	}
	a = getValue(env, a);
	struct Instruction * inst = newInstruction();
	inst->type = ASSIGN;
	inst->a = newOperand();
	inst->a->var->type = &INT_TYPE;
	inst->b = a = printCast(env, inst->a->var, a);
	if(a->constant) {
		inst->a->constant = 1;
		inst->a->value = a->value;
	}
	push(env, inst);
	return inst->a;
}

struct Operand * printNegate(struct Function * env, struct Operand * a) {
	if(!isIntOrChar(a->var)) {
		ERROR();
	}
	a = getValue(env, a);
	struct Instruction * inst = newInstruction();
	inst->type = ASSIGN_NEGATE;
	inst->a = newOperand();
	inst->a->var->type = &INT_TYPE;
	inst->a->type = 2;
	inst->b = a = printCast(env, inst->a->var, a);
	if(a->constant) {
		inst->a->constant = 1;
		inst->a->value = -a->value;
	}
	push(env, inst);
	return inst->a;
}

struct Operand * printNot(struct Function * env, struct Operand * a) {
	if(!isIntOrChar(a->var)) {
		ERROR();
	}
	a = getValue(env, a);
	struct Instruction * inst = newInstruction();
	inst->type = ASSIGN_NOT;
	inst->a = newOperand();
	inst->a->var->type = &INT_TYPE;
	inst->b = a = printCast(env, inst->a->var, a);
	if(a->constant) {
		inst->a->constant = 1;
		inst->a->value = ~a->value;
	}
	push(env, inst);
	return inst->a;
}

struct Operand * printLogicalNot(struct Function * env, struct Operand * a) {
	//if(!isIntOrChar(a->var)) {
	//	ERROR();
	//}
	a = getValue(env, a);
	struct Instruction * inst = newInstruction();
	inst->type = ASSIGN_LOGICAL_NOT;
	inst->a = newOperand();
	inst->a->var->type = &INT_TYPE;
	inst->b = a = printCast(env, inst->a->var, a);
	if(a->constant) {
		inst->a->constant = 1;
		inst->a->value = !a->value;
	}
	push(env, inst);
	return inst->a;
}

void printGoto(struct Function * env, int label);

void printIfFalseGoto(struct Function * env, struct Operand * a, int label) {
	//if(isStruct(a->var)) {
	//	ERROR();
	//}
	a = getValue(env, a);
	if(a->constant) {
		if(a->value) {
			return;
		}else {
			printGoto(env, label);
		}
	}else {	
		struct Instruction * inst = newInstruction();
		inst->a = newOperand();
		inst->a->var->type = &INT_TYPE;
		inst->a = printCast(env, inst->a->var, a);
		inst->type = IF_FALSE_GOTO;
		inst->n = label;
		push(env, inst);
	}
}

void printIfGoto(struct Function * env, struct Operand * a, int label) {
	//if(isStruct(a->var)) {
	//	ERROR();
	//}
	a = getValue(env, a);
	if(a->constant) {
		if(!a->value) {
			return;
		}else {
			printGoto(env, label);
		}
	}else {	
		struct Instruction * inst = newInstruction();
		inst->a = newOperand();
		inst->a->var->type = &INT_TYPE;
		inst->a = printCast(env, inst->a->var, a);
		inst->type = IF_GOTO;
		inst->n = label;
		push(env, inst);
	}
}

void printLabel(struct Function * env, int label) {
	struct Instruction * inst = newInstruction();
	inst->type = LABEL;
	inst->n = label;
	push(env, inst);
}

void printGoto(struct Function * env, int label) {
	struct Instruction * inst = newInstruction();
	inst->type = GOTO;
	inst->n = label;
	push(env, inst);
}

void printFillZero(struct Function * env, struct Operand * a) {
	int i = 0, s = calcSize(a->var);
	//printf("printFillZero%d\n", s);
	//return;
	for( ; i < s; i++) {
		struct Instruction * inst = newInstruction();
		inst->type = ASSIGN_ADD;
		inst->a = newOperand();
		inst->a->var->type = &CHAR_TYPE;
		inst->a->type = 1;
		inst->b = a;
		inst->c = constInt(i);
		push(env, inst);
		printAssign(env, inst->a, constChar(0));
	}
}

void printNOP(struct Function * env) {
	struct Instruction * inst = newInstruction();
	inst->type = NOP;
	push(env, inst);
}

struct Operand * printPutchar(struct Function * env, struct Operand * a) {//务必返回void
	struct Instruction * inst = newInstruction();
	a = getValue(env, a);
	inst->type = PUTCHAR;
	inst->a = a;
	push(env, inst);
	struct Operand * ope = newOperand();
	ope->var->type = &VOID_TYPE;
	return ope;
}

struct Operand * printGetchar(struct Function * env) {
	struct Instruction * inst = newInstruction();
	inst->type = GETCHAR;
	inst->a = newOperand();
	inst->a->var->type = &CHAR_TYPE;
	inst->a->type = 2;
	inst->a->constant = 0;
	push(env, inst);
	return inst->a;
}

struct Operand * printMalloc(struct Function * env, struct Operand * a) {
	//printf("printMalloc\n");
	struct Instruction * inst = newInstruction();
	a = getValue(env, a);
	inst->type = MALLOC;
	inst->a = newOperand();
	inst->a->var->type = &VOID_TYPE;
	inst->a->var->level = 1;
	inst->b = a;
	push(env, inst);
	return inst->a;
}

void printDeclInt(struct Function * env, struct Operand * a) {
	struct Instruction * inst = newInstruction();
	inst->a = a;
	inst->type = DECL_INT;
	push(env, inst);
}

void printDeclChar(struct Function * env, struct Operand * a) {
	struct Instruction * inst = newInstruction();
	inst->a = a;
	inst->type = DECL_CHAR;
	push(env, inst);
}

void printDeclPointer(struct Function * env, struct Operand * a) {
	struct Instruction * inst = newInstruction();
	inst->a = a;
	inst->type = DECL_POINTER;
	push(env, inst);
}

void printGetArgu(struct Function * env, struct Operand * a) {
	struct Instruction * inst = newInstruction();
	inst->a = a;
	inst->type = GET_ARGU;
	push(env, inst);
}

void printReturn(struct Function * env, struct Operand * a) {
	struct Instruction * inst = newInstruction();
	a = getValue(env, a);
	inst->a = a;
	inst->type = RETURN;
	push(env, inst);
}

void printVoidReturn(struct Function * env) {
	struct Instruction * inst = newInstruction();
	inst->type = VOID_RETURN;
	push(env, inst);
}

struct Operand * printExit(struct Function * env, struct Operand * a) {
	struct Instruction * inst = newInstruction();
	a = getValue(env, a);
	inst->a = a;
	inst->type = EXIT;
	push(env, inst);
	struct Operand * ope = newOperand();
	ope->var->type = &VOID_TYPE;
	return ope;
}

struct Operand * directLvalue(struct Variable * v) {//将变量转换为直接左值
	struct Operand * res = newOperand();
	res->constant = 0;
	if(v->list == 0 && v->type->type != 2 && v->type->type != 3) {
		res->type = 0;//直接左值.
	}else {
		res->type = 1;//数组和结构体只能是解引用左值.
	}
	res->var = v;
	//printf("!%s\n", v->name);
	//printf("DIRECTLVALUE %d\n", res->var);
	return res;
}

struct Operand * parsePrimaryExpression(struct Function * env) {
	//printf("parsePrimaryExpression %d\n", look.type);
	if(look.type == IDENTIFIER) {
		char * bak = look.name;
		move();
		struct Variable * v = findVariable(bak);
		if(v) {
			return directLvalue(v);
		}else {
			v = newVariable();
			v->name = bak;
			v->type = &FUNC_TYPE;
			return directLvalue(v);
		}
	}else if(look.type == INT_CONSTANT) {
		int bak = look.value;
		//	printf("!!!\n");
		move();
		return constInt(bak);
	}else if(look.type == CHR_CONSTANT) {
		int bak = look.value;
		move();
		return constChar(bak);
	}else if(look.type == STR_CONSTANT) {
		struct Operand * ope = (struct Operand *)malloc(sizeof(struct Operand));
		ope->constant = 0;
		ope->value = 0;
		ope->type = 1;//DIRECT LVALUE, UNDEFIND IF YOU WRITE "123"[0] = a.
		ope->var = (struct Variable *)malloc(sizeof(struct Variable));
		ope->var->next = 0;
		ope->var->level = 0;
		ope->var->type = &CHAR_TYPE;
		ope->var->list = (struct List *)malloc(sizeof(struct List));
		ope->var->list->next = 0;
		ope->var->list->prev = ope->var->list;
		ope->var->list->value = look.value;
		ope->var->list->mul = look.value;
		int i = 0;
		for( ; look.name[i]; i++) {
			//printf("!%d\n", i);
			printAssign(env, printAccess(env, ope, constInt(i)), constChar(look.name[i]));
		}
		move();
		return ope;
	}else if(look.type == 500) {//'('
		//printf("!!!!\n");
		move();
		struct Operand * res = parseExpression(env);
		match(501);//')'
		return res;
	}else {
		ERROR();
	}
}

char _c_putchar__[8] = "putchar";

char _c_malloc__[8] = "malloc";

char _c_getchar__[8] = "getchar";

char _c_printf__[8] = "printf";

char _c___printf____[12] = "__printf__";

char _c_exit__[8] = "exit";

struct Function * findFunc(char * name);

struct Operand * parseActualArgument(struct Function * env, struct Operand * p) {
	struct Operand * res;
	//printf("parseActualArgument %s\n", p->var->name);
	if(!strcmp(p->var->name, _c_putchar__)) {
		res = printPutchar(env, parseAssignmentExpression(env));
		if(look.type != 501) {
			ERROR();
		}
		return res;
	}else if(!strcmp(p->var->name, _c_malloc__)) {
		res = printMalloc(env, parseAssignmentExpression(env));
		if(look.type != 501) {
			ERROR();
		}
		//printf("parseActualArgument %s\n", p->var->name);
		return res;
	}else if(!strcmp(p->var->name, _c_getchar__)) {
		res = printGetchar(env);
		if(look.type != 501) {
			ERROR();
		}
		return res;
	}else if(!strcmp(p->var->name, _c_exit__)) {
		res = printExit(env, parseAssignmentExpression(env));
		if(look.type != 501) {
			ERROR();
		}
		return res;
	}if(!strcmp(p->var->name, _c_printf__)) {
		struct Variable * v = newVariable();
		v->type = &CHAR_TYPE;
		v->level = 1;
		printArgu(env, printCast(env, v, parseAssignmentExpression(env)));
		struct Operand * ope = newOperand();
		ope->type = 1;
		ope->constant = 0;
		ope->var->type = &INT_TYPE;
		ope->var->level = 1;//手动int*
		int cnt = 0;
		//printf("parseActualArgument CALL\n");
		while(look.type != 501) {//')'
			match(503);//','
			//printf("parseActualArgument CALL\n");
			struct Instruction * inst = newInstruction();
			inst->type = ASSIGN_ADDRESS;
			inst->a = printAccess(env, ope, constInt(cnt));
			inst->b = parseAssignmentExpression(env);
			push(env, inst);
			cnt++;
		}
		//printf("parseActualArgument CALL\n");
		printAssign(env, ope, printMalloc(env, constInt(cnt * POINTER_SIZE)));
		printArgu(env, ope);
		return printCall(env, findFunc(_c___printf____), 2);
	}else {
		struct Function * f = findFunc(p->var->name);
		if(!f) {
			ERROR();
		}
		struct Variable * v = f->argu;
		int n = 0;
		//printf("%d\n", v);
		while(v) {
			n++;
			struct Operand * ope;
			if(v->list == 0) {
				printf("!! %s %d\n", f->name, v->level);
				ope = printCast(env, v, parseAssignmentExpression(env));
			}else {
				printf("!!\n");
				ope = parseAssignmentExpression(env);
			}
			printArgu(env, ope);
			//printf("parseActualArgument CALL\n");
			v = v->next;
			if(v) {
				match(503);//','
			}
		}
		//printf("parseActualArgument CALL\n");
		return printCall(env, f, n);
	}
}

struct Variable * parseTypeName() {
	struct Variable * v = (struct Variable *)malloc(sizeof(struct Variable));
	v->level = 0;
	v->name = 0;
	v->next = 0;
	v->list = 0;
	if(look.type == 301) {//void
		v->type = &VOID_TYPE;
		move();
	}else if(look.type == 302) {//char
		move();
		v->type = &CHAR_TYPE;
	}else if(look.type == 303) {//int
		move();
		v->type = &INT_TYPE;
	}else if(look.type == 304 || look.type == 305) {//struct union
		move();
		if(look.type != IDENTIFIER) {
			ERROR();
		}
		v->type = find(look.name);
		if(v->type == 0) {
			ERROR();
		}
		move();
	}
	while(look.type == 509) {//'*'
		v->level++;
		move();
	}
	return v;
}

struct Operand * parsePostfix(struct Function * env, struct Operand * p) {
	struct Operand * res;
	if(look.type == 507) {//'['
		move();
		res = printAccess(env, p, parseExpression(env));
		//printf("[]parsePostfix");
		match(508);//']'
		return parsePostfix(env, res);
	}else if(look.type == 500) {//'('
		move();
		//printf("!!\n");
		res = parseActualArgument(env, p);
		//printf("!!\n");
		match(501);
		return parsePostfix(env, res);
	}else if(look.type == 521) {//'.'
		move();
		if(look.type != IDENTIFIER) {
			ERROR();
		}
		res = printMemberAccess(env, p, look.name);
		move();
		return parsePostfix(env, res);
	}else if(look.type == 542) {//'->'
		move();
		res = printDeref(env, p);
		//printf("parsePostfix-> %s %s\n", p->var->type->name, look.name);
		if(look.type != IDENTIFIER) {
			ERROR();
		}
		printf("res %d %s\n", res, res->var->type->name);
		res = printMemberAccess(env, res, look.name);
		//printf("parsePostfix->\n");
		move();
		printf("res %d\n", res);
		res = parsePostfix(env, res);
		printf("res %d\n", res);
		return res;
	}else if(look.type == 530) {//'++'
		move();
		res = printCopy(env, p);
		struct Operand * tmp = printAssignOp(env, p, constInt(1), 535);
		printAssign(env, p, tmp);
		return parsePostfix(env, res);
	}else if(look.type == 531) {//'--'
		move();
		res = printCopy(env, p);
		struct Operand * tmp = printAssignOp(env, p, constInt(1), 536);
		printAssign(env, p, tmp);
		return parsePostfix(env, res);
	}else {
		//if(examine) {
		//	printf("postfixComplete, %d %d\n", p->constant, p->value);
		//}
		return p;
	}
}

struct Operand * parsePostfixExpression(struct Function * env) {
	struct Operand * res = parsePrimaryExpression(env);
	if(examine) {
//	printf("parsePostfixExpression %d\n", res->constant);
	}
	return parsePostfix(env, res);
}

struct Operand * parseCastExpression(struct Function * env);

struct Operand * parseUnaryExpression(struct Function * env) {
	//if(examine) {
	//	printf("parseUnaryExpression\n");
	//}

	if(look.type == 530) {//'++'
		move();
		struct Operand * tmp = parseUnaryExpression(env), *tmp1;
		if(tmp->type != 0 && tmp->type != 1) {//DIRECT LEFT VALUE OR DEREF LEFT VALUE
			ERROR();
		}
		tmp1 = printAssignOp(env, tmp, constInt(1), 535);
		printAssign(env, tmp, tmp1);
		return tmp;
	}else if(look.type == 531) {//'--'
		move();
		struct Operand * tmp = parseUnaryExpression(env), * tmp1;
		if(tmp->type != 0 && tmp->type != 1) {
			ERROR();
		}
		tmp1 = printAssignOp(env, tmp, constInt(1), 536);
		printAssign(env, tmp, tmp1);
		return tmp;
	}else if(look.type == 512) {//'&'
		move();
		struct Operand * tmp = parseCastExpression(env);
		/*if(tmp->type != 0 && tmp->type != 1) {
		  ERROR();
		  }*/
		return printAddressOf(env, tmp);
	}else if(look.type == 509) {//'*'
		move();
		struct Operand * tmp = parseCastExpression(env);
		return printDeref(env, tmp);//别忘了里面的类型检查
	}else if(look.type == 515) {//'+'
		move();
		struct Operand * tmp = parseCastExpression(env);
		return printPosite(env, tmp);
	}else if(look.type == 516) {//'-'
		move();
		struct Operand * tmp = parseCastExpression(env);
		return printNegate(env, tmp);
	}else if(look.type == 519) {//'~'
		move();
		struct Operand * tmp = parseCastExpression(env);
		return printNot(env, tmp);
	}else if(look.type == 520) {//'!'
		move();
		struct Operand * tmp = parseCastExpression(env);
		return printLogicalNot(env, tmp);
	}else if(look.type == 313) {//sizeof
		move();
		if(look.type == 500) {//'('
			move();
			struct Variable * v = parseTypeName();
			match(501);//')'
			if(v->level) {
				return constInt(POINTER_SIZE);
			}else {
				return constInt(v->type->size);
			}
		}else {
			struct Operand * tmp = parseUnaryExpression(env);
			return constInt(tmp->var->type->size);
		}
	}else {
		//printf("parseUnaryExpression\n" );
		return parsePostfixExpression(env);
	}
}

struct Operand * parseCastExpression(struct Function * env) {
	//printf("parseCastExpression ( %d %s\n", look.type, look.name);
	if(look.type == 500) {//'('
		move();
		//printf("parseCastExpression ( %d\n", look.type);
		if(look.type == 303 || look.type == 304 || look.type == 305 || look.type == 302 || look.type == 301) {
			//printf("parseCastExpression ( \n");
			struct Variable * v = parseTypeName();
			match(501);//')'
			return printCast(env, v, parseCastExpression(env));
		}else {
			struct Operand * res = parseExpression(env);
			match(501);
			return parsePostfix(env, res);
		}
	}else {
		return parseUnaryExpression(env);
	}
}

struct Operand * parseMultiplicativeExpression(struct Function * env) {
	struct Operand * res = parseCastExpression(env);
	for(;;) {
		if(look.type == 509) {//'*'
			move();
			res = printAssignOp(env, res, parseCastExpression(env), 532);
		}else if(look.type == 517) {//'/'
			move();
			res = printAssignOp(env, res, parseCastExpression(env), 533);
		}else if(look.type == 518) {//'%'
			move();
			res = printAssignOp(env, res, parseCastExpression(env), 534);
		}else {
			return res;
		}
	}
}

struct Operand * parseAdditiveExpression(struct Function * env) {
	struct Operand * res = parseMultiplicativeExpression(env);
	for(;;) {
		if(look.type == 515) {//'+'
			move();
			res = printAssignOp(env, res, parseMultiplicativeExpression(env), 535);
		}else if(look.type == 516) {//'-'
			move();
			res = printAssignOp(env, res, parseMultiplicativeExpression(env), 536);
		}else {
			return res;
		}
	}
}

struct Operand * parseShiftExpression(struct Function * env) {
	struct Operand * res = parseAdditiveExpression(env);
	for(;;) {
		if(look.type == 528) {//'<<'
			move();
			res = printAssignOp(env, res, parseAdditiveExpression(env), 537);
		}else if(look.type == 529) {//'>>'
			move();
			res = printAssignOp(env, res, parseAdditiveExpression(env), 538);
		}else {
			return res;
		}
	}
}

struct Operand * parseRelationalExpression(struct Function * env) {
	struct Operand * res = parseShiftExpression(env);
	for(;;) {
		if(look.type == 513) {//'<'
			move();
			res = printAssignOp(env, res, parseShiftExpression(env), 513);
		}else if(look.type == 514) {//'>'
			move();
			res = printAssignOp(env, res, parseShiftExpression(env), 514);
		}else if(look.type == 526) {//'<='
			move();
			res = printAssignOp(env, res, parseShiftExpression(env), 526);
		}else if(look.type == 527) {//'>='
			move();
			res = printAssignOp(env, res, parseShiftExpression(env), 527);
		}else {
			return res;
		}
	}
}

struct Operand * parseEqualityExpression(struct Function * env) {
	struct Operand * res = parseRelationalExpression(env);
	for(;;) {
		if(look.type == 524) {//'=='
			move();
			res = printAssignOp(env, res, parseRelationalExpression(env), 524);
		}else if(look.type == 525) {//'!='
			move();
			res = printAssignOp(env, res, parseRelationalExpression(env), 525);
		}else {
			return res;
		}
	}
}

struct Operand * parseAndExpression(struct Function * env) {
	struct Operand * res = parseEqualityExpression(env);
	for(;;) {
		if(look.type == 512) {//'&'
			move();
			res = printAssignOp(env, res, parseEqualityExpression(env), 539);
		}else {
			return res;
		}
	}
}

struct Operand * parseExclusiveOrExpression(struct Function * env) {
	struct Operand * res = parseAndExpression(env);
	for(;;) {
		if(look.type == 511) {//'^'
			move();
			res = printAssignOp(env, res, parseAndExpression(env), 540);
		}else {
			return res;
		}
	}
}

struct Operand * parseInclusiveOrExpression(struct Function * env) {
	struct Operand * res = parseExclusiveOrExpression(env);
	for(;;) {
		if(look.type == 510) {//'|'
			move();
			res = printAssignOp(env, res, parseExclusiveOrExpression(env), 541);
		}else {
			return res;
		}
	}
}

struct Operand * parseLogicalAndExpression(struct Function * env) {
	struct Operand * res = parseInclusiveOrExpression(env);
	int x = -1;
	if(look.type == 523) {
		x = newLabel();
	}else {
		//printf("parseLogicalAndExpression%d\n", res->constant);
		return res;
	}
	if(res->constant && res->value == 0) {
		return constInt(0);
	}
	for(;;) {
		if(look.type == 523) {//'&&'
			//printf("parseLogicalAndExpression%d\n", res->constant);
			move();
			printIfFalseGoto(env, res, x);
			//printf("parseLogicalAndExpress!!IFFALion%d\n", res->constant);
			struct Operand * ope = parseInclusiveOrExpression(env);
			//printf("parseLogicalAndExpress!!ion%d\n", res->constant);
			if(ope->constant && ope->value == 0) {
				return constInt(0);
			}
			res = printAssignOp(env, res, ope, 523);
		}else {
			break;
		}
	}
	struct Operand * rtn = newOperand();
	rtn->type = 0;
	rtn->var->type = &INT_TYPE;
	printAssign(env, rtn, res);
	int y = newLabel();
	printGoto(env, y);
	printLabel(env, x);
	printAssign(env, rtn, constInt(0));
	printLabel(env, y);
	return printCopy(env, rtn);
}


struct Operand * parseLogicalOrExpression(struct Function * env) {
	struct Operand * res = parseLogicalAndExpression(env);
	int x = -1;
	if(look.type == 522) {
		x = newLabel();
	}else {
		return res;
	}
	if(res->constant && res->value != 0) {
		return constInt(1);
	}	
	for(;;) {
		if(look.type == 522) {//'||'
			move();
			printIfGoto(env, res, x);
			struct Operand * ope = parseLogicalAndExpression(env);
			if(ope->constant && ope->value != 0) {
				return constInt(1);
			}
			res = printAssignOp(env, res, ope, 522);
		}else {
			break;
		}
	}

	struct Operand * rtn = newOperand();
	rtn->type = 0;
	rtn->var->type = &INT_TYPE;
	printAssign(env, rtn, res);
	int y = newLabel();
	printGoto(env, y);
	printLabel(env, x);
	printAssign(env, rtn, constInt(1));
	printLabel(env, y);
	return printCopy(env, rtn);
}

struct Operand * parseConstantExpression(struct Function * env) {
	return parseLogicalOrExpression(env);
}

struct Operand * parseAssignmentExpression(struct Function * env) {
	printf("parseAssignmentExpression %s\n", look.name);
	struct Operand * res = parseLogicalOrExpression(env);
	if(isAssignmentOperator(look.type)) {
		int assignType = look.type;
		move();
		if(res->type != 0 && res->type != 1) {//DIRECT LVALUE or DEREF LVALUE.
			ERROR();
		}//
		if(assignType == 504) {
			//printf("parseAssignmentExpression\n");z
			struct Operand * tmp = parseAssignmentExpression(env);
			printAssign(env, res, tmp);
			
		}else {
			struct Operand * tmp = printAssignOp(env, res, parseAssignmentExpression(env), assignType);
			printAssign(env, res, tmp);
		}
		return res;
	}else {
		printf("parseAssignmentExpression %d\n", res);
		return res;
	}
}

struct Operand * parseExpression(struct Function * env) {//常数表达式优化.
	struct Operand * res;
	for(;;) {
		res = parseAssignmentExpression(env);
		if(look.type == 503) {//','
			move();
			continue;
		}else {
			break;
		}
	}
	return res;
}


struct List * parseArray() {//分析数组
	struct List * v = 0;
	while(look.type == 507) {//'['
		move();
		struct Operand * ope = parseConstantExpression(calculator);//分析常量表达式
		//printf("parseArray %d %d\n", ope->constant, ope->value);
		if(ope->constant == 0) {
			ERROR();
		}
		//printf("parseArray\n");
		struct List * a = (struct List *)malloc(sizeof(struct List));
		a->value = ope->value;
		a->next = 0;
		if(v == 0) {
			v = a;
			a->prev = a;
		}else {
			a->prev = v->prev;
			v->prev = a;
			a->prev->next = a;
		}
		//printf("parseArray %d\n", look.type);
		match(508);
	}
	struct List * a = v->prev;
	while(1) {
		if(a->next == 0) {
			a->mul = a->value;
		}else {
			a->mul = a->next->mul * a->value;
		}
		if(a == v) {
			break;
		}
		a = a->prev;
	}
	return v;
}

struct Variable * parsePlainDeclarator(int enableAnony) {//分析指针阶数和变量名!
	struct Variable * v = newVariable();
	while(look.type == 509) {//'*'
		v->level++;
		move();
	}
	//printf("parsePlainDeclarator %d %c%c%c%c%c%c%c%c%c%c\n", look.type, program[0],  program[1],  program[2],  program[3],  program[4],  program[5],  program[6],  program[7],  program[8],  program[9]);
	if(look.type == IDENTIFIER) {
		v->name = look.name;
		move();
	}else {
		if(!enableAnony) {
			ERROR();
		}
		//支持匿名变量, 仅限函数的arguments
	}
	return v;
}

struct Type * find(char * name) {//查找union或者struct名字, 没有到上层符号表中找.
	struct SymbolList * p = top;
	for(; p;) {
		struct Type * itr = p->QaQ;
		while(itr) {
			if(!strcmp(itr->name, name)) {
				return itr;
			}
			itr = itr->next;
		}
		p = p->prev;
	}
	return 0;
}

struct Variable * findMem(struct Variable * vars, char * name) {//找成员变量
	struct Variable * p = vars;
	while(p) {
		if(!strcmp(p->name, name)) {
			return p;
		}
		p = p->next;
	}
	return 0;
}

int newTypeDefined;

struct Type * parseTypeSpecifier() {//分析类型
	//printf("parseTypeSpecifier\n");
	if(look.type == 304 || look.type == 305) {//'struct' 'union'类型
		int s_or_u = look.type;
		move();
		struct Token structName = look;
		move();
		if(structName.type != IDENTIFIER) {
			ERROR();
		}
		//printf("parseTypeSpecifier %s\n", structName.name);
		if(look.type == 505) {//'{'说明要先定义
			struct Type * a;
			a = find(structName.name);
			newTypeDefined = 1;
			if(a == 0) {
				a = (struct Type *)malloc(sizeof(struct Type));
				a->next = top->QaQ;
				top->QaQ = a;
			}else {
				if(a->size != -1 || a->type != s_or_u - 302) {
					ERROR();
				}
			}
			a->size = 0;
			a->vars = 0;
			a->type = s_or_u - 302;
			a->name = structName.name;
			move();
			struct SymbolList * newTop = (struct SymbolList *)malloc(sizeof(struct SymbolList));
			newTop->prev = top;
			top = newTop;
			top->QaQ = 0;
			top->vars = 0;
			for(; look.type != 506;) {//'}'
				struct Type * t = parseTypeSpecifier();//分析成员的类型
				for( ; look.type != 502; ) {//';'
					struct Variable * v = parsePlainDeclarator(0);//成员的名字和数组阶数
					if(findMem(a->vars, v->name)) {//成员不能重名
						ERROR();
					}
					if(look.type == 507) {//'['说明是数组成员
						v->list = parseArray();
					
					}
					v->type = t;
					v->next = a->vars;
					a->vars = v;
					int s = calcSize(v);
					if(s_or_u == 304) {//struct, 要全部分配内存
						a->size += s;
					}else {//union, 只需要最大的内存
						a->size = max(a->size, s);
					}
					if(look.type == 503) {//','
						move();
					}
				}
				move();
			}
			top = top->prev;
			move();
			return a;
		}else {
			struct Type * t = find(structName.name);//不给出定义的struct
			if(!t) {
				struct Type * a = (struct Type *)malloc(sizeof(struct Type));//初始化一个类
				a->next = top->QaQ;
				top->QaQ = a;
				a->size = -1;
				a->vars = 0;
				a->type = s_or_u - 302;
				a->name = structName.name;
				return a;
			}else {
				return t;
			}
		}
	}else {
		if(look.type == 302) {//char
			move();
			return &CHAR_TYPE;
		}else if(look.type == 303) {//int
			move();
			//printf("!!\n");
			return &INT_TYPE;
		}else if(look.type == 301) {//void
			move();
			return &VOID_TYPE;
		}else {
			ERROR();
		}
	}

}

struct Variable * findVariable(char * name) {//在变量表中找名字, 找不到到上层符号表中找!
	struct SymbolList * s = top;
	//printf("findVariable %s\n", name);
	while(s) {
		struct Variable * p = s->vars;
		//		printf("%s\n", p->name);
		while(p) {
			//printf("%s\n", p->name);
			if(!strcmp(p->name, name)) {
				//printf("findVariable %s\n", name);
				return p;
			}
			p = p->next;
		}
		s = s->prev;
	}
	//printf("findVariable %s\n", name);
	return 0;
}

struct Function * findFunc(char * name) {//在函数表中找名字
	struct Function * p = funcs;
	while(p) {
		if(!strcmp(p->name, name)) {
			return p;
		}
		p = p->next;
	}
	return 0;
}

int compFunc(struct Function * p, struct Function * q) {//比较函数定义
	if(!compType(p->rtn, q->rtn)) {//比较返回值类型
		return 0;
	}
	struct Variable * v = p->argu, * u = q->argu;
	for(;;) {//比较参数个数和类型
		if(!v && !u) {
			return 1;
		}
		if(!v || !u) {
			return 0;
		}
		if(!compType(v, u)) {
			return 0;
		}
		v = v->next;
		u = u->next;
	}
}

void parseInitialization(struct Function * env, struct Variable * v) {//分析初始化
	//printf("parseInitialization\n");
	if(look.type == 505) {//'{'说明是初始化列表
		//printf("parseInitialization %d\n", v->list);
		//exit(0);
		struct List * p = v->list;
		for(; ; ) {//清空list里面的临时变量, 一会用到
			p->tmp = 0;
			if(p->next == 0) {
				p->next = &TMP;
				TMP.prev = p;
				TMP.tmp = 0;
				break;
			}else {
				p = p->next;
			}
		}
		int flag = 0;
		p = v->list;
		int index = 0;
		//	printf("parseInitialization\n");
		for(;;) {
			if(look.type == 505) {//'{'说明数组又深了一层
				//printf("parseInitialization{\n");
				if(p->next == 0) {
					ERROR();
				}else {
					p = p->next;
				}
				move();
			}else if(look.type == 506) {//'}'说明数组又浅了一层
				//printf("parseInitialization}\n");
				flag = 1;
				if(p == v->list) {
					ERROR();
				}else {
					p->tmp = 0;
					p = p->prev;
					index -= index % p->mul;
				}
				move();
				if(p == v->list) {
					break;
				}
			}else if(look.type == 503) {//',', 说明下标+1了, 指针index对应移动
				if(!flag) {//{,}这样不行, {0,}则可以
					ERROR();
				}
				flag = 0;
				//printf("parseInitialization,\n");
				p->tmp ++;
				if(p->tmp == p->prev->value) {
					ERROR();
				}
				index += calcElementSize(v) * p->mul;
				move();
			}else {//是个赋值表达式, 赋值之.
				//以直接左值v作为基准, 地址+index, 赋值.
				//下面本来是字符数组的特殊初始化, 还不知道怎么弄.
				if(look.type == STR_CONSTANT) {
					int special = 0;
					if(p != &TMP && p && p->next ==&TMP) {
						special = 1;
						p = &TMP;
						p->tmp = 0;
					}
					if(p == &TMP && p->tmp == 0) {
						int i = 0;
						while(i == 0 || look.name[i - 1]) {
							flag = 1;
							if(i == p->prev->value) {
								ERROR();
							}
							struct Instruction * inst = newInstruction();
							inst->type = ASSIGN_ADD;
							inst->a = newOperand();
							inst->a->type = 1;
							*inst->a->var = *v;
							inst->a->var->list = 0;
							inst->b = directLvalue(v);
							inst->c = constInt(index + i);
							push(env, inst);
							printAssign(env, inst->a, constChar(look.name[i]));
							i++;
						}
						move();
						if(special == 1) {
							p->tmp = 0;
							p = p->prev;
						}else {
							if(look.type != 506) {//'}'
								ERROR();
							}
						}
					}else {
						ERROR();
					}
				}else {
					if(p != &TMP) {
						ERROR();
					}else {
						flag = 1;
						//printf("%d\n", look.type);
						struct Instruction * inst = newInstruction();
						inst->type = ASSIGN_ADD;
						inst->a = newOperand();
						inst->a->type = 1;
						*inst->a->var = *v;
						inst->a->var->list = 0;
						inst->b = directLvalue(v);
						inst->c = constInt(index);
						push(env, inst);
						printAssign(env, inst->a, parseAssignmentExpression(env));
					}
				}
			}
		}
		if(p != v->list) {
			ERROR();
		}else {
			while(p->next != &TMP) {
				p = p->next;
			}
			p->next = 0;
		}
	}else if(look.type == STR_CONSTANT) {
		//printf("parseInitialization\n");
		if(calcDepth(v->list) != 1) {
			ERROR();
		}
		int i = 0;
		while(i == 0 || look.name[i - 1]) {
			//printf("parseInitialization %d\n", i);
			if(i == v->list->value) {
				ERROR();
			}
			printAssign(env, printAccess(env, directLvalue(v), constInt(i)), constChar(look.name[i]));
			i++;
		}
		printAssign(env, printAccess(env, directLvalue(v), constInt(i)), constChar(0));
		move();
	}else {//直接初始化.
		//printf("parseInitialization\n");
		printAssign(env, directLvalue(v), parseAssignmentExpression(env));
	}
}

void parseDeclaractionOrFunctionDefinition(struct Function * env);

void parseStatement(int b, int a, struct Function * env) {//分析语句.
	//b: before, a:after
	//if(examine) {
	//	printf("parseStatement\n");
	//}
	if(look.type == 505) {//'{'复合语句
		move();
		struct SymbolList * newTop = (struct SymbolList*)malloc(sizeof(struct SymbolList));//新建参数表, 上级为原来的参数表.
		newTop->prev = top;
		top = newTop;
		top->QaQ = 0;
		top->vars = 0;
		while(look.type != 506) {//'}'
			if(look.type >= 301 && look.type <= 305) {
				parseDeclaractionOrFunctionDefinition(env);
			}else {
				parseStatement(b, a, env);
			}
		}
		move();
		top = top->prev;
	}else if(look.type == 306) { //if语句
		//if(examine) {
		//	printf("parseStatement If\n");
		//}
		move();
		match(500);//'('
		int after = newLabel();//标记else之前的位置

		printIfFalseGoto(env, parseExpression(env), after);//不满足就跳!

		//if(examine) {
		//	printf("parseStatement If\n");
		//}
		

		match(501);//')'

		//if(examine) {
		//	printf("parseStatement If\n");
		//}
		parseStatement(b, a, env);//满足时执行的语句
		//if(examine) {
		//	printf("parseStatementElse\n");
		//}
		if(look.type == 307) {//else语句
			move();
			int last = newLabel();//else结束的位置
			printGoto(env, last);//满足时跳过else
			printLabel(env, after);//标记else之前的位置
			parseStatement(b, a, env);//不满足时执行的语句
			printLabel(env, last);//标记else结束的位置
		}else {
			printLabel(env, after);//没有else, 直接标记结束位置.
		}
	}else if(look.type == 309) {//for
		move();
		match(500);//'('
		int body = newLabel(), begin = newLabel(), after = newLabel();//循环k控制位置, 循环变量变更位置, 循环结束位置
		if(look.type == 502) {
			//支持不初始化!
		}else {
			parseExpression(env);//分析循环初始化表达式
		}
		match(502);//';'
		printLabel(env, body);//标记循环控制位置
		if(look.type == 502) {
			printIfFalseGoto(env, constInt(1), after);//支持死循环
		}else {
			printIfFalseGoto(env, parseExpression(env), after);//分析循环控制表达式, 不满足就结束
		}
		match(502);//';'
		struct Function * tmp = (struct Function *)malloc(sizeof(struct Function));//复制函数环境
		*tmp = *env;
		tmp->insts = 0;
		if(look.type == 501) {//')'
			//支持死循环
		}else {
			parseExpression(tmp);//分析循环变量变更表达式
		}
		match(501);//')'
		//printf("parseStatement FOR\n");
		parseStatement(begin, after, env);//分析循环体
		printLabel(env, begin);//循环变量变更开始
		if(tmp->insts) {
			struct Instruction * p = tmp->insts;//复制循环变量变更代码
			while(p->next) {
				p = p->next;
			}
			p->next = env->insts;
			env->insts = tmp->insts;
		}
		printGoto(env, body);//跳到循环控制位置
		printLabel(env, after);//标记循环结束
	}else if(look.type == 308) {//while
		move();
		match(500);//'('
		int begin = newLabel(), after = newLabel();//循环控制位置, 循环结束位置
		printLabel(env, begin);//标记循环控制开始位置
		if(look.type == 501) {//')'
			ERROR();//支持死循环才怪!
			printIfFalseGoto(env, constInt(1), after);//支持死循环才怪!
		}else {
			printIfFalseGoto(env, parseExpression(env), after);//不满足就结束
		}
		match(501);//')'
		parseStatement(begin, after, env);//分析循环体
		printGoto(env, begin);
		printLabel(env, after);//标记结束位置
	}else if(look.type == 311) {//break
		if(a == -1) {
			ERROR();
		}
		move();
		printGoto(env, a);//跳到after处, 即for和while的结束位置
		match(502);//';'
	}else if(look.type == 310) {//continue
		if(b == -1) {
			ERROR();
		}
		move();
		printGoto(env, b);//跳到begin处, 即for的循环变量变更位置, while的循环控制位置.
		match(502);//';'
	}else if(look.type == 312) {//return!
		move();
		//if(examine) {
		//	printf("parseReturnStatement\n");
		//}
		if(env->rtn->type != &VOID_TYPE) {
			printReturn(env, parseExpression(env));
		}else {
			printVoidReturn(env); 
		}
		//printf("!!\n");
		match(502);
	}else {//表达式语句.
		parseExpression(env);
		match(502);//';'
	}
}

void parseFunctionBody(struct Function * env) {
	if(examine) {
		printf("parseFunctionBody %s\n", env->name);
	}
	top = (struct SymbolList*)malloc(sizeof(struct SymbolList));//新建函数表
	top->QaQ = 0;
	top->prev = base;//以主过程函数表为上级
	top->vars = 0;
	struct Variable * p = env->argu;//复制参数为初始变量表
	while(p) {
		struct Variable * q = (struct Variable *)malloc(sizeof(struct Variable));
		*q = *p;
		printf("%s %s\n", q->type->name, q->name);
		printGetArgu(env, directLvalue(q));//
		q->next = top->vars;
		top->vars = q;
		p = p->next;
	}
	move();
	while(look.type != 506) {//'}'
		if(look.type >= 301 && look.type <= 305) {//是void char int struct union中的一个
			parseDeclaractionOrFunctionDefinition(env);
		}else {
			parseStatement(-1, -1, env);//否则.
		}
	}
	//printf("!!!%d\n", look.type);
	move();
	top = top->prev;
}

struct Function * newFunction() {
	struct Function * f = (struct Function *)malloc(sizeof(struct Function));
	f->next = 0;
	f->argu = 0;
	f->rtn = 0;
	f->insts = 0;
	f->name = 0;
	return f;
}

struct Function * parseArguments() {
	move();//'('
	struct Function * f = newFunction();
	for(; look.type != 501;) { //')'
		newTypeDefined = 0;
		struct Type * p = parseTypeSpecifier();
		if(newTypeDefined) {//不能在参数里定义类型.
			ERROR();
		}
		struct Variable * v = parsePlainDeclarator(1);//允许匿名
		if(look.type == 507) {//'['
			v->list = parseArray();
		}
		v->type = p;
		v->next = f->argu;
		f->argu = v;//反向参数表!
		if(look.type == 503) {//','
			move();
		}
	}
	move();//')'
	struct Variable * tmp = f->argu, * tmp1;//把参数表正过来
	f->argu = 0;
	while(tmp) {
		tmp1 = tmp->next;
		tmp->next = f->argu;
		f->argu = tmp;
		tmp = tmp1;
	}
	return f;
}

struct Variable * findTopVariable(char * name) {
	struct Variable * p = top->vars;
	while(p) {
		if(!strcmp(p->name, name)) {
			return p;
		}
		p = p->next;
	}
	return 0;
}

void parseDeclaractionOrFunctionDefinition(struct Function * env) {
	//if(examine) {
	//	printf("parseDeclaractionOrFunctionDefinition\n");
	//}
	int i = 0;
	
	newTypeDefined = 0;//看看有没有进行struct和union的定义
	struct Type * t = parseTypeSpecifier();//分析类型
	//printf("!!\n");
	if(t->size == -1) {
		match(502);//';'
	//	printf("!!\n");
	
		return;
	}
	for(;look.type != 502;) {//';'
		i++;
	//	printf("parseDeclaractionOrFunctionDefinition parsePlainDeclarator\n");
		struct Variable * v = parsePlainDeclarator(0);//分析了指针的层数, 不允许匿名
		v->type = t;
	//	printf("parseDeclaractionOrFunctionDefinition %s %d\n", v->name, look.type);
		if(look.type == 500) {//'('说明是函数
	//		printf("parseDeclaractionOrFunctionDefinition %s\n", v->name);
	//		if(examine) {
	//			printf("def function %s\n", v->name);
	//		}
			if(findVariable(v->name) || newTypeDefined) {//函数不能和变量重名, 不能在返回值里定义struct.
				ERROR();
			}
			struct Function * f = parseArguments();//分析函数的参数
			f->name = v->name;//函数的名字
			f->rtn = v;//函数的返回值类型
			struct Function * p = findFunc(f->name);//寻找函数表, 有没有一样的函数
			if(p && !compFunc(p, f)) {//不能名字一样定义却不同
				ERROR();
			}
			if(!p) {//没有重名的函数
				f->next = funcs;//加入函数表
				funcs = f;
			}else {
				p->argu = f->argu;
				f = p;
			}
			//printf("%d %s %d\n", f, f->name, f->insts);
			if(look.type == 505) {//'{'说明是函数定义
				if(f->insts || i != 1 || env != chief) {//不能重复定义函数, 函数定义必须独占type-specifier, 不能在函数里定义函数.
					ERROR();
				}
				printNOP(f);
				//printf("1\n");
				//printf("%d %s %d %d\n", f, f->name, f->insts, f->insts->type);
				parseFunctionBody(f);//分析函数过程.
				//printf("%s %d %d\n", f->name, f->insts, f->insts->type);
				return;//函数定义必须独占type-specifier
			}else {
				//重复声明函数, 什么也不做.
			}
		}else {//不是函数
			if(findTopVariable(v->name) || findFunc(v->name)) {
				ERROR();
			}
			v->next = top->vars;
			top->vars = v;
			if(look.type == 507) {//'['说明是数组类型
			//	printf("parseDeclaractorOrFunctionDefinition ARRAY");
				v->list = parseArray();//分析数组的维度
			}
			if(v->type == &VOID_TYPE && v->level == 0) {//不能定义void类型的变量
				ERROR();
			}
			if(v->list) {
				struct Instruction * inst = newInstruction();
				inst->type = ASSIGN_ADDRESS;
				inst->a = directLvalue(v);
				//printf("%d\n", inst->a->var);
				inst->b = printMalloc(env, constInt(calcSize(v)));
				push(env, inst);
			}else if(v->level) {
				printDeclPointer(env, directLvalue(v));
			}else if(v->type->type == 2 || v->type->type == 3) {
				struct Instruction * inst = newInstruction();
				inst->type = ASSIGN_ADDRESS;
				inst->a = directLvalue(v);
				//printf("parseDeclaractorOrFunctionDefinition ARRAY MALLOC\n");
				inst->b = printMalloc(env, constInt(calcSize(v)));
				//printf("parseDeclaractorOrFunctionDefinition ARRAY MALLOC\n");
				push(env, inst);
			}else if(v->type == &CHAR_TYPE) {
				printDeclChar(env, directLvalue(v));
			}else if(v->type == &INT_TYPE) {
				printDeclInt(env, directLvalue(v));
			}
			if(env == chief) {//说明是全局变量
				printFillZero(env, directLvalue(v));//将v所占全部内存清0
			}
			if(look.type == 504) {//'='说明有初始化
				move();
				parseInitialization(env, v);//分析变量v的初始化
			}
			//printf("parseDeclaractorOrFunctionDefinition ARRAY MALLOC\n");
		}
		if(look.type == 503) {//','说明还有后续声明
			move();
			continue;
		}
	}
	move();
}	

char CHIEF[6] = "chief";

void parseProgram() {
	clear();//清空*top符号表

	base = top;//base:主程序符号表

	funcs = 0;

	chief = newFunction();//主过程

	chief->name = CHIEF;

	calculator = newFunction();//编译时的计算器

	printNOP(chief);//新建一个空操作.

	TMP.mul = 1;
	TMP.next = 0;

	int begin = newLabel(), end = newLabel();//主程序的开始和结束标签

	printLabel(chief, begin);

	move();

	while(look.type != NO_TOKEN) {
		parseDeclaractionOrFunctionDefinition(chief);
	}

	printLabel(chief, end);

	//chief->insts即为主程序的指令序列(倒序)
}

int stopAtLexer = 0, stopAt3AddrCode = 1;

void reverse(struct Function * f) {
	struct Instruction * tmp = f->insts, * tmp1;
	f->insts = 0;
	while(tmp) {
		tmp1 = tmp->next;
		tmp->next = f->insts;
		f->insts = tmp;
		tmp = tmp1;
	}
}

int main() {
	examine = 1;
	initBasicTypeName();//char & int
	program = (char*)malloc(sizeof(char) * 10);
	int length = 0;
	int capacity = 10;
	char c;
	int i = 0;
	for(; __stdio__printf__[i]; i++) {//标准库printf
		push_back(&program, &length, &capacity, __stdio__printf__[i]);
	}
	while(-1 != (c = getchar())) {
		push_back(&program, &length, &capacity, c);
	}
	push_back(&program, &length, &capacity, 0);
	printf("%s", program);
	beginOfLine = 1;
	if(stopAtLexer) {
		printTokens();
	}else {
		parseProgram();
		if(stopAt3AddrCode) {
			reverse(chief);
			struct Function * f = funcs;
			while(f) {
				reverse(f);
				f = f->next;
			}
			struct Instruction * p = chief->insts;
			printf("chief\n");
			while(p) {
				//printf("!%d\n", p->type);
				printIntermediateCode(p);
				p = p->next;
			}
			f = funcs;
			while(f) {
				p = f->insts;
				printf("\n%d %s\n", f, f->name);
				while(p) {
					printIntermediateCode(p);
					p = p->next;
				}
				f = f->next;
			}
		}else {
			//???
		}
	}
	//fclose(stdin);
	return 0;
}
