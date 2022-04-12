//
//  main.cpp
//  BJ17142
//
//  Created by 최화연 on 2022/04/12.
//

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

int lab[50][50] = {0, };
int copy_lab[50][50] = {0, };
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, -1, 0, 1};

int N, M;
int hole_cnt = 0;

vector<pair<int, int>> virus;
vector<pair<int, int>> active_virus;
int min_sec = -1;

void spread_virus() {
    memcpy(copy_lab, lab, sizeof(copy_lab));
    queue<pair<pair<int, int>, int>> q;
    for(int i=0; i<M; i++) {
        q.push({{active_virus[i].first, active_virus[i].second}, 0});
        copy_lab[active_virus[i].second][active_virus[i].first] = 3;
    }
    int hole = 0;
    
    while(!q.empty()) {
        int x = q.front().first.first;
        int y = q.front().first.second;
        int sec = q.front().second;
        q.pop();
        
        for(int d=0; d<4; d++) {
            int nx = x + dx[d];
            int ny = y + dy[d];
            if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
            //비활성화 바이러스인 경우,
            if (copy_lab[ny][nx] == 2) {
                copy_lab[ny][nx] = 3;
                q.push({{nx, ny}, sec+1});
            }
            //빈 칸인 경우,
            else if (copy_lab[ny][nx] == 0) {
                copy_lab[ny][nx] = 3;
                q.push({{nx, ny}, sec+1});
                hole ++;
                if (hole == hole_cnt) {
                    if (min_sec == -1 || min_sec > sec+1) {
                        min_sec = sec+1;
                    }
                    return;
                }
            }
        }
    }
}

void pick_M_virus(int i, int cnt) {
    if (cnt == M) {
        spread_virus();
        return;
    }
    
    for (int j=i; j<virus.size(); j++) {
        active_virus.push_back({virus[j].first, virus[j].second});
        pick_M_virus(j+1, cnt+1);
        active_virus.pop_back();
    }
    
}

int main(int argc, const char * argv[]) {
    cin >> N >> M;
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            cin >> lab[i][j];
            if (lab[i][j] == 0) {
                hole_cnt ++;
            }
            else if (lab[i][j] == 2) {
                virus.push_back({j, i});
            }
        }
    }
    if (hole_cnt == 0) cout << 0 << endl;
    else {
        pick_M_virus(0, 0);
        cout << min_sec << endl;
    }

    return 0;
}
