#include <stdio.h>


int isBitree(const char* buf) {
	int count = 0;

	for (const char* p = buf; *p; p++) {
		if (*p == '(') {
			count = 0;  // 새 노드 시작 → 자식 수 초기화
		}
		else if (*p == ')') {
			if (count > 2) return 0; // 자식이 3개 이상이면 이진트리 아님
		}
		else if (*p == ' ') {
			continue;   // 공백 무시
		}
		else {
			// 노드 시작 부분에서만 자식 카운트
			if (*(p - 1) == ' ' || *(p - 1) == '(') {
				count++;
			}
		}
	}

	return 1; // 모든 노드가 자식 2 이하
}

int main() {
	char buf[1000];
	fgets(buf, sizeof(buf), stdin);

	if (isBitree(buf) == 1) {
		printf("true");
	}
	else{
		printf("false");
	}
	return 0;
}


//괄호 안에 있는 노드의 자식이 2개 이하인지 확인하는 함수