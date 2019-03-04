#include "stdio.h"
#include "stdlib.h"
#include <vector>

using namespace std;

typedef struct treeData
{
	char data;
	bool color;//(0:black,1:red)
	treeData* parent;
	treeData* lChild;
	treeData* rChild;
}treeData,*treeNode;

void left_rotate(treeNode* T,treeNode x);
void right_rotate(treeNode* T,treeNode x);
void insert_node(treeNode* T,char c);
void insert_fixup(treeNode* T,treeNode z);
void build_tree(treeNode* T);
void delet_node(treeNode* T,char data);
void delete_node_fixup(treeNode *T,treeNode x);
void tree_printf(treeNode *T);

void left_rotate(treeNode* T,treeNode x)
{
	printf("begin left_rotate\n");
	if (!T || !*T || !x || !x->rChild)
	{
		return;
	}
	treeNode y = x->rChild;
	x->rChild = y->lChild;
	if (y->lChild != NULL)
	{
		y->lChild->parent = x;
	}
	y->lChild = x;
	y->parent = x->parent;
	if (x->parent == NULL)
	{
		*T = y;
	}
	else if (x == x->parent->lChild)
	{
		x->parent->lChild = y;
	}
	else
	{
		x->parent->rChild = y;
	}
	x->parent = y;
	printf("end left_rotate\n");
}

void right_rotate(treeNode* T,treeNode x)
{
	printf("begin right_rotate\n");
	if (!T || !*T || !x || !x->lChild)
	{
		return;
	}
	treeNode y = x->lChild;
	x->lChild = y->rChild;
	if (y->rChild != NULL)
	{
		y->rChild->parent = x;
	}
	y->rChild = x;
	y->parent = x->parent;
	if (x->parent == NULL)
	{
		*T = y;
	}
	else if (x == x->parent->lChild)
	{
		x->parent->lChild = y;
	}
	else
	{
		x->parent->rChild = y;
	}
	x->parent = y;
	printf("end right_rotate\n");
}

void insert_node(treeNode* T,char c)
{
	//printf("begin insert_node\n");
	if (!T)
	{
		return;
	}
	treeNode data = (treeNode)malloc(sizeof(treeData));
	data->data = c;
	data->color = 1;
	data->parent = NULL;
	data->lChild = NULL;
	data->rChild = NULL;

	if (!*T)
	{
		printf("root node\n");
		*T = data;
		insert_fixup(T,data);
		//printf("end insert_node\n");
		return;
	}

	treeNode p = *T;
	treeNode y = NULL;
	while(p != NULL)
	{
		y = p;
		if (data->data < p->data)
		{
			p = p->lChild;
		}
		else
		{
			p = p->rChild;
		}
	}
	data->parent = y;
	if (y == NULL)
	{
		*T = data;
		////printf("root\n");
	}
	else if (data->data < y->data)
	{
		y->lChild = data;
		//printf("left tree\n");
	}
	else
	{
		y->rChild = data;
		//printf("right tree\n");
	}
	//tree_printf(T);
	insert_fixup(T,data);
	//printf("end insert_node\n");
}

void insert_fixup(treeNode* T,treeNode z)
{
	//printf("begin insert_fixup\n");
	while(z && z->parent && z->parent->color == 1)
	{
		treeNode x = z->parent;
		if (x == x->parent->lChild)
		{
			treeNode y = x->parent->rChild;
			if (y && y->color == 1)
			{
				x->color = 0;
				y->color = 0;
				x->parent->color = 1;
				z = x->parent;
			}
			else if (z == z->parent->rChild)
			{
				z = z->parent;
				left_rotate(T,z);
			}
			else
			{
				z->parent->color = 0;
				z->parent->parent->color = 1;
				z = z->parent->parent;
				right_rotate(T,z);
			}
		}
		else
		{
			treeNode y = x->parent->lChild;
			if (y && y->color == 1)
			{
				x->color = 0;
				y->color = 0;
				x->parent->color = 1;
				z = x->parent;
			}
			else if (z == z->parent->lChild)
			{
				z = z->parent;
				right_rotate(T,z);
			}
			else
			{
				z->parent->color = 0;
				z->parent->parent->color = 1;
				z = z->parent->parent;
				left_rotate(T,z);
			}
		}
	}
	(*T)->color = 0;
	//printf("end insert_fixup\n");
}

void build_tree(treeNode* T)
{
	printf("please input number:\n");
	char c;
	scanf("%c",&c);
	//treeNode T = NULL;
	while(c != ' ')
	{
		insert_node(T,c);
		scanf("%c",&c);
	}
	printf("end build_tree\n");
}

