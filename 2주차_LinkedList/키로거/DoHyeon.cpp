#include <stdio.h>
#include <algorithm>
#include <string.h>

using namespace std;
#define NODE_SIZE 3000000

struct NODE {				
	char data;
	int prev;
	int next;
};
char input[NODE_SIZE];
			
int HEAD = NODE_SIZE - 1, TAIL = NODE_SIZE;
int pos;
NODE node[NODE_SIZE + 1];
	
void init(){
	node[HEAD].next = TAIL;
	node[HEAD].prev = HEAD;
	node[TAIL].prev = HEAD;
	node[TAIL].next = TAIL;
	pos = 0;
}

void push_back(int data, int cursur) {
	int prev = node[cursur].prev, next = cursur;
	node[pos].data = data;
	node[pos].prev = prev;
	node[prev].next = pos;
	node[pos].next = next;
	node[next].prev = pos;
	pos++;
}

void pop_back(int cursur) {
	int tar = node[cursur].prev;
	int next = node[tar].next, prev = node[tar].prev;

	node[prev].next = next;
	node[next].prev = prev;
}

void print() {
	int tar = node[HEAD].next;
	while (tar != TAIL) {
		printf("%c", node[tar].data);
		tar = node[tar].next;
	}
	printf("\n");
}

int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {

		scanf("%s", input);
		init();

		int len = strlen(input);
		int cursur = TAIL;
		for (int l = 0; l < len; l++) {
			if (input[l] == '<') {
				if (node[cursur].prev != HEAD)
				{
					cursur = node[cursur].prev;
				}
			}
			else if (input[l] == '>') {
				cursur = node[cursur].next;
			}
			else if (input[l] == '-') {
				pop_back(cursur);
			}
			else {
				push_back(input[l], cursur);
			}
		}
		print();
	}
	return 0;
}
