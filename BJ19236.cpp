//
//  main.cpp
//  BJ19236_1
//
//  Created by Hwayeon on 2021/10/22.
//

#include <iostream>
#include <string.h>
#include <vector>
#include <queue>
using namespace std;

struct Shark{
    int x;
    int y;
    int d;
    int eat = 0;
};
struct Fish{
    int x;
    int y;
    int num = 0;
    int d;
    bool arrive = true;
};
Fish fish;
Shark shark;

Fish fishes[17];

int area[4][4];

int dx[9] = {0, -1, -1, 0, 1 ,1, 1,  0, -1};
int dy[9] = {0, 0, -1, -1, -1, 0, 1, 1, 1};

int max_eat = 0;

void hunt(Shark now_shark, int area[][4], Fish fishes[17]){
    if(now_shark.eat > max_eat) max_eat = now_shark.eat;
    //1. 시뮬레이션 할 copy_area, copy_fishes 초기화
    Fish copy_fishes[17];
    int copy_area[4][4];
    memcpy(copy_area, area, sizeof(copy_area));
    memcpy(copy_fishes, fishes, sizeof(copy_fishes));
    
    //2. 물고기 이동
    for(int i=1; i<17; i++){
        //죽은 물고기
        if(!copy_fishes[i].arrive) continue;
        for(int d=copy_fishes[i].d; d<copy_fishes[i].d+8; d++){
            int nx, ny, nd;
            if(d <= 8) nd = d;
            else nd = d-8;
            nx = copy_fishes[i].x + dx[nd];
            ny = copy_fishes[i].y + dy[nd];
            if(nx<0 || nx>=4 || ny<0 || ny>=4) continue;
            if(nx == now_shark.x && ny == now_shark.y) continue;
            //빈칸 있는 곳으로 이동
            if(copy_area[nx][ny] == 0){
                copy_area[nx][ny] = i;
                copy_area[copy_fishes[i].x][copy_fishes[i].y] = 0;
                copy_fishes[i].d = nd;
                copy_fishes[i].x = nx;
                copy_fishes[i].y = ny;
            }
            //물고기 위치 바꾸기
            else{
                int swap = copy_area[nx][ny];
                copy_area[nx][ny] = i;
                copy_area[copy_fishes[i].x][copy_fishes[i].y] = swap;
                copy_fishes[swap].x = copy_fishes[i].x;
                copy_fishes[swap].y = copy_fishes[i].y;
                copy_fishes[i].d = nd;
                copy_fishes[i].x = nx;
                copy_fishes[i].y = ny;
            }
            break;
        }
    }
    
    //2. 상어 이동
    for(int dis=1; dis<4; dis++){
        int nx = now_shark.x + (dis*dx[now_shark.d]);
        int ny = now_shark.y + (dis*dy[now_shark.d]);
        if(nx<0 || nx>=4 || ny<0 || ny>=4) continue;
        if(copy_area[nx][ny] == 0) continue;
        //물고기 먹는다
        int eat_fish = copy_area[nx][ny];
        shark = now_shark;
        shark.eat += eat_fish;
        shark.d = copy_fishes[eat_fish].d;
        shark.x = nx;
        shark.y = ny;
        copy_fishes[eat_fish].arrive = false;
        copy_area[nx][ny] = 0;
        hunt(shark, copy_area, copy_fishes);
        copy_fishes[eat_fish].arrive = true;
        copy_area[nx][ny] = eat_fish;
    }
}

int main(int argc, const char * argv[]) {
    for(int x=0; x<4; x++){
        for(int y=0; y<4; y++){
            cin >> fish.num >> fish.d;
            fish.arrive = true;
            fish.x = x;
            fish.y = y;
            area[x][y] = fish.num;
            fishes[fish.num] = fish;
        }
    }
    //맨 처음 상어 (0, 0) 물고기를 먹는다
    fishes[area[0][0]].arrive = false;
    shark.eat = area[0][0];
    shark.d = fishes[area[0][0]].d;
    shark.x = 0;
    shark.y = 0;
    area[0][0] = 0;
    hunt(shark, area, fishes);
    cout << max_eat << endl;
    return 0;
}
