//
//  main.cpp
//  BJ21610
//
//  Created by Hwayeon on 2021/08/10.
//

#include <iostream>
#include <vector>
#include <deque>
using namespace std;

int N, M;
//1 <= x,y <= N
int A[51][51] = {0, };
int dx[9] = {0, -1, -1, 0, 1, 1, 1, 0, -1};
int dy[9] = {0, 0, -1, -1, -1, 0, 1, 1, 1};
vector<pair<int, int>> cmd;
//비바라기 시전 비구름 초기화
deque<pair<int, int>> cloud = {{1, N}, {2, N}, {1, N-1}, {2, N-1}};
vector<pair<int, int>> basket;
int d, s;

void move_cloud(int c){
    d = cmd[c].first;
    s = cmd[c].second;
    basket.clear();
    int nx, ny;
    //1. 모든 구름 d방향으로 s칸 이동
    while(!cloud.empty()){
        nx = cloud.front().first + dx[d] * s;
        ny = cloud.front().second + dy[d] * s;
        //경계값 넘었을 때 위치 찾아주기
        if(nx > N) nx %= N;
        if(nx < 1) nx += N*(abs(nx)/N+1);
        if(ny > N) ny %= N;
        if(ny < 1) ny += N*(abs(ny)/N+1);
        //2. 구름에서 비가 내려 바구니에 물의 양 1 증가 -> 증가한 바구니 위치 담기
        A[ny][nx] ++;
        basket.push_back({nx, ny});
        //3. 구름이 사라진다
        cloud.pop_front();
    }
    
    //4. 물복사버그 마법
    for(int i=0; i<basket.size(); i++){
        int bx = basket[i].first;
        int by = basket[i].second;
        //대각선 방향 체크
        for(int dd = 2; dd <= 8; dd+=2){
            nx = bx + dx[dd];
            ny = by + dy[dd];
            //경계값 체크
            if(nx >= 1 && nx <= N && ny >= 1 && ny <= N && A[ny][nx] > 0){
                A[by][bx]++;
            }
        }
    }
    
    //5. 물의 양이 2 이상인 모든 칸에 구름 생성 -> 물의 양 -= 2, basket 벡터에 없는 위치에만 생성
    for(int y=1; y<=N; y++){
        for(int x=1; x<=N; x++){
            if(A[y][x]>=2){
                int ck = 1;
                for(int i=0; i<basket.size(); i++){
                    if(y==basket[i].second && x==basket[i].first){
                        ck = 0;
                        break;
                    }
                }
                if(ck){
                    A[y][x] -= 2;
                    cloud.push_back({x, y});
                }
            }
        }
    }
}

int cal_water(){
    int sum_w = 0;
    for(int y=1; y<=N; y++){
        for(int x=1; x<=N; x++){
            sum_w += A[y][x];
        }
    }
    return sum_w;
}

int main(int argc, const char * argv[]) {
    cin >> N >> M;
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            cin >> A[i][j];
        }
    }
    for(int i=0; i<M; i++){
        cin >> d >> s;
        cmd.push_back({d, s});
    }
    for(int i=0; i<cmd.size(); i++){
        move_cloud(i);
    }
    cout << cal_water() << endl;
    return 0;
}
