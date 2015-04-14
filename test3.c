#include<stdio.h>
void f() {
}
void g(int a[8]) {
}
struct A {
} a;
int main() {
	int a[2][2] = {{0, 1}, {2, 3}};
	*a + 1;
	printf("%d %d\n", a, a + 1);
	int * b;
	(char )b;
	void * c;
//	*c = 'a';ERROR
	*c;
	(void)f;
	c = 10;
	printf("%d\n", sizeof(c[0]));
	malloc(c);
	g(c);
	char ch;
	ch++;
	printf("%d\n", sizeof(c++) * sizeof(++c));
}
