//
//  main.cpp
//  BJ17825
//
//  Created by 최화연 on 2022/04/28.
//

#include <iostream>
#include <string.h>
using namespace std;

struct Space {
    int next[2] = {0, };
    int score;
};

Space board[33] = {
    //0~5
    {{1, 0}, 0}, {{2, 0}, 2}, {{3, 0}, 4}, {{4, 0}, 6}, {{5, 0}, 8}, {{6, 21}, 10},
    //6~10
    {{7, 0}, 12}, {{8, 0}, 14}, {{9, 0}, 16}, {{10, 0}, 18}, {{11, 24}, 20},
    //11~15
    {{12, 0}, 22}, {{13, 0}, 24}, {{14, 0}, 26}, {{15, 0}, 28}, {{16, 27}, 30},
    //16~20
    {{17, 0}, 32}, {{18, 0}, 34}, {{19, 0}, 36}, {{20, 0}, 38}, {{32, 0}, 40},
    //21~25
    {{22, 0}, 13}, {{23, 0}, 16}, {{26, 0}, 19}, {{25, 0}, 22}, {{26, 0}, 24},
    //26~30
    {{30, 0}, 25}, {{28, 0}, 28}, {{29, 0}, 27}, {{26, 0}, 26}, {{31, 0}, 30},
    //31, 32
    {{20, 0}, 35}, {{0, 0}, 0}
};

int horse[5] = {0, };
int dice[10] = {0, };

int max_score = 0;

void play_game(int i, int score) {
    if (score > max_score) max_score = score;
    if (i >= 10) return;
    
    for (int h=1; h<=4; h++) {
        if (horse[h] >= 32) continue;
        //파란길로 가야할 때
        if (horse[h] == 5 || horse[h] == 10 || horse[h] == 15) {
            int temp_horse = horse[h];
            int new_horse = board[horse[h]].next[1];
            for (int d=1; d<dice[i]; d++) {
                new_horse = board[new_horse].next[0];
                if (new_horse >= 32) break;
            }
            bool check = true;
            for (int hh=1; hh<=4; hh++) {
                if (h == hh) continue;
                if (new_horse < 32 && new_horse == horse[hh]) {
                    check = false;
                    break;
                }
            }
            if (check) {
                horse[h] = new_horse;
                int new_score = score;
                if (new_horse < 32) new_score += board[new_horse].score;
                play_game(i+1, new_score);
                horse[h] = temp_horse;
            }
        }
        //빨간길로 가야할 때
        else {
            int temp_horse = horse[h];
            int new_horse = horse[h];
            for (int d=0; d<dice[i]; d++) {
                new_horse = board[new_horse].next[0];
                if (new_horse >= 32) break;
            }
            bool check = true;
            for (int hh=1; hh<=4; hh++) {
                if (h == hh) continue;
                if (new_horse < 32 && new_horse == horse[hh]) {
                    check = false;
                    break;
                }
            }
            if (check) {
                horse[h] = new_horse;
                int new_score = score;
                if (new_horse < 32) new_score += board[new_horse].score;
                play_game(i+1, new_score);
                horse[h] = temp_horse;
            }
        }
    }
    
}

int main(int argc, const char * argv[]) {
    for (int i=0; i<10; i++) {
        cin >> dice[i];
    }
    
    play_game(0, 0);
    
    cout << max_score << endl;
    
    return 0;
}
