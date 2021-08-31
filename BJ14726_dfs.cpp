//
//  main.cpp
//  BJ14726
//
//  Created by Hwayeon on 2021/08/31.
//

#include <iostream>
#include <queue>
using namespace std;

int M, N;
int sign[250][250] = {0, };
int visit[250][250] = {0, };
int letters = 0;

int dx[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
int dy[8] = {-1, -1, -1, 0, 0, 1, 1, 1};

void dfs(int x, int y){
    for(int i=0; i<8; i++){
        int nx = x+dx[i];
        int ny = y+dy[i];
        if(nx<0 || nx>=N || ny<0 || ny>=M) continue;
        if(visit[ny][nx]) continue;
        if(sign[ny][nx] == 1){
            visit[ny][nx] = 1;
            dfs(nx, ny);
        }
    }
}

int main(int argc, const char * argv[]) {
    cin >> M >> N;
    for(int i=0; i<M; i++){
        for(int j=0; j<N; j++){
            cin >> sign[i][j];
        }
    }
    for(int i=0; i<M; i++){
        for(int j=0; j<N; j++){
            if(sign[i][j] == 1 && visit[i][j] == 0){
                visit[i][j] = 1;
                dfs(j, i);
                letters ++;
            }
        }
    }
    cout << letters << endl;
    return 0;
}
