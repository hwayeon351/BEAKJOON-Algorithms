//
//  main.cpp
//  BJ19236
//
//  Created by 최화연 on 2022/04/27.
//

#include <iostream>
#include <cstring>
using namespace std;

struct Fish {
    int x;
    int y;
    int num = 0;
    int dir;
};
Fish area[4][4];
Fish fishes[17];
Fish fish;

struct Shark {
    int x;
    int y;
    int dir;
    int eat = 0;
};

int dx[9] = {0, -1, -1, 0, 1, 1, 1, 0, -1};
int dy[9] = {0, 0, -1, -1, -1, 0, 1, 1, 1};

int max_eat = 0;

void hunt_fish(Shark shark, Fish area[][4], Fish fishes[17]) {
    if (shark.eat > max_eat) max_eat = shark.eat;
    
    Fish copy_area[4][4];
    Fish copy_fishes[17];
    memcpy(copy_area, area, sizeof(copy_area));
    memcpy(copy_fishes, fishes, sizeof(copy_fishes));
    
    //1. 물고기 이동
    for (int i=1; i<=16; i++) {
        if (copy_fishes[i].num == 0) continue;
        for (int d=0; d<8; d++) {
            int new_dir = copy_fishes[i].dir + d;
            if (new_dir > 8) new_dir -= 8;
            int nx = copy_fishes[i].x + dx[new_dir];
            int ny = copy_fishes[i].y + dy[new_dir];
            if (nx < 0 || nx >= 4 || ny < 0 || ny >= 4) continue;
            if (nx == shark.x && ny == shark.y) continue;
            //빈칸인 경우
            if (copy_area[nx][ny].num == 0) {
                copy_area[copy_fishes[i].x][copy_fishes[i].y].num = 0;
                copy_fishes[i].x = nx;
                copy_fishes[i].y = ny;
                copy_fishes[i].dir = new_dir;
                copy_area[nx][ny] = copy_fishes[i];
            }
            //다른 물고기랑 위치 바꾸기
            else if (copy_area[nx][ny].num > 0) {
                fish = copy_area[nx][ny];
                fish.x = copy_fishes[i].x;
                fish.y = copy_fishes[i].y;
                copy_fishes[i].x = nx;
                copy_fishes[i].y = ny;
                copy_fishes[i].dir = new_dir;
                copy_area[nx][ny] = copy_fishes[i];
                copy_area[fish.x][fish.y] = fish;
                copy_fishes[fish.num] = fish;
            }
            break;
        }
    }
    
    //2. 상어 이동
    for (int i=1; i<=3; i++) {
        int nx = shark.x + i*dx[shark.dir];
        int ny = shark.y + i*dy[shark.dir];
        if (nx < 0 || nx >= 4 || ny < 0 || ny >= 4) continue;
        if (copy_area[nx][ny].num > 0) {
            Shark n_shark;
            Fish eat_fish = copy_area[nx][ny];
            n_shark.eat = shark.eat + eat_fish.num;
            n_shark.x = nx;
            n_shark.y = ny;
            n_shark.dir = eat_fish.dir;
            copy_area[nx][ny].num = 0;
            copy_fishes[eat_fish.num].num = 0;
            hunt_fish(n_shark, copy_area, copy_fishes);
            copy_fishes[eat_fish.num].num = eat_fish.num;
            copy_area[nx][ny].num = eat_fish.num;
        }
    }
}

int main(int argc, const char * argv[]) {
    for (int x=0; x<4; x++) {
        for (int y=0; y<4; y++) {
            cin >> fish.num >> fish.dir;
            fish.x = x;
            fish.y = y;
            area[x][y] = fish;
            fishes[fish.num] = fish;
        }
    }
    
    Shark shark;
    shark.x = 0;
    shark.y = 0;
    shark.eat = area[0][0].num;
    shark.dir = area[0][0].dir;
    fishes[area[0][0].num].num = 0;
    area[0][0].num = 0;
    
    hunt_fish(shark, area, fishes);
    
    cout << max_eat << endl;
    
    return 0;
}
