//
//  main.cpp
//  BJ16236_1
//
//  Created by Hwayeon on 2021/10/20.
//

#include <iostream>
#include <queue>
#include <vector>
#include <string.h>
using namespace std;

int N;
int area[21][21] = {0, };
int visit[21][21] = {0, };
int dx[4] = {0, -1, 1, 0};
int dy[4] = {-1, 0, 0, 1};
int shark_size = 2;
int shark_x, shark_y;
int shark_eat = 0;
int sec = 0;

struct Fish{
    int x;
    int y;
    int dis;
};
struct cmp{
    bool operator()(Fish f1, Fish f2){
        if(f1.dis == f2.dis){
            if(f1.y == f2.y){
                return f1.x > f2.x;
            }
            return f1.y > f2.y;
        }
        return f1.dis > f2.dis;
    }
};
Fish fish;

void move_shark(){
    while(true){
        memset(visit, 0, sizeof(visit));
        queue<pair<pair<int,int>, int>> q;
        q.push({{shark_x, shark_y}, 0});
        visit[shark_y][shark_x] = 1;
        priority_queue<Fish, vector<Fish>, cmp> pq;
        while(!q.empty()){
            int now_x = q.front().first.first;
            int now_y = q.front().first.second;
            int dis = q.front().second;
            q.pop();
            if(area[now_y][now_x] != 0 && area[now_y][now_x] < shark_size){
                pq.push({now_x, now_y, dis});
            }
            for(int i=0; i<4; i++){
                int nx = now_x + dx[i];
                int ny = now_y + dy[i];
                if(nx<0 || nx>=N || ny<0 || ny>=N) continue;
                if(area[ny][nx] > shark_size) continue;
                if(visit[ny][nx]) continue;
                visit[ny][nx] = 1;
                q.push({{nx, ny}, dis+1});
            }
        }
        if(pq.empty()) break;
        fish = pq.top();
        shark_eat++;
        area[fish.y][fish.x] = 0;
        shark_x = fish.x;
        shark_y = fish.y;
        if(shark_eat == shark_size){
            shark_size++;
            shark_eat = 0;
        }
        sec += fish.dis;
    }
}

int main(int argc, const char * argv[]) {
    cin >> N;
    for(int y=0; y<N; y++){
        for(int x=0; x<N; x++){
            cin >> area[y][x];
            if(area[y][x] == 9){
                shark_x = x;
                shark_y = y;
                area[y][x] = 0;
            }
        }
    }
    move_shark();
    cout << sec << endl;
    return 0;
}
