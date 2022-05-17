// BOJ 2607 비슷한 단어

/* 문제 분류: [구현] */

/* 문제 설명:
* 영문 알파벳 대문자로 이루어진 두 단어가 다음의 두 가지 조건을 만족하면 같은 구성을 갖는다고 말한다.
* 1. 두 개의 단어가 같은 종류의 문자로 이루어져 있다.
* 2. 같은 문자는 같은 개수 만큼 있다
* 
* 두 단어가 같은 구성을 갖는 경우, 또는 한 단어에서 한 문자를 더하거나, 빼거나, 
* 하나의 문자를 다른 문자로 바꾸어 나머지 한 단어와 같은 구성을 갖게 되는 경우에 이들 두 단어를 서로 비슷한 단어라고 한다.
* 
* 서로 다른 단어 여러개가 주어졌을 때, 첫번째 단어와 비슷한 단어가 모두 몇개인지 출력해라.
*/

/* 문제 풀이: 
* 모든 단어가 영문 알파벳 대문자로 입력되므로, alpabet배열로 구현.
* 각 알파벳에 대한 인덱스를 지정하기 편함. 
* A > 0, B > 1 ...
* 즉, alpabet[word[i] - 'A'] 에 접근. 
*/

/* 어려웠던 점 & 다시 한번 살펴볼 부분:
*/

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

void count(int a[26], string word) { //A부터 Z까지 알파벳을 배열로 생각하고, 해당 알파벳이 등장시 배열값을 1 증가시킨다.
	for (int i = 0; i < word.length(); i++) {
		a[word[i] - 'A']++;
	}
}

int solution(int n, vector<string>words) {
	int diff; //두 단어간의 알파벳 다른 것 개수
	int freq_first[26] = { 0 }; //첫번째 단어에서 알파벳 빈도를 저장할 배열
	int freq_others[26] = { 0 }; //다른 단어에서 알파벳 빈도를 저장할 배열
	int answer = 0;

	count(freq_first, words[0]); //첫번째 단어의 알파벳 빈도 계산

	for (int i = 1; i < n; i++) {
		diff = 0;
		memset(freq_others, 0x0, 26 * sizeof(int));
		count(freq_others, words[i]); //각 단어의 알파벳 빈도 계산

		for (int k = 0; k < 26; k++) //알파벳 개수 차이를 계산
			diff += abs(freq_others[k] - freq_first[k]);

		//비슷한 단어의 조건에 따라 비슷한단어인지 아닌지 판단.
		if (diff == 0 || diff == 1 || (diff == 2 && words[i].length() == words[0].length())) answer++;
	}

	return answer;
}

//test 메인
int main(void) {
	int n, i;

	int answer = 0;

	cin >> n;
	vector<string> words(n);
	for (i = 0; i < n; i++)
		cin >> words[i];

	answer = solution(n, words);
	cout << answer;
}