//
//  main.cpp
//  BJ12100
//
//  Created by Hwayeon on 2021/10/17.
//

#include <iostream>
#include <string.h>
#include <vector>
using namespace std;

int N;
int board[21][21] = {0, };
int copy_board[21][21] = {0, };

vector<int> cmds;
vector<int> temp;
long long max_block = 0;

void play_game(){
    memcpy(copy_board, board, sizeof(board));
    for(int i=0; i<cmds.size(); i++){
        int d = cmds[i];
        switch (d) {
            //좌
            case 0:
                for(int y=0; y<N; y++){
                    for(int x=N-1; x>=0; x--){
                        if(copy_board[y][x] == 0) continue;
                        temp.push_back(copy_board[y][x]);
                        copy_board[y][x] = 0;
                    }
                    int xx = 0;
                    while(!temp.empty()){
                        int num = temp.back();
                        temp.pop_back();
                        if(!temp.empty() && temp.back() == num){
                            num += temp.back();
                            temp.pop_back();
                        }
                        copy_board[y][xx] = num;
                        xx++;
                    }
                }
                break;
            //상
            case 1:
                for(int x=0; x<N; x++){
                    for(int y=N-1; y>=0; y--){
                        if(copy_board[y][x] == 0) continue;
                        temp.push_back(copy_board[y][x]);
                        copy_board[y][x] = 0;
                    }
                    int yy=0;
                    while(!temp.empty()){
                        int num = temp.back();
                        temp.pop_back();
                        if(!temp.empty() && temp.back() == num){
                            num += temp.back();
                            temp.pop_back();
                        }
                        copy_board[yy][x] = num;
                        yy++;
                    }
                }
                break;
            //우
            case 2:
                for(int y=0; y<N; y++){
                    for(int x=0; x<N; x++){
                        if(copy_board[y][x] == 0) continue;
                        temp.push_back(copy_board[y][x]);
                        copy_board[y][x] = 0;
                    }
                    int xx = N-1;
                    while(!temp.empty()){
                        int num = temp.back();
                        temp.pop_back();
                        if(!temp.empty() && temp.back() == num){
                            num += temp.back();
                            temp.pop_back();
                        }
                        copy_board[y][xx] = num;
                        xx--;
                    }
                }
                break;
            //하
            case 3:
                for(int x=0; x<N; x++){
                    for(int y=0; y<N; y++){
                        if(copy_board[y][x] == 0) continue;
                        temp.push_back(copy_board[y][x]);
                        copy_board[y][x] = 0;
                    }
                    int yy=N-1;
                    while(!temp.empty()){
                        int num = temp.back();
                        temp.pop_back();
                        if(!temp.empty() && temp.back() == num){
                            num += temp.back();
                            temp.pop_back();
                        }
                        copy_board[yy][x] = num;
                        yy--;
                    }
                }
                break;
        }
    }
}

void get_max_block(){
    long long max_b = 0;
    for(int y=0; y<N; y++){
        for(int x=0; x<N; x++){
            if(copy_board[y][x] > max_b) max_b = copy_board[y][x];
        }
    }
    if(max_b > max_block) max_block = max_b;
}

void get_cmds(int cnt){
    if(cnt == 5){
        play_game();
        get_max_block();
        return;
    }
    for(int d=0; d<4; d++){
        cmds.push_back(d);
        get_cmds(cnt+1);
        cmds.pop_back();
    }
}

int main(int argc, const char * argv[]) {
    cin >> N;
    for(int y=0; y<N; y++){
        for(int x=0; x<N; x++){
            cin >> board[y][x];
        }
    }
    get_cmds(0);
    cout << max_block << endl;
    
    return 0;
}
