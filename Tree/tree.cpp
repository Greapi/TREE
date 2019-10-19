#include <stdio.h>
#include<stdlib.h>
#define MaxSize 20
//Pre-树的链表表示法
typedef struct tree
{
	int date;
	tree* LChild, * RChild;
	int ltag=0, rtag=0;
}Tree;

//pre-购件一个二叉排序树
void setZero(Tree* tr)
{
	if (tr != NULL)
	{
		tr->ltag = tr->rtag = 0;
		setZero(tr->LChild);
		setZero(tr->RChild);
	}
}
void creatTree(Tree* head)
{
	Tree* t1 = (tree*)malloc(sizeof(Tree));
	Tree* t2 = (tree*)malloc(sizeof(Tree));
	Tree* t3 = (tree*)malloc(sizeof(Tree));
	Tree* t4 = (tree*)malloc(sizeof(Tree));
	Tree* t5 = (tree*)malloc(sizeof(Tree));
	Tree* t6 = (tree*)malloc(sizeof(Tree));
	Tree* t7 = (tree*)malloc(sizeof(Tree));
	head->LChild = t1;
	head->RChild = t2;
	head->date = 0;
	t1->LChild = t3;
	t1->RChild = t4;
	t1->date = 1;
	t2->LChild = t5;
	t2->RChild = NULL;
	t2->date = 2;
	t3->LChild = t3->RChild = NULL;
	t3->date = 3;
	t4->LChild = t6;
	t4->RChild = t7;
	t4->date = 4;
	t5->LChild = t5->RChild = NULL;
	t5->date = 5;
	t6->LChild = t6->RChild = NULL;
	t6->date = 6;
	t7->LChild = t7->RChild = NULL;
	t7->date = 7;
	setZero(head);
}


//算法
//1.前-中-后序列遍历
void travel(Tree* tr)
{
	if (tr != NULL)
	{
		//前序遍历
		travel(tr->LChild);
		//中序遍历
		travel(tr->RChild);
		printf("%d", tr->date);//后序遍历
	}
}

//2.非递归形式前序-中序
void Pretreval(Tree* head)
{
	Tree* Stack[MaxSize]; int top = -1;
	Tree* tmp = head;
	while (top != -1 || tmp!=NULL)
	{
		while (tmp != NULL )
		{
			printf("%d", tmp->date);
			Stack[++top] = tmp;
			tmp = tmp->LChild;
		}
		if (top != -1)
		{
			tmp = Stack[top--];
			tmp = tmp->RChild;
		}
	}
}

//3.非递归形式后序遍历    
//中-右-左所形成的先序遍历，其逆序即为后序遍历
void lastTravel(Tree* head)
{
	Tree* Stack1[MaxSize]; int top1 = -1;
	Tree* Stack2[MaxSize]; int top2 = -1;
	Tree* tmp=head;
	while (top1 != -1 || tmp != NULL)
	{
		while (tmp != NULL)
		{
			Stack2[++top2] = tmp;
			Stack1[++top1] = tmp;
			tmp = tmp->LChild;
		}
		if (top1 != -1)
		{
			tmp = Stack1[top1--]->LChild;
		}
	}
	while (top2 != -1)
		printf("%d", Stack2[top2--]->date);
}

//4.层序遍历
void cTravel(Tree* head)
{
	if (head == NULL) return;
	Tree* tmp;
	Tree* line[MaxSize]; int front = 0; int rear = 0;//创建一个循环队列
	line[++front] = head;
	
	while (front != rear)
	{
		rear = (++rear) % MaxSize;
		tmp = line[rear];
		printf("%d", tmp->date);
		if (tmp->LChild != NULL)
		{
			front = (++front) % MaxSize;
			line[front] = tmp->LChild;
		}
			
		if (tmp->RChild != NULL)
		{
			front = (++front) % MaxSize;
			line[front] = tmp->RChild;
		}

	}
}

//5.查找
void Find(Tree* tr, Tree*& q, int key)
{
	if (tr == NULL)return;
	if (tr->date == key)
		q = tr;
	else
	{
		//q的初始值为NULL
		Find(tr->LChild, q, key);
		if (q == NULL)
			Find(tr->RChild, q, key);
	}
}

//6.中序线索化
//初始pre=null
void treTree(Tree*tr,Tree*&pre)
{

	if (tr != NULL )
	{
		treTree(tr->LChild, pre);
		if (tr->LChild == NULL)					 //左儿子线索化
		{
			tr->LChild = pre;
			tr->ltag = 1;
		}
		if (pre != NULL && pre->RChild == NULL)	//pre的右儿子线索化，pre != NULL是防止查找根节点的右儿子是报错
		{
			pre->RChild = tr;
			pre->rtag = 1;
		}
		pre = tr;
		treTree(tr->RChild, pre);				//treTree(tr->RChild, tr);
	}
	
}

void clueTree(Tree*tr)
{
	Tree* pre = NULL;
	treTree(tr, pre);
	//pre->RChild = NULL;
	//pre->rtag = 0;
}

//7.中序线索线索树的遍历
//找到最左边的节点，此节点为子树的首节点
Tree* Firstnode(Tree* tr)
{
	while (tr->ltag == 0)
		tr = tr->LChild;
	return tr;
}
Tree* Next(Tree* tr)
{
	if (tr->rtag == 0 && tr->RChild!=NULL)
		return Firstnode(tr->RChild);
	return tr->RChild;
}
void travelS(Tree* tr)
{
	for (Tree* p = Firstnode(tr); p != NULL; p = Next(p))
		printf("%d",p->date);//打印
}

//8.打印叶子节点到根节点路径
Tree* Stack[MaxSize]; int top = -1;//栈中储存了开始节点到目前节点的路径
void printPath(Tree* tr)
{
	if (tr != NULL)
	{
		Stack[++top] = tr;
		if (tr->LChild == NULL && tr->RChild == NULL)//取得即是对每个节点的路径打印
		{
			for (int i = 0; i <= top; i++)
			{
				printf("%d", Stack[i]->date);
			}
			printf("\n");
			
		}		
		printPath(tr->LChild);
		printPath(tr->RChild);
		--top;					//当左右子树完成，下一次则会遍历当前节点的右兄弟，而当前节点不再右兄弟的路径上，故从栈中弹出
	}
}

//这是一个主程序
int main()
{
	Tree* head = (tree*)malloc(sizeof(Tree)); Tree* tmp=NULL;
	creatTree(head);
	clueTree(head);
	travelS(head);
	return 0;
}


