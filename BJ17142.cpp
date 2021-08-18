//
//  main.cpp
//  BJ17142
//
//  Created by Hwayeon on 2021/08/18.
//

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int N, M;
int lab[50][50] = {0, };
int copy_lab[50][50] = {0, };
vector<pair<int, int>> virus;
vector<pair<int, int>> v;
vector<pair<int, int>> nv;
int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};
int min_sec = -1;
int max_virus = 0;
int v_cnt = 0;

void copy_laboratory(){
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            copy_lab[i][j] = lab[i][j];
        }
    }
}

void spread_virus(){
    int sec = 0;
    copy_laboratory();
    queue<vector<pair<int, int>>> q;
    q.push(virus);
    //활성 상태로 바꾸기
    for(int i=0; i<q.front().size(); i++){
        copy_lab[q.front()[i].second][q.front()[i].first] = 3;
    }
    int cnt = v_cnt;

    int x, y, nx, ny;
    bool ck = false;
    while(!q.empty()){
        v.clear();
        nv.clear();
        if(cnt == max_virus){
            ck = true;
            break;
        }
        v = q.front();
        q.pop();
        for(int i=0; i<v.size(); i++){
            x = v[i].first;
            y = v[i].second;
            for(int d=0; d<4; d++){
                nx = x+dx[d];
                ny = y+dy[d];
                if(nx<0 || nx>=N || ny<0 || ny>=N) continue;
                //비활성 상태의 바이러스인 경우
                if(copy_lab[ny][nx] == 2){
                    copy_lab[ny][nx] = 3;
                    nv.push_back({nx, ny});
                }
                //빈 칸인 경우
                else if(copy_lab[ny][nx] == 0){
                    copy_lab[ny][nx] = 3;
                    nv.push_back({nx, ny});
                    cnt ++;
                }
            }
        }
        if(nv.size() > 0) q.push(nv);
        sec++;
    }
    if(ck){
        if(min_sec == -1) min_sec = sec;
        else if(sec < min_sec) min_sec = sec;
    }
}

void select_virus(int x, int y){
    if(virus.size() == M){
        spread_virus();
        return;
    }
    for(int i=y; i<N; i++){
        if(i > y) x = 0;
        for(int j=x; j<N; j++){
            if(lab[i][j] == 2){
                virus.push_back({j, i});
                select_virus(j+1, i);
                virus.pop_back();
            }
        }
    }
}

int main(int argc, const char * argv[]) {
    cin >> N >> M;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cin >> lab[i][j];
            if(lab[i][j] == 2){
                v_cnt++;
                max_virus++;
            }
            else if(lab[i][j] == 0) max_virus++;
        }
    }
    if(v_cnt == max_virus){
        cout << 0 << endl;
    }
    else{
        select_virus(0, 0);
        cout << min_sec << endl;
    }
    return 0;
}
