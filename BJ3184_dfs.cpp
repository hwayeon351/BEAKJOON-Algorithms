//
//  main.cpp
//  BJ3184
//
//  Created by Hwayeon on 2021/08/24.
//

#include <iostream>
#include <vector>
using namespace std;

int R, C;
char yard[250][250] = {'.',};
int visit[250][250] = {0,};
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, -1, 0, 1};
vector<pair<int, int>> wolf, sheep;
int sheeps = 0;
int wolves = 0;

void dfs(int x, int y){
    for(int i=0; i<4; i++){
        int nx = x+dx[i];
        int ny = y+dy[i];
        if(nx<0 || nx>=C || ny<0 || ny>=R) continue;
        if(visit[ny][nx] == 1) continue;
        if(yard[ny][nx] == '#') continue;
        else if(yard[ny][nx] == 'v'){
            wolf.push_back({nx, ny});
        }
        else if(yard[ny][nx] == 'o'){
            sheep.push_back({nx, ny});
        }
        visit[ny][nx] = 1;
        dfs(nx, ny);
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
            if(yard[i][j] != '#' && visit[i][j] == 0){
                wolf.clear();
                sheep.clear();
                visit[i][j] = 1;
                if(yard[i][j] == 'v') wolf.push_back({j, i});
                else if(yard[i][j] == 'o') sheep.push_back({j, i});
                dfs(j, i);
                if(wolf.size() < sheep.size()){
                    sheeps += sheep.size();
                }
                else{
                    wolves += wolf.size();
                }
            }
        }
    }
    cout << sheeps << " " << wolves << endl;
    return 0;
}
