#include <stdio.h>
#include <stdlib.h>
typedef struct polyNode {
	int coef; //���
	int expon; //����
	struct polyNode* next;
}polyNode;
#define TRUE	1
#define FALSE	0
void addPolynomial(polyNode** pHeadNode, int coef, int expon);
void removePolynomial(polyNode** pHeadNode, int expon);
polyNode* multiplication(polyNode* A, polyNode* B);
void showPolynomial(polyNode* pHeadNode);
void clearPolynomial(polyNode** pHeadNode);
int findPolynomial(polyNode* pHeadNode, int expon);
/* add
1. ���� �Է��Ϸ��� expon�� �̹� �ִٸ� �ߺ��� �����ϱ� ���� findPolynomial�Լ��� �̿��Ͽ� ���� ���θ� �ľ��϶�
	-> �̹� �����Ѵٸ� ���� �� ���ٴ� ���� ����ϰ� main���� ���ư���
2. �׷��� �ʴٸ� �߰��Ϸ��� ��� �������� �Ҵ�����
3. polynomial�� ó�� �������� ���� -> ó���̶�� headnode�� �������ְ� ����
4. �׷��� �ʴٸ� �Է¹��� expon�� �� ��ġ�� Ž��
	-> �� expon�� ����ũ�ٸ� head node�� ����
	-> Ž���ϸ鼭 �� �ڸ� �ٷ� ������ ��ġ�� ���� ����
*/
/* remove
1. findPolynomial�� �̿��� ���� expon�� �����ϴ��� Ȯ��
	-> ���ٸ� ���� �� ���ٰ� ����� ��
2. ���� expon�� head node���� Ȯ��
	-> head node��� head node�� ���� ��带 head node�� ����
3. head node�� �ƴ϶�� ���� node�� ���� node�� �̵��ϰ� �� node�� ���� node�� ���� node�� ����
4. ���� node �޸� ����
*/
/* multi
1. ���� A�� B ���� �ϳ��� NULL �̸� ����ó�� ����
2. A�� B�� node�� �ϳ��� �� ���鼭 ���� �����ؾ� ��
3. ���� expon�� �̹� C�� �����ϴ��� Ȯ��
	-> �ִٸ� �����ϴ� expon�� node�� �� coef�� ����� coef�� ����
	-> ���� ���� ���� 0�̶�� removePolynomial �Լ��� �̿��Ͽ� ����
4. ���� expon�� ������ C�� ���ٸ� addPolynomial�� �̿��Ͽ� C�� �־��ֱ�
5. ������ �Ϸ�� C node�� return
*/
void addPolynomial(polyNode** pHeadNode, int coef, int expon)//���׽� A,B�� �����Ͽ� ���� �߰��ϴ� �Լ�
{
	int i;
	polyNode* pNewNode = NULL;
	polyNode* pTmpNode = NULL;
	
	if( findPolynomial(*pHeadNode,expon) == TRUE )
	{
		printf("this exponent already exists!\n");
		return;
	}
	
	pNewNode = (polyNode*)malloc(sizeof(polyNode));
	pNewNode->expon = expon;
	pNewNode->coef = coef;
	pNewNode->next = NULL;
	if( (*pHeadNode) == NULL )
	{
		(*pHeadNode) = pNewNode;
		(*pHeadNode)->next = NULL;
		return;
	}
	if( pNewNode->expon > (*pHeadNode)->expon )
	{
		pNewNode->next = (*pHeadNode);
		(*pHeadNode) = pNewNode;
		return;
	}
	pTmpNode = (*pHeadNode);
	while( (pNewNode->expon < pTmpNode->expon) )
	{
		if(pTmpNode->next == NULL)
		{
			pTmpNode->next = pNewNode;
			break;
		}
		if(pNewNode->expon > pTmpNode->next->expon)
		{
			pNewNode->next = pTmpNode->next;
			pTmpNode->next = pNewNode;
			break;
		}
		pTmpNode = pTmpNode->next;
	}
	
}
void removePolynomial(polyNode** pHeadNode, int expon) // A,B �� ���ϴ� ������ �����ϴ� �Լ�
{
	polyNode *pPrevyNode, *pDummyNode;
	
	if( findPolynomial(*pHeadNode,expon) == FALSE )
	{
		printf("there is no x^%d\n",expon);
		return;
	}
	if(expon == (*pHeadNode)->expon)
	{
		pDummyNode = (*pHeadNode); 
		(*pHeadNode) = (*pHeadNode)->next;
		free(pDummyNode);
		return;
	}
	pDummyNode = (*pHeadNode);
	while(expon != pDummyNode->expon)
	{
		pPrevyNode = pDummyNode;
		pDummyNode = pDummyNode->next;
	}
	pPrevyNode->next = pDummyNode->next;
	free(pDummyNode);
}
polyNode* multiplication(polyNode* A, polyNode* B) // A*B -> C ����ϴ� �Լ�
{
	polyNode* pTmpNodeA = A;
	polyNode* pTmpNodeB = B;
	polyNode* pTmpNodeC = NULL;
	polyNode* C = NULL;
	int coef, expon;
	
	if(A==NULL || B==NULL)
	{
		printf(" A or B is NULL!\n");
		return NULL;
	}
	while(pTmpNodeA != NULL)
	{
		while(pTmpNodeB != NULL)
		{
			coef = pTmpNodeA->coef * pTmpNodeB->coef;
			expon = pTmpNodeA->expon + pTmpNodeB->expon;
			
			addPolynomial(&pTmpNodeC,coef,expon);
			
			if( findPolynomial(C,expon) == TRUE )
			{
				polyNode* pTmpNode = C;
				while(pTmpNode != NULL)
				{
					if(pTmpNode->expon == expon)
					{
						pTmpNode->coef += coef;
						if(pTmpNode->coef == 0)
						{
							removePolynomial(&C,expon);
						}
						break;
					}
					pTmpNode = pTmpNode->next;
				}
				removePolynomial(&pTmpNodeC,expon);
			}
			pTmpNodeB= pTmpNodeB->next;
		}
	
		while(pTmpNodeC != NULL)
		{
			addPolynomial(&C,pTmpNodeC->coef,pTmpNodeC->expon);
			pTmpNodeC = pTmpNodeC->next;
		}
		pTmpNodeA = pTmpNodeA->next;
		pTmpNodeB = B;
	}
	return C;
}
void showPolynomial(polyNode* pHeadNode) // ������ A,B ���¸� ����ϴ� �Լ�
{
	polyNode* pTmpNode;
	printf("\n");
	pTmpNode = pHeadNode;
	if(pHeadNode == NULL)
	{
		printf("\n===================\n");
		return;
	}
	while(pTmpNode != NULL)
	{
		printf("%d*X^%d ",pTmpNode->coef , pTmpNode->expon);
		if(pTmpNode->next != NULL)
			printf("+ ");
		pTmpNode = pTmpNode->next;
	}
	printf("\n===================\n");
}
void clearPolynomial(polyNode** pHeadNode)  // A,B �� ������ �ʱ�ȭ
{
	polyNode* pTmpNode=(*pHeadNode);
	polyNode* pDummyNode=NULL;
	if( (*pHeadNode) == NULL )
	{
		printf("already clear!\n");
		return;
	}
	while(pTmpNode != NULL)
	{
		pDummyNode = pTmpNode;
		pTmpNode = pTmpNode->next;
		free(pDummyNode);
	}
	(*pHeadNode)=NULL;
}
int findPolynomial(polyNode* pHeadNode, int expon) // A,B �� ������ ���ϴ� ������ �����ϴ��� Ȯ��
{
	polyNode* pTmpNode = pHeadNode;
	if(pHeadNode == NULL)
		return FALSE;
	while(pTmpNode != NULL)
	{
		if(pTmpNode->expon == expon)
		{
			return TRUE;
		}
		pTmpNode = pTmpNode->next;
	}
	return FALSE;
}
int main()
{
	int mode, coef, expon;
	char poly;
	
	polyNode *A, *B, *C;
	A = B = C = NULL;
	do
	{
		printf("\nSelect the mode\n");
		printf("=================\n");
		printf("1: add polynomial\n");
		printf("2: remove polynomial\n");
		printf("3: Multiplication\n");
		printf("4: show polynomial\n");
		printf("5: clear polynomial\n");
		printf("-1: exit the program\n");
		printf("==================\n");
		printf("mode: ");
		scanf("%d", &mode);
		switch (mode)
		{
		case 1:
			printf("\nChoose the polynomial to add ('A'or'B')\n");
			printf("Which polynomial?: ");
			scanf(" %c", &poly);
			if (poly != 'A' && poly != 'B')
				printf("Please choose right polynomial (A or B)\n");
			else
			{
				//����� ������ �Է� �޾Ƽ� polynomial�� �߰��ϴ� �Լ� ����
				//�̹� �����ϴ� ������ �Է� ���� ��� �߰��� �� ����
				printf("input the coef: ");
				scanf("%d", &coef);
				printf("input the expon: ");
				scanf("%d", &expon);
				if (poly == 'A')
					addPolynomial(&A, coef, expon);
				else
					addPolynomial(&B, coef, expon);
			}
			break;
		case 2:
			printf("\nChoose the polynomial to remove ('A'or'B')\n");
			printf("Which polynomial?: ");
			scanf(" %c", &poly);
			if (poly != 'A' && poly != 'B')
				printf("Please choose right polynomial (A or B)\n");
			else
			{
				printf("input the expon: ");
				scanf("%d", &expon);
				//������ �Է� �޾Ƽ� polynomial���� �����ϴ� �Լ� ����
				if (poly == 'A')
					removePolynomial(&A, expon);
				else
					removePolynomial(&B, expon);
			}
			break;
		case 3:
			printf("\nMultiplication with A and B\n");
			//C = A * B ������ ����
			C = multiplication(A, B);
			printf("C: ");
			//C�� ����� ���
			showPolynomial(C);
			break;
		case 4:
			//A,B polynomial ���� ���
			printf("A: ");
			showPolynomial(A);
			printf("B: ");
			showPolynomial(B);
			break;
		case 5:
			printf("\nChoose the polynomial to clear ('A'or'B')\n");
			printf("Which polynomial?: ");
			scanf(" %c", &poly);
			if (poly != 'A' && poly != 'B')
				printf("Please choose right polynomial (A or B)\n");
			else
				//�ش� polynomial�� �ʱ�ȭ ��Ű�� �Լ� ����
			{
				if (poly == 'A')
					clearPolynomial(&A);
				else
					clearPolynomial(&B);
			}
			break;
		default:
			break;
		}
	} while (mode != -1);
	return 0;
}