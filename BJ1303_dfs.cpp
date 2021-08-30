//
//  main.cpp
//  BJ1303
//
//  Created by Hwayeon on 2021/08/30.
//

#include <iostream>
#include <math.h>
using namespace std;

int N, M;
int blue, white = 0;
char ground[100][100] = {'W', };
int visit[100][100] = {0, };

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, -1, 0, 1};
int army = 0;

void dfs(int x, int y){
    for(int i=0; i<4; i++){
        int nx = x+dx[i];
        int ny = y+dy[i];
        if(nx<0 || nx>=N || ny<0 || ny>=M) continue;
        if(visit[ny][nx]) continue;
        if(ground[ny][nx] != ground[y][x]) continue;
        visit[ny][nx] = 1;
        dfs(nx, ny);
        army++;
    }
}

int main(int argc, const char * argv[]) {
    cin >> N >> M;
    for(int i=0; i<M; i++){
        for(int j=0; j<N; j++){
            scanf("%1s", &ground[i][j]);
        }
    }
    for(int i=0; i<M; i++){
        for(int j=0; j<N; j++){
            if(visit[i][j] == 0){
                visit[i][j] = 1;
                army = 1;
                dfs(j, i);
                if(ground[i][j] == 'B') blue += pow(army, 2);
                else white += pow(army, 2);
            }
        }
    }
    cout << white << " " << blue << endl;
    return 0;
}
