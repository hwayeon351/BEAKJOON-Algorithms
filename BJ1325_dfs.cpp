//
//  main.cpp
//  BJ1325
//
//  Created by Hwayeon on 2021/08/18.
//

#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

int N, M;
vector<int> graph[10001];
int counts[10001] = {0, };
int visit[10001] = {0, };
int max_cnt = 0;

void dfs(int v, int s){
    for(int i=0; i<graph[v].size(); i++){
        if(!visit[graph[v][i]]){
            visit[graph[v][i]] = 1;
            counts[s]++;
            dfs(graph[v][i], s);
        }
    }
}

int main(int argc, const char * argv[]) {
    cin >> N >> M;
    for(int i=0; i<M; i++){
        int v1, v2;
        cin >> v1 >> v2;
        graph[v2].push_back(v1);
    }
    for(int i=1; i<=N; i++){
        memset(visit, 0, sizeof(visit));
        visit[i] = 1;
        dfs(i, i);
        if(counts[i] > max_cnt) max_cnt = counts[i];
    }
    for(int i=1; i<=N; i++){
        if(counts[i] == max_cnt) cout << i << " ";
    }
    cout << endl;
    return 0;
}
