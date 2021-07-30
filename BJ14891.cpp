#include <iostream>
#include <deque>
#include <cmath>
using namespace std;
int wheels[4][8] = {0, };
int K;
deque<pair<int, int>> cmd;
deque<pair<int, int>> rotate_wh;
int score = 0;
void check_wheels(int num, int d){
    switch(num){
        case 0:
            //0-1
            if(wheels[0][2] != wheels[1][6]){
                rotate_wh.push_back(make_pair(1, -1*d));
                //1-2
                if(wheels[1][2] != wheels[2][6]){
                    rotate_wh.push_back(make_pair(2, d));
                    //2-3
                    if(wheels[2][2] != wheels[3][6]){
                        rotate_wh.push_back(make_pair(3, -1*d));
                    }
                }
            }
            break;
        case 1:
            //1-0
            if(wheels[1][6] != wheels[0][2]){
                rotate_wh.push_back(make_pair(0, -1*d));
            }
            //1-2
            if(wheels[1][2] != wheels[2][6]){
                rotate_wh.push_back(make_pair(2, -1*d));
                //2-3
                if(wheels[2][2] != wheels[3][6]){
                    rotate_wh.push_back(make_pair(3, d));
                }
            }
            break;
        case 2:
            //2-1
            if(wheels[2][6] != wheels[1][2]){
                rotate_wh.push_back(make_pair(1, -1*d));
                //1-0
                if(wheels[1][6] != wheels[0][2]){
                    rotate_wh.push_back(make_pair(0, d));
                }
            }
            //2-3
            if(wheels[2][2] != wheels[3][6]){
                rotate_wh.push_back(make_pair(3, -1*d));
            }
            break;
        case 3:
            //3-2
            if(wheels[3][6] != wheels[2][2]){
                rotate_wh.push_back(make_pair(2, -1*d));
                if(wheels[2][6] != wheels[1][2]){
                    rotate_wh.push_back(make_pair(1, d));
                    if(wheels[1][6] != wheels[0][2]){
                        rotate_wh.push_back(make_pair(0, -1*d));
                    }
                }
            }
            break;
    }
    return;
}
void rotate_wheels(){
    while(!cmd.empty()){
        rotate_wh.clear();
        rotate_wh.push_back(cmd.front());
        cmd.pop_front();
        check_wheels(rotate_wh.front().first, rotate_wh.front().second);
        while(!rotate_wh.empty()){
            int wh = rotate_wh.front().first;
            int d = rotate_wh.front().second;
            rotate_wh.pop_front();
            if(d == 1){
                int temp = wheels[wh][7];
                for(int i=6; i>=0; i--){
                    wheels[wh][i+1] = wheels[wh][i];
                }
                wheels[wh][0] = temp;
            }
            else{
                int temp = wheels[wh][0];
                for(int i=1; i<=7; i++){
                    wheels[wh][i-1] = wheels[wh][i];
                }
                wheels[wh][7] = temp;
            }
        }
    }
}
void cal_score(){
    for(int i=0; i<4; i++){
        if(wheels[i][0] == 1){
            score += pow(2, i);
        }
    }
}
int main(int argc, const char * argv[]) {
    for(int i=0; i<4; i++){
        int n;
        cin >> n;
        for(int j=7; j>=0; j--){
            wheels[i][j] = n % 10;
            n /= 10;
        }
    }
    cin >> K;
    for(int i=0; i<K; i++){
        int num, d;
        cin >> num >> d;
        cmd.push_back(make_pair(num-1, d));
    }
    rotate_wheels();
    cal_score();
    cout << score << endl;
    
    return 0;
}
