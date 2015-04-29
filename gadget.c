 #include <stdio.h>
# include<stdlib.h>

int POINTER_SIZE = 4;

int examine = 1;

char * newEmptyString() {
	char * res = (char *)malloc(sizeof(char));
	res[0] = 0;
	return res;
}

char __stdio__printf__[11111] = 
"void __printf__(char * str, int * argu) { int index = 0; while(*str) { if(*str == '%') { str[0]; str++; if(str[0] == '%') { putchar('%'); }else if(str[0] == 'c') { putchar((char)argu[index++]); }else if(str[0] == 's') { char * s = (char *)argu[index++]; while(*s) { putchar(*s); s++; } }else if(str[0] == 'd') { putint(argu[index++]); }else if(str[0] == '.') { int x = str[1] - '0'; int cnt = 0, tmp, flag = 0; if(argu[index] < 0) { argu[index] = -argu[index]; flag = 1; } tmp = argu[index]; if(flag) { putchar('-'); } cnt = tmp == 0; while(tmp) {cnt++; tmp /= 10;} while(x > cnt) {putchar('0'); x--;} putint(argu[index++]); str += 2; } }else { putchar(*str); } str++; } }\nvoid __memset__(char * a, int len) {while(len) {*a = '\\0'; a++; len--; } } \nvoid __memcpy__(char * a, char * b, int len) {while(len) {*a = *b; a++; b++; len--;} }\n";
//
//ERROR
//

char _c___memcpy__[20] = "__memcpy__";

char * bp, * program;

void ERROR(int label) {
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
	program = program - 100;
	program[210] = '\0';
	printf("%d %d\a\a\a%s", label, program - bp, program);
	exit(1);
}

void printERROR(char * s) {
	printf(s);
	exit(0);
}

int strcmp(char * a, char * b) {
	int i = 0;
	for( ; a[i] != 0 && b[i] != 0; i++) {
		if(a[i] != b[i]) {
			return 1;
		}
	}
	return a[i] != b[i];
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
		*a = tmp;
	}
	(*a)[(*length)++] = c;
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
				int x = 0;
				while(isHex(program[1])) {
					x = x * 16 + hex(program[1]);
					program++;
				}
				res = x;
			}else {
				ERROR(1);
			}
		}else if(isOct(*program)) {
			int x = oct(program[0]);
			while(isOct(program[1])) {
				x = x * 8 + oct(program[1]);
				program++;
			}
			res = x;
		}else {
			res = *program;
		}
		program++;
		return res;
	}else {
		if(isNewLine(*program)) {
			ERROR(3);
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
	//printf("[%c]\n", *program);
	struct Token res;
	res.name = newEmptyString();
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
			if(!beginOfLine) {
				ERROR(90);
			}
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
		if(program[0] == '0' && (program[1] == 'x' || program[1] == 'X')) {
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
				//printf("!!!\n");
				//printf("!!%c%c%c%c\n", program[0], program[1], program[2], program[3]);
				ERROR(4);
			}else if(isDigit(*program)) {
				x = x * base + *program - '0';
			}else if(base == 10) {
				ERROR(5);
			}else if(isHex(*program)) {
				x = x * base + hex(*program);
			}else {
				ERROR(6);
			}
			program++;
		}
		if(isLetter(*program)) {
			ERROR(7);//etc. 123aa
		}
		res.type = INT_CONSTANT;
		res.value = x;
		return res;
	}else if(*program == '\'') {
		program++;
		if(*program == '\'') {
			ERROR(8);
		}
		int x = nextChar();
//		res.value = nextChar();
		while(*program != '\'') {//字符常量长度溢出, 直接忽略.
			if(isNewLine(*program)) {
				ERROR(9);
			}else {
				x = x * 256 + nextChar();
			}
			program++;
		}
		res.value = x;
		program++;
		res.type = CHR_CONSTANT;
		return res;
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
				ERROR(10);
			}else {
				cnt++;
				int x = nextChar();
				if(x == 0) {
					ERROR(11);
				}
			}
		}
	}else if(isOp()) {
		res.type = op(res);
		return res;
	}else {
		ERROR(12);
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
	int mul;
	struct List * next, * prev;
} TMP;

struct List * newList() {
	struct List * res = (struct List *)malloc(sizeof(struct List));
	res->value = 0;
	res->mul = 0;
	res->prev = 0;
	res->next = 0;
	return res;
}

struct Type;

int totIndex = 0;

struct Variable {
	char * name;
	int level;//count of '*'
	struct Type * type;//basic type
	struct List * list;//dimensions of array
	struct Variable * next;
	int index;
} * INT_VARIABLE, * VOID_VARIABLE;

struct SymbolList;

struct Function {
	char * name;
	struct Variable * rtn;//return type
	struct Variable * argu;//arguments type
	struct Instruction * insts;
	struct Function * next;
	struct SymbolList * symbolList;
	struct List * occupy;
}* chief, * bucket;

struct Function * newFunction() {
	struct Function * f = (struct Function *)malloc(sizeof(struct Function));
	f->next = 0;
	f->argu = 0;
	f->rtn = 0;
	f->insts = 0;
	f->name = newEmptyString();
	f->symbolList = 0;
	f->occupy = 0;
	return f;
}

struct Type {
	char * name;
	int type;//0 int, 1 char, 2 struct, 3 union, 4 void, 5 function
	struct Type * next;//used for SymbolList
	struct Variable * vars;//members
	int size;
	struct List * posi;
} * CHAR_TYPE, * INT_TYPE, * VOID_TYPE, * FUNC_TYPE;

struct Type * newType() {
	struct Type * res = (struct Type *)malloc(sizeof(struct Type));
	res->name = newEmptyString();
	res->type = 0;
	res->next = 0;
	res->vars = 0;
	res->size = 0;
	return res;
}

struct Variable * newVariable() {
	struct Variable * res = (struct Variable *)malloc(sizeof(struct Variable));
	res->name = newEmptyString();
	res->level = 0;
	res->type = INT_TYPE;
	res->list = 0;
	res->next = 0;
	res->index = ++totIndex;
	return res;
}

void copyType(struct Variable * a, struct Variable * b) {
	a->level = b->level;
	a->type = b->type;
	a->list = b->list;
}

void initModVariables() {
	INT_VARIABLE = newVariable();
	INT_VARIABLE->type = INT_TYPE;
	VOID_VARIABLE = newVariable();
	VOID_VARIABLE->type = VOID_TYPE;
}

void initBasicTypeName() {
	CHAR_TYPE = newType();
	CHAR_TYPE->type = 1;
	CHAR_TYPE->size = 1;
	INT_TYPE = newType();
	INT_TYPE->size = 4;
	VOID_TYPE = newType();
	VOID_TYPE->type = 4;
	VOID_TYPE->size = 1;//!!!
	FUNC_TYPE = newType();
	FUNC_TYPE->type = 5;
}

struct Token look, look1;

void move() {

	look = look1;
	look1 = nextToken();
	while(look.type == STR_CONSTANT && look1.type == STR_CONSTANT) {
		int cnt = 0;
		int i = 0;
		while(look.name[i]) {
			i++;
			cnt++;
		}
		i = 0;
		while(look1.name[i]) {
			i++;
			cnt++;
		}
		char * name1 = (char *)malloc(sizeof(char) * (cnt + 1));
		int l = 0;
		i = 0;
		while(look.name[i]) {
			name1[l++] = look.name[i++];
		}
		i = 0;
		while(look1.name[i]) {
			name1[l++] = look1.name[i++];
		}
		name1[l] = 0;
		look.name = name1;
		look1 = nextToken();
	}
}

void match(int type) {
	if(look.type == type) {
		move();
	}else {
		printf("[%d]\n", type);
		ERROR(13);
	}
}

struct SymbolList {
	struct SymbolList * prev;
	struct Variable * vars;
	struct Function * funcs;
	struct Type * QaQ;//structs & unions
} * top;

struct SymbolList * newSymbolList(struct SymbolList * top) {
	struct SymbolList * res = (struct SymbolList *)malloc(sizeof(struct SymbolList));
	res->vars = 0;
	res->funcs = 0;
	res->QaQ = 0;
	res->prev = top;
	return res;
}

struct Operand {
	int constant;//编译时常数?
	int value;//如果是编译时常数, 值?
	int type;//0 直接左值, 1 解引用左值, 2 右值
	struct Variable * var;//操作数和变量类型
	int loadable;
};

int nLabel = 0;

int newLabel() {
	return nLabel++;
}

struct Instruction {
	int type;//
	int n;
	struct Operand * a;
	struct Operand * b;
	struct Operand * c;
	struct Instruction * next;
	struct Function * f;
} * assignInst = 0;

struct Operand * newOperand(struct Variable * var, int type, int constant, int value) {
	struct Operand * res = (struct Operand *)malloc(sizeof(struct Operand));
	res->constant = constant;
	res->type = type;
	res->value = value;
	res->var = var;
	res->loadable = 0;
	return res;
}

struct Instruction * newInstruction(int type, struct Operand * a, struct Operand * b, struct Operand * c) {
	struct Instruction * inst = (struct Instruction *)malloc(sizeof(struct Instruction));
	inst->f = 0;
	inst->n = 0;
	inst->a = a;
	inst->b = b;
	inst->c = c;
	inst->type = type;
	return inst;
}

struct FuncList {
	struct Function * f;
	struct FuncList * next;
} * funcList;

struct FuncList * newFuncList(struct Function * f, struct FuncList * next) {
	struct FuncList * res = (struct FuncList *)malloc(sizeof(struct FuncList));
	res->f = f;
	res->next = next;
	return res;
}

int isAssignmentOperator(int x) {
	return x == 504 || (x >= 532 && x <= 541);
}

struct Operand * constIntOrChar(int i) {
	struct Operand * res = (struct Operand *)malloc(sizeof(struct Operand));
	res->type = 2;
	res->constant = 1;
	res->value = i;
	res->var = newVariable();
	res->var->index = -1;
	totIndex--;
	//res->loadable = 1;
/*	res->var = (struct Variable *)malloc(sizeof(struct Variable));
	res->var->level = 0;
	res->var->name = newEmptyString();
	res->var->next = 0;
	res->var->list = 0;
	res->var->index = -1;*/
	return res;
}

struct Operand * constInt(int i) {//返回一个常量i
	struct Operand * res = constIntOrChar(i);
	res->var->type = INT_TYPE;
	return res;
}

