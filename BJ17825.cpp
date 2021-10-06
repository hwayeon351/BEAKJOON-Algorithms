//
//  main.cpp
//  BJ17825
//
//  Created by Hwayeon on 2021/10/06.
//

#include <iostream>
#include <string.h>
using namespace std;

//map[loc] = loc 위치의 점수
//loc = 0 -> 출발지, loc = 32 -> 도착지
int map[33] = {0, 2, 4, 6, 8, 10,
    12, 14, 16, 18, 20,
    22, 24, 26, 28, 30,
    32, 34, 36, 38, 13,
    16, 19, 22, 24, 28,
    27, 26, 25, 30, 35, 40, 0};

/*
 1. go[loc][0] = loc 위치에서 방향 전환 없이 다음 위치로 가기 위한 거리값
    loc = 0~18, 20, 21, 23, 25~31 -> 거리값 = 1
    예외) loc = 19 -> 거리값 = 12, loc = 22 -> 거리값 = 6, loc = 24 -> 거리값 = 4
 
 2. go[loc][1] = loc 위치에서 방향 전환이 이뤄질 때 다음 위치로 가기 위한 거리값
    loc = 5 -> 거리값 = 15, loc = 10 -> 거리값 = 13, loc = 15 -> 거리값 = 10
    loc = 0~4, 6~9, 11~14, 16~31 -> 방향 전환 없음(거리값 = 0)
*/
int go[32][2] = {
    {1, 0}, {1, 0}, {1, 0}, {1, 0}, {1, 0}, {1, 15},
    {1, 0}, {1, 0}, {1, 0}, {1, 0}, {1, 13},
    {1, 0}, {1, 0}, {1, 0}, {1, 0}, {1, 10},
    {1, 0}, {1, 0}, {1, 0}, {12, 0},  {1, 0},
    {1, 0}, {6, 0}, {1, 0}, {4, 0}, {1, 0},
    {1, 0}, {1, 0}, {1, 0}, {1, 0}, {1, 0}, {1, 0}
};

//pieces[i] = i번째 말의 위치 loc
int pieces[4] = {0, 0, 0, 0};
int order[10] = {0, };
int turn[10] = {0, };
int max_score = 0;

void play_game(){
    memset(pieces, 0, sizeof(pieces));
    int score = 0;
    for(int i=0; i<10; i++){
        int piece = order[i];
        int now_loc = pieces[piece];
        if(now_loc >= 32) return;
        int now_turn = turn[i];
        int new_loc = 0;
        while(now_turn > 0){
            switch(now_loc){
                case 5:
                case 10:
                case 15:
                    if(now_turn == turn[i])
                        new_loc = now_loc + go[now_loc][1];
                    else
                        new_loc = now_loc + go[now_loc][0];
                    break;
                default:
                    new_loc = now_loc + go[now_loc][0];
                    break;
            }
            pieces[piece] = new_loc;
            now_loc = pieces[piece];
            new_loc = 0;
            now_turn--;
            if(now_loc >= 32) break;
        }
        //같은 위치의 말이 있는지 체크
        if(now_loc >= 32){
            pieces[piece] = 32;
            now_loc = 32;
        }
        else{
            for(int j=0; j<4; j++){
                if(piece == j) continue;
                if(pieces[j] == now_loc) return;
            }
        }
        score += map[now_loc];
    }
    if(score > max_score) max_score = score;
}

void get_order(int cnt){
    //말을 놓는 모든 경우의 수에 대해 게임을 진행
    if(cnt == 10){
        play_game();
        return;
    }
    for(int i=0; i<4; i++){
        order[cnt] = i;
        get_order(cnt+1);
        order[cnt] = 0;
    }
}

int main(int argc, const char * argv[]) {
    for(int i=0; i<10; i++){
        cin >> turn[i];
    }
    get_order(0);
    cout << max_score << endl;
    
    return 0;
}
