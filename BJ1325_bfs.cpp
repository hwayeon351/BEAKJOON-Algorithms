//
//  main.cpp
//  BJ1325_bfs
//
//  Created by Hwayeon on 2021/08/18.
//

#include <iostream>
#include <string.h>
#include <vector>
#include <queue>
using namespace std;

int N, M;
int counts[10001] = {0, };
int visit[10001] = {0, };
vector<int> graph[10001];
int max_cnt = 0;

void bfs(int s){
    queue<int> q;
    q.push(s);
    visit[s] = 1;
    counts[s]++;
    while(!q.empty()){
        int nv = q.front();
        q.pop();
        for(int i=0; i<graph[nv].size(); i++){
            if(!visit[graph[nv][i]]){
                counts[s]++;
                visit[graph[nv][i]] = 1;
                q.push(graph[nv][i]);
            }
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
        bfs(i);
        if(counts[i] > max_cnt) max_cnt = counts[i];
    }
    for(int i=1; i<=N; i++){
        if(counts[i] == max_cnt) cout << i << " ";
    }
    
    return 0;
}
