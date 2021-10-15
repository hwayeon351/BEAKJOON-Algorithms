//
//  main.cpp
//  BJ21610_1
//
//  Created by Hwayeon on 2021/10/15.
//

#include <iostream>
#include <vector>
using namespace std;

int N, M;
int A[51][51] = {0, };

//cmds[i] = {d, s};
vector<pair<int, int>> cmds;
vector<pair<int, int>> clouds;
vector<pair<int, int>> new_clouds;

int dr[9] = {0, 0, -1, -1, -1, 0, 1, 1, 1};
int dc[9] = {0, -1, -1, 0, 1, 1, 1, 0, -1};

void move_clouds(int d, int s){
    int cr, cc;
    for(int i=0; i<clouds.size(); i++){
        cr = clouds[i].first;
        cc = clouds[i].second;
        for(int ss=0; ss<s; ss++){
            cr += dr[d];
            cc += dc[d];
            if(cr == N+1) cr = 1;
            else if(cr == 0) cr = N;
            if(cc == N+1) cc = 1;
            else if(cc == 0) cc = N;
        }
        clouds[i].first = cr;
        clouds[i].second = cc;
    }
}

void play_bug_copy_water(){
    int r, c;
    int cnt = 0;
    for(int i=0; i<clouds.size(); i++){
        r = clouds[i].first;
        c = clouds[i].second;
        cnt = 0;
        for(int d=2; d<=8; d+=2){
            int nr = r+dr[d];
            int nc = c+dc[d];
            if(nr<=0 || nr>N || nc<=0 || nc>N) continue;
            if(A[nr][nc] > 0) cnt++;
        }
        A[r][c] += cnt;
    }
}

void make_new_clouds(){
    new_clouds.clear();
    bool check = true;
    for(int r=1; r<=N; r++){
        for(int c=1; c<=N; c++){
            if(A[r][c] >= 2){
                check = true;
                for(int i=0; i<clouds.size(); i++){
                    if(clouds[i].first == r && clouds[i].second == c){
                        check = false;
                        break;
                    }
                }
                if(!check) continue;
                new_clouds.push_back({r, c});
                A[r][c] -= 2;
            }
        }
    }
    clouds = new_clouds;
}

void play_bibaragi(){
    for(int cmd=0; cmd<M; cmd++){
        //1. 구름 이동
        move_clouds(cmds[cmd].first, cmds[cmd].second);
        //2. 구름에서 비 내림
        for(int i=0; i<clouds.size(); i++){
            A[clouds[i].first][clouds[i].second]++;
        }
        //3. 물복사 버그
        play_bug_copy_water();
        //4. 새 구름 생성
        make_new_clouds();
    }
}

int get_sum_water(){
    int sum = 0;
    for(int r=1; r<=N; r++){
        for(int c=1; c<=N; c++){
            sum += A[r][c];
        }
    }
    return sum;
}

int main(int argc, const char * argv[]) {
    cin >> N >> M;
    for(int r=1; r<=N; r++){
        for(int c=1; c<=N; c++){
            cin >> A[r][c];
        }
    }
    int d, s;
    for(int i=0; i<M; i++){
        cin >> d >> s;
        cmds.push_back({d, s});
    }
    //비구름 초기화
    clouds.push_back({N, 1});
    clouds.push_back({N, 2});
    clouds.push_back({N-1, 1});
    clouds.push_back({N-1, 2});
    
    play_bibaragi();
    cout << get_sum_water() << endl;
    
    return 0;
}
