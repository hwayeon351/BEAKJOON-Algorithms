//
//  main.cpp
//  BJ14888
//
//  Created by Hwayeon on 2021/07/09.
//

#include <iostream>
using namespace std;

int N;
int num[100] = {0,};
//1 +, 2 -, 3 *, 4 //
int op_cnt[5] = {0,};
int op[100] = {0,};

long long max_result = -1000000000;
long long min_result = 1000000000;

void dfs(int cnt){
    if(cnt == N-1){
        //결과 값 구하기
        int result = num[0];
        for(int i=1; i<N; i++){
            switch(op[i]){
                case 1:
                    result += num[i];
                    break;
                case 2:
                    result -= num[i];
                    break;
                case 3:
                    result *= num[i];
                    break;
                case 4:
                    result /= num[i];
                    break;
            }
        }
        //cout << result << endl;
        if(result > max_result) max_result = result;
        if(result < min_result) min_result = result;
        return;
    }
    for(int i=1; i<=4; i++){
        if(op_cnt[i] > 0){
            op_cnt[i]--;
            op[cnt+1] = i;
            dfs(cnt+1);
            op_cnt[i]++;
            op[cnt+1] = 0;
        }
    }
}

int main(int argc, const char * argv[]) {
    cin >> N;
    for(int i=0; i<N; i++){
        cin >> num[i];
    }
    for(int i=1; i<=4; i++){
        cin >> op_cnt[i];
    }
    dfs(0);
    cout << max_result << endl;
    cout << min_result << endl;
    return 0;
}
