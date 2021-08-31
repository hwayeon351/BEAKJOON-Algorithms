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

void bfs(int x, int y){
    queue<pair<int, int>> q;
    q.push({x, y});
    visit[y][x] = 1;
    while(!q.empty()){
        int now_x = q.front().first;
        int now_y = q.front().second;
        q.pop();
        for(int i=0; i<8; i++){
            int nx = now_x + dx[i];
            int ny = now_y + dy[i];
            if(nx<0 || nx>=N || ny<0 || ny>=M) continue;
            if(visit[ny][nx] == 1) continue;
            if(sign[ny][nx] == 1){
                visit[ny][nx] = 1;
                q.push({nx, ny});
            }
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
                bfs(j, i);
                letters ++;
            }
        }
    }
    cout << letters << endl;
    return 0;
}
