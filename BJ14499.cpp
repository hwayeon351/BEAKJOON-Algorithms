//
//  main.cpp
//  BJ14499
//
//  Created by Hwayeon on 2021/07/21.
//

#include <iostream>
#include <deque>
using namespace std;

int map[20][20] = {0,};
int N, M, K;
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, -1, 1};

struct dices{
    int x;
    int y;
    int nums[6] = {0,};
};
dices dice;
deque<int> command;

void change_dice(int d){
    switch(d){
        int temp;
        //동쪽
        case 0:
            temp = dice.nums[5];
            dice.nums[5] = dice.nums[3];
            dice.nums[3] = dice.nums[2];
            dice.nums[2] = dice.nums[1];
            dice.nums[1] = temp;
            break;
        //서쪽
        case 1:
            temp = dice.nums[1];
            dice.nums[1] = dice.nums[2];
            dice.nums[2] = dice.nums[3];
            dice.nums[3] = dice.nums[5];
            dice.nums[5] = temp;
            break;
        //북쪽
        case 2:
            temp = dice.nums[0];
            dice.nums[0] = dice.nums[2];
            dice.nums[2] = dice.nums[4];
            dice.nums[4] = dice.nums[5];
            dice.nums[5] = temp;
            break;
        //남쪽
        case 3:
            temp = dice.nums[5];
            dice.nums[5] = dice.nums[4];
            dice.nums[4] = dice.nums[2];
            dice.nums[2] = dice.nums[0];
            dice.nums[0] = temp;
            break;
    }
}

void roll_dice(){
    while(!command.empty()){
        int cmd = command.front();
        command.pop_front();
        int nx = dice.x + dx[cmd];
        int ny = dice.y + dy[cmd];
        if(nx<0 || nx>M-1 || ny<0 || ny>N-1) continue;
        dice.x = nx;
        dice.y = ny;
        change_dice(cmd);

        if(map[ny][nx] == 0){
            map[ny][nx] = dice.nums[5];
        }
        else{
            dice.nums[5] = map[ny][nx];
            map[ny][nx] = 0;
        }
        cout << dice.nums[2] << endl;
    }
}


int main(int argc, const char * argv[]) {
    cin >> N >> M >> dice.y >> dice.x >> K;
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            cin >> map[i][j];
        }
    }
    for(int i=0; i<K; i++){
        int c;
        cin >> c;
        command.push_back(c-1);
    }
    roll_dice();
    return 0;
}
