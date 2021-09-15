//
//  main.cpp
//  BJ20058
//
//  Created by Hwayeon on 2021/09/15.
//

#include <iostream>
#include <queue>
#include <math.h>
using namespace std;

int board[64][64] = {0, };
int visit[64][64] = {0, };
int N, Q;
int max_rc;
queue<int> q;

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, -1, 0, 1};

int max_hunk = 0;

void rotate(int sx, int sy, int rc){
    vector<int> temp;
    int nx = sx;
    int ny = sy;
    int nrc = rc;
    while(nrc>=2){
        //1. temp 담기
        temp.clear();
        for(int d=nrc-2; d>=0; d--){
            temp.push_back(board[ny+d][nx]);
        }
        
        //2. 회전
        for(int d=0; d<nrc; d++){
            board[ny+d][nx] = board[ny+nrc-1][nx+d];
        }
        
        for(int d=0; d<nrc-1; d++){
            board[ny+nrc-1][nx+nrc-1-d] = board[ny+d][nx+nrc-1];
        }
        for(int d=nrc-1; d>=1; d--){
            board[ny+d][nx+nrc-1] = board[ny][nx+d];
        }
        
        for(int i=1; i<=temp.size(); i++){
            board[ny][nx+i] = temp[i-1];
        }
        nrc -= 2;
        nx += 1;
        ny += 1;
    }
}

void reduce_ice(){
    vector<pair<int, int>> spots;
    for(int y=0; y<max_rc; y++){
        for(int x=0; x<max_rc; x++){
            if(board[y][x]<=0) continue;
            int cnt = 0;
            for(int d=0; d<4; d++){
                int nx = x+dx[d];
                int ny = y+dy[d];
                if(nx<0 || nx>=max_rc || ny<0 || ny>=max_rc) continue;
                if(board[ny][nx] > 0) cnt++;
            }
            if(cnt<3) spots.push_back({x, y});
        }
    }
    for(int i=0; i<spots.size(); i++){
        int x = spots[i].first;
        int y = spots[i].second;
        board[y][x] --;
    }
}

void firestorm(){
    while(!q.empty()){
        int n = q.front();
        int rc = pow(2, n);
        q.pop();
        for(int sy=0; sy<max_rc; sy+=rc){
            for(int sx=0; sx<max_rc; sx+=rc){
                rotate(sx, sy, rc);
            }
        }
        reduce_ice();
    }
}

void bfs(int sx, int sy){
    queue<pair<int, int>> queue;
    queue.push({sx, sy});
    visit[sy][sx] = 1;
    int cnt = 1;
    while(!queue.empty()){
        int now_x = queue.front().first;
        int now_y = queue.front().second;
        queue.pop();
        for(int i=0; i<4; i++){
            int nx = now_x + dx[i];
            int ny = now_y + dy[i];
            if(nx<0 || nx>=max_rc || ny<0 || ny>=max_rc) continue;
            if(visit[ny][nx]) continue;
            if(board[ny][nx] <= 0) continue;
            queue.push({nx, ny});
            visit[ny][nx] = 1;
            cnt++;
        }
    }
    if(cnt > max_hunk) max_hunk = cnt;
}

int main(int argc, const char * argv[]) {
    cin >> N >> Q;
    max_rc = pow(2, N);
    for(int i=0; i<max_rc; i++){
        for(int j=0; j<max_rc; j++){
            cin >> board[i][j];
        }
    }
    for(int i=0; i<Q; i++){
        int qq;
        cin >> qq;
        q.push(qq);
    }
    firestorm();
    int remain_ice = 0;
    for(int y=0; y<max_rc; y++){
        for(int x=0; x<max_rc; x++){
            remain_ice += board[y][x];
            if(board[y][x] > 0 && !visit[y][x]) bfs(x, y);
        }
    }
    
    cout << remain_ice << endl;
    cout << max_hunk << endl;
    
    return 0;
}
