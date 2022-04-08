//
//  main.cpp
//  BJ3190
//
//  Created by 최화연 on 2022/04/08.
//

#include <iostream>
#include <queue>
#include <deque>
using namespace std;

int N, K, L;
int map[101][101] = {0, };
queue<pair<int, char>> cmds;

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, -1, 0, 1};
int sec = 0;

struct Snake {
    deque<pair<int, int>> body = {{1, 1}};
    int dir = 2;
};
Snake snake;

void play_game() {
    map[1][1] = 2;
    
    while (true) {
        sec++;
        
        //1. 뱀의 몸길이를 늘려 머리를 다음칸에 위치시킨다
        int head_x = snake.body.front().first+dx[snake.dir];
        int head_y = snake.body.front().second+dy[snake.dir];
        
        //2. 벽에 부딪힌 경우, 게임 끝
        if (head_x <= 0 || head_x > N || head_y <= 0 || head_y > N) return;
        //3. 몸에 부딪힌 경우, 게임 끝
        if (map[head_y][head_x] == 2) return;
        
        snake.body.push_front({head_x, head_y});
        
        //4. 이동한 칸에 사과가 있는 경우,
        if (map[head_y][head_x] == 1) {
            map[head_y][head_x] = 2;
        }
        
        //5. 이동한 칸에 사과가 없는 경우,
        else if (map[head_y][head_x] == 0) {
            map[head_y][head_x] = 2;
            int tail_x = snake.body.back().first;
            int tail_y = snake.body.back().second;
            snake.body.pop_back();
            map[tail_y][tail_x] = 0;
        }
        
        if (cmds.front().first == sec) {
            if (cmds.front().second == 'L') {
                snake.dir = (snake.dir - 1 + 4) % 4;
            } else {
                snake.dir = (snake.dir + 1) % 4;
            }
            cmds.pop();
        }
        
    }
}

int main(int argc, const char * argv[]) {
    cin >> N;
    cin >> K;
    for(int i=0; i<K; i++) {
        int y, x;
        cin >> y >> x;
        map[y][x] = 1;
    }
    cin >> L;
    for(int i=0; i<L; i++) {
        int X;
        char C;
        cin >> X >> C;
        cmds.push({X, C});
    }
    
    play_game();
    cout << sec << endl;
    
    return 0;
}
