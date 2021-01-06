//
//  main.cpp
//  BJ14502
//
//  Created by Hwayeon on 2020/12/16.
//

#include <iostream>
#include <vector>
using namespace std;

int N, M;
int max_area = 0;
int lab[8][8] = {-1,};
struct location{
    int x;
    int y;
};
vector<location> virus;
vector<location> init;
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, -1, 0 ,1};


void print_lab(){
    for(int y=0; y<N; y++){
        for(int x=0; x<M; x++){
            cout << lab[y][x];
        }
        cout << endl;
    }
}

int check_safe_area(){
    int virus = 0, wall = 0;
    for(int y=0; y<N; y++){
        for(int x=0; x<M; x++){
            if(lab[y][x]==2) virus++;
            else if(lab[y][x]==1) wall++;
        }
    }
    return N * M - (virus + wall);
}

void init_lab(){
    for(int i=0; i<init.size(); i++){
        lab[init[i].y][init[i].x] = 0;
    }
    init.clear();
}

int spread_virus(){
    bool visit[8][8] = {false,};
    int area = 0;
    while(virus.size()>0){
        int x = virus.back().x;
        int y = virus.back().y;
        virus.pop_back();
        visit[y][x] = true;
        for(int d=0; d<4; d++){
            int nx = x+dx[d];
            int ny = y+dy[d];
            if((lab[ny][nx] == 1)||(nx<0 || nx>=M) || (ny<0 || ny>=N) || (visit[ny][nx]==true)) continue;
            lab[ny][nx] = 2;
            location new_v;
            new_v.x = nx;
            new_v.y = ny;
            virus.push_back(new_v);
            init.push_back(new_v);
        }
    }
    area = check_safe_area();
    init_lab();
    return area;
}

void install_wall(int cnt){
    if(cnt>=3){
        int area = spread_virus();
        if(area > max_area) max_area = area;
        return;
    }
    for(int y=0; y<N; y++){
        for(int x=0; x<M; x++){
            if(lab[y][x] == 0){
                lab[y][x] = 1;
                install_wall(cnt+1);
                lab[y][x] = 0;
            }
        }
    }

}

int main(int argc, const char * argv[]) {
    cin >> N >> M;
    for(int y=0; y<N; y++){
        for(int x=0; x<M; x++){
            cin >> lab[y][x];
            if(lab[y][x]==2){
                location loc;
                loc.x = x;
                loc.y = y;
                virus.push_back(loc);
            }
        }
    }
    install_wall(1);
    cout << max_area;
    return 0;
}
