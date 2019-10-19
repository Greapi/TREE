#include <stdio.h>
#include<stdlib.h>
#define MaxSize 20
//Pre-���������ʾ��
typedef struct tree
{
	int date;
	tree* LChild, * RChild;
	int ltag=0, rtag=0;
}Tree;

//pre-����һ������������
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


//�㷨
//1.ǰ-��-�����б���
void travel(Tree* tr)
{
	if (tr != NULL)
	{
		//ǰ�����
		travel(tr->LChild);
		//�������
		travel(tr->RChild);
		printf("%d", tr->date);//�������
	}
}

//2.�ǵݹ���ʽǰ��-����
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

//3.�ǵݹ���ʽ�������    
//��-��-�����γɵ����������������Ϊ�������
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

//4.�������
void cTravel(Tree* head)
{
	if (head == NULL) return;
	Tree* tmp;
	Tree* line[MaxSize]; int front = 0; int rear = 0;//����һ��ѭ������
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

//5.����
void Find(Tree* tr, Tree*& q, int key)
{
	if (tr == NULL)return;
	if (tr->date == key)
		q = tr;
	else
	{
		//q�ĳ�ʼֵΪNULL
		Find(tr->LChild, q, key);
		if (q == NULL)
			Find(tr->RChild, q, key);
	}
}

//6.����������
//��ʼpre=null
void treTree(Tree*tr,Tree*&pre)
{

	if (tr != NULL )
	{
		treTree(tr->LChild, pre);
		if (tr->LChild == NULL)					 //�����������
		{
			tr->LChild = pre;
			tr->ltag = 1;
		}
		if (pre != NULL && pre->RChild == NULL)	//pre���Ҷ�����������pre != NULL�Ƿ�ֹ���Ҹ��ڵ���Ҷ����Ǳ���
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

//7.���������������ı���
//�ҵ�����ߵĽڵ㣬�˽ڵ�Ϊ�������׽ڵ�
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
		printf("%d",p->date);//��ӡ
}

//8.��ӡҶ�ӽڵ㵽���ڵ�·��
Tree* Stack[MaxSize]; int top = -1;//ջ�д����˿�ʼ�ڵ㵽Ŀǰ�ڵ��·��
void printPath(Tree* tr)
{
	if (tr != NULL)
	{
		Stack[++top] = tr;
		if (tr->LChild == NULL && tr->RChild == NULL)//ȡ�ü��Ƕ�ÿ���ڵ��·����ӡ
		{
			for (int i = 0; i <= top; i++)
			{
				printf("%d", Stack[i]->date);
			}
			printf("\n");
			
		}		
		printPath(tr->LChild);
		printPath(tr->RChild);
		--top;					//������������ɣ���һ����������ǰ�ڵ�����ֵܣ�����ǰ�ڵ㲻�����ֵܵ�·���ϣ��ʴ�ջ�е���
	}
}

//����һ��������
int main()
{
	Tree* head = (tree*)malloc(sizeof(Tree)); Tree* tmp=NULL;
	creatTree(head);
	clueTree(head);
	travelS(head);
	return 0;
}


