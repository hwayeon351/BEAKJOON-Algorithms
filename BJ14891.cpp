//
//  main.cpp
//  BJ14891
//
//  Created by 최화연 on 2022/03/30.
//

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int wheel[5][8] = {0, };
int K;
vector<pair<int, int>> cmds;
queue<pair<int, int>> rotates;

void rotate() {
    while (!rotates.empty()) {
        int n = rotates.front().first;
        int d = rotates.front().second;
        rotates.pop();
        if (d == 1) {
            int temp = wheel[n][7];
            for(int i=6; i>=0; i--) {
                wheel[n][i+1] = wheel[n][i];
            }
            wheel[n][0] = temp;
        }
        else {
            int temp = wheel[n][0];
            for(int i=1; i<=7; i++) {
                wheel[n][i-1] = wheel[n][i];
            }
            wheel[n][7] = temp;
        }
    }
}

void rotate_wheels(int n, int d) {
    rotates.push({n, d});
    switch (n) {
        case 1:
            if (wheel[1][2] != wheel[2][6]) {
                rotates.push({2, d*(-1)});
                if (wheel[2][2] != wheel[3][6]) {
                    rotates.push({3, d});
                    if(wheel[3][2] != wheel[4][6]) {
                        rotates.push({4, d*(-1)});
                    }
                }
            }
            break;
        
        case 2:
            if (wheel[2][6] != wheel[1][2]) {
                rotates.push({1, d*(-1)});
            }
            if (wheel[2][2] != wheel[3][6]) {
                rotates.push({3, d*(-1)});
                if(wheel[3][2] != wheel[4][6]) {
                    rotates.push({4, d});
                }
            }
            break;
            
        case 3:
            if (wheel[3][6] != wheel[2][2]) {
                rotates.push({2, d*(-1)});
                if(wheel[2][6] != wheel[1][2]) {
                    rotates.push({1, d});
                }
            }
            if (wheel[3][2] != wheel[4][6]) {
                rotates.push({4, d*(-1)});
            }
            break;
            
        case 4:
            if (wheel[4][6] != wheel[3][2]) {
                rotates.push({3, d*(-1)});
                if(wheel[3][6] != wheel[2][2]) {
                    rotates.push({2, d});
                    if(wheel[2][6] != wheel[1][2]) {
                        rotates.push({1, d*(-1)});
                    }
                }
            }
            break;
    }
    rotate();
}

int calculate_score() {
    int score = 0;
    if (wheel[1][0]) score ++;
    if (wheel[2][0]) score += 2;
    if (wheel[3][0]) score += 4;
    if (wheel[4][0]) score += 8;
    return score;
}

int main(int argc, const char * argv[]) {
    for(int i=1; i<=4; i++) {
        int n;
        cin >> n;
        for(int j=7; j>=0; j--) {
            wheel[i][j] = n % 10;
            n /= 10;
        }
    }
    cin >> K;
    for(int i=0; i<K; i++) {
        int n, d;
        cin >> n >> d;
        cmds.push_back({n, d});
    }
    
    for(int i=0; i<K; i++) {
        rotate_wheels(cmds[i].first, cmds[i].second);
    }
    
    cout << calculate_score() << endl;
    
    return 0;
}
