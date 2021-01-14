//
//  main.cpp
//  BJ14890
//
//  Created by Hwayeon on 2021/01/12.
//
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

int road[100][100];
int N, L;

int find_road_row(){
    vector<pair<int,int> > q;
    int row_road = 0;
    for(int row=0; row<N; row++){
        q.clear();
        bool visit[100] = {false,};
        q.push_back(make_pair(row, 0));
        int col = 1;
        while(col < N){
            if(road[row][col] == road[q.back().first][q.back().second]){
                q.push_back(make_pair(row, col));
                col++;
            }
            else if(road[row][col] > road[q.back().first][q.back().second]){
                if(abs(road[row][col] - road[q.back().first][q.back().second]) == 1){
                    if(q.size()>=L){
                        bool check = true;
                        for(int i=1; i<=L; i++){
                            int now_col = q[q.size()-i].second;
                            if(visit[now_col]==true) check = false;
                        }
                        if(check == false) break;
                        else{
                            q.clear();
                            q.push_back(make_pair(row, col));
                            col++;
                        }
                    }
                    else break;
                }
                else break;
            }
            else{
                if(abs(road[row][col] - road[q.back().first][q.back().second]) == 1){
                    bool check = true;
                    for(int i=col; i<col+L; i++){
                        if(road[row][i] != road[row][col]) check = false;
                    }
                    if(check == false) break;
                    else{
                        q.clear();
                        for(int i=col; i<col+L; i++){
                            visit[i] = true;
                        }
                        q.push_back(make_pair(row, col+L-1));
                        col = col+L;
                    }
                }
                else break;
            }
        }
        if(col == N) {
            row_road++;
        }
    }
    return row_road;
}

int find_road_col(){
    int col_road = 0;
    vector<pair<int,int> > q;
    for(int col=0; col<N; col++){
        q.clear();
        bool visit[100] = {false,};
        q.push_back(make_pair(0, col));
        int row = 1;
        while(row < N){
            if(road[row][col] == road[q.back().first][q.back().second]){
                q.push_back(make_pair(row, col));
                row++;
            }
            else if(road[row][col] > road[q.back().first][q.back().second]){
                if(abs(road[row][col] - road[q.back().first][q.back().second]) == 1){
                    if(q.size()>=L){
                        bool check = true;
                        for(int i=1; i<=L; i++){
                            int now_row = q[q.size()-i].first;
                            if(visit[now_row]==true) check = false;
                        }
                        if(check == false) break;
                        q.clear();
                        q.push_back(make_pair(row, col));
                        row++;
                    }
                    else break;
                }
                else break;
            }
            else{
                bool check = true;
                for(int i=row; i<row+L; i++){
                    if(road[i][col] != road[row][col]) check = false;
                }
                if(check == false) break;
                else{
                    q.clear();
                    for(int i=row; i<row+L; i++){
                        visit[i] = true;
                    }
                    q.push_back(make_pair(row+L-1, col));
                    row = row+L;
                }
            }
        }
        if(row == N) {
            col_road++;
        }
    }
    return col_road;
}

int main(int argc, const char * argv[]) {
    cin >> N >> L;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cin >> road[i][j];
        }
    }
    cout << find_road_row()+find_road_col() << endl;
    return 0;
}