void delet_node(treeNode* T,char data)
{
	printf("begin delet_node\n");
	if (T == NULL || *T == NULL)
	{
		return;
	}
	treeNode p = *T;
	treeNode y = NULL;
	while(p != NULL)
	{
		if (data < p->data)
		{
			p = p->lChild;
		}
		else if (data > p->data)
		{
			p = p->rChild;
		}
		else
		{
			break;
		}
	}

	if (p == NULL)
	{
		return;
	}

	printf("finde delete node is %c\n", p->data);

	y = p;
	if (p->lChild == NULL && p->rChild == NULL)
	{
		delete_node_fixup(T,y);
		//删除y；
		if (y == y->parent->lChild)
		{
			y->parent->lChild = NULL;
		}
		else
		{
			y->parent->rChild = NULL;
		}
		return;
	}
	if (p->lChild != NULL && p->rChild == NULL)
	{
		y = p->lChild;
		if (p == *T)
		{
			*T = y;
			y->color = 0;
		}
		else
		{
			y->color = 0;
			y->parent = p->parent;
			if (p == p->parent->lChild)
			{
				p->parent->lChild = y;
			}
			else
			{
				p->parent->rChild = y;
			}
		}
		return;
	}
	else if(p->lChild == NULL)
	{
		y = p->rChild;
				if (p == *T)
		{
			*T = y;
			y->color = 0;
		}
		else
		{
			y->color = 0;
			y->parent = p->parent;
			if (p == p->parent->lChild)
			{
				p->parent->lChild = y;
			}
			else
			{
				p->parent->rChild = y;
			}
		}
		return;
	}
	else
	{
		//找到右子树中最小的点来替代P;
		treeNode q = p->rChild;
		while(q)
		{
			y = q;
			q = q->lChild;
		}
	}
	printf("find replace node is %c\n", y->data);
	if (y->rChild)
	{
		printf("y's rChild is not NULL\n");
		// if (y == *T)
		// {
		// 	printf("y == *T\n");
		// 	y->rChild->color = 0;
		// 	*T = y->rChild;
		// }
		// else
		// {
			//printf("y != *T\n");
			y->rChild->color = 0;
			if (y == y->parent->lChild)
			{
				y->parent->lChild = y->rChild;
			}
			else
			{
				y->parent->rChild = y->rChild;
			}			
			y->rChild->parent = y->parent;
			tree_printf(T);

			//y替换p------修改指针可能更快速，因为=调用operator=
			//p->data = y->data;
			y->lChild = p->lChild;
			p->lChild->parent = y;
			y->rChild = p->rChild;
			p->rChild->parent = y;
			y->parent = p->parent;
			if (p != *T)
			{
				if (p == p->parent->lChild)
				{
					p->parent->lChild = y;
				}else
				{
					p->parent->rChild = y;
				}
			}
			else
			{
				*T = y;
			}
		//}
	}
	else
	{
		//tree_printf(T);
		//printf("y's rChild is NULL\n");
		//y替换p------修改指针可能更快速，因为=调用operator=
		//p->data = y->data;
		treeNode yp = y->parent;
		// if (y == y->parent->lChild)
		// {
		// 	yp->lChild = NULL;
		// }
		// else
		// {
		// 	yp->rChild = NULL;
		// }
		y->lChild = p->lChild;
		p->lChild->parent = y;
		y->rChild = p->rChild;
		p->rChild->parent = y;
		y->parent = p->parent;
		if (p != *T)
		{
		//	printf("P != *T\n");
			if (p == p->parent->lChild)
			{
				p->parent->lChild = y;
			}
			else
			{
				p->parent->rChild = y;
			}
		}
		else
		{
			*T = y;
		}
		//tree_printf(T);
		if (yp == p)
		{
		//	printf("yp == p\n");
			y->rChild = p;
			p->parent = y;
		}
		else
		{
			yp->lChild = p;
			p->parent = yp;
		}
		p->lChild = NULL;
		p->rChild = NULL;

		//tree_printf(T);
		delete_node_fixup(T,y);
		// tree_printf(T);
		// if (p->lChild == NULL && p->rChild == NULL)
		// {
		// 	printf("p is leaf/n");
		// }

		//删除p；
		if (p ==p->parent->lChild)
		{
			p->parent->lChild = NULL;
		}
		else
		{
			p->parent->rChild = NULL;
		}
	}
	printf("end delet_node\n");
}


void delete_node_fixup(treeNode *T,treeNode x)
{
	printf("begin delete_node_fixup\n");
	while(x && x->color == 0)
	{
		if (x == *T)
		{
			break;
		}
		//treeNode x = z->parent;
		if (x == x->parent->lChild)
		{
			treeNode y = x->parent->rChild;
			if (y && y->color == 1)
			{
				//x->color = 0;
				y->color = 0;
				x->parent->color = 1;
				left_rotate(T,x->parent);
				x = x->parent->rChild;
			}
			if(y->lChild->color == 0 && y->rChild->color == 0)
			{
				//y->lChild->color = 1;
				//y->rChild->color = 1;
				y->color = 1;
				x = x->parent;
			}
			else if (y->rChild->color == 0)
			{
				y->lChild->color = 0;
				y->color = 1;
				right_rotate(T,y);
				y = x->parent->rChild;
			}
			else
			{
				y->color = x->parent->color;
				x->parent->color = 0;
				y->rChild->color = 0;
				left_rotate(T,x->parent);
				x = *T;
			}
			
		}
		else
		{
			treeNode y = x->parent->lChild;
			if (y->color == 1)
			{
				y->color = 0;
				x->parent->color = 1;
				left_rotate(T,x->parent);
			}
			if (y->lChild->color == 0 && y->rChild->color == 0)
			{
				y->color = 1;
				x= x->parent;
			}
			else if (y->lChild == 0)
			{
				y->rChild->color = 0;
				y->color = 1;
				left_rotate(T,y);
				y = x->parent->lChild;
			}
			else
			{
				y->color = x->parent->color;
				x->parent->color = 0;
				x->lChild->color = 0;
				right_rotate(T,x->parent);
				x = *T;
			}
		}
	}
	x->color = 0;
	printf("end delete_node_fixup\n");
}

