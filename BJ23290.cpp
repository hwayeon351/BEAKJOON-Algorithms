//
//  main.cpp
//  BJ23290
//
//  Created by 최화연 on 2022/04/27.
//

#include <iostream>
#include <vector>
using namespace std;

int M, S;

struct Fish {
    int r;
    int c;
    int dir;
};
Fish fish;

struct Space {
    int smell = 0;
    vector<Fish> fishes;
};
Space board[5][5];

int shark_x, shark_y;

int dr[9] = {0, 0, -1, -1, -1, 0, 1, 1, 1};
int dc[9] = {0, -1, -1, 0, 1, 1, 1, 0, -1};
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, -1, 0, 1};

void practice() {
    for (int s=0; s<S; s++) {
        //1. 복제 마법 시전
        vector<Fish> copied_fishes;
        vector<Fish> fishes;
        for (int r=1; r<=4; r++) {
            for (int c=1; c<=4; c++) {
                for (int i=0; i<board[r][c].fishes.size(); i++) {
                    copied_fishes.push_back(board[r][c].fishes[i]);
                    fishes.push_back(board[r][c].fishes[i]);
                }
                board[r][c].fishes.clear();
            }
        }
        
        //2. 물고기 한 칸 이동
        for (int i=0; i<fishes.size(); i++) {
            for (int d=0; d<8; d++) {
                int new_dir = fishes[i].dir - d;
                if (new_dir <= 0) new_dir += 8;
                int nr = fishes[i].r + dr[new_dir];
                int nc = fishes[i].c + dc[new_dir];
                if (nr < 1 || nr > 4 || nc < 1 || nc > 4) continue;
                if (shark_x == nr && shark_y == nc) continue;
                if (board[nr][nc].smell > 0) continue;
                fishes[i].r = nr;
                fishes[i].c = nc;
                fishes[i].dir = new_dir;
                break;
            }
            board[fishes[i].r][fishes[i].c].fishes.push_back(fishes[i]);
        }
        
        //3. 상어 3칸 이동
        int max_fish_cnt = -1;
        int d[3] = {0, };
        for (int d1=0; d1<4; d1++) {
            int fish_cnt1 = 0;
            int nx1 = shark_x + dx[d1];
            int ny1 = shark_y + dy[d1];
            if (nx1 < 1 || nx1 > 4 || ny1 < 1 || ny1 > 4) continue;
            fish_cnt1 = board[nx1][ny1].fishes.size();
            
            for (int d2=0; d2<4; d2++) {
                int nx2 = nx1 + dx[d2];
                int ny2 = ny1 + dy[d2];
                int fish_cnt2 = 0;
                if (nx2 < 1 || nx2 > 4 || ny2 < 1 || ny2 > 4) continue;
                if (!(nx2 == nx1 && ny2 == ny1)) fish_cnt2 = board[nx2][ny2].fishes.size();
                
                for (int d3=0; d3<4; d3++) {
                    int nx3 = nx2 + dx[d3];
                    int ny3 = ny2 + dy[d3];
                    int fish_cnt3 = 0;
                    if (nx3 < 1 || nx3 > 4 || ny3 < 1 || ny3 > 4) continue;
                    if ((!(nx3 == nx1 && ny3 == ny1)) && (!(nx3 == nx2 && ny3 == ny2))) fish_cnt3 = board[nx3][ny3].fishes.size();
                    int total_cnt = fish_cnt1+fish_cnt2+fish_cnt3;
                    if (total_cnt > max_fish_cnt) {
                        max_fish_cnt = total_cnt;
                        d[0] = d1;
                        d[1] = d2;
                        d[2] = d3;
                    }
                }
            }
        }
        
        //4. 물고기 냄새 사라짐
        for (int r=1; r<=4; r++) {
            for (int c=1; c<=4; c++) {
                if (board[r][c].smell == 0) continue;
                board[r][c].smell --;
            }
        }
        
        for (int i=0; i<3; i++) {
            shark_x += dx[d[i]];
            shark_y += dy[d[i]];
            if (board[shark_x][shark_y].fishes.size() > 0) {
                board[shark_x][shark_y].fishes.clear();
                board[shark_x][shark_y].smell = 2;
            }
        }
                
        //5. 복제 마법 완료
        for (int i=0; i<copied_fishes.size(); i++) {
            board[copied_fishes[i].r][copied_fishes[i].c].fishes.push_back(copied_fishes[i]);
        }
    }
}

int get_fish_cnt() {
    int cnt = 0;
    
    for (int r=1; r<=4; r++) {
        for (int c=1; c<=4; c++) {
            cnt += board[r][c].fishes.size();
        }
    }
    
    return cnt;
}

int main(int argc, const char * argv[]) {
    cin >> M >> S;
    for (int m=0; m<M; m++) {
        cin >> fish.r >> fish.c >> fish.dir;
        board[fish.r][fish.c].fishes.push_back(fish);
    }
    cin >> shark_x >> shark_y;
    
    practice();
    
    cout << get_fish_cnt() << endl;
    
    return 0;
}
