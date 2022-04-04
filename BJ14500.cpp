//
//  main.cpp
//  BJ14500
//
//  Created by 최화연 on 2022/04/04.
//

#include <iostream>
using namespace std;

int board[500][500] = {0, };
int tetromino[19][4][2] = {
    //ㅡ
    {{0, 0}, {1, 0}, {2, 0}, {3, 0}},
    //ㅣ
    {{0, 0}, {0, 1}, {0, 2}, {0, 3}},
    //ㅁ
    {{0, 0}, {1, 0}, {0, 1}, {1, 1}},
    //ㄴ
    {{0, 0}, {0, 1}, {0, 2}, {1, 2}},
    {{2, -1}, {0, 0}, {1, 0}, {2, 0}},
    {{0, 0}, {1, 0}, {1, 1}, {1, 2}},
    {{0, 0}, {1, 0}, {2, 0}, {0, 1}},
    {{1, -2}, {1, -1}, {1, 0}, {0, 0}},
    {{0, 0}, {0, 1}, {1, 1}, {2, 1}},
    {{0, 0}, {1, 0}, {0, 1}, {0, 2}},
    {{0, 0}, {1, 0}, {2, 0}, {2, 1}},
    //ㄹ
    {{0, 0}, {0, 1}, {1, 1}, {1, 2}},
    {{0, 0}, {1, -1}, {2, -1}, {1, 0}},
    {{1, -1}, {0, 0}, {1, 0}, {0, 1}},
    {{0, 0}, {1, 0}, {1, 1}, {2, 1}},
    //ㅜ
    {{0, 0}, {1, 0}, {2, 0}, {1, 1}},
    //ㅏ
    {{0, 0}, {0, 1}, {1, 1}, {0, 2}},
    //ㅓ
    {{1, -1}, {0, 0}, {1, 0}, {1, 1}},
    //ㅗ
    {{1, -1}, {0, 0}, {1, 0}, {2, 0}}
};

int max_sum = 0;
int N, M;

void get_max_sum() {
    for(int y=0; y<N; y++) {
        for(int x=0; x<M; x++) {
            for(int i=0; i<19; i++) {
                int sum = 0;
                bool check = true;
                for(int j=0; j<4; j++) {
                    int nx = x + tetromino[i][j][0];
                    int ny = y + tetromino[i][j][1];
                    if (nx<0 || nx>=M || ny<0 || ny>=N) {
                        check = false;
                        break;
                    }
                    sum += board[ny][nx];
                }
                if (!check) continue;
                if (max_sum < sum) max_sum = sum;
            }
        }
    }
}

int main(int argc, const char * argv[]) {
    cin >> N >> M;
    for(int i=0; i<N; i++) {
        for(int j=0; j<M; j++) {
            cin >> board[i][j];
        }
    }
    
    get_max_sum();
    
    cout << max_sum << endl;
    
    return 0;
}
