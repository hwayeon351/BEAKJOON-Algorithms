#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;


int R, C, K, W;

struct Space {
    int degree = 0;

    //1 -> 위에 벽, 2 -> 오른쪽에 벽, 3 -> 위와 오른쪽 둘다 벽
    int wall = 0;
};
Space room[21][21];
Space copy_room[21][21];

struct Heater {
    int r;
    int c;
    int num;
};
vector<Heater> heaters;

vector<pair<int, int> > research;

int visit[21][21] = { 0, };
int dr[5] = { 0, 0, 0, -1, 1 };
int dc[5] = { 0, 1, -1, 0, 0 };

void play_heater(int idx) {
    /*
    switch (heaters[idx].num)
    {
    case 1:
        if (heaters[idx].c + dc[heaters[idx].num] > C || room[heaters[idx].r][heaters[idx].c].wall == 2 || room[heaters[idx].r][heaters[idx].c].wall == 3) return;
        break;
    case 2:
        if (heaters[idx].c + dc[heaters[idx].num] < 1 || room[heaters[idx].r][heaters[idx].c + dc[heaters[idx].num]].wall == 2 || room[heaters[idx].r][heaters[idx].c + dc[heaters[idx].num]].wall == 3) return;
        break;
    case 3:
        if (heaters[idx].r + dr[heaters[idx].num] < 1 || room[heaters[idx].r][heaters[idx].c].wall == 1 || room[heaters[idx].r][heaters[idx].c].wall == 3) return;
        break;
    case 4:
        if (heaters[idx].r + dr[heaters[idx].num] > R || room[heaters[idx].r + dr[heaters[idx].num]][heaters[idx].c].wall == 1 || room[heaters[idx].r + dr[heaters[idx].num]][heaters[idx].c].wall == 3) return;
        break;
    }*/

    memset(visit, 0, sizeof(visit));
    queue<pair<pair<int, int>, int> > q;
    room[heaters[idx].r + dr[heaters[idx].num]][heaters[idx].c + dc[heaters[idx].num]].degree += 5;
    q.push({ {heaters[idx].r + dr[heaters[idx].num], heaters[idx].c + dc[heaters[idx].num]}, 5 });
    visit[heaters[idx].r + dr[heaters[idx].num]][heaters[idx].c + dc[heaters[idx].num]] = 1;
    
    while (!q.empty()) {
        int r = q.front().first.first;
        int c = q.front().first.second;
        int wind = q.front().second;
        q.pop();

        if (wind == 1) continue;
        
        switch (heaters[idx].num)
        {
        //오른쪽
        case 1:
            //오른쪽 위
            if (r > 1 && c < C && visit[r - 1][c + 1] == 0) {
                if (room[r - 1][c].wall != 2 && room[r - 1][c].wall != 3 && room[r][c].wall != 1 && room[r][c].wall != 3) {
                    visit[r - 1][c + 1] = 1;
                    room[r - 1][c + 1].degree += wind - 1;
                    q.push({ {r - 1, c + 1}, wind - 1 });
                }
            }

            //바로 오른쪽
            if (c < C && visit[r][c + 1] == 0) {
                if (room[r][c].wall != 2 && room[r][c].wall != 3) {
                    visit[r][c + 1] = 1;
                    room[r][c + 1].degree += wind - 1;
                    q.push({ {r, c + 1}, wind - 1 });
                }
            }

            //오른쪽 아래
            if (r < R && c < C && visit[r + 1][c + 1] == 0) {
                if (room[r + 1][c].wall == 0) {
                    visit[r + 1][c + 1] = 1;
                    room[r + 1][c + 1].degree += wind - 1;
                    q.push({ {r + 1, c + 1}, wind - 1 });
                }
            }
            break;

        case 2:
            //왼쪽 위
            if (r > 1 && c > 1 && visit[r - 1][c - 1] == 0) {
                if (room[r - 1][c - 1].wall != 2 && room[r - 1][c - 1].wall != 3 && room[r][c].wall != 1 && room[r][c].wall != 3) {
                    visit[r - 1][c - 1] = 1;
                    room[r - 1][c - 1].degree += wind - 1;
                    q.push({ {r - 1, c - 1}, wind - 1 });
                }
            }

            //바로 왼쪽
            if (c > 1 && visit[r][c - 1] == 0) {
                if (room[r][c - 1].wall != 2 && room[r][c - 1].wall != 3) {
                    visit[r][c - 1] = 1;
                    room[r][c - 1].degree += wind - 1;
                    q.push({ {r, c - 1}, wind - 1 });
                }
            }

            //왼쪽 아래
            if (r < R && c > 1 && visit[r + 1][c - 1] == 0) {
                if (room[r + 1][c].wall != 1 && room[r + 1][c].wall != 3 && room[r + 1][c - 1].wall != 2 && room[r + 1][c - 1].wall != 3) {
                    visit[r + 1][c - 1] = 1;
                    room[r + 1][c - 1].degree += wind - 1;
                    q.push({ {r + 1, c - 1}, wind - 1 });
                }
            }
            break;
        
        //위쪽
        case 3:
            //왼쪽 위
            if (r > 1 && c > 1 && visit[r - 1][c - 1] == 0) {
                if (room[r][c - 1].wall == 0) {
                    visit[r - 1][c - 1] = 1;
                    room[r - 1][c - 1].degree += wind - 1;
                    q.push({ {r - 1, c - 1}, wind - 1 });
                }
            }

            //바로 위
            if (r > 1 && visit[r - 1][c] == 0) {
                if (room[r][c].wall != 1 && room[r][c].wall != 3) {
                    visit[r - 1][c] = 1;
                    room[r - 1][c].degree += wind - 1;
                    q.push({ {r - 1, c}, wind - 1 });
                }
            }

            //오른쪽 위
            if (r > 1 && c < C && visit[r - 1][c + 1] == 0) {
                if (room[r][c].wall != 2 && room[r][c].wall != 3 && room[r][c + 1].wall != 1 && room[r][c + 1].wall != 3) {
                    visit[r - 1][c + 1] = 1;
                    room[r - 1][c + 1].degree += wind - 1;
                    q.push({ {r - 1, c + 1}, wind - 1 });
                }
            }
            break;
        
        //아래쪽
        case 4:
            //왼쪽 아래
            if (r < R && c > 1 && visit[r + 1][c - 1] == 0) {
                if (room[r + 1][c - 1].wall != 1 && room[r + 1][c - 1].wall != 3 && room[r][c - 1].wall != 2 && room[r][c - 1].wall != 3) {
                    visit[r + 1][c - 1] = 1;
                    room[r + 1][c - 1].degree += wind - 1;
                    q.push({ {r + 1, c - 1}, wind - 1 });
                }
            }
            //바로 아래
            if (r < R && visit[r + 1][c] == 0) {
                if (room[r + 1][c].wall != 1 && room[r + 1][c].wall != 3) {
                    visit[r + 1][c] = 1;
                    room[r + 1][c].degree += wind - 1;
                    q.push({ {r + 1, c}, wind - 1 });
                }
            }

            //오른쪽 아래
            if (r < R && c < C && visit[r + 1][c + 1] == 0) {
                if (room[r][c].wall != 2 && room[r][c].wall != 3 && room[r + 1][c + 1].wall != 1 && room[r + 1][c + 1].wall != 3) {
                    visit[r + 1][c + 1] = 1;
                    room[r + 1][c + 1].degree += wind - 1;
                    q.push({ {r + 1, c + 1}, wind - 1 });
                }
            }
            break;
        }
    }
}

