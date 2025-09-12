#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct Node {
    char name;
    struct Node** children;
    int child_count;
} Node;

Node* create_node(char name) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->name = name;
    node->children = NULL;
    node->child_count = 0;
    return node;
}

void add_child(Node* parent, Node* child) {
    parent->child_count++;
    parent->children = (Node**)realloc(parent->children, sizeof(Node*) * parent->child_count);
    parent->children[parent->child_count - 1] = child;
}

typedef struct Stack {
    Node** data;
    int top;
} Stack;

void init_stack(Stack* s) {
    s->data = NULL;
    s->top = -1;
}

void push(Stack* s, Node* node) {
    s->top++;
    s->data = (Node**)realloc(s->data, sizeof(Node*) * (s->top + 1));
    s->data[s->top] = node;
}

Node* pop(Stack* s) {
    if (s->top == -1) return NULL;
    Node* node = s->data[s->top];
    s->top--;
    return node;
}

Node* peek(Stack* s) {
    if (s->top == -1) return NULL;
    return s->data[s->top];
}

int tree_height(Node* node) {
    if (!node) return -1;
    if (node->child_count == 0) return 0;

    int max_h = 0;
    for (int i = 0; i < node->child_count; i++) {
        int h = tree_height(node->children[i]);
        if (h > max_h) max_h = h;
    }
    return max_h + 1;
}

int count_nodes(Node* node) {
    if (!node) return 0;
    int total = 1;
    for (int i = 0; i < node->child_count; i++)
        total += count_nodes(node->children[i]);
    return total;
}

int count_leaves(Node* node) {
    if (!node) return 0;
    if (node->child_count == 0) return 1;

    int leaves = 0;
    for (int i = 0; i < node->child_count; i++)
        leaves += count_leaves(node->children[i]);
    return leaves;
}

// 수정된 parse_tree
Node* parse_tree(char* str) {
    Stack s;
    init_stack(&s);
    Node* root = NULL;

    for (int i = 0; str[i] != '\0'; i++) {
        char c = str[i];

        if (c == '(') {
            continue; // 그냥 다음 문자 준비
        }
        else if (c == ')') {
            pop(&s); // 현재 노드 종료
        }
        else if (isalpha(c)) {
            Node* node = create_node(c);
            if (!root) root = node; // 루트 설정
            if (peek(&s)) add_child(peek(&s), node); // 부모가 있으면 자식으로 추가

            // 다음 문자가 '('이면 자식이 존재하므로 스택에 push
            int j = i + 1;
            while (str[j] == ' ') j++; // 공백 건너뛰기
            if (str[j] == '(') {
                push(&s, node); // 자식이 있으므로 스택에 push
            }
        }
    }

    return root;
}

int main(void) {
    char input[1000];
    fgets(input, sizeof(input), stdin);s

    Node* root = parse_tree(input);

    int height = tree_height(root);
    int total_nodes = count_nodes(root);
    int leaf_nodes = count_leaves(root);

    printf("%d, %d, %d\n", height, total_nodes, leaf_nodes);

    return 0;
}
