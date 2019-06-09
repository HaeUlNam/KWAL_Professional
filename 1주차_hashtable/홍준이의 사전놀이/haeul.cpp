#define MAXQuery 100000
#define PN 23
 
int ht[3 * MAXQuery][10];
int htsize[3 * MAXQuery][10];
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
     
    for(register int i = 0; str[i] != 0; i++)
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
 
    for(register int i = 1; i <= ssize; i++)
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
 
void init(void) {
    int msize = 3 * MAXQuery;
    int mmsize = 5 * MAXQuery;
 
    for(register int i = 0; i < msize; i++)
    {
        for(register int j = 0; j < 10 ; j++)
        {
            ht[i][j] = 0;
            htsize[i][j] = 0;
        }
    }
 
    for(register int i = 0; i < mmsize; i++)
    {
        for(register int j = 0; j < 11; j++)
        {
            ss[i][j] = 0;
        }
    }
 
    strSize = 0;
}
 
void insert(int buffer_size, char *buf) {
    char sss[11] = {0};
 
    for(register int i = 0; i < buffer_size; i++)
    {
        sss[i] = buf[i];
        int key = getHashcode(sss);
        int sR = search(key, sss);
         
        if(sR == -1)
        {
            add(key, sss);
        }
        else
        {
            htsize[key][sR]++;
        }
    }
}
 
int query(int buffer_size, char *buf) {
    int key = getHashcode(buf);
    int sR = search(key, buf);
 
    int result = 0;
    if(sR != -1) result = htsize[key][sR];
 
    return result;
}