//
//  main.cpp
//  BJ14501
//
//  Created by Hwayeon on 2020/12/10.
//
#include <iostream>
using namespace std;

int N;
int T[15];
int P[15];
int money = 0;

void consult(int i, int pay, int day){
    if(i >= N){
        if(pay > money){
            money = pay;
        }
        return;
    }
    if(day+T[i]<=N && i+1+T[i]<=N+1) consult(i+T[i], pay+P[i], day+T[i]);
    consult(i+1, pay, day);
}

int main(int argc, const char * argv[]) {
    cin >> N;
    for(int i=0; i<N; i++) {
        cin >> T[i] >> P[i];
    }
    consult(0, 0, 0);
    cout << money << endl;
    return 0;
}
