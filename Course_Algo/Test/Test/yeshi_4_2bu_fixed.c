/*
�˰���׹����ذ��� 2���� ���� ����

yeshi_3_1bu.c

2���� 1�� �����ð��� ���� ����� �� ���Ͽ� stack �ڷᱸ���� Quicksort()�� �߰��ϰ�,
�׽�Ʈ�� ���� �־��� �迭�� ������ ���� ��� �ִ� FillRandomly()�� �߰��ϰ�,
Compare(), Swap() ȣ�� Ƚ���� ������ global ���� count_Compare, count_Swap�� ��� �ξ����.


���� ������ �� ���� ����鿡 �ּ��� �޾� �ΰ�
// (����) �� ���� �������� ǥ���� �ξ����.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// �κ� �迭�� ���� index�� �� index ������ ���� ��� ���� ����ü �����Դϴ�.
struct Data_SubArray
{
	// �κ� �迭�� 0��° ĭ�� ��ü �迭�� �� ��° ĭ������ ��Ÿ���ϴ�.
	int idx_begin;

	// �κ� �迭�� length��° ĭ�� ��ü �迭�� �� ��° ĭ������ ��Ÿ���ϴ�.
	// (length��° ĭ�� �κ� �迭�� ������ ����)
	int idx_end;
};

// �迭�� �Ἥ �ſ� ������ ������ �� stack�Դϴ�.
struct Stack
{
	struct Data_SubArray *data;
	struct Data_SubArray *top;
};

// �� stack�� ����� return�մϴ�.
// ��� basic operation�� �ƴϱ� ������, �� C++ / Java�� ������ ���� �������� ���� �� �� �ؿ�.
struct Stack *New_Stack()
{
	struct Stack *result = malloc(sizeof(struct Stack));

	// �������Ƿ� �׳� 256ĭ���� ��� �� -> ������ ��û ū �迭�� sort�� �� �ƴ� �̻� ��ĥ ���� ���� ��
	result->data = malloc(sizeof(struct Data_SubArray) * 256);

	// top�� 0�̸� ��� �ִ� ��
	result->top = 0;
}

// �־��� stack�� ��� �ִ��� ���θ� return�մϴ�.
// ��� �� basic operation�̶� �� �� �־��.
int IsEmpty(struct Stack *stack)
{
	return stack->top == 0;
}

// �־��� stack�� ���ο� �κ� �迭 ������ �ø��ϴ�.
// ��� basic operation�̿���.
void Push(struct Stack *stack, struct Data_SubArray new_data)
{
	// stack�� ��� ���� �ʴٸ� ���� top ���� ĭ�� ���ο� top�� ��
	if ( IsEmpty(stack) == 0 )
		++stack->top;
	// stack�� ��� �ִٸ� �̸� ��� �� data �迭�� 0��° ĭ�� top�� ��
	else
		stack->top = stack->data;

	stack->top->idx_begin = new_data.idx_begin;
	stack->top->idx_end = new_data.idx_end;
}

// �־��� stack�� �� ���� �ִ� �κ� �迭 ������ ���� return�մϴ�.
// ��� basic operation�̿���.
struct Data_SubArray Pop(struct Stack *stack)
{
	struct Data_SubArray result;

	result.idx_begin = stack->top->idx_begin;
	result.idx_end = stack->top->idx_end;

	// Pop()�� �ص� ������ stack�� ���� ���� �����̶�� '�ٷ� �� ĭ'�� ���ο� top�� ��
	if ( stack->top != stack->data )
		--stack->top;
	// Pop() �ϸ� stack�� �� �����̶�� top�� 0���� ��� ��
	else
		stack->top = 0;

	// ��� ������ �� ��� ������ return
	return result;
}

// ����� ���� stack�� �����մϴ�.
// ��� basic operation�� �ƴϱ� ������, �� C++�� �ı��� ���� �������� ���� �� �� �ؿ�.
void Delete_Stack(struct Stack *stack)
{
	free(stack->data);
	free(stack);
}







/*
��ǻ�� �о߿��� '��'�� ���� ������ ���� �����ؿ�.

Sorting problem������ '����'�� '�켼'�� �ǹ��ϸ�,
Compare()�� ������ return�ϴ� ���� 'left�� �켼'�� �ǹ��ؿ�.
*/

int count_Compare;

int Compare(int left, int right)
{
	count_Compare = count_Compare + 1;

	//���� ū ���� �켼�ϵ��� ����� �ʹٸ� �� �ݴ�� ������ ��!
	//return right - left;

	return left - right;
}


