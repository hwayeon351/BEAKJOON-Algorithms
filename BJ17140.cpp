//
//  main.cpp
//  BJ17140
//
//  Created by Hwayeon on 2021/08/17.
//

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int A[100][100] = {0,};
int new_A[100][100] = {0,};
int R, C, K;
int sec = 0;
struct items{
    int num;
    int cnt;
};
struct cmp{
    bool operator()(items x, items y){
        //등장 횟수가 같은 경우
        if(x.cnt == y.cnt){
            //수가 커지는 순으로
            return x.num > y.num;
        }
        //등장 횟수가 커지는 순으로
        return x.cnt > y.cnt;
    }
};

int main(int argc, const char * argv[]) {
    cin >> R >> C >> K;
    R--;
    C--;
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            cin >> A[i][j];
        }
    }
    
    int r_cnt = 3;
    int c_cnt = 3;
    
    while(sec <= 100){
        //행 개수 구하기
        r_cnt = 0;
        for(int c=0; c<100; c++){
            int cnt = 0;
            for(int r=0; r<100; r++){
                if(A[r][c] == 0) break;
                cnt++;
            }
            if(cnt > r_cnt) r_cnt = cnt;
        }
        
        //열 개수 구하기
        c_cnt = 0;
        for(int r=0; r<100; r++){
            int cnt = 0;
            for(int c=0; c<100; c++){
                if(A[r][c] == 0) break;
                cnt++;
            }
            if(cnt>c_cnt) c_cnt = cnt;
        }
        
        if(r_cnt >= R && c_cnt >= C){
            if(A[R][C] == K){
                cout << sec << endl;
                return 0;
            }
        }
        
        //R연산
        if(r_cnt >= c_cnt){
            for(int r=0; r<r_cnt; r++){
                //1. 등장 횟수 세기
                int visit[101] ={0,};
                for(int c=0; c<c_cnt; c++){
                    visit[A[r][c]]++;
                }
                //2. 정렬
                priority_queue<items, vector<items>, cmp> pq;
                for(int n=1; n<=100; n++){
                    if(visit[n] > 0){
                        pq.push({n, visit[n]});
                    }
                }
                //3. new_A에 추가
                int item_cnt = pq.size();
                for(int c=0; c<item_cnt*2; c+=2){
                    if(c==100) break;
                    new_A[r][c] = pq.top().num;
                    new_A[r][c+1] = pq.top().cnt;
                    pq.pop();
                }
            }
        }
        //C연산
        else{
            for(int c=0; c<c_cnt; c++){
                //1. 등장 횟수 세기
                int visit[101] ={0,};
                for(int r=0; r<r_cnt; r++){
                    visit[A[r][c]]++;
                }
                //2. 정렬
                priority_queue<items, vector<items>, cmp> pq;
                for(int i=1; i<=100; i++){
                    if(visit[i] > 0){
                        pq.push({i, visit[i]});
                    }
                }
                //3. new_A에 추가
                int item_cnt = pq.size();
                for(int r=0; r<item_cnt*2; r+=2){
                    if(r==100) break;
                    new_A[r][c] = pq.top().num;
                    new_A[r+1][c] = pq.top().cnt;
                    pq.pop();
                }

            }
        }
        //A = new_A, new_A 초기화
        for(int i=0; i<100; i++){
            for(int j=0; j<100; j++){
                A[i][j] = new_A[i][j];
                new_A[i][j] = 0;
            }
        }
        sec++;
    }
    cout << -1 << endl;
    return 0;
}
