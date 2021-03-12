#include <iostream>
using namespace std;
#define ERROR -1
#define OVERFLOW -2
#define OK 1

typedef struct {
	int* elem;//��ַ
	int length;//��ǰ����
	int listsize;//��ǰ����Ĵ洢����
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

int Add(Sqlist& L, int target)//׷��Ԫ��
{
	if (L.length >= L.listsize)//�ж�Խ��
	{
		return OVERFLOW;
	}
	int* now = L.elem + L.length;
	*now = target;
	L.length++;
	return OK;
}

int Explore(Sqlist L)//��������Ԫ��
{
	for (int i = 0; i < L.length; i++)
	{
		cout << *(L.elem+i) << " ";
	}
	cout << endl;
	return OK;
}

int DelEle(Sqlist& L, int Eleno)//ɾ���ڼ���Ԫ��
{
	if (Eleno >= L.length)
	{
		return OVERFLOW;
	}
	int* target = L.elem;//Ŀ��ɾ����Ԫ��
	for (int i = 0; i != Eleno; i++)
	{
		target++;
	}
	int* next = target + 1;
	while (1)//��Ŀ��ɾ����Ԫ�ؿ�ʼ���ú�һλ����ǰһλ��ֱ����һλ(next)�����ĩβ
	{
		*target = *next;
		target++;
		next++;
		if (next >= L.elem + L.length)//�ж�next�Ƿ�Խ�磬Խ����˳�ѭ��
		{
			break;
		}
	}
	L.length -= 1;
	return OK;
}

bool IsExist(Sqlist L, int target)//�ж�ĳ��Ԫ���Ƿ��Ѿ�����
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

int Find(Sqlist L, int target)//����Ŀ��Ԫ�����ڵ�λ�ã����ش�0��ʼ��λ��
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

int DelDup(Sqlist& Orgin)//ȥ��
{
	Sqlist Nlist;//��ʼ��һ���±����ڴ洢���ظ���Ԫ��
	Init(Nlist);
	for (int* now = Orgin.elem; now <= Orgin.elem + Orgin.length; now++)
		//����һ��ָ�룬ָ���ĵ�һ��Ԫ�أ�Ȼ��ָ����ǰ�ƽ���ֱ���ﵽ��ı߽�Ϊֹ
	{
		if (!IsExist(Nlist, *now))
			//������Ԫ�����±��в����ڣ��Ͱ����Ԫ�ش浽�±���
		{
			Add(Nlist, *now);
		}
	}

	Orgin.elem = Nlist.elem;//���ϱ�Ļ�ַָ�룬�ĳ��±��ָ��
	Orgin.length = Nlist.length;//�ĳ���
	Orgin.listsize = Nlist.listsize;//�Ĵ�С
	return OK;
}

int Rev(Sqlist& L)//����
{
	Sqlist NList;//����һ���±����ڴ洢���õ�����
	Init(NList);
	int* now;
	for (now = L.elem + L.length - 1; now >= L.elem; now--)
	{
		Add(NList, *now);
	}
	L.elem = NList.elem;
	return OK;
}

int Link(Sqlist& L1, Sqlist& L2)//������������һ��
{
	int* now;
	for (now = L2.elem; now <= L2.elem + L2.length - 1; now++)
	{
		Add(L1, *now);
	}
	return OK;
}

int main()//������������
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
	//cin >> temp;//¼��Ҫɾ�������
	//DelEle(mylist, temp);
	//cout << Find(mylist, temp)+1 << endl;
	//Rev(mylist);
	Link(mylist, list2);
	Explore(mylist);
}