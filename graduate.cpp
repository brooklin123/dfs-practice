#include <iostream>
#include <vector>
using namespace std;

//check為 確認是否超過兩項
bool check(vector<int>&result, int i){
    int s = result.size();
    if(s >= 2){
        return !(result[s-1] == result[s-2] && result[s-1] == i);
    }
    return true;//size = 1 
} 
// result 放組合
//我遞迴 每層代表 我第i調紙帶要甚麼顏色 !
int dfs(vector<int>&colors, int all , vector<int>&result){
    int ans = 0;
    if(all == 0) return 1; // 全部拿完
    for(int i = 0 ; i < colors.size() ; i++){  
        if(check(result, i) && colors[i] > 0){
            result.push_back(i);
            colors[i]--;
            ans += dfs(colors,all-1,result);
            result.pop_back();
            colors[i]++;
        }
    return ans;
}


int main(){ 
    int n ,all = 0; // all是所有紙條的數量
    cin >> n ;
    vector<int>colors(n);
    for(int i = 0 ; i < n ; i++){
        cin >> colors[i];
        all += colors[i];
    }
    colors.push_back(all); //最後一項 當作是白色
    vector<int>result;
    cout << dfs(colors, all,result);
 
    return 0;
}


// ---------------------------------------------
// the poorly readiable version

/*
int dfs(vector<int>&colors, int pre , int limit, int all){
    int ans = 0;
    if(all == 0) return 1; // 全部拿完
    cout << colors.size() << endl;
    for(int i = -1 ; i < (int)colors.size() ; i++){  
        if(i == -1 && pre != -1){ //我要取白色!且前者不是白色。要避免與同樣拿到兩次
            ans += dfs(colors , -1 , 1 , all-1);
        }
        else if(i == -1 && pre == -1 && limit < 2){ //我要取白色 且前者也是白色
            ans += dfs(colors , -1 , 2 , all-1);
        }
        else if(i != -1 && pre != i && colors[i] > 0){ // (取非白色的) 與前面顏色不同
            colors[i]--;
            ans += dfs(colors, i ,1 , all-1);
            colors[i]++;
        }//取非白色 且與前一個顏色相同
        if(i !=-1 && pre == i && limit < 2 && colors[i] > 0){
            colors[i]--;
            ans += dfs(colors , i , 2 , all-1);
            colors[i]++;
        } 
    }
    return ans;
}

int main(){
    int n ,all = 0; // all是所有紙條的數量
    cin >> n ;
    vector<int>colors(n);
    for(int i = 0 ; i < n ; i++){
        cin >> colors[i];
        all += colors[i];
    }
    // int limit = 0; //最多兩調相同顏色
    // int pre = -2; //前一個的顏色，以數字分，-1代表白色，> 0為有顏色的編號

    cout << dfs(colors, pre , limit , all);
    return 0;
}
*/