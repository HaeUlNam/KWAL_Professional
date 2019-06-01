/* na982님의 youtube hashtable 강의를 참고하여 코드를 작성하였습니다.*/

#include<iostream>
#include<map>
#include<algorithm>
using namespace std;

const int PN = 23;
const int HASH_SIZE = 10000;

int table[HASH_SIZE][50]; //0번째 key의 size
int hash_size = 0;
char hash_raw[30000][100];//string들을 index 순서대로 저장

char input[30000][100];
map<char *, int> test;

unsigned int get_key(char str[]){
    unsigned int key = 0, p = 1;

    for(int i = 0; str[i] != 0; ++i){
        key += (str[i] * p);
        p *= PN;
    }

    return (key % HASH_SIZE);
}

/* a가 사전순으로 앞에 있어야 하면, 음수*/
/* b가 사전순으로 앞에 있어야 하면, 양수*/
/* 같으면 0*/
int my_strcamp(char a[], char b[]){
    int i = 0, j = 0;
    while(a[i]){
        if(a[i++] != b[j++]){
            --i; --j;
            break;
        }
    }
    return a[i] - b[j];
}

void add(char str[]){
    int len = 0;
    for(len = 0; str[len] != 0; ++len){
        hash_raw[hash_size][len] = str[len];
    }
    //종료 문자 삽입
    hash_raw[hash_size][len] = 0;

    unsigned int key = get_key(str);
    int& size = table[key][0];
    table[key][++size] = hash_size;

    ++hash_size;
}

bool remove(char str[]){
    unsigned int key = get_key(str);
    int & size = table[key][0];
    for(int i = 1; i <= size; ++i){
        int pos = table[key][i];

        //삭제
        if(my_strcamp(hash_raw[pos], str) == 0){
            for(int j = i + 1; j <= size; j++){
                table[key][j - 1] = table[key][j]; 
            }
            --size;
            return true;
        }
    }

    return false;
}

int contain(char str[]){
    unsigned int key = get_key(str);
    int size = table[key][0];       //가장 처음이 key의 size
    for(int i = 1; i <= size; ++i){
        int pos = table[key][i];
        if(my_strcamp(hash_raw[pos], str) == 0){ // 0이면 같은 것
            //존재하는 것이기에,
            return pos;
        }
    }

    //존재하지 않는다.
    return -1;
}
