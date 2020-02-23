/*
	�˰���׹����ذ��� 2���� ���� ����

	yeshi_2_1bu.c

	1�� �����ð��� ���� ����� �� �����̿���.

	���� ������ �� ���� ����鿡 �ּ��� �޾� �ΰ�
	// (����) �� ���� �������� ǥ���� �ξ����.
*/

#include <stdio.h>
#include <stack>
/*
	��ǻ�� �о߿��� '��'�� ���� ������ ���� �����ؿ�.

	Sorting problem������ '����'�� '�켼'�� �ǹ��ϸ�,
	Compare()�� ������ return�ϴ� ���� 'left�� �켼'�� �ǹ��ؿ�.
*/
int Compare(int left, int right)
{
	//���� ū ���� �켼�ϵ��� ����� �ʹٸ� �� �ݴ�� ������ ��!
	//return right - left;

	return left - right;
}


/*
	���� ��ǥ�� '���� �迭 �ڸ��� ��� ���'�� ���� ���̴� �������� Swap()�̿���.
	�� �̹� �ٵ� �˰� ���� �״� �׳� ���� �� ��.
*/
void Swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}


void Selection_Sort(int arr[], int length);
void Insertion_Sort(int arr[], int length);
void Bubble_Sort(int arr[], int length);
void Quicksort(int arr[], int length);

// (����) ���� ������ ��, �Ʒ��� ������ �� �� sort �Լ��� �� �ϳ��� ��ġ�� ��� ���� ������ ��������.
//        ó������ selection sort�� �����ϵ��� ������ �����.(�ٸ� �Լ� �̸��� = �����ʿ� ��� ���� �θ� �װ� ȣ�� ����!)
void (*fp_Sort_Selected)(int arr[], int length) = Bubble_Sort;

int main()
{
	// Data ����(�������� �߾��)
	int arr[] = { 6, 5, 4, 3, 2, 1 };
	int length = sizeof arr / sizeof(int);

	// ����� �� index ���� ����
	int idx;

	printf("Before: [");
	for ( idx = 0; idx < length; ++idx )
		printf("%d, ", arr[idx]);
	printf("\b\b]\n"); // (����) '\b'�� ���� '�齺���̽� ����'�� print�����ν� ���ڸ� ���� �� �־��!

	// main() ������ ���� & �ʱ�ȭ�� �� ������ ������ �Ἥ '������ �� sort �Լ�'�� ȣ���ϰ� �־��.
	fp_Sort_Selected(arr, length);

	printf("After:  [");
	for ( idx = 0; idx < length; ++idx )
		printf("%d, ", arr[idx]);
	printf("\b\b]\n");


	return 0;
}

void Selection_Sort(int arr[], int length)
{
	int idx_target;

	// 0����� n����� ������ �ڸ��� ����...
	for ( idx_target = 0; idx_target < length; ++idx_target )
	{
		// ������ ã��(�갡 �´ٰ� �����ϰ� �װ� �³� ����)
		int idx_god = idx_target;
		int idx_challenger;

		for ( idx_challenger = idx_god + 1; idx_challenger < length; ++idx_challenger )
		{
			// ������ Ʋ�ȴٸ� �� �ٲٱ�
			if ( Compare(arr[idx_god], arr[idx_challenger]) > 0 )
			{
				idx_god = idx_challenger;
			}
		}

		// Swap()
		Swap(&arr[idx_target], &arr[idx_god]);
	}
}


void Insertion_Sort(int arr[], int length)
{
	int idx_new = 1;

	// ���ο� �� ĭ�� �����ϴ� 'sorted ����' �����ϱ�
	for ( idx_new = 1; idx_new < length; ++idx_new )
	{
		int idx_target = idx_new;

		// �� �� ĭ�� �ɾҴ� ���ڰ� '������ �ö󰡾�' sorted ���¶�� ������ �� �ֳ� üũ
		for ( idx_target = idx_new; idx_target > 0; --idx_target )
			if ( Compare(arr[idx_target - 1], arr[idx_target]) > 0 )
				Swap(&arr[idx_target - 1], &arr[idx_target]);
			else
				break;

	}
}

