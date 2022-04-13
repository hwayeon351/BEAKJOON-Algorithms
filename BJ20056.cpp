//
//  main.cpp
//  BJ20056
//
//  Created by 최화연 on 2022/04/13.
//

#include <iostream>
#include <vector>
using namespace std;

int N, M, K;

struct Fireball {
    int r;
    int c;
    int m;
    int s;
    int d;
};
Fireball fireball;

vector<Fireball> fireballs;
vector<Fireball> board[50][50];

int dx[8] = {0, 1, 1, 1, 0, -1, -1, -1};
int dy[8] = {-1, -1, 0, 1, 1, 1, 0, -1};


void move_fireballs() {
    for(int i=0; i<K; i++) {
        //초기화
        for(int r=0; r<N; r++) {
            for(int c=0; c<N; c++) {
                board[r][c].clear();
            }
        }
        
        //1.
        for (int j=0; j<fireballs.size(); j++) {
            int nr = fireballs[j].r + dy[fireballs[j].d] * (fireballs[j].s % N);
            int nc = fireballs[j].c + dx[fireballs[j].d] * (fireballs[j].s % N);
            if (nr < 0) nr += N;
            if (nr >= N) nr -= N;
            if (nc < 0) nc += N;
            if (nc >= N) nc -= N;
            fireballs[j].r = nr;
            fireballs[j].c = nc;
            board[nr][nc].push_back(fireballs[j]);
        }
        
        //2.
        fireballs.clear();
        for(int r=0; r<N; r++) {
            for(int c=0; c<N; c++) {
                if (board[r][c].size() == 1) {
                    fireballs.push_back(board[r][c].front());
                }
                else if (board[r][c].size() >= 2) {
                    int sum_m = 0;
                    int sum_s = 0;
                    bool check_d = true;
                    int d = board[r][c].front().d % 2;
                    for (int j=0; j<board[r][c].size(); j++) {
                        sum_m += board[r][c][j].m;
                        sum_s += board[r][c][j].s;
                        if (board[r][c][j].d % 2 != d) check_d = false;
                    }
                    int m = sum_m/5;
                    int s = sum_s/board[r][c].size();
                    if (m == 0) continue;
                    if (check_d) {
                        for (int d=0; d<=6; d+=2) {
                            fireballs.push_back({r, c, m, s, d});
                        }
                    }
                    else {
                        for (int d=1; d<=7; d+=2) {
                            fireballs.push_back({r, c, m, s, d});
                        }
                    }
                }
            }
        }
    }
}

int get_fireballs_m_sum() {
    int sum = 0;
    for(int i=0; i<fireballs.size(); i++) {
        sum += fireballs[i].m;
    }
    return sum;
}


int main(int argc, const char * argv[]) {
    cin >> N >> M >> K;
    for (int i=0; i<M; i++) {
        cin >> fireball.r >> fireball.c >> fireball.m >> fireball.s >> fireball.d;
        fireball.r--;
        fireball.c--;
        fireballs.push_back(fireball);
    }
    
    move_fireballs();
    cout << get_fireballs_m_sum() << endl;
    
    return 0;
}
