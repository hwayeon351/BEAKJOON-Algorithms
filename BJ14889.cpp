//
//  main.cpp
//  BJ14889
//
//  Created by Hwayeon on 2021/07/07.
//

#include <iostream>
#include <cmath>
using namespace std;

int N;
int S[20][20] = {0, };
int visit[20] = {0,};
int answer = 987654321;

void dfs(int idx, int start_n){
    if(idx >= N) return;
    //팀 배정 완료
    if(start_n == N/2){
        //능력치 구하기
        int start_sum = 0;
        int link_sum = 0;
        for(int i=0; i<N; i++){
            for(int j=0; j<N; j++){
                if(visit[i]+visit[j]==2) start_sum += S[i][j];
                else if(visit[i]+visit[j]==0) link_sum += S[i][j];
            }
        }
        int differ = abs(start_sum-link_sum);
        if(differ < answer) answer = differ;
        return;
    }
    
    //팀원 뽑기
    for(int i=idx; i<N; i++){
        if(start_n+1<=N/2){
            visit[i] = 1;
            dfs(i+1, start_n+1);
            visit[i] = 0;
        }
    }
}
    
int main(int argc, const char * argv[]) {
    cin >> N;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cin >> S[i][j];
        }
    }
    dfs(0, 0);
    cout << answer << endl;
    return 0;
}
