//
//  main.cpp
//  BJ16234
//
//  Created by Hwayeon on 2021/08/05.
//

#include <iostream>
#include <cmath>
using namespace  std;
int N, L, R;
int A[50][50] ={0,};
int day = 0;

void move_population(){
    int unity[50][50] = {0,};
    int u = 0;
    int unit[2501][2] = {0,};
    
    //1. 국경선 체크
    for(int y=0; y<N; y++){
        for(int x=0; x<N; x++){
            int r_x = x+1;
            int r_y = y;
            int b_x = x;
            int b_y = y+1;
            if(r_x < N){
                //오른쪽 체크
                int r_differ = abs(A[y][x]-A[r_y][r_x]);
                if(r_differ >= L && r_differ <= R){
                    //(r_x, r_y) 나라가 연합이 없는 경우,
                    if(unity[r_y][r_x] == 0){
                        //(x, y) 나라가 연합이 있는 경우, 연합 추가
                        if(unity[y][x] != 0){
                            unity[r_y][r_x] = unity[y][x];
                            unit[unity[y][x]][0] += A[r_y][r_x];
                            unit[unity[y][x]][1]++;
                        }
                        //(x, y) 나라가 연합이 없는 경우, 연합 생성
                        else{
                            u++;
                            unit[u][0] = A[y][x] + A[r_y][r_x];
                            unit[u][1] = 2;
                            unity[y][x] = u;
                            unity[r_y][r_x] = u;
                        }
                    }
                    //(r_x, r_y) 나라가 연합이 있는 경우,
                    else if(unity[y][x] != unity[r_y][r_x]){
                        //(x, y) 나라가 연합이 없는 경우, 연합 추가
                        if(unity[y][x] == 0){
                            unity[y][x] = unity[r_y][r_x];
                            unit[unity[r_y][r_x]][0] += A[y][x];
                            unit[unity[r_y][r_x]][1] ++;
                        }
                        //(x, y) 나라가 연합이 있는 경우, 연합을 합친다
                        else{
                            int before_u = unity[r_y][r_x];
                            unit[unity[y][x]][0] += unit[unity[r_y][r_x]][0];
                            unit[unity[r_y][r_x]][0] = 0;
                            unit[unity[y][x]][1] += unit[unity[r_y][r_x]][1];
                            unit[unity[r_y][r_x]][1] = 0;
                            int iy = y;
                            if(b_y < N) iy = b_y;
                            for(int i=0; i<=iy; i++){
                                for(int j=0; j<N; j++){
                                    if(unity[i][j] == before_u){
                                        unity[i][j] = unity[y][x];
                                    }
                                }
                            }
                        }
                    }
                    
                }
            }
            if(b_y < N){
                //아래쪽 체크
                int b_differ = abs(A[y][x]-A[b_y][b_x]);
                if(b_differ >= L && b_differ <= R){
                    //(b_x, b_y) 나라가 연합이 없는 경우,
                    if(unity[b_y][b_x] == 0){
                        //(x, y) 나라가 연합이 있는 경우, 연합 추가
                        if(unity[y][x] != 0){
                            unity[b_y][b_x] = unity[y][x];
                            unit[unity[y][x]][0] += A[b_y][b_x];
                            unit[unity[y][x]][1]++;
                        }
                        //(x, y) 나라가 연합이 없는 경우, 연합 생성
                        else{
                            u++;
                            unit[u][0] = A[y][x] + A[b_y][b_x];
                            unit[u][1] = 2;
                            unity[y][x] = u;
                            unity[b_y][b_x] = u;
                        }
                    }
                    //(b_x, b_y) 나라가 연합이 있는 경우,
                    else if(unity[y][x] != unity[b_y][b_x]){
                        //(x, y) 나라가 연합이 없는 경우, 연합 추가
                        if(unity[y][x] == 0){
                            unity[y][x] = unity[b_y][b_x];
                            unit[unity[b_y][b_x]][0] += A[y][x];
                            unit[unity[b_y][b_x]][1] ++;
                        }
                        //(x, y) 나라가 연합이 있는 경우,
                        else{
                            int before_u = unity[b_y][b_x];
                            unit[unity[y][x]][0] += unit[unity[b_y][b_x]][0];
                            unit[unity[y][x]][1] += unit[unity[b_y][b_x]][1];
                            unit[unity[b_y][b_x]][0] = 0;
                            unit[unity[b_y][b_x]][1] = 0;
                            for(int i=0; i<=b_y; i++){
                                for(int j=0; j<N; j++){
                                    if(unity[i][j] == before_u){
                                        unity[i][j] = unity[y][x];
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    //연합이 없는 경우, 종료
    if(u == 0) return;
    //인구 이동
    day++;
    for(int i=1; i<=u; i++){
        if(unit[i][1] > 0){
            int np = unit[i][0]/unit[i][1];
            for(int y=0; y<N; y++){
                for(int x=0; x<N; x++){
                    if(unity[y][x] == i){
                        A[y][x] = np;
                    }
                }
            }
        }
    }
    move_population();
}

int main(int argc, const char * argv[]) {
    cin >> N >> L >> R;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cin >> A[i][j];
        }
    }
    move_population();
    cout << day << endl;
    return 0;
}
