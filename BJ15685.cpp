//
//  main.cpp
//  BJ15685
//
//  Created by 최화연 on 2022/04/21.
//

#include <iostream>
#include <deque>
using namespace std;

int N;
int board[102][102] = {0, };
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, -1, 0, 1};

deque<int> curve;
int answer = 0;


int main(int argc, const char * argv[]) {
    cin >> N;
    for (int i=0; i<N; i++) {
        int x, y, d, g;
        cin >> x >> y >> d >> g;
        
        curve.push_back(d);
        for (int j=0; j<g; j++) {
            int idx = curve.size()-1;
            for (int k=idx; k>=0; k--) {
                curve.push_back((curve[k]+1)%4);
            }
        }
        
        board[y][x] ++;
        for (int j=0; j<curve.size(); j++) {
            x += dx[curve[j]];
            y += dy[curve[j]];
            board[y][x] ++;
        }
        curve.clear();
    }
    
    for (int y=0; y<=100; y++) {
        for (int x=0; x<=100; x++) {
            if (board[y][x] > 0 && board[y][x+1] > 0 && board[y+1][x] > 0 && board[y+1][x+1] > 0) {
                answer ++;
            }
        }
    }
    
    cout << answer << endl;
    
    return 0;
}
