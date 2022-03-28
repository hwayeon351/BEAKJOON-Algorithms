//
//  main.cpp
//  BJ16234
//
//  Created by 최화연 on 2022/03/28.
//

#include <iostream>
#include <queue>
using namespace std;

int N, L, R;
int A[100][100] = {0, };
int unity[100][100] = {0, };
int day = 0;

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, -1, 0, 1};

int open_border() {
    int cnt = 0;
    for(int r=0; r<2*N; r++) {
        for(int c=0; c<2*N; c++) {
            unity[r][c] = 0;
        }
    }
    for(int r=0; r<N; r++) {
        for(int c=0; c<N; c++) {
            unity[r*2][c*2] = 1;
            for(int d=0; d<4; d++) {
                int nr = 2*r+2*dy[d];
                int nc = 2*c+2*dx[d];
                if(nr < 0 || nr >= 2*N || nc < 0 || nc >= 2*N) continue;
                int differ = abs(A[r*2][c*2]-A[nr][nc]);
                if(L <= differ && differ <= R) {
                    unity[r*2+dy[d]][c*2+dx[d]] = 1;
                    cnt ++;
                }
            }
        }
    }
    return cnt;
}

void make_unity(int sr, int sc) {
    int p_num = A[sr][sc];
    int countries = 1;
    unity[sr][sc] = 2;
    queue<pair<int, int>> q;
    q.push({sr, sc});
    vector<pair<int, int>> loc;
    loc.push_back({sr, sc});
    while(!q.empty()) {
        int r = q.front().first;
        int c = q.front().second;
        q.pop();
        for(int i=0; i<4; i++) {
            int nr = r + dy[i];
            int nc = c + dx[i];
            if(nr < 0 || nr >= 2*N || nc < 0 || nc >= 2*N) continue;
            if(unity[nr][nc] == 1) {
                unity[nr][nc] = 2;
                if ((nr%2 + nc%2) == 0) {
                    p_num += A[nr][nc];
                    countries += 1;
                    loc.push_back({nr, nc});
                }
                q.push({nr, nc});
            }
        }
    }
    int new_num = p_num/countries;
    for(int i=0; i<loc.size(); i++) {
        A[loc[i].first][loc[i].second] = new_num;
    }
}

void get_unities() {
    for(int r=0; r<N; r++) {
        for(int c=0; c<N; c++) {
            if(unity[2*r][2*c] == 1) {
                make_unity(2*r, 2*c);
            }
        }
    }
}

void move_people() {
    while(true) {
        int border = open_border();
        if (border == 0) break;
        get_unities();
        day ++;
    }
}

int main(int argc, const char * argv[]) {
    cin >> N >> L >> R;
    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            cin >> A[i*2][j*2];
        }
    }
    
    move_people();
    cout << day << endl;
    
    return 0;
}
