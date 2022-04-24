//
//  main.cpp
//  BJ14890
//
//  Created by 최화연 on 2022/04/24.
//

#include <iostream>
using namespace std;

int N, L;
int map[100][100] = {0, };
int answer = 0;

void find_route_row() {
    //row에 대하여
    for (int r=0; r<N; r++) {
        int visits[100] = {0, };
        int c = 1;
        int before_h = map[r][0];
        int cnt = 1;
        bool check = true;
        while (c < N) {
            int differ = abs(map[r][c] - before_h);
            if (differ > 1) {
                check = false;
                break;
            }
            else if (differ == 0) cnt ++;
            else {
                //왼쪽에 경사로 설치
                if (map[r][c] > before_h) {
                    if (cnt < L) {
                        check = false;
                        break;
                    }
                    else {
                        //check visits
                        for (int l=1; l<=L; l++) {
                            int cc = c - l;
                            if (visits[cc]) {
                                check = false;
                                break;
                            }
                            visits[cc] = 1;
                        }
                        if (!check) break;
                        before_h = map[r][c];
                        cnt = 1;
                    }
                }
                //오른쪽에 경사로 설치
                else {
                    before_h = map[r][c];
                    for (int l=0; l<L; l++) {
                        int cc = c + l;
                        if (cc >= N || map[r][cc] != before_h) {
                            check = false;
                            break;
                        }
                        visits[cc] = 1;
                    }
                    if (!check) break;
                    if (c+L < N) {
                        if (before_h > map[r][c+L-1]) {
                            check = false;
                            break;
                        }
                    }
                    cnt = 0;
                    c += (L-1);
                }
            }
            c++;
        }
        
        if (check) {
            answer ++;
        }
    }
}

void find_route_col() {
    //col에 대하여
    for (int c=0; c<N; c++) {
        int visits[100] = {0, };
        int r = 1;
        int before_h = map[0][c];
        int cnt = 1;
        bool check = true;
        while (r < N) {
            int differ = abs(map[r][c] - before_h);
            if (differ > 1) {
                check = false;
                break;
            }
            else if (differ == 0) cnt ++;
            else {
                //위쪽에 경사로 설치
                if (map[r][c] > before_h) {
                    if (cnt < L) {
                        check = false;
                        break;
                    }
                    else {
                        //check visits
                        for (int l=1; l<=L; l++) {
                            int rr = r - l;
                            if (visits[rr]) {
                                check = false;
                                break;
                            }
                            visits[rr] = 1;
                        }
                        if (!check) break;
                        before_h = map[r][c];
                        cnt = 1;
                    }
                }
                //아래쪽에 경사로 설치
                else {
                    before_h = map[r][c];
                    for (int l=0; l<L; l++) {
                        int rr = r + l;
                        if (rr >= N || map[rr][c] != before_h) {
                            check = false;
                            break;
                        }
                        visits[rr] = 1;
                    }
                    if (!check) break;
                    if (r+L < N) {
                        if (before_h > map[r+L-1][c]) {
                            check = false;
                            break;
                        }
                    }
                    cnt = 0;
                    r += (L-1);
                }
            }
            r++;
        }

        if (check) {
            answer ++;
        }
    }
}

int main(int argc, const char * argv[]) {
    cin >> N >> L;
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            cin >> map[i][j];
        }
    }
    
    find_route_row();
    find_route_col();
    
    cout << answer << endl;
    
    return 0;
}
