#include <iostream>
using namespace std;
#define ERROR -1
#define OVERFLOW -2
#define OK 1

typedef struct {
	int* elem;//基址
	int length;//当前长度
	int listsize;//当前分配的存储容量
}Sqlist;
#define MAX 100

int Init(Sqlist& L)
{
	L.elem = new int[MAX];
	if (!L.elem)
	{
		exit(OVERFLOW);
	}
	L.length = 0;
	L.listsize = MAX;

	return OK;

}

int Add(Sqlist& L, int target)//追加元素
{
	if (L.length >= L.listsize)//判断越界
	{
		return OVERFLOW;
	}
	int* now = L.elem + L.length;
	*now = target;
	L.length++;
	return OK;
}

int Explore(Sqlist L)//回显所有元素
{
	for (int i = 0; i < L.length; i++)
	{
		cout << *(L.elem+i) << " ";
	}
	cout << endl;
	return OK;
}

int DelEle(Sqlist& L, int Eleno)//删除第几个元素
{
	if (Eleno >= L.length)
	{
		return OVERFLOW;
	}
	int* target = L.elem;//目标删除的元素
	for (int i = 0; i != Eleno; i++)
	{
		target++;
	}
	int* next = target + 1;
	while (1)//从目标删除的元素开始，让后一位覆盖前一位，直到后一位(next)到达表末尾
	{
		*target = *next;
		target++;
		next++;
		if (next >= L.elem + L.length)//判断next是否越界，越界就退出循环
		{
			break;
		}
	}
	L.length -= 1;
	return OK;
}

bool IsExist(Sqlist L, int target)//判断某个元素是否已经存在
{
	for (int* now = L.elem; now <= L.elem + L.length; now++)
	{
		if (*now == target)
		{
			return true;
		}
	}
	return false;
}

int Find(Sqlist L, int target)//查找目标元素所在的位置，返回从0开始的位序
{
	for (int* now = L.elem; now <= L.elem + L.length; now++)
	{
		if (*now == target)
		{
			return now-L.elem;
		}
	}
	return ERROR;
}

int DelDup(Sqlist& Orgin)//去重
{
	Sqlist Nlist;//初始化一个新表，用于存储不重复的元素
	Init(Nlist);
	for (int* now = Orgin.elem; now <= Orgin.elem + Orgin.length; now++)
		//创建一个指针，指向表的第一个元素，然后指针向前推进，直到达到表的边界为止
	{
		if (!IsExist(Nlist, *now))
			//如果这个元素在新表中不存在，就把这个元素存到新表里
		{
			Add(Nlist, *now);
		}
	}

	Orgin.elem = Nlist.elem;//把老表的基址指针，改成新表的指针
	Orgin.length = Nlist.length;//改长度
	Orgin.listsize = Nlist.listsize;//改大小
	return OK;
}

int Rev(Sqlist& L)//表倒置
{
	Sqlist NList;//创建一个新表用于存储倒置的数据
	Init(NList);
	int* now;
	for (now = L.elem + L.length - 1; now >= L.elem; now--)
	{
		Add(NList, *now);
	}
	L.elem = NList.elem;
	return OK;
}

int Link(Sqlist& L1, Sqlist& L2)//两个表连接在一起
{
	int* now;
	for (now = L2.elem; now <= L2.elem + L2.length - 1; now++)
	{
		Add(L1, *now);
	}
	return OK;
}

int main()//测试性主函数
{
	Sqlist mylist;
 	Init(mylist);
	int temp;
	while (cin >> temp)
	{
		if (temp == -1)
		{
			break;
		}
		Add(mylist, temp);
	}
	Sqlist list2;
	Init(list2);
	while (cin >> temp)
	{
		if (temp == -1)
		{
			break;
		}
		Add(list2, temp);
	}
	Explore(mylist);
	//DelDup(mylist);
	//cin >> temp;//录入要删除的序号
	//DelEle(mylist, temp);
	//cout << Find(mylist, temp)+1 << endl;
	//Rev(mylist);
	Link(mylist, list2);
	Explore(mylist);
}