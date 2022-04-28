//
//  main.cpp
//  BJ17837
//
//  Created by 최화연 on 2022/04/28.
//

#include <iostream>
#include <deque>
#include <vector>
using namespace std;

int N, K;
struct Horse {
    int num = 0;
    int r;
    int c;
    int d;
};
Horse horse;

int board[13][13] = {0, };
vector<Horse> chess[13][13];
Horse horses[11];

int dr[5] = {0, 0, 0, -1, 1};
int dc[5] = {0, 1, -1, 0, 0};
int opposite[5] = {0, 2, 1, 4, 3};

int play_game() {
    int turn = 0;
    while (turn < 1000) {
        turn ++;
        for (int i=1; i<=K; i++) {
            deque<Horse> dq;
            int k = -1;
            for (int j=0; j<chess[horses[i].r][horses[i].c].size(); j++) {
                if (chess[horses[i].r][horses[i].c][j].num == i) {
                    k = j;
                    break;
                }
            }
            int size = chess[horses[i].r][horses[i].c].size();
            for (int j=0; j<size-k; j++) {
                dq.push_front(chess[horses[i].r][horses[i].c].back());
                chess[horses[i].r][horses[i].c].pop_back();
            }
            
            int nr = horses[i].r + dr[horses[i].d];
            int nc = horses[i].c + dc[horses[i].d];
            
            //파란색 칸이거나 격자를 벗어난 경우,
            if (nr < 1 || nr > N || nc < 1 || nc > N || board[nr][nc] == 2) {
                dq[0].d = opposite[dq[0].d];
                nr += 2*dr[dq[0].d];
                nc += 2*dc[dq[0].d];
                //파란색 칸이거나 격자를 벗어난 경우, 이동하지 않는다
                if (nr < 1 || nr > N || nc < 1 || nc > N || board[nr][nc] == 2) {
                    while (!dq.empty()) {
                        Horse h = dq.front();
                        horses[h.num] = h;
                        dq.pop_front();
                        chess[h.r][h.c].push_back(h);
                    }
                }
                //이동한다
                else {
                    if (chess[nr][nc].size() + dq.size() >= 4) return turn;
                    //빨간색인 경우,
                    if (board[nr][nc] == 1) {
                        while (!dq.empty()) {
                            Horse h = dq.back();
                            h.r = nr;
                            h.c = nc;
                            horses[h.num] = h;
                            dq.pop_back();
                            chess[nr][nc].push_back(h);
                        }
                    }
                    //흰색인 경우,
                    {
                        while (!dq.empty()) {
                            Horse h = dq.front();
                            h.r = nr;
                            h.c = nc;
                            horses[h.num] = h;
                            dq.pop_front();
                            chess[nr][nc].push_back(h);
                        }
                    }
                }
            }
            
            //빨간색 칸인 경우,
            else if (board[nr][nc] == 1) {
                if (chess[nr][nc].size() + dq.size() >= 4) return turn;
                while (!dq.empty()) {
                    Horse h = dq.back();
                    h.r = nr;
                    h.c = nc;
                    horses[h.num] = h;
                    dq.pop_back();
                    chess[nr][nc].push_back(h);
                }
            }
            
            //흰색인 경우,
            else {
                if (chess[nr][nc].size() + dq.size() >= 4) return turn;
                while (!dq.empty()) {
                    Horse h = dq.front();
                    h.r = nr;
                    h.c = nc;
                    horses[h.num] = h;
                    dq.pop_front();
                    chess[nr][nc].push_back(h);
                }
                
            }
        }
    }
    
    return -1;
}

int main(int argc, const char * argv[]) {
    cin >> N >> K;
    for (int r=1; r<=N; r++) {
        for (int c=1; c<=N; c++) {
            cin >> board[r][c];
        }
    }
    
    for (int k=1; k<=K; k++) {
        horse.num = k;
        cin >> horse.r >> horse.c >> horse.d;
        chess[horse.r][horse.c].push_back(horse);
        horses[k] = horse;
    }
    
    cout << play_game() << endl;
    
    return 0;
}
