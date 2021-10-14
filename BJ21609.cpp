//
//  main.cpp
//  BJ21609
//
//  Created by Hwayeon on 2021/10/14.
//

#include <iostream>
#include <math.h>
#include <string.h>
#include <queue>
#include <vector>
using namespace std;

int N, M;
int board[20][20] = {0, };
int copy_board[20][20] = {0, };
int visit[20][20] = {0, };
int score = 0;

struct Group{
    int pr;
    int pc;
    int rainbow_blocks_cnt = 0;
    int blocks_cnt = 0;
    vector<pair<int, int>> blocks;
};
Group group;
struct cmp{
    bool operator()(Group g1, Group g2){
        if(g1.blocks_cnt == g2.blocks_cnt){
            if(g1.rainbow_blocks_cnt == g2.rainbow_blocks_cnt){
                if(g1.pr == g2.pr){
                    return g1.pc < g2.pc;
                }
                return g1.pr < g2.pr;
            }
            return g1.rainbow_blocks_cnt < g2.rainbow_blocks_cnt;
        }
        return g1.blocks_cnt < g2.blocks_cnt;
    }
};
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, -1, 0, 1};
vector<pair<int, int>> rainbow_blocks;

Group find_group(int sr, int sc){
    Group new_group;
    new_group.pr = sr;
    new_group.pc = sc;
    new_group.blocks_cnt = 1;
    new_group.blocks.push_back({sr, sc});
    queue<pair<int, int>> q;
    q.push({sr, sc});
    visit[sr][sc] = 1;
    while(!q.empty()){
        int now_r = q.front().first;
        int now_c = q.front().second;
        q.pop();
        for(int d=0; d<4; d++){
            int nr = now_r + dy[d];
            int nc = now_c + dx[d];
            if(nr < 0 || nr >= N || nc < 0 || nc >= N) continue;
            if(visit[nr][nc]) continue;
            if(board[nr][nc] == -1) continue;
            if(board[nr][nc] == 0){
                visit[nr][nc] = 1;
                new_group.blocks_cnt++;
                new_group.rainbow_blocks_cnt++;
                new_group.blocks.push_back({nr, nc});
                q.push({nr, nc});
            }
            else if(board[nr][nc] == board[sr][sc]){
                visit[nr][nc] = 1;
                new_group.blocks_cnt++;
                new_group.blocks.push_back({nr, nc});
                q.push({nr, nc});
            }
        }
    }
    for(int i=0; i<rainbow_blocks.size(); i++){
        visit[rainbow_blocks[i].first][rainbow_blocks[i].second] = 0;
    }
    return new_group;
}

void apply_gravity(){
    for(int c=0; c<N; c++){
        for(int r=N-1; r>=0; r--){
            if(board[r][c] == -2 || board[r][c] == -1) continue;
            for(int rr=r; rr<N-1; rr++){
                if(board[rr+1][c] != -2){
                    if(rr != r){
                        board[rr][c] = board[r][c];
                        board[r][c] = -2;
                    }
                    break;
                }
                else if(rr == N-2){
                    board[N-1][c] = board[r][c];
                    board[r][c] = -2;
                }
            }
        }
    }
}

void rotate_board(){
    memcpy(copy_board, board, sizeof(board));
    int rr = 0;
    int cc = 0;
    for(int c=N-1; c>=0; c--){
        cc = 0;
        for(int r=0; r<N; r++){
            board[rr][cc] = copy_board[r][c];
            cc++;
        }
        rr++;
    }
}

void play_auto_game(){
    while(true){
        //1. find groups
        memset(visit, 0, sizeof(visit));
        priority_queue<Group, vector<Group>, cmp> groups;
        for(int r=0; r<N; r++){
            for(int c=0; c<N; c++){
                if(board[r][c] == -1 || board[r][c] == 0 || board[r][c] == -2) continue;
                if(visit[r][c]) continue;
                group = find_group(r, c);
                if(group.blocks_cnt >= 2) groups.push(group);
            }
        }
        if(groups.empty()) break;
        //2. erase blocks in group and get score
        group = groups.top();
        score += pow(group.blocks_cnt, 2);
        for(int i=0; i<group.blocks.size(); i++){
            board[group.blocks[i].first][group.blocks[i].second] = -2;
        }
        //3. apply gravity
        apply_gravity();
        //4. rotate 90 degrees
        rotate_board();
        //5. re-apply gravity
        apply_gravity();
        //6. update rainbow blocks location
        rainbow_blocks.clear();
        for(int r=0; r<N; r++){
            for(int c=0; c<N; c++){
                if(board[r][c]==0){
                    rainbow_blocks.push_back({r, c});
                }
            }
        }
    }
}

int main(int argc, const char * argv[]) {
    cin >> N >> M;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cin >> board[i][j];
            if(board[i][j] == 0){
                rainbow_blocks.push_back({i, j});
            }
        }
    }
    play_auto_game();
    cout << score << endl;
    return 0;
}
