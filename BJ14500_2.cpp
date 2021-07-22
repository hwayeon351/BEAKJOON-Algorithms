//
//  main.cpp
//  BJ14500
//
//  Created by Hwayeon on 2021/07/22.
//

#include <iostream>
using namespace std;

int N, M;
int paper[500][500] = {0,};
int answer = 0;

struct tetromino{
    pair<int, int> loc[4];
};
tetromino tm[19] = {
    //ㅡ
    {make_pair(0,0), make_pair(0,1), make_pair(0,2), make_pair(0,3)},
    //|
    {make_pair(0,0), make_pair(1,0), make_pair(2,0), make_pair(3,0)},
    //ㅁ
    {make_pair(0,0), make_pair(0,1), make_pair(1,0), make_pair(1,1)},
    //ㄴ
    {make_pair(0,0), make_pair(1,0), make_pair(2,0), make_pair(2,1)},
    {make_pair(0,0), make_pair(0,1), make_pair(0,2), make_pair(1,0)},
    {make_pair(0,0), make_pair(0,1), make_pair(1,1), make_pair(2,1)},
    {make_pair(1,0), make_pair(1,1), make_pair(1,2), make_pair(0,2)},
    {make_pair(2,0), make_pair(2,1), make_pair(1,1), make_pair(0,1)},
    {make_pair(0,0), make_pair(1,0), make_pair(1,1), make_pair(1,2)},
    {make_pair(0,0), make_pair(0,1), make_pair(1,0), make_pair(2,0)},
    {make_pair(0,0), make_pair(0,1), make_pair(0,2), make_pair(1,2)},
    //ㄹ
    {make_pair(0,0), make_pair(1,0), make_pair(1,1), make_pair(2,1)},
    {make_pair(0,1), make_pair(0,2), make_pair(1,1), make_pair(1,0)},
    {make_pair(0,1), make_pair(1,0), make_pair(1,1), make_pair(2,0)},
    {make_pair(0,0), make_pair(0,1), make_pair(1,1), make_pair(1,2)},
    //ㅜ
    {make_pair(0,0), make_pair(0,1), make_pair(0,2), make_pair(1,1)},
    //ㅓ
    {make_pair(1,0), make_pair(0,1), make_pair(1,1), make_pair(2,1)},
    //ㅗ
    {make_pair(0,1), make_pair(1,0), make_pair(1,1), make_pair(1,2)},
    //ㅏ
    {make_pair(0,0), make_pair(1,0), make_pair(1,1), make_pair(2,0)}
};

int main(int argc, const char * argv[]) {
    cin >> N >> M;
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            cin >> paper[i][j];
        }
    }
    //tetromino 선택
    for(int t=0; t<19; t++){
        //위치 선택
        for(int i=0; i<N; i++){
            for(int j=0; j<M; j++){
                int sum = 0;
                int x, y = 0;
                //tetromino가 놓인 칸에 쓰인 수의 합
                for(int k=0; k<4; k++){
                    y = tm[t].loc[k].first+i;
                    x = tm[t].loc[k].second+j;
                    if(x<0||x>=M||y<0||y>=N){
                        sum = 0;
                        break;
                    }
                    sum += paper[y][x];
                }
                if(sum == 0) continue;
                if(answer < sum) answer = sum;
            }
        }
    }
    cout << answer << endl;
    return 0;
}
