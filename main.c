#include<stdio.h>
#include<stdbool.h>

typedef struct node node;
typedef struct linkedlist linkedlist;

struct node
{
	int val;
	node* next;
};

struct linkedlist
{
	node* head;
	int size;
};


linkedlist* create()
{
	return calloc(1, sizeof(linkedlist));
}

void add_to_head(linkedlist* list, int val)
{
	node* t = calloc(1, sizeof(node));
	if (!t)
		return;
	t->val = val;
	if (!list->head)
	{
		list->head = t;
		list->size++;
		return;
	}
	t->next = list->head;
	list->head = t;
	list->size++;
	return;
}

bool isEmpty(linkedlist* list)
{
	return !list->head;
}

int indexOf(linkedlist* list, int val)
{
	int idx = 0;
	if (isEmpty(list))
		return -1;
	node* t = list->head;
	while (t)
	{
		if (t->val == val)
		{
			break;
		}
		t = t->next;
		idx++;
	}
	if (!t)
		return -1;
	return idx;
}

void del_index_val(linkedlist* list, int index)//index从0开始
{
	if (isEmpty(list) || index >= list->size)
		return;
	if (index == 0)
	{
		node* t = list->head;
		list->head = t->next;
		free(t);
		list->size--;
	}
	else
	{
		node* pre = list->head;
		while (--index)
		{
			pre = pre->next;
		}
		node* t = pre->next;
		pre->next = t->next;
		free(t);
		list->size--;
	}
}


void add_index_val(linkedlist* list, int index, int val)//向指定位置添加结点
{
	if (index < 0)
		return;
	node* t = calloc(1, sizeof(node));
	if (!t)
		return;
	t->val = val;
	if (!index)//index==0
	{
		t->next = list->head;
		list->head = t;
		list->size++;
		return;
	}
	else
	{
		node* pre = list->head;
		while (--index)
		{
			pre = pre->next;
		}
		t->next = pre->next;
		pre->next = t;
		list->size++;
		return;
	}
}


void destroy(linkedlist* list)
{
	if (isEmpty(list))
		free(list);
	else
	{
		node* cur = list->head;
		while (cur)
		{
			node* t = cur;
			cur = cur->next;
			free(t);
		}
		free(list);
	}
}
/*
*	LRU:
*		a.存在
*		  删除该节点，在头结点前面添加
*		b.不存在
*		  缓存满了
*				删除尾结点
*				在头结点前面添加
*		  缓存没满
*				在头结点前面添加
*/

void LRU(linkedlist* list,int n,int val)//n为块大小，val为进入块的值
{
	int index = indexOf(list, val);
	if (index != -1)
	{
		del_index_val(list, index);
		add_to_head(list, val);
	}
	else
	{
		if (list->size == n)
		{
			del_index_val(list, n - 1);
			add_to_head(list, val);
		}
		else
		{
			add_to_head(list, val);
		}
	}
}



int main()
{
	int n = 5;
	linkedlist* list = create();
	printf("%d\n", isEmpty(list));
	add_to_head(list, 5);
	add_to_head(list, 4);
	//add_to_head(list, 3);
	//add_to_head(list, 2);
	//add_to_head(list, 1);

	//printf("%d\n", isEmpty(list));
	//printf("%d\n", indexOf(list, 5));
	//printf("%d\n", indexOf(list, 1));
	//printf("%d\n", indexOf(list, 0));
	//del_index_val(list, 0);
	//del_index_val(list, 0);
	//add_index_val(list, 2, 6);
	//add_index_val(list, 0, 9);
	//destroy(list);

	LRU(list, n, 6);
	LRU(list, n, 1);
	destroy(list);

}
