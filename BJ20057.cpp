//
//  main.cpp
//  BJ20057
//
//  Created by Hwayeon on 2021/09/16.
//

#include <iostream>
using namespace std;

int N;
int board[500][500] = {0, };
int dc[4] = {-1, 0, 1, 0};
int dr[4] = {0, 1, 0, -1};
long long total_out = 0;

void spread_sand(int r, int c, int d){
    int sum = 0;
    int per = 0;
    int out = 0;
    int y = board[r][c];
    switch (d) {
        //왼쪽
        case 0:
            per = y*0.02;
            if(r-2 >= 0){
                board[r-2][c] += per;
                sum += per;
            }
            else out += per;
            if(r+2 < N) {
                board[r+2][c] += per;
                sum += per;
            }
            else out += per;
            per = y*0.07;
            if(r-1 >= 0){
                board[r-1][c] += per;
                sum += per;
            }
            else out += per;
            if(r+1 < N){
                board[r+1][c] += per;
                sum += per;
            }
            else out += per;
            per = y*0.01;
            if(r-1 >= 0 && c+1 < N){
                board[r-1][c+1] += per;
                sum += per;
            }
            else out += per;
            if(r+1 < N && c+1 < N){
                board[r+1][c+1] += per;
                sum += per;
            }
            else out += per;
            per = y*0.1;
            if(r-1 >= 0 && c-1 >= 0){
                board[r-1][c-1] += per;
                sum += per;
            }
            else out += per;
            if(r+1 < N && c-1 >= 0){
                per = y*0.1;
                board[r+1][c-1] += per;
                sum += per;
            }
            else out += per;
            per = y*0.05;
            if(c-2 >= 0){
                board[r][c-2] += per;
                sum += per;
            }
            else out += per;
            if(c-1 >= 0) board[r][c-1] += (board[r][c] - (sum + out));
            else out += (board[r][c] - (sum + out));
            board[r][c] = 0;
            total_out += out;
            break;
        //아래쪽
        case 1:
            per = y*0.02;
            if(c-2 >= 0){
                board[r][c-2] += per;
                sum += per;
            }
            else out += per;
            if(c+2 < N) {
                board[r][c+2] += per;
                sum += per;
            }
            else out += per;
            per = y*0.07;
            if(c-1 >= 0){
                board[r][c-1] += per;
                sum += per;
            }
            else out += per;
            if(c+1 < N){
                board[r][c+1] += per;
                sum += per;
            }
            else out += per;
            per = y*0.01;
            if(r-1 >= 0 && c+1 < N){
                board[r-1][c+1] += per;
                sum += per;
            }
            else out += per;
            if(r-1 >= 0 && c-1 >= 0){
                board[r-1][c-1] += per;
                sum += per;
            }
            else out += per;
            per = y*0.1;
            if(r+1 < N && c-1 >= 0){
                board[r+1][c-1] += per;
                sum += per;
            }
            else out += per;
            if(r+1 < N && c+1 < N){
                board[r+1][c+1] += per;
                sum += per;
            }
            else out += per;
            per = y*0.05;
            if(r+2 < N){
                board[r+2][c] += per;
                sum += per;
            }
            else out += per;
            if(r+1 < N) board[r+1][c] += (board[r][c] - (sum + out));
            else out += (board[r][c] - (sum + out));
            board[r][c] = 0;
            total_out += out;
            break;
        //오른쪽
        case 2:
            per = y*0.02;
            if(r-2 >= 0){
                board[r-2][c] += per;
                sum += per;
            }
            else out += per;
            if(r+2 < N) {
                board[r+2][c] += per;
                sum += per;
            }
            else out += per;
            per = y*0.07;
            if(r-1 >= 0){
                board[r-1][c] += per;
                sum += per;
            }
            else out += per;
            if(r+1 < N){
                board[r+1][c] += per;
                sum += per;
            }
            else out += per;
            per = y*0.01;
            if(r-1 >= 0 && c-1 >= 0){
                board[r-1][c-1] += per;
                sum += per;
            }
            else out += per;
            if(r+1 < N && c-1 >= 0){
                board[r+1][c-1] += per;
                sum += per;
            }
            else out += per;
            per = y*0.1;
            if(r-1 >= 0 && c+1 < N){
                board[r-1][c+1] += per;
                sum += per;
            }
            else out += per;
            if(r+1 < N && c+1 < N){
                board[r+1][c+1] += per;
                sum += per;
            }
            else out += per;
            per = y*0.05;
            if(c+2 < N){
                board[r][c+2] += per;
                sum += per;
            }
            else out += per;
            if(c+1 < N) board[r][c+1] += (board[r][c] - (sum + out));
            else out += (board[r][c] - (sum + out));
            board[r][c] = 0;
            total_out += out;
            break;
        //위쪽
        case 3:
            per = y*0.02;
            if(c-2 >= 0){
                board[r][c-2] += per;
                sum += per;
            }
            else out += per;
            if(c+2 < N) {
                board[r][c+2] += per;
                sum += per;
            }
            else out += per;
            per = y*0.07;
            if(c-1 >= 0){
                board[r][c-1] += per;
                sum += per;
            }
            else out += per;
            if(c+1 < N){
                board[r][c+1] += per;
                sum += per;
            }
            else out += per;
            per = y*0.01;
            if(r+1 < N && c+1 < N){
                board[r+1][c+1] += per;
                sum += per;
            }
            else out += per;
            if(r+1 < N && c-1 >= 0){
                board[r+1][c-1] += per;
                sum += per;
            }
            else out += per;
            per = y*0.1;
            if(r-1 >= 0 && c-1 >= 0){
                board[r-1][c-1] += per;
                sum += per;
            }
            else out += per;
            if(r-1 >= 0 && c+1 < N){
                board[r-1][c+1] += per;
                sum += per;
            }
            else out += per;
            per = y*0.05;
            if(r-2 >= 0){
                board[r-2][c] += per;
                sum += per;
            }
            else out += per;
            if(r-1 >= 0) board[r-1][c] += (board[r][c] - (sum + out));
            else out += (board[r][c] - (sum + out));
            board[r][c] = 0;
            total_out += out;
            break;
    }
}

void move_tornado(){
    int tc = N/2;
    int tr = N/2;
    int dir = 0;
    for(int i=1; i<=N; i++){
        for(int j=0; j<2; j++){
            for(int k=1; k<=i; k++){
                int yr = tr+dr[dir];
                int yc = tc+dc[dir];
                tr = yr;
                tc = yc;
                if(i==N && k==N-1){
                    spread_sand(yr, yc, dir);
                    cout << total_out <<endl;
                    return;
                }
                if(board[yr][yc] == 0) continue;
                spread_sand(yr, yc, dir);
            }
            dir = (dir+1) % 4;
        }
    }
}

int main(int argc, const char * argv[]) {
    cin >> N;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cin >> board[i][j];
        }
    }
    move_tornado();
    return 0;
}
