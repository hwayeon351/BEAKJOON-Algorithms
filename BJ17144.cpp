//
//  main.cpp
//  BJ17144
//
//  Created by Hwayeon on 2021/08/08.
//

#include <iostream>
#include <vector>
using namespace std;

int R, C, T;
int A[50][50] = {0,};
struct air_cleaner{
    int tx = 0;
    int ty = 0;
    int bx = 0;
    int by = 0;
};
air_cleaner cleaner;
vector<pair<int, int>> dust;
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, -1, 0, 1};
int total_dust = 0;

void clean_air(){
    while(T > 0){
        //1. 확산
        int change[50][50] = {0, };
        while(!dust.empty()){
            int x = dust.back().first;
            int y = dust.back().second;
            dust.pop_back();
            int cnt = 0;
            for(int i=0; i<4; i++){
                int nx = x + dx[i];
                int ny = y + dy[i];
                //칸이 없는 경우,
                if(nx<0 || nx>=C || ny<0 || ny>=R) continue;
                //공기청정기인 경우,
                if(A[ny][nx] == -1) continue;
                change[ny][nx] += A[y][x]/5;
                cnt++;
            }
            change[y][x] -= (A[y][x]/5*cnt);
        }
        for(int i=0; i<R; i++){
            for(int j=0; j<C; j++){
                A[i][j] += change[i][j];
            }
        }
        
        //2. 공기청정기 작동
        //위쪽 바람
        //하 -> col = 0, row = 0~cleaner.ty-1
        for(int r=cleaner.ty-2; r>=0; r--){
            A[r+1][0] = A[r][0];
        }
        //좌 -> row = 0, col = 0~R-1
        for(int c=1; c<=C-1; c++){
            A[0][c-1] = A[0][c];
        }
        //상 -> col = C-1, row = 0~cleaner.ty
        for(int r=0; r<cleaner.ty; r++){
            A[r][C-1] = A[r+1][C-1];
        }
        //우 -> row = cleaner.ty, col = 1~C-1
        for(int c=C-2; c>=1; c--){
            A[cleaner.ty][c+1] = A[cleaner.ty][c];
        }
        A[cleaner.ty][1] = 0;
        
        //아래쪽 바람
        //상 -> col = 0, row = cleaner.by+1~R-1
        for(int r=cleaner.by+2; r<=R-1; r++){
            A[r-1][0] = A[r][0];
        }
        //좌 -> row = R-1, col = 0~C-1
        for(int c=1; c<=C-1; c++){
            A[R-1][c-1] = A[R-1][c];
        }
        //하 -> col = C-1, row = cleaner.by~R-1
        for(int r=R-2; r>=cleaner.by; r--){
            A[r+1][C-1] = A[r][C-1];
        }
        //우 -> row = cleaner.by, col = 1~C-1
        for(int c=C-2; c>=1; c--){
            A[cleaner.by][c+1] = A[cleaner.by][c];
        }
        A[cleaner.by][1] = 0;
        
        //먼지 위치 추가, 미세먼지 양 카운팅
        int t_d = 0;
        for(int i=0; i<R; i++){
            for(int j=0; j<C; j++){
                if(A[i][j] > 0) {
                    t_d += A[i][j];
                    dust.push_back(make_pair(j, i));
                }
            }
        }
        total_dust = t_d;
        T--;
    }
}

int main(int argc, const char * argv[]) {
    cin >> R >> C >> T;
    for(int i=0; i<R; i++){
        for(int j=0; j<C; j++){
            cin >> A[i][j];
            //공기청정기인 경우,
            if(A[i][j] == -1){
                if(cleaner.ty == 0){
                    cleaner.ty = i;
                }
                else{
                    cleaner.by = i;
                }
            }
            //먼지인 경우,
            else if(A[i][j] > 0){
                dust.push_back(make_pair(j, i));
            }
        }
    }
    clean_air();
    cout << total_dust << endl;
    return 0;
}
