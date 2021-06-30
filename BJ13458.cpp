//
//  main.cpp
//  BJ13458
//
//  Created by Hwayeon on 2021/06/30.
//

#include <iostream>
using namespace std;

int N, B, C;
int p[1000000] = {0,};
long long ans = 0;

int main(int argc, const char * argv[]) {
    cin >> N;
    for(int i=0; i<N; i++){
        cin >> p[i];
    }
    cin >> B >> C;
    
    for(int i=0; i<N; i++){
        int num_c = p[i]-B;
        if(num_c <= 0) ans ++;
        else if(num_c % C!=0){
            int num_bc = 2+num_c/C;
            ans += num_bc;
        }
        else{
            int num_bc = 1+num_c/C;
            ans += num_bc;
        }
    }
    cout << ans << endl;
    
    return 0;
}
