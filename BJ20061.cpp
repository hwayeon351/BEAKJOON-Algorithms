//
//  main.cpp
//  BJ20061
//
//  Created by 최화연 on 2022/04/27.
//

#include <iostream>
#include <vector>
using namespace std;

int N;
int board[10][10] = {0, };
vector<pair<int, pair<int, int>>> blocks;

int score = 0;

void put_block(int t, int r, int c) {
    //1. 파란색 보드에 블록 놓기
    switch (t) {
        case 1:
            for (int c=3; c<=8; c++) {
                if (c+1 == 9 && board[r][c+1] == 0) {
                    board[r][9] = 1;
                    break;
                }
                if (board[r][c+1] == 0) continue;
                board[r][c] = 1;
                break;
            }
            break;
            
        case 2:
            for (int c=3; c<=8; c++) {
                if (c+1 == 9 && board[r][c+1] == 0) {
                    board[r][9] = 1;
                    board[r][8] = 1;
                    break;
                }
                if (board[r][c+1] == 0) continue;
                board[r][c] = 1;
                board[r][c-1] = 1;
                break;
            }
            break;
            
        case 3:
            for (int c=3; c<=8; c++) {
                if (c+1 == 9 && board[r][c+1] == 0 && board[r+1][c+1] == 0) {
                    board[r][9] = 1;
                    board[r+1][9] = 1;
                    break;
                }
                if (board[r][c+1] == 0 && board[r+1][c+1] == 0) continue;
                board[r][c] = 1;
                board[r+1][c] = 1;
                break;
            }
            break;
    }
    
    
    //2. 초록색 보드에 블록 놓기
    switch (t) {
        case 1:
            for (int r=3; r<=8; r++) {
                if (r+1 == 9 && board[r+1][c] == 0) {
                    board[9][c] = 1;
                    break;
                }
                if (board[r+1][c] == 0) continue;
                board[r][c] = 1;
                break;
            }
            break;
            
        case 2:
            for (int r=3; r<=8; r++) {
                if (r+1 == 9 && board[r+1][c] == 0 && board[r+1][c+1] == 0) {
                    board[9][c] = 1;
                    board[9][c+1] = 1;
                    break;
                }
                if (board[r+1][c] == 0 && board[r+1][c+1] == 0) continue;
                board[r][c] = 1;
                board[r][c+1] = 1;
                break;
            }
            break;
            
        case 3:
            for (int r=3; r<=8; r++) {
                if (r+1 == 9 && board[r+1][c] == 0) {
                    board[9][c] = 1;
                    board[8][c] = 1;
                    break;
                }
                if (board[r+1][c] == 0) continue;
                board[r][c] = 1;
                board[r-1][c] = 1;
                break;
            }
            break;
    }
}

void check_green_board() {
    int r=9;
    while (r > 5) {
        bool check = true;
        for (int c=0; c<=3; c++) {
            if (board[r][c] == 0) {
                check = false;
                break;
            }
        }
        if (!check) {
            r--;
            continue;
        }
        score++;
        for (int c=0; c<=3; c++) {
            for (int rr=r; rr>=4; rr--) {
                board[rr][c] = board[rr-1][c];
            }
        }
    }
}

void check_blue_board() {
    int c=9;
    while (c > 5) {
        bool check = true;
        for (int r=0; r<=3; r++) {
            if (board[r][c] == 0) {
                check = false;
                break;
            }
        }
        if (!check) {
            c--;
            continue;
        }
        score++;
        for (int r=0; r<=3; r++) {
            for (int cc=c; cc>=4; cc--) {
                board[r][cc] = board[r][cc-1];
            }
        }
    }
}

void check_light_green_board() {
    int n = 0;
    for (int r=4; r<=5; r++) {
        for (int c=0; c<=3; c++) {
            if (board[r][c]) {
                n ++;
                break;
            }
        }
    }
    
    if (n == 0) return;
    for (int c=0; c<=3; c++) {
        for (int r=9; r>=4; r--) {
            board[r][c] = board[r-n][c];
        }
    }
}

void check_light_blue_board() {
    int n = 0;
    for (int c=4; c<=5; c++) {
        for (int r=0; r<=3; r++) {
            if (board[r][c]) {
                n ++;
                break;
            }
        }
    }
    
    if (n == 0) return;
    for (int r=0; r<=3; r++) {
        for (int c=9; c>=4; c--) {
            board[r][c] = board[r][c-n];
        }
    }
}

void monominodomino() {
    for (int i=0; i<N; i++) {
        int t = blocks[i].first;
        int r = blocks[i].second.first;
        int c = blocks[i].second.second;
        
        put_block(t, r, c);
        
        check_green_board();
        
        check_blue_board();
        
        check_light_green_board();
        
        check_light_blue_board();
    }
}

int get_blocks() {
    int cnt = 0;
    for (int r=0; r<=9; r++) {
        for (int c=0; c<=9; c++) {
            cnt += board[r][c];
        }
    }
    
    return cnt;
}

int main(int argc, const char * argv[]) {
    cin >> N;
    for (int i=0; i<N; i++) {
        int t, x, y;
        cin >> t >> x >> y;
        blocks.push_back({t, {x, y}});
    }
    
    monominodomino();
    cout << score << endl;
    cout << get_blocks() << endl;
    
    return 0;
}
