// Gauss-seidel �ݺ���

#include <stdio.h>
#include <math.h>
#include <Windows.h>

void BubbleSort(double subA[], int n); // ���� ���� �˰��� -> ���� ū ����� ã�� ����
double printselect(double subA[]); // ���� ū ����� ���ϱ� ���� �Լ�
void inspectDiagonal(double select,double cpyA[][5]); // select�� �밢���� ��ġ�ߴ��� �˻��ϴ� �Լ�
void exchangeLine(double cpyA[][5],int originalLine,int changedLine); // �� ��ȯ�� ���� �Լ�

int select_line0,select_line1,select_line2,select_line3; // select�� ��
int k=0; // �࿡�� ���� ����� ū �������� ���ϱ� ���� �ݺ� ����
double e=0.001; // ������

int main(void)
{
	//�ʱ�ȭ ����
	double A[4][4] = {{12.0,-2.0,-2.0,-3.0},{2.0,7.0,-1.0,1.0},{0.0,1.0,5.0,-2.0},{1.0,2.0,0.0,-8.0}}; // ����������
	double X[4] = {0.0,}; // ������������ �� , 0���� �ʱ�ȭ
	double P[20][4] = {0.0,}; // �ݺ��Ǵ� �� P
	double B[4] = {5,9,4,-5}; // �����
	double subA[4] = {0.0,}; // ���� ���� �˰����� ����ϱ� ���� �迭 , 0���� �ʱ�ȭ
	double cpyA[4][5] = {0.0,}; // �ؿ� ���� ���� ����� ���� �迭 , 0���� �ʱ�ȭ
	double select[4]={0,}; //select
	
	
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<4; j++)
		{
			cpyA[i][j] = A[i][j]; //A�� ����
		}
	}
	for(int i=0; i<4; i++)
	{
		cpyA[i][4] = B[i]; // B�� ����
	}

	// Jacobi �ݺ��� ����

for(int i=0; i<4; i++) // 1. ������ �Ŀ��� ���� ����� ū ������ ���ϱ�
{
	for(int j=0; j<4; j++)
	{
			subA[j] = A[k][j]; // A�� ��� �� subA�� ����
	}
	BubbleSort(subA,sizeof(subA)/sizeof(double)); // 1) select ���ϱ� ���� ���� ���� �˰���
	select[k] = printselect(subA); // 2) select ���ϱ�(����� ���� ū ������ ���ϱ�)
	//printf("%lf \n",select[k]);
	k++; // �����࿡�� ���� ū ��� ã��
}

for(int i=0; i<4; i++) // 2. ������ ���� ���� ū ����� ������
{
	for(int j=0 ; j<5; j++)
	{
		cpyA[i][j] /= select[i];
	}
}

for(int i=0; i<4; i++) // 3. select�� �밢���� ��ġ�ϰ� �ִ��� �˻� 4. �� ��ȯ
{
	inspectDiagonal(select[i],cpyA); 
}

//5. �ݺ��Ǵ� P ����
int num=0;
for(num=1; num<20; num++) // Ż�� ���� 1
{
	// �ٲ� �κ� : �� P[num][����]���� ������ �ϼ��� p[num][����]���� �ٷ� �����!
	P[num][0] = ((-cpyA[0][1])*P[num-1][1]) + ((-cpyA[0][2])*P[num-1][2]) + ((-cpyA[0][3])*P[num-1][3]) + cpyA[0][4];
	P[num][1] = ((-cpyA[1][0])*P[num][0]) + ((-cpyA[1][2])*P[num-1][2]) + ((-cpyA[1][3])*P[num-1][3]) + cpyA[1][4];
	P[num][2] = ((-cpyA[2][0])*P[num][0]) + ((-cpyA[2][1])*P[num][1]) + ((-cpyA[2][3])*P[num-1][3]) + cpyA[2][4];
	P[num][3] = ((-cpyA[3][0])*P[num][0]) + ((-cpyA[3][1])*P[num][1]) + ((-cpyA[3][2])*P[num][2]) + cpyA[3][4];

	printf("P[%d] : ",num-1);
	for(int j=0; j<4; j++)
	{
		printf("%0.3lf\t",P[num-1][j]);
	}
	printf("\n");

	if( (P[num][0] - P[num-1][0]) < e && (P[num][1] - P[num-1][1]) < e && (P[num][2] - P[num-1][2]) < e && (P[num][3] - P[num-1][3]) < e ) // Ż�� ���� 2
		break;
}
	printf("\n");
	printf("��� : x1=%0.3lf x2=%0.3lf x3=%0.3lf x4=%0.3lf\n",P[num][0],P[num][1],P[num][2],P[num][3]);
	
system("pause");

return 0;
}

void BubbleSort(double arr[], int n)
{
	int i, j;
	double temp;

	for(i=0; i<n-1; i++) // select�� ���� ������ �迭�� �����ϱ� ���� �ݺ���
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

double printselect(double subA[])
{
	return subA[3]; // select ��ȯ
}

void inspectDiagonal(double select,double cpyA[][5]) // select�� �밢���� ��ġ�ߴ��� �˻��ϴ� �Լ�
{
	if( select == cpyA[0][0] || select == cpyA[1][1] || select == cpyA[2][2] || select == cpyA[3][3] )
	{
	}
	else // select�� �밢���� �ƴ϶��
	{
		if(select == cpyA[0][1]){exchangeLine(cpyA,1,0);}
		if(select == cpyA[0][2]){exchangeLine(cpyA,2,0);}
		if(select == cpyA[0][3]){exchangeLine(cpyA,3,0);}

		if(select == cpyA[1][0]){exchangeLine(cpyA,0,1);}
		if(select == cpyA[1][2]){exchangeLine(cpyA,2,1);}
		if(select == cpyA[1][3]){exchangeLine(cpyA,3,1);}

		if(select == cpyA[2][0]){exchangeLine(cpyA,0,2);}
		if(select == cpyA[2][1]){exchangeLine(cpyA,1,2);}
		if(select == cpyA[2][3]){exchangeLine(cpyA,3,2);}

		if(select == cpyA[3][0]){exchangeLine(cpyA,0,3);}
		if(select == cpyA[3][1]){exchangeLine(cpyA,1,3);}
		if(select == cpyA[3][2]){exchangeLine(cpyA,2,3);}
	}
}

void exchangeLine(double cpyA[][5],int originalLine,int changedLine) // �� ��ȯ�� ���� �Լ�
{
	double temp[4][5] = {0,};

	for(int i=0; i<5; i++) // �� ��ȯ
	{
		temp[changedLine][i] = cpyA[changedLine][i];
		cpyA[changedLine][i] = cpyA[originalLine][i];
		cpyA[originalLine][i] = temp[changedLine][i];
	}
}