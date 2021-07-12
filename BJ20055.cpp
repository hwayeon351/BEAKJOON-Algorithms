//
//  main.cpp
//  BJ20055
//
//  Created by Hwayeon on 2021/07/12.
//

#include <iostream>
using namespace std;

int N, K;
int conv[200];
int robot[100];

void move_conv(){
    int temp = conv[2*N-1];
    for(int i=2*N-2; i>=0; i--){
        conv[i+1] = conv[i];
    }
    conv[0] = temp;

    for(int i=N-3; i>=0; i--){
        robot[i+1] = robot[i];
    }
    robot[0] = 0;
    robot[N-1] = 0;
}

void move_robot(){
    if(robot[N-2] && conv[N-1] > 0){
        robot[N-2] = 0;
        conv[N-1]--;
    }
    for(int i=N-3; i>=1; i--){
        if(robot[i] && conv[i+1] > 0 && !robot[i+1]){
            robot[i] = 0;
            robot[i+1] = 1;
            conv[i+1]--;
        }
    }
}

void lift_robot(){
    if(conv[0] > 0){
        conv[0]--;
        robot[0] = 1;
    }
}

int check_conv(){
    int cnt = 0;
    for(int i=0; i<2*N; i++){
        if(conv[i]==0) cnt++;
    }
    return cnt;
}

int move(){
    int cnt = 0;
    while(true){
        //수행 단계 카운팅
        cnt ++;
        
        //1. 벨트와 로봇 한 칸 회전
        move_conv();

        //2. 로봇 이동
        move_robot();

        //3. 로봇 추가
        lift_robot();

        //4. 내구도 검사
        int k = check_conv();
        if(K <= k) break;
    }
    return cnt;
}

int main(int argc, const char * argv[]) {
    cin >> N >> K;
    for(int i=0; i<2*N; i++){
        cin >> conv[i];
    }
    cout << move() << endl;
    return 0;
}
