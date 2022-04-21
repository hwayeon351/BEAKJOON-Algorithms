//
//  main.cpp
//  BJ16235
//
//  Created by 최화연 on 2022/04/21.
//

#include <iostream>
#include <deque>
#include <vector>
using namespace std;

int area[11][11] = {0, };
int A[11][11] = {0, };

int N, M, K;

struct Tree {
    int r;
    int c;
    int age = 1;
};
Tree tree;

int dr[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dc[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

deque<Tree> trees;
vector<Tree> dead_trees;
vector<Tree> breed_trees;

int year = 0;

void spring() {
    deque<Tree> new_trees;
    while(!trees.empty()) {
        tree = trees.front();
        trees.pop_front();
        if (area[tree.r][tree.c] < tree.age) {
            dead_trees.push_back(tree);
            continue;
        }
        area[tree.r][tree.c] -= tree.age;
        tree.age ++;
        new_trees.push_back(tree);
        if (tree.age % 5 == 0) breed_trees.push_back(tree);
    }
    trees = new_trees;
}

void summer() {
    for(int i=0; i<dead_trees.size(); i++) {
        area[dead_trees[i].r][dead_trees[i].c] += int(dead_trees[i].age/2);
    }
    dead_trees.clear();
}

void fall() {
    for(int i=0; i<breed_trees.size(); i++) {
        for (int d=0; d<8; d++) {
            int nr = breed_trees[i].r + dr[d];
            int nc = breed_trees[i].c + dc[d];
            if (nr < 1 || nr > N || nc < 1 || nc > N) continue;
            Tree t;
            t.r = nr;
            t.c = nc;
            trees.push_front(t);
        }
    }
    breed_trees.clear();
}

void winter() {
    for (int r=1; r<=N; r++) {
        for (int c=1; c<=N; c++) {
            area[r][c] += A[r][c];
        }
    }
}

void grow_trees() {
    while(year < K) {
        spring();
        summer();
        fall();
        winter();
        
        year ++;
    }
}



int main(int argc, const char * argv[]) {
    cin >> N >> M >> K;
    for (int i=1; i<=N; i++) {
        for (int j=1; j<=N; j++) {
            cin >> A[i][j];
            area[i][j] = 5;
        }
    }
    
    for (int i=0; i<M; i++) {
        cin >> tree.r >> tree.c >> tree.age;
        trees.push_back(tree);
    }
    
    grow_trees();
    cout << trees.size() << endl;
    
    return 0;
}
