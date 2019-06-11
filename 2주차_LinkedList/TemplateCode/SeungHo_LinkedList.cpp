/*
배열기반 연결리스트 구현
출처: https://na982.tistory.com/110
참고사항: 시험장에서의 빠른 구현 목적으로 한 코드로, 다음과 같은 문제점이 있음
	* 삭제된 인덱스의 재사용을 고려하지 않은 코드임. 즉, pos가 NODE_SIZE를 넘길 가능성 있음
		-> NODE_SIZE 설정시, 입력기준의 최대치로 설정해야함. (또는 인덱스 재사용을 위한 추가 코드 필요)
	* 비어있을 때 pop할 시의 예외처리가 안되어있음.
	* 기능 함수로 삽입, 삭제만 구현되어 있음
*/
#include <stdio.h>
#include <algorithm>
#include <list>
#include "Windows.h"
using namespace std;

////////////////////////////////
//구현 연결리스트 변수, 구조체//
////////////////////////////////
const int NODE_SIZE = 30000;		//입력 최대치 만큼 설정

struct NODE {				//연결리스트 형식: 이중 연결리스트
	int data;
	int prev;
	int next;
};

struct ModLL {				//연결리스트 구조체
	int HEAD = NODE_SIZE, TAIL = NODE_SIZE + 1;
	int pos;
	NODE node[NODE_SIZE + 2];
	
	ModLL() {
		node[HEAD].next = TAIL;
		node[TAIL].prev = HEAD;
		pos = 0;
	}

	void push_back(int data) {
		int prev = node[TAIL].prev, next = TAIL;

		node[pos].data = data;

		node[pos].prev = prev;
		node[prev].next = pos;

		node[pos].next = next;
		node[next].prev = pos;

		pos++;
	}

	void push_front(int data) {
		int prev = HEAD, next = node[HEAD].next;

		node[pos].data = data;

		node[pos].prev = prev;
		node[prev].next = pos;

		node[pos].next = next;
		node[next].prev = pos;

		pos++;

	}

	void insert(int p, int data) {
		int next = node[HEAD].next;
		for (register int i = 0; i < p; i++) {
			next = node[next].next;
		}
		int prev = node[next].prev;

		node[pos].data = data;

		node[pos].prev = prev;
		node[prev].next = pos;

		node[pos].next = next;
		node[next].prev = pos;

		pos++;
	}

	void pop_back() {
		int tar = node[TAIL].prev;
		int next = node[tar].next, prev = node[tar].prev;

		node[prev].next = next;
		node[next].prev = prev;
	}

	void pop_front() {
		int tar = node[HEAD].next;
		int next = node[tar].next, prev = node[tar].prev;

		node[prev].next = next;
		node[next].prev = prev;
	}

	void erase(int p) {
		int tar = node[HEAD].next;
		for (register int i = 0; i < p; i++) {
			tar = node[tar].next;
		}
		int next = node[tar].next, prev = node[tar].prev;

		node[prev].next = next;
		node[next].prev = prev;
	}
};

/////////////////////
//테스트용 전역변수//
/////////////////////
//명령 코드
const int PUSH_BACK = 0;
const int PUSH_FRONT = 1;
const int INSERT = 2;
const int POP_BACK = 3;
const int POP_FRONT = 4;
const int ERASE = 5;
//명령 저장 배열
int test_cmd[NODE_SIZE][3];

//구현 연결리스트 선언
ModLL my_list;
//STL 연결리스트 선언
list<int> stl_list;

/////////////////
//테스트용 코드//
/////////////////
int main() {
	// Test case 생성
	int cur_size = 0;
	for (int i = 0; i < NODE_SIZE; ++i) {
		if (i < NODE_SIZE / 3) {
			test_cmd[i][0] = rand() % 2;
		}
		else {
			test_cmd[i][0] = rand() % 6;
		}

		switch (test_cmd[i][0]) {
		case PUSH_BACK:
		case PUSH_FRONT: {
			test_cmd[i][1] = rand();
			++cur_size;
			break;
		}
		case INSERT: {
			test_cmd[i][1] = rand() % cur_size;
			test_cmd[i][2] = rand();
			++cur_size;
			break;
		}
		case POP_BACK:
		case POP_FRONT: {
			--cur_size;
			break;
		}
		case ERASE: {
			test_cmd[i][1] = rand() % cur_size;
			--cur_size;
			break;
		}
		}
	}

	// 구현 연결리스트 시험
	int my_list_begin = GetTickCount();
	for (int i = 0; i < NODE_SIZE; ++i) {
		switch (test_cmd[i][0]) {
		case PUSH_BACK: {
			my_list.push_back(test_cmd[i][1]);
			break;
		}
		case PUSH_FRONT: {
			my_list.push_front(test_cmd[i][1]);
			break;
		}
		case INSERT: {
			my_list.insert(test_cmd[i][1], test_cmd[i][2]);
			break;
		}

		case POP_BACK: {
			my_list.pop_back();
			break;
		}
		case POP_FRONT: {
			my_list.pop_front();
			break;
		}
		case ERASE: {
			my_list.erase(test_cmd[i][1]);
			break;
		}
		}
	}
	int my_list_end = GetTickCount();

	// STL 연결리스트 시험
	int stl_list_begin = GetTickCount();
	for (int i = 0; i < NODE_SIZE; ++i) {
		switch (test_cmd[i][0]) {
		case PUSH_BACK: {
			stl_list.push_back(test_cmd[i][1]);
			break;
		}
		case PUSH_FRONT: {
			stl_list.push_front(test_cmd[i][1]);
			break;
		}
		case INSERT: {
			list<int>::iterator it = stl_list.begin();
			for (int k = 0; k < test_cmd[i][1]; ++k) {
				++it;
			}
			stl_list.insert(it, test_cmd[i][2]);
			break;
		}

		case POP_BACK: {
			stl_list.pop_back();
			break;
		}
		case POP_FRONT: {
			stl_list.pop_front();
			break;
		}
		case ERASE: {
			list<int>::iterator it = stl_list.begin();
			for (int k = 0; k < test_cmd[i][1]; ++k) {
				++it;
			}
			stl_list.erase(it);
			break;
		}
		}
	}
	int stl_list_end = GetTickCount();

	//시간 비교
	printf("my list : %d\n", (my_list_end - my_list_begin));
	printf("stl list : %d\n", (stl_list_end - stl_list_begin));

	//결과 검증
	list<int>::iterator it = stl_list.begin();
	int cur = my_list.node[my_list.HEAD].next;
	while (it != stl_list.end()) {
		if (*it != my_list.node[cur].data) {
			printf("Error\n");
		}
		++it;
		cur = my_list.node[cur].next;
	}

	return 0;
}
