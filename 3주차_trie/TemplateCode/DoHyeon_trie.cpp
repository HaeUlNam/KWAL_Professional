#include <stdio.h>
#include <stdlib.h>
#include <string>

typedef struct node {
	node *child[26];
	int end;
};
node* newnode() {
	node* root = (node*)malloc(sizeof(node));
	for (int i = 0; i < 26; i++) {
		root->child[i] = 0;
	}
	root->end = 0;
	return root;
}
void showall(node *now, char* str, int depth) {
	if (now->end == 1) {
		printf("%s\n", str);
	}
	for (int i = 0; i < 26; i++) {
		if (now->child[i] != 0) {
			str[depth] = i + 'a';
			str[depth + 1] = 0;
			showall(now->child[i], str, depth + 1);
		}
	}
}

void insert(node* root, char* arr) {
	int len = strlen(arr);
	node* ptr = root;

	for (int i = 0; i < len; i++) {
		if (ptr->child[arr[i] - 'a'] == 0) {
			ptr->child[arr[i] - 'a'] = newnode();
		}
		ptr = ptr->child[arr[i] - 'a'];
	}
	ptr->end = 1;
}

int search(node* root, const char* str) {
	int len = strlen(str);
	for (int i = 0; i < len; i++) {
		if (root->child[str[i] - 'a'] == 0) {
			return 0;
		}
		root = root->child[str[i] - 'a'];
	}
	return root->end;
}

int del(node* now, char* arr, int i) {
	if (i == strlen(arr)) {
		for (int i = 0; i < 26; i++) {
			if (now->child[i] != 0)
				return 0;
		}
		return 1;
	}

	if (now->child[arr[i] - 'a'] != 0) {
		if (del(now->child[arr[i] - 'a'], arr, i + 1) == 1) {
			free(now->child[arr[i] - 'a']);
			now->child[arr[i] - 'a'] = 0;

			for (int i = 0; i < 26; i++) {
				if (now->child[i] != 0)
					return 0;
			}
			return 1;
		}

	}
	return 0;
}
void recommend(node *root, char *str) {
	int len = strlen(str);
	node* now = root;
	for (int i = 0; i < len; i++) {
		if (now->child[str[i] - 'a'] == 0) {
			return;
		}
		now = now->child[str[i] - 'a'];
	}
	showall(now, str, len);
}
int main() {
	char my[][8] = { "below", "blue", "ban", "bzak", "bzu", "a", "im", "i" };

	node* root = newnode();

	for (int i = 0; i < 8; i++) {
		insert(root, my[i]);
	}
	char tmp[20];
	printf("show all word\n");
	showall(root, tmp, 0);

	printf("\ndo i have?...\n");
	printf("%s : %s\n", "bz", search(root, "bz") ? "YES" : "NO");
	printf("%s : %s\n", "blue", search(root, "blue") ? "YES" : "NO");
	printf("%s : %s\n", "i", search(root, "i") ? "YES" : "NO");
}