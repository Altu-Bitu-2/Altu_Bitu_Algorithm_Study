// BOJ 18111 마인크래프트

/* 문제 분류: brute force */

/* 문제 설명:
* 마인크래프트, 땅 고르기 문제
* (i,j) 위치의 땅제거 = 2초, 인벤토리에서 꺼내서 땅쌓기 = 1초
* 땅 고를 수 있는 최소시간과 그때의 땅 높이
*/

/* 문제 풀이:
* 최소높이~최대높이까지 살펴보며, 해당 높이로 맞출때 걸리는 시간을 계산해서 최소시간 갱신.
*/

/* 어려웠던 점 & 다시 한번 살펴볼 부분:
*/

#include <iostream>
#include <limits.h> //INT_MAX사용 위한 헤더
#include <vector>
using namespace std;

int main(void) {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

	int n, m, b;
	int map[500][500];
	int min_time = INT_MAX;
	int min_height;

	//입력
	cin >> n >> m >> b;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			cin >> map[i][j];

	//brute force
	for (int h = 0; h <= 256; h++) {
		int build = 0; //쌓을 개수
		int remove = 0; //제거할 개수

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				int diff = map[i][j] - h;
				if (diff > 0) remove += diff;
				else if (diff < 0) build -= diff;
			}
		}

		//제거할 개수 + 인벤토리에 남은 개수 >= 쌓을 개수 일때만 가능
		if (remove + b >= build) { 
			int time = remove * 2 + build;

			if (min_time >= time) { //최소시간 갱신
				min_time = time;
				min_height = h;
			}
		}
	}
	cout << min_time << ' ' << min_height << '\n';

	return 0;
}