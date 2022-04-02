//
//  main.cpp
//  BJ14502
//
//  Created by 최화연 on 2022/04/02.
//

#include <iostream>
#include <vector>
#include <queue>
#include <string.h>
using namespace std;

int max_safe_num = 0;
int N, M;
int lab[8][8] = {0, };
int copy_lab[8][8] = {0, };
vector<pair<int, int>> virus;
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, -1, 0, 1};

void spread_virus(int sy, int sx) {
    queue<pair<int, int>> q;
    q.push({sx, sy});
    while(!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        for(int i=0; i<4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx < 0 || nx >= M || ny < 0 || ny >= N) continue;
            if (copy_lab[ny][nx] == 0) {
                copy_lab[ny][nx] = 2;
                q.push({nx, ny});
            }
        }
    }
}

int get_safe_area() {
    int cnt = 0;
    for(int i=0; i<N; i++) {
        for(int j=0; j<M; j++) {
            if (copy_lab[i][j] == 0) {
                cnt ++;
            }
        }
    }
    return cnt;
}

void build_walls(int x, int y, int cnt) {
    if (cnt == 3) {
        memcpy(copy_lab, lab, sizeof(copy_lab));
        for(int i=0; i<virus.size(); i++) {
            spread_virus(virus[i].first, virus[i].second);
        }
        int safe_area = get_safe_area();
        if (safe_area > max_safe_num) max_safe_num = safe_area;
        return;
    }
    for(int i=y; i<N; i++) {
        if(i > y) x = 0;
        for(int j=x; j<M; j++) {
            if (lab[i][j] == 0) {
                lab[i][j] = 1;
                build_walls((j+1)%M, i, cnt+1);
                lab[i][j] = 0;
            }
        }
    }
}

int main(int argc, const char * argv[]) {
    cin >> N >> M;
    for(int i=0; i<N; i++) {
        for(int j=0; j<M; j++) {
            cin >> lab[i][j];
            if (lab[i][j] == 2) {
                virus.push_back({i, j});
            }
        }
    }
    
    build_walls(0, 0, 0);
    cout << max_safe_num << endl;
    
    return 0;
}
