// 1_1.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include "bits/stdc++.h"

using namespace std;
int n;
int main() {
    cin >> n;
    int a = 0;
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            a += i + j;
            cnt++;
        }
    }
    cout << a << '\n';
    cout << "cnt:" << cnt << '\n';
    return 0;
}
