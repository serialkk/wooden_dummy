#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <memory.h>
#include <stdlib.h>

#define LOCATION_A  "A"
#define LOCATION_B  "B"
#define LOCATION_C  "C"
/*
int func(int i) {
	if (i == 1)
		return 1;
	else
		//printf("recursive call\n");
		return i*func(i - 1);
}
void main() {
	int i = 4;
	printf("%d",func(i));
}
*/

/*
typedef struct _node {
	int num;
	struct _node* foward;
	struct _node* back;
}node;

void main() {
	node root;
	memset(&root,0,sizeof(node));

	root.num = 1;

	memset(&root, 0, sizeof(node));

}
*/
typedef struct _hanoi {
	int num;
	char loc;
}hanoi;

void main() {

	int i=0, stack = 4;

	hanoi* Hanoi_A = (hanoi*)malloc(sizeof(hanoi)*stack);
	hanoi* Hanoi_B = (hanoi*)malloc(sizeof(hanoi)*stack);
	hanoi* Hanoi_C = (hanoi*)malloc(sizeof(hanoi)*stack);

	memset(Hanoi_A, 0, sizeof(hanoi)*stack);
	memset(Hanoi_B, 0, sizeof(hanoi)*stack);
	memset(Hanoi_C, 0, sizeof(hanoi)*stack);

	for (i = 0; i < stack;i++){
		Hanoi_A[i].loc=65;
		Hanoi_A[i].num=i+1;
	}

	for (i = 0; i < stack; i++) {
		printf("%c %d\n", Hanoi_A[i].loc, Hanoi_A[i].num);
	}

	/*
	node root;
	memset(&root, 0, sizeof(node));

	root.num = 1;

	memset(&root, 0, sizeof(node));
	*/

}



/*                                                           */
/*  TREE1.C  :   Make parse tree & traverse                  */
/*                                                           */
/*                  Programmed By Lee jaekyu                 */
/*                                                           */
//
//#include <stdio.h>
//#include <stdlib.h>
//
//typedef struct _node
//{
//	int key;
//	struct _node *left;
//	struct _node *right;
//} node;
//
//node *head, *tail;
//
//#define MAX  100
//
//node *stack[MAX];
//int top;
//
//void init_stack(void)
//{
//	top = -1;
//}
//
//node *push(node *t)
//{
//	if (top >= MAX - 1)
//	{
//		printf("\n    Stack overflow.");
//		return NULL;
//	}
//	stack[++top] = t;
//	return t;
//}
//
//node *pop(void)
//{
//	if (top < 0)
//	{
//		printf("\n    Stack underflow.");
//		return NULL;
//	}
//	return stack[top--];
//}
//
//int is_stack_empty(void)
//{
//	return (top == -1);
//}
//
//node *queue[MAX];
//int front, rear;
//
//void init_queue(void)
//{
//	front = rear = 0;
//}
//
//node *put(node *k)
//{
//	if ((rear + 1) % MAX == front)   /* queue is full */
//	{
//		printf("\n    Queue overflow.");
//		return NULL;
//	}
//	queue[rear] = k;
//	rear = ++rear % MAX;
//	return k;
//}
//
//node *get(void)
//{
//	node *i;
//	if (front == rear)   /* queue is empty */
//	{
//		printf("\n    Queue underflow.");
//		return NULL;
//	}
//	i = queue[front];
//	front = ++front % MAX;
//	return i;
//}
//
//int is_queue_empty(void)
//{
//	return (front == rear);
//}
//
//void init_tree(void)
//{
//	head = (node*)malloc(sizeof(node));
//	tail = (node*)malloc(sizeof(node));
//	head->left = tail;
//	head->right = tail;
//	tail->left = tail;
//	tail->right = tail;
//}
//
//int is_operator(int k)
//{
//	return (k == '+' || k == '-' || k == '*' || k == '/');
//}
//
//node *make_parse_tree(char *p)
//{
//	node *t;
//	while (*p)
//	{
//		while (*p == ' ')
//			p++;
//		t = (node*)malloc(sizeof(node));
//		t->key = *p;
//		t->left = tail;
//		t->right = tail;
//		if (is_operator(*p))
//		{
//			t->right = pop();
//			t->left = pop();
//		}
//		push(t);
//		p++;
//	}
//	return pop();
//}
//
//int is_legal(char *s)
//{
//	int f = 0;
//	while (*s)
//	{
//		while (*s == ' ')   /* remove space */
//			s++;
//		if (is_operator(*s))
//			f--;
//		else
//			f++;
//		if (f < 1)  break; /* check situation like A + B */
//		s++;
//	}
//	return (f == 1);   /* legal if valuable - operator == 1 */
//}
//
//void visit(node *t)
//{
//	printf("%c  ", t->key);
//}
//
//void preorder_traverse(node *t)
//{
//	if (t != tail)
//	{
//		visit(t);
//		preorder_traverse(t->left);
//		preorder_traverse(t->right);
//	}
//}
//
//void inorder_traverse(node *t)
//{
//	if (t != tail)
//	{
//		inorder_traverse(t->left);
//		visit(t);
//		inorder_traverse(t->right);
//	}
//}
//
//void postorder_traverse(node *t)
//{
//	if (t != tail)
//	{
//		postorder_traverse(t->left);
//		postorder_traverse(t->right);
//		visit(t);
//	}
//}
//
//void levelorder_traverse(node *t)
//{
//	put(t);
//	while (!is_queue_empty())
//	{
//		t = get();
//		visit(t);
//		if (t->left != tail)
//			put(t->left);
//		if (t->right != tail)
//			put(t->right);
//	}
//}
//
//void main(void)
//{
//	char post[256];
//	init_stack();
//	init_queue();
//	init_tree();
//	while (1)
//	{
//		printf("\n\nInput Postfix expression -> ");
//		scanf("%s",post);
//		if (*post == NULL)
//		{
//			printf("\n Program ends...");
//			exit(0);
//		}
//		if (!is_legal(post))
//		{
//			printf("\nExpression is not legal.");
//			continue;
//		}
//
//		head->right = make_parse_tree(post);
//
//		printf("\nPreorder   traverse -> ");
//		preorder_traverse(head->right);
//
//		printf("\nInorder    traverse -> ");
//		inorder_traverse(head->right);
//
//		printf("\nPostorder  traverse -> ");
//		postorder_traverse(head->right);
//
//		printf("\nLevelorder traverse -> ");
//		levelorder_traverse(head->right);
//	}
//}
//
