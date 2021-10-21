//
//  main.cpp
//  BJ17144_1
//
//  Created by Hwayeon on 2021/10/21.
//

#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int R, C, T;
int A[50][50] = {0, };
int dc[4] = {-1, 0, 1, 0};
int dr[4] = {0, -1, 0, 1};
int cleaner_r1 = -1;
int cleaner_r2 = -1;
int cleaner_c1 = -1;
int cleaner_c2 = -1;
vector<pair<pair<int, int>, int>> dusts;
queue<int> temp;
int total_dust = 0;

void spread_dust(){
    dusts.clear();
    for(int r=0; r<R; r++){
        for(int c=0; c<C; c++){
            if(A[r][c] > 0){
                int spread = 0;
                for(int d=0; d<4; d++){
                    int nr = r+dr[d];
                    int nc = c+dc[d];
                    if(nr<0 || nr>=R || nc<0 || nc>=C) continue;
                    if(A[nr][nc] == -1) continue;
                    dusts.push_back({{nr, nc}, A[r][c]/5});
                    spread += (A[r][c]/5);
                }
                A[r][c] -= spread;
            }
        }
    }
    for(int i=0; i<dusts.size(); i++){
        A[dusts[i].first.first][dusts[i].first.second] += dusts[i].second;
    }
}

void play_cleaner(){
    //위쪽 바람
    for(int c=1; c<C; c++){
        temp.push(A[cleaner_r1][c]);
    }
    for(int r=cleaner_r1-1; r>=0; r--){
        temp.push(A[r][C-1]);
    }
    for(int c=C-2; c>=0; c--){
        temp.push(A[0][c]);
    }
    for(int r=1; r<cleaner_r1-1; r++){
        temp.push(A[r][0]);
    }
    A[cleaner_r1][1] = 0;
    for(int c=2; c<C; c++){
        A[cleaner_r1][c] = temp.front();
        temp.pop();
    }
    for(int r=cleaner_r1-1; r>=0; r--){
        A[r][C-1] = temp.front();
        temp.pop();
    }
    for(int c=C-2; c>=0; c--){
        A[0][c] = temp.front();
        temp.pop();
    }
    for(int r=1; r<cleaner_r1; r++){
        A[r][0] = temp.front();
        temp.pop();
    }
    
    //아래쪽 바람
    for(int c=1; c<C; c++){
        temp.push(A[cleaner_r2][c]);
    }
    for(int r=cleaner_r2+1; r<R; r++){
        temp.push(A[r][C-1]);
    }
    for(int c=C-2; c>=0; c--){
        temp.push(A[R-1][c]);
    }
    for(int r=R-2; r>cleaner_r2+1; r--){
        temp.push(A[r][0]);
    }
    A[cleaner_r2][1] = 0;
    for(int c=2; c<C; c++){
        A[cleaner_r2][c] = temp.front();
        temp.pop();
    }
    for(int r=cleaner_r2+1; r<R; r++){
        A[r][C-1] = temp.front();
        temp.pop();
    }
    for(int c=C-2; c>=0; c--){
        A[R-1][c] = temp.front();
        temp.pop();
    }
    for(int r=R-2; r>cleaner_r2; r--){
        A[r][0] = temp.front();
        temp.pop();
    }
}

void simulate(){
    for(int t=0; t<T; t++){
        //1. 미세먼지 확산
        spread_dust();
        //2. 공기청정기 작동
        play_cleaner();
    }
}

void get_total_dust(){
    for(int r=0; r<R; r++){
        for(int c=0; c<C; c++){
            if(A[r][c] <= 0) continue;
            total_dust += A[r][c];
        }
    }
}

int main(int argc, const char * argv[]) {
    cin >> R >> C >> T;
    for(int r=0; r<R; r++){
        for(int c=0; c<C; c++){
            cin >> A[r][c];
            if(A[r][c] == -1){
                if(cleaner_c1 == -1){
                    cleaner_c1 = c;
                    cleaner_r1 = r;
                }
                else{
                    cleaner_c2 = c;
                    cleaner_r2 = r;
                }
            }
        }
    }
    simulate();
    get_total_dust();
    cout << total_dust << endl;
    
    return 0;
}
