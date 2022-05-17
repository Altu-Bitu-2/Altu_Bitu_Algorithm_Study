// BOJ 2615 오목

/* 문제 분류: 구현, 부르트포스 */

/* 문제 설명:
* 같은색 바둑알이 가로, 세로, 대각선 방향으로 연속5개면 우승. 6개이상 연속인건 우승아님.
* 입력 주어졌을 때, 검정이 이기면 1, 흰색이 이기면 2, 승부 결정안됐으면 3 출력해라.
* 승부가 결정된 경우에는, 연속된 5개 바둑알 중에서 가장 왼쪽 위에 있는 것의 가로줄 번호 세로줄 번호도 출력해라.
* (동시에 이기는 경우는 입력으로 들어오지 않음)
*/

/* 문제 풀이:
*/

/* 어려웠던 점 & 다시 한번 살펴볼 부분:
*/


#include <iostream>
#include <vector>

using namespace std;
const int SIZE = 19;

bool promising(int r, int c, int stone, vector<vector<int>>& board) {
    //범위가 유효한지, 돌의 종류가 유효한지 확인
    return r >= 0 && r < SIZE && c >= 0 && c < SIZE && board[r][c] == stone; 
}

bool validDir(int r, int c, int d, int stone, vector<vector<int>>& board) {
    //가로, 세로, 우하향 대각선, 우상향 대각선
    int dr[4] = { 0, 1, 1, -1 };
    int dc[4] = { 1, 0, 1, 1 };

    //(r, c) 이전에 위치한 이어지는 돌이 있나?
    if (promising(r - dr[d], c - dc[d], stone, board)) {
        return false;
    }

    int cnt = 0;
    while (cnt < 6 && promising(r, c, stone, board)) { //(r, c)를 가장 왼쪽으로 하는 이어지는 바둑알의 개수
        cnt++;
        r += dr[d];
        c += dc[d];
    }

    return cnt == 5;
}

bool isEnd(int r, int c, vector<vector<int>>& board) {

    for (int i = 0; i < 4; i++) { //가로, 세로, 우하향 대각선, 우상향 대각선
       
        if (validDir(r, c, i, board[r][c], board)) {
            return true;
        }
    }
    return false;
}

/**
 * [오목]
 *
 * 1. 특정 좌표(r, c)를 가장 왼쪽으로 하는 가능한 모든 오목 배치에 대해 오목 여부 확인
 *    가능한 모든 배치 :  오른쪽, 아래, 우하향, 우상향
 * 2. (주의) 육목이상이 되는지 확인해야 함
 *
 */

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    vector<vector<int>> board(SIZE, vector<int>(SIZE, 0)); //SIZE * SIZE 를 0으로 초기화

    //입력
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            cin >> board[i][j];
        }
    }

    //연산 & 출력
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {

            if (!board[i][j]) { //돌이 없음
                continue;
            }

            if (isEnd(i, j, board)) { //결과 나왔으면 출력
                cout << board[i][j] << '\n' << i + 1 << ' ' << j + 1;
                return 0;
            }
        }
    }
    cout << 0;
    return 0;
}