//
//  main.cpp
//  BJ14890
//
//  Created by Hwayeon on 2021/09/18.
//

#include <iostream>
#include <math.h>
#include <string.h>
using namespace std;

int map[100][100] = {0, };
int visit[100] = {0, };
int road = 0;
int N, L;

void check_road(){
    for(int r=0; r<N; r++){
        memset(visit, 0, sizeof(visit));
        int check = true;
        int before = map[r][0];
        int cnt = 1;
        int c = 1;
        while(c < N){
            if(map[r][c] == before){
                cnt ++;
                c ++;
                continue;
            }
            //높이 차이가 2 이상인 경우, 길이 아니다
            else if(abs(map[r][c] - before) > 1){
                check = false;
                break;
            }
            //높이 차이가 1인 경우,
            else{
                //오르막길 인 경우,
                if(map[r][c] - before == 1){
                    //경사로를 놓을 수 있는 경우,
                    if(cnt >= L){
                        for(int cc=c-L; cc<c; cc++){
                            //이미 경사로가 설치되어 있는 경우, 설치 불가 -> 길이 아니다
                            if(visit[cc]){
                                check = false;
                                break;
                            }
                            visit[cc] = 1;
                        }
                        //경사로 설치 완료
                        before = map[r][c];
                        cnt = 1;
                        c ++;
                        continue;
                    }
                    //경사로를 놓을 수 없는 경우, 길이 아니다
                    else{
                        check = false;
                        break;
                    }
                }
                //내리막길 인 경우,
                else{
                    int cc;
                    for(cc=c+1; cc<c+L; cc++){
                        if(map[r][cc] == map[r][c]) continue;
                        check = false;
                        break;
                    }
                    if(!check) break;
                    //경사로를 놓을 수 있는 경우, 경사로 설치
                    for(cc=c; cc<c+L; cc++){
                        visit[cc] = 1;
                    }
                    before = map[r][c];
                    cnt = L;
                    c++;
                    continue;
                }
            }
        }
        if(check) {
            road++;
        }
    }
    for(int c=0; c<N; c++){
        memset(visit, 0, sizeof(visit));
        int check = true;
        int before = map[0][c];
        int cnt = 1;
        int r = 1;
        while(r < N){
            if(map[r][c] == before){
                cnt ++;
                r ++;
                continue;
            }
            //높이 차이가 2 이상인 경우, 길이 아니다
            else if(abs(map[r][c] - before) > 1){
                check = false;
                break;
            }
            //높이 차이가 1인 경우,
            else{
                //오르막길 인 경우,
                if(map[r][c] - before == 1){
                    //경사로를 놓을 수 있는 경우,
                    if(cnt >= L){
                        for(int rr=r-L; rr<r; rr++){
                            //이미 경사로가 설치되어 있는 경우, 설치 불가 -> 길이 아니다
                            if(visit[rr]){
                                check = false;
                                break;
                            }
                            visit[rr] = 1;
                        }
                        //경사로 설치 완료
                        before = map[r][c];
                        cnt = 1;
                        r ++;
                        continue;
                    }
                    //경사로를 놓을 수 없는 경우, 길이 아니다
                    else{
                        check = false;
                        break;
                    }
                }
                //내리막길 인 경우,
                else{
                    int rr;
                    for(rr=r+1; rr<r+L; rr++){
                        if(map[rr][c] == map[r][c]) continue;
                        check = false;
                        break;
                    }
                    if(!check) break;
                    //경사로를 놓을 수 있는 경우, 경사로 설치
                    for(rr=r; rr<r+L; rr++){
                        visit[rr] = 1;
                    }
                    before = map[r][c];
                    cnt = L;
                    r++;
                    continue;
                }
            }
        }
        if(check) {
            road++;
        }
    }
}

int main(int argc, const char * argv[]) {
    cin >> N >> L;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cin >> map[i][j];
        }
    }
    check_road();
    cout << road << endl;
    return 0;
}
