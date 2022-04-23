//
//  main.cpp
//  BJ15684
//
//  Created by 최화연 on 2022/04/23.
//

#include <iostream>
using namespace std;

int N, M, H;
int ladder[31][20] = {0, };

int answer = -1;

bool check_ladder() {
    bool check = true;
    for (int c=1; c<=N; c++) {
        int col = 2*(c-1)+1;
        int row = 1;
        while (row <= H) {
            //오른쪽 체크
            if (col < 2*(N-1)+1 && ladder[row][col+1]) {
                col += 2;
            }
            //왼쪽 체크
            else if (col > 1 && ladder[row][col-1]) {
                col -= 2;
            }
            row ++;
        }
        if (col == 2*(c-1)+1) continue;
        check = false;
        break;
    }
    return check;
}

void add_lines(int cnt, int col, int row, int num) {
    if (answer == num) return;
    if (cnt == num) {
        if (check_ladder()) {
            answer = num;
        }
        return;
    }
    
    for (int c=1; c<N; c++) {
        int nc = 2*(c-1)+1;
        int rr = row;
        if (c < col) rr = row+1;
        for (int r=rr; r<=H; r++) {
            if (ladder[r][nc+1]) continue;
            ladder[r][nc+1] = 1;
            if (c == N-1) add_lines(cnt+1, 1, r+1, num);
            else add_lines(cnt+1, c+1, r, num);
            ladder[r][nc+1] = 0;
        }
    }
}

int main(int argc, const char * argv[]) {
    cin >> N >> M >> H;
    for (int i=0; i<M; i++) {
        int a, b;
        cin >> a >> b;
        ladder[a][2*(b-1)+2] = 1;
    }
    
    for (int c=1; c<=N; c++) {
        int col = 2*(c-1)+1;
        for (int r=1; r<=H; r++) {
            ladder[r][col] = 1;
        }
    }
    
    if (M == 0 || check_ladder()) cout << 0 << endl;
    else {
        for (int i=1; i<=3; i++) {
            if (answer != -1) break;
            add_lines(0, 1, 1, i);
        }
        
        cout << answer << endl;
    }
    
    return 0;
}
