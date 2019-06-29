/*
참고 : https://www.acmicpc.net/board/view/19412
*/

#include<iostream>
using namespace std;

class Node{
public:
    Node * data[95];
    float count;  
    Node()
    {
        for(int i = 0; i < 95; i++)
        {
            data[i] = 0;
        }
        count = 0;
    }

    ~Node()
    {
        for(int i = 0; i < 95; i++)
        {
            if(data[i] != 0) delete data[i];
        }
    }
};

class trie{
public:
    Node nn;
    trie(){}
};

trie tt;
float totalcount;

void recur(int v, Node * dd, char * cc)
{
    if((*dd).count > 0)
    {
        cout << cc << " ";
        float result = (*dd).count / totalcount;
        result *= 100.0;
        cout << result << "\n";
    }

    for(int i = 0; i < 95; i++)
    {
        if(dd->data[i] != 0) 
        {
            cc[v] = (char)(32 + i);
            recur(v + 1, dd->data[i], cc);
            cc[v] = 0;
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cout << fixed;
    cout.precision(4);

    char iin[31] = {0};
    while(cin.getline(iin,31))
    {
        totalcount++;
        
        Node * cur = &tt.nn;
        for(int i = 0; i < 30 && iin[i]!= 0; i++)
        {
            int aa = (int)(iin[i] - ' ');
            if((*cur).data[aa] == 0)
              (*cur).data[aa] = new Node();
            cur = (*cur).data[aa];
        }

        (*cur).count++;
    }

    char cc[31] = {0};
    recur(0,&tt.nn, cc);

    return 0;
}