//
//  main.cpp
//  BJ19237
//
//  Created by Hwayeon on 2021/10/03.
//

#include <iostream>
#include <string.h>
#include <vector>
#include <queue>
using namespace std;

int N, M, k;
int board[20][20] = {0, };
int sec = 0;

int dx[5] = {0, 0, 0, -1, 1};
int dy[5] = {0, -1, 1, 0, 0};
                  
struct Shark{
    int x;
    int y;
    int num;
    int dir;
    int priority[5][4] = {0, };
};
Shark shark;
vector<Shark> sharks;
queue<Shark> cp_sharks;

struct Smell{
    int shark_num;
    int timer = 0;
};

Smell smell[20][20];
vector<pair<int, int>> smell_locs;
vector<pair<int, int>> cp_smell_locs;

void move_sharks(){
    for(int i=0; i<sharks.size(); i++){
        shark = sharks[i];
        bool ck = false;
        int new_x = -1;
        int new_y = -1;
        int new_dir = -1;
        for(int j=0; j<4; j++){
            int n_dir = sharks[i].priority[sharks[i].dir][j];
            int nx = sharks[i].x + dx[n_dir];
            int ny = sharks[i].y + dy[n_dir];
            if(nx<0 || nx>=N || ny<0 || ny>=N) continue;
            if(smell[ny][nx].timer == 0){
                ck = true;
                shark.x = nx;
                shark.y = ny;
                shark.dir = n_dir;
                cp_sharks.push(shark);
                break;
            }
            else if(smell[ny][nx].shark_num == sharks[i].num){
                if(new_x != -1) continue;
                new_x = nx;
                new_y = ny;
                new_dir = n_dir;
            }
        }
        if(!ck){
            shark.x = new_x;
            shark.y = new_y;
            shark.dir = new_dir;
            cp_sharks.push(shark);
        }
    }
    
    sharks.clear();
    memset(board, 0, sizeof(board));
    while(!cp_sharks.empty()){
        shark = cp_sharks.front();
        cp_sharks.pop();
        if(board[shark.y][shark.x] != 0) continue;
        board[shark.y][shark.x] = shark.num;
        sharks.push_back(shark);
    }
}

void count_timer(){
    cp_smell_locs = smell_locs;
    smell_locs.clear();
    while(!cp_smell_locs.empty()){
        int x = cp_smell_locs.back().first;
        int y = cp_smell_locs.back().second;
        cp_smell_locs.pop_back();
        smell[y][x].timer--;
        if(smell[y][x].timer == 0) continue;
        smell_locs.push_back({x, y});
    }
}

void spread_smell(){
    for(int i=0; i<sharks.size(); i++){
        smell[sharks[i].y][sharks[i].x].shark_num = sharks[i].num;
        if(smell[sharks[i].y][sharks[i].x].timer == 0){
            smell_locs.push_back({sharks[i].x, sharks[i].y});
        }
        smell[sharks[i].y][sharks[i].x].timer = k;
    }
}

void play(){
    while(true){
        sec++;
        if(sec > 1000){
            sec = -1;
            return;
        }
        //1. 상어 움직이기
        move_sharks();
        //2. 냄새 타이머 1초 빼기
        count_timer();
        //3. 상어 위치에 냄새 뿌리기
        spread_smell();
        //4. 격자 안 상어 카운팅
        if(sharks.size() == 1) break;
    }
}

int main(int argc, const char * argv[]) {
    cin >> N >> M >> k;
    for(int i=1; i<=M; i++){
        shark.num = i;
        sharks.push_back(shark);
    }
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cin >> board[i][j];
            if(board[i][j] != 0){
                sharks[board[i][j]-1].x = j;
                sharks[board[i][j]-1].y = i;
                smell[i][j].timer = k;
                smell[i][j].shark_num = board[i][j];
                smell_locs.push_back({j, i});
            }
        }
    }
    for(int i=0; i<M; i++){
        cin >> sharks[i].dir;
    }
    for(int i=0; i<M; i++){
        for(int j=1; j<=4; j++){
            for(int k=0; k<4; k++){
                cin >> sharks[i].priority[j][k];
            }
        }
    }
    play();
    cout << sec << endl;
    
    return 0;
}
