//
//  main.cpp
//  BJ19237
//
//  Created by 최화연 on 2022/04/25.
//

#include <iostream>
#include <deque>
using namespace std;

int N, M, k;

struct Smell {
    int timer = 0;
    int shark = 0;
};
Smell smell;
Smell board[20][20];

int dr[5] = {0, -1, 1, 0, 0};
int dc[5] = {0, 0, 0, -1, 1};

struct Shark {
    int r;
    int c;
    int num;
    int dir;
    int priority[5][4];
};
Shark shark;
Shark sharks[401];

deque<Shark> alive_sharks;

int adult_sharks() {
    int sec = 0;
    
    while (1) {
        sec ++;
        
        //상어 이동방향 정하기
        deque<Shark> new_sharks;
        while (!alive_sharks.empty()) {
            shark = alive_sharks.front();
            alive_sharks.pop_front();
            int my_r = -1;
            int my_c = -1;
            int my_d = -1;
            bool check = false;
            for (int d=0; d<4; d++) {
                int r = shark.r + dr[shark.priority[shark.dir][d]];
                int c = shark.c + dc[shark.priority[shark.dir][d]];
                if (r < 0 || r >= N || c < 0 || c >= N) continue;
                //냄새가 없는 칸인 경우
                if (board[r][c].shark == 0) {
                    shark.r = r;
                    shark.c = c;
                    shark.dir = shark.priority[shark.dir][d];
                    new_sharks.push_back(shark);
                    check = true;
                    break;
                }
                //자신의 냄새가 있는 칸인 경우
                else if (board[r][c].shark == shark.num) {
                    if (my_r == -1) {
                        my_r = r;
                        my_c = c;
                        my_d = shark.priority[shark.dir][d];
                    }
                }
            }
            if (!check) {
                shark.r = my_r;
                shark.c = my_c;
                shark.dir = my_d;
                new_sharks.push_back(shark);
            }
        }
        
        //이전 냄새 카운팅
        for (int r=0; r<N; r++) {
            for (int c=0; c<N; c++) {
                if (board[r][c].timer > 0) {
                    board[r][c].timer -= 1;
                    if (board[r][c].timer == 0) {
                        board[r][c].shark = 0;
                    }
                }
            }
        }
        
        //상어 이동하고 냄새뿌리기
        while (!new_sharks.empty()) {
            shark = new_sharks.front();
            new_sharks.pop_front();
            if (board[shark.r][shark.c].shark == 0) {
                smell.timer = k;
                smell.shark = shark.num;
                board[shark.r][shark.c] = smell;
                alive_sharks.push_back(shark);
            }
            else if (board[shark.r][shark.c].shark == shark.num) {
                board[shark.r][shark.c].timer = k;
                alive_sharks.push_back(shark);
            }
        }
        if (alive_sharks.size() == 1) break;
        if (sec >= 1000) return -1;
    }
    
    return sec;
}

int main(int argc, const char * argv[]) {
    cin >> N >> M >> k;
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            int n;
            cin >> n;
            if (n > 0) {
                shark.num = n;
                shark.r = i;
                shark.c = j;
                sharks[shark.num] = shark;
            }
        }
    }
    
    for (int i=1; i<=M; i++) {
        cin >> sharks[i].dir;
    }
    
    for (int i=1; i<=M; i++) {
        for (int d=1; d<=4; d++) {
            for (int dd=0; dd<4; dd++) {
                cin >> sharks[i].priority[d][dd];
            }
        }
    }
    
    for (int i=1; i<=M; i++) {
        alive_sharks.push_back(sharks[i]);
        
        //자신의 위치에 냄새 뿌리기
        board[sharks[i].r][sharks[i].c].timer = k;
        board[sharks[i].r][sharks[i].c].shark = i;
    }
        
    cout << adult_sharks() << endl;
    
    return 0;
}
