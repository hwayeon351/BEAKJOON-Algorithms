//
//  main.cpp
//  BJ17837
//
//  Created by Hwayeon on 2021/10/05.
//

#include <iostream>
#include <vector>
#include <deque>
using namespace std;

int N, K;
int board[13][13] = {0, };
int chess[13][13][3] = {0, };

int dx[5] = {0, 1, -1, 0, 0};
int dy[5] = {0, 0, 0, -1, 1};

struct Piece{
    int r;
    int c;
    int d;
};
Piece piece;
vector<Piece> pieces;

int turn = 0;

int get_opposite_dir(int dir){
    int ndir = -1;
    switch(dir){
        case 1:
            ndir = 2;
            break;
        case 2:
            ndir = 1;
            break;
        case 3:
            ndir = 4;
            break;
        case 4:
            ndir = 3;
            break;
    }
    return ndir;
}

void play_game(){
    deque<int> move_pieces;
    
    while(true){
        turn++;
        if(turn > 1000){
            turn = -1;
            break;
        }
        
        for(int i=0; i<K; i++){
            int nr = pieces[i].r + dy[pieces[i].d];
            int nc = pieces[i].c + dx[pieces[i].d];
            //이동할 위치가 체스판을 벗어나거나, 파란색인 경우
            if((nr<1 || nr>N || nc<1 || nc>N) || board[nr][nc] == 2){
                //이동 방향을 반대로 바꾼다
                pieces[i].d = get_opposite_dir(pieces[i].d);
                
                nr = pieces[i].r + dy[pieces[i].d];
                nc = pieces[i].c + dx[pieces[i].d];
                //이동하려는 칸이 파란색이거나 체스판을 벗어나는 경우, 이동하지 않는다
                if(board[nr][nc] == 2 || (nr<1 || nr>N || nc<1 || nc>N)) continue;
                
                //이동하려는 칸이 파란색이 아닌 경우
                if(board[nr][nc] == 0){
                    //이동하려는 칸의 말 개수 + 이동할 말 개수 구하기
                    int dest_cnt = 0;
                    for(int j=0; j<3; j++){
                        if(chess[nr][nc][j] == 0) break;
                        dest_cnt++;
                    }
                    int group_from = -1;
                    int group_to = -1;
                    for(int j=0; j<3; j++){
                        if(chess[pieces[i].r][pieces[i].c][j] == i+1){
                            group_from = j;
                            move_pieces.push_back(i+1);
                        }
                        else if(chess[pieces[i].r][pieces[i].c][j] != 0 && group_from != -1){
                            group_to = j;
                            move_pieces.push_back(chess[pieces[i].r][pieces[i].c][j]);
                        }
                    }
                    if(group_to == -1) group_to = group_from;
                    //이동 후 말이 4개 이상 쌓이면, 함수를 종료한다
                    if(dest_cnt + move_pieces.size() >= 4){
                        return;
                    }
                    int src_cnt = move_pieces.size();
                    //위에 올려져 있는 말과 함께 한 칸 이동
                    for(int j=dest_cnt; j<dest_cnt+src_cnt; j++){
                        chess[nr][nc][j] = move_pieces.front();
                        move_pieces.pop_front();
                    }
                    for(int j=group_from; j<=group_to; j++){
                        chess[pieces[i].r][pieces[i].c][j] = 0;
                    }
                    for(int j=dest_cnt; j<dest_cnt+src_cnt; j++){
                        pieces[chess[nr][nc][j]-1].r = nr;
                        pieces[chess[nr][nc][j]-1].c = nc;
                    }
                }
                else if(board[nr][nc] == 1){
                    //이동하려는 칸의 말 개수 + 이동할 말 개수 구하기
                    int dest_cnt = 0;
                    for(int j=0; j<3; j++){
                        if(chess[nr][nc][j] == 0) break;
                        dest_cnt++;
                    }
                    int group_from = -1;
                    int group_to = -1;
                    for(int j=0; j<3; j++){
                        if(chess[pieces[i].r][pieces[i].c][j] == i+1){
                            group_from = j;
                            move_pieces.push_back(i+1);
                        }
                        else if(chess[pieces[i].r][pieces[i].c][j] != 0 && group_from != -1){
                            group_to = j;
                            move_pieces.push_back(chess[pieces[i].r][pieces[i].c][j]);
                        }
                    }
                    if(group_to == -1) group_to = group_from;
                    int src_cnt = move_pieces.size();
                    //이동 후 말이 4개 이상 쌓이면, 함수를 종료한다
                    if(dest_cnt + src_cnt >= 4){
                        return;
                    }
                    //위에 올려져 있는 말과 함께 한 칸 이동
                    for(int j=dest_cnt; j<dest_cnt+src_cnt; j++){
                        chess[nr][nc][j] = move_pieces.back();
                        move_pieces.pop_back();
                    }
                    for(int j=group_from; j<=group_to; j++){
                        chess[pieces[i].r][pieces[i].c][j] = 0;
                    }
                    for(int j=dest_cnt; j<dest_cnt+src_cnt; j++){
                        pieces[chess[nr][nc][j]-1].r = nr;
                        pieces[chess[nr][nc][j]-1].c = nc;
                    }
                }
            }
            //이동할 위치가 흰색인 경우
            else if(board[nr][nc] == 0){
                //이동하려는 칸의 말 개수 + 이동할 말 개수 구하기
                int dest_cnt = 0;
                for(int j=0; j<3; j++){
                    if(chess[nr][nc][j] == 0) break;
                    dest_cnt++;
                }
                int group_from = -1;
                int group_to = -1;
                for(int j=0; j<3; j++){
                    if(chess[pieces[i].r][pieces[i].c][j] == i+1){
                        group_from = j;
                        move_pieces.push_back(i+1);
                    }
                    else if(chess[pieces[i].r][pieces[i].c][j] != 0 && group_from != -1){
                        group_to = j;
                        move_pieces.push_back(chess[pieces[i].r][pieces[i].c][j]);
                    }
                }
                if(group_to == -1) group_to = group_from;
                int src_cnt = move_pieces.size();
                //이동 후 말이 4개 이상 쌓이면, 함수를 종료한다
                if(dest_cnt + src_cnt >= 4){
                    return;
                }
                //위에 올려져 있는 말과 함께 한 칸 이동
                for(int j=dest_cnt; j<dest_cnt+src_cnt; j++){
                    chess[nr][nc][j] = move_pieces.front();
                    move_pieces.pop_front();
                }
                for(int j=group_from; j<=group_to; j++){
                    chess[pieces[i].r][pieces[i].c][j] = 0;
                }
                
                for(int j=dest_cnt; j<dest_cnt+src_cnt; j++){
                    pieces[chess[nr][nc][j]-1].r = nr;
                    pieces[chess[nr][nc][j]-1].c = nc;
                }
            }
            //이동할 위치가 빨간색인 경우
            else if(board[nr][nc] == 1){
                //이동하려는 칸의 말 개수 + 이동할 말 개수 구하기
                int dest_cnt = 0;
                for(int j=0; j<3; j++){
                    if(chess[nr][nc][j] == 0) break;
                    dest_cnt++;
                }
                int group_from = -1;
                int group_to = -1;
                for(int j=0; j<3; j++){
                    if(chess[pieces[i].r][pieces[i].c][j] == i+1){
                        group_from = j;
                        move_pieces.push_back(i+1);
                    }
                    else if(chess[pieces[i].r][pieces[i].c][j] != 0 && group_from != -1){
                        group_to = j;
                        move_pieces.push_back(chess[pieces[i].r][pieces[i].c][j]);
                    }
                }
                if(group_to == -1) group_to = group_from;
                int src_cnt = move_pieces.size();
                //이동 후 말이 4개 이상 쌓이면, 함수를 종료한다
                if(dest_cnt + src_cnt >= 4){
                    return;
                }
                //위에 올려져 있는 말과 함께 한 칸 이동
                for(int j=dest_cnt; j<dest_cnt+src_cnt; j++){
                    chess[nr][nc][j] = move_pieces.back();
                    move_pieces.pop_back();
                }
                for(int j=group_from; j<=group_to; j++){
                    chess[pieces[i].r][pieces[i].c][j] = 0;
                }
                for(int j=dest_cnt; j<dest_cnt+src_cnt; j++){
                    pieces[chess[nr][nc][j]-1].r = nr;
                    pieces[chess[nr][nc][j]-1].c = nc;
                }
            }
        }
    }
}

int main(int argc, const char * argv[]) {
    cin >> N >> K;
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            cin >> board[i][j];
        }
    }
    for(int i=1; i<=K; i++){
        cin >> piece.r >> piece.c >> piece.d;
        pieces.push_back(piece);
        chess[piece.r][piece.c][0] = i;
    }
    play_game();
    cout << turn << endl;
    
    return 0;
}
