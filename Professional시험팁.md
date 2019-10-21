## 이 파일은 삼성 Professional 시험을 볼 때 팁들을 모아둔 파일입니다.

* 모든 for문에 아래와 같이 register int를 사용하면 최적화를 통해, 속도가 빨라진다. (30퍼~ 40퍼 정도)
```cpp 
    for(register int i = 0; i < n; i++){} 
``` 

* C/C++ 최적화 : https://copynull.tistory.com/119
