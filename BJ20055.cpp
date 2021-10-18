//
//  main.cpp
//  BJ20055_1
//
//  Created by Hwayeon on 2021/10/18.
//

#include <iostream>
#include <deque>
using namespace std;

int N, K;
struct Convey{
    int A;
    bool robot = false;
};
Convey cv;
deque<Convey> belts;
int cnt = 0;

void move_robots(){
    while(true){
        cnt++;
        
        //1. 벨트 한 칸 회전
        cv = belts.back();
        belts.pop_back();
        belts.push_front(cv);
        //내리는 곳에 로봇이 있는 경우, 로봇을 내린다
        if(belts[N-1].robot) belts[N-1].robot = false;
        
        //2. 가장 먼저 벨트에 올라간 로봇부터, 한 칸 이동
        for(int i=N-2; i>=0; i--){
            if(!belts[i].robot) continue;
            if(belts[i+1].robot) continue;
            if(belts[i+1].A > 0){
                belts[i+1].robot = true;
                belts[i+1].A--;
                belts[i].robot = false;
            }
        }
        //내리는 곳에 로봇이 있는 경우, 로봇을 내린다
        if(belts[N-1].robot) belts[N-1].robot = false;
        
        //3. 올리는 위치에 로봇을 올린다
        if(belts[0].A > 0){
            belts[0].robot = true;
            belts[0].A --;
        }
        
        //4. 내구도가 0인 칸의 개수 세기
        int gone = 0;
        for(int i=0; i<2*N; i++){
            if(belts[i].A == 0) gone++;
        }
        if(gone >= K) break;
    }
}

int main(int argc, const char * argv[]) {
    cin >> N >> K;
    for(int i=0; i<2*N; i++){
        cin >> cv.A;
        belts.push_back(cv);
    }
    move_robots();
    cout << cnt << endl;
    
    return 0;
}
