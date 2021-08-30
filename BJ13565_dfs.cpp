//
//  main.cpp
//  BJ13565.cpp
//
//  Created by Hwayeon on 2021/08/30.
//

#include <iostream>
#include <string.h>
using namespace std;

int M, N;
int fiber[1000][1000] = {0, };
int visit[1000][1000] = {0, };
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, -1, 0, 1};
bool check = false;

void dfs(int x, int y){
    if(y == M-1){
        check = true;
        return;
    }
    if(check) return;
    for(int i=0; i<4; i++){
        int nx = x+dx[i];
        int ny = y+dy[i];
        if(nx<0 || nx>= N || ny<0 || ny>=M) continue;
        if(visit[ny][nx]) continue;
        if(fiber[ny][nx]) continue;
        visit[ny][nx] = 1;
        dfs(nx, ny);
    }
}

int main(int argc, const char * argv[]) {
    cin >> M >> N;
    for(int i=0; i<M; i++){
        for(int j=0; j<N; j++){
            scanf("%1d", &fiber[i][j]);
        }
    }
    for(int i=0; i<N; i++){
        if(check) break;
        memset(visit, 0, sizeof(visit));
        if(!fiber[0][i]) {
            visit[0][i] = 1;
            dfs(i, 0);
        }
    }
    if(check) cout << "YES" << endl;
    else cout << "NO" << endl;
    return 0;
}
