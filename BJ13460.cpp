//
//  main.cpp
//  BJ13460_1
//
//  Created by Hwayeon on 2021/10/17.
//

#include <iostream>
#include <queue>
using namespace std;

int N, M;
char board[10][10] = {'.',};
int visit[10][10][10][10] = {0, };

struct State{
    int rx;
    int ry;
    int bx;
    int by;
    int cnt = 0;
};
State st;

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, -1, 0, 1};
queue<State> q;

void move(int& x, int& y, int& dis, int& d){
    while(board[y+dy[d]][x+dx[d]] != '#' && board[y][x] != 'O'){
        x += dx[d];
        y += dy[d];
        dis ++;
    }
}

void bfs(){
    while(!q.empty()){
        int rx = q.front().rx;
        int ry = q.front().ry;
        int bx = q.front().bx;
        int by = q.front().by;
        int cnt = q.front().cnt;
        q.pop();
        if(cnt >= 10) break;
        for(int d=0; d<4; d++){
            int nrx = rx;
            int nry = ry;
            int r_dis = 0;
            int nbx = bx;
            int nby = by;
            int b_dis = 0;
            int ncnt = cnt+1;
            move(nrx, nry, r_dis, d);
            move(nbx, nby, b_dis, d);
            if(board[nby][nbx] == 'O') continue;
            if(board[nry][nrx] == 'O'){
                cout << ncnt << endl;
                return;
            }
            if(nrx == nbx && nry == nby){
                if(r_dis > b_dis){
                    nrx -= dx[d];
                    nry -= dy[d];
                }
                else{
                    nbx -= dx[d];
                    nby -= dy[d];
                }
            }
            if(visit[nrx][nry][nbx][nby]) continue;
            visit[nrx][nry][nbx][nby] = 1;
            q.push({nrx, nry, nbx, nby, ncnt});
        }
    }
    cout << -1 << endl;
}

int main(int argc, const char * argv[]) {
    cin >> N >> M;
    for(int y=0; y<N; y++){
        for(int x=0; x<M; x++){
            cin >> board[y][x];
            if(board[y][x] == 'R'){
                st.rx = x;
                st.ry = y;
                board[y][x] = '.';
            }
            else if(board[y][x] == 'B'){
                st.bx = x;
                st.by = y;
                board[y][x] = '.';
            }
        }
    }
    q.push(st);
    visit[st.rx][st.ry][st.bx][st.by] = 1;
    bfs();
    
    return 0;
}
