//
//  main.cpp
//  BJ3190
//
//  Created by Hwayeon on 2021/07/18.
//

#include <iostream>
#include <deque>
using namespace std;

int map[101][101] = {0,};
int N, K, L;
int change[100][2] = {0, };

//+ -> 오른쪽 회전 D => (i+1)%4
//- -> 왼쪽 회전 L => (i+3)%4
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
int timer = 0;

deque<pair<int, int>> snake;
int s_dir = 0;

void start_dummy(){
    map[1][1] = 1;
    snake.push_back(make_pair(1, 1));
    int l = 0;
    while(1){
        if(l<=L-1 and change[l][0] == timer){
            s_dir = (s_dir + change[l][1])%4;
            l++;
        }
        timer ++;
        //머리 이동할 다음 칸
        int nx = snake.front().first + dx[s_dir];
        int ny = snake.front().second + dy[s_dir];
        //벽에 부딪힌 경우
        if(nx < 1 || nx > N || ny < 1 || ny > N) return;
        //자기 몸과 부딪힌 경우
        if(map[ny][nx] == 1) return;
        //사과가 있는 경우
        else if(map[ny][nx] == 4){
            //머리만 이동
            map[ny][nx] = 1;
            snake.push_front(make_pair(nx, ny));
        }
        //사과가 없는 경우
        else{
            //머리 이동
            map[ny][nx] = 1;
            snake.push_front(make_pair(nx, ny));
            //꼬리 이동
            pair<int, int> tail = snake.back();
            map[tail.second][tail.first] = 0;
            snake.pop_back();
        }
    }
}

int main(int argc, const char * argv[]) {
    cin >> N >> K;
    for(int i=0; i<K; i++){
        int x, y;
        cin >> y >> x;
        map[y][x] = 4;
    }
    cin >> L;
    for(int i=0; i<L; i++){
        char dir;
        cin >> change[i][0] >> dir;
        if(dir == 'L') change[i][1] = 3;
        else change[i][1] = 1;
    }
    
    start_dummy();
    cout << timer << endl;
    return 0;
}
