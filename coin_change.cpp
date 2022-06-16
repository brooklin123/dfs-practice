// https://cpe.cse.nsysu.edu.tw/cpe/file/attendance/problemPdf/674.pdf
#include <iostream>
#include <vector>
using namespace std;

vector<int> moneytype({50, 25, 10, 5, 1});
//二維record存 row代表第幾個moneytype 第0pos代表最大可用各樹 之後逐一遞減1
vector<vector<int>> record(5);
//pos當作決定第幾個moneytype

int dfs(int n , int pos){
    int ans = 0;
    if(n == 0){
        // cout  <<"win ";
        return 1;
    } 
    if(n < 0 || pos >= 5){
        // if(pos > 5) cout << "lose ";
        return 0;
    }
    else{
        for(int j = 0 ; j < record[pos].size() ; j++){
            if(record[pos][j] != -1){
                // cout << "money " << n <<" moneytype "<< moneytype[pos] << " record :" << record[pos][j] << endl;
                int num = record[pos][j];
                record[pos][j] = -1;
                ans += dfs(n - moneytype[pos] * num , pos + 1);
                record[pos][j] = num;
            }
        }
    }
    // cout <<"?";
    return ans;
}

int main(){
    int n;
    while(cin >> n){
        //每個最大可能
        for(int i = 0 ; i < 5 ; i++){
            int maxval = n / moneytype[i];
            for(int j = maxval ; j > 0 ; j--){
                record[i].push_back(j);
            } 
            record[i].push_back(0);
        }
        cout << dfs(n , 0);
    }
    return 0;
}