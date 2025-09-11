#include <stdio.h>


int errorflag = 0;	// 괄호 구조 오류 발생 여부
int biflag = 1;		// 이지느리 조건 만족 여부
const char* p;		// 현재 문자열 위치를 가르키는 포인터

void parsetree(void) {
	int childcount = 0;  // 자식 노드 개수		
	
	while (*p == ' ') p++;   //공백 건너뛰기

	if (*p != '(') {errorflag = 1; return;}		// 현재 문자가 '('가 아니면
												// errorflag를 1로 설정
												// 함수 종료
	p++;	// 포인터를 다음 문자로 이동
	
	while (*p == ' ') p++;   //공백 건너뛰기

	if(*p== ')') {p++; return;}		// 현재 문자가 ')'이면
									// 포인터를 다음 문자로 이동
									// 함수 종료 (빈 노드)

	if (!((*p >= 'A' && *p <= 'Z') || (*p >= 'a' && *p <= 'z'))) {
		errorflag = 1;
		return;
	}					// 영문자가 아니면 1로 설정
						 // 함수 종료						

	p++;	// 포인터를 다음 문자로 이동

	while (*p == ' ') p++;   //공백 건너뛰기

	while (1) {
		while (*p == ' ') p++;  // 공백 건너뛰기

		if (*p == '(') {  // 자식 노드가 '('로 시작하면
			childcount++;
			if (childcount > 2) {
				biflag = 0;
			}
			parsetree();
		}
		else if ((*p >= 'A' && *p <= 'Z') || (*p >= 'a' && *p <= 'z')) {  
			// 자식 노드가 영문자일 때
			// 여러 문자가 연속될 수 있으니 반복문으로 처리
			while ((*p >= 'A' && *p <= 'Z') || (*p >= 'a' && *p <= 'z')) {
				childcount++;
				if (childcount > 2) {
					biflag = 0;
				}
				p++;  // 문자 하나씩 처리
				while (*p == ' ') p++;  // 문자 사이 공백 건너뛰기
			}
		}
		else {
			break;
		}
	}
}

int main(void) {
	printf("input: ");

	char tree[1000];		// tree 배열 1000칸 선언
	// fgets(문자열 저장 버퍼, 읽어올 최대 문자 수, 읽어올 파일 포인터) 
	if (!fgets(tree, sizeof(tree), stdin)) {	//stdin > standard input(키보드 입력)
		printf("ERROR\n");
		return 0;
		// fgets()가 null을 반환시, !null -> true가 되어 error 출력 후 종료
	}
	// 입력 문자열 끝의 개행 제거
	size_t len = strlen(tree);
	if (len > 0 && tree[len - 1] == '\n') {
		tree[len - 1] = '\0';
	}

	printf("\n");
	printf("output: ");	// fgets()가 false가 되어 tree 출력

	p = tree;         // 포인터 초기화
	errorflag = 0;
	biflag = 1;

	parsetree();      // 재귀적으로 트리 검사

	// 2. 결과 출력
	if (errorflag) {
		printf("ERROR\n");
	}
	else if (biflag) {
		printf("TRUE\n");
	}
	else {
		printf("FALSE\n");
	}

	return 0;
}