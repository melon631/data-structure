#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct treeNode {
    char data;
    struct treeNode* left;
    struct treeNode* right;
} treeNode;

treeNode* makeNode(char c) {
    treeNode* n = (treeNode*)malloc(sizeof(treeNode));
    n->data = c;
    n->left = n->right = NULL;
    return n;
}

/* simple stack for treeNode* */
#define STACK_MAX 1000
typedef struct {
    treeNode* data[STACK_MAX];
    int top;
} Stack;

void initStack(Stack* s) { s->top = -1; }
int isEmpty(Stack* s) { return s->top == -1; }
void push(Stack* s, treeNode* n) { if (s->top + 1 < STACK_MAX) s->data[++(s->top)] = n; }
treeNode* pop(Stack* s) { if (s->top == -1) return NULL; return s->data[(s->top)--]; }
treeNode* peek(Stack* s) { if (s->top == -1) return NULL; return s->data[s->top]; }

/* Parser:
   - 읽으면서 문자(영문자) 만나면 노드 생성
   - 스택의 top이 있으면 top->left가 비어있으면 left에 붙이고, 아니면 right에 붙임.
   - 생성한 노드 뒤에 '(' 가 오면 그 노드를 스택에 push (즉 자식이 생김을 의미)
   - ')'를 만나면 스택에서 pop
   이 방식은 괄호/공백으로 구분된 단일 문자 노드 입력에 대해, 예시에서 기대하신 이진트리 구조를 만듭니다.
*/
treeNode* parseBinaryFromParens(const char* s) {
    int i = 0;
    int n = (int)strlen(s);
    Stack st; initStack(&st);
    treeNode* root = NULL;

    while (i < n) {
        if (s[i] == '(') { i++; continue; }
        if (isspace((unsigned char)s[i])) { i++; continue; }

        if (isalpha((unsigned char)s[i])) {
            char ch = s[i++];
            treeNode* node = makeNode(ch);
            if (!root) root = node;

            treeNode* parent = peek(&st);
            if (parent) {
                if (!parent->left) parent->left = node;
                else if (!parent->right) parent->right = node;
                else {
                    /* 드물게 더 상위 부모 중 빈칸을 찾아 붙임 (안전장치) */
                    int k = st.top - 1;
                    while (k >= 0 && st.data[k]->right) k--;
                    if (k >= 0) st.data[k]->right = node;
                }
            }

            /* lookahead: 다음 non-space 문자가 '('이면 이 노드는 자식이 있으므로 push */
            int j = i;
            while (j < n && isspace((unsigned char)s[j])) j++;
            if (j < n && s[j] == '(') {
                push(&st, node);
            }
            continue;
        }

        if (s[i] == ')') {
            /* 닫는 괄호 -> 현재 그룹(스택 최상위) 끝 */
            if (!isEmpty(&st)) pop(&st);
            i++;
            continue;
        }

        /* 그 외 문자: 무시 */
        i++;
    }

    return root;
}

/* 반복(스택) 기반 순회들 */

// 전위 반복
void preorderIter(treeNode* root) {
    if (!root) { printf("\n"); return; }
    Stack s; initStack(&s);
    push(&s, root);
    int first = 1;
    while (!isEmpty(&s)) {
        treeNode* node = pop(&s);
        if (!first) printf(" ");
        printf("%c", node->data);
        first = 0;
        if (node->right) push(&s, node->right);
        if (node->left) push(&s, node->left);
    }
    printf("\n");
}

// 중위 반복
void inorderIter(treeNode* root) {
    Stack s; initStack(&s);
    treeNode* curr = root;
    int first = 1;
    while (curr || !isEmpty(&s)) {
        while (curr) {
            push(&s, curr);
            curr = curr->left;
        }
        curr = pop(&s);
        if (!first) printf(" ");
        printf("%c", curr->data);
        first = 0;
        curr = curr->right;
    }
    printf("\n");
}

// 후위 반복 (두 스택 방식)
void postorderIter(treeNode* root) {
    if (!root) { printf("\n"); return; }
    Stack s1, s2; initStack(&s1); initStack(&s2);
    push(&s1, root);
    while (!isEmpty(&s1)) {
        treeNode* node = pop(&s1);
        push(&s2, node);
        if (node->left) push(&s1, node->left);
        if (node->right) push(&s1, node->right);
    }
    int first = 1;
    while (!isEmpty(&s2)) {
        treeNode* node = pop(&s2);
        if (!first) printf(" ");
        printf("%c", node->data);
        first = 0;
    }
    printf("\n");
}

int main(void) {
    char input[2000];
    if (scanf("%1999[^\n]", input) != 1) return 0;

    treeNode* root = parseBinaryFromParens(input);

    preorderIter(root);
    inorderIter(root);
    postorderIter(root);

    return 0;
}