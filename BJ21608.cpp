//
//  main.cpp
//  BJ21608_1
//
//  Created by Hwayeon on 2021/10/17.
//

#include <iostream>
#include <math.h>
#include <vector>
#include <queue>
using namespace std;

int N;
int room[21][21] = {0, };

struct Student{
    int s_id;
    int like[4] = {0, };
};
Student st;
Student students[401];
vector<Student> cmds;

struct Seat{
    int x;
    int y;
    int hole = 0;
    int like = 0;
};
Seat seat;
struct cmp{
    bool operator()(Seat s1, Seat s2){
        if(s1.like == s2.like){
            if(s1.hole == s2.hole){
                if(s1.y == s2.y){
                    return s1.x > s2.x;
                }
                return s1.y > s2.y;
            }
            return s1.hole < s2.hole;
        }
        return s1.like < s2.like;
    }
};
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, -1, 0, 1};

int satisfy = 0;

void find_seat(Student st){
    priority_queue<Seat, vector<Seat>, cmp> pq;
    for(int y=1; y<=N; y++){
        for(int x=1; x<=N; x++){
            if(room[y][x] > 0) continue;
            Seat new_seat;
            new_seat.x = x;
            new_seat.y = y;
            //1. 인접한 좋아하는 학생 수와 빈자리 수 구하기
            for(int d=0; d<4; d++){
                int nx = x + dx[d];
                int ny = y + dy[d];
                if(nx<=0 || nx>N || ny<=0 || ny>N) continue;
                if(room[ny][nx] == 0) new_seat.hole ++;
                else{
                    for(int i=0; i<4; i++){
                        if(room[ny][nx] == st.like[i]){
                            new_seat.like++;
                            break;
                        }
                    }
                }
            }
            //2. 자리 후보 우선순위 큐에 추가
            pq.push(new_seat);
        }
    }
    //자리 선정
    seat = pq.top();
    room[seat.y][seat.x] = st.s_id;
}

void get_satisfy(){
    for(int y=1; y<=N; y++){
        for(int x=1; x<=N; x++){
            int s_id = room[y][x];
            int cnt = 0;
            //인접한 좋아하는 친구 수 카운트
            for(int d=0; d<4; d++){
                int nx = x+dx[d];
                int ny = y+dy[d];
                if(nx<=0 || nx>N || ny<=0 || ny>N) continue;
                for(int i=0; i<4; i++){
                    if(room[ny][nx] == students[s_id].like[i]){
                        cnt++;
                        break;
                    }
                }
            }
            if(cnt == 0) continue;
            satisfy += pow(10, cnt-1);
        }
    }
}

int main(int argc, const char * argv[]) {
    cin >> N;
    for(int i=1; i<=N*N; i++){
        cin >> st.s_id >> st.like[0] >> st.like[1] >> st.like[2] >> st.like[3];
        students[st.s_id] = st;
        cmds.push_back(st);
    }
    //모든 학생을 자리에 앉힌다
    for(int i=0; i<cmds.size(); i++){
        st = cmds[i];
        find_seat(st);
    }
    //만족도 구하기
    get_satisfy();
    cout << satisfy << endl;
    
    return 0;
}
