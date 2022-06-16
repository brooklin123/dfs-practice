// https://cpe.cse.nsysu.edu.tw/cpe/file/attendance/problemPdf/674.pdf
#include <iostream>
#include <vector>
using namespace std;

vector<int> moneytype({50, 25, 10, 5, 1});

//pos當作決定第幾個moneytype
int dfs(int n , int pos){
    int ans = 0;
    if(n == 0){
        return 1;
    } 
    if(n < 0 || pos >= moneytype.size()){
        return 0;
    }
    for(int i = 0 ; i <= n/moneytype[pos] ; i++){
        ans += dfs(n - moneytype[pos]*i , pos + 1);
    }  
    return ans;
}
int main(){
    int n;
    while(cin >> n){
        cout << dfs(n , 0);
    }
    return 0;
}