void Bubble_Sort(int arr[], int length)
{
	int idx_test;
	int isSorted = 0;
	//int idx_sorted = length; //ū �ݺ� 1ȸ�ϸ� ������ �迭�� sorted�� �� ���̴� ������ compare�� ���� �� ����

	// Sort�� �� �Ǿ��ٰ� Ȯ���� �� ���� ������ �ݺ�(��� �ִ� Ƚ���� �������̱� �ѵ� ��� ���� ����)
	while ( isSorted == 0 )
	{
		// �ϴ� ���� �� ����
		isSorted = 1;

		for ( idx_test = 1; idx_test < length; ++idx_test )
		//for (idx_test = 1; idx_test < idx_sorted; ++idx_test) //ū �ݺ� 1ȸ�ϸ� ������ �迭�� sorted�� �� ���̴� ������ compare�� ���� �� ����
		{
			// ���(left > right)�� ���δٸ�...
			if ( Compare(arr[idx_test - 1], arr[idx_test]) > 0 )
			{
				// �� ���� Swap()�ؼ� �� �տ� ���̴� ����� ����
				Swap(&arr[idx_test - 1], &arr[idx_test]);

				// �ϴ� �̹� �ݺ��� �۷����Ƿ� ǥ���� ��(��� ���� �ݺ��� �ݵ�� ����� ����)
				isSorted = 0;
			}
		}
		//idx_sorted--; //ū �ݺ� 1ȸ�ϸ� ������ �迭�� sorted�� �� ���̴� ������ compare�� ���� �� ���� 

		// ���� �� �ϳ��� ����� �߰ߵ��� �ʾҴٸ� isSorted ���� ������ 1�� ���̰�,
		// �׷��ٸ� sort�� �Ϸ�� ���̹Ƿ� �ݺ��� ������ �� --> ������ ��
	}
}

struct Data_SubArray
{
	int idx_begin; //�ڷᱸ���ν� �迭�� ����ϱ� ���� ��������
	int idx_end; // ���̸� �˾ƾ� ��
};

void Quicksort(int arr[], int length)
{
	std::stack<Data_SubArray> stack;
	Data_SubArray data_current;
	Data_SubArray data_left_subArray;
	Data_SubArray data_right_subArray;

	data_current.idx_begin = 0;
	data_current.idx_end = length;

	stack.push(data_current); // initialize // ��ü�� sort�ϱ� ����

	while (stack.empty() == false) // termination // �ƹ��� ���� ���Ƶ� n�� ����
	{
		//data ����
		int idx_left;
		int idx_mid;
		int idx_begin;
		int idx_end;

		// �̹� �ݺ����� �� ���� ��������
		data_current = stack.top();
		idx_begin = data_current.idx_begin;
		idx_end = data_current.idx_end;
		stack.pop();

		idx_left = idx_begin;
		idx_mid = idx_end-2; //end�� �����̹Ƿ� 1�� ���� �� �������� ���ذ��̴� �� 1�� ����

		// maintenance // ��Ȯ�� ������ �ؾ� �ϴ����� �߿�!!! �� ������ �Ѱ�
		
		while (idx_left <= idx_mid)
		{
			// ��� �߻��ߴ��� �˻�
			if (Compare(arr[idx_left], arr[idx_end - 1]) > 0)
			{
				// �߻��ϸ�(���� ���ں��� ũ�� -> ������ ������ �־����)
				Swap(&arr[idx_left], &arr[idx_mid]);
				idx_mid -= 1;
			}
			else
			{
				// �߻����� �ʾҴٸ� ���� ���� �˻��ϱ� ����
				idx_left += 1;
			}
		}

		// ���� ���ڸ� ������ ��ġ�� Swap
		Swap(&arr[idx_left], &arr[idx_end - 1]);

		//���� �ݺ��� ���� �� ���� ��� ����

		if (idx_left - idx_begin > 1)
		{
			data_left_subArray.idx_begin = idx_begin;
			data_left_subArray.idx_end = idx_left;

			stack.push(data_left_subArray);
		}

		if (idx_end - idx_left > 2)
		{
			data_right_subArray.idx_begin = idx_left + 1;
			data_right_subArray.idx_end = idx_end;

			stack.push(data_right_subArray);
		}

	}
}