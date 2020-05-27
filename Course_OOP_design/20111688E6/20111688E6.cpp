#include <iostream>
using namespace std;

class CMember
{
	char *m_name;
protected:
	char m_gender;
	double m_tall;
	double m_weight;
public:
	CMember(char *name, char gender, double tall, double weight);
	void Output();
};
CMember::CMember(char *name, char gender, double tall, double weight)
{
	m_name = name;
	m_gender = gender;
	m_tall = tall;
	m_weight = weight;
}
void CMember::Output()
{
	cout.setf(ios::fixed);
	cout.precision(1);
	cout<<"= = = = [�� �⺻ ����] = = = =\n";
	cout<<"�̸� : "<<m_name<<endl;
	cout<<"���� : "<<m_gender<<endl;
	cout<<"���� : "<<m_tall<<endl;
	cout<<"ü�� : "<<m_weight<<endl;
}

class CIndiHealth : public CMember
{
	double m_std_weight; // ǥ�� ü��
	double m_condition_factor; // �񸸵�
public:
	CIndiHealth(char* name, char gender, double tall, double weight);
	void Calculate_Condition_Factor();
	char* Result_Condition_Factor();
	void Output();
};
CIndiHealth::CIndiHealth(char* name, char gender, double tall, double weight) : CMember(name,gender,tall,weight)
{
	m_std_weight = 0.0;
	m_condition_factor = 0.0;
}
void CIndiHealth::Calculate_Condition_Factor()
{
	if(m_gender=='M' || m_gender=='m')
	{
		m_std_weight = (CMember::m_tall - 100) * 0.9;
	}
	else if(m_gender=='F' || m_gender=='f')
	{
		m_std_weight = (CMember::m_tall - 100) * 0.85;
	}

	m_condition_factor = CMember::m_weight / m_std_weight * 100;
}
char* CIndiHealth::Result_Condition_Factor()
{
	if(m_condition_factor < 90)
	{
		return "��ü��";
	}
	else if(m_condition_factor >= 91 && m_condition_factor <= 100)
	{
		return "���� ü��";
	}
	else if(m_condition_factor >= 111 && m_condition_factor <= 120)
	{
		return "��ü��";
	}
	else if(m_condition_factor >= 121 && m_condition_factor <= 130)
	{
		return "�浵��";
	}
	else if(m_condition_factor >= 131 && m_condition_factor <= 150)
	{
		return "�ߵ���";
	}
	else if(m_condition_factor >= 150)
	{
		return "����";
	}
}
void CIndiHealth::Output()
{
	CMember::Output();
	cout<<endl;

	cout<<"= = = = [�� �ǰ� ���] = = = =\n";
	cout.setf(ios::fixed);
	cout.precision(1);
	cout<<"����� �񸸵��� "<<m_condition_factor<<"�̰� "<<Result_Condition_Factor()<<"�Դϴ�"<<endl<<endl;

	if(strcmp(Result_Condition_Factor(),"��ü��") == 0)
	{
		cout<<"����� ǥ��ü���� "<<m_std_weight<<"kg �̹Ƿ� "<<m_std_weight - m_weight<<"kg ������ �ʿ��մϴ�.\n"<<endl;
	}
	else if(strcmp(Result_Condition_Factor(),"���� ü��") == 0)
	{
		cout<<"����� ǥ��ü���� "<<m_std_weight<<"kg �̰� ���� ���� ü���Դϴ�.\n"<<endl;
	}
	else
	{
		cout<<"����� ǥ��ü���� "<<m_std_weight<<"kg �̹Ƿ� "<<m_weight - m_std_weight<<"kg ������ �ʿ��մϴ�.\n"<<endl;
	}
}

void Input_Data(char* name, char &gender, double &tall, double &weight);

void main()
{
	char selection;
	char name[30];
	char gender;
	double tall;
	double weight;
	CIndiHealth* client;

	do
	{

	Input_Data(name,gender,tall,weight);

	client = new CIndiHealth(name, gender, tall, weight); 
	client->Calculate_Condition_Factor();
	client->Output();

		cout<<"������ �ٽ� �Է��Ϸ��� Y�� y��, �����Ϸ��� N �Ǵ� n�� �Է��ϼ��� : ";
		cin>>selection;
		while(selection !='Y' && selection !='y' && selection !='N' && selection !='n')
		{
			cout<<"���� Y,y,N,n�� �Է��Ͻÿ� : ";
			cin>>selection;
		}
	}while(selection =='Y' || selection == 'y');

	system("PAUSE");
}

void Input_Data(char* name, char &gender, double &tall, double &weight)
{
	cout<<"= = = = [�� ���� �Է�] = = = =\n";
	cout<<"�̸� : ";
	cin>>name;

	cout<<"���� : ";
	cin>>gender;

	while(gender !='F' && gender !='f' && gender !='M' && gender !='m')
	{
		cout<<"���� M, m, F, f�� �Է��Ͻÿ� : ";
		cin>>gender;
	}

	cout<<"���� : ";
	cin>>tall;

	cout<<"ü�� : ";
	cin>>weight;

}