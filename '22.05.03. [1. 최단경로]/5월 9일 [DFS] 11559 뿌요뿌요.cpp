// BOJ 11559 Puyo Puyo 뿌요뿌요


/* 문제 분류: DFS(BFS) */

/* 문제 설명:
* 애니팡 게임과 유사, BOJ 2638 치즈녹이기 문제(이퍼 기출)와 유사.
* 5가지 색상의 뿌요가 같은 색상인게 상하좌우로 4개이상 모이면 터짐. & 밑에가 비어있으면 중력에 의해 내려옴.
* 동시에 여러군데서 터져도 연쇄횟수 +1
* 맨 처음 뿌요의 상태가 2차원배열로 주어졌을 때, 몇번의 연쇄가 일어날지 계산하기
*/

/* 문제 풀이:
* STEP1. 상하좌우로 없앨지 말지 기록 by DFS
* STEP2. 다 찾았으면 한번에 없애고, 연쇄횟수+1
* STEP3. 중력 적용시켜서 빈칸없게 아래로 뿌요 내리기
* STEP1,2,3 반복.
*/

/* 어려웠던 점 & 다시 한번 살펴볼 부분:
* 터질게 없을 경우를 대비해 flag 필요
*/

#include <iostream>
#include <cstring> //memset함수 쓰려면 <string>아니고 <cstring>이나 <string.h>필요
#include <vector>
using namespace std;

char map[12][6]; //뿌요뿌요 게임판
bool visited[12][6];
int dx[] = { -1, 0, 1, 0 };
int dy[] = { 0, -1, 0, 1 };
vector<pair<int, int>> pop_temp; //해당 반복에서 터질 뿌요들을 저장. 후에 한번에 터트림.
vector<pair<int, int>> pop;
int cnt; //모여있는 같은 색상 뿌요 개수

void dfs(int x, int y) {
	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];

		if (nx < 0 || ny < 0 || nx >= 12 || ny >= 6) continue; //올바르지 못한 좌표 (게임판 밖) 접근한 경우
		if (map[nx][ny] == '.') continue; //뿌요 없는 경우
		if (visited[nx][ny] == true) continue; //이미 방문한 경우
		if (map[x][y] != map[nx][ny]) continue; //색상이 다른 경우

		cnt++;
		visited[nx][ny] = true; //방문함을 표시
		pop_temp.push_back(make_pair(nx, ny)); //터질 뿌요 목록에 저장
		dfs(nx, ny); //재귀함수 호출
	}
}

int main(void) {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	for (int i = 0; i < 12; i++)
		for (int j = 0; j < 6; j++)
			cin >> map[i][j];

	int ans = 0;

	while (true) {
		//초기화
		bool flag = false;
		memset(visited, false, sizeof(visited));
		pop_temp.clear();

		//STEP1.상하좌우로 없앨지 말지 기록 by DFS
		for (int i = 0; i < 12; i++) {
			for (int j = 0; j < 6; j++) {

				if (map[i][j] != '.' && visited[i][j] == false) {
					cnt = 1;
					visited[i][j] = true; //방문함을 표시
					pop_temp.push_back(make_pair(i, j)); //터질 뿌요 목록에 저장
					dfs(i, j); //재귀함수 호출

					if (cnt >= 4) {
						flag = true;
						for (int k = 0; k < pop_temp.size(); k++) //pop_temp꺼를 pop로 옮겨주기
							pop.push_back(pop_temp[k]);
					}
					pop_temp.clear();
				}
			}
		}

		//STEP2.다 찾았으면 한번에 없애고, 연쇄횟수 + 1
		for (int i = 0; i < pop.size(); i++) {
			int x = pop[i].first;
			int y = pop[i].second;

			map[x][y] = '.';
		}

		if (flag == true) ans++;
		else break;

		pop.clear(); //이거 한줄 없어서 틀렸습니다 떴었음.

		//STEP3. 중력 적용시켜서 빈칸없게 아래로 뿌요 내리기
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