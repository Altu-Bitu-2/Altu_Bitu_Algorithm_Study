// BOJ 3613 Java vs C++

/* 문제 분류: 문자열, 구현 */

/* 문제 설명:
* 변수명에 대해,
* java형식 : 첫단어는 소문자, 다음단어는 첫 문자만 대문자.
* c++형식 : 변수명에 소문자만 사용. _로 구분.
*  C++형식의 변수명을 Java형식의 변수명으로, 또는 그 반대로 바꿔주는 프로그램을 만들어라.
*/

/* 문제 풀이:
* java형식인지, c++형식인지 알아내기.
* 각자 형식바꿔주기.
*/

/* 어려웠던 점 & 다시 한번 살펴볼 부분:
* 1. 대문자인지 확인하는 함수. int isupper(string). 대문자가 아니면 0.
* 
* 2. string::npos를 이용한 단어 유무 찾기
* 
*       str.find("key") == string::npos >> 있으면 true, 없으면 false가 됨.
* 
*    str.find() : 찾는 문자열의 첫번째 인덱스반환
*    string::npos : -1 값을 가지는 상수. find()함수에 의해 find되지 않으면 npos값이 리턴됨.
*/

#include <iostream>

using namespace std;

bool isCpp(string str) { //c++ 형식인가?
    for (int i = 0; i < str.size(); i++) {
        if (isupper(str[i])) { //대문자가 있으면 안됨
            return false;
        }
        if (str[i] == '_' && (i == 0 || i == str.size() - 1 || str[i - 1] == '_')) { //첫 or 마지막 글자가 '_' 또는 '_'가 연속 등장
            return false;
        }
    }
    return true;
}

bool isJava(string str) { //java 형식인가?
    return !isupper(str[0]) && str.find('_') == string::npos; //첫 글자가 대문자거나, '_'가 있으면 안됨
}

string toCpp(string str) { //java 형식을 c++로
    string result;

    for (int i = 0; i < str.size(); i++) { //for문이용해 한개씩 처리.
        if (isupper(str[i])) { //대문자라면 앞에 '_' 삽입
            result += '_';
        }

        result += tolower(str[i]); //소문자로 바꿔서 넣기
    }
    return result;
}

string toJava(string str) { //c++ 형식을 java로
    string result;

    for (int i = 0; i < str.size(); i++) {//for문이용해 한개씩 처리.
        if (str[i] == '_') { //'_' 라면 그 다음 글자를 대문자로 바꿔서 삽입
            result += toupper(str[i + 1]);
            i++;
            continue;
        }

        result += str[i]; //나머지 글자는 그냥 삽입
    }
    return result;
}

/**
 * [Java vs C++]
 *
 * 1. 입력으로 주어진 변수가 C++ 형식에도 맞고, JAVA 형식에도 맞을 수 있음 (ex. name)
 * 2. "Error!"인 경우 (C++)
 *    2-1. 언더바('_')로 시작하거나, 끝나는 변수
 *    2-2. 언더바('_')가 연속해서 등장하는 변수
 *    2-3. 대문자가 등장하는 변수
 * 3. "Error!"인 경우 (Java)
 *    3-1. 대문자로 시작하는 변수
 *    3-2. 언더바('_')가 등장하는 변수
 */

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    string str;

    cin >> str;
    bool is_cpp = isCpp(str);
    bool is_java = isJava(str);

    if (is_cpp && is_java) { //두 형식에 모두 부합하면 그냥 출력
        cout << str;
    }
    else if (is_cpp) { //c++ 형식이라면 java로 바꿔서 출력
        cout << toJava(str);
    }
    else if (is_java) { //java 형식이라면 c++로 바꿔서 출력
        cout << toCpp(str);
    }
    else { //둘 다 아니라면 에러
        cout << "Error!";
    }
    return 0;
}