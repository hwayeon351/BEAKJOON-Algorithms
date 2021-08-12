//
//  main.cpp
//  BJ15685
//
//  Created by Hwayeon on 2021/08/12.
//

#include <iostream>
#include <vector>
using namespace std;

int N;
vector<pair<int, int>> dragon_curve;

int board[102][102] = {0,};
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, -1, 0, 1};

void make_dragon_curve(int g){
    while(g > 0){
        int lx = dragon_curve.back().first;
        int ly = dragon_curve.back().second;
        int d_size = dragon_curve.size();
        for(int i=d_size-2; i>=0; i--){
            //평행이동
            int x = dragon_curve[i].first - lx;
            int y = dragon_curve[i].second - ly;
            //회전변환 후 평행이동
            int nx = -y + lx;
            int ny = x + ly;
            dragon_curve.push_back({nx, ny});
            board[ny][nx] = 1;
        }
        g--;
    }
}

int cal_area(){
    int area = 0;
    for(int i=0; i<101; i++){
        for(int j=0; j<101; j++){
            if(board[i][j] && board[i][j+1] && board[i+1][j] && board[i+1][j+1]) area++;
        }
    }
    return area;
}

int main(int argc, const char * argv[]) {
    cin >> N;
    for(int i=0; i<N; i++){
        int x, y, d, g;
        cin >> x >> y >> d >> g;
        dragon_curve.clear();
        dragon_curve.push_back(make_pair(x, y));
        board[y][x] = 1;
        dragon_curve.push_back(make_pair(x+dx[d], y+dy[d]));
        board[y+dy[d]][x+dx[d]] = 1;
        make_dragon_curve(g);
    }
    cout << cal_area() << endl;
    return 0;
}
