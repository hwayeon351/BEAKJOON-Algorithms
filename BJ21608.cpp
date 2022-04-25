//
//  main.cpp
//  BJ21608
//
//  Created by 최화연 on 2022/04/26.
//

#include <iostream>
#include <cmath>
#include <queue>
using namespace std;

int N;

struct Student {
    int s_num = 0;
    int like[4] = {0, };
};
Student student;
Student room[21][21];
queue<Student> students;

struct Seat {
    int r;
    int c;
    int like = 0;
    int hole = 0;
};
struct cmp {
    bool operator() (Seat s1, Seat s2) {
        if (s1.like == s2.like) {
            if (s1.hole == s2.hole) {
                if (s1.r == s2.r) {
                    return s1.c > s2.c;
                }
                return s1.r > s2.r;
            }
            return s1.hole < s2.hole;
        }
        return s1.like < s2.like;
    }
};
Seat seat;

int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, -1, 0, 1};

void assign_seat() {
    while (!students.empty()) {
        student = students.front();
        students.pop();
        
        priority_queue<Seat, vector<Seat>, cmp> pq;
        for (int r=1; r<=N; r++) {
            for (int c=1; c<=N; c++) {
                if (room[r][c].s_num > 0) continue;
                Seat s;
                s.r = r;
                s.c = c;
                for (int d=0; d<4; d++) {
                    int nr = r + dr[d];
                    int nc = c + dc[d];
                    if (nr < 1 || nr > N || nc < 1 || nc > N) continue;
                    if (room[nr][nc].s_num == 0) {
                        s.hole ++;
                        continue;
                    }
                    for (int i=0; i<4; i++) {
                        if (room[nr][nc].s_num == student.like[i]) {
                            s.like ++;
                            break;
                        }
                    }
                }
                pq.push(s);
            }
        }
        
        seat = pq.top();
        pq.pop();
        room[seat.r][seat.c] = student;
    }
}

int get_satisfy() {
    int answer = 0;
    for (int r=1; r<=N; r++) {
        for (int c=1; c<=N; c++) {
            int like = 0;
            for (int d=0; d<4; d++) {
                int nr = r + dr[d];
                int nc = c + dc[d];
                if (nr < 1 || nr > N || nc < 1 || nc > N) continue;
                for (int i=0; i<4; i++) {
                    if (room[nr][nc].s_num == room[r][c].like[i]) {
                        like ++;
                        break;
                    }
                }
            }
            if (like == 0) continue;
            answer += pow(10, like-1);
        }
    }
    
    return answer;
}


int main(int argc, const char * argv[]) {
    cin >> N;
    for (int i=0; i<N*N; i++) {
        cin >> student.s_num;
        for (int j=0; j<4; j++) {
            cin >> student.like[j];
        }
        students.push(student);
    }
    
    assign_seat();
    cout << get_satisfy() << endl;
    
    return 0;
}
