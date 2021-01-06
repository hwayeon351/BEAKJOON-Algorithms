//
//  main.cpp
//  BJ14889
//
//  Created by Hwayeon on 2021/01/06.
//

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int N, start_s, link_s;
vector<vector<int> > s;
int min_ds = 987654321;
vector<int> start_team, link_team;
bool visit[20] = {false,};

void get_ds(){
    link_team.clear();
    start_s = 0;
    link_s = 0;
    for(int i=0; i<N; i++){
        if(!visit[i]) link_team.push_back(i);
    }
    for(int i=0; i<N/2; i++){
        for(int j=0; j<N/2; j++){
            start_s += s[start_team[i]][start_team[j]];
            link_s += s[link_team[i]][link_team[j]];
        }
    }
    if(abs(start_s-link_s) < min_ds) min_ds = abs(start_s-link_s);
}

void make_start_team(int idx){
    if(start_team.size() == N/2) {
        get_ds();
        return;
    }
    int n;
    for(n=idx; n<N; n++){
        if(visit[n]) continue;
        visit[n] = true;
        start_team.push_back(n);
        make_start_team(n);
        visit[n] = false;
        start_team.pop_back();
    }
}

int main(int argc, const char * argv[]) {
    cin >> N;
    vector<int> row;
    for(int i=0; i<N; i++){
        row.clear();
        for(int j=0; j<N; j++){
            int s_num;
            cin >> s_num;
            row.push_back(s_num);
        }
        s.push_back(row);
    }
    make_start_team(0);
    cout << min_ds << endl;

    return 0;
}
