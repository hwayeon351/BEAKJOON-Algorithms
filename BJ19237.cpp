//
//  main.cpp
//  BJ19237_1
//
//  Created by Hwayeon on 2021/10/19.
//

#include <iostream>
#include <deque>
using namespace std;

int N, M, k;
int dx[5] = {0, 0, 0, -1, 1};
int dy[5] = {0, -1, 1, 0, 0};

struct Shark{
    int num;
    int x;
    int y;
    int d;
    int priority[5][4] = {0, };
};

//board[y][x]= {shark_num, smell_timer}
int board[20][20][2] = {0, };
deque<Shark> sharks;
deque<Shark> copy_sharks;
int sec = 0;

void move_sharks(){
    while(sharks.size() > 1){
        if(sec >= 1000){
            sec = -1;
            break;
        }
        //1. 상어 이동 방향 정하기
        while(!sharks.empty()){
            Shark now_shark = sharks.front();
            sharks.pop_front();
            bool check = false;
            for(int d=0; d<4; d++){
                int nd = now_shark.priority[now_shark.d][d];
                int nx = now_shark.x + dx[nd];
                int ny = now_shark.y + dy[nd];
                if(nx<0 || nx>=N || ny<0 || ny>=N) continue;
                if(board[ny][nx][0] == 0){
                    check = true;
                    now_shark.x = nx;
                    now_shark.y = ny;
                    now_shark.d = nd;
                    break;
                }
            }
            if(check) {
                copy_sharks.push_back(now_shark);
                continue;
            }
            //자신의 냄새가 있는칸으로
            for(int d=0; d<4; d++){
                int nd = now_shark.priority[now_shark.d][d];
                int nx = now_shark.x + dx[nd];
                int ny = now_shark.y + dy[nd];
                if(nx<0 || nx>=N || ny<0 || ny>=N) continue;
                if(board[ny][nx][0] == now_shark.num){
                    now_shark.x = nx;
                    now_shark.y = ny;
                    now_shark.d = nd;
                    break;
                }
            }
            copy_sharks.push_back(now_shark);
        }
        //2. 냄새 타이머 가동
        for(int y=0; y<N; y++){
            for(int x=0; x<N; x++){
                if(board[y][x][0] == 0) continue;
                board[y][x][1]--;
                if(board[y][x][1] == 0) board[y][x][0] = 0;
            }
        }
        //3. 이동하기
        while(!copy_sharks.empty()){
            Shark now_shark = copy_sharks.front();
            copy_sharks.pop_front();
            if(board[now_shark.y][now_shark.x][0] == 0 || board[now_shark.y][now_shark.x][0] == now_shark.num){
                board[now_shark.y][now_shark.x][0] = now_shark.num;
                board[now_shark.y][now_shark.x][1] = k;
                sharks.push_back(now_shark);
            }
        }
        sec++;
    }
}

int main(int argc, const char * argv[]) {
    cin >> N >> M >> k;
    for(int i=0; i<M; i++){
        Shark shark;
        shark.num = i+1;
        sharks.push_back(shark);
    }
    for(int y=0; y<N; y++){
        for(int x=0; x<N; x++){
            cin >> board[y][x][0];
            if(board[y][x][0] > 0){
                sharks[board[y][x][0]-1].x = x;
                sharks[board[y][x][0]-1].y = y;
                board[y][x][1] = k;
            }
        }
    }
    for(int i=0; i<M; i++){
        cin >> sharks[i].d;
    }
    for(int i=0; i<M; i++){
        for(int d=1; d<=4; d++){
            for(int j=0; j<4; j++){
                cin >> sharks[i].priority[d][j];
            }
        }
    }
    move_sharks();
    cout << sec << endl;
    return 0;
}
