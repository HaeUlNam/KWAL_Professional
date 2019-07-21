#include<iostream>
using namespace std;

#define MAXSIZE 100001

void swap(int * a, int * b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

struct MaxHeap{
    int arr[MAXSIZE];
    int ssize;
    
    /*생성자 초기화*/
    MaxHeap()
    {
        for(int i = 0; i < MAXSIZE; i++)
        {
            arr[i]= 0;
        }

        ssize = 0;
    }

    void push(int num)
    {
        if(ssize >= MAXSIZE)
        {
            cout << "[ERROR] push" << "\n";
            return;
        }

        int cur = ++ssize;

        /*root가 아니고, 부모가 자식보다 작을 때*/
        while(cur != 1 && arr[cur / 2] < num)
        {
            /*부모와 자식 swap*/
            arr[cur] = arr[cur / 2];
            /*index 변경*/
            cur /= 2;
        }

        /*cur 위치에 값 저장*/
        arr[cur] = num;
    }

    void pop()
    {
        if(ssize <= 0)
        {
            // cout << "[ERROR] pop" << "\n";
            return;
        }

        swap(arr[1], arr[ssize--]);

        int cur = 1;
        int child = cur * 2;

        int comNum = arr[1];

        while(child <= ssize)
        {
            /*child 왼쪽 오른쪽 중 큰 것으로 결정*/
            if(child < ssize && arr[child] < arr[child + 1]) ++child;

            /*child보다 크면 멈춤*/
            if(comNum >= arr[child]) break;

            /*아니면 계속 진행*/
            arr[cur] = arr[child];

            cur = child;
            child *= 2;    
        }

        arr[cur] = comNum;
    }

    int front()
    {
        if(ssize <= 0) return 0;

        return arr[1];
    }

    void print()
    {
        for(int i = 1; i <= ssize; i++)
            cout << arr[i] << " ";
        cout << "\n";
    }    
};

MaxHeap mm;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int t;
    cin >> t; 

    int aa;
    for(int i = 0; i < t; i++)
    {
        cin >> aa;
        if(aa == 0)
        {
            cout << mm.front() << "\n";
            mm.pop();
        }
        else
        {
            mm.push(aa);
        }
    }

    return 0;
}