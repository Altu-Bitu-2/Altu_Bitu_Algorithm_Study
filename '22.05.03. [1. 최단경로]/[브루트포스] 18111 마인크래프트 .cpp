// BOJ 18111 ����ũ����Ʈ

/* ���� �з�: brute force */

/* ���� ����:
* ����ũ����Ʈ, �� ���� ����
* (i,j) ��ġ�� ������ = 2��, �κ��丮���� ������ ���ױ� = 1��
* �� �� �� �ִ� �ּҽð��� �׶��� �� ����
*/

/* ���� Ǯ��:
* �ּҳ���~�ִ���̱��� ���캸��, �ش� ���̷� ���⶧ �ɸ��� �ð��� ����ؼ� �ּҽð� ����.
*/

/* ������� �� & �ٽ� �ѹ� ���캼 �κ�:
*/

#include <iostream>
#include <limits.h> //INT_MAX��� ���� ���
#include <vector>
using namespace std;

int main(void) {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int n, m, b;
	int map[500][500];
	int min_time = INT_MAX;
	int min_height;

	//�Է�
	cin >> n >> m >> b;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			cin >> map[i][j];

	//brute force
	for (int h = 0; h <= 256; h++) {
		int build = 0; //���� ����
		int remove = 0; //������ ����

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				int diff = map[i][j] - h;
				if (diff > 0) remove += diff;
				else if (diff < 0) build -= diff;
			}
		}

		//������ ���� + �κ��丮�� ���� ���� >= ���� ���� �϶��� ����
		if (remove + b >= build) { 
			int time = remove * 2 + build;

			if (min_time >= time) { //�ּҽð� ����
				min_time = time;
				min_height = h;
			}
		}
	}
	cout << min_time << ' ' << min_height << '\n';

	return 0;
}