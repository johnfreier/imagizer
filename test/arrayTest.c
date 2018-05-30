#include <stdio.h>
#include <stdlib.h>

char * createArray() {
	int xsize = 10;
	char test[xsize];
	test[0] = 'j';
	test[1] = 'j';
	test[2] = 'o';

	printf("CHAR:%c\n", test[1]);

	char *p_test;
	p_test = test;

	return p_test;
}

void checkVariables(int a) {
	a = 2;
}

// Pointer * are used for both decleration and to get the value.
// (* contents of) (% location of);
void checkVariables2(int *a) {
	*a = 2;
};

int main(int argc, char **argv) {

	char *pTest = createArray();

	printf("Array Test: %c\n", pTest[1]);
	printf("The end.\n");

	int a = 1;
	checkVariables(a);
	printf("Result: %i\n", a);

	int *p_a = &a;
	checkVariables2(p_a);
	printf("Result: %i\n", a);

	return 0;
}