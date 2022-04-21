//
//  main.cpp
//  BJ15685
//
//  Created by 최화연 on 2022/04/21.
//

#include <iostream>
#include <vector>
using namespace std;

int N, M;
int office[8][8] = {0, };
vector<pair<pair<int, int>, int>> cctvs;
int hole = 0;

int dr[4] = {0, -1, 0, 1};
int dc[4] = {-1, 0, 1, 0};
vector<vector<int>> cctv[6] = {
    {},
    {{2}, {1}, {0}, {3}},
    {{0, 2}, {1, 3}},
    {{1, 2}, {2, 3}, {3, 0}, {0, 1}},
    {{0, 1, 2}, {1, 2, 3}, {2, 3, 0}, {3, 0, 1}},
    {{0, 1, 2, 3}}
};
vector<int> direction;

int answer = 64;

int operate_cctvs() {
    int visits[8][8] = {0, };
    int cnt = 0;
    for (int i=0; i<cctvs.size(); i++) {
        for (int d=0; d<cctv[cctvs[i].second][direction[i]].size(); d++) {
            int dir = cctv[cctvs[i].second][direction[i]][d];
            int r = cctvs[i].first.first + dr[dir];
            int c = cctvs[i].first.second + dc[dir];
            while (r >= 0 && r < N && c >= 0 && c < M) {
                if (office[r][c] == 6) break;
                if (office[r][c] == 0 && !visits[r][c]) {
                    visits[r][c] = 1;
                    cnt ++;
                }
                r += dr[dir];
                c += dc[dir];
            }
        }
    }
    return hole - cnt;
}

void choose_direction(int i) {
    if (i == cctvs.size()) {
        int result = operate_cctvs();
        if (answer > result) answer = result;
        return;
    }
    for (int d=0; d<cctv[cctvs[i].second].size(); d++) {
        direction.push_back(d);
        choose_direction(i+1);
        direction.pop_back();
    }
}

int main(int argc, const char * argv[]) {
    cin >> N >> M;
    for (int i=0; i<N; i++) {
        for (int j=0; j<M; j++) {
            cin >> office[i][j];
            if (office[i][j] == 0) hole ++;
            else if (office[i][j] >= 1 && office[i][j] <= 5) {
                cctvs.push_back({{i, j}, office[i][j]});
            }
        }
    }
    
    choose_direction(0);
    cout << answer << endl;
    
    return 0;
}
