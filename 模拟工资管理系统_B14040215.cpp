//����Ա��
//1���������¼ϵͳ
//2��¼��Ա����Ϣ���幤�ʣ�������Ӧ��˰�𣨼������μ����¹��������ߣ�
//3����ѯ����ʾ���е�Ա��������Ϣ
//4����ʾͳ����Ϣ��Ա����Ŀ������������˰������
//4������ָ��������ѯ
//5����ɾ����Ա����¼
//˰�����߻����ǲ�ͬ����ȼ��Ĺ���ʹ�ò�ͬ�ı�����ȡ˰���������±�
//����		˰��
//0��1500		0��
//1500��2500	10�����������֣�
//2500��3500	15�����������֣�
//3500��5000	20�����������֣�
//5000��10000	30�����������֣�
//10000��		40�����������֣�
//     Ա����
//1��	�Թ���Ϊ��¼ID�������Լ��趨��
//2��	���Բ�ѯ���˵������Ϣ��
//3��	ϵͳ�ṩָ��ʱ�����Ĳ�ѯ���ܡ�

//����Ա����ΪB14040215���û���¼IDΪ����,��ʼ����Ϊ0215
#include<iostream>
#include<string>
#include<fstream>
#include <cstdlib>    //exit()
#include<conio.h>   //getch()
#include<windows.h>  //SetFileAttributes()
#include<iomanip>   //setw(2)
using namespace std;
const int N = 100;//N��Ϊ���ְ������
int buffer = 0;//ְ�������Ļ���
int loc = -1;//��¼�û���¼ʱ�û���ID�±�

//ְ�� ��
class Worker
{
public:
	Worker(){
		age = 0; salary = 0; tax = 0; pay = 0;
		strcpy(Pw,"0215");
	}
	~Worker(){}
	void Show();//ְ����Ϣ��ʾ
	double GetTax();  // ��ȡ��˰
	double GetPay();  // ��ȡʵ������
	friend class Workers;
private:
	string ID, name, sex, edu, address, tel;//���ţ��������Ա𣬽����̶ȣ�סַ���绰
	int age;//����
	double salary,tax, pay;//��н��˰��ʵ������
	char Pw[20];//ְ������
};
//ְ��Ⱥ ��
class Workers
{
private:
	Worker w[N];
	int NUM;//��������ְ����Ŀ
	int count;// �������㵱ǰ��������ӵ�ְ����Ŀ
	double tsalary = 0, ttax = 0;// ����������˰������
public:
	int  Num();//���㲢�����ļ��Ѱ�����ְ������
	void add();//ְ����Ϣ���
	void Sort();//ְ����Ϣ����
	void Search();//����ְ����Ϣ��������������Ϊ�Ѿ��������ļ��е�ְ����
	void Delete();//ְ����Ϣɾ��
	void Amend();//ְ����Ϣ�޸�
	void Save();//ְ����Ϣ���ļ���ʽ����
	void Showsaved();//ְ����Ϣ��ʾ��������ʾ�ļ��е����ݣ�
	void Showcur();//��ȡ����ʾְ����Ϣ����ǰ�������������Ϣ��
	Workers()
	{
		NUM = 0;
		count = 0;
	}
	string GetID(int);//���ְ������
	char * GetPw(int);//��ȡְ��������
	void Show(int );//�û���¼ʱ��ʾ��ǰ�û���Ϣ
	void Total();//ͳ����Ϣ������ʾ
	void ChangePw();//�û��޸�����
};

