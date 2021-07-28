//
//  main.cpp
//  BJ14503
//
//  Created by Hwayeon on 2021/07/29.
//

#include <iostream>
using namespace std;

int N, M;
int map[50][50] = {0,};

struct robots{
    int d;
    int x;
    int y;
};
robots robot;

//상 우 하 좌
int dx[4] = {0, 1, 0, -1};
int dy[4] = {-1, 0, 1, 0};

int clean_area = 0;

void clean(){
    while(true){
        //1. 현재 위치 청소
        if(map[robot.y][robot.x] == 0){
            map[robot.y][robot.x] = 2;
            clean_area++;
        }
        
        //2.
        bool check = false;
        for(int i=0; i<4; i++){
            int next_d = (4 + robot.d-1) % 4;
            int nx = robot.x + dx[next_d];
            int ny = robot.y + dy[next_d];
            //2-a
            if(map[ny][nx] == 0){
                robot.d = next_d;
                robot.x = nx;
                robot.y = ny;
                check = true;
                break;
            }
            //2-b
            robot.d = next_d;
        }
        if(!check){
            int back_d = (4 + robot.d-2) % 4;
            int back_x = robot.x + dx[back_d];
            int back_y = robot.y + dy[back_d];
            if(map[back_y][back_x] != 1){
                robot.x = back_x;
                robot.y = back_y;
            }
            //2-d
            else return;
        }
    }
}

int main(int argc, const char * argv[]) {
    cin >> N >> M;
    cin >> robot.y >> robot.x >> robot.d;
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            cin >> map[i][j];
        }
    }
    clean();
    cout << clean_area << endl;
    return 0;
}
