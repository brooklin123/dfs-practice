// https://zerojudge.tw/ShowProblem?problemid=c074
// 輸入一個Set，需要一個數量為6 從小排到大的組合
// 不用去考慮前者了!
#include <iostream>
#include <vector>
using namespace std;
vector<int>vec;
vector<int>tmp(6);

void dfs(int depth , int start){
    if(depth == 6){
        // print the combination
        for(int i : tmp){
            cout << i << " ";
        }
        cout << endl ;
        return;
    }
    for(int i = start ; i < vec.size() ; i++){
        tmp[depth] = vec[i];
        dfs(depth+1 , i+1);
    }
}

int main(){
    int n , m;
    while(cin >> n && n){
        for(int i = 0 ; i < n ; i++){
            cin >> m ; 
            vec.push_back(m);
        }
        dfs(0,0);
    }
    return 0;
}