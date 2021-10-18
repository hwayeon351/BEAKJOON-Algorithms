//
//  main.cpp
//  BJ20057_1
//
//  Created by Hwayeon on 2021/10/18.
//

#include <iostream>
using namespace std;

int N;
int A[500][500] = {0, };

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

int spread[4][10][3] = {
    //0-좌
    {{0,-2,2}, {-1,-1,10}, {0,-1,7}, {1,-1,1}, {-2,0,5}, {-1,1,10}, {0,1,7}, {1,1,1}, {0,2,2}, {-1, 0, 0}},
    //1-하
    {{-1,-1,1}, {1,-1,1}, {-2,0,2}, {-1,0,7}, {1,0,7}, {2,0,2}, {-1,1,10}, {1,1,10}, {0,2,5}, {0,1,0}},
    //2-우
    {{0,-2,2}, {-1,-1,1}, {0,-1,7}, {1,-1,10}, {2,0,5}, {-1,1,1}, {0,1,7}, {1,1,10}, {0,2,2}, {1,0,0}},
    //3-상
    {{0,-2,5}, {-1,-1,10}, {1,-1,10}, {-2,0,2}, {-1,0,7}, {1,0,7}, {2,0,2}, {-1,1,1}, {1,1,1}, {0,-1,0}}
};

int tx, ty;
int gone = 0;

void spread_sand(int tx, int ty, int d){
    int ay = A[ty][tx];
    int total_spread = 0;
    A[ty][tx] = 0;
    int x, y, p, sand;
    for(int i=0; i<9; i++){
        x = tx + spread[d][i][0];
        y = ty + spread[d][i][1];
        p = spread[d][i][2];
        sand = ay*(0.01*p);
        if(x<0 || x>=N || y<0 || y>=N) gone += sand;
        else A[y][x] += sand;
        total_spread += sand;
    }
    x = tx + spread[d][9][0];
    y = ty + spread[d][9][1];
    if(x<0 || x>=N || y<0 || y>=N) gone += (ay-total_spread);
    else A[y][x] += (ay-total_spread);
}

void move_tornado(){
    int d = 0;
    for(int dis=1; dis<=N; dis++){
        int ndis = dis;
        for(int i=0; i<2; i++){
            if(dis == N) ndis = N-1;
            for(int j=0; j<ndis; j++){
                tx += dx[d];
                ty += dy[d];
                spread_sand(tx, ty, d);
            }
            if(dis == N) return;
            d = (d+1)%4;
        }
    }
}

int main(int argc, const char * argv[]) {
    cin >> N;
    for(int y=0; y<N; y++){
        for(int x=0; x<N; x++){
            cin >> A[y][x];
        }
    }
    tx = N/2;
    ty = N/2;
    move_tornado();
    cout << gone << endl;
    
    return 0;
}
