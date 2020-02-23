// Gauss-jordan �ҰŹ�

#include <stdio.h>
#include <math.h>

//�ǹ��� ���ϱ� ���� �Լ�
void BubbleSort(double subA[], int n); // ���� ���� �˰��� -> �ǹ��� ã�� ����
double printPivot(double subA[]); // �ǹ��� ���ϱ� ���� �Լ�
void searchPivotIndex(double pivot,double cpyA[][4]); // �ǹ��� ��� ���� ���ϱ� ���� �Լ�
void inspectDiagonal(double pivot,double cpyA[][4]); // �ǹ��� �밢���� ��ġ�ߴ��� �˻��ϴ� �Լ�
void exchangeLine(double cpyA[][4],int originalLine,int changedLine); // �� ��ȯ�� ���� �Լ�
void makeFromPivotToOne(double pivot,double cpyA[][4]); // pivot�� 1�� ����� �Լ�
void insertToNotPivotLine(double cpyA[][4]); // ���������ϴ� �Լ�
void insertFromcpyAToA(double A[][3], double cpyA[][4]); // �ǹ��� �Ϸ��� �ǹ��� Ž������ ���� , A�� ����� cpyA�� ������ �����ϱ� ���� �Լ�

int pivot_column,pivot_line; // pivot�� index
int count;