//��½����
void loginmenu()
{
	system("cls");
	cout << "\n\n              *************************************************" << endl;
	cout << "              **            ��ѡ��������Ҫ��ģʽ             **" << endl;
	cout << "              **                1.����Աģʽ                 **" << endl;
	cout << "              **                2.�û�ģʽ                   **" << endl;
	cout << "              *************************************************" << endl;


}
//����Ա�˵�
void admenu()
{

	cout << endl;
	cout << "        **************************************************************" << endl;
	cout << "        **                                                          **" << endl;
	cout << "        **        ===��ӭʹ���Ͼ��ʵ��ѧְ�����ʹ���ϵͳ===        **" << endl;
	cout << "        **                                                          **" << endl;
	cout << "        **                   1.ְ����Ϣ���                         **" << endl;
	cout << "        **                   2.��ǰ��Ϣ�鿴                         **" << endl;
	cout << "        **                   3.ְ����Ϣ����                         **" << endl;
	cout << "        **                   4.ְ����Ϣ����                         **" << endl;
	cout << "        **                   5.ְ����Ϣ�޸�                         **" << endl;
	cout << "        **                   6.ְ����Ϣ����                         **" << endl;
	cout << "        **                   7.ְ����Ϣɾ��                         **" << endl;
	cout << "        **                   8.�Ѵ���Ϣ��ʾ                         **" << endl;
	cout << "        **                   9.ְ����Ϣͳ��                         **" << endl;
	cout << "        **                   0.�˳�                                 **" << endl;
	cout << "        **                                                          **" << endl;
	cout << "        **************************************************************" << endl;
	cout << endl;
}
//�û��˵�
void usermenu()
{

	cout << endl;
	cout << "        **************************************************************" << endl;
	cout << "        **                                                          **" << endl;
	cout << "        **        ===��ӭʹ���Ͼ��ʵ��ѧְ�����ʹ���ϵͳ===        **" << endl;
	cout << "        **                                                          **" << endl;
	cout << "        **                   1.��Ϣ��ѯ                             **" << endl;
	cout << "        **                   2.�޸�����                             **" << endl;
	cout << "        **                   0.�˳�                                 **" << endl;
	cout << "        **                                                          **" << endl;
	cout << "        **************************************************************" << endl;
	cout << endl;
}
//���Һ����˵�
void Searchmenu()
{
	cout << "��ѡ����ҷ�ʽ��" << endl;
	cout << "               ***********************************************" << endl;
	cout << "               **            1.�����Ų���                  **" << endl;
	cout << "               **            2.����������                  **" << endl;
	cout << "               **            3.�����ʲ���                  **" << endl;
	cout << "               **            4.��ѧ������                  **" << endl;
	cout << "               **            5.���������                  **" << endl;
	cout << "               **            6.����ַ����                  **" << endl;
	cout << "               **            0.�������˵�                  **" << endl;
	cout << "               ***********************************************" << endl;
}
//�޸ĺ����˵�
void Amendmenu()
{
	cout << endl;
	cout << "               ***********************************************" << endl;
	cout << "               **            1.�޸Ĺ���                    **" << endl;
	cout << "               **            2.�޸�����                    **" << endl;
	cout << "               **            3.�޸��Ա�                    **" << endl;
	cout << "               **            4.�޸�ѧ��                    **" << endl;
	cout << "               **            5.�޸�����                    **" << endl;
	cout << "               **            6.�޸Ĺ���                    **" << endl;
	cout << "               **            7.�޸ĵ�ַ                    **" << endl;
	cout << "               **            8.�޸ĵ绰                    **" << endl;
	cout << "               **            0.�������˵�                  **" << endl;
	cout << "               ***********************************************" << endl;
}
//2015���µ�˰�����ߣ�
//�����㣺3500
//ȫ��Ӧ��˰���ö�                                            ˰��         ����۳���(Ԫ)
//ȫ��Ӧ��˰�����1500Ԫ                           3 %                     0
//ȫ��Ӧ��˰���1500Ԫ��4500Ԫ              10 %                   105
//ȫ��Ӧ��˰���4500Ԫ��9000Ԫ              20 %                   555
//ȫ��Ӧ��˰���9000Ԫ��35000Ԫ            25 %                  1005
//ȫ��Ӧ��˰���35000Ԫ��55000Ԫ          30 %                  2755
//ȫ��Ӧ��˰���55000Ԫ��80000Ԫ          35 %                  5505
//ȫ��Ӧ��˰���80000Ԫ                             45 %                 13505
double  Worker::GetTax()  // ��˰
{
	double beyond = salary - 3500;
	if (salary <= 3500)
		return tax = 0;
	else if (salary <= 5000)
		return tax = beyond*0.03 - 0;
	else if (salary <= 8000)
		return tax = beyond * 0.10 - 105;
	else if (salary <= 12500)
		return tax = beyond *0.20 - 555;
	else if (salary <= 38500)
		return tax = beyond * 0.25 - 1005;
	else if (salary <= 58500)
		return tax = beyond*0.30 - 2755;
	else if (salary <= 83500)
		return tax = beyond*0.35 - 5505;
	else
		return tax = beyond*0.45 - 13505;
}
double Worker::GetPay()
{
	return pay = salary - tax;
}
void Worker::Show()//��ʾְ����Ϣ����ʵ��
{
	cout << "����\t����\t�Ա�\tѧ��\t����\t��ַ\t�绰\t\tʵ������" << endl;
	cout << ID << '\t' << name << '\t' << sex << '\t' << edu << '\t' << age << '\t' << address << '\t' << tel << '\t' << GetPay() << endl;
	cout << endl;
}
//���˵�����ʵ��
void Execute()
{
	string p;//���ղ˵�ѡ����ַ���
	int error = 0;//�����������������
	char pw[20];//�洢���������
	char password;//����������ַ�
	Workers wl;
	int cnum = wl.Num();//cnum:�ѱ����ְ����
	int choice0;//ѡ�����Ա��¼�����û���¼
	loginmenu();
	cout << "������ѡ��";
	cin >> choice0;
	switch (choice0)
	{
	case 1:
		do
		{
			cout << endl;
			cout << "����Ա��¼"<<endl;
			cout << "���������룺";
			for (int j = 0; j<20; j++)
			{
				password = getch();
				if (password == 13)
				{
					pw[j] = '\0';
					break;
				}
				if (password == 8)
				{
					cout << '\b' << ' ' << '\b';
					j -= 2;
				}
				else 
				{
					pw[j] = password;
					cout << '*';
				}
			}
			if (strcmp(pw, "B14040215") == 0)
			{
				cout << "\n��¼�ɹ���ף������˳�����������!" << endl;
				Sleep(2000);
				break;
			}
			else
			{
				error++;
				if (3-error>0)
					cout << "\n�㻹��" << 3-error << "�λ��ᣡ" << endl;
				if (error == 3)
				{
					for (int i = 10; i >= 0; i--)
					{
						system("cls");
						cout << "\n     ****************************************************" << endl;
						cout << "     **�������3�Σ�ϵͳ"<<setw(2)<<i<<"����Զ��˳������Ժ����µ�¼**" << endl;
						cout << "     *******************************************************" << endl;
						Sleep(1000);
					}
					exit(1);
				}
				cout << "\n�����������������" << endl;
				Sleep(1000);
			}
		} while (error<3);
		while (1)
		{
			system("cls");
			admenu();
			cout << "��ѡ�����ֱ��0~8" << endl;
			int choice1;//ѡ�����Ա�˵��Ĺ���
			cin >> choice1;
			while (!(choice1 >= 0 && choice1 <= 9))
			{
				cout << "�����������������룺" << endl;
				cin >> choice1;
			}
			switch (choice1)
			{
			case 1:
				wl.add();
				cout << "\n�Ƿ�ϣ��������Ϣ��" << endl;
				cout << "�ǣ�Y��     ��(N)" << endl;
				char choice2;
				cin >> choice2;
				while (1)
				{
					if (choice2 == 'y' ||choice2== 'Y'){
						wl.Save(); break;
					}
					else if (choice2 == 'n' || choice2=='N'){
						break;
					}
					else{
						cout << "��������������Y/N(y/n):" << endl;
						cin >> choice2;
					}
				}
				break;
			case 2:
				wl.Showcur();//�鿴��ǰ��Ϣ
				break;
			case 3:
				wl.Save();//���浱ǰ��Ϣ
				break;
			case 4:
				wl.Search();//����
				break;
			case 5:
				wl.Amend();//�޸�
				break;
			case 6:
				wl.Sort();//����
				break;
			case 7:
				wl.Delete();//ɾ��
				break;
			case 8:
				wl.Showsaved();//�鿴�Ѵ������Ϣ
				break;
			case 9:
				wl.Total();//ͳ�Ʋ��鿴ͳ����Ϣ
				break;
			case 0:
				cout << "                           �������Ҫ�뿪������" << endl;
				cout << "                       �ţ��ݰݣ�Y��     �᲻��(N)" << endl;
				char choice3;
				cin >> choice3;
				while (1)
				{
					if (choice3 == 'y' || choice3 == 'Y'){
						cout << "ϵͳ�˳���" << endl; 
						exit(0);
					}
					else if (choice3 == 'n' || choice3 == 'N'){
						break;
					}
					else{
						cout << "��������������Y/N(y/n):" << endl;
						cin >> choice3;
					}
				}
				break;
			default:
				break;
			}
			cout << "�Ƿ񷵻����˵�?  Y/N" << endl;
			cin >> p;
			while (1){
				if (p == "n" || p == "N")
				{
					cout << "                           �������Ҫ�뿪������" << endl;
					cout << "                       �ţ��ݰݣ�Y��     �᲻��(N)" << endl;
					char choice3;
					cin >> choice3;
					while (1)
					{
						if (choice3 == 'y' || choice3 == 'Y'){
							cout << "ϵͳ�˳���" << endl; 
							exit(0);
						}
						else if (choice3 == 'n' || choice3 == 'N'){
							break;
						}
						else{
							cout << "��������������Y/N(y/n):" << endl;
							cin >> choice3;
						}
					}
					break;
				}
				else if (p == "y" || p == "Y")break;
				else{
					cout << "�������������� Y/N(y/n) !" << endl;
					cin >> p;
				}
			}
		}
		break;
	case 2:
		cout << endl;
		if (cnum == 0){
			cout << "δ¼���κ�ְ����Ϣ��ϵͳ���˳�" << endl;
			Sleep(1500);
			cout << "ϵͳ�˳���" << endl; 
			exit(0);
		}
		cout << "�û���¼���������û��������룡" << endl;
		cout << "�û��������ţ���";
		string id;//�����ְ������
		while (loc == cnum || loc == -1)
		{
			if (loc != -1){
				cout << "��������û��������ڣ����������룺" << endl;
				cout << "�û��������ţ���";
			}
			cin >> id;
			for (loc = 0; loc< cnum; loc++)
			{
				bool k = (wl.GetID(loc) == id);
				if (k)
					break;
			}
		}
		do
		{
			cout << "���룺";
			for (int j = 0; j<20; j++)
			{
				password = getch();
				if (password == 13)
				{
					pw[j] = '\0';
					break;
				}
				if (password == 8)
				{
					cout << '\b' << ' ' << '\b';
					j -= 2;
				}
				else
				{
					pw[j] = password;
					cout << '*';
				}
			}
			if (strcmp(pw, wl.GetPw(loc) )== 0)
			{
				cout << "\n��¼�ɹ���ף������˳�����������!" << endl;
				Sleep(2000);
				break;
			}
			else
			{
				error++;
				if (3 - error>0)
					cout << "\n�㻹��" << 3 - error << "�λ��ᣡ" << endl;
				if (error == 3)
				{
					for (int i = 10; i >= 0; i--)
					{
						system("cls");

						cout << "\n     ****************************************************" << endl;
						cout << "     **�������3�Σ�ϵͳ" << setw(2) << i << "����Զ��˳������Ժ����µ�¼**" << endl;
						cout << "     *******************************************************" << endl;
						Sleep(1000);
					}
					exit(0);
				}
				cout << "\n�����������������" << endl;
				Sleep(1000);
			}
		} while (error<3);
		while (1)
		{
			system("cls");
			usermenu();
			cout << "��ѡ��0-2����" << endl;
			int choice1;
			cin >> choice1;
			while (!(choice1 >= 0 && choice1 <= 7))
			{
				cout << "�����������������룺" << endl;
				cin >> choice1;
			}
			switch (choice1)
			{
			case 1:
				wl.Show(loc);
				Sleep(3000);
				break;
			case 2:
				wl.ChangePw();
				break;
			case 0:
				cout << "                           �������Ҫ�뿪������" << endl;
				cout << "                       �ţ��ݰݣ�Y��     �᲻��(N)" << endl;
				char choice3;
				cin >> choice3;
				while (1)
				{
					if (choice3 == 'y' || choice3 == 'Y'){
						cout << "ϵͳ�˳���" << endl; 
						exit(0);
					}
					else if (choice3 == 'n' || choice3 == 'N'){
						break;
					}
					else{
						cout << "��������������Y/N(y/n):" << endl;
						cin >> choice3;
					}
				}
				break;
			default:
				break;
			}
			cout << "�Ƿ񷵻����˵�?  Y/N" << endl;
			cin >> p;
			while (1){
				if (p == "n" || p == "N")
				{
					cout << "                           �������Ҫ�뿪������" << endl;
					cout << "                       �ţ��ݰݣ�Y��     �᲻��(N)" << endl;
					char choice3;
					cin >> choice3;
					while (1)
					{
						if (choice3 == 'y' || choice3 == 'Y'){
							cout << "ϵͳ�˳���" << endl; 
							exit(0);
						}
						else if (choice3 == 'n' || choice3 == 'N'){
							break;
						}
						else{
							cout << "��������������Y/N(y/n):" << endl;
							cin >> choice3;
						}
					}
					break;
				}
				else if (p == "y" || p == "Y")break;
				else{
					cout << "�������������� Y/N(y/n) !" << endl;
					cin >> p;
				}
			}
		}
	}
}
//���㲢�����ļ��Ѱ�����ְ������
int  Workers::Num()
{
	SetFileAttributes(L"E:\\password.txt", FILE_ATTRIBUTE_NORMAL);
	ifstream in("E:\\worker.txt");
	ifstream inp("E:\\password.txt");
	int i = 0;
	while (in >> w[i].ID >> w[i].name >> w[i].sex >> w[i].edu >> w[i].age >> w[i].address >> w[i].tel >> w[i].salary >> w[i].tax >> w[i].pay&&inp >> w[i].Pw)
	{
		i++;
	}
	NUM = i;
	in.close();
	inp.close();
	SetFileAttributes(L"E:\\password.txt", FILE_ATTRIBUTE_HIDDEN);
	return NUM;
}
//ְ����Ϣ��Ӻ���
void Workers::add()
{
	cout << "������ְ����Ϣ:" << endl;
	string num;
	cout << "����:";
	cin >> num;
	for (int i = 0; i<NUM; i++)
		if (w[i].ID == num){
			cout << "��ְ������Ѵ��ڣ����������룺" << endl;
			cin >> num;
			i = 0;
		}
	w[NUM].ID = num; 
	bool f = 1;
	while (f){
		cout << "����:"; cin >> w[NUM].name;
		if (w[NUM].name.size() <= 1){
			cout << "������Ҳ̫���˰ɣ����������룺" << endl;
			continue;
		}
		for (unsigned int i = 0; i < w[NUM].name.size(); i++)
		{
			if (w[NUM].name[i] >= 48 && w[NUM].name[i] <= 57){
				cout << "˭�����������ְ������������룺" << endl;break;
			}
			else if (w[NUM].name[0] >= 97 && w[NUM].name[0] <= 122){
				cout << "����ĸ���д�����������룺" << endl; break;
			}
			else f = 0;
		}
	}
	f = 1;
	while (f){
		cout << "�Ա�:"; cin >> w[NUM].sex;
		if (w[NUM].sex == "��" || w[NUM].sex == "Ů")
			f = 0;
		else
			cout << "�ѵ��Ǵ�˵�еĵ������Ա����������루��/Ů����" << endl;
	}
	f = 1;
	while (f){
		cout << "ѧ��(Сѧ/����/��ר/����/ר��/����/˶ʿ/��ʿ/��ʿ��):"; cin >> w[NUM].edu;
		if (w[NUM].edu == "Сѧ" || w[NUM].edu == "����" || w[NUM].edu == "��ר" || w[NUM].edu == "����" || w[NUM].edu == "ר��" ||
			w[NUM].edu == "����" || w[NUM].edu == "˶ʿ" || w[NUM].edu == "��ʿ" || w[NUM].edu == "��ʿ��")
			f = 0;
		else
			cout << "��������ȷ��ѧ����" << endl;
	}
	f = 1;
	while (f){
		cout << "����:"; cin >> w[NUM].age;
		if (w[NUM].age >= 16 && w[NUM].age <=60)
			f = 0;
		else
			cout << "��������ȷ������(16~60)��" << endl;
	}
	f = 1;
	while (f){
		cout << "��н:"; cin >> w[NUM].salary;
		if (w[NUM].salary >= 0)
			if (w[NUM].salary >= 1250)//1250��2015�й���͹��ʣ����Ϊ�����У�
				f = 0;
			else
				cout << "ְ�������ƺ��������͹���͹��ʣ����������룺" << endl;
		else
			cout << "�����Ǹ��ĵö�ң����������룺" << endl;
	}
	f = 1;
	cout << "��ַ:"; cin >> w[NUM].address;
	while (f){
		cout << "�绰:"; cin >> w[NUM].tel;
		if (w[NUM].tel.size() == 11 || w[NUM].tel.size() == 8)
			f = 0;
		else
			cout << "��������ȷλ���ĺ��룺" << endl;
	}
	w[NUM].GetTax();
	w[NUM].GetPay();
	++NUM;
	++count;
}
//��ȡ����ʾְ����Ϣ����ǰ�������������Ϣ��
void Workers::Showcur()
{
	if (count == 0)
	{
		cout << "û��ְ����Ϣ���룬ϵͳ���������˵�" << endl;
		return;
	}
	cout << "��ǰ�����ְ����Ϣ���£�" << endl;
	cout << "����\t����\t�Ա�\tѧ��\t����\t��ַ\t�绰\t\tʵ������" << endl;
	for (int i = 0; i < NUM; i++)
	{
		cout << w[i].ID << '\t' << w[i].name << '\t' << w[i].sex << '\t' << w[i].edu << '\t' << w[i].age;
		cout << '\t' << w[i].address << '\t' << w[i].tel << '\t' << w[i].pay << endl;
	}
}
//ְ����Ϣ�����ļ�����
void Workers::Save()
{
	if (NUM == 0)
	{
		cout << "û��ְ����Ϣ���룬ϵͳ���������˵�" << endl;
		return;
	}
	else
	{
		ofstream fout,foutp;
		fout.open("E:\\worker.txt", ios_base::trunc);
		if (!fout){
			cout << "File open error!\n";
			exit(1);
		}
		SetFileAttributes(L"E:\\password.txt", FILE_ATTRIBUTE_NORMAL);
		foutp.open("E:\\password.txt", ios_base::trunc);
		if (!foutp){
			cout << "File open error!\n";
			SetFileAttributes(L"E:\\password.txt", FILE_ATTRIBUTE_HIDDEN);
			exit(1);
		}
		cout << "�ļ����ڱ���......���Ժ򣡣�" << endl;
		cout << "���ݱ���ɹ�������" << endl;
		for (int i = 0; i < NUM; i++)
		{
			fout << w[i].ID << '\t' << w[i].name << '\t' << w[i].sex << '\t' << w[i].edu << '\t' << w[i].age;
			fout << '\t' << w[i].address << '\t' << w[i].tel << '\t' << w[i].salary << '\t' << w[i].tax << '\t' << w[i].pay << endl;
			foutp << w[i].Pw << endl;
		}
		this->Showsaved();
		cout << "ϵͳ�������˵���" << endl;
		fout.close();
		foutp.close();
		SetFileAttributes(L"E:\\password.txt", FILE_ATTRIBUTE_HIDDEN);
	}
}
//����ְ����Ϣ��������������Ϊ�Ѿ��������ļ��е�ְ����
void Workers::Search()
{
	int flag = 1;
	int first = 1;
	buffer = NUM;
	this->Num();
	if (NUM == 0)
	{
		cout << "û��ְ����Ϣ���룬ϵͳ���������˵�" << endl;
		NUM = buffer;
		return;
	}
	Searchmenu();
	cout << endl;
	cout << "��ѡ�����ֱ��0~6" << endl;
	int choice5;
	cin >> choice5;
	while (choice5<0 || choice5>6)
	{
		cout << "�����������������룺" << endl;
		cin >> choice5;
	}
	if (choice5 == 1)
	{
		string id;
		cout << "������Ҫ��ѯ��ְ���Ĺ��ţ�" << endl;
		cin >> id;
		while (flag)
		{
			for (int j=0; j<NUM; j++)
			{
				if (id == w[j].ID)
				{
					int k = j;
					if (first){
						flag = 0;
						cout << "��ѯ��ְ����Ϣ���£�" << endl;
						cout << "����\t����\t�Ա�\tѧ��\t����\t��ַ\t�绰\t\tʵ������" << endl;
						cout << w[k].ID << '\t' << w[k].name << '\t' << w[k].sex << '\t' << w[k].edu << '\t' << w[k].age;
						cout << '\t' << w[k].address << '\t' << w[k].tel << '\t' << w[k].pay << endl;
						first = 0;
						NUM = buffer;
					}
					else{
						cout << w[k].ID << '\t' << w[k].name << '\t' << w[k].sex << '\t' << w[k].edu << '\t' << w[k].age;
						cout << '\t' << w[k].address << '\t' << w[k].tel << '\t' << w[k].pay << endl;
					}
				}
			}
			if (flag)
			{
				flag = 0;
				cout << "������������ְ��!!\n�������˵�" << endl;
				NUM = buffer;
				break;
			}
		}
		flag = 1;
		first = 1;
	}
	else if (choice5 == 2)
	{
		string name;
		cout << "������Ҫ��ѯ��ְ����������" << endl;
		cin >> name;
		while (flag)
		{
			for (int j = 0; j<NUM; j++)
			{
				if (name == w[j].name)
				{
					int k = j;
					if (first){
						flag = 0;
						cout << "��ѯ��ְ����Ϣ���£�" << endl;
						cout << "����\t����\t�Ա�\tѧ��\t����\t��ַ\t�绰\t\tʵ������" << endl;
						cout << w[k].ID << '\t' << w[k].name << '\t' << w[k].sex << '\t' << w[k].edu << '\t' << w[k].age;
						cout << '\t' << w[k].address << '\t' << w[k].tel << '\t' << w[k].pay << endl;
						first = 0;
						NUM = buffer;
					}
					else{
						cout << w[k].ID << '\t' << w[k].name << '\t' << w[k].sex << '\t' << w[k].edu << '\t' << w[k].age;
						cout << '\t' << w[k].address << '\t' << w[k].tel << '\t' << w[k].pay << endl;
					}
				}
			}
			if (flag)
			{
				flag = 0;
				cout << "������������ְ��!!\n�������˵�" << endl;
				NUM = buffer;
				break;
			}
		}
		flag = 1;
		first = 1;
	}
	else if (choice5 == 3)
	{
		double salary;
		cout << "������Ҫ��ѯ��ְ���Ĺ��ʣ�" << endl;
		cin >> salary;
		while (flag)
		{
			for (int j = 0; j<NUM; j++)
			{
				if (salary== w[j].salary)
				{
					int k = j;
					if (first){
						flag = 0;
						cout << "��ѯ��ְ����Ϣ���£�" << endl;
						cout << "����\t����\t�Ա�\tѧ��\t����\t��ַ\t�绰\t\tʵ������" << endl;
						cout << w[k].ID << '\t' << w[k].name << '\t' << w[k].sex << '\t' << w[k].edu << '\t' << w[k].age;
						cout << '\t' << w[k].address << '\t' << w[k].tel << '\t' << w[k].pay << endl;
						first = 0;
						NUM = buffer;
					}
					else{
						cout << w[k].ID << '\t' << w[k].name << '\t' << w[k].sex << '\t' << w[k].edu << '\t' << w[k].age;
						cout << '\t' << w[k].address << '\t' << w[k].tel << '\t' << w[k].pay << endl;
					}
				}
			}
			if (flag)
			{
				flag = 0;
				cout << "������������ְ��!!\n�������˵�" << endl;
				NUM = buffer;
				break;
			}
		}
		flag = 1;
		first = 1;
	}
	else if (choice5 == 4)
	{
		string edu;
		cout << "������Ҫ��ѯ��ְ����ѧ����" << endl;
		cin >> edu;
		while (flag)
		{
			for (int j = 0; j<NUM; j++)
			{
				if (edu== w[j].edu)
				{
					int k = j;
					if (first){
						flag = 0;
						cout << "��ѯ��ְ����Ϣ���£�" << endl;
						cout << "����\t����\t�Ա�\tѧ��\t����\t��ַ\t�绰\t\tʵ������" << endl;
						cout << w[k].ID << '\t' << w[k].name << '\t' << w[k].sex << '\t' << w[k].edu << '\t' << w[k].age;
						cout << '\t' << w[k].address << '\t' << w[k].tel << '\t' << w[k].pay << endl;
						first = 0;
						NUM = buffer;
					}
					else{
						cout << w[k].ID << '\t' << w[k].name << '\t' << w[k].sex << '\t' << w[k].edu << '\t' << w[k].age;
						cout << '\t' << w[k].address << '\t' << w[k].tel << '\t' << w[k].pay << endl;
					}
				}
			}
			if (flag)
			{
				flag = 0;
				cout << "������������ְ��!!\n�������˵�" << endl;
				NUM = buffer;
				break;
			}
		}
		flag = 1;
		first = 1;
	}
	else if (choice5 == 5)
	{
		int  age;
		cout << "������Ҫ��ѯ��ְ�������䣺" << endl;
		cin >>age;
		while (flag)
		{
			for (int j = 0; j<NUM; j++)
			{
				if (age == w[j].age)
				{
					int k = j;
					if (first){
						flag = 0;
						cout << "��ѯ��ְ����Ϣ���£�" << endl;
						cout << "����\t����\t�Ա�\tѧ��\t����\t��ַ\t�绰\t\tʵ������" << endl;
						cout << w[k].ID << '\t' << w[k].name << '\t' << w[k].sex << '\t' << w[k].edu << '\t' << w[k].age;
						cout << '\t' << w[k].address << '\t' << w[k].tel << '\t' << w[k].pay << endl;
						first = 0;
						NUM = buffer;
					}
					else{
						cout << w[k].ID << '\t' << w[k].name << '\t' << w[k].sex << '\t' << w[k].edu << '\t' << w[k].age;
						cout << '\t' << w[k].address << '\t' << w[k].tel << '\t' << w[k].pay << endl;
					}
				}
			}
			if (flag)
			{
				flag = 0;
				cout << "������������ְ��!!\n�������˵�" << endl;
				NUM = buffer;
				break;
			}
		}
		flag = 1;
		first = 1;
	}
	else if (choice5 == 6)
	{
		string address;
		cout << "������Ҫ��ѯ��ְ���ĵ�ַ��" << endl;
		cin >> address;
		while (flag)
		{
			for (int j = 0; j<NUM; j++)
			{
				if (address == w[j].address)
				{
					int k = j;
					if (first){
						flag = 0;
						cout << "��ѯ��ְ����Ϣ���£�" << endl;
						cout << "����\t����\t�Ա�\tѧ��\t����\t��ַ\t�绰\t\tʵ������" << endl;
						cout << w[k].ID << '\t' << w[k].name << '\t' << w[k].sex << '\t' << w[k].edu << '\t' << w[k].age;
						cout << '\t' << w[k].address << '\t' << w[k].tel << '\t' << w[k].pay << endl;
						first = 0;
						NUM = buffer;
					}
					else{
						cout << w[k].ID << '\t' << w[k].name << '\t' << w[k].sex << '\t' << w[k].edu << '\t' << w[k].age;
						cout << '\t' << w[k].address << '\t' << w[k].tel << '\t' << w[k].pay << endl;
					}
				}
			}
			if (flag)
			{
				flag = 0;
				cout << "������������ְ��!!\n�������˵�" << endl;
				NUM = buffer;
				break;
			}
		}
	}
	else if (choice5 == 0)
		return ;
}
//ְ����Ϣ�޸ĺ���
void Workers::Amend()
{
	buffer = NUM;
	this->Num();
	if (NUM == 0)
	{
		cout << "û��ְ����Ϣ���룬ϵͳ���������˵�" << endl;
		NUM = buffer;
		return;
	}
	this->Showsaved();
	cout << "��������Ҫ�޸���Ϣְ���Ĺ��ţ�" << endl;
	string num1;
	cin >> num1;
	int j = 0, k;
	int flag = 1;
	while (flag)
	{
		for (; j<NUM; j++)
		{
			if (num1 == w[j].ID)
			{
				flag = 0;
				k = j;
				break;
			}
		}
		if (flag)
		{
			cout << "�����ڴ�Ա�������������룺" << endl;
			j = 0;
			cin >> num1;
		}
		NUM = buffer;
	}
	cout << "��ѡ���ְ������ϢΪ��" << endl;
	cout << "����\t����\t�Ա�\tѧ��\t����\t��ַ\t�绰\t\tʵ������" << endl;
	cout << w[k].ID << '\t' << w[k].name << '\t' << w[k].sex << '\t' << w[k].edu << '\t' << w[k].age;
	cout << '\t' << w[k].address << '\t' << w[k].tel << '\t'  <<w[k].pay<<endl;
	Amendmenu();
	cout << endl;
	cout << "��ѡ�����ֱ��0~8" << endl;
	int choice6;
	cin >> choice6;
	while (choice6<0 || choice6>8)
	{
		cout << "�����������������룺" << endl;
		cin >> choice6;
	}
	switch (choice6)
	{
	case 1:
		cout << "�������µ�ְ������:";
		cin >> w[k].ID;
		cout << "�޸���Ϣ�ѱ��棺" << endl;
		break;
	case 2:
		cout << "�������µ�ְ������:";
		cin >> w[k].name;
		cout << "�޸���Ϣ�ѱ��棺" << endl;
		break;
	case 3:
		cout << "�������µ�ְ���Ա�:";
		cin >> w[k].sex;
		cout << "�޸���Ϣ�ѱ��棺" << endl;
		break;
	case 4:
		cout << "�������µ�ְ��ѧ��:";
		cin >> w[k].edu;
		cout << "�޸���Ϣ�ѱ��棺" << endl;
		break;
	case 5:
		cout << "�������µ�ְ������:";
		cin >> w[k].age;
		cout << "�޸���Ϣ�ѱ��棺" << endl;
		break;
	case 6:
		cout << "�������µ�ְ����н:";
		cin >> w[k].salary;
		w[k].GetTax();
		w[k].GetPay();
		cout << "�޸���Ϣ�ѱ��棺" << endl;
		break;
	case 7:
		cout << "�������µ�ְ����ַ:";
		cin >> w[k].address;
		cout << "�޸���Ϣ�ѱ��棺" << endl;
		break;
	case 8:
		cout << "�������µ�ְ���绰:";
		cin >> w[k].tel;
		cout << "�޸���Ϣ�ѱ��棺" << endl;
		break;
	case 0:
		break;
	default:
		break;
	}
	this->Save();
}
//ְ����Ϣ������
void Workers::Sort()
{
	buffer = NUM;
	this->Num();
	if (NUM == 0)
	{
		cout << "û��ְ����Ϣ���룬ϵͳ���������˵�" << endl;
		NUM = buffer;
		return;
	}
	else
	{
		cout << "��ѡ������ʽ��" << endl;
		cout << "               ***********************************************" << endl;
		cout << "               **            1.��������������         **" << endl;
		cout << "               **            2.���������򣨽���          **" << endl;
		cout << "               **            3.��������������          **" << endl;
		cout << "               **            4.���������򣨽���          **" << endl;
		cout << "               **            5.��������������          **" << endl;
		cout << "               **            6.���������򣨽���          **" << endl;
		cout << "               **            0.�������˵�                  **" << endl;
		cout << "               ***********************************************" << endl;
		cout << endl;
		cout << "��ѡ�����ֱ��0~6" << endl;
		int choice2;
		cin >> choice2;
		while (choice2 < 0 || choice2>6)
		{
			cout << "�����������������룺" << endl;
			cin >> choice2;
		}
		if (choice2 == 1)
		{
			int i, j;
			for (i = 0; i < NUM - 1; i++)
				for (j = 0; j < NUM - 1 - i; j++)
					if (w[j].ID.size()>w[j + 1].ID.size() || (w[j].ID.size() == w[j + 1].ID.size() && w[j].ID > w[j + 1].ID))
					{
						Worker *temp = new Worker(w[j]);
						w[j] = w[j + 1];
						w[j + 1] = *temp;
						delete temp;
					}
			cout << "��������������Ϣ���£�" << endl;
			cout << "����\t����\t�Ա�\tѧ��\t����\t��ַ\t�绰\t\tʵ������" << endl;
			for (i = 0; i < NUM; i++)
			{
				cout << w[i].ID << '\t' << w[i].name << '\t' << w[i].sex << '\t' << w[i].edu << '\t' << w[i].age;
				cout << '\t' << w[i].address << '\t' << w[i].tel << '\t'<< w[i].pay << endl;
			}
		}
		else if (choice2 == 2)
		{
			int i, j;
			for (i = 0; i < NUM - 1; i++)
				for (j = 0; j < NUM - 1 - i; j++)
					if (w[j].ID.size()<w[j + 1].ID.size() || (w[j].ID.size() == w[j + 1].ID.size() && w[j].ID < w[j + 1].ID))
					{
						Worker *temp = new Worker(w[j]);
						w[j] = w[j + 1];
						w[j + 1] = *temp;
						delete temp;
					}
			cout << "�����Ž�������Ϣ���£�" << endl;
			cout << "����\t����\t�Ա�\tѧ��\t����\t��ַ\t�绰\t\tʵ������" << endl;
			for (i = 0; i < NUM; i++)
			{
				cout << w[i].ID << '\t' << w[i].name << '\t' << w[i].sex << '\t' << w[i].edu << '\t' << w[i].age;
				cout << '\t' << w[i].address << '\t' << w[i].tel << '\t'   << w[i].pay << endl;
			}
		}
		else if (choice2 == 3)
		{
			int i, j;
			for (i = 0; i < NUM - 1; i++)
				for (j = 0; j < NUM - 1 - i; j++)
					if (w[j].name > w[j + 1].name)
					{
						Worker *temp = new Worker(w[j]);
						w[j] = w[j + 1];
						w[j + 1] = *temp;
						delete temp;
					}
			cout << "��������������Ϣ���£�" << endl;
			cout << "����\t����\t�Ա�\tѧ��\t����\t��ַ\t�绰\t\tʵ������" << endl;
			for (i = 0; i < NUM; i++)
			{
				cout << w[i].ID << '\t' << w[i].name << '\t' << w[i].sex << '\t' << w[i].edu << '\t' << w[i].age;
				cout << '\t' << w[i].address << '\t' << w[i].tel << '\t'<< w[i].pay << endl;
			}
		}
		else if (choice2 == 4)
		{
			int i, j;
			for (i = 0; i < NUM - 1; i++)
				for (j = 0; j < NUM - i - 1; j++)
					if (w[j].name < w[j + 1].name)
					{
						Worker *temp = new Worker(w[j]);
						w[j] = w[j + 1];
						w[j + 1] = *temp;
						delete temp;
					}
			cout << "��������������Ϣ���£�" << endl;
			cout << "����\t����\t�Ա�\tѧ��\t����\t��ַ\t�绰\t\tʵ������" << endl;
			for (i = 0; i < NUM; i++)
			{
				cout << w[i].ID << '\t' << w[i].name << '\t' << w[i].sex << '\t' << w[i].edu << '\t' << w[i].age;
				cout << '\t' << w[i].address << '\t' << w[i].tel << '\t'  << w[i].pay << endl;
			}
		}
		else if (choice2 == 5)
		{
			int i, j;
			for (i = 0; i < NUM - 1; i++)
				for (j = 0; j < NUM - i - 1; j++)
					if (w[j].pay > w[j + 1].pay)
					{
						Worker *temp = new Worker(w[j]);
						w[j] = w[j + 1];
						w[j + 1] = *temp;
						delete temp;
					}
			cout << "��������������Ϣ���£�" << endl;
			cout << "����\t����\t�Ա�\tѧ��\t����\t��ַ\t�绰\t\tʵ������" << endl;
			for (i = 0; i < NUM; i++)
			{
				cout << w[i].ID << '\t' << w[i].name << '\t' << w[i].sex << '\t' << w[i].edu << '\t' << w[i].age;
				cout << '\t' << w[i].address << '\t' << w[i].tel << '\t'<< w[i].pay << endl;
			}
		}
		else if (choice2 == 6)
		{
			int i, j;
			for (i = 0; i < NUM - 1; i++)
				for (j = 0; j < NUM - i - 1; j++)
					if (w[j].pay < w[j + 1].pay)
					{
						Worker *temp = new Worker(w[j]);
						w[j] = w[j + 1];
						w[j + 1] = *temp;
						delete temp;
					}
			cout << "�����ʽ�������Ϣ���£�" << endl;
			cout << "����\t����\t�Ա�\tѧ��\t����\t��ַ\t�绰\t\tʵ������" << endl;
			for (i = 0; i < NUM; i++)
			{
				cout << w[i].ID << '\t' << w[i].name << '\t' << w[i].sex << '\t' << w[i].edu << '\t' << w[i].age;
				cout << '\t' << w[i].address << '\t' << w[i].tel << '\t'<< w[i].pay << endl;
			}
		}
		else if (choice2 == 0)
			return;
	}
	ofstream fout;
	fout.open("E:\\worker.txt", ios_base::ate);
	if (!fout){
		cout << "File open error!\n";
		exit(1);
	}
	cout << "�ļ����ڱ���......���Ժ򣡣�" << endl;
	cout << "���ݱ���ɹ�������" << endl;
	for (int i = 0; i < NUM; i++)
	{
		fout << w[i].ID << '\t' << w[i].name << '\t' << w[i].sex << '\t' << w[i].edu << '\t' << w[i].age;
		fout << '\t' << w[i].address << '\t' << w[i].tel << '\t' << w[i].salary << '\t' << w[i].tax << '\t' << w[i].pay << endl;
	}
	cout << "ϵͳ�������˵���" << endl;
	fout.close();
	NUM = buffer;
}
// ְ����Ϣɾ������
void Workers::Delete()
{
	if (NUM == 0)
	{
		cout << "û��ְ����Ϣ���룬ϵͳ���������˵�" << endl;
		return;
	}
	else
	{
		ofstream fout, foutp;
		fout.open("E:\\worker.txt", ios_base::trunc);
		if (!fout){
			cout << "File open error!\n";
			exit(1);
		}
		SetFileAttributes(L"E:\\password.txt", FILE_ATTRIBUTE_NORMAL);
		foutp.open("E:\\password.txt", ios_base::trunc);
		if (!foutp){
			cout << "File open error!\n";
			SetFileAttributes(L"E:\\password.txt", FILE_ATTRIBUTE_HIDDEN);
			exit(1);
		}
		cout << "�ļ����ڱ���......���Ժ򣡣�" << endl;
		cout << "���ݱ���ɹ�������" << endl;
		for (int i = 0; i < NUM; i++)
		{
			fout << w[i].ID << '\t' << w[i].name << '\t' << w[i].sex << '\t' << w[i].edu << '\t' << w[i].age;
			fout << '\t' << w[i].address << '\t' << w[i].tel << '\t' << w[i].salary << '\t' << w[i].tax << '\t' << w[i].pay << endl;
			foutp << w[i].Pw << endl;
		}
		this->Showsaved();
		fout.close();
		foutp.close();
		SetFileAttributes(L"E:\\password.txt", FILE_ATTRIBUTE_HIDDEN);
	}
	int buffer0 = NUM;
	this->Num();
	if (NUM == 0)
	{
		cout << "û��ְ����Ϣ���룬ϵͳ���������˵�" << endl;
		NUM = buffer0;
		return;
	}
	cout << "��������Ҫɾ����Ϣְ���Ĺ��ţ�" << endl;
	string delid;
	cin >> delid;
	int k;
	int flag = 1;
	while (flag)
	{
		for (int i=0; i<NUM;i++)
		{
			if (delid == w[i].ID)
			{
				flag = 0;
				k = i;
				break;
			}
		}
		if (flag)
		{
			cout << "�����ڴ�Ա�������������룺" << endl;
			cin >> delid;
		}
	}
	cout << "��ѡ���ְ������ϢΪ��" << endl;
	cout << "����\t����\t�Ա�\tѧ��\t����\t��ַ\t�绰\t\tʵ������" << endl;
	cout << w[k].ID << '\t' << w[k].name << '\t' << w[k].sex << '\t' << w[k].edu << '\t' << w[k].age;
	cout << '\t' << w[k].address << '\t' << w[k].tel << '\t' << w[k].pay << endl;
	cout << "ȷ��������Y\t�������˵�������N " << endl;
	string p;
	cin >> p;
	while (1)
	{
		if (p == "y" || p == "Y")
		{
			cout << "Ա����Ϣ��ɾ����" << endl;
			for (int i = 0; i < NUM; i++)
			{
				int j=0;
				if (w[i].ID == delid)
				{
					j = i;
					for (; j < NUM; j++)
						w[j] = w[j + 1];
					NUM--;
				}
			}
			ofstream fout,foutp;
			fout.open("E:\\worker.txt", ios_base::trunc);
			if (!fout){
				cout << "File open error!\n";
				exit(1);
			}
			SetFileAttributes(L"E:\\password.txt", FILE_ATTRIBUTE_NORMAL);
			foutp.open("E:\\password.txt", ios_base::trunc);
			if (!foutp){
				cout << "File open error!\n";
				SetFileAttributes(L"E:\\password.txt", FILE_ATTRIBUTE_HIDDEN);
				exit(1);
			}
			cout << "�ļ����ڱ���......���Ժ򣡣�" << endl;
			cout << "���ݱ���ɹ�������" << endl;
			for (int i = 0; i < NUM; i++)
			{
				fout << w[i].ID << '\t' << w[i].name << '\t' << w[i].sex << '\t' << w[i].edu << '\t' << w[i].age;
				fout << '\t' << w[i].address << '\t' << w[i].tel << '\t' << w[i].salary << '\t' << w[i].tax << '\t' << w[i].pay << endl;
				foutp << w[i].Pw << endl;
			}
			this->Showsaved();
			cout << "ϵͳ�������˵���" << endl;
			fout.close();
			foutp.close();
			SetFileAttributes(L"E:\\password.txt", FILE_ATTRIBUTE_HIDDEN);
			break;
		}
		else if (p == "n" || p == "N")
		{
			NUM = buffer0;
			return;
		}
		else
		{
			cout << "�����������������룺";
			cin >> p;
		}
	}
	NUM = buffer0;
}
//ְ����Ϣ��ʾ��������ʾ�ļ��е����ݣ�
void Workers::Showsaved()
{
	buffer = NUM;
	this->Num();
	if (NUM==0)
	{
		cout << "ְ���ĵ�Ϊ�գ�ϵͳ���������˵�" << endl;
		NUM = buffer;
		return;
	}
	else
	{
		NUM = buffer;
		ifstream in("E:\\worker.txt");
		if (!in){
			cout << "File open error!\n";
			exit(1);
		}
		cout << "�ѱ����ְ����Ϣ���£�" << endl;
		cout << "����\t����\t�Ա�\tѧ��\t����\t��ַ\t�绰\t\tʵ������" << endl;
		if (NUM == count)
			for (int i = 0; i < count; i++)
			{
				in >> w[i].ID >> w[i].name >> w[i].sex >> w[i].edu >> w[i].age >> w[i].address >> w[i].tel >> w[i].salary >> w[i].tax >> w[i].pay;
				cout << w[i].ID << '\t' << w[i].name << '\t' << w[i].sex << '\t' << w[i].edu << '\t' << w[i].age;
				cout << '\t' << w[i].address << '\t' << w[i].tel << '\t' << w[i].pay << endl;
			}
		else
			for (int i = 0; i < NUM; i++)
		{
			in >> w[i].ID >> w[i].name >> w[i].sex >> w[i].edu >> w[i].age >> w[i].address >> w[i].tel >> w[i].salary >> w[i].tax >> w[i].pay;
			cout << w[i].ID << '\t' << w[i].name << '\t' << w[i].sex << '\t' << w[i].edu << '\t' << w[i].age;
			cout << '\t' << w[i].address << '\t' << w[i].tel <<'\t'<< w[i].pay << endl;
		}
		in.close();
	}
}
//���ְ������
string Workers::GetID(int i)
{
	return w[i].ID;
}
//�û���¼ʱ��ʾ��ǰ�û���Ϣ
void Workers::Show(int i)
{
	w[i].Show();
}
//��ȡĳ��ְ��������
char * Workers::GetPw(int l)
{
	return w[l].Pw;
}
//ͳ����Ϣ������ʾ
void Workers::Total()
{
	buffer = NUM;
	this->Num();
	for (int i = 0; i < NUM; i++)
	{
		tsalary += w[i].salary;
		ttax += w[i].tax;
	}
	cout << "\nְ������\t��������\t˰������" << endl;
	cout << NUM << "\t\t"<< tsalary << "\t\t" << ttax << endl;
	NUM = buffer;
}
//�û��޸�����
void Workers::ChangePw()
{
	buffer = NUM;
	this->Num();
	char password;
	char pw[20];
	int error = 0;
	bool back = 0;
	bool out = 0;
	do{
		do{
			cout << "\n�������޸�ǰ�����룺" << endl;
			for (int j = 0; j < 20; j++)
			{
				password = getch();
				if (password == 13)
				{
					pw[j] = '\0';
					break;
				}
				if (password == 8)
				{
					cout << '\b' << ' ' << '\b';
					j -= 2;
				}
				else
				{
					pw[j] = password;
					cout << '*';
				}
			}
			if (strcmp(pw, w[loc].Pw) == 0)
			{
				char *p = new char[50];
				char p1[20];
				while (1){
					cout << "\n������������(ע�����볤������6λ�������ó���20λ����" << endl;
					for (int i = 0; i < 50; i++){
						password = getch();
						if (password == 13)
						{
							p[i] = '\0';
							break;
						}
						if (password == 8)
						{
							cout << '\b' << ' ' << '\b';
							i -= 2;
						}
						else
						{
							p[i] = password;
							cout << '*';
						}
					}
					if (strlen(p) > 20)
						cout << "\n������������������룺" << endl;
					else if (strlen(p) < 6)
						cout << "\n������̣����������룺" << endl;
					else
						break;
				}
				while (1){
					cout << "\n���ٴ����������룺" << endl;
					for (int i = 0; i < 20; i++){
						password = getch();
						if (password == 13)
						{
							p1[i] = '\0';
							break;
						}
						if (password == 8)
						{
							cout << '\b' << ' ' << '\b';
							i -= 2;
						}
						else
						{
							p1[i] = password;
							cout << '*';
						}
					}
					if (strcmp(p1, p) == 0){
						strcpy(w[loc].Pw, p1);
						ofstream fout;
						SetFileAttributes(L"E:\\password.txt", FILE_ATTRIBUTE_NORMAL);
						fout.open("E:\\password.txt", ios_base::trunc);
						if (!fout){
							cout << "File open error!\n";
							SetFileAttributes(L"E:\\password.txt", FILE_ATTRIBUTE_HIDDEN);
							exit(1);
						}
						for (int i = 0; i < NUM; i++)
						{
							fout <<  w[i].Pw <<'\t'<< endl;
						}
						fout.close();
						SetFileAttributes(L"E:\\password.txt", FILE_ATTRIBUTE_HIDDEN);
						back = 0; 
						out = 1;
						cout << "\n�����޸ĳɹ���" << endl;
						Sleep(1000);
						break;
					}
					else{
						cout << "\n�������벻��ͬ " << endl;
						cout << "�Ƿ���Ҫ���أ�" << endl;
						cout << "��(Y)      ��(N)" << endl;
						char choice4;
						cin >> choice4;
						while (1){
							if (choice4 == 'y' || choice4 == 'Y'){
								back = 1; break;
							}
							else if (choice4 = 'n' || choice4 == 'N') {
								back = 0; out = 1; break;
							}
							else{
								cout << "\n��������������Y/N(y/n):" << endl;
								cin >> choice4;
							}
						}
						if (!back)break;
						else continue;
					}
				}
				delete[]p;
			}
			else
			{
				error++;
				if (error == 3)
				{
					for (int i = 10; i >= 0; i--)
					{
						system("cls");
						cout << "\n     ****************************************************" << endl;
						cout << "     **�������3�Σ�ϵͳ" << setw(2) << i << "����Զ��˳������Ժ����µ�¼**" << endl;
						cout << "     *******************************************************" << endl;
						Sleep(1000);
					}
					exit(1);
				}
				cout << "\n�����������������" << endl;
				Sleep(1000);
			}
		} while (error < 3&&!out);
	} while (back);
	NUM = buffer;
	cout << endl;
}
//main��������ִ�к���Execute()
int main()
{
	system("COLOR 30");
	Execute();
	SetFileAttributes(L"E:\\password.txt", FILE_ATTRIBUTE_HIDDEN);
	return 0;
}