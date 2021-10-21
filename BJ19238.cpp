//
//  main.cpp
//  BJ19238_1
//
//  Created by Hwayeon on 2021/10/21.
//

#include <iostream>
#include <queue>
#include <string.h>
using namespace std;

int N, M;
long long gas;
int area[22][22] = {0, };
int visit[22][22] = {0, };
int texi_x, texi_y;

struct Customer{
    int num;
    int start_x;
    int start_y;
    int dest_x;
    int dest_y;
    int dis = 0;
    bool done = false;
};
struct cmp{
    bool operator()(Customer c1, Customer c2){
        if(c1.dis == c2.dis){
            if(c1.start_y == c2.start_y){
                return c1.start_x > c2.start_x;
            }
            return c1.start_y > c2.start_y;
        }
        return c1.dis > c2.dis;
    }
};
Customer cus;
Customer customers[401];

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, -1, 0, 1};

int cnt = 0;

Customer find_customer(){
    priority_queue<Customer, vector<Customer>, cmp> pq;
    for(int i=0; i<M; i++){
        if(customers[i].done) continue;
        cus = customers[i];
        memset(visit, 0, sizeof(visit));
        queue<pair<pair<int, int>, int>> q;
        q.push({{texi_x, texi_y}, 0});
        visit[texi_y][texi_x] = 1;
        while(!q.empty()){
            int x = q.front().first.first;
            int y = q.front().first.second;
            int dis = q.front().second;
            q.pop();
            if(x==cus.start_x && y==cus.start_y){
                cus.dis = dis;
                pq.push(cus);
                break;
            }
            for(int d=0; d<4; d++){
                int nx = x+dx[d];
                int ny = y+dy[d];
                if(nx<1 || nx>N || ny<1 || ny>N) continue;
                if(area[ny][nx]) continue;
                if(visit[ny][nx]) continue;
                visit[ny][nx] = 1;
                q.push({{nx, ny}, dis+1});
            }
        }
    }
    if(pq.empty()){
        cus.num = -1;
        return cus;
    }
    return pq.top();
}

void start_texi(){
    while(cnt < M){
        cus = find_customer();
        if(cus.num == -1){
            gas = -1;
            break;
        }
        //1. 손님 태우러 이동
        gas -= cus.dis;
        if(gas < 0){
            gas = -1;
            break;
        }
        texi_x = cus.start_x;
        texi_y = cus.start_y;
        
        //2. 목적지로 이동
        memset(visit, 0, sizeof(visit));
        queue<pair<pair<int, int>, int>> q;
        q.push({{texi_x, texi_y}, 0});
        visit[texi_y][texi_x] = 1;
        int dest_dis = 0;
        while(!q.empty()){
            int x = q.front().first.first;
            int y = q.front().first.second;
            int dis = q.front().second;
            q.pop();
            if(x==cus.dest_x && y==cus.dest_y){
                gas -= dis;
                dest_dis = dis;
                texi_x = x;
                texi_y = y;
                customers[cus.num].done = true;
                break;
            }
            for(int d=0; d<4; d++){
                int nx = x+dx[d];
                int ny = y+dy[d];
                if(nx<1 || nx>N || ny<1 || ny>N) continue;
                if(area[ny][nx]) continue;
                if(visit[ny][nx]) continue;
                visit[ny][nx] = 1;
                q.push({{nx, ny}, dis+1});
            }
        }
        if(dest_dis == 0 || gas < 0){
            gas = -1;
            break;
        }
        cnt++;
        gas += (2*dest_dis);
    }
}

int main(int argc, const char * argv[]) {
    cin >> N >> M >> gas;
    for(int y=1; y<=N; y++){
        for(int x=1; x<=N; x++){
            cin >> area[y][x];
        }
    }
    cin >> texi_y >> texi_x;
    for(int i=0; i<M; i++){
        cin >> cus.start_y >> cus.start_x >> cus.dest_y >> cus.dest_x;
        cus.num = i;
        customers[i] = cus;
    }
    
    start_texi();
    cout << gas << endl;
    
    return 0;
}
