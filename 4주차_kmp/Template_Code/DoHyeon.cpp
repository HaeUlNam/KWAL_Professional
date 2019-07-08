#include <iostream>
#include <string>
#include <cstdio>
int pi[5005] = { 0, };
char arr[5005] = { 0, };
void init() {
	for (int i = 0; i < 5005; i++) {
		pi[i] = 0;
		arr[i] = 0;
	}
}

void getPi(char *s) {
	int len = 0, j = 0;
	while (s[len] != 0) {
		len++;
	}
	for (int i = 1; i < len; i++) {
		while (j > 0 && s[i] != s[j]) {
			j = pi[j - 1];
		}
		if (s[i] == s[j]) {
			pi[i] = ++j;
		}
	}
}
int main(void)
{
	init();
	int max = 0, len = 0, res = 0;
	scanf("%s", arr);
	while (arr[len] != 0) {
		len++;
	}

	for (int i = 0; i < len; i++) {
		getPi(&arr[i]);

		for (int i = 0; i < 5005; i++) {
			if (pi[i] > max) {
				max = pi[i];
			}
			pi[i] = 0;
		}
		res = (res < max) ? max : res;
	}
	printf("%d\n", res);
}
