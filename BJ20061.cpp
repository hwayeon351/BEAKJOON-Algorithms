//
//  main.cpp
//  BJ20061
//
//  Created by Hwayeon on 2021/10/13.
//

#include <iostream>
#include <vector>
using namespace std;

int N;

/*
 red board -> 0<=x<=3, 0<=y<=3
 blue board -> 6<=x<=9, 0<=y<=3
 sky blue board -> 4<=x<=5, 0<=y<=3
 green board -> 0<=x<=3, 6<=y<=9
 light green board -> 0<=x<=3, 4<=y<=5
 */
int board[10][10] = {0, };
struct Block{
    int t;
    int x;
    int y;
};
Block b;
vector<Block> blocks;
int score = 0;
int blue_blocks = 0;
int green_blocks = 0;

void put_block1(int bx, int by){
    //put block on blue board
    for(int x=4; x<=8; x++){
        if(board[by][x+1]){
            board[by][x] = 1;
            break;
        }
        else if(x == 8){
            board[by][9] = 1;
        }
    }
    //put block on green board
    for(int y=4; y<=8; y++){
        if(board[y+1][bx]){
            board[y][bx] = 1;
            break;
        }
        else if(y == 8){
            board[9][bx] = 1;
        }
    }
}

void put_block2(int bx, int by){
    //put block on blue board
    for(int x=4; x<=8; x++){
        if(board[by][x+1]){
            board[by][x] = 1;
            board[by][x-1] = 1;
            break;
        }
        else if(x == 8){
            board[by][9] = 1;
            board[by][8] = 1;
        }
    }
    
    //put block on green board
    for(int y=4; y<=8; y++){
        if(board[y+1][bx] || board[y+1][bx+1]){
            board[y][bx] = 1;
            board[y][bx+1] = 1;
            break;
        }
        else if(y == 8){
            board[9][bx] = 1;
            board[9][bx+1] = 1;
        }
    }
}

void put_block3(int bx, int by){
    //put block on blue board
    for(int x=4; x<=8; x++){
        if(board[by][x+1] || board[by+1][x+1]){
            board[by][x] = 1;
            board[by+1][x] = 1;
            break;
        }
        else if(x == 8){
            board[by][9] = 1;
            board[by+1][9] = 1;
        }
    }
    
    //put block on green board
    for(int y=4; y<=8; y++){
        if(board[y+1][bx]){
            board[y][bx] = 1;
            board[y-1][bx] = 1;
            break;
        }
        else if(y == 8){
            board[8][bx] = 1;
            board[9][bx] = 1;
        }
    }
}

void check_blue_board(){
    int x = 9;
    bool check = true;
    while(x >= 6){
        check = true;
        for(int y=0; y<4; y++){
            if(!board[y][x]) check = false;
        }
        if(!check){
            x--;
            continue;
        }
        score++;
        for(int xx=x; xx>=5; xx--){
            for(int y=0; y<4; y++){
                board[y][xx] = board[y][xx-1];
            }
        }
        for(int y=0; y<4; y++){
            board[y][4] = 0;
        }
    }
}

void check_green_board(){
    int y = 9;
    bool check = true;
    while(y >= 6){
        check = true;
        for(int x=0; x<4; x++){
            if(!board[y][x]) check = false;
        }
        if(!check){
            y--;
            continue;
        }
        score++;
        for(int yy=y; yy>=5; yy--){
            for(int x=0; x<4; x++){
                board[yy][x] = board[yy-1][x];
            }
        }
        for(int x=0; x<4; x++){
            board[4][x] = 0;
        }
    }
}

void check_sky_blue_board(){
    int check = 0;
    for(int x=5; x>=4; x--){
        for(int y=0; y<4; y++){
            if(board[y][x]){
                check++;
                break;
            }
        }
    }
    switch(check){
        case 0:
            break;
        case 1:
            for(int x=9; x>=6; x--){
                for(int y=0; y<4; y++){
                    board[y][x] = board[y][x-1];
                }
            }
            for(int y=0; y<4; y++){
                board[y][5] = 0;
            }
            break;
        case 2:
            for(int x=9; x>=5; x--){
                for(int y=0; y<4; y++){
                    board[y][x] = board[y][x-2];
                }
            }
            for(int x=4; x<=5; x++){
                for(int y=0; y<4; y++){
                    board[y][x] = 0;
                }
            }
            break;
    }
}

void check_light_green_board(){
    int check = 0;
    for(int y=5; y>=4; y--){
        for(int x=0; x<4; x++){
            if(board[y][x]){
                check++;
                break;
            }
        }
    }
    switch(check){
        case 0:
            break;
        case 1:
            for(int y=9; y>=6; y--){
                for(int x=0; x<4; x++){
                    board[y][x] = board[y-1][x];
                }
            }
            for(int x=0; x<4; x++){
                board[5][x] = 0;
            }
            break;
        case 2:
            for(int y=9; y>=5; y--){
                for(int x=0; x<4; x++){
                    board[y][x] = board[y-2][x];
                }
            }
            for(int y=4; y<=5; y++){
                for(int x=0; x<4; x++){
                    board[y][x] = 0;
                }
            }
            break;
    }
}

void monominodomino(){
    for(int i=0; i<blocks.size(); i++){
        b = blocks[i];
        //put block
        switch(b.t){
            case 1:
                put_block1(b.x, b.y);
                break;
            case 2:
                put_block2(b.x, b.y);
                break;
            case 3:
                put_block3(b.x, b.y);
                break;
        }
        //check board
        check_blue_board();
        check_green_board();
        check_sky_blue_board();
        check_light_green_board();
    }
}

int get_blocks(){
    //get blocks on blue block
    for(int y=0; y<4; y++){
        for(int x=6; x<=9; x++){
            blue_blocks += board[y][x];
        }
    }
    //get blocks on green block
    for(int y=6; y<=9; y++){
        for(int x=0; x<4; x++){
            green_blocks += board[y][x];
        }
    }
    return blue_blocks+green_blocks;
}

int main(int argc, const char * argv[]) {
    cin >> N;
    for(int i=0; i<N; i++){
        cin >> b.t >> b.y >> b.x;
        blocks.push_back(b);
    }
    monominodomino();
    cout << score << endl;
    cout << get_blocks() << endl;
    return 0;
}
