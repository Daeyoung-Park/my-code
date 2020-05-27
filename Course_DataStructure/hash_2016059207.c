#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KEY_SIZE 10
//#define TABLE_SIZE 5 //�ǽ���
#define TABLE_SIZE 13 // ������
#define empty(e) (strlen(e.key)==0) // ������, ��������� 1�� ������ ����
#define equal(e1,e2) (!strcmp(e1.key,e2.key)) //�ǽ���, ������ , ������ 1�� ������ �ҷ��� !���� ���̴�

typedef struct Element
{
	char key[KEY_SIZE]; // key ���� ���ڿ�, �ִ�ũ��� 10
}Element;

/*
typedef struct ListNode
{
Element item;
struct ListNode *link;
}ListNode;
*/


//ListNode *hashTable[TABLE_SIZE]; //�ǽ���
Element hashTable[TABLE_SIZE];

/* //�ǽ���
void initTable(ListNode* ht[])
{
int i;
for (i = 0; i < TABLE_SIZE; i++)
ht[i] = NULL;
}
*/

void initTable(Element ht[])
{
	int i;
	for (i = 0; i < TABLE_SIZE; i++)
		ht[i].key[0] = NULL;
}

int transform(char* key)
{
	int i;
	int number = 0;
	int size = strlen(key);
	for (i = 0; i < size; i++)
		number = number + key[i];

	return number;
}

int hashFunction(char *key)
{
	return transform(key) % TABLE_SIZE;
}

//������
void addHashTable(Element item, Element ht[])
{
	int i, hashValue;
	i = hashValue = hashFunction(item.key);

	
	while(!empty(ht[i]))
	{
		if (equal(item, ht[i]))
		{
			printf("�ߺ� ���� ���� �߻�!\n");
			return;
		}

		i = (i + 1) % TABLE_SIZE;

		if (i == hashValue)
		{
			printf("��Ŷ�� ��� ��á���ϴ�!\n");
			return;
		}
	}

	ht[i] = item;
}

/* //�ǽ���
void addHashTable(Element item, ListNode* ht[])
{
int hashValue = hashFunction(item.key); // �ؽ��� ���ϱ�
ListNode *ptr; // ���ο� ��� �����Ҵ�� ������
ListNode *node = ht[hashValue]; // �ؽ����̺��� ��Ŷ�� ��������Ʈ

for (; node; node = node->link) // �ߺ����� �ƴ��� �׽�Ʈ
{
//equal��� -> ������ ������ �ߺ��̶�� �ϰ� ������
if (equal(item, node->item)) // ����! �׳� element�� �־��ִ°��̴�
{
printf("�ߺ� ���� ���� �߻�!\n");
return;
}
}

ptr = (ListNode*)malloc(sizeof(ListNode));
ptr->item = item;

ptr->link = ht[hashValue]; // ����! node�� ������ �ȵȴ�!!
ht[hashValue] = ptr;
}
*/

//������
void hashSearch(Element item, Element ht[])
{
	int i, hashValue;
	i = hashValue = hashFunction(item.key);

	while (!empty(ht[i]))
	{
		if (equal(item, ht[i]))
		{
			printf("Ž�� ���� : �����մϴ�.\n");
			return;
		}

		i = (i + 1) % TABLE_SIZE;

		if (i == hashValue)
		{
			printf("��Ŷ�� ��� ��á���ϴ�!\n");
			return;
		}
	}

	printf("���̺� ã�� ���� �����ϴ�.\n");
}

/* // �ǽ���
void hashSearch(Element item, ListNode* ht[])
{
ListNode *node;

int hashValue = hashFunction(item.key);
for (node = ht[hashValue]; node; node = node->link)
{
if (equal(node->item, item))
{
printf("Ž�� ���� : �����մϴ�.\n");
return;
}
}

printf("Ž�� ����\n");
}
*/

/* // �ǽ���
void printHashTable(ListNode* ht[])
{
int i;
ListNode *temp;
for (i = 0; i < TABLE_SIZE; i++)
{
temp = ht[i];
for(; temp; temp = temp->link)
{
printf("%s\t", temp->item.key);
//temp = temp->link; �Ǽ�����!
}
printf("\n");
}
}
*/

//������
void printHashTable(Element ht[])
{
	int i;
	for (i = 0; i < TABLE_SIZE; i++)
	{
		printf("[%d]       %s\n", i, ht[i].key);
	}
}

int main()
{
	Element temp;
	int op;

	while (1)
	{
		printf("���� �Է�(0 : �߰�, 1 : Ž��, 2 : ����) = ");
		scanf("%d", &op);

		if (op == 2) break;

		printf("Ű �Է� : ");
		scanf("%s", temp.key);

		if (op == 0)
			addHashTable(temp, hashTable);
		else if (op == 1)
			hashSearch(temp, hashTable);
		
		printHashTable(hashTable);
	}

	return 0;
}

/* //�ǽ���
int main()
{
Element temp;
int op;

while (1)
{
printf("���� �Է�(0 : �߰�, 1 : Ž��, 2 : ���, 3 : ����) = ");
scanf("%d", &op);

if (op == 3)
break;
if (op == 2)
printHashTable(hashTable);
else
{
printf("Ű �Է� : ");
scanf("%s", temp.key);

if (op == 0)
addHashTable(temp, hashTable);
else if (op == 1)
hashSearch(temp, hashTable);
}
}

return 0;
}
*/
