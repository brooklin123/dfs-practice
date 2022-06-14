// https://hackmd.io/4lnbCuLWSE2RR9DSbV2v5Q?view
#include <iostream>
#include <vector>
using namespace std;
int n , m; // n是matrix的size // m是bomb的量

vector<pair<int,int>> dir = {{-1,0},{0,-1},{0,1},{1,0}};
bool isInBorder(int x ,int y){ //看x,y 有沒有超過邊界
    if(x < n &&  y < n && x >= 0 && y >= 0){
        return true;
    }
    return false;
}
bool check_onEdgeButCorner(int r , int c){ 
    if(r == 0 || r == n-1 || c == 0|| c == n-1){
        if((r == 0 && c == 0) || (r == 0 && c ==n-1) || (r == n-1 && c == 0) || (r == n-1 && c == n-1))return false;
        return true;
    }
    return false;
}
/*
  param int r {the row of position}
  param int c {the column of position}
  param vector<vector<int>> matrix {the maze. the wall = 1,and aisle = 0}
  param vector<vector<int>> isUsed {record each cell whether it is used}
  param int bomb_use {the column of the number of used bomb}
  return pair<int,int> dfs {the least step and least bomb}
*/
pair<int,int> dfs(int r , int c , vector<vector<int>>&matrix , vector<vector<int>>&isUsed){
    pair<int,int>least_step_and_bomb = {1e8 , 1e8};
    if(!isInBorder(r,c)){
        return least_step_and_bomb;
    }
    if(!matrix[r][c] && check_onEdgeButCorner(r,c)){ //周圍 但非位置是四個角 是可以出去的
        return {0,0};
    }
    // variable int temp_step {temporaryly store step ,because waana pass the next val +1}
    pair<int,int>temp_pair={1e8,1e8};
    for(int i = 0 ; i < 4 ; i++){
        int nextX = r + dir[i].first;
        int nextY = c + dir[i].second;
        if(isInBorder(nextX,nextY) && !isUsed[nextX][nextY]){ // 沒有超過邊界 且 沒有用過!
            if(matrix[nextX][nextY] == 0){ // 是0直接走
                isUsed[nextX][nextY] = true;
                temp_pair = dfs(nextX , nextY , matrix , isUsed);
                temp_pair.first++;
                isUsed[nextX][nextY] = false;
            }
            else if(matrix[nextX][nextY] == 1 && nextX != 0 && nextY != 0 && nextX != n-1 && nextY != n-1){//非0 用炸彈~ 但在外圍不可以用!
                isUsed[nextX][nextY] = true;
                temp_pair = dfs(nextX , nextY , matrix , isUsed);
                temp_pair.first++, temp_pair.second++ ;
                isUsed[nextX][nextY] = false;
            }
            if(temp_pair.second <= m){ //the num of bomb use cannot over the limit
                if(temp_pair.first < least_step_and_bomb.first){
                least_step_and_bomb.first = temp_pair.first;
                least_step_and_bomb.second = temp_pair.second;
                }
                if(least_step_and_bomb.first == temp_pair.first && least_step_and_bomb.second > temp_pair.second){
                    least_step_and_bomb.second = temp_pair.second;
                }  
            }
            
        } 
    }
    return least_step_and_bomb;
}
int main(){
    int r , c; 
    cin >> n >> m;
    vector<vector<int>>matrix(n,vector<int>(n));
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < n ; j++){
            cin >> matrix[i][j];
        }
    }
    vector<vector<int>>isUsed(n,vector<int>(n,0));
    cin >> r >> c;
    isUsed[r][c] = true;
    pair<int,int> ans = dfs(r , c , matrix , isUsed);
    cout << "step : " << ans.first;
    cout << " bomb : " << ans.second;
    return 0;
}

/* 進步:第55行!
把used_bomb 寫在dfs()參數裡， 而非在遞迴完在做判斷
導致會吃TLE。
*/