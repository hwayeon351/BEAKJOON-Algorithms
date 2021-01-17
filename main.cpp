//
//  main.cpp
//  BJ14888
//
//  Created by Hwayeon on 2021/01/17.
//

#include <iostream>
using namespace std;

int N;
int num[11] = {0, };
int op[4] = {0, };
long max_anwer = -9999999999;
long min_answer = 9999999999;

void calculate(int idx, long answer){
    if(idx == N-1){
        if(answer < min_answer) min_answer = answer;
        if(answer > max_anwer) max_anwer = answer;
        return;
    }
    int n1 = num[idx];
    int n = num[idx+1];
    long ans = 0;
    for(int i=0; i<4; i++){
        if(op[i] > 0){
            switch (i) {
                case 0:
                    if(idx == 0) ans = n1 + n;
                    else ans = n + answer;
                    break;
                case 1:
                    if(idx == 0) ans = n1 - n;
                    else ans = answer - n;
                    break;
                case 2:
                    if(idx == 0) ans = n1 * n;
                    else ans = answer * n;
                    break;
                case 3:
                    if(idx == 0) ans = n1 / n;
                    else ans = answer / n;
                    break;

            }
            op[i]--;
            calculate(idx+1, ans);
            op[i]++;
        }
    }
}

int main(int argc, const char * argv[]) {
    cin >> N;
    for(int i=0; i<N; i++){
        cin >> num[i];
    }
    for(int i=0; i<4; i++){
        cin >> op[i];
    }
    calculate(0, 0);
    cout << max_anwer << endl << min_answer << endl;
    
    return 0;
}
