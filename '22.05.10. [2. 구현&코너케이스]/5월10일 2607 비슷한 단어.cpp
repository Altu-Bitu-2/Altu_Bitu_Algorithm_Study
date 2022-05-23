// BOJ 2607 ����� �ܾ�

/* ���� �з�: [����] */

/* ���� ����:
* ���� ���ĺ� �빮�ڷ� �̷���� �� �ܾ ������ �� ���� ������ �����ϸ� ���� ������ ���´ٰ� ���Ѵ�.
* 1. �� ���� �ܾ ���� ������ ���ڷ� �̷���� �ִ�.
* 2. ���� ���ڴ� ���� ���� ��ŭ �ִ�
* 
* �� �ܾ ���� ������ ���� ���, �Ǵ� �� �ܾ�� �� ���ڸ� ���ϰų�, ���ų�, 
* �ϳ��� ���ڸ� �ٸ� ���ڷ� �ٲپ� ������ �� �ܾ�� ���� ������ ���� �Ǵ� ��쿡 �̵� �� �ܾ ���� ����� �ܾ��� �Ѵ�.
* 
* ���� �ٸ� �ܾ� �������� �־����� ��, ù��° �ܾ�� ����� �ܾ ��� ����� ����ض�.
*/

/* ���� Ǯ��: 
* ��� �ܾ ���� ���ĺ� �빮�ڷ� �ԷµǹǷ�, alpabet�迭�� ����.
* �� ���ĺ��� ���� �ε����� �����ϱ� ����. 
* A > 0, B > 1 ...
* ��, alpabet[word[i] - 'A'] �� ����. 
*/

/* ������� �� & �ٽ� �ѹ� ���캼 �κ�:
*/

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

void count(int a[26], string word) { //A���� Z���� ���ĺ��� �迭�� �����ϰ�, �ش� ���ĺ��� ����� �迭���� 1 ������Ų��.
	for (int i = 0; i < word.length(); i++) {
		a[word[i] - 'A']++;
	}
}

int solution(int n, vector<string>words) {
	int diff; //�� �ܾ�� ���ĺ� �ٸ� �� ����
	int freq_first[26] = { 0 }; //ù��° �ܾ�� ���ĺ� �󵵸� ������ �迭
	int freq_others[26] = { 0 }; //�ٸ� �ܾ�� ���ĺ� �󵵸� ������ �迭
	int answer = 0;

	count(freq_first, words[0]); //ù��° �ܾ��� ���ĺ� �� ���

	for (int i = 1; i < n; i++) {
		diff = 0;
		memset(freq_others, 0x0, 26 * sizeof(int));
		count(freq_others, words[i]); //�� �ܾ��� ���ĺ� �� ���

		for (int k = 0; k < 26; k++) //���ĺ� ���� ���̸� ���
			diff += abs(freq_others[k] - freq_first[k]);

		//����� �ܾ��� ���ǿ� ���� ����Ѵܾ����� �ƴ��� �Ǵ�.
		if (diff == 0 || diff == 1 || (diff == 2 && words[i].length() == words[0].length())) answer++;
	}

	return answer;
}

//test ����
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