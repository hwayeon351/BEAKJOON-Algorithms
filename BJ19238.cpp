//
//  main.cpp
//  BJ19238
//
//  Created by 최화연 on 2022/04/24.
//

#include <iostream>
#include <queue>
using namespace std;

int N, M;
struct Texi {
    int r;
    int c;
    int fuel;
};
Texi texi;

struct Customer {
    int sr;
    int sc;
    int er;
    int ec;
    int s_dis;
};
struct cmp {
    bool operator() (Customer c1, Customer c2) {
        if (c1.s_dis == c2.s_dis) {
            if (c1.sr == c2.sr) {
                return c1.sc > c2.sc;
            }
            return c1.sr > c2.sr;
        }
        return c1.s_dis > c2.s_dis;
    }
};
Customer customer;
priority_queue<Customer, vector<Customer>, cmp> pq;

int map[21][21] = {0, };
int dr[4] = {0, -1, 0, 1};
int dc[4] = {-1, 0, 1, 0};

int get_dis_bfs(int sr, int sc, int er, int ec) {
    int visits[21][21] = {0, };
    queue<pair<pair<int, int>, int>> q;
    q.push({{sr, sc}, 0});
    visits[sr][sc] = 1;
    
    while (!q.empty()) {
        int r = q.front().first.first;
        int c = q.front().first.second;
        int dis = q.front().second;
        q.pop();
        if (r == er && c == ec) return dis;
        for (int d=0; d<4; d++) {
            int nr = r + dr[d];
            int nc = c + dc[d];
            if (nr < 1 || nr > N || nc < 1 || nc > N) continue;
            if (visits[nr][nc] || map[nr][nc]) continue;
            visits[nr][nc] = 1;
            q.push({{nr, nc}, dis+1});
        }
    }
    
    return -1;
}

void start_texi() {
    while (!pq.empty()) {
        customer = pq.top();
        pq.pop();
        
        if (customer.s_dis > texi.fuel) {
            texi.fuel = -1;
            return;
        }
        
        texi.r = customer.sr;
        texi.c = customer.sc;
        texi.fuel -= customer.s_dis;
        
        int e_dis = get_dis_bfs(texi.r, texi.c, customer.er, customer.ec);
        if (e_dis == -1 || e_dis > texi.fuel) {
            texi.fuel = -1;
            return;
        }
        
        texi.fuel += e_dis;
        texi.r = customer.er;
        texi.c = customer.ec;
        
        priority_queue<Customer, vector<Customer>, cmp> new_pq;
        while (!pq.empty()) {
            customer = pq.top();
            pq.pop();
            customer.s_dis = get_dis_bfs(texi.r, texi.c, customer.sr, customer.sc);
            new_pq.push(customer);
        }
        pq = new_pq;
    }
}

int main(int argc, const char * argv[]) {
    cin >> N >> M >> texi.fuel;
    
    for (int r=1; r<=N; r++) {
        for (int c=1; c<=N; c++) {
            cin >> map[r][c];
        }
    }
    
    cin >> texi.r >> texi.c;
    
    for (int m=0; m<M; m++) {
        cin >> customer.sr >> customer.sc >> customer.er >> customer.ec;
        customer.s_dis = get_dis_bfs(texi.r, texi.c, customer.sr, customer.sc);
        if (customer.s_dis == -1) {
            cout << -1 << endl;
            return 0;
        }
        pq.push(customer);
    }
    
    start_texi();
    cout << texi.fuel << endl;

    return 0;
}
