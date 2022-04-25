//
//  main.cpp
//  BJ20057
//
//  Created by 최화연 on 2022/04/24.
//

#include <iostream>
using namespace std;

int N;
int A[499][499] = {0, };

//moves[d][9] -> 알파
int moves[4][10][3] = {
    //0 좌
    {
        {-1, 0, 1}, {1, 0, 1}, {-2, -1, 2}, {-1, -1, 7}, {1, -1, 7}, {2, -1, 2}, {-1, -2, 10}, {1, -2, 10}, {0, -3, 5}, {0, -2, 0}
    },
    //1 하
    {
        {0, -1, 1}, {0, 1, 1}, {1, -2, 2}, {1, -1, 7}, {1, 1, 7}, {1, 2, 2}, {2, -1, 10}, {2, 1, 10}, {3, 0, 5}, {2, 0, 0}
    },
    //2 우
    {
        {-1, 0, 1}, {1, 0, 1}, {-2, 1, 2}, {-1, 1, 7}, {1, 1, 7}, {2, 1, 2}, {-1, 2, 10}, {1, 2, 10}, {0, 3, 5}, {0, 2, 0}
    },
    //3 상
    {
        {0, -1, 1}, {0, 1, 1}, {-1, -2, 2}, {-1, -1, 7}, {-1, 1, 7}, {-1, 2, 2}, {-2, -1, 10}, {-2, 1, 10}, {-3, 0, 5}, {-2, 0, 0}
    }
};

int dr[4] = {0, 1, 0, -1};
int dc[4] = {-1, 0, 1, 0};

int answer = 0;

void tornado() {
    int tr = N/2;
    int tc = N/2;
    int td = 0;
    for (int i=1; i<=N; i++) {
        for (int j=0; j<2; j++) {
            int n = i;
            if (i == N) n = N-1;
            for (int k=0; k<n; k++) {
                int ntr = tr+dr[td];
                int ntc = tc+dc[td];
                int y = A[ntr][ntc];
                A[ntr][ntc] = 0;
                int sand = 0;
                for (int l=0; l<9; l++) {
                    int r = tr + moves[td][l][0];
                    int c = tc + moves[td][l][1];
                    int spread = (moves[td][l][2] * 0.01) * y;
                    if (r < 0 || r >= N || c < 0 || c >= N) answer += spread;
                    else A[r][c] += spread;
                    sand += spread;
                }
                int r = tr + moves[td][9][0];
                int c = tc + moves[td][9][1];
                int spread = y - sand;
                if (r < 0 || r >= N || c < 0 || c >= N) answer += spread;
                else A[r][c] += spread;
                tr = ntr;
                tc = ntc;
            }
            if (i == N) return;
            //방향 바꾸기
            td = (td + 1) % 4;
        }
    }
}

int main(int argc, const char * argv[]) {
    cin >> N;
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            cin >> A[i][j];
        }
    }
    
    tornado();
    cout << answer << endl;
    
    return 0;
}
