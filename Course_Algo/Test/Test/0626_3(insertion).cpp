#include <stdio.h>

#define Compare(a,b) a-b

void Swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}
/* �� �Ǽ� �Ф�
void insertion_Sort(int data[])
{
int key;
int i,j;
int size = sizeof(data);

for (i = 0; i < size; i++)
{
for (j = i - 1; j >= 0; j--)
{
if (Compare(data[i], data[j]) > 0)
{
Swap(&data[i], &data[j]);
}
}
}
}
*/

void insertion_Sort(int data[],int length)
{
	int i, j;
	int size = length;

	for (i = 1; i < size; i++) //initialize : 0��° ĭ�� sorted����
	{
		for (j = i; j > 0; j--)
		{
			if (Compare(data[j - 1], data[j] > 0))
			{
				Swap(&data[j - 1], &data[j]);
			}
			else // ���� efficient�ϰ� �ϱ� ���� ������ ������ sorted�� �迭
			{
				break;
			}
		}
	}
}

void main()
{
	int arr[6] = { 1,4,3,2,5,6 };
	int length = sizeof(arr) / sizeof(int);

	insertion_Sort(arr,length);

	printf("%d %d %d %d %d %d\n", arr[0], arr[1], arr[2], arr[3],
		arr[4], arr[5]);
}