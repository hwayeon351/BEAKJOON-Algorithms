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

void print_tp(){
    for(int i=0; i<N; i++) cout << T[i] << " " << P[i] << endl;
}

void consult(int i, int pay, int day){
    cout << "now idx = " << i << ", pay = " << pay << ", day = " << day << endl;
    if(i >= N){
        if(pay > money) money = pay;
        cout << "finish money = " << money << endl;
        return;
    }
    if((day+T[i]<=N || day == 0) && (i+1+T[i]<=N+1)) consult(T[i]+i, pay+P[i], day+T[i]);
    consult(i+1, pay, day);
    return;
}

int main(int argc, const char * argv[]) {
    cin >> N;
    for(int i=0; i<N; i++) cin >> T[i] >> P[i];
    consult(0, 0, 0);
    cout << money << endl;
    return 0;
}
