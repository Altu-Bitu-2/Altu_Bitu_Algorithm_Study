// BOJ 1719 �ù�

/* ���� �з�: [�ִܰ��]-�÷��̵����*/

/* ���� ����:
* ����ġ �׷����� �־�������, (������� �� �������� ����� ������)
* �� �����忡�� �ٸ� ���������� �ִܰ�η� �������ؼ�, ���� ���� ���ľ��ϴ� �������� ����� 2�����迭ǥ�� ������.
*/

/* ���� Ǯ��:
* �÷��̵���� 
*   : �ѹ� ���࿡ ��� ��尣 �ִ� ��θ� ���ϴ� �˰���
*   : ���ͽ�Ʈ�� �˰���� �޸�, ���� ������ ��밡��
*   : O(n^3)
*/

/* ������� �� & �ٽ� �ѹ� ���캼 �κ�:
*/

#include <iostream>
#include <vector>

using namespace std;
const int INF = 1e5 * 2; //�ִ� n-1���� ������ ������ ��

void floydWarshall(int n, vector<vector<int>>& graph, vector<vector<int>>& table) {
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                int new_dist = graph[i][k] + graph[k][j]; //k�� ����

                if (new_dist < graph[i][j]) { //�ִܰŸ� ����
                    graph[i][j] = new_dist;
                    table[i][j] = table[i][k];
                }
            }
        }
    }
}

/*
 * [�ý�]
 *
 * graph : �÷��̵�-���� ��� ��� �׷���
 * table : ���ǥ. table[i][j] = i->j�� ���� ���� ���� ���� ���ľ� �ϴ� ����
 *
 * 1. i->j�� �߰� ��θ� i�� �ʱ�ȭ
 * 2. i->k->j�� i->j���� ª�ٸ� i->j�� �߰� ��θ� i->k�� �߰� ���(table[i][k])�� ����
 *    k�� �����ϴ°� �ƴ϶� table[i][k]�� �����ϴ� ������?
 *    ���� i->k�� ��ΰ� i->t->k��� ���� ��δ� i->t->k->j
 *    �ٷ� k�� �����ϸ� t�� ��ĥ �� �ֱ� ������ table[i][k]�� ����
 *    line 14�� table[i][j] = k�� �ٲٸ� ����� ��� �Ǵ��� Ȯ���غ�����
 */

int main() {
    int n, m, s, d, c;

    //�Է�
    cin >> n >> m;
    vector<vector<int>> graph(n + 1, vector<int>(n + 1, INF));
    vector<vector<int>> table(n + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= n; i++) {
        graph[i][i] = 0;
    }

    while (m--) { //������ �׷���
        cin >> s >> d >> c;
        //���� ����
        graph[s][d] = graph[d][s] = c;

        //��� ����
        table[s][d] = d;
        table[d][s] = s;
    }

    //����
    floydWarshall(n, graph, table);

    //���
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