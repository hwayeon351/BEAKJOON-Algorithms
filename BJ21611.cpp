//
//  main.cpp
//  BJ21611
//
//  Created by Hwayeon on 2021/10/15.
//

#include <iostream>
#include <vector>
using namespace std;

int N, M;
int dr[5] = {0, -1, 1, 0, 0};
int dc[5] = {0, 0, 0, -1, 1};
int mc[4] = {-1, 0, 1, 0};
int mr[4] = {0, 1, 0, -1};
int board[50][50] = {0, };

//blizards[i] = {d, s}
vector<pair<int, int>> blizards;
vector<vector<pair<int, int>>> beads_group;
vector<pair<int, int>> beads;
vector<int> new_beads;
int shark_r = 0;
int shark_c = 0;
int bomb_beads_cnt[4] = {0,};

void move_beads(){
    int r = shark_r;
    int c = shark_c;
    int br = shark_r;
    int bc = shark_c;
    int ss = 0;
    int d = 0;
    for(int s=1; s<=N; s++){
        for(int i=1; i<=2; i++){
            ss = s;
            if(ss == N) ss--;
            for(int j=1; j<=ss; j++){
                r += mr[d];
                c += mc[d];
                if(board[br][bc] == 0){
                    board[br][bc] = board[r][c];
                    board[r][c] = 0;
                }
                br = r;
                bc = c;
            }
            if(s == N) return;
            d = (d+1)%4;
        }
    }
}

int bead_bomb(){
    beads_group.clear();
    beads.clear();
    int r = shark_r;
    int c = shark_c;
    int ss = 0;
    int d = 0;
    bool check = true;
    for(int s=1; s<=N; s++){
        for(int i=1; i<=2; i++){
            ss = s;
            if(ss == N) ss--;
            for(int j=1; j<=ss; j++){
                r += mr[d];
                c += mc[d];
                if(beads.empty()) beads.push_back({r, c});
                else if(board[beads.back().first][beads.back().second] == board[r][c]){
                    beads.push_back({r, c});
                }
                else{
                    if(beads.size() >= 4) beads_group.push_back(beads);
                    beads.clear();
                    beads.push_back({r, c});
                }
            }
            if(s == N){
                check = false;
                break;
            }
            d = (d+1)%4;
        }
        if(!check) break;
    }
    int cnt = 0;
    for(int i=0; i<beads_group.size(); i++){
        bomb_beads_cnt[board[beads_group[i].back().first][beads_group[i].back().second]] += beads_group[i].size();
        cnt += beads_group[i].size();
        for(int j=0; j<beads_group[i].size(); j++){
            board[beads_group[i][j].first][beads_group[i][j].second] = 0;
        }
    }
    return cnt;
}

void change_beads(){
    beads_group.clear();
    beads.clear();
    int r = shark_r;
    int c = shark_c;
    int ss = 0;
    int d = 0;
    bool check = true;
    for(int s=1; s<=N; s++){
        for(int i=1; i<=2; i++){
            ss = s;
            if(ss == N) ss--;
            for(int j=1; j<=ss; j++){
                r += mr[d];
                c += mc[d];
                if(beads.empty()) beads.push_back({r, c});
                else if(board[beads.back().first][beads.back().second] == board[r][c]){
                    beads.push_back({r, c});
                }
                else{
                    beads_group.push_back(beads);
                    beads.clear();
                    beads.push_back({r, c});
                }
            }
            if(s == N){
                check = false;
                break;
            }
            d = (d+1)%4;
        }
        if(!check) break;
    }
    
    int A = 0;
    int B = 0;
    new_beads.clear();
    for(int i=0; i<beads_group.size(); i++){
        A = beads_group[i].size();
        B = board[beads_group[i].back().first][beads_group[i].back().second];
        new_beads.push_back(A);
        new_beads.push_back(B);
    }
    
    r = shark_r;
    c = shark_c;
    ss = 0;
    d = 0;
    int k = 0;
    check = true;
    for(int s=1; s<=N; s++){
        for(int i=1; i<=2; i++){
            ss = s;
            if(ss == N) ss--;
            for(int j=1; j<=ss; j++){
                r += mr[d];
                c += mc[d];
                if(k >= new_beads.size()) board[r][c] = 0;
                else board[r][c] = new_beads[k];
                k++;
            }
            if(s == N){
                check = false;
                break;
            }
            d = (d+1)%4;
        }
        if(!check) break;
    }
}

void play_blizards(){
    for(int i=0; i<M; i++){
        //1. 블리자드 시전
        for(int s=blizards[i].second; s>=1; s--){
            int br = shark_r + dr[blizards[i].first]*s;
            int bc = shark_c + dc[blizards[i].first]*s;
            board[br][bc] = 0;
        }
        //2. 구슬 이동
        for(int j=0; j<=blizards[i].second; j++) move_beads();
        //3. 구슬 폭발
        int cnt = bead_bomb();
        //4. 구슬 이동
        while(cnt > 0){
            for(int j=1; j<=cnt; j++) move_beads();
            cnt = bead_bomb();
        }
        //5. 구슬 변화
        change_beads();
    }
}

int main(int argc, const char * argv[]) {
    cin >> N >> M;
    for(int r=1; r<=N; r++){
        for(int c=1; c<=N; c++){
            cin >> board[r][c];
        }
    }
    for(int i=0; i<M; i++){
        int d, s;
        cin >> d >> s;
        blizards.push_back({d, s});
    }
    shark_r = (N+1)/2;
    shark_c = (N+1)/2;
    board[shark_r][shark_c] = -1;
    play_blizards();
    cout << 1*bomb_beads_cnt[1] + 2*bomb_beads_cnt[2] + 3* bomb_beads_cnt[3] << endl;
    return 0;
}
