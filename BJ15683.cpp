//
//  main.cpp
//  BJ15683
//
//  Created by Hwayeon on 2021/08/03.
//

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int N, M;
int office[8][8] = {0, };
int c_office[8][8] = {0, };

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

//cctv_info[c_num][d_num][d]
vector<vector<vector<int>>> cctv_info = {
    {{}},
    //cctv1
    {{0}, {1}, {2}, {3}},
    //cctv2
    {{0,2}, {1,3}},
    //cctv3
    {{0,3}, {1,0}, {1,2}, {2,3}},
    //cctv4
    {{0,2,3}, {0,1,3}, {0,1,2}, {1,2,3}},
    //cctv5
    {{0,1,2,3}}
};

//cctvs[i] = {c_num, {x, y}}
vector<pair<int, pair<int, int>>> cctvs;
int answer = 64;

int cal_blind_spot(){
    int cnt = 0;
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            if(c_office[i][j] == 0){
                cnt ++;
            }
        }
    }
    return cnt;
}

void copy_office(){
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            c_office[i][j] = office[i][j];
        }
    }
}

void turn_direction(){
    if(cctvs.size()==0){
        copy_office();
        answer = cal_blind_spot();
        return;
    }
    queue<vector<pair<int, int>>> q;
    vector<pair<int, int>> cc;
    int c_num = cctvs[0].first;
    int d_kinds = int(cctv_info[c_num].size());
    int d_num;
    for(int i=0; i<d_kinds; i++){
        cc.clear();
        cc.push_back({c_num, i});
        q.push(cc);
    }
    while(!q.empty()){
        cc.clear();
        cc = q.front();
        q.pop();
        if(cc.size() == cctvs.size()){
            copy_office();
            for(int i=0; i<cctvs.size(); i++){
                c_num = cc[i].first;
                d_num = cc[i].second;
                int x = cctvs[i].second.first;
                int y = cctvs[i].second.second;
                for(int d=0; d<cctv_info[c_num][d_num].size(); d++){
                    int nx = x+dx[cctv_info[c_num][d_num][d]];
                    int ny = y+dy[cctv_info[c_num][d_num][d]];
                    while(true){
                        //사무실을 벗어난 경우
                        if(ny < 0 or ny > N-1 or nx < 0 or nx > M-1) break;
                        
                        //벽인 경우
                        if(c_office[ny][nx] == 6) break;
                        //빈 칸인 경우
                        else if(c_office[ny][nx] == 0) c_office[ny][nx] = 9;
                        
                        nx += dx[cctv_info[c_num][d_num][d]];
                        ny += dy[cctv_info[c_num][d_num][d]];
                    }
                }
            }
            int b_spot = cal_blind_spot();
            if(answer > b_spot) answer = b_spot;
            continue;
        }
        c_num = cctvs[int(cc.size())].first;
        d_kinds = int(cctv_info[c_num].size());
        for(int i=0; i<d_kinds; i++){
            cc.push_back({c_num, i});
            q.push(cc);
            cc.pop_back();
        }
    }
}

int main(int argc, const char * argv[]) {
    cin >> N >> M;
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            cin >> office[i][j];
            //cctv인 경우
            if(office[i][j] >= 1 and office[i][j] <= 5){
                cctvs.push_back({office[i][j], {j, i}});
            }
        }
    }
    turn_direction();
    cout << answer << endl;
    return 0;
}
