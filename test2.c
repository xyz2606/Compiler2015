#include<stdio.h>
int * a, * b;
void * va, * vb;
int ia, ib;
int main() {
	va < a;
	a < b;
	a > b;
	a <= b;
	a >= b;
	va <= vb;
	va >= vb;
	va < vb;
	va > vb;
	va + ia;
	va - ib;
	va += ia;
	va -= ia;
	a + ia;
	a - ib;
	a += ia;
	a -= ib;
	va - vb;
	a - b;
	a -= b;
//	va - a;ERROR
//	ia - a;ERROR
	ia - 'a';
	va -= vb;
	!va;
	!a;
	int x;
	a = &x;
	va = a;
	printf("%d\n", (int)va);
	va ++;
	printf("%d\n", (int)va);
}
