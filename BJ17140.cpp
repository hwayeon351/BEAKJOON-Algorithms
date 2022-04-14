//
//  main.cpp
//  BJ17140
//
//  Created by 최화연 on 2022/04/14.
//

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int row, col, k;
int A[101][101] = {0, };
int R = 3;
int C = 3;

struct Item {
    int num;
    int cnt;
};
struct cmp {
    bool operator() (Item a, Item b) {
        if (a.cnt == b.cnt) {
            return a.num > b.num;
        }
        return a.cnt > b.cnt;
    }
};

int sort_A() {
    int sec = 0;
    while (sec < 100) {
        if (A[row][col] == k) return sec;
        sec ++;
        
        //C 연산
        if (R < C) {
            int new_R = 0;
            for (int c=1; c<=C; c++) {
                int visit[101] = {0, };
                for (int r=1; r<=R; r++) {
                    visit[A[r][c]]++;
                }
                priority_queue<Item, vector<Item>, cmp> pq;
                for (int i=1; i<101; i++) {
                    if (visit[i] > 0) {
                        pq.push({i, visit[i]});
                    }
                }
                int r = 1;
                while (!pq.empty()) {
                    Item item = pq.top();
                    pq.pop();
                    if (r > 100) break;
                    A[r][c] = item.num;
                    if (r > new_R) new_R = r;
                    r++;
                    if (r > 100) break;
                    A[r][c] = item.cnt;
                    if (r > new_R) new_R = r;
                    r++;
                }
                //나머지 0으로 채우기
                for (int rr=r; rr<=100; rr++) {
                    A[rr][c] = 0;
                }
            }
            R = new_R;
        }
        
        //R 연산
        else {
            int new_C = 0;
            for (int r=1; r<=R; r++) {
                int visit[101] = {0, };
                for (int c=1; c<=C; c++) {
                    visit[A[r][c]]++;
                }
                priority_queue<Item, vector<Item>, cmp> pq;
                for (int i=1; i<101; i++) {
                    if (visit[i] > 0) {
                        pq.push({i, visit[i]});
                    }
                }
                int c = 1;
                while (!pq.empty()) {
                    Item item = pq.top();
                    pq.pop();
                    if (c > 100) break;
                    A[r][c] = item.num;
                    if (c > new_C) new_C = c;
                    c++;
                    if (c > 100) break;
                    A[r][c] = item.cnt;
                    if (c > new_C) new_C = c;
                    c++;
                }
                //나머지 0으로 채우기
                for (int cc=c; cc<=100; cc++) {
                    A[r][cc] = 0;
                }
            }
            C = new_C;
        }
    }
    if (A[row][col] == k) return sec;
    return -1;
}

int main(int argc, const char * argv[]) {
    cin >> row >> col >> k;

    for(int i=1; i<=3; i++) {
        for(int j=1; j<=3; j++) {
            cin >> A[i][j];
        }
    }
        
    cout << sort_A() << endl;
    
    return 0;
}
