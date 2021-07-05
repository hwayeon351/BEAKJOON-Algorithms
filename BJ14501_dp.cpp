//
//  main.cpp
//  BJ14501_dp
//
//  Created by Hwayeon on 2021/07/05.
//

#include <iostream>
using namespace std;
int N;
int T[15], P[15], dp[15];
int money = 0;

int main(int argc, const char * argv[]) {
    cin >> N;
    for(int i=N-1; i>=0; i--){
        cin >> T[i] >> P[i];
        if(T[i]+(N-i-1) > N){
            T[i] = 0;
            P[i] = 0;
        }
    }
    dp[0]  = P[0];
    money = dp[0];
    for(int i=1; i<N; i++){
        int after_consult = dp[i-T[i]] + P[i];
        if(after_consult > dp[i-1]) dp[i] = after_consult;
        else dp[i] = dp[i-1];
        if(dp[i] > money) money = dp[i];
    }
    cout << money << endl;
    
    return 0;
}
