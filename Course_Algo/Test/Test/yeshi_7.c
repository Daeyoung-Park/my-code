#include <stdio.h>
#include <stdlib.h>

// for ordinary VS environments ( x86 + Windows )
#ifdef WIN32
#include <Windows.h>
LARGE_INTEGER startTime, endTime;
LARGE_INTEGER freq;
int isClockAlreadyCalled;

LARGE_INTEGER clock()
{
	LARGE_INTEGER now;

	if ( isClockAlreadyCalled == 0 )
	{
		isClockAlreadyCalled = 1;
		QueryPerformanceFrequency(&freq);
	}

	QueryPerformanceCounter(&now);

	return now;
}

// for Mac, Linux, or Windows x64
#else

#include <time.h>
clock_t startTime, endTime;

#endif

// ù ������ ����� �⺻ ����ǥ(���̰� 1�̸� 1��° ĭ�� ��� ���� ��)
int default_prices[] = { 0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30 };

int *r; // r_0 ~ r_n���� ���� ���� //����2�� ����3���� ���
int *idxs; //step4�� ����

// �� ����ǥ�� ����� ���� �� �ٽ� ������ �� �Լ�
// ������ �׳� �⺻ ����ǥ�� return�ϵ��� ����� ���Ҿ��.
int *make_prices(int n)
{
	int max_gap = 10; //������ ����ǥ�� initialize�ϴ� �κ� 
	int min_gap = 1;

	int *result = malloc(sizeof(int) * (n + 1));
	int idx;

	r = malloc(sizeof(int) * (n + 1));
	idxs = malloc(sizeof(int) * (n + 1));


	for (idx = 0; idx <= n; ++idx)
	{
		r[idx] = 0; //������ ���ŵǵ��� ���� �� ��Ƴ��� + ������ r[0]�� 0�̹Ƿ�
		idxs[idx] = 0;
	}

	result[0] = 0; //���̰� 0�̸� 0��(value�� 0)

	for (idx = 1; idx <= n; ++idx)
	{
		result[idx] = result[idx - 1] + rand() % (max_gap-min_gap); 
		// ���̰� �����Կ� ���� ���������� �����߼��� �ݿ��ϱ� ����
	}

	//return result;  //������ ����ǥ
	return default_prices; //���� ����ǥ
}


long long call_count;

// p_1 --> prices[1]
int cut_rod_topdown(int *prices, int n) //prices�� ����ǥ
{
	int max_value;
	int idx;

	call_count += 1;

	// ���̰� 0�̸� ��, n == 0�̸� value 0 ��ȯ 
	if (n == 0)
		return 0;

	// n != 0�̸� �ݺ� + ��� ȣ���� ���� max �� ã��
	max_value = -1; // ���� �������� ���� value�� ����
	
	for (idx = 1; idx <= n; ++idx) // max ���ϴ� �κ� // idx=0���� �ϸ� �ȵ� ����!!
	{
		//idx��° ���� �߶���!
		int current_value = prices[idx] + cut_rod_topdown(prices,n-idx); //pi + rn-i �κ�
							//���ʺκ�(�������� �ű��) �������� �ٽ� ���� ����

		if (current_value > max_value) // �̷��� �ڸ��� �� ��������� ���� ���� ���� �� �� ������ ǥ��
		{
			max_value = current_value;
			idxs[n] = idx; //step4��
		}
	}

	return max_value;
}

int cut_rod_topdown_memorized(int *prices, int n) //memorized top-down ���
{
	int max_value;
	int idx;

	call_count += 1;

	// n == 0�̸� 0,
	if (n == 0)
		return 0;

	if (r[n] != 0)
	{
		return r[n];
	}

	// n != 0�̸� �ݺ� + ��� ȣ���� ���� max �� ã��
	max_value = -1; // ����

	for (idx = 1; idx <= n; ++idx) // max ���ϴ� �κ�
	{
		//idx��° ���� �߶���!
		int current_value = prices[idx] + cut_rod_topdown_memorized(prices, n - idx);
		//���ʺκ�(�������� �ű��) �������� �ٽ� ���� ����

		if (current_value > max_value) // �̷��� �ڸ��� �� ��������� ���� ���� ���� �� �� ������ ǥ��
		{
			idxs[n] = idx;

			max_value = current_value;
		}
	}

	r[n] = max_value;

	return max_value;
}

int cut_rod_bottomup(int *prices, int n) //bottop-up ���
{
	int max_value;
	int idx_target;

	call_count += 1;

	// n == 0�̸� 0,
	if (n == 0)
		return 0;

	max_value = -1;

	for (idx_target = 1; idx_target <= n; ++idx_target)
	{
		int idx_verify;

		for (idx_verify = 1; idx_verify <= idx_target; ++idx_verify)
		{
			int current_value = prices[idx_verify] + r[idx_target - idx_verify];

			if (current_value > r[idx_target]) // �̷��� �ڸ��� �� ��������� ���� ���� ���� �� �� ������ ǥ��
			{
				max_value = current_value;

				r[idx_target] = max_value;
				idxs[idx_target] = idx_verify;
			}
		}
		
	}
	return max_value;
}


int main()
{
	int n = 3; // 1 2 3 4 .. 10 �� Ȯ���غ���
	int *prices = make_prices(n);

	int result;
	double elapsedTime;

	// '������ ����'�� �������� �����ϰ� �־��.
	// '���� �ٸ� ���ڷ� �� ����' �Ѵٸ� �Ʒ��� ���ڸ� �ٸ� �ŷ� �ٲٸ� �ſ�.
	srand(796167);

	call_count = 0;

	startTime = clock();

	result = cut_rod_topdown_memorized(prices, n);

	endTime = clock();

#ifdef WIN32
	elapsedTime = endTime.QuadPart - startTime.QuadPart;
	elapsedTime /= freq.QuadPart;
#else
	elapsedTime = endTime;
	elapsedTime -= startTime;
	elapsedTime /= CLOCKS_PER_SEC;
#endif

	 //step4�� �����ϴ� �ڵ�
	/*
	while (n > 0)
	{
		printf("%d, ", idxs[n]);

		n = n - idxs[n];
	}

	printf("\b\b\n");
	*/
	
	
	
	
	printf("cut_rod(%d) -> %d\n"
		   "Call count: %lld\n"
		   "Elapsed time: %.15f seconds\n", n, result, call_count, elapsedTime);
		   
	printf("Done.\n");
	
	

	return 0;
}