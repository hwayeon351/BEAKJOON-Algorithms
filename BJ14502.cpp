//
//  main.cpp
//  BJ14502
//
//  Created by Hwayeon on 2021/07/27.
//

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int N, M;
int map[8][8] = {0,};
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, -1, 0, 1};
int cmp_map[8][8] = {0,};
int answer = 0;
vector<pair<int, int>> virus;

void copy_map(){
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            cmp_map[i][j] = map[i][j];
        }
    }
}

void spread_virus(){
    queue<pair<int, int>> q;
    for(int i=0; i<virus.size(); i++){
        q.push(virus[i]);
    }
    while(!q.empty()){
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        for(int i=0; i<4; i++){
            int nx = x+dx[i];
            int ny = y+dy[i];
            if(nx<0 || nx>=M || ny<0 || ny>=N) continue;
            if(cmp_map[ny][nx] == 0){
                cmp_map[ny][nx] = 2;
                q.push(make_pair(nx, ny));
            }
        }
    }
}

void count_safe_area(){
    int safe_area = 0;
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            if(cmp_map[i][j] == 0) safe_area++;
        }
    }
    if(answer < safe_area) answer = safe_area;
}

void build_wall(int cnt){
    if(cnt == 3){
        //spread virus
        copy_map();
        spread_virus();
        count_safe_area();
        return;
    }
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            if(map[i][j] == 0){
                map[i][j] = 1;
                build_wall(cnt+1);
                map[i][j] = 0;
            }
        }
    }
}

int main(int argc, const char * argv[]) {
    cin >> N >> M;
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            cin >> map[i][j];
            if(map[i][j] == 2){
                virus.push_back(make_pair(j, i));
            }
        }
    }
    build_wall(0);
    cout << answer << endl;
    return 0;
}
