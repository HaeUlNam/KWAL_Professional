/*
해시 함수 구현 및 STL 맵과 비교
출처: https://na982.tistory.com/103?category=92742
*/

#include <stdio.h>
#include <algorithm>
#include <map>
#include "Windows.h"

using namespace std;

/////////////////////
//테스트용 전역변수//
/////////////////////
//입력 데이터 저장 배열
char input[30000][100];		//데이터 개수: 3만개
//해시 명령 종류
const int REMOVE = 1;
const int FIND = 2;
//해시 명령 배열
int cmd[30000][2];
//해시 결과 배열
int my_find[30000], stl_find[30000];

/////////////////////
//STL 해시 전역변수//
/////////////////////
map<char*, int> stl_hash;

//////////////////////
//수제 해시 전역변수//
//////////////////////
const int PN = 19;
const int HASH_SIZE = 10000;	//해시 사이즈: 데이터 개수의 3분의 1
int name_size;
char name[30000][100];
int table[HASH_SIZE][30];	//해시 테이블 크기: 실데이터양의 5배 -> 15만 이상([해시사이즈][15이상]

//////////////////////
//수제 해시 기능함수//
//////////////////////
//key 생성 !!!최적화1순위!!!
unsigned int get_key(char _name[]) {	//unsigned int로 오버플로우로 인한 결과값 음수화 방지
							//오버플로우 되더라도 같은 데이터에 같은 key만 출력되면 상관없음
	unsigned int key = 0, p = 1;
	for (int i = 0; _name[i] != 0; i++) {
		key += (_name[i] * p);
		p *= PN;
	}

	return (key % HASH_SIZE);		//테이블 인덱스 범위 내로 한정해서 key 생성
							//전체 데이터가 전체 key에 균등하게 분포될 수록 좋은 성능을 보여줌
							//-> 데이터 수가 가장 적은 키와 가장 큰 키의 차이가 3~5배 이내면 무난함
}

//데이터 비교 !!!최적화2순위!!!
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

//데이터 검색
int contain(char _name[]) {			//해시에 데이터가 있으면 인덱스를 반환
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

//데이터 추가
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

//데이터 삭제
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
//테스트용 함수//
/////////////////
int make_int(int min, int max) {		//범위 내의 임의의 수를 반환
	return (rand() % (max - min)) + min;
}
int make_char() {					//임의의 소문자 혹은 대문자를 반환
	int val = rand() % 52;
	if (val < 26) {
		return static_cast<char>('a' + val);
	}
	return static_cast<char>('A' + val - 26);
}


///////////////////////////
/////////메인 함수/////////
///////////////////////////
int main() {
	//테스트 데이터 생성
	for (int i = 0; i < 30000; i++) {
		int len = make_int(10, 100);
		//데이터 입력
		for (int j = 0; j < len; j++) {
			input[i][j] = make_char();
		}
		input[i][len] = 0;
		//명령어 입력
		if (i > 1000) {
			cmd[i][0] = rand() % 3;
			cmd[i][1] = rand() % i;
		}
	}

	//해시 함수 테스트
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

	//STL 해시 함수 테스트
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

	//결과값 비교
	int my_hash_size = 0;
	for (int i = 0; i < HASH_SIZE; i++) {
		my_hash_size += table[i][0];
	}

	if (my_hash_size != stl_hash.size()) {
		printf("해시 사이즈 불일치\n");
	}
	for (int i = 0; i < 30000; i++) {
		if (my_find[i] != stl_find[i]) {
			printf("해시 검색 함수 오류\n");
		}
	}

	//처리시간 비교
	printf("수제 해시 시간 : %d\n", my_hash_end - my_hash_begin);
	printf("STL 해시 시간 : %d\n", stl_hash_end - stl_hash_begin);

	return 0;
}