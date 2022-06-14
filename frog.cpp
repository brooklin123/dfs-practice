// https://hackmd.io/WOf3a4ZiRqmTRwLccInDvw
#include <iostream>
#include <vector>
using namespace std;

int dfs(vector<int>&frogweight, vector<int>&leafseat, vector<int>&leafweight, int pos){
    //return值是 答案數
    //用重量與位置數篩選掉不適合的combination
    //每一隻蛙決定一個葉子坐，故pos是蛙，每隻蛙都考慮都要考慮所有葉子~
    int ans = 0;
    if(pos == frogweight.size())return 1;
    for(int i = 0; i < leafseat.size() ; i++){
        if(leafseat[i] > 0 && leafweight[i] > 0){
            leafseat[i] -=1;
            leafweight[i] -= frogweight[pos];
            if(leafweight[i] >= 0){
                ans += dfs(frogweight, leafseat, leafweight, pos+1);
            }
            leafweight[i] += frogweight[pos];
            leafseat[i] +=1;
        }
    }
    return ans;
}

int main(){
    int frog , leaf;
    cin >> frog >> leaf ;
    vector<int>frogweight(frog);
    vector<int>leafseat(leaf);
    vector<int>leafweight(leaf);
    for(int f = 0 ; f < frog ; f++){
        cin >> frogweight[f];
    }
    for(int i = 0 ; i < leaf ; i++){
        cin >> leafseat[i];
    }
    for(int i = 0 ; i < leaf ; i++){
        cin >> leafweight[i];
    }
    cout << dfs(frogweight, leafseat, leafweight , 0);
    return 0;
}