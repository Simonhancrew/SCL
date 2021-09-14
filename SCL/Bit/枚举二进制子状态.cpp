#include <iostream>

using namespace std;

// 可以看作原来的集合忽略0之后不断的-1，但是因为和原集合&的关系，原来0的部分一定不会变1。

int main(){
    int st;
    cin >> st;
    for(int i = st;i;i = (i - 1)& st){
        cout << i << endl;
    }
    return 0;    
}