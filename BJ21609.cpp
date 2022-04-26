//
//  main.cpp
//  BJ221609
//
//  Created by 최화연 on 2022/04/26.
//

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

int N, M;
int block[21][21] = {0, };
int copy_block[21][21] = {0, };
int visits[21][21] = {0, };

struct Group {
    int pr;
    int pc;
    int rainbow_cnt = 0;
    int cnt = 0;
};
struct cmp {
    bool operator() (Group g1, Group g2) {
        if (g1.cnt == g2.cnt) {
            if (g1.rainbow_cnt == g2.rainbow_cnt) {
                if (g1.pr == g2.pr) {
                    return g1.pc < g2.pc;
                }
                return g1.pr < g2.pr;
            }
            return g1.rainbow_cnt < g2.rainbow_cnt;
        }
        return g1.cnt < g2.cnt;
    }
};
Group group;

vector<pair<int, int>> rainbow_blocks;
int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, -1, 0, 1};

int total_score = 0;

Group bfs(int pr, int pc) {
    group.pr = pr;
    group.pc = pc;
    group.cnt = 1;
    group.rainbow_cnt = 0;
    queue<pair<int, int>> q;
    
    q.push({pr, pc});
    visits[pr][pc] = 1;
    
    for (int i=0; i<rainbow_blocks.size(); i++) {
        visits[rainbow_blocks[i].first][rainbow_blocks[i].second] = 0;
    }
    
    while (!q.empty()) {
        int r = q.front().first;
        int c = q.front().second;
        q.pop();
        for (int d=0; d<4; d++) {
            int nr = r + dr[d];
            int nc = c + dc[d];
            if (nr < 1 || nr > N || nc < 1 || nc > N) continue;
            if (visits[nr][nc]) continue;
            if (block[nr][nc] == block[pr][pc] || block[nr][nc] == 0) {
                visits[nr][nc] = 1;
                if (block[nr][nc] == 0) group.rainbow_cnt ++;
                group.cnt ++;
                q.push({nr, nc});
            }
        }
    }
    
    return group;
}

void erase_blocks(Group g) {
    int num = block[g.pr][g.pc];
    block[g.pr][g.pc] = -2;
    queue<pair<int, int>> q;
    q.push({g.pr, g.pc});
    
    while (!q.empty()) {
        int r = q.front().first;
        int c = q.front().second;
        q.pop();
        for (int d=0; d<4; d++) {
            int nr = r + dr[d];
            int nc = c + dc[d];
            if (nr < 1 || nr > N || nc < 1 || nc > N) continue;
            if (block[nr][nc] == num || block[nr][nc] == 0) {
                block[nr][nc] = -2;
                q.push({nr, nc});
            }
        }
    }
}

void gravity() {
    for (int c=1; c<=N; c++) {
        for (int r=N; r>=1; r--) {
            if (block[r][c] == -2 || block[r][c] == -1) continue;
            for (int rr=r; rr<N; rr++) {
                if (block[rr+1][c] != -2) break;
                block[rr+1][c] = block[rr][c];
                block[rr][c] = -2;
            }
        }
    }
}

void rotate_blocks() {
    memcpy(copy_block, block, sizeof(copy_block));
    for (int r=1; r<=N; r++) {
        for (int c=N; c>=1; c--) {
            block[N-c+1][r] = copy_block[r][c];
        }
    }
}

void get_rainbow_blocks() {
    rainbow_blocks.clear();
    for (int r=1; r<=N; r++) {
        for (int c=1; c<=N; c++) {
            if (block[r][c] == 0) {
                rainbow_blocks.push_back({r, c});
            }
        }
    }
}


void auto_play() {
    while (1) {
        //1. 크기가 가장 큰 블록그룹 찾기
        priority_queue<Group, vector<Group>, cmp> pq;
        memset(visits, 0, sizeof(visits));
        
        for (int r=1; r<=N; r++) {
            for (int c=1; c<=N; c++) {
                if (block[r][c] <= 0) continue;
                if (visits[r][c]) continue;
                group = bfs(r, c);
                if (group.cnt >= 2) pq.push(group);
            }
        }
        if (pq.empty()) break;
    
        //2. 블록 그룹의 블록 제거하기
        erase_blocks(pq.top());
        total_score += (pq.top().cnt * pq.top().cnt);
        
        //3. 중력 작용하기
        gravity();
        
        //4. 90도 반시계 방향으로 회전
        rotate_blocks();
        
        //5. 중력 작용하기
        gravity();
        
        //무지개블록 위치
        get_rainbow_blocks();
    }
}


int main(int argc, const char * argv[]) {
    cin >> N >> M;
    for (int r=1; r<=N; r++) {
        for (int c=1; c<=N; c++) {
            cin >> block[r][c];
            if (block[r][c] == 0) {
                rainbow_blocks.push_back({r, c});
            }
        }
    }
    
    auto_play();
    
    cout << total_score << endl;
    
    return 0;
}