/*
���� ��ǥ�� '���� �迭 �ڸ��� ��� ���'�� ���� ���̴� �������� Swap()�̿���.
�� �̹� �ٵ� �˰� ���� �״� �׳� ���� �� ��.
*/

int count_Swap;

void Swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;

	count_Swap = count_Swap + 1;
}



void Selection_Sort(int arr[], int length);
void Insertion_Sort(int arr[], int length);
void Bubble_Sort(int arr[], int length);
void Quicksort(int arr[], int length);

void FillRandomly(int arr[], int length);

// (����) ���� ������ ��, �Ʒ��� ������ �� �� sort �Լ��� �� �ϳ��� ��ġ�� ��� ���� ������ ��������.
//        ó������ selection sort�� �����ϵ��� ������ �����.(�ٸ� �Լ� �̸��� = �����ʿ� ��� ���� �θ� �װ� ȣ�� ����!)
void(*fp_Sort_Selected)(int arr[], int length) = Selection_Sort;

int main()
{
	// Data ����
	int arr[8];
	int length = sizeof arr / sizeof(int);

	FillRandomly(arr, length);
	count_Compare = 0;


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

	printf("Compare: %d times, Swap: %d times\n", count_Compare, count_Swap);


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

	// Sort�� �� �Ǿ��ٰ� Ȯ���� �� ���� ������ �ݺ�(��� �ִ� Ƚ���� �������̱� �ѵ� ��� ���� ����)
	while ( isSorted == 0 )
	{
		// �ϴ� ���� �� ����
		isSorted = 1;

		for ( idx_test = 1; idx_test < length; ++idx_test )
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

		// ���� �� �ϳ��� ����� �߰ߵ��� �ʾҴٸ� isSorted ���� ������ 1�� ���̰�,
		// �׷��ٸ� sort�� �Ϸ�� ���̹Ƿ� �ݺ��� ������ �� --> ������ ��
	}
}


