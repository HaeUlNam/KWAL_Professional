/*
SWEA 제출결과
일자:  2019-06-10 22:27
메모리: 49,628 kb
실행시간: 633 ms
코드길이: 1,760
*/

#define HASH_SIZE 100000
#define PN 19

int dataInd;
char dataList[1000000][10];
int dataCount[1000000];
int dataSize[1000000];
int tInd[HASH_SIZE][50];
unsigned int key;

unsigned int getKey(char *buf, int bufSize) {
	unsigned int key = 0, p = 1;
	for (int i = 0; i < bufSize; i++) {
		key += p * buf[i];
		p *= PN;
	}
	     
	return key % HASH_SIZE;
}

void hashAdd(char *buf, int size) {
	dataSize[dataInd] = size;
	for (int i = 0; i < size; i++) {
		dataList[dataInd][i] = buf[i];
	}
	dataCount[dataInd]++;
	tInd[key][++tInd[key][0]] = dataInd;
	dataInd++;
}

bool hashComp(int table_ind, char* buf, int bufSize) {
	int i = 0;
	while (i < bufSize) {
		if (dataList[table_ind][i] != buf[i])
			return 1;
		i++;
	}

	return 0;
}

int hashFind(char *buf, int bufSize) {
	int h_size = tInd[key][0];
	for (int i = 1; i <= h_size; i++) {
		int n = tInd[key][i];
		if (dataSize[n] == bufSize) {
			if (hashComp(n, buf, bufSize) == 0) {
				return n;
			}
		}
	} 

	return -1;
}

void init(void) {
	//dataList, dataCount 초기화
	for (int i = 1; i < dataInd; i++) {
		for (int j = 0; dataList[i][j] != 0; j++) {
			dataList[i][j] = 0;
		}
		dataSize[i] = 0;
		dataCount[i] = 0;
	}
	dataInd = 1;
	//tInd 초기화
	for (int i = 0; i < HASH_SIZE; i++) {
		int h_size = tInd[i][0];
		for (int j = 1; j < h_size; j++) {
			tInd[i][j] = 0;
		}
		tInd[i][0] = 0;
	}

}

void insert(int buffer_size, char *buf) {
	for (int i = 1; i <= buffer_size; i++) {
		int ind = 0;
		key = getKey(buf, i);
		ind = hashFind(buf, i);
		if (ind == -1) {
			hashAdd(buf, i);
		}
		else {
			dataCount[ind]++;
		}
	}
}

int query(int buffer_size, char *buf) {
	key = getKey(buf, buffer_size);

	int tar = hashFind(buf, buffer_size);
	if (tar != -1) {
		return dataCount[tar];
	}

	return 0;
}