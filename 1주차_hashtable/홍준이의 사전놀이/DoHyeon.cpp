#include <stdio.h>
#include <iostream>
using namespace std;
#define PN 19
#define HS 1000000

int table[1000000][10] = { 0, };
int H_idx = 0;
char H[1000000][15] = { 0, };
int Count[1000000] = { 0, };

unsigned int get_key(char *buf, int buffer_size) {
	unsigned int key = 0, p = 1;
	for (int i = 0; i < buffer_size; i++) {
		key += (buf[i] * p);
		p *= PN;
	}
	return key % HS;
}

void init() {
	H_idx = 0;
	for (int i = 0; i < 1000000; i++) {
		table[i][0] = 0;
		Count[i] = 0;
	}
	for (int i = 0; i < 1000000; i++) {
		for (int j = 0; j < 15; j++) {
			H[i][j] = 0;
		}
	}
}
void add(char* buf, int size) {
	unsigned int key = get_key(buf, size);

	int key_count = table[key][0];
	table[key][++key_count] = H_idx;
	table[key][0] = key_count;
	int i;
	for (i = 0; i < size; i++) {
		H[H_idx][i] = buf[i];
	}
	H[H_idx][i] = 0;
	Count[H_idx]++;
	H_idx++;
}
int cmp(char *str1, char *str2) {
	int i = 0, j = 0;

	while (str1[i] != 0)
	{
		if (str1[i++] != str2[j++])
		{
			i--; j--;
			break;
		}
	}

	return str1[i] - str2[j];
}
int find(char *buf, int size) {
	unsigned int key = get_key(buf, size);
	int idx_count = table[key][0];
	for (int i = 1; i <= idx_count; i++) {
		if (cmp(buf, H[table[key][i]]) == 0) {
			return table[key][i];
		}
	}
	return -1;
}
void copy(char* str1, char* str2, int len) {
	int i;
	for (i = 0; i < len; i++) {
		str1[i] = str2[i];
	}
	str1[i] = 0;
}
void insert(int buffer_size, char *buf) {
	for (int k = 1; k <= buffer_size; k++) {
		char str[20] = { 0, };
		copy(str, buf, k);
		int index = find(str, k);
		if (index == -1) {
			add(str, k);
		}
		else {
			Count[index]++;
		}
	}
}

int query(int buffer_size, char *buf) {
	int tar = find(buf, buffer_size);
	if (tar != -1) {
		return Count[tar];
	}
	return 0;
}
