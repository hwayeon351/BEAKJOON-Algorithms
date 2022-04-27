//
//  main.cpp
//  BJ21611
//
//  Created by 최화연 on 2022/04/27.
//

#include <iostream>
#include <vector>
#include <deque>
using namespace std;

int N, M;
int board[50][50] = {0, };
vector<pair<int, int>> cmd;

int dr[5] = {0, -1, 1, 0, 0};
int dc[5] = {0, 0, 0, -1, 1};
int dy[4] = {0, 1, 0, -1};
int dx[4] = {-1, 0, 1, 0};
int shark_r, shark_c;

int broken_beads[4] = {0, };

void break_beads(int d, int s) {
    for (int ss=1; ss<=s; ss++) {
        int r = shark_r + ss*dr[d];
        int c = shark_c + ss*dc[d];
        if (board[r][c] == 0) continue;
        board[r][c] = 0;
    }
}

void move_beads() {
    int r = shark_r;
    int c = shark_c;
    int d = 0;
    deque<int> dq;
    
    for (int n=1; n<=N; n++) {
        int nn = n;
        if (n == N) nn = N-1;
        for (int i=0; i<2; i++) {
            for (int j=0; j<nn; j++) {
                r += dy[d];
                c += dx[d];
                if (board[r][c] > 0) {
                    dq.push_back(board[r][c]);
                    board[r][c] = 0;
                }
            }
            if (n == N) break;
            d = (d+1)%4;
        }
    }
    
    r = shark_r;
    c = shark_c;
    d = 0;
    for (int n=1; n<=N; n++) {
        int nn = n;
        if (n == N) nn = N-1;
        for (int i=0; i<2; i++) {
            for (int j=0; j<nn; j++) {
                r += dy[d];
                c += dx[d];
                if (dq.empty()) return;
                board[r][c] = dq.front();
                dq.pop_front();
            }
            if (n == N) return;
            d = (d+1)%4;
        }
    }
}

bool explode_beads() {
    int r = shark_r;
    int c = shark_c;
    int d = 0;
    bool check = false;
    deque<pair<int, int>> dq;
    
    for (int n=1; n<=N; n++) {
        int nn = n;
        if (n == N) nn = N-1;
        for (int i=0; i<2; i++) {
            for (int j=0; j<nn; j++) {
                r += dy[d];
                c += dx[d];
                if (dq.empty() || board[dq.front().first][dq.front().second] == board[r][c]) {
                    dq.push_back({r, c});
                }
                else {
                    if (dq.size() >= 4) {
                        check = true;
                        broken_beads[board[dq.front().first][dq.front().second]] += dq.size();
                        while (!dq.empty()) {
                            int rr = dq.front().first;
                            int cc = dq.front().second;
                            dq.pop_front();
                            board[rr][cc] = 0;
                        }
                    }
                    dq.clear();
                    dq.push_back({r, c});
                }
            }
            if (n == N) break;
            d = (d+1)%4;
        }
    }
    
    return check;
}

void change_beads() {
    int r = shark_r;
    int c = shark_c;
    int d = 0;
    deque<pair<int, int>> dq;
    deque<int> new_beads;
    
    for (int n=1; n<=N; n++) {
        int nn = n;
        if (n == N) nn = N-1;
        for (int i=0; i<2; i++) {
            for (int j=0; j<nn; j++) {
                r += dy[d];
                c += dx[d];
                if (dq.empty() || board[dq.front().first][dq.front().second] == board[r][c]) {
                    dq.push_back({r, c});
                }
                else {
                    new_beads.push_back(dq.size());
                    new_beads.push_back(board[dq.front().first][dq.front().second]);
                    dq.clear();
                    dq.push_back({r, c});
                }
            }
            if (n == N) break;
            d = (d+1)%4;
        }
    }
    
    r = shark_r;
    c = shark_c;
    d = 0;
    
    for (int n=1; n<=N; n++) {
        int nn = n;
        if (n == N) nn = N-1;
        for (int i=0; i<2; i++) {
            for (int j=0; j<nn; j++) {
                r += dy[d];
                c += dx[d];
                if (!new_beads.empty()) {
                    board[r][c] = new_beads.front();
                    new_beads.pop_front();
                }
                else {
                    board[r][c] = 0;
                }
            }
            if (n == N) break;
            d = (d+1)%4;
        }
    }
}

void blizard() {
    for(int i=0; i<M; i++) {
        //1. 구슬 파괴하기
        break_beads(cmd[i].first, cmd[i].second);
        
        //2. 구슬 이동하기
        move_beads();
        
        //3. 구슬 폭발하기
        bool check = explode_beads();
        
        while (check) {
            move_beads();
            check = explode_beads();
        }
        
        //4. 구슬 변화하기
        change_beads();
    }
    
}

int main(int argc, const char * argv[]) {
    cin >> N >> M;
    for (int r=1; r<=N; r++) {
        for (int c=1; c<=N; c++) {
            cin >> board[r][c];
        }
    }
    
    for (int m=0; m<M; m++) {
        int d, s;
        cin >> d >> s;
        cmd.push_back({d, s});
    }
    
    shark_r = (N+1)/2;
    shark_c = (N+1)/2;
    blizard();
    
    cout << broken_beads[1] + 2*broken_beads[2] + 3*broken_beads[3] << endl;
    
    return 0;
}
