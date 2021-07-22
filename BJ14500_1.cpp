//
//  main.cpp
//  BJ14500
//
//  Created by Hwayeon on 2020/12/04.
//
#include <iostream>
using namespace std;

int board[500][500];
int N,M;
int answer = 0;
int polio[19][4][2] = {
    //ㅡ 2
    {{0,0},{0,1},{0,2},{0,3}},
    {{0,0},{1,0},{2,0},{3,0}},
    //ㅁ 1
    {{0,0},{0,1},{1,0},{1,1}},
    //ㄴ 8
    {{0,0},{1,0},{2,0},{2,1}},
    {{0,0},{1,0},{0,1},{0,2}},
    {{0,0},{0,1},{1,1},{2,1}},
    {{0,2},{1,0},{1,1},{1,2}},
    {{0,1},{1,1},{2,1},{2,0}},
    {{0,0},{1,0},{1,1},{1,2}},
    {{0,0},{0,1},{1,0},{2,0}},
    {{0,0},{0,1},{0,2},{1,2}},
    //ㄹ 4
    {{0,0},{1,0},{1,1},{2,1}},
    {{1,0},{1,1},{0,1},{0,2}},
    {{1,0},{2,0},{1,1},{0,1}},
    {{0,0},{0,1},{1,1},{1,2}},
    //ㅗ 4
    {{0,1},{1,0},{1,1},{1,2}},
    {{0,0},{1,0},{2,0},{1,1}},
    {{0,0},{0,1},{0,2},{1,1}},
    {{1,0},{0,1},{1,1},{2,1}}
};

void print_board(){
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            cout << board[i][j];
        }
        cout << endl;
    }
}

void search_max(){
    for(int p=0; p<19; p++){
        for(int y=0; y<N; y++){
            for(int x=0; x<M; x++){
                int sum = 0;
                for(int cnt=0; cnt<4; cnt++){
                    int now_x = x+polio[p][cnt][1];
                    int now_y = y+polio[p][cnt][0];
                    if(now_x<M && now_x>=0 && now_y<N && now_y>=0){
                        sum += board[now_y][now_x];
                    }
                    else break;
                }
                if(sum > answer) answer = sum;
            }
        }
    }
}

int main(int argc, const char * argv[]) {
    cin >> N >> M;
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            cin >> board[i][j];
        }
    }
    print_board();
    search_max();
    cout << answer;
    return 0;
}
