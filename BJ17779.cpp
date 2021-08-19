//
//  main.cpp
//  BJ17779
//
//  Created by Hwayeon on 2021/08/19.
//

#include <iostream>
#include <string.h>
using namespace std;

int N;
int A[101][101] = {0, };
int area[101][101] = {0, };
int population[6] = {0, };
int max_A = 0;
int min_A = 400001;
int min_differ = 400001;
int d1, d2 = 0;
int px, py = 0;

int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};

void make_district1(){
    for(int x=1; x<px+d1; x++){
        for(int y=1; y<=py; y++){
            if(area[x][y] == 0){
                area[x][y] = 1;
                population[1] += A[x][y];
            }
        }
    }
    if(population[1] > max_A) max_A = population[1];
    if(population[1] < min_A) min_A = population[1];
}

void make_district2(){
    for(int x=1; x<=px+d2; x++){
        for(int y=py+1; y<=N; y++){
            if(area[x][y] == 0){
                area[x][y] = 2;
                population[2] += A[x][y];
            }
        }
    }
    if(population[2] > max_A) max_A = population[2];
    if(population[2] < min_A) min_A = population[2];
}

void make_district3(){
    for(int x=px+d1; x<=N; x++){
        for(int y=1; y<py-d1+d2; y++){
            if(area[x][y] == 0){
                area[x][y] = 3;
                population[3] += A[x][y];
            }
        }
    }
    if(population[3] > max_A) max_A = population[3];
    if(population[3] < min_A) min_A = population[3];
}

void make_district4(){
    for(int x=px+d2+1; x<=N; x++){
        for(int y=py-d1+d2; y<=N; y++){
            if(area[x][y] == 0){
                area[x][y] = 4;
                population[4] += A[x][y];
            }
        }
    }
    if(population[4] > max_A) max_A = population[4];
    if(population[4] < min_A) min_A = population[4];
}

//dfs
void make_district5(int x, int y){
    if(area[x][y]==0){
        area[x][y] = 5;
        population[5] += A[x][y];
    }
    for(int i=0; i<4; i++){
        int nx = x+dx[i];
        int ny = y+dy[i];
        if(area[nx][ny] == 0) make_district5(nx, ny);
    }
}

void make_border(){
    memset(area, 0, sizeof(area));
    memset(population, 0, sizeof(population));
    //1.
    int nx, ny;
    for(int d=0; d<=d1; d++){
        nx = px + d;
        ny = py - d;
        area[nx][ny] = 5;
        population[5] += A[nx][ny];
    }
    //2.
    for(int d=0; d<=d2; d++){
        nx = px + d;
        ny = py + d;
        if(area[nx][ny] == 0){
            area[nx][ny] = 5;
            population[5] += A[nx][ny];
        }
    }
    //3.
    for(int d=0; d<=d2; d++){
        nx = px + d1 + d;
        ny = py - d1 + d;
        if(area[nx][ny] == 0){
            area[nx][ny] = 5;
            population[5] += A[nx][ny];
        }
    }
    //4.
    for(int d=0; d<=d1; d++){
        nx = px + d2 + d;
        ny = py + d2 - d;
        if(area[nx][ny] == 0){
            area[nx][ny] = 5;
            population[5] += A[nx][ny];
        }
    }
    //경계선 안 5 채워넣기
    for(int d=0; d<d1; d++){
        nx = px + d;
        ny = py - d;
        make_district5(nx+1, ny);
    }
    for(int d=1; d<=d1; d++){
        nx = px + d2 + d;
        ny = py + d2 - d;
        make_district5(nx-1, ny);
    }
    if(population[5] > max_A) max_A = population[5];
    if(population[5] < min_A) min_A = population[5];
}

void select_pivot(){
    for(int dd1=1; dd1<=N-1; dd1++){
        for(int dd2=1; dd2<=N-1; dd2++){
            for(int x=1; x<=N-2; x++){
                for(int y=2; y<=N-1; y++){
                    //기준점과 경계의 길이가 될 수 있는 조건
                    if(x+dd1+dd2 <= N && y-dd1 >= 1 && y+dd2 <= N){
                        max_A = 0;
                        min_A = 400001;
                        px = x;
                        py = y;
                        d1 = dd1;
                        d2 = dd2;
                        make_border();
                        make_district1();
                        make_district2();
                        make_district3();
                        make_district4();
                        if(min_differ > (max_A-min_A)) min_differ = max_A-min_A;
                    }
                }
            }
        }
    }
}

int main(int argc, const char * argv[]) {
    cin >> N;
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            cin >> A[i][j];
        }
    }
    select_pivot();
    cout << min_differ << endl;
    return 0;
}
