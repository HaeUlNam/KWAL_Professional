#define MAXQuery 100000
#define PN 23
#include<iostream>
using namespace std;

struct aaa{
    int hash;
    int key;
};

int ht[3 * MAXQuery][5];
int htsize[3 * MAXQuery][5];
char ss[5 * MAXQuery][11];

int strSize;

int strcmp__(char * a, char * b)
{
    int i = 0, j = 0;

    while(a[i]!= 0)
    {
        if(a[i++] != b[j++])
        {
            i--; j--;
            break;
        }
    }

    return a[i] - b[j];
}

int getHashcode(char * str)
{
    /* unsigned로 해서, overflow나도 양수가 되도록 한다.*/
    unsigned long key = 0;
    unsigned long hash = 1;
    int c;

    for(int i = 0; str[i]!= 0; i++){
        key += (str[i] * hash);
        hash *= PN;
    }

    return (key % (3 * MAXQuery));
}

void add(int key, char * str)
{
    int & ssize = ht[key][0];

    ssize++;
    ht[key][ssize] = strSize;
    
    for(int i = 0; str[i] != 0; i++)
    {
        ss[strSize][i] = str[i];
    }
    
    htsize[key][ssize]++;
    strSize++;
}

//-1 없음, >0는 해당 key에서의 index
int search(int key, char * str)
{
    int ssize = ht[key][0];
    int result = -1;

    for(int i = 1; i <= ssize; i++)
    {
        int iidx = ht[key][i];
        if(!strcmp__(str, ss[iidx]))
        {
            result = i;
            break;
        }    
    }

    return result;
}

void gggetHashcode(char * str)
{
    /* unsigned로 해서, overflow나도 양수가 되도록 한다.*/
    unsigned long key = 0;
    unsigned long hash = 1;
    int c;
    char sss[11] = {0};

    for(int i = 0; str[i]!= 0; i++){
        sss[i] = str[i];
        key += (str[i] * hash);
        key %= (3 * MAXQuery);

        int sR = search(key, sss);
        
        if(sR == -1)
        {
            add(key, sss);
        }
        else
        {
            htsize[key][sR]++;
        }

        hash *= PN;
    }
}

void init(void) {
    int msize = 3 * MAXQuery;
    int mmsize = 5 * MAXQuery;

    for(int i = 0; i < msize; i++)
    {
        for(int j = 0; j < 10 ; j++)
        {
            ht[i][j] = 0;
            htsize[i][j] = 0;
        }
    }

    for(int i = 0; i < mmsize; i++)
    {
        for(int j = 0; j < 11; j++)
        {
            ss[i][j] = 0;
        }
    }

    strSize = 0;
}

void insert(int buffer_size, char *buf) {
    gggetHashcode(buf);
}

int query(int buffer_size, char *buf) {
    int key = getHashcode(buf);
    int sR = search(key, buf);

    int result = 0;
    if(sR != -1) result = htsize[key][sR];

	return result;
}