// (����)���� ���� �ִ� stack ���� �ڵ���� ������ ���� ���� ���ھ��
void Quicksort(int arr[], int length)
{
	// Data ����

	// ū �ݺ��� ���̿��� data�� �ְ�ޱ� ���� stack�Դϴ�.
	struct Stack *stack = New_Stack(); //O(3) -> O(1)

	// �̹� �ݺ����� �ٷ� �κ� �迭�� ���� ������ stack���� Pop()�� �� ���� �����Դϴ�.
	struct Data_SubArray data_current;

	// �̹� �ݺ����� ���� ���� �κ� �迭�� ���� ������ stack�� Push()�ϱ� ���� �ӽ÷� ��� �� �����Դϴ�.
	struct Data_SubArray data_left_subArray;

	// �̹� �ݺ����� ���� ������ �κ� �迭�� ���� ������ stack�� Push()�ϱ� ���� �ӽ÷� ��� �� �����Դϴ�.
	struct Data_SubArray data_right_subArray;

	// ���� �κ� �迭�� ���̸� ����� ��� ���� �����Դϴ�.
	int lengthOfLeftSubArray;

	// ������ �κ� �迭�� ���̸� ����� ��� ���� �����Դϴ�.
	int lengthOfRightSubArray;



	// Initialization: ù �ݺ��� '��ü �迭'�� �ٷ��� �ϹǷ� �ش� ������ stack�� Push()�� ��
	data_current.idx_begin = 0; //O(1)
	data_current.idx_end = length; //O(1)
	Push(stack, data_current); //O(3) -> O(1)

	// Termination: stack�� �� �̻� 'sort�� �κ� �迭 ����'�� ������ Ż��
	while ( IsEmpty(stack) == 0 ) //n���� ���ذ��� ���ڸ� �θ� �ݺ��� �����Ƿ� O(n) 
	{
		// Data ����
		int idx_left;
		int idx_mid;
		int idx_begin;
		int idx_end;

		// �̹� �ݺ��� �� ���� Pop()�� ����
		data_current = Pop(stack); //O(4) -> O(1)

		// Pop�� ������ ���� �� �� �б� ���� �����鿡 �Ű� ����
		idx_begin = data_current.idx_begin; //O(1)
		idx_end = data_current.idx_end; //O(1) 

		// ������ �� �κ����� ���� �����̹Ƿ� idx�� �� �� �� �ʿ�
		idx_left = idx_begin; //O(1)
		idx_mid = idx_end - 2; //O(1)

		// Maintenance
		while ( idx_left <= idx_mid ) // n���� ���� ���� -> O(n)
		{
			// ����� �߻��߳� �˻�
			if ( Compare(arr[idx_left], arr[idx_end - 1]) > 0 ) // if�� ��ü O(1)
			{
				// �߻��ߴٸ� ��� ���� ���ں��� ũ��. --> ���������� ������ ������ �־�� ��.
				Swap(&arr[idx_left], &arr[idx_mid]);
				idx_mid -= 1;
			}
			else
			{
				// �߻����� �ʾҴٸ� ��� ���� �ΰ� ���� ģ���� �˻��ϱ� ����
				idx_left += 1;
			}
		}

		// ���� ���ڸ� ������ ��ġ�� Swap()
		Swap(&arr[idx_left], &arr[idx_end - 1]); // O(1)


		/*
			(����)
			stack�� ���� �� ���� ũ�Ⱑ ���� �κ� �迭�� ���� ���� ������, 
			���� �κ� �迭�� �� ū ���� ���� Push()�ϰ� �־��.
		
			�̷��� �ϸ� space complexity�� O(lg n)���� ���� �� ����!		
		*/

		// ���� �κ� �迭�� ���� ���ϱ�
		lengthOfLeftSubArray = idx_left - idx_begin; //O(1)
		lengthOfRightSubArray = idx_end - idx_left - 1; //O(1)


		// ���� �κ� �迭�� �� ũ�� �긦 ���߿� sort�ϱ� ���� ���� Push()
		if ( lengthOfLeftSubArray > lengthOfRightSubArray ) // ū if�� ��ü O(1)
		{
			// ���� �ݺ��� ���� �� ���� ��� ����
			if ( lengthOfLeftSubArray > 1 ) // O(1)
			{
				data_left_subArray.idx_begin = idx_begin;
				data_left_subArray.idx_end = idx_left;

				Push(stack, data_left_subArray);
			}

			if ( lengthOfRightSubArray > 1 ) // O(1)
			{
				data_right_subArray.idx_begin = idx_left + 1;
				data_right_subArray.idx_end = idx_end;

				Push(stack, data_right_subArray);
			}
		}
		// �ݴ��� ��쿡�� ������ �κ� �迭�� ���� Push()
		else
		{
			// ���� �ݺ��� ���� �� ���� ��� ����
			if ( lengthOfRightSubArray > 1 )
			{
				data_right_subArray.idx_begin = idx_left + 1;
				data_right_subArray.idx_end = idx_end;

				Push(stack, data_right_subArray);
			}

			if ( lengthOfLeftSubArray > 1 )
			{
				data_left_subArray.idx_begin = idx_begin;
				data_left_subArray.idx_end = idx_left;

				Push(stack, data_left_subArray);
			}
		}
	}

	// Sort�� �� �����ٸ� stack �ݳ� �� ����
	Delete_Stack(stack);
}


void FillRandomly(int arr[], int length)
{
	// Bogosort������ ����� ��������, ��ġ�� �ʴ� ���� ������ ���� ������ ��� ���� ���� �����̿���.

	int max_number = length * 8; //O(1)
	int isUnique;

	srand(time(0));


	// �ϴ� �ּ� �� ���� �̾ƾ� �ϴ� '��ħ == �ݺ� �� �ؾ� ��'���� ����
	isUnique = 0;

	// ��ġ�� �ʴ� ���� ������ ���� ������ �ݺ�
	while ( isUnique == 0 )
	{
		int idx_target = 0;
		int idx_verify = 0;

		// �ϴ� �������� ����
		isUnique = 1;

		// ������ ���� ����
		while ( idx_target < length )
		{
			arr[idx_target] = rand() % max_number;

			idx_verify = 0;

			while ( idx_verify < idx_target )
			{
				// '����' �񱳵� �̸� ����� �� Compare()�� ����ϰ� �־��.
				if ( Compare(arr[idx_verify], arr[idx_target]) == 0 )
				{
					// �ϳ��� ���ٸ� �� �̻��� ������ ���ʿ�
					isUnique = 0;
					break;
				}

				idx_verify = idx_verify + 1;
			}

			// �ϳ��� ���ٸ� �� �̻��� ���� �̱�� ���ʿ�
			if ( isUnique == 0 )
			{
				break;
			}

			idx_target = idx_target + 1;
		}


	}
}
