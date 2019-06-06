#include<stdio.h>

#define PN 23
#define HASH_SIZE 1000


char input[1000][100];
int index_table[HASH_SIZE][50];
int hash_size = 0;
char hash_table[1000][100];

int get_key(char *str) {
	int key = 0, p = 1;

	for (int i = 0; str[i] != 0; ++i) {
		key += (str[i] * p);
		p *= PN;
	}

	return (key % HASH_SIZE);
}

int str_cmp(char* str1, char* str2) {            //데이터 비교 함수
	int i = 0, j = 0;
	while (str1[i] != 0) {
		if (str1[i++] != str2[j++]) {
			i--; 
			j--;
			break;
		}
	}
	return str1[i] - str2[j];
}
int is_exit(char *str) {                //hash table 데이터가 존재하는지 확인하는 함수
	int key = get_key(str);
	int size = index_table[key][0];
	for (int i = 1; i <= size; ++i) {
		int index = index_table[key][i];
		if (str_cmp(hash_table[index], str) == 0) {
			return 1;
		}
	}
	return 0;
}
int insert(char* str) {             //hash table에 데이터를 추가하는 함수
	int i = 0;
	for (i = 0; str[i] != 0; i++) {
		hash_table[hash_size][i] = str[i];
	}
	hash_table[hash_size][i] = 0;

	int key = get_key(str);
	int size = index_table[key][0];
	index_table[key][++size] = ++hash_size;
	index_table[key][0] = size;

	return 0;
}

int del(char *str) {          //hash table에서 데이터를 삭제하는 함수
	if (is_exit(str) == 0) {
		return -1;
	}
	int key = get_key(str);
	int size = index_table[key][0];
	for (int i = 1; i <= size; ++i) {
		int index = index_table[key][i];
		if (str_cmp(hash_table[index], str) == 0) {
			for (int j = i + 1; j <= size; j++) {
				index_table[key][j-1] = index_table[key][j];
			}
			index_table[key][0] = --size;
			return 0;
		}
	}
}