//
//  main.cpp
//  BJ15686
//
//  Created by Hwayeon on 2021/08/04.
//

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

int N, M;
int map[51][51] = {0,};
vector<pair<int, int>> house;
vector<pair<int, int>> chicken_shop;
vector<pair<int, int>> survive_chicken_shop;

int answer = 20001;

int cal_chicken_distance(){
    int chicken_distance = 0;
    for(int h=0; h<house.size(); h++){
        int hx = house[h].first;
        int hy = house[h].second;
        int min_dis = 100;
        for(int c=0; c<survive_chicken_shop.size(); c++){
            int cx = survive_chicken_shop[c].first;
            int cy = survive_chicken_shop[c].second;
            int n_dis = abs(cx-hx) + abs(cy-hy);
            if(min_dis > n_dis){
                min_dis = n_dis;
            }
        }
        chicken_distance += min_dis;
    }
    return chicken_distance;
}

void choose_chicken_shop(int cnt, int idx){
    //폐업시키지 않을 치킨집을 M개 고른 경우,
    if(cnt == M){
        int chicken_distance = cal_chicken_distance();
        if(answer > chicken_distance) answer = chicken_distance;
        return;
    }
    if(M-cnt > chicken_shop.size()-(idx+1)) return;
    for(int i=idx+1; i<chicken_shop.size(); i++){
        survive_chicken_shop.push_back(chicken_shop[i]);
        choose_chicken_shop(cnt+1, i);
        survive_chicken_shop.pop_back();
    }
}

int main(int argc, const char * argv[]) {
    cin >> N >> M;
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            cin >> map[i][j];
            //집인 경우,
            if(map[i][j] == 1){
                house.push_back({j, i});
            }
            //치킨 집인 경우,
            else if(map[i][j] == 2){
                chicken_shop.push_back({j, i});
            }
        }
    }
    choose_chicken_shop(0, -1);
    cout << answer << endl;
    return 0;
}
