//
//  main.cpp
//  BJ14499
//
//  Created by 최화연 on 2022/04/23.
//

#include <iostream>
using namespace std;

int N, M, K;

struct Dice {
    int x;
    int y;
    int side[7] = {0, };
};
Dice dice;

int map[20][20] = {0, };
int dx[5] = {0, 0, 0, -1, 1};
int dy[5] = {0, 1, -1, 0, 0};

bool move_dice(int dir) {
    dice.x += dx[dir];
    dice.y += dy[dir];
    
    if (dice.x < 0 || dice.x >= N || dice.y < 0 || dice.y >= M) {
        dice.x -= dx[dir];
        dice.y -= dy[dir];
        return false;
    }
    
    int temp = dice.side[1];
    switch (dir) {
        case 1:
            dice.side[1] = dice.side[4];
            dice.side[4] = dice.side[6];
            dice.side[6] = dice.side[3];
            dice.side[3] = temp;
            break;
            
        case 2:
            dice.side[1] = dice.side[3];
            dice.side[3] = dice.side[6];
            dice.side[6] = dice.side[4];
            dice.side[4] = temp;
            break;
            
        case 3:
            dice.side[1] = dice.side[5];
            dice.side[5] = dice.side[6];
            dice.side[6] = dice.side[2];
            dice.side[2] = temp;
            break;
            
        case 4:
            dice.side[1] = dice.side[2];
            dice.side[2] = dice.side[6];
            dice.side[6] = dice.side[5];
            dice.side[5] = temp;
            break;
    }
    
    return true;
}

int main(int argc, const char * argv[]) {
    cin >> N >> M >> dice.x >> dice.y >> K;
    for (int i=0; i<N; i++) {
        for (int j=0; j<M; j++) {
            cin >> map[i][j];
        }
    }
    for (int k=0; k<K; k++) {
        int dir;
        cin >> dir;
        if (move_dice(dir)) {
            if (map[dice.x][dice.y] == 0) map[dice.x][dice.y] = dice.side[6];
            else {
                dice.side[6] = map[dice.x][dice.y];
                map[dice.x][dice.y] = 0;
            }
            cout << dice.side[1] << endl;
        }
    }
    return 0;
}
