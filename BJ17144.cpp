//
//  main.cpp
//  BJ17144
//
//  Created by 최화연 on 2022/04/15.
//

#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int R, C, T;
int room[50][50] = {0, };
int copy_room[50][50] = {0, };
int dc[4] = {-1, 0, 1, 0};
int dr[4] = {0, -1, 0, 1};

struct Aircleaner {
    vector<pair<int, int>> locs;
};
Aircleaner aircleaner;


void spread_dust() {
    memcpy(copy_room, room, sizeof(copy_room));
    for (int r=0; r<R; r++) {
        for (int c=0; c<C; c++) {
            if (copy_room[r][c] > 0) {
                //dusts.push_back({r, c});
                int cnt = 0;
                int spread_dust = copy_room[r][c]/5;
                for(int d=0; d<4; d++) {
                    int nr = r + dr[d];
                    int nc = c + dc[d];
                    if (nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
                    if ((nr == aircleaner.locs[0].first and nc == aircleaner.locs[0].second) || (nr == aircleaner.locs[1].first and nc == aircleaner.locs[1].second)) continue;
                    room[nr][nc] += spread_dust;
                    cnt ++;
                }
                room[r][c] -= cnt*spread_dust;
            }
        }
    }
}

void clean_air() {
    //위쪽 공기 청정기
    for (int r=aircleaner.locs[0].first-2; r>=0; r--) {
        room[r+1][0] = room[r][0];
    }
    for (int c=1; c<C; c++) {
        room[0][c-1] = room[0][c];
    }
    for (int r=0; r<aircleaner.locs[0].first; r++) {
        room[r][C-1] = room[r+1][C-1];
    }
    for (int c=C-1; c>=2; c--) {
        room[aircleaner.locs[0].first][c] = room[aircleaner.locs[0].first][c-1];
    }
    room[aircleaner.locs[0].first][1] = 0;
    
    //아래쪽 공기 청정기
    for (int r=aircleaner.locs[1].first+2; r<R; r++) {
        room[r-1][0] = room[r][0];
    }
    for (int c=1; c<C; c++) {
        room[R-1][c-1] = room[R-1][c];
    }
    for (int r=R-2; r>=aircleaner.locs[1].first; r--) {
        room[r+1][C-1] = room[r][C-1];
    }
    for (int c=C-1; c>=2; c--) {
        room[aircleaner.locs[1].first][c] = room[aircleaner.locs[1].first][c-1];
    }
    room[aircleaner.locs[1].first][1] = 0;
}

void play_aircleaner() {
    for (int t=0; t<T; t++) {
        //미세먼지 확산
        spread_dust();
        
        //공기청정기 작동
        clean_air();
    }
}

int get_dust() {
    int dust = 0;
    for (int r=0; r<R; r++) {
        for (int c=0; c<C; c++) {
            dust += room[r][c];
        }
    }
    return dust;
}

int main(int argc, const char * argv[]) {
    cin >> R >> C >> T;
    for (int r=0; r<R; r++) {
        for (int c=0; c<C; c++) {
            cin >> room[r][c];
            if (room[r][c] == -1) {
                aircleaner.locs.push_back({r, c});
                room[r][c] = 0;
            }
        }
    }
    
    play_aircleaner();
    cout << get_dust() << endl;
    
    return 0;
}
