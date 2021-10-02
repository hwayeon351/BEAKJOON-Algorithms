//
//  main.cpp
//  BJ17822
//
//  Created by Hwayeon on 2021/09/21.
//

#include <iostream>
#include <deque>
using namespace std;

int N, M, T;
int board[50][50] = {0, };

struct Command{
    int x;
    int d;
    int k;
};
deque<Command> cmds;
Command cmd;
int answer = 0;

void rotate(){
    deque<int> x_board;
    deque<pair<int, int>> erase;
    
    while(!cmds.empty()){
        cmd = cmds.front();
        cmds.pop_front();
        for(int x=cmd.x-1; x<N; x+=cmd.x){
            x_board.clear();
            for(int j=0; j<M; j++){
                x_board.push_back(board[x][j]);
            }
            if(cmd.d == 0){
                for(int k=0; k<cmd.k; k++){
                    int temp = x_board.back();
                    x_board.pop_back();
                    x_board.push_front(temp);
                }
            }
            else{
                for(int k=0; k<cmd.k; k++){
                    int temp = x_board.front();
                    x_board.pop_front();
                    x_board.push_back(temp);
                }
            }
            for(int j=0; j<M; j++){
                board[x][j] = x_board[j];
            }
        }
        
        erase.clear();
        for(int i=0; i<N; i++){
            for(int j=0; j<M; j++){
                if(board[i][j] == 0) continue;
                if(j < M-1){
                    if(board[i][j] == board[i][j+1]){
                        erase.push_back({j, i});
                        erase.push_back({j+1, i});
                        if(i < N-1){
                            if(board[i][j] == board[i+1][j]){
                                erase.push_back({j, i+1});
                            }
                        }
                    }
                    else if(i < N-1){
                        if(board[i][j] == board[i+1][j]){
                            erase.push_back({j, i});
                            erase.push_back({j, i+1});
                        }
                    }
                }
                else {
                    if(i < N-1){
                        if(board[i][j] == board[i+1][j]){
                            erase.push_back({j, i});
                            erase.push_back({j, i+1});
                        }
                    }
                    if(board[i][j] == board[i][0]){
                        erase.push_back({j, i});
                        erase.push_back({0, i});
                    }
                }
            }
        }
        if(erase.size() > 0){
            for(int i=0; i<erase.size(); i++){
                board[erase[i].second][erase[i].first] = 0;
            }
        }
        else{
            int cnt = 0;
            int sum = 0;
            for(int i=0; i<N; i++){
                for(int j=0; j<M; j++){
                    if(board[i][j] == 0) continue;
                    sum += board[i][j];
                    cnt++;
                }
            }
            if(sum == 0){
                answer = 0;
                break;
            }
            double avg = (double)sum/cnt;
            for(int i=0; i<N; i++){
                for(int j=0; j<M; j++){
                    if(board[i][j] == 0) continue;
                    if(board[i][j] < avg) board[i][j]++;
                    else if(board[i][j] > avg) board[i][j] --;
                }
            }
        }
        answer = 0;
        for(int i=0; i<N; i++){
            for(int j=0; j<M; j++){
                if(board[i][j] == 0) continue;
                answer += board[i][j];
            }
        }
        if(answer == 0) break;
    }
}

int main(int argc, const char * argv[]) {
    cin >> N >> M >> T;
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            cin >> board[i][j];
        }
    }
    for(int t=0; t<T; t++){
        cin >> cmd.x >> cmd.d >> cmd.k;
        cmds.push_back(cmd);
    }
    rotate();
    cout << answer << endl;
    
    return 0;
}
