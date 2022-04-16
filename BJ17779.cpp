//
//  main.cpp
//  BJ17779
//
//  Created by 최화연 on 2022/04/16.
//

#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

int N;
int A[21][21] = {0, };
int vst[21][21] = {0, };
int min_differ = -1;
int total_A = 0;
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, -1, 0, 1};

int get_area_5(int sx, int sy) {
    if (vst[sx][sy]) return 0;
    int sum = A[sx][sy];
    vst[sx][sy] = 1;
    queue<pair<int, int>> q;
    q.push({sx, sy});
    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        for (int d=0; d<4; d++) {
            int nx = x + dx[d];
            int ny = y + dy[d];
            if (1 <= nx && nx <= N && 1 <= ny && ny <= N) {
                if (vst[nx][ny]) continue;
                vst[nx][ny] = 1;
                sum += A[nx][ny];
                q.push({nx, ny});
            }
        }
    }
    
    return sum;
}

void divide_group() {
    for(int d1=1; d1<N; d1++) {
        for (int d2=1; d2<N; d2++) {
            for (int y=1; y<=N; y++) {
                for (int x=1; x<=N; x++) {
                    if (!(1 <= x && x < x+d1+d2 && x+d1+d2 <= N)) continue;
                    if (!(1 <= y-d1 && y-d1 < y && y < y+d2 && y+d2 <= N)) continue;
                    
                    memset(vst, 0, sizeof(vst));
                    int a[6] = {0, };
                    
                    //경계선
                    for (int i=0; i<=d1; i++) {
                        if (!vst[x+i][y-i]) {
                            vst[x+i][y-i] = 1;
                            a[5] += A[x+i][y-i];
                        }
                        if (!vst[x+d2+i][y+d2-i]) {
                            vst[x+d2+i][y+d2-i] = 1;
                            a[5] += A[x+d2+i][y+d2-i];
                        }
                    }
                    for (int i=0; i<=d2; i++) {
                        if (!vst[x+d1+i][y-d1+i]) {
                            vst[x+d1+i][y-d1+i] = 1;
                            a[5] += A[x+d1+i][y-d1+i];
                        }
                        if (!vst[x+i][y+i]) {
                            vst[x+i][y+i] = 1;
                            a[5] += A[x+i][y+i];
                        }
                    }
                    
                    //경계선 내부
                    for (int i=0; i<d1; i++) {
                        a[5] += get_area_5(x+i+1, y-i);
                    }
                    for (int i=1; i<=d1; i++) {
                        a[5] += get_area_5(x+d2+d1-1, y+d2-d1);
                    }
                    
                    //1번
                    for (int r=1; r<x+d1; r++) {
                        for (int c=1; c<=y; c++) {
                            if (vst[r][c]) continue;
                            vst[r][c] = 1;
                            a[1] += A[r][c];
                        }
                    }
                    
                    //2번
                    for (int r=1; r<=x+d2; r++) {
                        for (int c=y+1; c<=N; c++) {
                            if (vst[r][c]) continue;
                            vst[r][c] = 1;
                            a[2] += A[r][c];
                        }
                    }
                    
                    //3번
                    for (int r=x+d1; r<=N; r++) {
                        for (int c=1; c<y-d1+d2; c++) {
                            if (vst[r][c]) continue;
                            vst[r][c] = 1;
                            a[3] += A[r][c];
                        }
                    }
                    
                    //4번
                    for (int r=x+d2; r<=N; r++) {
                        for (int c=y-d1+d2; c<=N; c++) {
                            if (vst[r][c]) continue;
                            vst[r][c] = 1;
                            a[4] += A[r][c];
                        }
                    }
                    
                    int max_a = 0;
                    int min_a = total_A;
                    for (int i=1; i<=5; i++) {
                        if (a[i] > max_a) max_a = a[i];
                        if (a[i] < min_a) min_a = a[i];
                    }

                    int differ = max_a - min_a;

                    if (min_differ == -1 || min_differ > differ) min_differ = differ;
                }
            }
        }
    }
}

int main(int argc, const char * argv[]) {
    cin >> N;
    for (int r=1; r<=N; r++) {
        for (int c=1; c<=N; c++) {
            cin >> A[r][c];
            total_A += A[r][c];
        }
    }
    divide_group();
    
    cout << min_differ << endl;
    
    return 0;
}
