//
//  main.cpp
//  BJ14502
//
//  Created by Hwayeon on 2021/01/09.
//
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int N,M;
int map[8][8] = {1,};
int map_copy[8][8] = {0,};
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, -1, 0, 1};
int max_safe_area = 0;
struct location{
    int x;
    int y;
};
location loc;
vector<location> virus;

void spread_virus(){
    queue<location> q;
    int safe_area = 0;
    for(int i=0; i<virus.size(); i++){
        q.push(virus[i]);
    }
    while(!q.empty()){
        int v_x = q.front().x;
        int v_y = q.front().y;
        q.pop();
        for(int d=0; d<4; d++){
            int new_x = v_x+dx[d];
            int new_y = v_y+dy[d];
            if(new_x<0 || new_x>=N || new_y<0 || new_y>=M) continue;
            if(map_copy[new_x][new_y] == 0){
                map_copy[new_x][new_y] = 2;
                loc.x = new_x;
                loc.y = new_y;
                q.push(loc);
            }
        }
    }
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            if(map_copy[i][j]==0) safe_area++;
        }
    }
    if(safe_area > max_safe_area) max_safe_area = safe_area;
    return;
}

void install_wall(int wall){
    if(wall == 3){
        for(int i=0; i<N; i++){
            for(int j=0; j<M; j++){
                map_copy[i][j] = map[i][j];
            }
        }
        spread_virus();
        return;
    }
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            if(map[i][j] == 0){
                map[i][j] = 1;
                install_wall(wall+1);
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
            if(map[i][j] == 0) continue;
            else if(map[i][j] == 2){
                loc.x = i;
                loc.y = j;
                virus.push_back(loc);
            }
        }
    }
    install_wall(0);
    cout << max_safe_area <<endl;
    
    return 0;
}
