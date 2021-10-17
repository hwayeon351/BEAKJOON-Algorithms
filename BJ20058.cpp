//
//  main.cpp
//  BJ20058_1
//
//  Created by Hwayeon on 2021/10/17.
//

#include <iostream>
#include <vector>
#include <queue>
#include <math.h>
using namespace std;

int N, Q;
int A[65][65] = {0, };
int visit[65][65] = {0, };
int cmd[1001] = {0, };
int NN;
int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};

vector<pair<int, int>> loc;
vector<int> temp;
int big_group = 0;
int total_ice = 0;

void remove_ice(){
    int nx, ny, cnt;
    loc.clear();
    for(int y=0; y<NN; y++){
        for(int x=0; x<NN; x++){
            if(A[y][x] == 0) continue;
            cnt = 0;
            for(int d=0; d<4; d++){
                nx = x + dx[d];
                ny = y + dy[d];
                if(nx<0 || nx>=NN || ny<0 || ny>=NN) continue;
                if(A[ny][nx] > 0) cnt++;
            }
            if(cnt < 3) loc.push_back({x, y});
        }
    }
    for(int i=0; i<loc.size(); i++){
        A[loc[i].second][loc[i].first]--;
    }
}

void play_firestorm(){
    int L, LL;
    for(int q=0; q<Q; q++){
        L = cmd[q];
        LL = pow(2, L);
        for(int l=0; l<NN; l+=LL){
            for(int m=0; m<NN; m+=LL){
                temp.clear();
                for(int y=l; y<l+LL; y++){
                    for(int x=m; x<m+LL; x++){
                        temp.push_back(A[y][x]);
                    }
                }
                for(int x=m; x<m+LL; x++){
                    for(int y=l+LL-1; y>=l; y--){
                        A[y][x] = temp.back();
                        temp.pop_back();
                    }
                }
            }
        }
        remove_ice();
    }
}

int get_ice(){
    int cnt = 0;
    for(int y=0; y<NN; y++){
        for(int x=0; x<NN; x++){
            cnt += A[y][x];
        }
    }
    return cnt;
}

void get_big_group(int sx, int sy){
    int cnt = 1;
    visit[sy][sx] = 1;
    queue<pair<int, int>> q;
    q.push({sx, sy});
    while(!q.empty()){
        int now_x = q.front().first;
        int now_y = q.front().second;
        q.pop();
        for(int d=0; d<4; d++){
            int nx = now_x + dx[d];
            int ny = now_y + dy[d];
            if(nx<0 || nx>=NN || ny<0 || ny>=NN) continue;
            if(visit[ny][nx]) continue;
            if(A[ny][nx]==0) continue;
            visit[ny][nx] = 1;
            cnt ++;
            q.push({nx, ny});
        }
    }
    if(cnt > big_group) big_group = cnt;
}

int main(int argc, const char * argv[]) {
    cin >> N >> Q;
    NN = pow(2, N);
    for(int y=0; y<NN; y++){
        for(int x=0; x<NN; x++){
            cin >> A[y][x];
        }
    }
    for(int q=0; q<Q; q++){
        cin >> cmd[q];
    }
    play_firestorm();
    total_ice = get_ice();
    if(total_ice == 0){
        cout << 0 << endl;
        cout << 0 << endl;
        return 0;
    }
    for(int y=0; y<NN; y++){
        for(int x=0; x<NN; x++){
            if(A[y][x] > 0 && !visit[y][x]){
                get_big_group(x, y);
            }
        }
    }
    cout << total_ice << endl;
    cout << big_group << endl;
    return 0;
}