bool check_degree() {
    bool check = true;

    for (int i = 0; i < research.size(); i++) {
        if (room[research[i].first][research[i].second].degree >= K) continue;
        check = false;
        break;
    }

    return check;
}

void decrease_degree() {
    for (int r = 1; r <= R; r++) {
        if (room[r][1].degree > 0) room[r][1].degree--;
        if (room[r][C].degree > 0) room[r][C].degree--;
    }
    for (int c = 2; c < C; c++) {
        if (room[1][c].degree > 0) room[1][c].degree--;
        if (room[R][c].degree > 0) room[R][c].degree--;
    }
}

void change_degree() {
    memcpy(copy_room, room, sizeof(copy_room));
    for (int r = 1; r <= R; r++) {
        for (int c = 1; c <= C; c++) {
            //오른쪽
            if (c < C && copy_room[r][c].wall != 2 && copy_room[r][c].wall != 3) {
                if (copy_room[r][c].degree > copy_room[r][c + 1].degree) {
                    int degree = (copy_room[r][c].degree - copy_room[r][c + 1].degree) / 4;
                    room[r][c].degree -= degree;
                    room[r][c + 1].degree += degree;
                }
                else if (copy_room[r][c].degree < copy_room[r][c + 1].degree){
                    int degree = (copy_room[r][c + 1].degree - copy_room[r][c].degree) / 4;
                    room[r][c].degree += degree;
                    room[r][c + 1].degree -= degree;
                }
            }
            //아래쪽
            if (r < R && copy_room[r + 1][c].wall != 1 && copy_room[r + 1][c].wall != 3) {
                if (copy_room[r][c].degree > copy_room[r + 1][c].degree) {
                    int degree = (copy_room[r][c].degree - copy_room[r + 1][c].degree) / 4;
                    room[r][c].degree -= degree;
                    room[r + 1][c].degree += degree;
                }
                else if (copy_room[r][c].degree < copy_room[r + 1][c].degree) {
                    int degree = (copy_room[r + 1][c].degree - copy_room[r][c].degree) / 4;
                    room[r][c].degree += degree;
                    room[r + 1][c].degree -= degree;
                }
            }
        }
    }
}

int eat_choco() {
    int choco = 0;
    bool check = false;
    while (!check) {
        if (choco > 100) break;

        //1. 온풍기에서 바람 나온다
        for (int i = 0; i < heaters.size(); i++) {
            play_heater(i);
        }
        
        //2. 온도가 조절된다
        change_degree();

        //3. 바깥쪽 칸의 온도가 1 감소한다
        decrease_degree();

        //4. 초콜릿을 하나 먹는다
        choco++;

        //5. 조사하는 모든 칸의 온도 확인하기
        check = check_degree();
    }

    return choco;
}

int main()
{
    cin >> R >> C >> K;
    for (int r = 1; r <= R; r++) {
        for (int c = 1; c <= C; c++) {
            int num;
            cin >> num;
            if (num > 0 && num < 5) {
                Heater h;
                h.r = r;
                h.c = c;
                h.num = num;
                heaters.push_back(h);
            }
            else if (num == 5) {
                research.push_back({ r, c });
            }
        }
    }
    
    cin >> W;
    for (int w = 0; w < W; w++) {
        int x, y, t;
        cin >> x >> y >> t;
        if (room[x][y].wall == 0) {
            if (t == 0) {
                room[x][y].wall = 1;
            }
            else {
                room[x][y].wall = 2;
            }
        }
        else {
            room[x][y].wall = 3;
        }
    }

    cout << eat_choco() << "\n";

    return 0;
}
