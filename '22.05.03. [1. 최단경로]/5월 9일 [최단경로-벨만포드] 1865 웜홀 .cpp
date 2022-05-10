// BOJ 1865 웜홈
/* 문제 분류: [최단경로]벨만포드*/

/* 문제 설명:
* N개의 정점, M개의 도로(시간 양수), W개의 웜홀(시간 음수)
* 한지점에서 출발, 다시 그 지점으로 돌아왔을때, 
* 출발했을때보다 시간이 빨라진 경우가 있는지 판단
*/

/* 문제 풀이:
* 벨만포드
*   : 한노드에서 다른노드까지의 최단거리 구하는 알고리즘 (간선중심)
*   : 간선 가중치 음수 가능 (다익스트라는 안됨)
*   1. 출발노드 설정
*   2. 최단거리 테이블 초기화
*   3. 아래과정 v-1 번 반복
*       1) 모든 간선 E개 하나씩 확인
*       2) 각 간선을 거쳐 다른 노드로 가는 비용을 계산해서 최단거리테이블 갱신
* 
*   음수 간선 순환이 발생하는지 체크하고 싶다면 3번 과정을 한 번 더 수행
*   최단 거리 테이블이 갱신된다면 음수 간선 순환이 존재하는 것
*/

#include <iostream>
#include <vector>
#include <tuple>

using namespace std;
typedef tuple<int, int, int> tp;
const int INF = 5e6; //최대 n-1개의 간선을 지나게 됨 -> n * (가중치 최대값)

vector<int> bellmanFord(int start, int n, vector<tp>& edges) {
    vector<int> dist(n + 1, 0); 
    //시작점을 정해주지 않았으므로 모든 정점에서 음의 사이클이 있나 없나 확인해야함 (그게 되돌아왔는데 시간이 빨라지는 경우임)
    //따라서 일반적인 벨만포드와 달리, 시작점을 정하지 않고, 간선가중치0으로 모든 정점에 갈 수 있는 가상의 정점을 하나 만들고 그것을 시작점으로 함.
    //따라서 그 점으로부터 모든 점까지의 가중치는 다 0이므로 dist vector를 0으로 초기화해야함.

    for (int i = 1; i <= n; i++) { //정점개수-1 번 반복

        bool flag = true;

        for (int j = 0; j < edges.size(); j++) {
            int s = get<0>(edges[j]);
            int d = get<1>(edges[j]);
            int w = get<2>(edges[j]);

            if (dist[s] == INF) {
                continue;
            }

            //음의 사이클이 생겼는지 확인
            int weight = dist[s] + w;
            if (weight < dist[d]) {
                dist[d] = weight;
                flag = false;
                if (i == n) {
                    return { INF + 1 }; //음의 사이클이 생겼음을 INF+1로 나타냄
                }
            }
        }

        if (flag) {
            break;
        }
    }
    return dist;
}

/**
 * [웜홀]
 *
 * 벨만-포드 문제
 *
 * 시간이 되돌아가서 출발 지점에 도착하는 경우 = 음의 사이클이 생긴 경우
 *
 * 특별히 시작점이 주어지지 않았으므로, 벨만-포드를 특정 정점에서 시작하는 경우만 돌릴 시 해당 정점에서 닿을 수 없는 음의 사이클의 존재를 판단할 수 없음
 * 그러나, 모든 정점에서 벨만-포드 연산을 하게 되면 O(n^2*E)의 시간 복잡도가 걸려서 효율적이지 않음
 * => 모든 정점에 도달할 수 있는 임의의 가짜 정점을 만들어서 시작점을 0으로 하는 한 번의 벨만-포드 연산으로 그래프 전체에 대한 음의 사이클 존재 여부 판단!
 * => 이때, 가짜 정점 0에서 모든 정점으로의 거리가 0인 간선이 있다고 가정하여 dist배열을 0으로 초기화
 */

int main() {
    int tc, n, m, w, s, e, t;

    //테스트케이스
    cin >> tc;

    while (tc--) {
        //입력
        cin >> n >> m >> w;

        vector<tp> edges; //간선의 수
        while (m--) { //도로 -> 무방향
            cin >> s >> e >> t;
            edges.push_back({ s, e, t });
            edges.push_back({ e, s, t });
        }
        while (w--) { //웜홀 -> 방향
            cin >> s >> e >> t;
            edges.push_back({ s, e, -t });
        }

        //연산
        vector<int> dist = bellmanFord(0, n, edges);

        //출력
        if (dist[0] == INF + 1) {
            cout << "YES\n";
        }
        else {
            cout << "NO\n";
        }
    }
    return 0;
}