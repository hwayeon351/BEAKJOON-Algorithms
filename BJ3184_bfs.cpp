//
//  main.cpp
//  BJ3184_bfs
//
//  Created by Hwayeon on 2021/08/24.
//

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int R, C;
char yard[250][250] = {'.',};
int visit[250][250] = {0, };
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, -1, 0, 1};
vector<pair<int, int>> wolf, sheep;
int wolves = 0;
int sheeps = 0;

void bfs(int sx, int sy){
    wolf.clear();
    sheep.clear();
    visit[sy][sx] = 1;
    if(yard[sy][sx] == 'v') wolf.push_back({sx, sy});
    else if(yard[sy][sx] == 'o') sheep.push_back({sx, sy});
    queue<pair<int, int>> q;
    q.push({sx, sy});
    while(!q.empty()){
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        for(int i=0; i<4; i++){
            int nx = x+dx[i];
            int ny = y+dy[i];
            if(nx<0 || nx>=C || ny<0 || ny>=R) continue;
            if(visit[ny][nx] == 1) continue;
            if(yard[ny][nx] == '#') continue;
            else if(yard[ny][nx] == 'v') wolf.push_back({nx, ny});
            else if(yard[ny][nx] == 'o') sheep.push_back({nx, ny});
            q.push({nx, ny});
            visit[ny][nx] = 1;
        }
    }
}

int main(int argc, const char * argv[]) {
    cin >> R >> C;
    for(int i=0; i<R; i++){
        for(int j=0; j<C; j++){
            cin >> yard[i][j];
        }
    }
    for(int i=0; i<R; i++){
        for(int j=0; j<C; j++){
            if(yard[i][j]!='#' && visit[i][j]==0){
                bfs(j, i);
                if(sheep.size() > wolf.size()) sheeps += sheep.size();
                else wolves += wolf.size();
            }
        }
    }
    cout << sheeps << " " << wolves << endl;
    return 0;
}
