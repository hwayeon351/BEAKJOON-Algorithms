//
//  main.cpp
//  BJ15684
//
//  Created by Hwayeon on 2021/08/11.
//

#include <iostream>
using namespace std;

int N, M, H;
int ladder[32][12] = {0, };
int min_line = -1;

bool check_ladder(){
    for(int c=1; c<=N; c++){
        int now_c = c;
        for(int r=1; r<=H; r++){
            //왼쪽으로 가야하는 경우
            if(ladder[r][now_c] == 0 && ladder[r][now_c-1] == 1){
                now_c--;
            }
            //오른쪽으로 가야하는 경우
            else if(ladder[r][now_c] == 1){
                now_c++;
            }
        }
        //i번 세로선의 i번 결과가 아닌 경우 실패
        if(c != now_c) return false;
    }
    return true;
}

void install_line(int cnt, int n, int row, int col){
    if(cnt == n){
        //사다리게임
        if(check_ladder()){
            min_line = n;
        }
        return;
    }
    for(int r=row; r<=H; r++){
        if(r > row) col = 1;
        for(int c=col; c<=N; c++){
            if(ladder[r][c]==0 && ladder[r][c-1] == 0 && ladder[r][c+1] == 0){
                ladder[r][c] = 1;
                install_line(cnt+1, n, r, c+2);
                ladder[r][c] = 0;
            }
        }
    }
}

int main(int argc, const char * argv[]) {
    cin >> N >> M >> H;
    for(int i=0; i<M; i++){
        int col, row;
        cin >> row >> col;
        ladder[row][col] = 1;
    }
    for(int i=0; i<=3; i++){
        if(min_line != -1) break;
        install_line(0, i, 1, 1);
    }
    cout << min_line << endl;
    
    return 0;
}
