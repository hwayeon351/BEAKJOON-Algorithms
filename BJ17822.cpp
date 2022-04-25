//
//  main.cpp
//  BJ17822
//
//  Created by 최화연 on 2022/04/25.
//

#include <iostream>
#include <deque>
#include <cstring>
#include <queue>
using namespace std;

int N, M, T;

//circle[i][j] = i번째 원판에 적힌 j번째 수
deque<deque<int>> circles = {{}, };
int visits[51][51] = {0, };

void rotate_circle(int x, int d, int k) {
    for (int i=x; i<=N; i+=x) {
        //시계
        if (d == 0) {
            for (int j=0; j<k; j++) {
                int num = circles[i].back();
                circles[i].pop_back();
                circles[i].push_front(num);
            }
        }
        //반시계
        else {
            for (int j=0; j<k; j++) {
                int num = circles[i].front();
                circles[i].pop_front();
                circles[i].push_back(num);
            }
        }
    }
}

int erase_num(int si, int sj, int num) {
    int cnt = 1;
    visits[si][sj] = 1;
    queue<pair<int, int>> q;
    q.push({si, sj});
    
    while (!q.empty()) {
        int i = q.front().first;
        int j = q.front().second;
        q.pop();
        if (j == M-1) {
            if (circles[i][0] == num && visits[i][0] == 0) {
                visits[i][0] = 1;
                circles[i][0] = 0;
                cnt ++;
                q.push({i, 0});
            }
            if (circles[i][M-2] == num && visits[i][M-2] == 0) {
                visits[i][M-2] = 1;
                circles[i][M-2] = 0;
                cnt ++;
                q.push({i, M-2});
            }
        }
        else if (j == 0) {
            if (circles[i][1] == num && visits[i][1] == 0) {
                visits[i][1] = 1;
                circles[i][1] = 0;
                cnt ++;
                q.push({i, 1});
            }
            if (circles[i][M-1] == num && visits[i][M-1] == 0) {
                visits[i][M-1] = 1;
                circles[i][M-1] = 0;
                cnt ++;
                q.push({i, M-1});
            }
        }
        else {
            if (circles[i][j-1] == num && visits[i][j-1] == 0) {
                visits[i][j-1] = 1;
                circles[i][j-1] = 0;
                cnt ++;
                q.push({i, j-1});
            }
            if (circles[i][j+1] == num && visits[i][j+1] == 0) {
                visits[i][j+1] = 1;
                circles[i][j+1] = 0;
                cnt ++;
                q.push({i, j+1});
            }
        }
        
        if (i < N) {
            if (circles[i+1][j] == num && visits[i+1][j] == 0) {
                visits[i+1][j] = 1;
                circles[i+1][j] = 0;
                cnt ++;
                q.push({i+1, j});
            }
        }
        
        if (i > 1) {
            if (circles[i-1][j] == num && visits[i-1][j] == 0) {
                visits[i-1][j] = 1;
                circles[i-1][j] = 0;
                cnt ++;
                q.push({i-1, j});
            }
        }
    }
    
    if (cnt > 1) circles[si][sj] = 0;
    return cnt;
}

int main(int argc, const char * argv[]) {
    cin >> N >> M >> T;
    for (int i=1; i<=N; i++) {
        deque<int> circle;
        for (int j=1; j<=M; j++) {
            int n;
            cin >> n;
            circle.push_back(n);
        }
        circles.push_back(circle);
    }
    
    int x, d, k;
    for (int t=0; t<T; t++) {
        cin >> x >> d >> k;
        rotate_circle(x, d, k);
        
        memset(visits, 0, sizeof(visits));
        int erase_cnt = 0;
        int non_cnt = 0;
        int sum = 0;
        for (int i=1; i<=N; i++) {
            for (int j=0; j<M; j++) {
                if (visits[i][j] || circles[i][j] == 0) continue;
                int num = circles[i][j];
                int same = erase_num(i, j, num);
                if (same == 1) {
                    sum += num;
                    non_cnt ++;
                }
                else {
                    sum += same*num;
                    erase_cnt += same;
                }
            }
        }
        
        if(sum == 0) {
            cout << 0 << endl;
            return 0;
        }
        
        if(erase_cnt == 0) {
            double average = (double)sum/double(non_cnt);
            for (int i=1; i<=N; i++) {
                for (int j=0; j<M; j++) {
                    if (circles[i][j] == 0) continue;
                    if (circles[i][j] > average) circles[i][j] --;
                    else if (circles[i][j] < average) circles[i][j] ++;
                }
            }
        }
    }
    
    int answer = 0;
    for (int i=1; i<=N; i++) {
        for (int j=0; j<M; j++) {
            answer += circles[i][j];
        }
    }
    cout << answer << endl;
    
    return 0;
}