int main(void)
{
	//�ʱ�ȭ ����
	double A[3][3] = {{3.0,1.0,1.0},{-1.0,1.0,-2.0},{2.0,0.0,-1.0}};
	double X[3] = {0.0,}; // ������������ �� , 0���� �ʱ�ȭ
	double B[3] = {2.0,7.0,5.0};
	double subA[9] = {0.0,}; // ���� ���� �˰����� ����ϱ� ���� �迭 , 0���� �ʱ�ȭ
	double cpyA[3][4] = {0.0,}; // Gauss-Jordan �ҰŹ��� ������ �迭 , 0���� �ʱ�ȭ , Ȯ�����
	double pivot=0; //pivot
	
	
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
		{
			cpyA[i][j] = A[i][j]; //A�� Ȯ����Ŀ� ����
		}
	}
	for(int i=0; i<3; i++)
	{
		cpyA[i][3] = B[i]; // B�� Ȯ����Ŀ� ����
	}

	// Gauss-Jordan �ҰŹ� ����
	for(int i=0; i<3; i++)
{
	count++;
	int k=0;
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
		{
			subA[k++] = A[i][j]; // A�� ��� �� subA�� ����
		}
	}
	BubbleSort(subA,sizeof(subA)/sizeof(double)); // 1. pivot ���ϱ� ���� ���� ���� �˰���
	pivot = printPivot(subA); // 2. pivot ���ϱ�
	searchPivotIndex(pivot,cpyA); // 3. pivot�� index ���ϱ�
	inspectDiagonal(pivot,cpyA); // 4. pivot�� �밢���� ��ġ�ϰ� �ִ��� �˻� 5. �� ��ȯ
	makeFromPivotToOne(pivot,cpyA); // 5. pivot�� 1�� �����
	insertToNotPivotLine(cpyA); // 6. ��������
	insertFromcpyAToA(A,cpyA); // 7. Gauss-Jordan �ҰŹ� �� ����� ��� ���� ��Ŀ� ����
}
	//���
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<4; j++)
		{
			printf("%0.3lf  ", cpyA[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
	for(int i=0; i<3; i++)
	{
		X[i] = cpyA[i][3];
	}

	for(int i=0; i<3; i++)
	{
		printf("X%d = %0.3lf ",i+1,X[i]);
	}
	printf("\n");

	return 0;
}

void BubbleSort(double arr[], int n)
{
	int i, j;
	double temp;

	for(i=0; i<n-1; i++) // pivot�� ���� ������ �迭�� �����ϱ� ���� �ݺ���
	{
		for(j=0; j<(n-i)-1; j++)
		{
			if(fabs(arr[j]) > fabs(arr[j+1]))
			{
				temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}
		}
	}
}

double printPivot(double subA[])
{
	return subA[8]; // pivot ��ȯ
}

void searchPivotIndex(double pivot,double cpyA[][4])
{
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
		{
			if(pivot == cpyA[i][j])
			{
				pivot_column = j;
				pivot_line = i;
			}
		}
	}
}

void inspectDiagonal(double pivot,double cpyA[][4])
{
	if(count==3)
	{
		return;
	}
	if( (pivot_line == 0 && pivot_column == 0) || (pivot_line == 1 && pivot_column == 1) 
		|| (pivot_line == 2 && pivot_column == 2) ) // pivot �� �밢���̶��
	{
	}
	else // pivot�� �밢���� �ƴ϶��
	{
		if(pivot_line==0) // pivot�� 0��° ���� ���
		{
			if(pivot_column==1) // pivot�� 1��° ���� ���
			{
				exchangeLine(cpyA,0,1);
				pivot_line++;
			}
			if(pivot_column==2) // pivot�� 2��° ���� ���
			{
				exchangeLine(cpyA,0,2);
				pivot_line+=2;
			}
		}
		else if(pivot_line==1) // pivot�� 1��° ���� ���
		{
			if(pivot_column==0) // pivot�� 0��° ���� ���
			{
				exchangeLine(cpyA,1,0);
				pivot_line--;
			}
			if(pivot_column==2) // pivot�� 2��° ���� ���
			{
				exchangeLine(cpyA,1,2);
				pivot_line++;
			}
		}
		else if(pivot_line==2) // pivot�� 2��° ���� ���
		{
			if(pivot_column==0) // pivot�� 0��° ���� ���
			{
				exchangeLine(cpyA,2,0);
				pivot_line -=2;
			}
			if(pivot_column==1) // pivot�� 1��° ���� ���
			{
				exchangeLine(cpyA,2,1);
				pivot_line--;
			}
		}
	}
}

void exchangeLine(double cpyA[][4],int originalLine,int changedLine)
{
	double temp[3][4] = {0,};

	for(int i=0; i<4; i++) // �� ��ȯ
	{
		temp[changedLine][i] = cpyA[changedLine][i];
		cpyA[changedLine][i] = cpyA[originalLine][i];
		cpyA[originalLine][i] = temp[changedLine][i];
	}
}

void makeFromPivotToOne(double pivot,double cpyA[][4])
{
	for(int i=0; i<4; i++)
	{
		cpyA[pivot_line][i] /= pivot;
	}
}

void insertToNotPivotLine(double cpyA[][4])
{
	double pivotline[4];
	double changedNotpivotline1[4];
	double changedNotpivotline2[4];

	if(pivot_line == 0)
	{
		for(int i=0; i<4; i++) // �����Ŀ� �ִ� ���ҵ� ������ 
		{
			pivotline[i] = cpyA[pivot_line][i];
			changedNotpivotline1[i] = cpyA[1][i];
			changedNotpivotline2[i] = cpyA[2][i];
		}
		for(int i=0; i<4; i++) // ���� �� ����
		{
			pivotline[i] *= (-changedNotpivotline1[pivot_column]);
			cpyA[1][i] = pivotline[i] + changedNotpivotline1[i];

			pivotline[i] = cpyA[pivot_line][i];

			pivotline[i] *= (-changedNotpivotline2[pivot_column]);
			cpyA[2][i] = pivotline[i] + changedNotpivotline2[i];
		}
	}
	else if(pivot_line == 1)
	{
		for(int i=0; i<4; i++) // �����Ŀ� �ִ� ���ҵ� ������ 
		{
			pivotline[i] = cpyA[pivot_line][i];
			changedNotpivotline1[i] = cpyA[0][i];
			changedNotpivotline2[i] = cpyA[2][i];
		}
		for(int i=0; i<4; i++) // ���� �� ����
		{
			pivotline[i] *= (-changedNotpivotline1[pivot_column]);
			cpyA[0][i] = pivotline[i] + changedNotpivotline1[i];

			pivotline[i] = cpyA[pivot_line][i];

			pivotline[i] *= (-changedNotpivotline2[pivot_column]);
			cpyA[2][i] = pivotline[i] + changedNotpivotline2[i];
		}
	}
	else
	{
		for(int i=0; i<4; i++) // �����Ŀ� �ִ� ���ҵ� ������ 
		{
			pivotline[i] = cpyA[pivot_line][i];
			changedNotpivotline1[i] = cpyA[0][i];
			changedNotpivotline2[i] = cpyA[1][i];
		}
		for(int i=0; i<4; i++) // ���� �� ����
		{
			pivotline[i] *= (-changedNotpivotline1[pivot_column]);
			cpyA[0][i] = pivotline[i] + changedNotpivotline1[i];

			pivotline[i] = cpyA[pivot_line][i];

			pivotline[i] *= (-changedNotpivotline2[pivot_column]);
			cpyA[1][i] = pivotline[i] + changedNotpivotline2[i];
		}
	}
}

void insertFromcpyAToA(double A[][3], double cpyA[][4])
{
	if(count==1)
	{
		if(pivot_line==0) // pivot�� 0��° ���� ���
		{
			for(int i=0; i<3; i++)
			{
				A[1][i] = cpyA[1][i];
				A[2][i] = cpyA[2][i];
			}
		}
		else if(pivot_line==1) // pivot�� 1��° ���� ���
		{
			for(int i=0; i<3; i++)
			{
				A[0][i] = cpyA[0][i];
				A[2][i] = cpyA[2][i];
			}
		}
		else if(pivot_line==2) // pivot�� 2��° ���� ���
		{
			for(int i=0; i<3; i++)
			{
				A[0][i] = cpyA[0][i];
				A[1][i] = cpyA[1][i];
			}
		}

		for(int i=0; i<3; i++)
		{
			A[pivot_line][i] = 0;
		}
	}
	if(count==2)
	{
		//�밢���� 1�� �ƴ� �� ã��, A�� �־��ֱ�
		if(cpyA[0][0] != 1.0)
		{
			for(int i=0; i<3; i++)
			{
				for(int j=0; j<3; j++)
				{
					A[i][j] = 0;
				}
			}

			A[0][0] = cpyA[0][0];
		}
		else if(cpyA[1][1] != 1.0)
		{
			for(int i=0; i<3; i++)
			{
				for(int j=0; j<3; j++)
				{
					A[i][j] = 0;
				}
			}

			A[1][1] = cpyA[1][1];
		}
		else if(cpyA[2][2] != 1.0)
		{
			for(int i=0; i<3; i++)
			{
				for(int j=0; j<3; j++)
				{
					A[i][j] = 0;
				}
			}

			A[2][2] = cpyA[2][2];
		}
	}
}