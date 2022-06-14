// https://hackmd.io/@alina-YuTing/HJHlc6ajt
#include <iostream>
#include <vector>
using namespace std;

bool isInBorder(int x ,int y ,int size){ //看x,y 有沒有超過邊界
    if(x < size &&  y < size && x >= 0 && y >= 0){
        return true;
    }
    return false;
}
int dfs(vector<vector<int>>&matrix,int x, int y){
    vector<pair<int,int>> dir= {{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};
    int size = matrix.size(); //這也可以放進dfs的參數，從main func傳進來~
    // if(x >= size || y >= size || x < 0 || y < 0) return -1; //終止條件 超出邊界
    if(isInBorder(x ,y ,size) == false) return -1; //終止條件 超出邊界

    //每個方向都試試看(寫八次太麻煩w)
    int times = 0;
    for(int i = 0 ; i < 8 ; i++){
        int neighborX = x+ dir[i].first ;
        int neighborY = y+ dir[i].second ;
        int jumpX = neighborX+dir[i].first;
        int jumpY = neighborY+dir[i].second;
        // 確保 沒有超過 邊界 並且 我的neighborhood 有東西 與 我跳的地方沒東西
        //我確保 我要跳的地方有沒有超過邊界就好，因為若沒有 也就代表neighborhood也就沒有超過邊界，反之也沒有跳的意義XD
        if (isInBorder(jumpX , jumpY,size) && matrix[neighborX][neighborY] == true  && matrix[jumpX][jumpY]==false){
            matrix[x][y] = false;
            matrix[neighborX][neighborY] = false; // 把他設消失~
            matrix[neighborX+dir[i].first][neighborY+dir[i].second] = true;
            // times = max(times,dfs(matrix , neighborX+dir[i].first , neighborY+dir[i].second) +1);
            int thisTime =  dfs(matrix , neighborX+dir[i].first , neighborY+dir[i].second) +1;
            if(times< thisTime){
                times = thisTime;
            }
            matrix[x][y] = true;
            matrix[neighborX][neighborY] = true; // 又要設回來~
            matrix[neighborX+dir[i].first][neighborY+dir[i].second] = false;
        }
        
    }
    return times;
    
}
int main(){
    int size,x, y;
    cin >> size >> x >> y;
    vector<vector<int> >matrix(size,vector<int>(size,0)); //bool matrix[size][size]
    for(int i = 0 ; i< size ; i++){
        for(int j = 0 ; j< size ; j++){
            cin >> matrix[i][j];
        }
    } 
    cout << dfs(matrix , x , y);
    return 0;
}