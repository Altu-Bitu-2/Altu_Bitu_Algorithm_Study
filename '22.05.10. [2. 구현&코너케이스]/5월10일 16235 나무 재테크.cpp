// BOJ 16235 ���� ����ũ

/* ���� �з�: ����, �ùķ��̼� */

/* ���� ����: 
* N*N ¥�� ���� 1*1�� ����.
* M���� ���� ������ ����.
* �� ó���� �� ĭ���� ���5��ŭ �������.
* 
* �� : �������̸�ŭ ��� �԰�, ���� 1 ����. ��ĭ�� ���� ������ �ִٸ�, ���̰� � �������� ��� ����. ��о����� �ٷ� ����.
* ���� : ���� ���� ���� % 2 ��ŭ ����� �߰���.
* ���� : ���̰� 5�� ����� ������ ������ 8���� ĭ�� ���̰� 1�� ������ ����. 
* �ܿ� : A[r][c]��ŭ �� ĭ�� ��� �߰�.
* 
* K�� �Ŀ� ���� ����ִ� ������ ������?
*/

/* ���� Ǯ��:
*/

/* ������� �� & �ٽ� �ѹ� ���캼 �κ� :
  1. tuple �̿�
  typedef tuple<int, int, int> tp;

  deque<tp> tree;

  int age = get<0>(tree.front()); //����
  int row = get<1>(tree.front()); //��
  int col = get<2>(tree.front()); //��
  tree.pop_front();

  2. vector����. ���.
  typedef vector<vector<int>> matrix;

  matrix a(n, vector<int>(n, 0)); //nxn 0���� �ʱ�ȭ
  matrix land(n, vector<int>(n, 5)); //nxn 5�� �ʱ�ȭ

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

    while (size--) { //��� ���� �˻�

        int age = get<0>(tree.front()); //����
        int row = get<1>(tree.front()); //��
        int col = get<2>(tree.front()); //��

        tree.pop_front();

        if (land[row][col] < age) { //�ڽ��� ���̸�ŭ ����� ���� �� ���ٸ�
            dead_tree.push({ age, row, col });
            continue;
        }

        land[row][col] -= age; //��� ����
        tree.emplace_back(age + 1, row, col); //���� 1 ����

        if ((age + 1) % 5 == 0) { //���̰� 5�� ������
            breeding_tree.push({ row, col }); 
        }
    }

    return dead_tree;
}

void summer(queue<tp>& dead_tree, matrix& land) {
    while (!dead_tree.empty()) {
        int age = get<0>(dead_tree.front()); //���� ������ ����
        int row = get<1>(dead_tree.front()); //���� ������ �� ��ġ
        int col = get<2>(dead_tree.front()); //���� ������ �� ��ġ

        dead_tree.pop();

        land[row][col] += (age / 2);
    }
}

void fall(int n, deque<tp>& tree, queue<pair<int, int>>& breeding_tree) {
    //����迭 �̿��ؼ� ���� 8ĭ �湮
    int dr[8] = { -1, 1, 0, 0, -1, -1, 1, 1 };
    int dc[8] = { 0, 0, -1, 1, -1, 1, -1, 1 };

    while (!breeding_tree.empty()) {
        int row = breeding_tree.front().first; //������ ������ ��
        int col = breeding_tree.front().second; //������ ������ ��

        breeding_tree.pop();

        for (int j = 0; j < 8; j++) {
            int nr = row + dr[j];
            int nc = col + dc[j];

            if (nr < 0 || nr >= n || nc < 0 || nc >= n) { ///�ùٸ� ��ǥ�� �ƴϸ�, (�� ������ �ƴϸ�)
                continue;
            }

            tree.push_front({ 1, nr, nc }); //���� ���� ����
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
 * [���� ����] - �ܼ� ���� ����
 * ��: �ϳ��� ĭ���� ���̰� � �������� �ڽ��� ���̸�ŭ ����� �԰�, ���̰� 1 ������
 *    �� ĭ�� ����� ������ �ڽ��� ���̸�ŭ ����� �� �Դ� ������ ��� ����
 * ����: ���� ���� ������ ������� ����. ���� �������� ���̸� 2�� ���� ���� ������� �߰� (�Ҽ��� ����)
 * ����: ���̰� 5�� ����� ������ ����. ������ 8�� ĭ�� ���̰� 1�� ������ ����
 * �ܿ�: �κ�(S2D2)�� ���� ���ƴٴϸ鼭 A[r][c]��ŭ �� ĭ�� ��� �߰�
 *
 * K���� ���� �� ���� ���� ����ִ� ������ ����
 *
 * [���� Ǯ��]
 * a: �κ�(S2D2)�� �ܿ￡ �ִ� ����� ��
 * land: ���� ���
 * breeding_tree: ���̰� 5�� ����� Ʈ�� (������ Ʈ��)
 * tree: ���� ���� ���� ����, ��, �� ����
 * -> deque �����̳ʸ� Ȱ���� ������ ������ �տ� �־��ָ� �Է� �Ŀ��� �����ؼ� ��� ����
 *
 * ������ ������ ������ ������ ����
 */

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int n, m, k, x, y, z;

    //�Է�
    cin >> n >> m >> k;
    matrix a(n, vector<int>(n, 0));
    matrix land(n, vector<int>(n, 5)); //ó�� ��� ��� ĭ�� 5
    queue<pair<int, int>> breeding_tree; //������ Ʈ��
    deque<tp> tree;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }

    while (m--) {
        cin >> x >> y >> z;
        tree.emplace_back(z, x - 1, y - 1); //(0, 0)���� �����ϵ��� �����ϱ����� 1�� ���� �ε����� ����
    }

    //����
    sort(tree.begin(), tree.end()); //� ���� ������ ����

    while (k--) {
        queue<tp> dead_tree = spring(land, tree, breeding_tree); //���� ������ ���� ����
        summer(dead_tree, land);
        fall(n, tree, breeding_tree);
        winter(n, a, land);
    }

    //���
    cout << tree.size();
    return 0;
}