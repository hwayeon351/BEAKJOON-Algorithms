//
//  main.cpp
//  BJ14503
//
//  Created by Hwayeon on 2021/01/10.
//
#include <iostream>
#include <cmath>
using namespace std;

int N, M, d, r_x, r_y;
int dx[4] = {0, 1, 0, -1};
int dy[4] = {-1, 0, 1, 0};
int back[4] = {2, 3, 0, 1};
int room[50][50];
bool clean[50][50] = {false,};
int cleaned_area = 0;

void cal_clean_area(){
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            if(clean[i][j]) cleaned_area++;
        }
    }
}

void clean_room(int x, int y, int dir){
    if(clean[y][x] == false) clean[y][x] = true;
    for(int i=1; i<=4; i++){
        int left = (dir-i+4)%4;
        int new_x = x+dx[left];
        int new_y = y+dy[left];
        if(room[new_y][new_x] == 0 && clean[new_y][new_x] == false){
            clean_room(new_x, new_y, left);
            return;
        }
    }
    if(room[y+dy[back[dir]]][x+dx[back[dir]]] == 0) clean_room(x+dx[back[dir]], y+dy[back[dir]], dir);
    else if(room[y+dy[back[dir]]][x+dx[back[dir]]] == 1) cal_clean_area();
}

int main(int argc, const char * argv[]) {
    cin >> N >> M;
    cin >> r_y >> r_x >> d;
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            cin >> room[i][j];
        }
    }
    clean_room(r_x, r_y, d);
    cout << cleaned_area << endl;
    
    return 0;
}
