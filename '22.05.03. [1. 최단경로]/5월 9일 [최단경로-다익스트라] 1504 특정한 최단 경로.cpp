// BOJ 1504 특정한 최단 경로

/* 문제 분류: [최단경로]다익스트라*/

/* 문제 설명:
* 양방향그래프. 1~N번 정점 존재.
* 1번 정점에서 N번 정점까지,
* 1) v1, v2 정점을 지나고 
* 2) 지났던 정점, 간선 다시 지날 수 있을 때
* 최단경로를 구해라.
*/

/* 문제 풀이:
* 다익스트라
*   1. 출발노드 설정
*   2. 출발노드 기준으로 각 노드의 최소 비용 저장
*   3. 방문하지 않은 노드 중 최소비용인 노드 선택
*   4. 해당 노드 거쳐서 특정한 노드로 가는 경우 >> 최소 비용 갱신
*/

/* 어려웠던 점 & 다시 한번 살펴볼 부분:
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;
typedef pair<int, int> ci;
const int INF = 1e5 * 8 * 3; //최대 N-1개의 간선을 지나게 됨 * 중복 순회 가능(3)

//다익스트라
vector<int> dijkstra(int start, int v, vector<vector<ci>>& graph) {
    vector<int> dist(v + 1, INF);
    priority_queue<ci, vector<ci>, greater<>> pq; //우선순위 큐 (힙)

    dist[start] = 0; //출발노드 설정
    pq.push({ 0, start });

    while (!pq.empty()) {
        //우선순위큐에서 하나 꺼내기. 비용이 최소인 것이 꺼내짐.
        int weight = pq.top().first;
        int node = pq.top().second;
        pq.pop();

        //최단거리가 아닌 경우 스킵
        if (weight > dist[node]) {
            continue;
        }

        for (int i = 0; i < graph[node].size(); i++) {
            int next_node = graph[node][i].first; //선택된 노드의 인접 노드
            int next_weight = weight + graph[node][i].second; //선택된 노드를 인접 노드로 거쳐서 가는 비용
            
            if (next_weight < dist[next_node]) { //최소비용 갱신
                dist[next_node] = next_weight;
                pq.push({ next_weight, next_node });
            }
        }
    }
    return dist;
}

/**
 * [특정한 최단 경로]
 *
 * 가능한 경로
 * 1. 1 -> v1 -> v2 -> n
 * 2. 1 -> v2 -> v1 -> n
 * -> 1, v1, v2를 시작점으로 하는 다익스트라 함수 실행하기
 *
 * !주의! 한 번 이동했던 정점, 간선을 다시 방문할 수 있음. 즉 1->N의 최댓값이 INF(1e5*8)이 아니라 3*INF!
 */

int main() {
    int n, e, a, b, c, v1, v2;

    //입력
    cin >> n >> e;

    vector<vector<ci>> graph(n + 1, vector<ci>(0));
    vector<vector<int>> dist(3, vector<int>(n + 1, 0));

    while (e--) { //무방향 그래프
        cin >> a >> b >> c;
        graph[a].emplace_back(b, c); //무방향그래프이므로 정점a에도 넣고,
        graph[b].emplace_back(a, c); //정점b에도 넣음
    }
    cin >> v1 >> v2;

    //연산
    vector<int> start_nodes = { 1, v1, v2 };
    for (int i = 0; i < 3; i++) { //1, v1, v2에서 시작한 다익스트라 결과 저장
        dist[i] = dijkstra(start_nodes[i], n, graph);
    }

    //1->v1->v2->n의 경로와 1->v2->v1->n의 경로 중 최솟값
    //무방향 그래프기 때문에 v1->v2와 v2->v1은 사실 같은 값!
    int ans = min(dist[0][v1] + dist[1][v2] + dist[2][n], 
                dist[0][v2] + dist[2][v1] + dist[1][n]);

    //출력
    cout << ((ans >= INF) ? -1 : ans);
    return 0;
}