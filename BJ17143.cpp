#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

int R, C, M;

//board[r][c] = 해당 칸에 있는 상어 크기
int board[100][100] = {0,};

//0-상, 1-하, 2-우, 4-좌
int dx[4] = {0, 0, 1, -1};
int dy[4] = {-1, 1, 0, 0};

//낚시킹의 위치(열)
int fisher_king = -1;

//낚시킹이 잡은 상어 크기의 합
int cnt = 0;

struct Shark{
    int r;
    int c;
    int s;
    int d;
    int z;
};
Shark shark;

//격자판에 있는 상어들을 담는 벡터
vector<Shark> sharks;

//상어 이동 때 사용하는 벡터
vector<Shark> cp_sharks;

//다른 상어에 의해 잡아 먹힌 상어 크기를 담는 벡터
vector<int> dead_sharks;

//상어 이동을 하는 함수
Shark move_shark(Shark shark){
    //이동 후의 상어 상태를 담을 nshark, 속력과 크기는 변하지 않는다
    Shark nshark;
    nshark.s = shark.s;
    nshark.z = shark.z;
    
    //행 이동
    if(shark.d == 0 || shark.d == 1){
        int nr = shark.r+shark.s*dy[shark.d];
        while(nr < 0 || nr >= R){
            if(nr < 0){
                shark.s -= (shark.r+1);
                shark.r = 1;
                shark.d = 1;
                nr = shark.r+shark.s*dy[shark.d];
            }
            else if(nr >= R){
                shark.s -= (R-shark.r);
                shark.r = R-2;
                shark.d = 0;
                nr = shark.r+shark.s*dy[shark.d];
            }
        }
        nshark.r = nr;
        nshark.c = shark.c;
        nshark.d = shark.d;
    }
    //열 이동
    else{
        int nc = shark.c+shark.s*dx[shark.d];
        while(nc < 0 || nc >= C){
            if(nc < 0){
                shark.s -= (shark.c+1);
                shark.c = 1;
                shark.d = 2;
                nc = shark.c+shark.s*dx[shark.d];
            }
            else if(nc >= C){
                shark.s -= (C-shark.c);
                shark.c = C-2;
                shark.d = 3;
                nc = shark.c+shark.s*dx[shark.d];
            }
        }
        nshark.r = shark.r;
        nshark.c = nc;
        nshark.d = shark.d;
    }
    return nshark;
}

void fish(){
    //낚시 킹이 C-1에서 낚시를 할 때까지 반복한다
    while(fisher_king < C-1){
        //1. move fisher_king
        fisher_king++;
        
        //2. fish shark
        //잡힌 상어 크기를 담는 변수
        int caught = 0;
        //땅에서 가까운 상어를 잡기 위해 0부터 탐색한다
        for(int r=0; r<R; r++){
            //잡을 상어가 있는 경우, 상어를 잡는다
            if(board[r][fisher_king] != 0){
                cnt += board[r][fisher_king];
                //잡힌 상어 크기를 caught에 담아주고, 해당 격자판의 칸을 0으로 바꿔준다
                caught = board[r][fisher_king];
                board[r][fisher_king] = 0;
                break;
            }
        }
        
        //3. move sharks
        //상어를 옮긴 상태로 격자판을 만들어 주기 위해 격자판을 초기화한다
        memset(board, 0, sizeof(board));
        //기존 상어들의 상태가 당긴 sharks를 cp_sharks에 담아주고, 새로운 상어 상태를 저장하기 위해 sharks를 비운다
        cp_sharks = sharks;
        sharks.clear();
        dead_sharks.clear();
        
        while(!cp_sharks.empty()){
            shark = cp_sharks.back();
            cp_sharks.pop_back();
            //해당 상어가 낚시킹에게 잡힌 상어인 경우, 상어를 이동시키지 않고 없애준다
            if(shark.z == caught) continue;
            //이동 후의 상어 상태를 shark에 받아온다
            shark = move_shark(shark);
            
            //현재 상어의 위치에 다른 상어가 없거나, 더 작은 상어가 있는 경우, 현재 상어를 격자판에 위치시킨다
            if(board[shark.r][shark.c] < shark.z){
                //다른 상어가 있는 경우, 해당 상어를 잡아먹는다
                if(board[shark.r][shark.c] > 0){
                    dead_sharks.push_back(board[shark.r][shark.c]);
                }
                board[shark.r][shark.c] = shark.z;
                //이동한 상어를 sharks에 추가한다
                sharks.push_back(shark);
            }
        }
        
        //sharks 안에 죽은 상어를 없애준다 -> 상어 이동 후 최종 상어들의 상태를 cp_sharks에 담는다
        for(int i=0; i<sharks.size(); i++){
            bool ck = true;
            for(int j=0; j<dead_sharks.size(); j++){
                if(sharks[i].z == dead_sharks[j]){
                    ck = false;
                    break;
                }
            }
            if(ck) cp_sharks.push_back(sharks[i]);
        }
        //sharks를 cp_sharks로 바꿔준다
        sharks = cp_sharks;
    }
}

int main(int argc, const char * argv[]) {
    cin >> R >> C >> M;
    for(int i=0; i<M; i++){
        cin >> shark.r >> shark.c >> shark.s >> shark.d >> shark.z;
        //r,c,d를 각각 1씩 빼준다
        shark.r--;
        shark.c--;
        shark.d--;
        sharks.push_back(shark);
        board[shark.r][shark.c] = shark.z;
    }
    //상어가 0마리인 경우, 0 출력 후 종료
    if(M == 0){
        cout << 0 << endl;
        return 0;
    }
    //낚시 시작
    fish();
    cout << cnt << endl;
    return 0;
}
