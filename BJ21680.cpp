//
//  main.cpp
//  BJ21680
//
//  Created by Hwayeon on 2021/07/14.
//

#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Seat{
    int x;
    int y;
    int like;
    int hole;
};

struct cmp{
    bool operator()(Seat a, Seat b){
        if(a.like == b.like){
            if(a.hole == b.hole){
                if(a.y == b.y){
                    return a.x > b.x;
                }
                return a.y > b.y;
            }
            return a.hole < b.hole;
        }
        return a.like < b.like;
    }
};

int N;
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, -1, 0, 1};

Seat s;
int room[20][20] = {0,};
int order_s[400] = {0, };
int st[400][4] = {0,};
long long answer = 0;
int s_num = 0;
int cnt;

int main(int argc, const char * argv[]) {
    cin >> N;
    for(int i=0; i<N*N; i++){
        cin >> s_num;
        order_s[i] = s_num;
        for(int j=0; j<4; j++){
            cin >> st[s_num][j];
        }
    }
    room[1][1] = order_s[0];
    //학생 순서 i
    for(int i=1; i<N*N; i++){
        //자리 탐색
        priority_queue<Seat, vector<Seat>, cmp> pq;
        for(int y=0; y<N; y++){
            for(int x=0; x<N; x++){
                //이미 배정된 자리
                if(room[y][x]!=0) continue;
                //빈 자리 pq에 추가
                s = {x, y, 0, 0};
                int nx, ny;
                for(int d=0; d<4; d++){
                    //인접 자리가 빈칸인 경우
                    nx = x+dx[d];
                    ny = y+dy[d];
                    if(nx<0 || nx>N-1 || ny<0 || ny>N-1) continue;
                    if(room[ny][nx] == 0){
                        s.hole++;
                    }
                    //인접 자리에 학생이 있는 경우
                    else{
                        //st[i] 학생이 좋아하는 학생인지 체크
                        for(int k=0; k<4; k++){
                            if(room[ny][nx] == st[order_s[i]][k]){
                                s.like++;
                                break;
                            }
                        }
                    }
                }
                pq.push(s);
            }
        }
        room[pq.top().y][pq.top().x] = order_s[i];
    }

    for(int y=0; y<N; y++){
        for(int x=0; x<N; x++){
            cnt = 0;
            s_num = room[y][x];
            for(int d=0; d<4; d++){
                int nx = x+dx[d];
                int ny = y+dy[d];
                if(nx<0 || nx>N-1 || ny<0 || ny>N-1) continue;
                for(int i=0; i<4; i++){
                    if(room[ny][nx] == st[s_num][i]){
                        cnt ++;
                        break;
                    }
                }
            }
            if(cnt == 1) answer++;
            else if(cnt == 2) answer += 10;
            else if(cnt == 3) answer += 100;
            else if(cnt == 4) answer += 1000;
        }
    }
    cout << answer << endl;
    return 0;
}
