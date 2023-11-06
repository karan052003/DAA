#include <iostream>
using namespace std;

int recursive_fibonacci(int n){
    if(n == 0) return 0;
    if(n == 1) return 1;
    
    return recursive_fibonacci(n - 1) + recursive_fibonacci(n - 2);
}

int iterative_fibonacci(int n){
    if(n == 0) return 0;
    if(n == 1) return 1;    
    int pre = 0, curr = 1;
    
    for(int i = 2; i <= n; i++){
        int temp = pre;
        
        pre = curr;
        curr = curr + temp;
    }
    
    
    return curr;  
}

int main(){
    for(int i = 0; i <= 10; i++) cout << recursive_fibonacci(i) << " ";
    cout << endl;
    
    for(int i = 0; i <= 10; i++) cout << iterative_fibonacci(i) << " ";
    cout << endl;
    
    return 0;
}
