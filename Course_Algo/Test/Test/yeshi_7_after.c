/*
	��:
		- ����ǥ�� ���Ƿ� ���ϰ� ���� �� �ٲ� �� �ڵ���� make_prices() �Լ� ���� �ȿ� ���� ��� �ξ����.
			> 50��° �� ������ �־��
			> ����: n �� ��ü�� main()���� �����ϰ� ����!

		- ������ ��� Ÿ�ֿ̹� ������ �������� �� �����ֵ��� �ٸ� �ξ����.
*/

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

// r_0 ~ r_n������ ���� ����
int *r;
int *idxs;

// �� ����ǥ�� ����� ���� �� �ٽ� ������ �� �Լ�
int *make_prices(int n)
{
	int max_gap = 10;
	int min_gap = 1;

	// '������ ����'�� �������� �����ϰ� �־��.
	// '���� �ٸ� ���ڷ� �� ����' �Ѵٸ� �Ʒ��� ���ڸ� �ٸ� �ŷ� �ٲٸ� �ſ�.
	srand(796167);


	int *result = malloc(sizeof(int) * (n + 1));
	int idx;

	r = malloc(sizeof(int) * (n + 1));
	idxs = malloc(sizeof(int) * (n + 1));

	for ( idx = 0; idx <= n; ++idx )
	{
		r[idx] = 0;
		idxs[idx] = 0;
	}

	result[0] = 0;
	
	for ( idx = 1; idx <= n; ++idx )
		result[idx] = result[idx - 1] + rand() % (max_gap - min_gap) + min_gap;

	return default_prices;
	//return result;
}


long long call_count;

// p_1 --> prices[1]
int cut_rod_topdown(int *prices, int n)
{
	int max_value;
	int idx;

	call_count += 1;

	// n == 0�̸� 0,
	if ( n == 0 )
	{
		return 0;
	}

	// n != 0�̸� �ݺ� + ��� ȣ���� ���� max �� ã��
	max_value = -1;

	// �� ���� �߶� ���� maximal value�� �����ϱ� ����
	// ��: idx�� [0, n) �������� ������ ���� �ֱ� ���ٵ�,
	//     ���� �ڵ� ���������δ� �׷��� �ϸ� ���ѷ����� ��������.
	//     (�߶��� �� '�� �ڸ���'�� ���� ���� ���� ������ ���̸� idx�� ��� ���̶� �׷���)
	for ( idx = 1; idx <= n; ++idx )
	{
		// idx��° ���� �߶� ����.
		int current_value = prices[idx] + cut_rod_topdown(prices, n - idx);

		// �̷��� �ڸ��� �� ��������� ���� ���� ���� �� �� �ִٸ� ǥ��
		if ( current_value > max_value )
		{
			max_value = current_value;
			idxs[n] = idx;
		}
	}

	return max_value;
}


// p_1 --> prices[1]
int cut_rod_topdown_memoized(int *prices, int n)
{
	int max_value;
	int idx;

	call_count += 1;

	// n == 0�̸� 0,
	if ( n == 0 )
	{
		return 0;
	}

	// �̹� �޸� �����ϸ� �ٽ� Ǯ�� ���� ����
	if ( r[n] != 0 )
	{
		return r[n];
	}

	// n != 0�̸� �ݺ� + ��� ȣ���� ���� max �� ã��
	max_value = -1;

	// �� ���� �߶� ���� maximal value�� �����ϱ� ����
	// ��: idx�� [0, n) �������� ������ ���� �ֱ� ���ٵ�,
	//     ���� �ڵ� ���������δ� �׷��� �ϸ� ���ѷ����� ��������.
	//     (�߶��� �� '�� �ڸ���'�� ���� ���� ���� ������ ���̸� idx�� ��� ���̶� �׷���)
	for ( idx = 1; idx <= n; ++idx )
	{
		// idx��° ���� �߶� ����.
		int current_value = prices[idx] + cut_rod_topdown_memoized(prices, n - idx);

		// �̷��� �ڸ��� �� ��������� ���� ���� ���� �� �� �ִٸ� ǥ��
		if ( current_value > max_value )
		{
			max_value = current_value;
			idxs[n] = idx;
		}
	}

	r[n] = max_value;

	return max_value;
}

// p_1 --> prices[1]
int cut_rod_bottomup(int *prices, int n)
{
	int idx_target;

	call_count += 1;

	// n == 0�̸� 0,
	if ( n == 0 )
	{
		return 0;
	}

	// r_1���� r_n(����)���� ä������ ����
	for ( idx_target = 1; idx_target <= n; ++idx_target )
	{
		int idx_verify;

		for ( idx_verify = 1; idx_verify <= idx_target; ++idx_verify )
		{
			// idx��° ���� �߶� ����.
			int current_value = prices[idx_verify] + r[idx_target - idx_verify];

			// �̷��� �ڸ��� �� ��������� ���� ���� ���� �� �� �ִٸ� ǥ��
			if ( current_value > r[idx_target] )
			{
				r[idx_target] = current_value;
				idxs[idx_target] = idx_verify;
			}
		}
	}

	return r[n];
}




int main()
{
	int n = 4;
	int *prices = make_prices(n);
	int idx;

	int result;
	double elapsedTime;

	call_count = 0;

	startTime = clock();

	//result = cut_rod_topdown(prices, n);
	//result = cut_rod_topdown_memoized(prices, n);
	result = cut_rod_topdown_memoized(prices, n);

	endTime = clock();

#ifdef WIN32
	elapsedTime = endTime.QuadPart - startTime.QuadPart;
	elapsedTime /= freq.QuadPart;
#else
	elapsedTime = endTime;
	elapsedTime -= startTime;
	elapsedTime /= CLOCKS_PER_SEC;
#endif

	// prices
	printf("p: [");
	for ( idx = 0; idx <= n; ++idx )
		printf("%d, ", prices[idx]);
	printf("\b\b]\n");

	// revenues
	printf("r: [");
	for ( idx = 0; idx <= n; ++idx )
		printf("%d, ", r[idx]);
	printf("\b\b]\n");

	// idxs(���� ���� ������ ����)
	printf("i: [");
	for ( idx = 0; idx <= n; ++idx )
		printf("%d, ", idxs[idx]);
	printf("\b\b] - memoized\n");


	// optimal solution(�׷��� ��� ��� �߶�� �ϴ���)
	printf("   [");
	while ( n > 0 )
	{
		printf("%d, ", idxs[n]);

		n = n - idxs[n];
	}
	printf("\b\b] - actual\n");

	// value of optimal solution
	printf("r[n]: %d\n", result);

	printf("Elapsed time: %.15f seconds\n", elapsedTime);
	printf("Done.\n");

	return 0;
}