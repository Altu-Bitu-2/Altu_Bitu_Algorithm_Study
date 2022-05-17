// BOJ 16236 아기 상어

/* 문제 분류: 구현, BFS */

/* 문제 설명:
* NxN 공간, 물고기 M마리, 상어 1마리. 한칸에 물고기 최대 1마리.
* 아기상어 1초에 한칸, 상하좌우로 이동가능.
* 아기상어 크기 < 물고기 크기 : 지나갈 수 없음.
* 아기상어 크기 == 물고기 크기 : 지나갈 수는 있고, 먹을 수는 없음.
* 아기상어 크기 > 물고기 크기 : 지나갈 수 있고, 먹을 수도 있음.
* 
* 1개면 그거 먹으러.
* 1개이상이면 가까운 거. 거리가 가까운 물고기가 많다면, 가장 왼쪽 위에 있는 물고기.
* 
* 아기상어크기와 같은 수의 물고기 먹으면 크기 1 증가.
* 
* 공간전체에 먹을거 없을때까지 몇초가 걸리는가?
*/

/* 문제 풀이:
*/

/* 어려웠던 점 & 다시 한번 살펴볼 부분:
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
const int INF = 401;
typedef pair<int, int> ci;

pair<int, ci> nextPos(int n, int shark_size, ci& shark, vector<vector<int>>& board) {
    int dr[4] = { -1, 1, 0, 0 };
    int dc[4] = { 0, 0, -1, 1 };

    int min_dist = INF;
    queue<ci> q; //상어가 갈 수 있는 곳
    vector<vector<int>> dist(n, vector<int>(n, 0)); //상어의 방문 여부 + 거리
    vector<ci> list; //상어가 먹을 수 있는 물고기들의 위치

    dist[shark.first][shark.second] = 1;

    q.push(shark);

    while (!q.empty()) {

        int row = q.front().first;
        int col = q.front().second;

        q.pop();

        if (dist[row][col] >= min_dist) { //최단거리 이상은 탐색할 필요 없음
            continue;
        }

        //방향배열 이용해 탐색
        for (int i = 0; i < 4; i++) {
            int nr = row + dr[i];
            int nc = col + dc[i];

            if (nr < 0 || nr >= n || nc < 0 || nc >= n || dist[nr][nc] || board[nr][nc] > shark_size) { //올바른 범위가 아니거나, 물고기 크기가 상어크기보다 크면,
                continue;
            }

            dist[nr][nc] = dist[row][col] + 1;

            if (board[nr][nc] && board[nr][nc] < shark_size) { //먹을 수 있는 물고기 발견
                list.emplace_back(nr, nc);
                min_dist = dist[nr][nc];
                continue;
            }

            q.push({ nr, nc });
        }
    }

    if (list.empty()) { //상어가 갈 수 있는 곳이 없음
        return { min_dist, {-1, -1} };
    }

    sort(list.begin(), list.end(), [](const ci& p1, const ci& p2) { //정렬 (compare 함수를 정의하지 않아도 됨)
        if (p1.first != p2.first) {
            return p1.first < p2.first;
        }

        return p1.second < p2.second;
        });

    return { min_dist - 1, list[0] };
}

int simulation(int n, pair<int, int>& shark, vector<vector<int>>& board) {
    int ans = 0, size = 2, cnt = 0;

    while (true) {
        //다음 위치 받아오기
        pair<int, ci> result = nextPos(n, size, shark, board);

        //더 이상 먹을 수 있는 물고기가 공간에 없을때
        if (result.first == INF) { //더 이상 먹을 수 있는 물고기가 공간에 없음
            break;
        }

        //먹을 수 있는 물고기 있을 때
        ans += result.first; 
        cnt++;

        if (cnt == size) { //상어 크기 증가
            cnt = 0;
            size++;
        }

        //상어 이동
        board[shark.first][shark.second] = 0;
        shark = result.second;
    }

    return ans;
}

/**
 * [아기 상어]
 *
 * 1. 상어로부터 가장 가까운 거리에 있는 모든 물고기 탐색 (BFS)
 * 2. 우선순위 조건에 맞추어 먹으러 갈 물고기 확정
 *    탐색하는 방향에 우선순위를 두는 걸로 해결되지 않음! (예제 입력 4) 정렬 필요
 * 3. 상어가 이동할 수 있는 곳이 없을 때까지 BFS 탐색 반복
 *
 * 입력 범위가 작기 때문에 매번 BFS 탐색을 반복해도 시간 초과 X
 * 가능한 물고기의 최대 마리 수 : 399마리
 * 최대 BFS 탐색 횟수 : 399회, 1회 탐색마다 while 문은 최대 400회 미만으로 순회
 * 총 연산 횟수 약 160000번으로 충분히 가능
 */

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int n;
    pair<int, int> shark_pos;

    //입력
    cin >> n;
    vector<vector<int>> board(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> board[i][j];

            if (board[i][j] == 9) { //상어의 초기 위치
                shark_pos = make_pair(i, j);
            }
        }
    }

    //연산 & 출력
    cout << simulation(n, shark_pos, board);
    return 0;
}