// BOJ 16235 나무 재테크

/* 문제 분류: 구현, 시뮬레이션 */

/* 문제 설명: 
* N*N 짜리 땅을 1*1로 나눔.
* M개의 나무 구매해 심음.
* 맨 처음엔 각 칸마다 양분5만큼 들어있음.
* 
* 봄 : 나무나이만큼 양분 먹고, 나이 1 증가. 한칸에 여러 나무가 있다면, 나이가 어린 나무부터 양분 먹음. 양분없으면 바로 죽음.
* 여름 : 죽은 나무 나이 % 2 만큼 양분이 추가됨.
* 가을 : 나이가 5의 배수인 나무에 인접한 8개의 칸에 나이가 1인 나무가 생김. 
* 겨울 : A[r][c]만큼 각 칸에 양분 추가.
* 
* K년 후에 땅에 살아있는 나무의 개수는?
*/

/* 문제 풀이:
*/

/* 어려웠던 점 & 다시 한번 살펴볼 부분 :
  1. tuple 이용
  typedef tuple<int, int, int> tp;

  deque<tp> tree;

  int age = get<0>(tree.front()); //나이
  int row = get<1>(tree.front()); //행
  int col = get<2>(tree.front()); //열
  tree.pop_front();

  2. vector응용. 행렬.
  typedef vector<vector<int>> matrix;

  matrix a(n, vector<int>(n, 0)); //nxn 0으로 초기화
  matrix land(n, vector<int>(n, 5)); //nxn 5로 초기화

*/

#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <tuple>
#include <algorithm>

using namespace std;
typedef vector<vector<int>> matrix;
typedef tuple<int, int, int> tp;

queue<tp> spring(matrix& land, deque<tp>& tree, queue<pair<int, int>>& breeding_tree) {
    queue<tp> dead_tree;

    int size = tree.size();

    while (size--) { //모든 나무 검사

        int age = get<0>(tree.front()); //나이
        int row = get<1>(tree.front()); //행
        int col = get<2>(tree.front()); //열

        tree.pop_front();

        if (land[row][col] < age) { //자신의 나이만큼 양분을 먹을 수 없다면
            dead_tree.push({ age, row, col });
            continue;
        }

        land[row][col] -= age; //양분 먹음
        tree.emplace_back(age + 1, row, col); //나이 1 증가

        if ((age + 1) % 5 == 0) { //나이가 5의 배수라면
            breeding_tree.push({ row, col }); 
        }
    }

    return dead_tree;
}

void summer(queue<tp>& dead_tree, matrix& land) {
    while (!dead_tree.empty()) {
        int age = get<0>(dead_tree.front()); //죽은 나무의 나이
        int row = get<1>(dead_tree.front()); //죽은 나무의 행 위치
        int col = get<2>(dead_tree.front()); //죽은 나무의 열 위치

        dead_tree.pop();

        land[row][col] += (age / 2);
    }
}

void fall(int n, deque<tp>& tree, queue<pair<int, int>>& breeding_tree) {
    //방향배열 이용해서 인접 8칸 방문
    int dr[8] = { -1, 1, 0, 0, -1, -1, 1, 1 };
    int dc[8] = { 0, 0, -1, 1, -1, 1, -1, 1 };

    while (!breeding_tree.empty()) {
        int row = breeding_tree.front().first; //번식할 나무의 행
        int col = breeding_tree.front().second; //번식할 나무의 열

        breeding_tree.pop();

        for (int j = 0; j < 8; j++) {
            int nr = row + dr[j];
            int nc = col + dc[j];

            if (nr < 0 || nr >= n || nc < 0 || nc >= n) { ///올바른 좌표가 아니면, (땅 영역이 아니면)
                continue;
            }

            tree.push_front({ 1, nr, nc }); //새로 생긴 나무
        }
    }
}

void winter(int n, matrix& a, matrix& land) {

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            land[i][j] += a[i][j];
        }
    }
}

/**
 * [문제 설명] - 단순 구현 문제
 * 봄: 하나의 칸마다 나이가 어린 나무부터 자신의 나이만큼 양분을 먹고, 나이가 1 증가함
 *    각 칸에 양분이 부족해 자신의 나이만큼 양분을 못 먹는 나무는 즉시 죽음
 * 여름: 봄에 죽은 나무가 양분으로 변함. 죽은 나무마다 나이를 2로 나눈 값이 양분으로 추가 (소수점 버림)
 * 가을: 나이가 5의 배수인 나무가 번식. 인접한 8개 칸에 나이가 1인 나무가 생김
 * 겨울: 로봇(S2D2)이 땅을 돌아다니면서 A[r][c]만큼 각 칸에 양분 추가
 *
 * K년이 지난 후 상도의 땅에 살아있는 나무의 개수
 *
 * [문제 풀이]
 * a: 로봇(S2D2)가 겨울에 주는 양분의 양
 * land: 땅의 양분
 * breeding_tree: 나이가 5의 배수인 트리 (번식할 트리)
 * tree: 땅에 심은 나무 나이, 행, 열 정보
 * -> deque 컨테이너를 활용해 번식한 나무를 앞에 넣어주면 입력 후에만 정렬해서 사용 가능
 *
 * 문제의 설명대로 계절별 연산을 진행
 */

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int n, m, k, x, y, z;

    //입력
    cin >> n >> m >> k;
    matrix a(n, vector<int>(n, 0));
    matrix land(n, vector<int>(n, 5)); //처음 양분 모든 칸에 5
    queue<pair<int, int>> breeding_tree; //번식할 트리
    deque<tp> tree;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }

    while (m--) {
        cin >> x >> y >> z;
        tree.emplace_back(z, x - 1, y - 1); //(0, 0)부터 시작하도록 구현하기위해 1을 빼준 인덱스에 접근
    }

    //연산
    sort(tree.begin(), tree.end()); //어린 나이 순으로 정렬

    while (k--) {
        queue<tp> dead_tree = spring(land, tree, breeding_tree); //봄이 지나고 죽은 나무
        summer(dead_tree, land);
        fall(n, tree, breeding_tree);
        winter(n, a, land);
    }

    //출력
    cout << tree.size();
    return 0;
}