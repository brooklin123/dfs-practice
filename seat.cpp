#include <iostream>
#include <vector>
using namespace std;
class Student{
    public:
        int number;
        int days;
        Student(){ //他沒有自動補0.0
        }
        Student(int num){ //this is pointer!
            this->number = num;
            this->days = 0;
        }
};

pair<int,int> findPos(int num , vector<vector<Student>>& classroom){
    pair<int,int>iamHere;
    int avoidNothisMan = false; //沒有這個人!
    for(int i = 0; i < classroom.size() ; i++){
        for(int j = 0 ; j < classroom.size() ; j++){
            if(classroom[i][j].number == num){
                iamHere.first = i;
                iamHere.second = j;
                avoidNothisMan = true;
                return iamHere;
            }
        }
    }
    if(!avoidNothisMan){
        cout <<"i cannot find this man: " << num <<"\n";
        return iamHere; //empty
    }
    return iamHere;
}
void minusAday(vector<vector<Student>>& classroom,int n){
    for(int i = 0; i < n ; i++){
        for(int j = 0 ; j < n ; j++){
            if(classroom[i][j].days > 0){
                classroom[i][j].days-=1;
            }
        }
    }
}
bool isInBorder(int x ,int y ,int size){ //看x,y 有沒有超過邊界
    if(x < size &&  y < size && x >= 0 && y >= 0){
        return true;
    }
    return false;
}
void addDays(pair<int,int>& virusCenter,vector<vector<Student>>& classroom){
    int centerR = virusCenter.first;
    int centerC = virusCenter.second;
    classroom[centerR][centerC].days = 14;
    // 9宮格內同學們加3，且要確保不超過邊界!
    vector<pair<int,int>>gird = {{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};
    int theManR ,theManC;
    for(int i = 0 ; i < 8 ; i++){
        theManR = centerR + gird[i].first;
        theManC = centerC + gird[i].second;
        if (isInBorder(theManR , theManC , classroom.size())){
            if(classroom[theManR][theManC].days < 3){ //大於三的保持原本的隔離天數
                classroom[theManR][theManC].days = 3;
            }
        }
    }
}

void printDays(vector<vector<Student>>& classroom , int n){
    for(int i = 0; i < n ; i++){
        for(int j = 0 ; j < n ; j++){
            cout << classroom[i][j].days <<" ";
        }
        cout << endl;
    }
}
int main(){
    int n; 
    int virusGotU[7];
    cin >> n;
    vector<vector<Student>>classroom(n,vector<Student>(n));
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < n ; j++){
            int number;
            cin >> number;
            classroom[i][j] = Student(number);
        }
    }
    
    for(int i = 0 ; i < 7 ; i++){
        minusAday(classroom, n);
        cin >>virusGotU[i];
        if(virusGotU[i] != 0){
            pair<int,int> itisME = findPos(virusGotU[i],classroom); // return row and col
            addDays(itisME,classroom);
        }
    }
    printDays(classroom,n);

    return 0;
}