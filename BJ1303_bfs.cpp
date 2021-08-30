//
//  main.cpp
//  BJ1303
//
//  Created by Hwayeon on 2021/08/30.
//

#include <iostream>
#include <queue>
#include <math.h>
using namespace std;

int N, M;
int blue, white = 0;
char ground[100][100] = {'W', };
int visit[100][100] = {0, };

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, -1, 0, 1};

void bfs(int x, int y){
    queue<pair<int, int>> q;
    q.push({x, y});
    visit[y][x] = 1;
    int cnt = 0;
    
    while(!q.empty()){
        int now_x = q.front().first;
        int now_y = q.front().second;
        cnt ++;
        q.pop();
        for(int i=0; i<4; i++){
            int nx = now_x+dx[i];
            int ny = now_y+dy[i];
            if(nx<0 || nx>=N || ny<0 || ny>=M) continue;
            if(visit[ny][nx] == 1) continue;
            if(ground[ny][nx] != ground[now_y][now_x]) continue;
            q.push({nx, ny});
            visit[ny][nx] = 1;
        }
    }
    if(ground[y][x] == 'B') blue += pow(cnt, 2);
    else white += pow(cnt, 2);
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
                bfs(j, i);
            }
        }
    }
    cout << white << " " << blue << endl;
    return 0;
}
