//
//  main.cpp
//  BJ13460
//
//  Created by Hwayeon on 2021/01/16.
//
#include <iostream>
#include <queue>
using namespace std;

int N, M;
char board[10][10];
bool visit[10][10][10][10] = {false, };
int answer = 11;
struct location{
    int x;
    int y;
};
location r_loc, b_loc, h_loc;
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, -1, 0, 1};

void escape_bead(){
    int cnt = 0;
    queue<pair<pair<location, location>, int>> q;
    q.push(make_pair(make_pair(r_loc, b_loc), cnt));
    while(cnt < 10 && !q.empty()){
        location r = q.front().first.first;
        location b = q.front().first.second;
        cnt = q.front().second;
        visit[r.y][r.x][b.y][b.x] = true;
        q.pop();
        for(int i=0; i<4; i++){
            r_loc.x = r.x;
            r_loc.y = r.y;
            b_loc.x = b.x;
            b_loc.y = b.y;
            int new_rx = r.x + dx[i];
            int new_ry = r.y + dy[i];
            int new_bx = b.x + dx[i];
            int new_by = b.y + dy[i];
            while((board[new_ry][new_rx]=='.' && !(new_rx==b_loc.x && new_ry==b_loc.y)) || (board[new_by][new_bx]=='.' && !(new_bx==r_loc.x && new_by==r_loc.y))){
                if(board[new_ry][new_rx]=='.' && !(new_rx==b_loc.x && new_ry==b_loc.y)){
                    r_loc.x = new_rx;
                    r_loc.y = new_ry;
                    new_rx += dx[i];
                    new_ry += dy[i];
                }
                if(board[new_by][new_bx]=='.' && !(new_bx==r_loc.x && new_by==r_loc.y)){
                    b_loc.x = new_bx;
                    b_loc.y = new_by;
                    new_bx += dx[i];
                    new_by += dy[i];
                }
            }
            if(board[new_ry][new_rx] == '#' || (new_rx==b_loc.x && new_ry==b_loc.y)){
                if(board[new_by][new_bx] == '#' || (new_bx==r_loc.x && new_by==r_loc.y)){
                    if(!visit[new_ry - dy[i]][new_rx - dx[i]][new_by - dy[i]][new_bx - dx[i]]){
                        location new_r, new_b;
                        new_r.x = new_rx-dx[i];
                        new_r.y = new_ry-dy[i];
                        new_b.x = new_bx-dx[i];
                        new_b.y = new_by-dy[i];
                        q.push(make_pair(make_pair(new_r, new_b), cnt+1));
                    }
                }
            }
            else if(board[new_ry][new_rx] == 'O'){
                if(board[new_by+dy[i]][new_bx+dx[i]] != 'O'){
                    if(answer == -1) answer = cnt+1;
                    else{
                        if(cnt+1 < answer) answer = cnt+1;
                    }                
                }
            }
        }
    }
    if(answer == 11) answer = -1;
}

int main(int argc, const char * argv[]) {
    cin >> N >> M;
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            cin >> board[i][j];
            if(board[i][j] == 'B'){
                board[i][j] = '.';
                b_loc.x = j;
                b_loc.y = i;
            }
            else if(board[i][j] == 'R'){
                board[i][j] = '.';
                r_loc.x = j;
                r_loc.y = i;
            }
            else if(board[i][j] == 'O'){
                h_loc.x = j;
                h_loc.y = i;
            }
        }
    }
    escape_bead();
    cout << answer << endl;
    
    return 0;
}
