// BOJ 1719 택배

/* 문제 분류: [최단경로]-플로이드워셜*/

/* 문제 설명:
* 가중치 그래프가 주어졌을때, (집하장과 각 집하장이 연결된 간선들)
* 한 집하장에서 다른 집하장으로 최단경로로 가기위해서, 가장 먼저 거쳐야하는 집하장을 기록한 2차원배열표를 만들어라.
*/

/* 문제 풀이:
* 플로이드워셜 
*   : 한번 실행에 모든 노드간 최단 경로를 구하는 알고리즘
*   : 다익스트라 알고리즘과 달리, 음의 간선도 사용가능
*   : O(n^3)
*/

/* 어려웠던 점 & 다시 한번 살펴볼 부분:
*/

#include <iostream>
#include <vector>

using namespace std;
const int INF = 1e5 * 2; //최대 n-1개의 간선을 지나게 됨

void floydWarshall(int n, vector<vector<int>>& graph, vector<vector<int>>& table) {
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                int new_dist = graph[i][k] + graph[k][j]; //k를 경유

                if (new_dist < graph[i][j]) { //최단거리 갱신
                    graph[i][j] = new_dist;
                    table[i][j] = table[i][k];
                }
            }
        }
    }
}

/*
 * [택시]
 *
 * graph : 플로이드-워셜 결과 행렬 그래프
 * table : 경로표. table[i][j] = i->j로 가기 위해 제일 먼저 거쳐야 하는 정점
 *
 * 1. i->j의 중간 경로를 i로 초기화
 * 2. i->k->j가 i->j보다 짧다면 i->j의 중간 경로를 i->k의 중간 경로(table[i][k])로 갱신
 *    k로 갱신하는게 아니라 table[i][k]로 갱신하는 이유는?
 *    만약 i->k의 경로가 i->t->k라면 최종 경로는 i->t->k->j
 *    바로 k로 갱신하면 t를 놓칠 수 있기 때문에 table[i][k]로 갱신
 *    line 14을 table[i][j] = k로 바꾸면 결과가 어떻게 되는지 확인해보세요
 */

int main() {
    int n, m, s, d, c;

    //입력
    cin >> n >> m;
    vector<vector<int>> graph(n + 1, vector<int>(n + 1, INF));
    vector<vector<int>> table(n + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= n; i++) {
        graph[i][i] = 0;
    }

    while (m--) { //무방향 그래프
        cin >> s >> d >> c;
        //간선 정보
        graph[s][d] = graph[d][s] = c;

        //경로 정보
        table[s][d] = d;
        table[d][s] = s;
    }

    //연산
    floydWarshall(n, graph, table);

    //출력
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) {
                cout << "- ";
            }
            else {
                cout << table[i][j] << ' ';
            }
        }
        cout << '\n';
    }
    return 0;
}