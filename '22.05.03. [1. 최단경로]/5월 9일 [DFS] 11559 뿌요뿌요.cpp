// BOJ 11559 Puyo Puyo �ѿ�ѿ�


/* ���� �з�: DFS(BFS) */

/* ���� ����:
* �ִ��� ���Ӱ� ����, BOJ 2638 ġ����̱� ����(���� ����)�� ����.
* 5���� ������ �ѿ䰡 ���� �����ΰ� �����¿�� 4���̻� ���̸� ����. & �ؿ��� ��������� �߷¿� ���� ������.
* ���ÿ� ���������� ������ ����Ƚ�� +1
* �� ó�� �ѿ��� ���°� 2�����迭�� �־����� ��, ����� ���Ⱑ �Ͼ�� ����ϱ�
*/

/* ���� Ǯ��:
* STEP1. �����¿�� ������ ���� ��� by DFS
* STEP2. �� ã������ �ѹ��� ���ְ�, ����Ƚ��+1
* STEP3. �߷� ������Ѽ� ��ĭ���� �Ʒ��� �ѿ� ������
* STEP1,2,3 �ݺ�.
*/

/* ������� �� & �ٽ� �ѹ� ���캼 �κ�:
* ������ ���� ��츦 ����� flag �ʿ�
*/

#include <iostream>
#include <cstring> //memset�Լ� ������ <string>�ƴϰ� <cstring>�̳� <string.h>�ʿ�
#include <vector>
using namespace std;

char map[12][6]; //�ѿ�ѿ� ������
bool visited[12][6];
int dx[] = { -1, 0, 1, 0 };
int dy[] = { 0, -1, 0, 1 };
vector<pair<int, int>> pop_temp; //�ش� �ݺ����� ���� �ѿ���� ����. �Ŀ� �ѹ��� ��Ʈ��.
vector<pair<int, int>> pop;
int cnt; //���ִ� ���� ���� �ѿ� ����

void dfs(int x, int y) {
	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];

		if (nx < 0 || ny < 0 || nx >= 12 || ny >= 6) continue; //�ùٸ��� ���� ��ǥ (������ ��) ������ ���
		if (map[nx][ny] == '.') continue; //�ѿ� ���� ���
		if (visited[nx][ny] == true) continue; //�̹� �湮�� ���
		if (map[x][y] != map[nx][ny]) continue; //������ �ٸ� ���

		cnt++;
		visited[nx][ny] = true; //�湮���� ǥ��
		pop_temp.push_back(make_pair(nx, ny)); //���� �ѿ� ��Ͽ� ����
		dfs(nx, ny); //����Լ� ȣ��
	}
}

int main(void) {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	for (int i = 0; i < 12; i++)
		for (int j = 0; j < 6; j++)
			cin >> map[i][j];

	int ans = 0;

	while (true) {
		//�ʱ�ȭ
		bool flag = false;
		memset(visited, false, sizeof(visited));
		pop_temp.clear();

		//STEP1.�����¿�� ������ ���� ��� by DFS
		for (int i = 0; i < 12; i++) {
			for (int j = 0; j < 6; j++) {

				if (map[i][j] != '.' && visited[i][j] == false) {
					cnt = 1;
					visited[i][j] = true; //�湮���� ǥ��
					pop_temp.push_back(make_pair(i, j)); //���� �ѿ� ��Ͽ� ����
					dfs(i, j); //����Լ� ȣ��

					if (cnt >= 4) {
						flag = true;
						for (int k = 0; k < pop_temp.size(); k++) //pop_temp���� pop�� �Ű��ֱ�
							pop.push_back(pop_temp[k]);
					}
					pop_temp.clear();
				}
			}
		}

		//STEP2.�� ã������ �ѹ��� ���ְ�, ����Ƚ�� + 1
		for (int i = 0; i < pop.size(); i++) {
			int x = pop[i].first;
			int y = pop[i].second;

			map[x][y] = '.';
		}

		if (flag == true) ans++;
		else break;

		pop.clear(); //�̰� ���� ��� Ʋ�Ƚ��ϴ� ������.

		//STEP3. �߷� ������Ѽ� ��ĭ���� �Ʒ��� �ѿ� ������
		for (int i = 0; i < 6; i++) {
			for (int j = 10; j >= 0; j--) {
				for (int k = 11; k > j; k--) {
					if (map[j][i] != '.' && map[k][i] == '.') {
						map[k][i] = map[j][i];
						map[j][i] = '.';
						break;
					}
				}
			}
		}
	}

	cout << ans << '\n';

	return 0;
}