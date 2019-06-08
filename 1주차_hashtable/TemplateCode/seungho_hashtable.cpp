/*
�ؽ� �Լ� ���� �� STL �ʰ� ��
��ó: https://na982.tistory.com/103?category=92742
*/

#include <stdio.h>
#include <algorithm>
#include <map>
#include "Windows.h"

using namespace std;

/////////////////////
//�׽�Ʈ�� ��������//
/////////////////////
//�Է� ������ ���� �迭
char input[30000][100];		//������ ����: 3����
//�ؽ� ��� ����
const int REMOVE = 1;
const int FIND = 2;
//�ؽ� ��� �迭
int cmd[30000][2];
//�ؽ� ��� �迭
int my_find[30000], stl_find[30000];

/////////////////////
//STL �ؽ� ��������//
/////////////////////
map<char*, int> stl_hash;

//////////////////////
//���� �ؽ� ��������//
//////////////////////
const int PN = 19;
const int HASH_SIZE = 10000;	//�ؽ� ������: ������ ������ 3���� 1
int name_size;
char name[30000][100];
int table[HASH_SIZE][30];	//�ؽ� ���̺� ũ��: �ǵ����;��� 5�� -> 15�� �̻�([�ؽû�����][15�̻�]

//////////////////////
//���� �ؽ� ����Լ�//
//////////////////////
//key ���� !!!����ȭ1����!!!
unsigned int get_key(char _name[]) {	//unsigned int�� �����÷ο�� ���� ����� ����ȭ ����
							//�����÷ο� �Ǵ��� ���� �����Ϳ� ���� key�� ��µǸ� �������
	unsigned int key = 0, p = 1;
	for (int i = 0; _name[i] != 0; i++) {
		key += (_name[i] * p);
		p *= PN;
	}

	return (key % HASH_SIZE);		//���̺� �ε��� ���� ���� �����ؼ� key ����
							//��ü �����Ͱ� ��ü key�� �յ��ϰ� ������ ���� ���� ������ ������
							//-> ������ ���� ���� ���� Ű�� ���� ū Ű�� ���̰� 3~5�� �̳��� ������
}

//������ �� !!!����ȭ2����!!!
int my_strcmp(char a[], char b[]) {
	int i = 0;
	while (a[i]) {
		if (a[i] != b[i]) {
			break;
		}
		i++;
	}

	return (a[i] - b[i]);
}

//������ �˻�
int contain(char _name[]) {			//�ؽÿ� �����Ͱ� ������ �ε����� ��ȯ
	unsigned int key = get_key(_name);
	int h_size = table[key][0];
	for (int i = 0; i <= h_size; i++) {
		int n_pos = table[key][i];
		if (my_strcmp(name[n_pos], _name) == 0) {
			return n_pos;
		}
	}

	return -1;
}

//������ �߰�
void add(char _name[]) {
	int len;
	for (len = 0; _name[len] != 0; len++) {
		name[name_size][len] = _name[len];
	}

	name[name_size][len] = 0;

	unsigned int key = get_key(_name);
	int& h_size = table[key][0];

	table[key][++h_size] = name_size;
	name_size++;
}

//������ ����
bool remove(char _name[]) {
	unsigned int key = get_key(_name);
	int& h_size = table[key][0];
	for (int i = 1; i <= h_size; i++) {
		int n_pos = table[key][i];
		if (my_strcmp(name[n_pos], _name) == 0) {
			for (int j = i + 1; j <= h_size; j++) {
				table[key][j - 1] = table[key][j];
			}
			h_size--;
			return true;
		}
	}

	return false;
}

/////////////////
//�׽�Ʈ�� �Լ�//
/////////////////
int make_int(int min, int max) {		//���� ���� ������ ���� ��ȯ
	return (rand() % (max - min)) + min;
}
int make_char() {					//������ �ҹ��� Ȥ�� �빮�ڸ� ��ȯ
	int val = rand() % 52;
	if (val < 26) {
		return static_cast<char>('a' + val);
	}
	return static_cast<char>('A' + val - 26);
}


///////////////////////////
/////////���� �Լ�/////////
///////////////////////////
int main() {
	//�׽�Ʈ ������ ����
	for (int i = 0; i < 30000; i++) {
		int len = make_int(10, 100);
		//������ �Է�
		for (int j = 0; j < len; j++) {
			input[i][j] = make_char();
		}
		input[i][len] = 0;
		//��ɾ� �Է�
		if (i > 1000) {
			cmd[i][0] = rand() % 3;
			cmd[i][1] = rand() % i;
		}
	}

	//�ؽ� �Լ� �׽�Ʈ
	int my_hash_begin = GetTickCount();
	for (int i = 0; i < 30000; i++) {
		if (contain(input[i]) == -1) {
			add(input[i]);
		}
		if (cmd[i][0] == REMOVE) {
			if (contain(input[cmd[i][1]]) != -1) {
				remove(input[cmd[i][1]]);
			}
		}
		if (cmd[i][0] == FIND) {
			my_find[i] = contain(input[cmd[i][1]]);
		}
	}
	int my_hash_end = GetTickCount();

	//STL �ؽ� �Լ� �׽�Ʈ
	int stl_hash_begin = GetTickCount();
	for (int i = 0; i < 30000; i++) {
		stl_hash[input[i]] = i;

		if (cmd[i][0] == REMOVE) {
			stl_hash.erase(input[cmd[i][1]]);
		}
		if (cmd[i][0] == FIND) {
			map<char*, int>::iterator iter = stl_hash.find(input[cmd[i][1]]);
			stl_find[i] = -1;
			if (iter != stl_hash.end()) {
				stl_find[i] = iter->second;
			}
		}
	}
	int stl_hash_end = GetTickCount();

	//����� ��
	int my_hash_size = 0;
	for (int i = 0; i < HASH_SIZE; i++) {
		my_hash_size += table[i][0];
	}

	if (my_hash_size != stl_hash.size()) {
		printf("�ؽ� ������ ����ġ\n");
	}
	for (int i = 0; i < 30000; i++) {
		if (my_find[i] != stl_find[i]) {
			printf("�ؽ� �˻� �Լ� ����\n");
		}
	}

	//ó���ð� ��
	printf("���� �ؽ� �ð� : %d\n", my_hash_end - my_hash_begin);
	printf("STL �ؽ� �ð� : %d\n", stl_hash_end - stl_hash_begin);

	return 0;
}