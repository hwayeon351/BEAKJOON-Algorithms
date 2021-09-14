//
//  main.cpp
//  BJ19238
//
//  Created by Hwayeon on 2021/09/14.
//

#include <iostream>
#include <queue>
#include <string.h>
using namespace std;

int N, M, gas;
int area[21][21] = {0, };
int visit[21][21] = {0, };
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, -1, 0, 1};
int texi_x, texi_y;

struct Customer{
    int start_x;
    int start_y;
    int dest_x;
    int dest_y;
    int dist_texi;
    int dist_dest;
};
Customer customer;
struct cmp{
    bool operator()(Customer c1, Customer c2){
        if(c1.dist_texi == c2.dist_texi){
            if(c1.start_y == c2.start_y){
                return c1.start_x > c2.start_x;
            }
            return c1.start_y > c2.start_y;
        }
        return c1.dist_texi > c2.dist_texi;
    }
};

priority_queue<Customer, vector<Customer>, cmp> customers;

int get_dist(int start_x, int start_y, int dest_x, int dest_y){
    int dist = -1;
    memset(visit, 0, sizeof(visit));
    visit[start_y][start_x] = 1;
    queue<pair<pair<int, int>, int>> q;
    q.push(make_pair(make_pair(start_x, start_y), 0));
    while(!q.empty()){
        int now_x = q.front().first.first;
        int now_y = q.front().first.second;
        int now_dist = q.front().second;
        q.pop();
        if(now_y == dest_y && now_x == dest_x){
            dist = now_dist;
            break;
        }
        for(int d=0; d<4; d++){
            int nx = now_x + dx[d];
            int ny = now_y + dy[d];
            if(nx<1 || nx>N || ny<1 || ny>N) continue;
            if(visit[ny][nx] == 1) continue;
            if(area[ny][nx] == 1) continue;
            q.push({{nx, ny}, now_dist+1});
            visit[ny][nx] = 1;
        }
    }
    return dist;
}


int main(int argc, const char * argv[]) {
    cin >> N >> M >> gas;
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            cin >> area[i][j];
        }
    }
    cin >> texi_y >> texi_x;
    bool check = true;
    for(int i=0; i<M; i++){
        cin >> customer.start_y >> customer.start_x >> customer.dest_y >> customer.dest_x;
        customer.dist_texi = get_dist(texi_x, texi_y, customer.start_x, customer.start_y);
        customer.dist_dest = get_dist(customer.start_x, customer.start_y, customer.dest_x, customer.dest_y);
        if(customer.dist_texi == -1 || customer.dist_dest == -1){
            check = false;
            continue;
        }
        customers.push(customer);
    }
    
    if(!check){
        cout << -1 << endl;
        return 0;
    }

    while(!customers.empty()){
        //1. 승객 태우기
        customer = customers.top();
        customers.pop();
        texi_x = customer.start_x;
        texi_y = customer.start_y;
        gas -= customer.dist_texi;
        if(gas <= 0){
            gas = -1;
            break;
        }
        
        //2. 목적지로 가기
        texi_x = customer.dest_x;
        texi_y = customer.dest_y;
        gas -= customer.dist_dest;
        if(gas < 0){
            gas = -1;
            break;
        }
        gas += (2*customer.dist_dest);
        
        //3. 승객 우선순위 재정렬
        priority_queue<Customer, vector<Customer>, cmp> copy_customers;
        while(!customers.empty()){
            customer = customers.top();
            customers.pop();
            customer.dist_texi = get_dist(texi_x, texi_y, customer.start_x, customer.start_y);
            copy_customers.push(customer);
        }
        customers = copy_customers;
    }
    cout << gas << endl;
    return 0;
}