void tree_mid_bianli(treeNode *T)
{
	if (!T || !*T)
	{
		return;
	}
	treeNode p = *T;
	tree_mid_bianli(&(p->lChild));
	printf("%c,",p->data);
	tree_mid_bianli(&(p->rChild));
}

int get_deep(treeNode *T)
{
	if (!T || !*T)
	{
		return 0;
	}
	treeNode p = *T;
	int leftDeep = get_deep(&p->lChild);
	int rightDeep = get_deep(&p->rChild);
	return leftDeep >= rightDeep ? leftDeep + 1 : rightDeep + 1;
}

//index初始化为-1，
void right_root_left(treeNode *T,std::vector<char*> &vecStr,int &index,int &step,int deep)
{
	if (!T || !*T)
	{
		return ;
	}
	treeNode p = *T;
	step += 1;
	right_root_left(&(p->rChild),vecStr,index,deep,step);
	index += 1;
	step -= 1;
	printf("begin read root:%c,index:%d,step:%d\n", p->data,index,step);
	if (vecStr.size() <= index)
	{
		char* str = new char[deep];
		memset(str,' ',deep);
		vecStr.push_back(str);
	}
	else if (vecStr[index] == NULL)
	{
		vecStr[index] = new char[deep];
		memset(vecStr[index],' ',deep);
	}
	vecStr[index][step] = p->data;
	index += 1;
	step += 1;
	right_root_left(&(p->lChild),vecStr,index,deep,step);
	step -= 1;
	index -= 1;

}

struct datacolor{
	datacolor():data(' '),color(3)
	{

	}
	char data;
	int color;
};

//右子树，根，左子树，遍历
void right_root_left02(treeNode *T,std::vector<datacolor*> &vecStr,int &index,int step,int deep)
{
	if (!T || !*T)
	{
		return ;
	}
	treeNode p = *T;
	right_root_left02(&(p->rChild),vecStr,index,step + 1,deep);
	printf("begin read root:%c,index:%d,step:%d\n", p->data,index,step);
	if (vecStr.size() <= index)
	{
		datacolor* str = new datacolor[deep + 1];
		vecStr.push_back(str);
	}
	else if (vecStr[index] == NULL)
	{
		datacolor* str = new datacolor[deep + 1];
		vecStr[index] = str;
	}
	vecStr[index][step].data = p->data;
	vecStr[index][step].color = p->color;
	index += 1;

	printf("mydata is:%c,myparent is:%c\n",p->data,p->parent ? p->parent->data : 0);
	right_root_left02(&(p->lChild),vecStr,index,step + 1,deep);

}

void tree_printf(treeNode *T)
{

	// //打印出树，

	std::vector<datacolor*> vecStr;
	int step = 0;
	int index = 0;
	int deep = get_deep(T);
	printf("deep:%d\n",deep);
	right_root_left02(T,vecStr,index,step,deep);
	printf("vecStr size:%d\n",int(vecStr.size()));

	//打印出vecStr顺时针旋转90度后的结果
	//
	
	for (int i = 0; i < deep; ++i)
	{
		for (int j = vecStr.size() - 1; j >= 0; --j)
		{
			if (vecStr[j][i].data != ' ')
			{
				if (vecStr[j][i].color)
				{
					printf("\033[47;31m%c\033[0m",vecStr[j][i].data);
				}
				else
				{
					printf("\033[47;30m%c\033[0m",vecStr[j][i].data);
				}
				
				//printf("%c,%d",vecStr[j][i].data,vecStr[j][i].color);
			}
			else
			{
				printf("%c",vecStr[j][i].data);
			}
			
		}
		printf("\n");
	}




	for (int i = 0; i < vecStr.size(); ++i)
	{
		if (vecStr[i] != NULL)
		{
			delete vecStr[i];
		}		
	}
	
	// printf("begin print tree\n");
	// tree_mid_bianli(T);


}

void print_range(treeNode *T)
{
	printf("begin print tree\n");
	tree_mid_bianli(T);
}

int main()
{
	treeNode T = NULL;
	build_tree(&T);
	tree_printf(&T);

	print_range(&T);
	printf("------------------\n");
	// printf("please input delete node:\n");
	// char c;
	// scanf("%c",&c);
	// printf("delete node is %c\n", c);
	// delet_node(&T,c);
	// tree_printf(&T);

	return 0;
}
