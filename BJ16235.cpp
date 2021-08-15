//
//  main.cpp
//  BJ16235
//
//  Created by Hwayeon on 2021/08/13.
//

#include <iostream>
#include <queue>
using namespace std;

struct Tree{
    int x;
    int y;
    int z;
};
Tree tree;
deque<Tree> trees, n_trees, breed_trees, dead_trees;

int soil[11][11] = {0,};

int N, M, K;
int A[11][11] = {0, };
int dx[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
int dy[8] = {-1, -1, -1, 0, 0, 1, 1, 1};

void spring(){
    for(int i=0; i<trees.size(); i++){
        tree = trees[i];
        
        //땅에 양분이 부족한 경우
        if(soil[tree.y][tree.x] < tree.z){
            dead_trees.push_back(tree);
            continue;
        }
        //트리의 나이만큼 양분을 먹고, 나이 1 증가
        soil[tree.y][tree.x] -= tree.z;
        tree.z ++;
        n_trees.push_back(tree);
        if(tree.z%5==0) breed_trees.push_back(tree);
    }
}

void summer(){
    for(int i=0; i<dead_trees.size(); i++){
        tree = dead_trees[i];
        soil[tree.y][tree.x] += (tree.z/2);
    }
}

void fall(){
    Tree ntree;
    for(int i=0; i<breed_trees.size(); i++){
        tree = breed_trees[i];
        for(int d=0; d<8; d++){
            ntree.x = tree.x + dx[d];
            ntree.y = tree.y + dy[d];
            //땅을 벗어나는 칸에는 나무를 심지 않는다
            if(ntree.x<1 || ntree.x>N || ntree.y<1 || ntree.y>N) continue;
            //나이가 1인 나무가 생긴다
            ntree.z = 1;
            n_trees.push_front(ntree);
        }
    }
}

void winter(){
    for(int y=1; y<=N; y++){
        for(int x=1; x<=N; x++){
            soil[y][x] += A[y][x];
        }
    }
}

int main(int argc, const char * argv[]) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    cin >> N >> M >> K;
    for(int i=1; i<=N; i++){
        for(int j=1; j<=N; j++){
            //S2D2가 추가하는 양분의 양
            cin >> A[i][j];
            //가장 처음에 양분은 5
            soil[i][j] = 5;
        }
    }
    for(int i=0; i<M; i++){
        cin >> tree.y >> tree.x >> tree.z;
        trees.push_back(tree);
    }
    for(int k=0; k<K; k++){
        spring();
        summer();
        fall();
        winter();
        trees = n_trees;
        n_trees.clear();
        breed_trees.clear();
        dead_trees.clear();
    }
    cout << trees.size() << endl;
    return 0;
}
