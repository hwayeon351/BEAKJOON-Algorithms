//
//  main.cpp
//  BJ20056
//
//  Created by Hwayeon on 2021/10/14.
//

#include <iostream>
#include <queue>
using namespace std;

int N, M, K;
int board[51][51] = {0, };
int dc[8] = {0, 1, 1, 1, 0, -1, -1, -1};
int dr[8] = {-1, -1, 0, 1, 1, 1, 0, -1};

struct Fireball{
    int r;
    int c;
    int m;
    int s;
    int d;
};
Fireball fireball;
struct cmp{
    bool operator()(Fireball f1, Fireball f2){
        if(f1.r == f2.r){
            return f1.c > f2.c;
        }
        return f1.r > f2.r;
    }
};
priority_queue<Fireball, vector<Fireball>, cmp> fireballs;
priority_queue<Fireball, vector<Fireball>, cmp> new_fireballs;
vector<Fireball> group_fireballs;
int total_fireballs_mass = 0;

void move_fireballs(){
    for(int k=0; k<K; k++){
        total_fireballs_mass = 0;
        //1.
        while(!fireballs.empty()){
            fireball = fireballs.top();
            fireballs.pop();
            int new_r = fireball.r;
            int new_c = fireball.c;
            for(int s=fireball.s; s>0; s--){
                new_r += dr[fireball.d];
                new_c += dc[fireball.d];
                if(new_r == 0) new_r = N;
                else if(new_r == N+1) new_r = 1;
                if(new_c == 0) new_c = N;
                else if(new_c == N+1) new_c = 1;
            }
            board[fireball.r][fireball.c]--;
            fireball.r = new_r;
            fireball.c = new_c;
            board[fireball.r][fireball.c]++;
            new_fireballs.push(fireball);
        }
        //2.
        while(!new_fireballs.empty()){
            fireball = new_fireballs.top();
            new_fireballs.pop();
            if(board[fireball.r][fireball.c] == 1){
                fireballs.push(fireball);
                total_fireballs_mass += fireball.m;
                continue;
            }
            int cnt = board[fireball.r][fireball.c]-1;
            group_fireballs.clear();
            group_fireballs.push_back(fireball);
            while(cnt > 0){
                fireball = new_fireballs.top();
                new_fireballs.pop();
                group_fireballs.push_back(fireball);
                cnt--;
            }
            int sum_m = 0;
            int sum_s = 0;
            int d = 0;
            for(int i=0; i<group_fireballs.size(); i++){
                sum_m += group_fireballs[i].m;
                sum_s += group_fireballs[i].s;
                d += (group_fireballs[i].d%2);
            }
            int m = sum_m/5;
            if(m == 0){
                board[group_fireballs[0].r][group_fireballs[0].c] = 0;
                group_fireballs.clear();
                continue;
            }
            fireball.r = group_fireballs[0].r;
            fireball.c = group_fireballs[0].c;
            fireball.m = m;
            fireball.s = sum_s/group_fireballs.size();
            board[fireball.r][fireball.c] = 4;
            total_fireballs_mass += (4*fireball.m);
            if(d == 0 || d == group_fireballs.size()){
                for(int d=0; d<=6; d+=2){
                    fireball.d = d;
                    fireballs.push(fireball);
                }
            }
            else{
                for(int d=1; d<=7; d+=2){
                    fireball.d = d;
                    fireballs.push(fireball);
                }
            }
        }
    }
}

int main(int argc, const char * argv[]) {
    cin >> N >> M >> K;
    for(int i=0; i<M; i++){
        cin >> fireball.r >> fireball.c >> fireball.m >> fireball.s >> fireball.d;
        board[fireball.r][fireball.c]++;
        fireballs.push(fireball);
    }
    if(M == 0){
        cout << 0 << endl;
        return 0;
    }
    move_fireballs();
    cout << total_fireballs_mass << endl;
    return 0;
}
