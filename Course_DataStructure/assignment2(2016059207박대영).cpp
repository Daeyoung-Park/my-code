#include <stdio.h>

int num = 0; //Ƚ�� ī����

void hanoi(int n,char from, char middle,char to)
	{
	        if(n==1)
	       {
	              printf("%d�� ������ %c���� %c�� �̵�\n",n,from,to); //Ż������
				  num += 1;
	       }
	        else
	       {
	              hanoi(n-1,from,to,middle); //n-1���ǿ��ݼ���A���� B���̵�
	              printf("%d�� ������ %c���� %c�� �̵�\n",n,from,to); //�ǾƷ�������A���� C���̵�
				  num += 1;
	              hanoi(n-1,middle,from,to); //n-1���ǿ��ݼ���B���� C���̵�
	       }
	}

int main()
{
	int n;
	printf("������ ������ �Է��Ͻÿ� : ");
	scanf("%d", &n);

	hanoi(n , 'A', 'B', 'C');

	printf("���̵�Ƚ�� : %d\n",num); // ���⼭���� �����ϸ� �ȴ�.
	return 0;
}

