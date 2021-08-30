//
//  main.cpp
//  BJ13565.cpp
//
//  Created by Hwayeon on 2021/08/30.
//

#include <iostream>
#include <queue>
using namespace std;

int M, N;
int fiber[1000][1000] = {0, };
int visit[1000][1000] = {0, };
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, -1, 0, 1};
bool check = false;

void bfs(int s){
    queue<pair<int,int>> q;
    q.push({s, 0});
    visit[0][s] = 1;
    while(!q.empty() && !check){
        int now_x = q.front().first;
        int now_y = q.front().second;
        q.pop();
        for(int i=0; i<4; i++){
            int nx = now_x+dx[i];
            int ny = now_y+dy[i];
            if(nx<0 || nx>=N || ny<0 || ny>=M) continue;
            if(visit[ny][nx] == 1) continue;
            if(fiber[ny][nx] == 0){
                visit[ny][nx] = 1;
                q.push({nx, ny});
                if(ny == M-1){
                    check = true;
                    break;
                }
            }
        }
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
        if(fiber[0][i] == 0) bfs(i);
    }
    if(check) cout << "YES" << endl;
    else cout << "NO" << endl;

    return 0;
}