struct Operand * constChar(int i) {//返回一个常量i
	struct Operand * res = constIntOrChar(i);
	res->var->type = CHAR_TYPE;
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
ASSIGN_DIV = 27,
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
INT_TO_CHAR = 38,
CHAR_TO_INT = 39,
DEREF_ASSIGN_ADDRESS = 40,
DEREF_ASSIGN = 41,
DEREF_ASSIGN_CHAR = 42,
RETURN = 43,
ASSIGN_ADDRESS_OF = 44,
ARGU = 45,
EXIT = 46,
VOID_RETURN = 47,
ASSIGN_DEREF_ADDRESS = 48,
ASSIGN_DEREF_CHAR = 49,
PUTINT = 50;
void printOperand(struct Operand * ope) {
//	if(ope->type == 0 && ope->var->name && ope->var->name[0]) {
//		printf("%s", ope->var->name);
//	}else {
		printf("R[%d]", ope->var->index);
//	}
	if(ope->constant) {
		printf("(constant ");
		if(ope->var->type == CHAR_TYPE && ope->var->level == 0 && ope->var->list == 0) {
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
		printf("declarate pointer %s := ", inst->a->var->name), printOperand(inst->a), printf("\n");
	}else if(inst->type == DECL_CHAR) {
		printf("declarate char %s := ", inst->a->var->name), printOperand(inst->a), printf("\n");
	}else if(inst->type == DECL_INT) {
		printf("declarate int %s := ", inst->a->var->name), printOperand(inst->a), printf("\n");
	}else if(inst->type == MALLOC) {
		printOperand(inst->a), printf(" = malloc "), printOperand(inst->b), printf("\n");
	}else if(inst->type == GETCHAR) {
		printOperand(inst->a), printf(" = getchar\n");
	}else if(inst->type == PUTCHAR) {
		printf("putchar "), printOperand(inst->a), printf("\n");
	}else if(inst->type == PUTINT) {
		printf("putint "), printOperand(inst->a), printf("\n");
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
	}else if(inst->type == ASSIGN_DIV) {
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
		printOperand(inst->a), printf(" = *(4)"),  printOperand(inst->b), printf("\n");
	}else if(inst->type == ASSIGN_DEREF_ADDRESS) {
		printOperand(inst->a), printf(" = *(%d)", POINTER_SIZE),  printOperand(inst->b), printf("\n");
	}else if(inst->type == ASSIGN_DEREF_CHAR) {
		printOperand(inst->a), printf(" = *(1)"),  printOperand(inst->b), printf("\n");
	}else if(inst->type == INT_TO_CHAR) {
		printOperand(inst->a), printf(" = (char)"),  printOperand(inst->b), printf("\n");
	}else if(inst->type == CHAR_TO_INT) {
		printOperand(inst->a), printf(" = (int)"),  printOperand(inst->b), printf("\n");
	}else if(inst->type == DEREF_ASSIGN_ADDRESS) {
		printf("address assign *(%d)", POINTER_SIZE), printOperand(inst->a), printf(" = "), printOperand(inst->b), printf("\n");
	}else if(inst->type == DEREF_ASSIGN) {
		printf("*(4)"), printOperand(inst->a), printf(" = "), printOperand(inst->b), printf("\n");
	}else if(inst->type == DEREF_ASSIGN_CHAR) {
		printf("*(1)"), printOperand(inst->a), printf(" = "), printOperand(inst->b), printf("\n");
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
		printf("argu "), printOperand(inst->a), printf("\n");
	}else {
		printf("\n\n???instruction???%d\n\n", inst->type);
	}
}
//print命令中, 只有赋值提供全部操作数, 其他运算都省去左边操作数作为临时操作数新建并返回.

void push(struct Function * env, struct Instruction * inst) {
	inst->next = env->insts;
	env->insts = inst;
}

void occupy(struct Function * env, struct Operand * ope) {
	struct List * new = newList();
	new->value = ope->var->index;
	new->next = env->occupy;
	env->occupy = new;
}

struct Operand * printCast(struct Function * env, struct Variable * a, struct Operand * b);

int isStruct(struct Variable * v) {
	return v->list == 0 && v->level == 0 && (v->type->type == 2 || v->type->type == 3);
}

struct Operand * getValue(struct Function * env, struct Operand * a) {
	if(!isStruct(a->var) && !a->var->list && a->type == 1) {
		struct Instruction * inst = newInstruction(0, newOperand(newVariable(), 2, 0, 0), a, 0);
		occupy(env, inst->a);
		copyType(inst->a->var, a->var);
		if(a->var->level) {
			inst->type = ASSIGN_DEREF_ADDRESS;
		}else if(a->var->type == CHAR_TYPE) {
			inst->type = ASSIGN_DEREF_CHAR;
		}else if(a->var->type == INT_TYPE) {
			inst->type = ASSIGN_DEREF;
		}else {
			ERROR(14);
		}
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
		return calcElementSize(var) * var->list->mul;
	}
}

void printArgu(struct Function * env, struct Operand * a);

struct Function * findFunc(char * a);

struct Operand * printAddressOf(struct Function * , struct Operand * );

void printAssign(struct Function * env, struct Operand * a, struct Operand * b) {//要处理是普通左值还是解引用左值
	if(a->var->list) {
		ERROR(15);
	}
	if(a->type == 2) {
		ERROR(85);
	}
	struct Operand * c = printCast(env, a->var, b);
	//printf("assign %s %d\n", a->var->name, a->var->level);
	if(isStruct(a->var)) {
		struct Operand * aa = newOperand(newVariable(), 0, 0, 0);
		struct Operand * cc = newOperand(newVariable(), 0, 0, 0);
		aa->var->type = CHAR_TYPE;
		cc->var->type = CHAR_TYPE;
		aa->var->level = 1;
		cc->var->level = 1;
		aa->var->index = a->var->index;
		cc->var->index = c->var->index;
		totIndex -= 2;
		printArgu(env, aa);
		printArgu(env, cc);
		printArgu(env, constInt(calcSize(a->var)));
		struct Instruction * inst = newInstruction(CALL, newOperand(newVariable(), 0, 0, 0), 0, 0);
		inst->a->var->type = VOID_TYPE;
		inst->f = findFunc(_c___memcpy__);
		inst->n = 3;
		push(env, inst);
		/*
		int i = 0, s = calcSize(a->var);
		for( ; i < s; ) {
			struct Instruction * inst = newInstruction(ASSIGN_ADD, newOperand(newVariable(), 1, 0, 0), a, constInt(i));
			push(env, inst);
			struct Instruction * inst1 = newInstruction(ASSIGN_ADD, newOperand(newVariable(), 1, 0, 0), c, constInt(i));
			if(i + 4 <= s) {
				i += 4;
			}else {
				i += 1;
				inst->a->var->type = CHAR_TYPE;
				inst1->a->var->type = CHAR_TYPE;
			}
			occupy(env, inst->a);
			occupy(env, inst1->a);
			push(env, inst1);
			printAssign(env, inst->a, inst1->a);
		}*/
	}else {
		struct Instruction * inst = newInstruction(0, a, c, 0);
		if(a->type == 0) {
			if(a->var->level) {
				inst->type = ASSIGN_ADDRESS;
			}else if(a->var->type == INT_TYPE) {
				inst->type = ASSIGN;//a = b;
			}else if(a->var->type == CHAR_TYPE) {
				inst->type = ASSIGN_CHAR;
			}
		}else if(a->type == 1) {
			if(a->var->level) {
				//printf("%s %d %d %d\n", env->name, a->var->level, inst->a->var->index, inst->b->var->index);
				inst->type = DEREF_ASSIGN_ADDRESS;
			}else if(a->var->type == INT_TYPE) {
				inst->type = DEREF_ASSIGN;//*a = b;
			}else if(a->var->type == CHAR_TYPE) {
				inst->type = DEREF_ASSIGN_CHAR;
			}
		}
		push(env, inst);
	}
}

int isIntOrChar(struct Variable * var) {
	return (var->type == INT_TYPE || var->type == CHAR_TYPE) && var->level == 0 && var->list == 0;
}

struct Operand * printAssignOp(struct Function * env, struct Operand * b, struct Operand * c, int op);

struct Operand * printAccess(struct Function * env, struct Operand * a, struct Operand * b) {
	b = printCast(env, INT_VARIABLE, b);
//	if(!isIntOrChar(b->var)) {
//		ERROR(16);
//	}
	a = getValue(env, a);
	if(a->var->list || a->var->level) {
		if(b->constant && b->value == 0) {
			struct Operand * res = newOperand(newVariable(), 1, 0, 0);
			copyType(res->var, a->var);
			//occupy(env, res);
			if(a->var->list) {
				res->var->list = a->var->list->next;
			}else {
				res->var->level = a->var->level - 1;
			}
			res->var->index = a->var->index;
			totIndex--;
			res->loadable = a->loadable && b->constant;
			return res;
		}else {
			struct Instruction * inst = newInstruction(ASSIGN_ADD, newOperand(newVariable(), 1, 0, 0), a, 0);
			occupy(env, inst->a);
			copyType(inst->a->var, a->var);
			if(a->var->list) {
				inst->a->var->list = a->var->list->next;
			}else {
				inst->a->var->level = a->var->level - 1;
			}
			inst->c = printAssignOp(env, b, constInt(calcSize(inst->a->var)), 532);
			push(env, inst);
			inst->a->loadable = a->loadable && b->constant;
			return inst->a;
		}
	}else {
		ERROR(17);
	}
}

struct Operand * printMalloc(struct Function * env, struct Operand * a);

struct Operand * printCopy(struct Function * env, struct Operand * a) {
	if(a->var->list) {
		ERROR(18);
	}
	//printf("parsePostfix++\n");
	struct Operand * ope = newOperand(newVariable(), 0, 0, 0);
	//printf("parsePostfix++ %d\n", env);
	occupy(env, ope);
	//	printf("parsePostfix++\n");
	if(isStruct(a->var)) {
		ope->type = 1;
		printMalloc(env, constInt(calcSize(a->var)));
		env->insts->a = ope;
	}
	copyType(ope->var, a->var);
	printAssign(env, ope, a);
	ope->type = 2;
	//printf("copy Complete %s %d\n", a->var->name, a->var->level);
	return ope;
}

void printArgu(struct Function * env, struct Operand * a) {
	struct Instruction * inst = newInstruction(ARGU, 0, 0, 0);
	if(isStruct(a->var)) {
		inst->a = printCopy(env, a);
	}else if(a->var->list) {
		inst->a = a;
	}else {
		inst->a = getValue(env, a);
	}
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

int isVoid(struct Variable * v) {
	return v->type == VOID_TYPE && !v->list && !v->level;
}

int isChar(struct Variable * v) {
	return v->type == CHAR_TYPE && !v->list && !v->level;
}

struct Operand * directLvalue(struct Variable * v) {//将变量转换为直接左值
	struct Operand * res = newOperand(v, !(v->list == 0 && !isStruct(v)), 0, 0);
	if(v->list || isStruct(v)) {
		res->loadable = 1;
	}
	return res;
}

int isPointer(struct Variable * v) {
	return v->list == 0 && v->level >= 1;
}

struct Operand * printCast(struct Function * env, struct Variable * b, struct Operand * a) {
	if(a->type == 1) {
		a = getValue(env, a);
	}
	if(isVoid(b)) {
		return directLvalue(VOID_VARIABLE);
	}
	if(isVoid(a->var)) {
		ERROR(20);
	}
	if(compType(b, a->var)) {
		return a;
	}
	if(isStruct(a->var) || isStruct(b)) {
		ERROR(19);
	}
	int s1 = isChar(b), s2 = isChar(a->var);
	struct Instruction * inst;
	if(s1 && !s2) {
		inst = newInstruction(INT_TO_CHAR, newOperand(newVariable(), 2, a->constant, a->value), a, 0);
		occupy(env, inst->a);
		inst->a->var->type = CHAR_TYPE;
		assignInst = inst;
		push(env, inst);
		return inst->a;
	}else {
		if(s2 && !s1) {
			inst = newInstruction(CHAR_TO_INT, newOperand(newVariable(), 2, a->constant, a->value), a, 0);
			occupy(env, inst->a);
			copyType(inst->a->var, b);
			assignInst = inst;
			push(env, inst);
			return inst->a;
		}else {
			struct Operand * res = newOperand(newVariable(), 2, a->constant, a->value);
			copyType(res->var, b);
			//occupy(env, res);
			res->var->index = a->var->index;
			totIndex--;
			return res;
		}
	}
}

struct Operand * printCall(struct Function * env, struct Function * f, int n) {
	struct Instruction * inst = newInstruction(CALL, newOperand(newVariable(), 2, 0, 0), 0, 0);
	occupy(env, inst->a);
	copyType(inst->a->var, f->rtn);
	inst->f = f;
	inst->n = n;
	push(env, inst);
	return inst->a;
}

struct Variable * findMem(struct Variable * vars, char * name) ;

struct Operand * printMemberAccess(struct Function * env, struct Operand * a, char * name) {
	if(!isStruct(a->var)) {
		ERROR(22);
	}else {
		if(a->var->type->type == 3) {
			struct Operand * res = newOperand(newVariable(), 2 - (a->type == 1), 0, 0);
			//occupy(env, res);
			copyType(res->var, findMem(a->var->type->vars, name));
			res->var->index = a->var->index;
			totIndex--;
			res->loadable = a->loadable;
			return res;
		}else if(a->var->type->type == 2) {
			struct Variable * p = a->var->type->vars;
			struct List * l = a->var->type->posi;
			while(p) {
				if(!strcmp(p->name, name)) {
					if(l->value) {
						struct Instruction * inst = newInstruction(ASSIGN_ADD, newOperand(newVariable(), 2 - (a->type == 1), 0, 0), a, constInt(l->value));
						occupy(env, inst->a);
						copyType(inst->a->var, p);
						push(env, inst);
						inst->a->loadable = a->loadable;
						return inst->a;
					}else {
						struct Operand * res = newOperand(newVariable(), 2 - (a->type == 1), 0, 0);
						//occupy(env, res);
						copyType(res->var, p);
						res->var->index = a->var->index;
						totIndex--;
						res->loadable = a->loadable;
						return res;
					}
				}
				p = p->next;
				l = l->next;
			}
			ERROR(91);
		}else {
			ERROR(23);
		}
	}
}

struct Operand * printDeref(struct Function * env, struct Operand * a) {
	if(a->var->list == 0 && a->var->level == 0) {
		ERROR(24);
	}
	//struct Instruction * inst = newInstruction(ASSIGN_ADDRESS, newOperand(newVariable(), 1, 0, 0), 0, 0);
	a = getValue(env, a);
	struct Operand * res = newOperand(newVariable(), 1, 0, 0);
	copyType(res->var, a->var);
	//occupy(env, res);
	res->var->index = a->var->index;
	if(a->var->list) {
		res->var->list = res->var->list->next;
	}else {
		res->var->level--;
	}
	totIndex--;
	res->loadable = a->loadable || a->constant;
	return res;
/*	if(a->var->list) {
		copyType(inst->a->var, a->var);
		inst->a->var->list = a->var->list->next;
		inst->b = a;
	}else {
		inst->b = getValue(env, a);
		*inst->a->var = *a->var;
		inst->a->var->level--;
	}
	push(env, inst);
	return inst->a;*/
}

struct Operand * printAssignOp(struct Function * env, struct Operand * b, struct Operand * c, int op) {
	if(op == 522 || op == 523) {
		if(b->loadable && (b->var->list || b->type != 1)) {
			b = constInt(1);
		}
		if(c->loadable && (c->var->list || c->type != 1)) {
			c = constInt(1);
		}
	}
	if(b->constant && c->constant) {
		int res;
		if(op == 523) {
			res = b->value && c->value;
		}else if(op == 522) {
			res = b->value || c->value;
		}else if(op == 513) {
			res = b->value < c->value;
		}else if(op == 514) {
			res = b->value > c->value;
		}else if(op == 526) {
			res = b->value <= c->value;
		}else if(op == 527) {
			res = b->value >= c->value;
		}else if(op == 524) {
			res = b->value == c->value;
		}else if(op == 525) {
			res = b->value != c->value;
		}else if(op == 532) {
			res = b->value * c->value;
		}else if(op == 533) {
			res = b->value / c->value;
		}else if(op == 534) {
			res = b->value % c->value;
		}else if(op == 535) {
			res = b->value + c->value;
		}else if(op == 536) {
			res = b->value - c->value;
		}else if(op == 537) {
			res = b->value << c->value;
		}else if(op == 538) {
			res = b->value >> c->value;
		}else if(op == 539) {
			res = b->value & c->value;
		}else if(op == 540) {
			res = b->value ^ c->value;
		}else if(op == 541) {
			res = b->value | c->value;
		}
		//printf("const operation %d\n", res);
		return constInt(res);
	}
	if(op == 532 && (b->constant && b->value == 0 || c->constant && c->value == 0)) {
		return constInt(0);
	}
	if(op == 522 && (b->constant && b->value || c->constant && c->value)) {
		return constInt(1);
	}
	if(op == 523 && (b->constant && !b->value || c->constant && !c->value)) {
		return constInt(0);
	}
	//printf("%s %s %d %d %d %d\n", b->var->name, c->var->name, isVoid(b->var), isVoid(c->var), isStruct(b->var), isStruct(c->var));
	if(isVoid(b->var) || isVoid(c->var) || isStruct(b->var) || isStruct(c->var)) {
		ERROR(25);
	}
	struct Instruction * inst;
	int loadable = b->loadable && c->loadable;
	if(op == 535 || op == 536) {
		if(isIntOrChar(b->var) && isIntOrChar(c->var)) {
			b = printCast(env, INT_VARIABLE, b);
			c = printCast(env, INT_VARIABLE, c);
			if(op == 536 && b->var->index == c->var->index) {
				return constInt(0);
			}
			inst = newInstruction(0, newOperand(newVariable(), 2, 0, 0), b, c);
			occupy(env, inst->a);
			if(op == 535) {
				inst->type = ASSIGN_ADD;
			}else {
				inst->type = ASSIGN_SUB;
			}
			/*if(b->constant && c->constant) {
				inst->a->constant = 1;
				if(op == 535) {
					inst->a->value = b->value + c->value;
				}else {
					inst->a->value = b->value - c->value;
				}
			}*/
			push(env, inst);
			assignInst = inst;
			return inst->a;
		}else if(isPointer(b->var) || isPointer(c->var) || b->var->list || c->var->list) {
			//printf("Pointer operation\n");
			if(compType(b->var, c->var) && op == 536) {
//				printf("!!\n");
				if(b->var->index == c->var->index) {
//				printf("!!\n");
					struct Operand * ope = newOperand(newVariable(), 2, 0, 0);
					//copyType(ope->var, b->var);
					ope->var->index = -1;
					totIndex--;
					ope->constant = 1;
					ope->value = 0;
					return ope;
				}
				inst = newInstruction(ASSIGN_SUB, newOperand(newVariable(), 2, 0, 0), b, c);//指针相减
				occupy(env, inst->a);
				push(env, inst);
				struct List * bak = b->var->list;
				if(bak) {
					b->var->list = bak->next;	
				}else {
					b->var->level--;
				}
				struct Operand * ope = constInt(calcSize(b->var));
				if(bak) {
					b->var->list = bak;
				}else {
					b->var->level++;
				}
				return printAssignOp(env, inst->a, ope, 533);
			}else {
				inst = newInstruction(0, 0, 0, 0);
				if(op == 535) {
					inst->type = ASSIGN_ADD;
				}else {
					inst->type = ASSIGN_SUB;
				}
				if(isPointer(c->var) || c->var->list) {
					if(op == 536) {
						ERROR(26);
					}
					struct Operand * tmp = b;
					b = c;
					c = tmp;
				}
				if(isPointer(c->var) || c->var->list) {
					ERROR(27);
				}
				inst->a = newOperand(newVariable(), 2, 0, 0);
				occupy(env, inst->a);
				copyType(inst->a->var, b->var);
				inst->b = b;
				struct List * bak = b->var->list;
				if(bak) {
					b->var->list = bak->next;	
				}else {
					b->var->level--;
				}
				//printf("%s %d\n", b->var->name, b->var->level);
				inst->c = printAssignOp(env, constInt(calcSize(b->var)), printCast(env, INT_VARIABLE, c), 532);
				//printf("%s %d\n", b->var->name, b->var->level);
				if(bak) {
					b->var->list = bak;
				}else {
					b->var->level++;
				}
				//printf("%s %d\n", b->var->name, b->var->level);
				push(env, inst);
				assignInst = inst;
				inst->a->loadable = b->loadable && c->constant;
				return inst->a;
			}
		}else {
			ERROR(28);
		}
	}else {
		b = printCast(env, INT_VARIABLE, b);
		c = printCast(env, INT_VARIABLE, c);
		inst = newInstruction(0, newOperand(newVariable(), 2, 0, 0), b, c); 
		occupy(env, inst->a);
		if((isPointer(b->var) || isPointer(c->var)) && op != 524 && op != 525 && op != 523 && op != 522 && op != 513 && op != 514 && op != 526 && op != 527) {//指针可以进行的算术操作, 除了刚才的指针加减整数, 整数加指针, 指针减指针, 还有<=, >=, <, >, ==, !=, &&, ||
			ERROR(29);
		}
		if(op == 523) {
			inst->type = ASSIGN_LOGIC_AND;
		}else if(op == 522) {
			inst->type = ASSIGN_LOGIC_OR;
		}else if(op == 513) {
			inst->type = ASSIGN_LESS_THAN;
		}else if(op == 514) {
			inst->type = ASSIGN_GREATER_THAN;
		}else if(op == 526) {
			inst->type = ASSIGN_LESS_THAN_OR_EQUAL_TO;
		}else if(op == 527) {
			inst->type = ASSIGN_GREATER_THAN_OR_EQUAL_TO;
		}else if(op == 524) {
			inst->type = ASSIGN_EQUAL_TO;
		}else if(op == 525) {
			inst->type = ASSIGN_NOT_EQUAL_TO;
		}else if(op == 532) {
			inst->type = ASSIGN_MUL;
		}else if(op == 533) {
			inst->type = ASSIGN_DIV;
		}else if(op == 534) {
			inst->type = ASSIGN_MOD;
		}else if(op == 535) {
			inst->type = ASSIGN_ADD;
		}else if(op == 536) {
			inst->type = ASSIGN_SUB;
		}else if(op == 537) {
			inst->type = ASSIGN_SHL;
		}else if(op == 538) {
			inst->type = ASSIGN_SHR;
		}else if(op == 539) {
			inst->type = ASSIGN_AND;
		}else if(op == 540) {
			inst->type = ASSIGN_EXCLUSIVE_OR;
		}else if(op == 541) {
			inst->type = ASSIGN_INCLUSIVE_OR;
		}
		push(env, inst);
		assignInst = inst;
		inst->a->loadable = loadable;
		return inst->a;
	}
}

struct Operand * printAddressOf(struct Function * env, struct Operand * a) {
	if(a->var->list) {// || isVoid(a->var)) {
		ERROR(30);//阉割版,不允许对数组取地址, 保证处理的变量全都是基本类型的指针的数组.
	}
	if(a->type == 0) {
		struct Instruction * inst = newInstruction(0, newOperand(newVariable(), 2, 0, 0), a, 0);
		occupy(env, inst->a);
		inst->type = ASSIGN_ADDRESS_OF;
		copyType(inst->a->var, a->var);
		inst->a->var->level++;
		push(env, inst);
		assignInst = inst;
		if(a->var->name[0]) {
			inst->a->loadable = 1;
		}
		return inst->a;
	}else if(a->type == 1) {
		struct Operand * res = newOperand(newVariable(), 2, 0, 0);
		copyType(res->var, a->var);
		//occupy(env, res);
		res->var->level++;
		res->var->index = a->var->index;
		totIndex--;
		res->loadable = a->loadable;
		return res;
	}else {
		ERROR(31);
	}
}

void printNNP(struct Function * env, struct Operand * a) {
	if(!isIntOrChar(a->var)) {
		ERROR(32);
	}
	struct Instruction * inst = newInstruction(0, newOperand(newVariable(), 2, 0, 0), printCast(env, INT_VARIABLE, a), 0);
	occupy(env, inst->a);
	assignInst = inst;
	push(env, inst);
}

struct Operand * printPosite(struct Function * env, struct Operand * a) {
	if(a->constant) {
		return constInt(a->value);
	}
	printNNP(env, a);
/*	if(env->insts->b->constant) {
		env->insts->a->constant = 1;
		env->insts->a->value = env->insts->b->value;
	}*/
	env->insts->type = ASSIGN;
	return env->insts->a;
}

struct Operand * printNegate(struct Function * env, struct Operand * a) {
	if(a->constant) {
		return constInt(-a->value);
	}
	printNNP(env, a);
/*	if(env->insts->b->constant) {
		env->insts->a->constant = 1;
		env->insts->a->value = -env->insts->b->value;
	}*/
	env->insts->type = ASSIGN_NEGATE;
	return env->insts->a;
}

struct Operand * printNot(struct Function * env, struct Operand * a) {
	if(a->constant) {
		return constInt(~a->value);
	}
	printNNP(env, a);
/*	if(env->insts->b->constant) {
		env->insts->a->constant = 1;
		env->insts->a->value = ~env->insts->b->value;
	}*/
	env->insts->type = ASSIGN_NOT;
	return env->insts->a;
}

struct Operand * printLogicalNot(struct Function * env, struct Operand * a) {
	if(a->constant) {
		return constInt(!a->value);
	}
	if(a->loadable && (a->var->list || a->type != 1)) {
		return constInt(1);
	}
	struct Instruction * inst = newInstruction(ASSIGN_LOGICAL_NOT, newOperand(newVariable(), 2, 0, 0), printCast(env, INT_VARIABLE, a), 0);
	occupy(env, inst->a);
	//if(inst->b->constant) {
	//	inst->a->constant = 1;
	//	inst->a->value = !inst->b->value;
	//}
	push(env, inst);
	assignInst = inst;
	inst->a->loadable = a->loadable;
	return inst->a;
}

void printGoto(struct Function * env, int label);

void printIfFalseGoto(struct Function * env, struct Operand * a, int label) {
	a = getValue(env, a);
	if(a->constant) {
		if(a->value) {
			return;
		}else {
			printGoto(env, label);
		}
	}else {	
		struct Instruction * inst = newInstruction(IF_FALSE_GOTO, printCast(env, INT_VARIABLE, a), 0, 0);
		inst->n = label;
		push(env, inst);
	}
}

void printIfGoto(struct Function * env, struct Operand * a, int label) {
	a = getValue(env, a);
	if(a->constant) {
		if(!a->value) {
			return;
		}else {
			printGoto(env, label);
		}
	}else {	
		struct Instruction * inst = newInstruction(IF_GOTO, printCast(env, INT_VARIABLE, a), 0, 0);
		inst->n = label;
		push(env, inst);
	}
}

void printLabel(struct Function * env, int label) {
	struct Instruction * inst = newInstruction(LABEL, 0, 0, 0);
	inst->n = label;
	push(env, inst);
}

void printGoto(struct Function * env, int label) {
	struct Instruction * inst = newInstruction(GOTO, 0, 0, 0);
	inst->n = label;
	push(env, inst);
}

char _c___memset__[20] = "__memset__";

struct Function * findFunc(char * name);

void printFillZero(struct Function * env, struct Operand * a) {
	if(a->type == 0) {
		struct Instruction * inst = newInstruction(0, a, 0, 0);
		if(isChar(a->var)) {
			inst->type = ASSIGN_CHAR;
			inst->b = constChar(0);
		}else if(isPointer(a->var)){
			inst->type = ASSIGN_ADDRESS;
			inst->b = constInt(0);
		}else {
			inst->type = ASSIGN;
			inst->b = constInt(0);
		}
		push(env, inst);
	}else {
		printArgu(env, a);
		printArgu(env, constInt(calcSize(a->var)));
		struct Instruction * inst = newInstruction(CALL, newOperand(newVariable(), 0, 0, 0), 0, 0);
		inst->a->var->type = VOID_TYPE;
		inst->n = 2;
		inst->f = findFunc(_c___memset__);
		push(env, inst);
/*		int i = 0, s = calcSize(a->var);
		for( ; i < s; ) {
			struct Instruction * inst = newInstruction(ASSIGN_ADD, newOperand(newVariable(), 1, 0, 0), a, constInt(i));
			occupy(env, inst->a);
			if(i + 4 <= s) {
				i += 4;
				push(env, inst);
				printAssign(env, inst->a, constInt(0));
			}else {
				i += 1;
				inst->a->var->type = CHAR_TYPE;
				push(env, inst);
				printAssign(env, inst->a, constChar(0));
			}
		}
*/
	}
}

void printNOP(struct Function * env) {
	struct Instruction * inst = newInstruction(NOP, 0, 0, 0);
	push(env, inst);
}

struct Operand * printPutchar(struct Function * env, struct Operand * a) {//务必返回void
	if(isVoid(a->var) || isStruct(a->var)) {
		ERROR(33);
	}
	struct Instruction * inst = newInstruction(PUTCHAR, getValue(env, a), 0, 0);
	push(env, inst);
	return directLvalue(VOID_VARIABLE);
}

struct Operand * printPutint(struct Function * env, struct Operand * a) {//务必返回void
	if(isVoid(a->var) || isStruct(a->var)) {
		ERROR(33);
	}
	struct Instruction * inst = newInstruction(PUTINT, getValue(env, a), 0, 0);
	push(env, inst);
	return directLvalue(VOID_VARIABLE);
}

struct Operand * printGetchar(struct Function * env) {
	struct Instruction * inst = newInstruction(GETCHAR, newOperand(newVariable(), 2, 0, 0), 0, 0);
	occupy(env, inst->a);
	assignInst = inst;
	push(env, inst);
	return inst->a;
}

struct Operand * printMalloc(struct Function * env, struct Operand * a) {
	if(isVoid(a->var) || isStruct(a->var)) {
		ERROR(34);
	}
	struct Instruction * inst = newInstruction(MALLOC, newOperand(newVariable(), 2, 0, 0), getValue(env, a), 0);
	inst->a->var->type = VOID_TYPE;
	inst->a->var->level = 1;
	push(env, inst);
	return inst->a;
}

void printDeclInt(struct Function * env, struct Operand * a) {
	struct Instruction * inst = newInstruction(DECL_INT, a, 0, 0);
	push(env, inst);
}

void printDeclChar(struct Function * env, struct Operand * a) {
	struct Instruction * inst = newInstruction(DECL_CHAR, a, 0, 0);
	push(env, inst);
}

void printDeclPointer(struct Function * env, struct Operand * a) {
	struct Instruction * inst = newInstruction(DECL_POINTER, a, 0, 0);
	push(env, inst);
}

void printGetArgu(struct Function * env, struct Operand * a) {
	struct Instruction * inst = newInstruction(GET_ARGU, a, 0, 0);
	push(env, inst);
}

void printReturn(struct Function * env, struct Operand * a) {
	if(isVoid(a->var)) {
		ERROR(35);
	}
	struct Instruction * inst = newInstruction(RETURN, getValue(env, a), 0, 0);
	push(env, inst);
}

void printVoidReturn(struct Function * env) {
	struct Instruction * inst = newInstruction(VOID_RETURN, 0, 0, 0);
	push(env, inst);
}

struct Operand * printExit(struct Function * env, struct Operand * a) {
	struct Instruction * inst = newInstruction(EXIT, printCast(env, INT_VARIABLE, a), 0, 0);
	push(env, inst);
	return directLvalue(VOID_VARIABLE);
}

struct Operand * parsePrimaryExpression(struct Function * env) {
	//printf("primary %d\n", env);
	//printf("%d %s\n", look.type, look.name, program[0], program[1], program[2], program[3]);
	if(look.type == IDENTIFIER) {
		char * bak = look.name;
		//printf("%s\n", look.name);
		move();
		struct Variable * v = findVariable(bak);
		//printf("%d\n", v);
		//printf("%d\n", v->type);
		
		if(v) {
		//	printf("%d\n", v);
			//printf("IDENTIFIER %s %d\n", v->name, v->level);
			return directLvalue(v);
		}else {
			v = newVariable();
			v->name = bak;
			v->type = FUNC_TYPE;
			return directLvalue(v);
		}
	}else if(look.type == INT_CONSTANT) {
		int bak = look.value;
		move();
		return constInt(bak);
	}else if(look.type == CHR_CONSTANT) {
		int bak = look.value;
		move();
		return constChar(bak);
	}else if(look.type == STR_CONSTANT) {
		int len = 0;
		while(look.name[len]) {
			len++;
		}
		printMalloc(env, constInt(len + 1));
		struct Operand * res = newOperand(newVariable(), 1, 0, 0);
		res->var->type = CHAR_TYPE;
		res->var->list = newList();
		struct Instruction * inst = env->insts;
		inst->a = res;
		occupy(env, inst->a);
		int i = 0;
		for( ; look.name[i]; i++) {
			printAssign(env, printAccess(env, inst->a, constInt(i)), constChar(look.name[i]));
		}
		printAssign(env, printAccess(env, inst->a, constInt(len)), constChar(0));
		res->var->list->value = i + 1;
		res->var->list->prev = res->var->list;
		move();
		return inst->a;
	}else if(look.type == 500) {//'('
		move();
		struct Operand * res = parseExpression(env);
		match(501);//')'
		return res;
	}else {
		ERROR(36);
	}
}

char _c_putchar__[8] = "putchar";

char _c_putint__[8] = "putint";

char _c_malloc__[8] = "malloc";

char _c_getchar__[8] = "getchar";

char _c_printf__[8] = "printf";

char _c___printf____[12] = "__printf__";

char _c_exit__[8] = "exit";

struct Function * findFunc(char * name);

struct Operand * parseActualArgument(struct Function * env, struct Operand * p) {
	struct Operand * res;
		//printf("!!%s\n", p->var->name);
	
	if(!strcmp(p->var->name, _c_putchar__)) {
		res = printPutchar(env, parseAssignmentExpression(env));
		if(look.type != 501) {
			ERROR(37);
		}
		return res;
	}else if(!strcmp(p->var->name, _c_putint__)) {
		res = printPutint(env, parseAssignmentExpression(env));
		if(look.type != 501) {
			ERROR(86);
		}
		return res;
	}else if(!strcmp(p->var->name, _c_malloc__)) {
		res = printMalloc(env, parseAssignmentExpression(env));
		occupy(env, res);
		if(look.type != 501) {
			ERROR(38);
		}
		return res;
	}else if(!strcmp(p->var->name, _c_getchar__)) {
		res = printGetchar(env);
		if(look.type != 501) {
			ERROR(39);
		}
		return res;
	}else if(!strcmp(p->var->name, _c_exit__)) {
		res = printExit(env, parseAssignmentExpression(env));
		if(look.type != 501) {
			ERROR(40);
		}
		return res;
	}else if(!strcmp(p->var->name, _c_printf__)) {
		struct Variable * v = newVariable();
		v->type = CHAR_TYPE;
		v->level = 1;
		printArgu(env, printCast(env, v, parseAssignmentExpression(env)));
		struct Operand * ope = newOperand(newVariable(), 0, 0, 0);
		ope->var->level = 1;//手动int*
		int cnt = 0;
		printMalloc(env, constInt(cnt * POINTER_SIZE));
		struct Instruction * inst = env->insts;
		inst->a = ope;
		while(look.type != 501) {//')'
			match(503);//','
			struct Operand * res;
			res = parseAssignmentExpression(env);
			if(isStruct(res->var)) {
				res = constInt(0);
			}else {
				res = printCast(env, INT_VARIABLE, res);
			}
			printAssign(env, printAccess(env, ope, constInt(cnt)), res	);
			cnt++;
		}
		inst->b->value = cnt * POINTER_SIZE;
		printArgu(env, ope);
		return printCall(env, findFunc(_c___printf____), 2);
	}else {
		struct Function * f = findFunc(p->var->name);
		if(!f) {
			printf("function %s unfound\n", p->var->name);
			ERROR(41);
		}
		struct Variable * v = f->argu;
		int n = 0;
		if(v == 0) {
			while(look.type != 501) {//')'
				parseAssignmentExpression(env);
				if(look.type != 501) {
					match(503);//','
				}
			}
		}else {
			while(v) {
				n++;
				printArgu(env, printCast(env, v, parseAssignmentExpression(env)));
				v = v->next;
				if(v) {
					match(503);//','
				}
			}
		}
		return printCall(env, f, n);
	}
}

struct Variable * parseTypeName() {
	struct Variable * v = newVariable();
	if(look.type == 301) {//void
		v->type = VOID_TYPE;
		move();
	}else if(look.type == 302) {//char
		move();
		v->type = CHAR_TYPE;
	}else if(look.type == 303) {//int
		move();
		v->type = INT_TYPE;
	}else if(look.type == 304 || look.type == 305) {//struct union
		move();
		if(look.type != IDENTIFIER) {
			ERROR(42);
		}
		v->type = find(look.name);
		if(v->type == 0) {
			ERROR(43);
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
	//printf("post %d\n", env);
	if(p->var->type == FUNC_TYPE && look.type != 500) {
		ERROR(44);
	}
	if(look.type == 507) {//'['
		move();
		//printf("parsePostfixAccess %s %d %d\n", p->var->name, p->type, p->var->level);
		res = printAccess(env, p, parseExpression(env));
		match(508);//']'
		return parsePostfix(env, res);
	}else if(look.type == 500) {//'('
		move();
		if(p->var->type != FUNC_TYPE) {
			ERROR(97);
		}
		res = parseActualArgument(env, p);
		match(501);
		return parsePostfix(env, res);
	}else if(look.type == 521) {//'.'
		move();
		if(look.type != IDENTIFIER) {
			ERROR(45);
		}
		res = printMemberAccess(env, p, look.name);
		move();
		return parsePostfix(env, res);
	}else if(look.type == 542) {//'->'
		move();
		res = printDeref(env, p);
		if(look.type != IDENTIFIER) {
			ERROR(46);
		}
		res = printMemberAccess(env, res, look.name);
		move();
		res = parsePostfix(env, res);
		return res;
	}else if(look.type == 530) {//'++'
		move();
		//printf("parsePostfix++ %d\n", env);
		res = printCopy(env, p);
		//printf("parsePostfix++\n");
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
		//printf("return %d\n", env);
		return p;
	}
}

struct Operand * parsePostfixExpression(struct Function * env) {
	struct Operand * res = parsePrimaryExpression(env);
	//printf("pp %d\n", env);
	return parsePostfix(env, res);
}

struct Operand * parseCastExpression(struct Function * env);

struct Operand * parseUnaryExpression(struct Function * env) {
	if(look.type == 530) {//'++'
		move();
		struct Operand * tmp = parseUnaryExpression(env), *tmp1;
		if(tmp->type != 0 && tmp->type != 1) {//DIRECT LEFT VALUE OR DEREF LEFT VALUE
			ERROR(47);
		}
		tmp1 = printAssignOp(env, tmp, constInt(1), 535);
		printAssign(env, tmp, tmp1);
		return tmp;
	}else if(look.type == 531) {//'--'
		move();
		struct Operand * tmp = parseUnaryExpression(env), * tmp1;
		if(tmp->type != 0 && tmp->type != 1) {
			ERROR(48);
		}
		tmp1 = printAssignOp(env, tmp, constInt(1), 536);
		printAssign(env, tmp, tmp1);
		return tmp;
	}else if(look.type == 512) {//'&'
		move();
		struct Operand * tmp = parseCastExpression(env);
		return printAddressOf(env, tmp);
	}else if(look.type == 509) {//'*'
		move();
		//printf("U %d\n", env);
		struct Operand * tmp = parseCastExpression(env);
	//	printf("U %d\n", env);
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
			if(look.type >= 301 && look.type <= 305) {//void int char union struct
				struct Variable * v = parseTypeName();
				match(501);//')'
				if(v->level) {
					return constInt(POINTER_SIZE);
				}else {
					if(v->type->size == -1) {
						ERROR(49);
					}
					return constInt(v->type->size);
				}
			}else {
				struct Operand * tmp = parseExpression(env);
				match(501);
				tmp = parsePostfix(env, tmp);
				return constInt(calcSize(tmp->var));
			}
		}else {
			struct Operand * tmp = parseUnaryExpression(env);
			return constInt(calcSize(tmp->var));
		}
	}else {
		return parsePostfixExpression(env);
	}
}

struct Operand * parseCastExpression(struct Function * env) {
	if(look.type == 500) {//'('
		move();
		if(look.type == 303 || look.type == 304 || look.type == 305 || look.type == 302 || look.type == 301) {
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
		return res;
	}
	for(;;) {
		if(look.type == 523) {//'&&'
			move();
			printIfFalseGoto(env, res, x);
			struct Operand * ope = parseInclusiveOrExpression(env);
			res = printAssignOp(env, res, ope, 523);
		}else {
			break;
		}
	}
	if(res->constant) {
		return res;
	}
	struct Operand * rtn = newOperand(newVariable(), 0, 0, 0);
	printAssign(env, rtn, res);
	int y = newLabel();
	printGoto(env, y);
	printLabel(env, x);
	printAssign(env, rtn, constInt(0));
	printLabel(env, y);
	rtn->type = 2;
	rtn->constant = res->constant;
	rtn->value = res->value;
	return rtn;
}


struct Operand * parseLogicalOrExpression(struct Function * env) {
	struct Operand * res = parseLogicalAndExpression(env);
	int x = -1;
	if(look.type == 522) {
		x = newLabel();
	}else {
		//printf("LO %d\n", env);
		return res;
	}
	for(;;) {
		if(look.type == 522) {//'||'
			move();
			printIfGoto(env, res, x);
			struct Operand * ope = parseLogicalAndExpression(env);
			res = printAssignOp(env, res, ope, 522);
		}else {
			break;
		}
	}
	if(res->constant) {
		return res;
	}
	struct Operand * rtn = newOperand(newVariable(), 0, 0, 0);
	printAssign(env, rtn, res);
	int y = newLabel();
	printGoto(env, y);
	printLabel(env, x);
	printAssign(env, rtn, constInt(1));
	printLabel(env, y);
	rtn->type = 2;
	rtn->constant = res->constant;
	rtn->value = res->value;
	return rtn;
}

struct Operand * parseConstantExpression(struct Function * env) {
	struct Operand * res = parseLogicalOrExpression(env);
	if(!res->constant) {
		ERROR(82);
	}
	return res;
}

struct Operand * parseAssignmentExpression(struct Function * env) {
	struct Operand * res = parseLogicalOrExpression(env);
	if(isAssignmentOperator(look.type)) {
		int assignType = look.type;
		move();
		if(res->type != 0 && res->type != 1 || res->var->list) {//DIRECT LVALUE or DEREF LVALUE.
			ERROR(50);
		}//TO BE CONTINUED
		if(assignType == 504) {
			struct Operand * tmp = parseAssignmentExpression(env);
			//printf("%d %d %d %d %d\n", assignInst, tmp, assignInst->a, isChar(tmp->var), isChar(res->var));
			if(assignInst && tmp == assignInst->a && isChar(tmp->var) == isChar(res->var) && res->type == 0) {
				assignInst->a = res;
			}else {
				printAssign(env, res, tmp);
			}
		}else {
			struct Operand * tmp = printAssignOp(env, res, parseAssignmentExpression(env), assignType);
			if(assignInst && tmp == assignInst->a && isChar(tmp->var) == isChar(res->var) && res->type == 0) {
				assignInst->a = res;//优化: 表达式拼接 such as a = b + c => t1 = b + c, a = t1 => a = b + c
			}else {
				printAssign(env, res, tmp);
			}
		}
		return res;
	}else {
		//printf("AE %d\n", env);
		
		return res;
	}
}

struct Operand * parseExpression(struct Function * env) {
	struct Operand * res;
	for(;;) {
		res = parseAssignmentExpression(env);
		if(look.type == 503) {//','
			move();
			continue;
		}else {
			//printf("E %d\n", env);
		
			break;
		}
	}
	return res;
}


struct List * parseArray() {//分析数组
	struct List * v = 0;
	while(look.type == 507) {//'['
		move();
		struct Operand * ope = parseConstantExpression(bucket);//分析常量表达式
		if(ope->constant == 0 || ope->constant && ope->value < 0 || !isIntOrChar(ope->var)) {
			ERROR(51);
		}
		struct List * a = newList();
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
	//printf("%d\n", look.type);
	while(look.type == 509) {//'*'
		v->level++;
		//printf("*\n");
		move();
	}
	if(look.type == IDENTIFIER) {
		v->name = look.name;
		move();
	}else {
		if(!enableAnony) {
			ERROR(52);
		}else {
			v->name = newEmptyString();
		}
	}
	//printf("%s\n", v->name);
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

struct Type * findTop(char * name) {
	//printf("findTop %d %d\n", top, top->QaQ);
	struct Type * itr = top->QaQ;
	while(itr) {
		//printf("%s %s\n", itr->name, name);
		if(!strcmp(itr->name, name)) {
			return itr;
		}
		//printf("%s %s\n", itr->name, name);
		itr = itr->next;
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

struct Type * parseTypeSpecifier() {//分析类型
	if(look.type == 304 || look.type == 305) {//'struct' 'union'类型
		int s_or_u = look.type;
		move();
		struct Token structName = look;
		if(structName.type != IDENTIFIER) {
			if(structName.type != 505) {
				ERROR(53);
			}else {
				structName.name = newEmptyString();
			}
		}else {
			move();
		}
		//printf("Typename %s\n", structName.name);
		if(look.type == 505) {//'{'说明要先定义
			struct Type * a;
			a = findTop(structName.name);
			if(structName.name[0] == 0 || a == 0) {
				a = (struct Type *)malloc(sizeof(struct Type));
				a->next = top->QaQ;
				top->QaQ = a;
			}else {
				if(a->size != -1 || a->type != s_or_u - 302) {
					ERROR(54);
				}
			}
			a->size = 0;
			a->vars = 0;
			a->type = s_or_u - 302;
			a->name = structName.name;
			move();
//			struct SymbolList * newTop = newSymbolList(top);
//			top = newTop;
			for(; look.type != 506;) {//'}'
				struct Type * t = parseTypeSpecifier();//分析成员的类型
				int flag = 0;
				for( ; look.type != 502; ) {//';'
					if(look.type == 506) {//'}', struct A {int x};这样可以的.
						break;
					}
					flag = 1;
					struct Variable * v = parsePlainDeclarator(0);//成员的名字和数组阶数
					if(findMem(a->vars, v->name)) {//成员不能重名
						ERROR(55);
					}
					if(look.type == 507) {//'['说明是数组成员
						v->list = parseArray();
					}
					v->type = t;
					if(v->level == 0 && v->type->size == -1) {
						ERROR(56);//未完成类型
					}
					v->next = a->vars;
					a->vars = v;
					struct List * l = newList();
					l->value = a->size;
					l->next = a->posi;
					a->posi = l;
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
//				printf("%s t %d %d\n", a->name, t->vars, t->name);
				
				if(look.type == 502) {
					move();
				}
				if((t->type == 3 || t->type == 2) && t->name[0] == 0 && flag == 0) {//struct{struct{int a, b;}} x; x.a; x.b;这样的代码.
					struct Variable * v = t->vars, * v1;
					int cur = 0;
					while(v) {
						if(findMem(a->vars, v->name)) {
							ERROR(57);
						}
						v1 = v->next;
						v->next = a->vars;
						a->vars = v;
						struct List * l = newList();
						l->value = a->size + cur;
						l->next = a->posi;
						a->posi = l;
						if(t->type == 2) {
							cur += calcSize(v);
						}
						v = v1;
					}
					if(a->type == 2) {
						a->size += t->size;
					}else {
						a->size = max(a->size, t->size);
					}
				}
			}
//			top = top->prev;
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
				if(t->type != s_or_u - 302) {
					ERROR(58);
				}
				return t;
			}
		}
	}else {
		if(look.type == 302) {//char
			move();
			//printf("char type\n");
			return CHAR_TYPE;
		}else if(look.type == 303) {//int
			move();
			//printf("int type\n");
			return INT_TYPE;
		}else if(look.type == 301) {//void
			move();
			//printf("void type\n");
			return VOID_TYPE;
		}else {
			ERROR(59);
		}
	}

}

struct Variable * findVariable(char * name) {//在变量表中找名字, 找不到到上层符号表中找!
	struct SymbolList * s = top;
	while(s) {
		struct Variable * p = s->vars;
		while(p) {
			if(!strcmp(p->name, name)) {
				return p;
			}
			p = p->next;
		}
		s = s->prev;
	}
	return 0;
}

struct Function * findFunc(char * name) {//在函数表中找名字
	struct SymbolList * s = top;
	while(s) {
		struct Function * p = s->funcs;
		while(p) {
			if(!strcmp(p->name, name)) {
				return p;
			}
			p = p->next;
		}
		s = s->prev;
	}
	return 0;
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

struct Function * findTopFunc(char * name) {
	struct Function * p = top->funcs;
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

void printStringAssign(struct Function * env, struct Operand * v) {
	struct Operand * res = newOperand(newVariable(), 1, 0, 0);
	res->var->type = CHAR_TYPE;
	int len = 0;
	while(len == 0 || look.name[len - 1]) {
		if(!v->var->list || len < v->var->list->value) {
			struct Instruction * inst = newInstruction(ASSIGN_ADD, res, v, constInt(len));
			push(env, inst);
			printAssign(env, res, constChar(look.name[len]));
		}
		len++;
	}
	move();
}

void parseElementInitialization(struct Function * env, struct Operand * v, int flag, int first) {
	if(look.type == 505) {
		move();
		parseElementInitialization(env, v, flag, 1);
		if(look.type != 506) {
			match(503);
		}
		while(look.type != 506) {
			parseElementInitialization(env, v, 0, 0);
			if(look.type != 506) {
				match(503);
			}
		}
		move();
	}else {
		if(!flag) {
			struct Operand * res = parseAssignmentExpression(bucket);
			if(first && env == chief && (v->var->level && !(res->loadable || res->constant) || !v->var->level && !res->constant)) {
				ERROR(96);
			}
		}else {
			if(v->var->level && look.type == STR_CONSTANT) {
				int len = 0;
				while(look.name[len]) {
					len++;
				}
				printMalloc(env, constInt(sizeof(char) * (len + 1)));
				env->insts->a = v;
				printStringAssign(env, v);
			}else {
				struct Operand * res = parseAssignmentExpression(env);
				if(env == chief && (v->var->level && !(res->loadable || res->constant) || !v->var->level && !res->constant)) {
					ERROR(95);
				}
				printAssign(env, v, res);
			}
		}
	}
}

void parseInitialization(struct Function * env, struct Operand * v) {
	if(v->var->list) {
		int isCharArray = v->var->type == CHAR_TYPE && v->var->list && !v->var->list->next && !v->var->level;
		if(look.type == 505) {
			move();
			if(isCharArray && look.type == STR_CONSTANT) {
				printStringAssign(env, v);
			}else {
				int tot = 0;
				while(look.type == 505 || look.type == STR_CONSTANT && v->var->list->next && !v->var->list->next->next) {

					if(tot < v->var->list->value) {
						parseInitialization(env, printAccess(env, v, constInt(tot)));
					}else {
						parseElementInitialization(env, v, 0, tot == 0);
					}

					tot++;
					if(look.type == 506) {
						break;
					}else {
						match(503);//','
					}
				}
				tot *= v->var->list->mul / v->var->list->value;
				while(look.type != 506) {
					struct Instruction * inst = newInstruction(ASSIGN_ADD, newOperand(newVariable(), 1, 0, 0), v, constInt(tot * v->var->type->size));
					occupy(env, inst->a);			
					inst->a->var->type = v->var->type;
					inst->a->var->level = v->var->level;
					push(env, inst);
					parseElementInitialization(env, inst->a, tot < v->var->list->mul, tot == 0);
					tot++;
					if(look.type == 506) {
						break;
					}else {
						match(503);
					}
				}
			}
			match(506);
		}else if(look.type == STR_CONSTANT && isCharArray) {
			printStringAssign(env, v);
		}else {
			ERROR(93);
		}
	}else {
		parseElementInitialization(env, v, 1, 1);
	}
}

void parseDeclaractionOrFunctionDefinition(struct Function * env);

void parseStatement(int b, int a, struct Function * env) {//分析语句.
	//b: before, a:after
	//printf("STA %d\n", env);
	if(look.type == 505) {//'{'复合语句
		move();
		top = newSymbolList(top);
		while(look.type != 506) {//'}'
			if(look.type >= 301 && look.type <= 305) {
				parseDeclaractionOrFunctionDefinition(env);
			}else {
				//printf("CS %d\n", env);
				parseStatement(b, a, env);
				//printf("CS %d\n", env);
			}
		}
		move();
		top = top->prev;
	}else if(look.type == 306) { //if语句
		move();
		match(500);//'('
		int after = newLabel();//标记else之前的位置

		printIfFalseGoto(env, parseExpression(env), after);//不满足就跳!
		match(501);//')'
		//printf("ifStatement\n");
		parseStatement(b, a, env);//满足时执行的语句
		//printf("ifStatement\n");
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
			ERROR(71);//支持死循环才怪!
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
			ERROR(72);
		}
		move();
		printGoto(env, a);//跳到after处, 即for和while的结束位置
		match(502);//';'
	}else if(look.type == 310) {//continue
		if(b == -1) {
			ERROR(73);
		}
		move();
		printGoto(env, b);//跳到begin处, 即for的循环变量变更位置, while的循环控制位置.
		match(502);//';'
	}else if(look.type == 312) {//return!
		move();
		if(env->rtn->type != VOID_TYPE) {
			printReturn(env, parseExpression(env));
		}else {
			printVoidReturn(env); 
		}
		match(502);
	}else {//表达式语句.
		//printf("expSta %d\n", env);
		if(look.type == 502) {
			move();
			return;
		}
		parseExpression(env);
		//printf("staExp %d\n", env);
		match(502);//';'
		//printf("staExp %d\n", env);

	}
}

void parseFunctionBody(struct Function * env) {
	top = env->symbolList;
	struct Variable * p = env->argu, * p1;//复制参数为初始变量表
	env->argu = 0;
	while(p) {
		p1 = p->next;
		p->next = env->argu;
		env->argu = p;
		p = p1;
	}

	p = env->argu;
	while(p) {
		printGetArgu(env, directLvalue(p));//
		occupy(env, directLvalue(p));
		//printf("get_argument %s %s %d\n", env->name, p->name, env->insts->a->var->level);
		p = p->next;
	}

	p = env->argu;
	env->argu = 0;
	while(p) {
		p1 = p->next;
		p->next = env->argu;
		env->argu = p;
		p = p1;
	}	
	move();
	while(look.type != 506) {//'}'
		if(look.type >= 301 && look.type <= 305) {//是void char int struct union中的一个
			parseDeclaractionOrFunctionDefinition(env);
		}else {
			//printf("FB %d\n", env);
			parseStatement(-1, -1, env);//否则.
			//printf("FB %d\n", env);
		}
	}
	move();
	top = top->prev;
}

struct Function * parseArguments(struct Function * env) {
	move();//'('
	struct Function * f = newFunction();
	f->symbolList = newSymbolList(top);
	top = f->symbolList;
	for(; look.type != 501;) { //')'
		struct Type * p = parseTypeSpecifier();
		struct Variable * v = parsePlainDeclarator(1);//允许匿名
		if(v->level == 0 && v->type == VOID_TYPE || v->name[0] != 0 && findTopVariable(v->name)) {
			ERROR(74);
		}
		if(look.type == 507) {//'['
			v->list = parseArray();
		}
		v->type = p;
		v->next = top->vars;
		top->vars = v;//反向参数表!!!!!!!!!!!!!!!!!!!!!!!!!
		if(look.type == 503) {//','
			move();
		}
	}
	move();//')'
	struct Variable * tmp, * tmp1;
	tmp = top->vars;
	top->vars = 0;
	while(tmp) {
		tmp1 = tmp->next;
		tmp->next = top->vars;
		top->vars = tmp;
		tmp = tmp1;
	}
	f->argu = top->vars;//符号表包含f的参数!
	top = top->prev;//!!
	return f;
}

void parseDeclaractionOrFunctionDefinition(struct Function * env) {
	int i = 0;
	//printf("Func Def");
	struct Type * t = parseTypeSpecifier();//分析类型
	//	if(t->size == -1) {
	//		match(502);//';'
	//		return;
	//	}
	//printf("parse FUNCTION\n");
	for(;look.type != 502;) {//';'
		i++;
		//printf("Func Def");
		struct Variable * v = parsePlainDeclarator(0);//分析了指针的层数, 不允许匿名
		if(t->size == -1 && !v->level) {
			ERROR(92);
		}
		//printf("Func Def3\n");
		//printf("parse FUNCTION\n");
		v->type = t;
		if(look.type == 500) {//'('说明是函数
			//printf("parse FUNCTION\n");
			if(findTopVariable(v->name)) {//函数不能和变量重名
				ERROR(150000);
			}
			//printf("parse FUNCTION\n");
			//printf("Func Def");
			struct Function * f = parseArguments(env);//分析函数的参数
			f->name = v->name;//函数的名字
			//printf("Func Def %s\n", f->name);
			f->rtn = v;//函数的返回值类型
			struct Function * p = findTopFunc(f->name);//寻找当前层函数表, 有没有一样的函数

			//printf("p = %d\n", p);
			if(p && !compFunc(p, f)) {//不能名字一样定义却不同
				ERROR(76);
			}
			if(!p) {//没有重名的函数
				f->next = top->funcs;
				top->funcs = f;
				funcList = newFuncList(f, funcList);
			}else {
				p->argu = f->argu;
				p->symbolList = f->symbolList;
				f = p;
			}
			if(look.type == 505) {//'{'说明是函数定义
				//printf("REAL DEF\n");
				if(f->insts || i != 1) {//不能重复定义函数, 函数定义必须独占type-specifier.
					ERROR(77);
				}
				printNOP(f);
				//printf("REAL DEF\n");
				parseFunctionBody(f);//分析函数过程.
				//printf("REAL DEF\n");
				return;//函数定义必须独占type-specifier
			}else {
				//重复声明函数, 什么也不做.
			}
		}else {//不是函数
			if(findTopVariable(v->name) || findTopFunc(v->name)) {
				ERROR(78);
			}
			v->next = top->vars;
			top->vars = v;
			if(look.type == 507) {//'['说明是数组类型
				v->list = parseArray();//分析数组的维度
			}
			if(v->type == VOID_TYPE && v->level == 0) {//不能定义void类型的变量
				ERROR(79);
			}
			if(v->list || isStruct(v)) {
				printDeclPointer(env, directLvalue(v));
				printMalloc(env, constInt(calcSize(v)));
				env->insts->a = directLvalue(v);
			}else if(v->level) {
				printDeclPointer(env, directLvalue(v));
			}else if(v->type == CHAR_TYPE) {
				printDeclChar(env, directLvalue(v));
			}else if(v->type == INT_TYPE) {
				printDeclInt(env, directLvalue(v));
			}
			occupy(env, directLvalue(v));
			//printf("!!\n");
			/*			if(env == chief) {//说明是全局变量

						printFillZero(env, directLvalue(v));//将v所占全部内存清0
			//printf("!!2\n");

			}*/
			if(look.type == 504) {//'='说明有初始化
				if(env == chief && (v->list || isStruct(v))) {
					printFillZero(env, directLvalue(v));
				}
				move();//'='
				parseInitialization(env, directLvalue(v));//分析变量v的初始化
			}else if(env == chief) {
				printFillZero(env, directLvalue(v));
			}
		}
		if(look.type != 502) {//','说明还有后续声明
			match(503);
		}
	}
	move();
}	

char CHIEF[6] = "chief";

void parseProgram() {
	TMP.value = TMP.mul = 1;
	chief = newFunction();//主过程
	funcList = newFuncList(chief, 0);
	chief->name = CHIEF;
	chief->symbolList = newSymbolList(top);
	top = chief->symbolList;
	bucket = newFunction();//垃圾桶
	printNOP(chief);//新建一个空操作.
	printNOP(bucket);
	int begin = newLabel(), end = newLabel();//主程序的开始和结束标签
	printLabel(chief, begin);
	look1 = nextToken();
	move();
	while(look.type != NO_TOKEN) {
		parseDeclaractionOrFunctionDefinition(chief);
	}
	printLabel(chief, end);
	//chief->insts即为主程序的指令序列(倒序)
}

struct Instruction ** jumpTo;

struct List * arguStack;

void reverse(struct Function * f) {//反向指令表, fetch label
	struct Instruction * tmp = f->insts, * tmp1;
	f->insts = 0;
	while(tmp) {
		tmp1 = tmp->next;
		tmp->next = f->insts;
		f->insts = tmp;
		tmp = tmp1;

	}
	tmp = f->insts;
	while(tmp) {
		if(tmp->type == LABEL) {
			jumpTo[tmp->n] = tmp;
		}
		tmp = tmp->next;
	}
}

struct Trie {
	struct Trie * s[2];
	int value;
} * root;

struct Trie * newTrie() {
	struct Trie * res = (struct Trie *)malloc(sizeof(struct Trie));
	res->s[0] = 0;
	res->s[1] = 0;
	res->value = 0;
	return res;
}

struct Trie * accessOperand(int x) {
	struct Trie * p = root;
	int d = x < 0;
	if(d) {
		x = -x;
	}
	if(p->s[d] == 0) {
		p->s[d] = newTrie();
	}
	p = p->s[d];
	while(x) {
		d = x & 1;
		if(p->s[d] == 0) {
			p->s[d] = newTrie();
		}
		p = p->s[d];
		x /= 2;
	}
	return p;
}

struct Instruction * inst;

int halt, result;

int run(struct Function * f) {
	struct Instruction * inst = f->insts;
	struct List * tmp = f->occupy;
	struct List * bak = 0;
	if(f != chief) {
		while(tmp) {
			struct List * new = newList();
			new->value = accessOperand(tmp->value)->value;
			new->next = bak;
			bak = new;
			tmp = tmp->next;
		}
	}
	int res;
	//printf("%s\n", f->name);
	while(inst) {
		int noJump = 1;
		struct Trie * a, * b, * c;
		//if(strcmp(f->name, "isLetter") && strcmp(f->name, "isDigit") && strcmp(f->name, "nextToken") && strcmp(f->name, "chief") ) {
		//if(strcmp(f->name, "__printf__")) {		
		//	printIntermediateCode(inst);
		//}
		//}
		if(inst->a) {
			if(inst->a->constant) {
				a = accessOperand(-3);
				a->value = inst->a->value;
			}else {
				a = accessOperand(inst->a->var->index);
			}
		}
		if(inst->b) {
			if(inst->b->constant) {
				b = accessOperand(-1);
				b->value = inst->b->value;
			}else {
				b = accessOperand(inst->b->var->index);
			}
		}
		if(inst->c) {
			if(inst->c->constant) {
				c = accessOperand(-2);
				c->value = inst->c->value;
			}else {
				c = accessOperand(inst->c->var->index);
			}

		}
		int t = inst->type;
		if(t == GET_ARGU) {
			if(arguStack) {
				a->value = arguStack->value;
				arguStack = arguStack->prev;
			}
		}else if(t == DECL_POINTER) {
			//DO NOTHING
		}else if(t == DECL_CHAR) {
			//DO NOTHING
		}else if(t == DECL_INT) {
			//DO NOTHING
		}else if(t == MALLOC) {
			a->value = (int)malloc(b->value);
			//printf("malloc %d %d\n", a->value, b->value);
		}else if(t == GETCHAR) {
			a->value = getchar();
			//			printf("%d\n", a->value);
		}else if(t == PUTCHAR) {
			putchar(a->value);
		}else if(t == NOP) {
			//DO NOTHING
		}else if(t == ASSIGN_ADD) {
			a->value = b->value + c->value;
			//printf("PLUS %d %d %d\n", a->value, b->value, c->value);
		}else if(t == GOTO) {
			inst = jumpTo[inst->n];
			noJump = 0;
		}else if(t == LABEL) {
			//DO NOTHING
		}else if(t == IF_GOTO) {
			if(a->value) {
				inst = jumpTo[inst->n];
				noJump = 0;
			}
		}else if(t == IF_FALSE_GOTO) {
			if(!a->value) {
				inst = jumpTo[inst->n];
				noJump = 0;
			}
		}else if(t == ASSIGN_LOGICAL_NOT) {
			a->value = !b->value;
		}else if(t == ASSIGN_NOT) {
			a->value = ~b->value;
		}else if(t == ASSIGN_NEGATE) {
			a->value = -b->value;
		}else if(t == ASSIGN || t == ASSIGN_CHAR || t == ASSIGN_ADDRESS || t == INT_TO_CHAR || t == CHAR_TO_INT) {
			a->value = b->value;
			//printf("ADDRESS_ASSIGN %d %d\n", a->value, b->value);
		}else if(t == ASSIGN_INCLUSIVE_OR) {
			a->value = b->value | c->value;
		}else if(t == ASSIGN_EXCLUSIVE_OR) {
			a->value = b->value ^ c->value;
		}else if(t == ASSIGN_AND) {
			a->value = b->value & c->value;
		}else if(t == ASSIGN_SHR) {
			a->value = b->value >> c->value;
		}else if(t == ASSIGN_SHL) {
			a->value = b->value << c->value;
		}else if(t == ASSIGN_SUB) {
			a->value = b->value - c->value;
		}else if(t == CALL) {
			a->value = run(inst->f);
			if(halt) {
				return 0;
			}
		}else if(t == ASSIGN_MOD) {
			if(c->value == 0) {
				printf("MODULO BY ZERO\n");
				ERROR(88);
			}
			a->value = b->value % c->value;
		}else if(t == ASSIGN_DIV) {
			if(c->value == 0) {
				printf("DIVIDE BY ZERO\n");
				ERROR(89);
			}
			a->value = b->value / c->value;
		}else if(t == ASSIGN_MUL) {
			a->value = b->value * c->value;
		}else if(t == ASSIGN_NOT_EQUAL_TO) {
			a->value = b->value != c->value;
		}else if(t == ASSIGN_EQUAL_TO) {
			a->value = b->value == c->value;
		}else if(t == ASSIGN_GREATER_THAN_OR_EQUAL_TO) {
			a->value = b->value >= c->value;
		}else if(t == ASSIGN_LESS_THAN_OR_EQUAL_TO) {
			a->value = b->value <= c->value;
		}else if(t == ASSIGN_GREATER_THAN) {
			//printf("%d %d\n", b->value, c->value);
			a->value = b->value > c->value;
		}else if(t == ASSIGN_LESS_THAN) {
			a->value = b->value < c->value;
		}else if(t == ASSIGN_LOGIC_OR) {
			a->value = b->value || c->value;
		}else if(t == ASSIGN_LOGIC_AND) {
			a->value = b->value && c->value;
		}else if(t == ASSIGN_DEREF || t == ASSIGN_DEREF_ADDRESS) {
			a->value = *(int *)b->value;
		}else if(t == ASSIGN_DEREF_CHAR) {
			a->value = *(char *)b->value;
		}else if(t == DEREF_ASSIGN_ADDRESS || t == DEREF_ASSIGN) {
			*(int *)a->value = b->value;
		}else if(t == DEREF_ASSIGN_CHAR) {
			*(char *)a->value = b->value;
		}else if(t == RETURN) {
			res = a->value;
			break;
		}else if(t == ASSIGN_ADDRESS_OF) {
			a->value = (int)&b->value;
		}else if(t == ARGU) {
			if(arguStack) {
				arguStack->next = newList();
				arguStack->next->value = a->value;
				arguStack->next->prev = arguStack;
				arguStack = arguStack->next;
			}else {
				arguStack = newList();
				arguStack->value = a->value;
			}
		}else if(t == EXIT) {
			halt = 1;
			result = a->value;
			break;
		}else if(t == VOID_RETURN) {
			break;
		}else if(t == PUTINT) {
			printf("%d", a->value);
		}else {
			printf("ffffffffffuuuuuuuuuuuuuucccccccccccccckkkkkkkkkkkkkk\n");
		}
		if(halt) {
			return 0;
		}
		if(noJump) {
			inst = inst->next;
		}
	}
	if(f != chief) {
		struct List * tmp1 = 0, * tmp2;
		while(bak) {
			tmp2 = bak->next;
			bak->next = tmp1;
			tmp1 = bak;
			bak = tmp2;
		}
		bak = tmp1;
		tmp = f->occupy;
		while(tmp) {
			accessOperand(tmp->value)->value = bak->value;
			bak = bak->next;
			tmp = tmp->next;
		}
	}
	return res;
}

int stopAtLexer = 0, stopAt3AddrCode = 1, interpreter = 1;

int main() {
	//	freopen("gadget.c", "r", stdin);
	examine = 1;
	initBasicTypeName();
	initModVariables();
	program = (char*)malloc(sizeof(char) * 10);
	int length = 0;
	int capacity = 10;
	char c;	
	int i = 0;
	for(; __stdio__printf__[i]; i++) {//标准库printf
		push_back(&program, &length, &capacity, __stdio__printf__[i]);
	}
	while(-1 != (c = getchar())) {
		//printf("%c\n", c);
		push_back(&program, &length, &capacity, c);
	}
	for(i = 0; i < 5; i++) {
		push_back(&program, &length, &capacity, 0);
	}
	int len = 0;
	for(i = 0; program[i]; i++) {
		if(program[i] != '\r') {
			program[len++] = program[i];
		}
	}
	program[len] = 0;
	len = 0;
	for(i = 0; program[i]; i++) {
		if(program[i] == '\\\
') {
			int j = 0;
			while(program[i + j + 1] == ' ' || program[i + j + 1] == '\t') {
				j++;
			}
			if(program[i + j + 1] == '\n') {
				i = i + j + 1;
				continue;
			}
		}
		program[len++] = program[i];
	}
	program[len] = 0;
	//printf("%s", program);
	beginOfLine = 1;
	bp = program;
	if(stopAtLexer) {
		printTokens();
	}else {
		parseProgram();
		//printf("parseProgramComplete\n");
		jumpTo = (struct Instruction **)malloc(sizeof(struct Instruction *) * nLabel);
		struct FuncList * p = funcList;
		while(p) {
			reverse(p->f);
			p = p->next;
		}
		if(stopAt3AddrCode) {
			struct FuncList * p = funcList;
			while(p) {
				printf("\nFUNCTION %d %s: \n", p->f, p->f->name);
				/*{
				  p = p->next;
				  continue;
				  }*/
				struct Instruction * itr = p->f->insts;
				while(itr) {
					printIntermediateCode(itr);
					itr = itr->next;
				}
				p = p->next;
			}
		}
		if(interpreter) {
			//printf("\ninterpreting...\n");
			arguStack = 0;
			halt = 0;
			struct FuncList * p = funcList;
			p = funcList;	
			root = newTrie();	
			while(p) {
				if(!strcmp(p->f->name, "chief")) {
					run(p->f);
					break;
				}
				p = p->next;
			}
			p = funcList;
			while(p) {
				if(!strcmp(p->f->name, "main")) {
					run(p->f);
					break;
				}
				p = p->next;
			}
		}
	}
	//fclose(stdin);
	return 0;
}
//totERROR = 1 ~ 97
