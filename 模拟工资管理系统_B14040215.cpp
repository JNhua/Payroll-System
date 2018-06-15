//管理员：
//1）以密码登录系统
//2）录入员工信息具体工资，计算相应的税金（计算规则参见最新公布的政策）
//3）查询并显示所有的员工具体信息
//4）显示统计信息：员工数目，工资总数和税金总数
//4）按照指定条件查询
//5）增删具体员工记录
//税金政策基本是不同收入等级的工资使用不同的比例收取税金。类似于下表：
//工资		税金
//0～1500		0％
//1500～2500	10％（超出部分）
//2500～3500	15％（超出部分）
//3500～5000	20％（超出部分）
//5000～10000	30％（超出部分）
//10000～		40％（超出部分）
//     员工：
//1）	以工号为登录ID，密码自己设定；
//2）	可以查询本人的相关信息；
//3）	系统提供指定时间间隔的查询功能。

//管理员密码为B14040215，用户登录ID为工号,初始密码为0215
#include<iostream>
#include<string>
#include<fstream>
#include <cstdlib>    //exit()
#include<conio.h>   //getch()
#include<windows.h>  //SetFileAttributes()
#include<iomanip>   //setw(2)
using namespace std;
const int N = 100;//N作为最大职工总数
int buffer = 0;//职工数量的缓存
int loc = -1;//记录用户登录时用户的ID下标

//职工 类
class Worker
{
public:
	Worker(){
		age = 0; salary = 0; tax = 0; pay = 0;
		strcpy(Pw,"0215");
	}
	~Worker(){}
	void Show();//职工信息显示
	double GetTax();  // 获取缴税
	double GetPay();  // 获取实发工资
	friend class Workers;
private:
	string ID, name, sex, edu, address, tel;//工号，姓名，性别，教育程度，住址，电话
	int age;//年龄
	double salary,tax, pay;//月薪，税金，实际收入
	char Pw[20];//职工密码
};
//职工群 类
class Workers
{
private:
	Worker w[N];
	int NUM;//用来计算职工数目
	int count;// 用来计算当前程序新添加的职工数目
	double tsalary = 0, ttax = 0;// 工资总数，税金总数
public:
	int  Num();//计算并返回文件已包含的职工数量
	void add();//职工信息添加
	void Sort();//职工信息排序
	void Search();//查找职工信息函数（查找内容为已经保存在文件中的职工）
	void Delete();//职工信息删除
	void Amend();//职工信息修改
	void Save();//职工信息以文件形式保存
	void Showsaved();//职工信息显示函数（显示文件中的内容）
	void Showcur();//读取并显示职工信息（当前程序中输入的信息）
	Workers()
	{
		NUM = 0;
		count = 0;
	}
	string GetID(int);//获得职工工号
	char * GetPw(int);//获取职工旧密码
	void Show(int );//用户登录时显示当前用户信息
	void Total();//统计信息并且显示
	void ChangePw();//用户修改密码
};

//登陆函数
void loginmenu()
{
	system("cls");
	cout << "\n\n              *************************************************" << endl;
	cout << "              **            请选择您所需要的模式             **" << endl;
	cout << "              **                1.管理员模式                 **" << endl;
	cout << "              **                2.用户模式                   **" << endl;
	cout << "              *************************************************" << endl;


}
//管理员菜单
void admenu()
{

	cout << endl;
	cout << "        **************************************************************" << endl;
	cout << "        **                                                          **" << endl;
	cout << "        **        ===欢迎使用南京邮电大学职工工资管理系统===        **" << endl;
	cout << "        **                                                          **" << endl;
	cout << "        **                   1.职工信息添加                         **" << endl;
	cout << "        **                   2.当前信息查看                         **" << endl;
	cout << "        **                   3.职工信息保存                         **" << endl;
	cout << "        **                   4.职工信息查找                         **" << endl;
	cout << "        **                   5.职工信息修改                         **" << endl;
	cout << "        **                   6.职工信息排序                         **" << endl;
	cout << "        **                   7.职工信息删除                         **" << endl;
	cout << "        **                   8.已存信息显示                         **" << endl;
	cout << "        **                   9.职工信息统计                         **" << endl;
	cout << "        **                   0.退出                                 **" << endl;
	cout << "        **                                                          **" << endl;
	cout << "        **************************************************************" << endl;
	cout << endl;
}
//用户菜单
void usermenu()
{

	cout << endl;
	cout << "        **************************************************************" << endl;
	cout << "        **                                                          **" << endl;
	cout << "        **        ===欢迎使用南京邮电大学职工工资管理系统===        **" << endl;
	cout << "        **                                                          **" << endl;
	cout << "        **                   1.信息查询                             **" << endl;
	cout << "        **                   2.修改密码                             **" << endl;
	cout << "        **                   0.退出                                 **" << endl;
	cout << "        **                                                          **" << endl;
	cout << "        **************************************************************" << endl;
	cout << endl;
}
//查找函数菜单
void Searchmenu()
{
	cout << "请选择查找方式：" << endl;
	cout << "               ***********************************************" << endl;
	cout << "               **            1.按工号查找                  **" << endl;
	cout << "               **            2.按姓名查找                  **" << endl;
	cout << "               **            3.按工资查找                  **" << endl;
	cout << "               **            4.按学历查找                  **" << endl;
	cout << "               **            5.按年龄查找                  **" << endl;
	cout << "               **            6.按地址查找                  **" << endl;
	cout << "               **            0.返回主菜单                  **" << endl;
	cout << "               ***********************************************" << endl;
}
//修改函数菜单
void Amendmenu()
{
	cout << endl;
	cout << "               ***********************************************" << endl;
	cout << "               **            1.修改工号                    **" << endl;
	cout << "               **            2.修改姓名                    **" << endl;
	cout << "               **            3.修改性别                    **" << endl;
	cout << "               **            4.修改学历                    **" << endl;
	cout << "               **            5.修改年龄                    **" << endl;
	cout << "               **            6.修改工资                    **" << endl;
	cout << "               **            7.修改地址                    **" << endl;
	cout << "               **            8.修改电话                    **" << endl;
	cout << "               **            0.返回主菜单                  **" << endl;
	cout << "               ***********************************************" << endl;
}
//2015最新的税金政策：
//起征点：3500
//全月应纳税所得额                                            税率         速算扣除数(元)
//全月应纳税额不超过1500元                           3 %                     0
//全月应纳税额超过1500元至4500元              10 %                   105
//全月应纳税额超过4500元至9000元              20 %                   555
//全月应纳税额超过9000元至35000元            25 %                  1005
//全月应纳税额超过35000元至55000元          30 %                  2755
//全月应纳税额超过55000元至80000元          35 %                  5505
//全月应纳税额超过80000元                             45 %                 13505
double  Worker::GetTax()  // 缴税
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
void Worker::Show()//显示职工信息函数实现
{
	cout << "工号\t姓名\t性别\t学历\t年龄\t地址\t电话\t\t实际收入" << endl;
	cout << ID << '\t' << name << '\t' << sex << '\t' << edu << '\t' << age << '\t' << address << '\t' << tel << '\t' << GetPay() << endl;
	cout << endl;
}
//主菜单函数实现
void Execute()
{
	string p;//接收菜单选项的字符串
	int error = 0;//标记密码输入错误次数
	char pw[20];//存储输入的密码
	char password;//输入的密码字符
	Workers wl;
	int cnum = wl.Num();//cnum:已保存的职工数
	int choice0;//选择管理员登录或者用户登录
	loginmenu();
	cout << "请输入选择：";
	cin >> choice0;
	switch (choice0)
	{
	case 1:
		do
		{
			cout << endl;
			cout << "管理员登录"<<endl;
			cout << "请输入密码：";
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
				cout << "\n登录成功，祝您工作顺利，心情愉快!" << endl;
				Sleep(2000);
				break;
			}
			else
			{
				error++;
				if (3-error>0)
					cout << "\n你还有" << 3-error << "次机会！" << endl;
				if (error == 3)
				{
					for (int i = 10; i >= 0; i--)
					{
						system("cls");
						cout << "\n     ****************************************************" << endl;
						cout << "     **密码错误3次，系统"<<setw(2)<<i<<"秒后自动退出，请稍后重新登录**" << endl;
						cout << "     *******************************************************" << endl;
						Sleep(1000);
					}
					exit(1);
				}
				cout << "\n密码错误！请重新输入" << endl;
				Sleep(1000);
			}
		} while (error<3);
		while (1)
		{
			system("cls");
			admenu();
			cout << "请选择数字编号0~8" << endl;
			int choice1;//选择管理员菜单的功能
			cin >> choice1;
			while (!(choice1 >= 0 && choice1 <= 9))
			{
				cout << "输入有误，请重新输入：" << endl;
				cin >> choice1;
			}
			switch (choice1)
			{
			case 1:
				wl.add();
				cout << "\n是否希望保存信息？" << endl;
				cout << "是（Y）     否(N)" << endl;
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
						cout << "输入有误，请输入Y/N(y/n):" << endl;
						cin >> choice2;
					}
				}
				break;
			case 2:
				wl.Showcur();//查看当前信息
				break;
			case 3:
				wl.Save();//保存当前信息
				break;
			case 4:
				wl.Search();//查找
				break;
			case 5:
				wl.Amend();//修改
				break;
			case 6:
				wl.Sort();//排序
				break;
			case 7:
				wl.Delete();//删除
				break;
			case 8:
				wl.Showsaved();//查看已存入的信息
				break;
			case 9:
				wl.Total();//统计并查看统计信息
				break;
			case 0:
				cout << "                           你真的想要离开我了吗？" << endl;
				cout << "                       嗯，拜拜（Y）     舍不得(N)" << endl;
				char choice3;
				cin >> choice3;
				while (1)
				{
					if (choice3 == 'y' || choice3 == 'Y'){
						cout << "系统退出！" << endl; 
						exit(0);
					}
					else if (choice3 == 'n' || choice3 == 'N'){
						break;
					}
					else{
						cout << "输入有误，请输入Y/N(y/n):" << endl;
						cin >> choice3;
					}
				}
				break;
			default:
				break;
			}
			cout << "是否返回主菜单?  Y/N" << endl;
			cin >> p;
			while (1){
				if (p == "n" || p == "N")
				{
					cout << "                           你真的想要离开我了吗？" << endl;
					cout << "                       嗯，拜拜（Y）     舍不得(N)" << endl;
					char choice3;
					cin >> choice3;
					while (1)
					{
						if (choice3 == 'y' || choice3 == 'Y'){
							cout << "系统退出！" << endl; 
							exit(0);
						}
						else if (choice3 == 'n' || choice3 == 'N'){
							break;
						}
						else{
							cout << "输入有误，请输入Y/N(y/n):" << endl;
							cin >> choice3;
						}
					}
					break;
				}
				else if (p == "y" || p == "Y")break;
				else{
					cout << "输入有误，请输入 Y/N(y/n) !" << endl;
					cin >> p;
				}
			}
		}
		break;
	case 2:
		cout << endl;
		if (cnum == 0){
			cout << "未录入任何职工信息，系统将退出" << endl;
			Sleep(1500);
			cout << "系统退出！" << endl; 
			exit(0);
		}
		cout << "用户登录，请输入用户名和密码！" << endl;
		cout << "用户名（工号）：";
		string id;//输入的职工工号
		while (loc == cnum || loc == -1)
		{
			if (loc != -1){
				cout << "您输入的用户名不存在，请重新输入：" << endl;
				cout << "用户名（工号）：";
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
			cout << "密码：";
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
				cout << "\n登录成功，祝您工作顺利，心情愉快!" << endl;
				Sleep(2000);
				break;
			}
			else
			{
				error++;
				if (3 - error>0)
					cout << "\n你还有" << 3 - error << "次机会！" << endl;
				if (error == 3)
				{
					for (int i = 10; i >= 0; i--)
					{
						system("cls");

						cout << "\n     ****************************************************" << endl;
						cout << "     **密码错误3次，系统" << setw(2) << i << "秒后自动退出，请稍后重新登录**" << endl;
						cout << "     *******************************************************" << endl;
						Sleep(1000);
					}
					exit(0);
				}
				cout << "\n密码错误！请重新输入" << endl;
				Sleep(1000);
			}
		} while (error<3);
		while (1)
		{
			system("cls");
			usermenu();
			cout << "请选择（0-2）：" << endl;
			int choice1;
			cin >> choice1;
			while (!(choice1 >= 0 && choice1 <= 7))
			{
				cout << "输入有误，请重新输入：" << endl;
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
				cout << "                           你真的想要离开我了吗？" << endl;
				cout << "                       嗯，拜拜（Y）     舍不得(N)" << endl;
				char choice3;
				cin >> choice3;
				while (1)
				{
					if (choice3 == 'y' || choice3 == 'Y'){
						cout << "系统退出！" << endl; 
						exit(0);
					}
					else if (choice3 == 'n' || choice3 == 'N'){
						break;
					}
					else{
						cout << "输入有误，请输入Y/N(y/n):" << endl;
						cin >> choice3;
					}
				}
				break;
			default:
				break;
			}
			cout << "是否返回主菜单?  Y/N" << endl;
			cin >> p;
			while (1){
				if (p == "n" || p == "N")
				{
					cout << "                           你真的想要离开我了吗？" << endl;
					cout << "                       嗯，拜拜（Y）     舍不得(N)" << endl;
					char choice3;
					cin >> choice3;
					while (1)
					{
						if (choice3 == 'y' || choice3 == 'Y'){
							cout << "系统退出！" << endl; 
							exit(0);
						}
						else if (choice3 == 'n' || choice3 == 'N'){
							break;
						}
						else{
							cout << "输入有误，请输入Y/N(y/n):" << endl;
							cin >> choice3;
						}
					}
					break;
				}
				else if (p == "y" || p == "Y")break;
				else{
					cout << "输入有误，请输入 Y/N(y/n) !" << endl;
					cin >> p;
				}
			}
		}
	}
}
//计算并返回文件已包含的职工数量
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
//职工信息添加函数
void Workers::add()
{
	cout << "请输入职工信息:" << endl;
	string num;
	cout << "工号:";
	cin >> num;
	for (int i = 0; i<NUM; i++)
		if (w[i].ID == num){
			cout << "此职工编号已存在，请重新输入：" << endl;
			cin >> num;
			i = 0;
		}
	w[NUM].ID = num; 
	bool f = 1;
	while (f){
		cout << "姓名:"; cin >> w[NUM].name;
		if (w[NUM].name.size() <= 1){
			cout << "这名字也太短了吧！请重新输入：" << endl;
			continue;
		}
		for (unsigned int i = 0; i < w[NUM].name.size(); i++)
		{
			if (w[NUM].name[i] >= 48 && w[NUM].name[i] <= 57){
				cout << "谁名字里有数字啊？请重新输入：" << endl;break;
			}
			else if (w[NUM].name[0] >= 97 && w[NUM].name[0] <= 122){
				cout << "首字母需大写，请重新输入：" << endl; break;
			}
			else f = 0;
		}
	}
	f = 1;
	while (f){
		cout << "性别:"; cin >> w[NUM].sex;
		if (w[NUM].sex == "男" || w[NUM].sex == "女")
			f = 0;
		else
			cout << "难道是传说中的第三种性别？请重新输入（男/女）：" << endl;
	}
	f = 1;
	while (f){
		cout << "学历(小学/初中/中专/高中/专科/本科/硕士/博士/博士后):"; cin >> w[NUM].edu;
		if (w[NUM].edu == "小学" || w[NUM].edu == "初中" || w[NUM].edu == "中专" || w[NUM].edu == "高中" || w[NUM].edu == "专科" ||
			w[NUM].edu == "本科" || w[NUM].edu == "硕士" || w[NUM].edu == "博士" || w[NUM].edu == "博士后")
			f = 0;
		else
			cout << "请输入正确的学历：" << endl;
	}
	f = 1;
	while (f){
		cout << "年龄:"; cin >> w[NUM].age;
		if (w[NUM].age >= 16 && w[NUM].age <=60)
			f = 0;
		else
			cout << "请输入正确的年龄(16~60)：" << endl;
	}
	f = 1;
	while (f){
		cout << "月薪:"; cin >> w[NUM].salary;
		if (w[NUM].salary >= 0)
			if (w[NUM].salary >= 1250)//1250是2015中国最低工资（最低为重庆市）
				f = 0;
			else
				cout << "职工工资似乎不符合劳工最低工资，请重新输入：" << endl;
		else
			cout << "工资是负的得多惨？请重新输入：" << endl;
	}
	f = 1;
	cout << "地址:"; cin >> w[NUM].address;
	while (f){
		cout << "电话:"; cin >> w[NUM].tel;
		if (w[NUM].tel.size() == 11 || w[NUM].tel.size() == 8)
			f = 0;
		else
			cout << "请输入正确位数的号码：" << endl;
	}
	w[NUM].GetTax();
	w[NUM].GetPay();
	++NUM;
	++count;
}
//读取并显示职工信息（当前程序中输入的信息）
void Workers::Showcur()
{
	if (count == 0)
	{
		cout << "没有职工信息输入，系统将返回主菜单" << endl;
		return;
	}
	cout << "当前输入的职工信息如下：" << endl;
	cout << "工号\t姓名\t性别\t学历\t年龄\t地址\t电话\t\t实际收入" << endl;
	for (int i = 0; i < NUM; i++)
	{
		cout << w[i].ID << '\t' << w[i].name << '\t' << w[i].sex << '\t' << w[i].edu << '\t' << w[i].age;
		cout << '\t' << w[i].address << '\t' << w[i].tel << '\t' << w[i].pay << endl;
	}
}
//职工信息存入文件功能
void Workers::Save()
{
	if (NUM == 0)
	{
		cout << "没有职工信息输入，系统将返回主菜单" << endl;
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
		cout << "文件正在保存......请稍候！！" << endl;
		cout << "数据保存成功！！！" << endl;
		for (int i = 0; i < NUM; i++)
		{
			fout << w[i].ID << '\t' << w[i].name << '\t' << w[i].sex << '\t' << w[i].edu << '\t' << w[i].age;
			fout << '\t' << w[i].address << '\t' << w[i].tel << '\t' << w[i].salary << '\t' << w[i].tax << '\t' << w[i].pay << endl;
			foutp << w[i].Pw << endl;
		}
		this->Showsaved();
		cout << "系统返回主菜单：" << endl;
		fout.close();
		foutp.close();
		SetFileAttributes(L"E:\\password.txt", FILE_ATTRIBUTE_HIDDEN);
	}
}
//查找职工信息函数（查找内容为已经保存在文件中的职工）
void Workers::Search()
{
	int flag = 1;
	int first = 1;
	buffer = NUM;
	this->Num();
	if (NUM == 0)
	{
		cout << "没有职工信息存入，系统将返回主菜单" << endl;
		NUM = buffer;
		return;
	}
	Searchmenu();
	cout << endl;
	cout << "请选择数字编号0~6" << endl;
	int choice5;
	cin >> choice5;
	while (choice5<0 || choice5>6)
	{
		cout << "输入有误，请重新输入：" << endl;
		cin >> choice5;
	}
	if (choice5 == 1)
	{
		string id;
		cout << "请输入要查询的职工的工号：" << endl;
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
						cout << "查询的职工信息如下：" << endl;
						cout << "工号\t姓名\t性别\t学历\t年龄\t地址\t电话\t\t实际收入" << endl;
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
				cout << "不存在这样的职工!!\n返回主菜单" << endl;
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
		cout << "请输入要查询的职工的姓名：" << endl;
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
						cout << "查询的职工信息如下：" << endl;
						cout << "工号\t姓名\t性别\t学历\t年龄\t地址\t电话\t\t实际收入" << endl;
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
				cout << "不存在这样的职工!!\n返回主菜单" << endl;
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
		cout << "请输入要查询的职工的工资：" << endl;
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
						cout << "查询的职工信息如下：" << endl;
						cout << "工号\t姓名\t性别\t学历\t年龄\t地址\t电话\t\t实际收入" << endl;
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
				cout << "不存在这样的职工!!\n返回主菜单" << endl;
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
		cout << "请输入要查询的职工的学历：" << endl;
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
						cout << "查询的职工信息如下：" << endl;
						cout << "工号\t姓名\t性别\t学历\t年龄\t地址\t电话\t\t实际收入" << endl;
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
				cout << "不存在这样的职工!!\n返回主菜单" << endl;
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
		cout << "请输入要查询的职工的年龄：" << endl;
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
						cout << "查询的职工信息如下：" << endl;
						cout << "工号\t姓名\t性别\t学历\t年龄\t地址\t电话\t\t实际收入" << endl;
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
				cout << "不存在这样的职工!!\n返回主菜单" << endl;
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
		cout << "请输入要查询的职工的地址：" << endl;
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
						cout << "查询的职工信息如下：" << endl;
						cout << "工号\t姓名\t性别\t学历\t年龄\t地址\t电话\t\t实际收入" << endl;
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
				cout << "不存在这样的职工!!\n返回主菜单" << endl;
				NUM = buffer;
				break;
			}
		}
	}
	else if (choice5 == 0)
		return ;
}
//职工信息修改函数
void Workers::Amend()
{
	buffer = NUM;
	this->Num();
	if (NUM == 0)
	{
		cout << "没有职工信息存入，系统将返回主菜单" << endl;
		NUM = buffer;
		return;
	}
	this->Showsaved();
	cout << "请输入需要修改信息职工的工号：" << endl;
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
			cout << "不存在此员工，请重新输入：" << endl;
			j = 0;
			cin >> num1;
		}
		NUM = buffer;
	}
	cout << "你选择的职工的信息为：" << endl;
	cout << "工号\t姓名\t性别\t学历\t年龄\t地址\t电话\t\t实际收入" << endl;
	cout << w[k].ID << '\t' << w[k].name << '\t' << w[k].sex << '\t' << w[k].edu << '\t' << w[k].age;
	cout << '\t' << w[k].address << '\t' << w[k].tel << '\t'  <<w[k].pay<<endl;
	Amendmenu();
	cout << endl;
	cout << "请选择数字编号0~8" << endl;
	int choice6;
	cin >> choice6;
	while (choice6<0 || choice6>8)
	{
		cout << "输入有误，请重新输入：" << endl;
		cin >> choice6;
	}
	switch (choice6)
	{
	case 1:
		cout << "请输入新的职工工号:";
		cin >> w[k].ID;
		cout << "修改信息已保存：" << endl;
		break;
	case 2:
		cout << "请输入新的职工姓名:";
		cin >> w[k].name;
		cout << "修改信息已保存：" << endl;
		break;
	case 3:
		cout << "请输入新的职工性别:";
		cin >> w[k].sex;
		cout << "修改信息已保存：" << endl;
		break;
	case 4:
		cout << "请输入新的职工学历:";
		cin >> w[k].edu;
		cout << "修改信息已保存：" << endl;
		break;
	case 5:
		cout << "请输入新的职工年龄:";
		cin >> w[k].age;
		cout << "修改信息已保存：" << endl;
		break;
	case 6:
		cout << "请输入新的职工月薪:";
		cin >> w[k].salary;
		w[k].GetTax();
		w[k].GetPay();
		cout << "修改信息已保存：" << endl;
		break;
	case 7:
		cout << "请输入新的职工地址:";
		cin >> w[k].address;
		cout << "修改信息已保存：" << endl;
		break;
	case 8:
		cout << "请输入新的职工电话:";
		cin >> w[k].tel;
		cout << "修改信息已保存：" << endl;
		break;
	case 0:
		break;
	default:
		break;
	}
	this->Save();
}
//职工信息排序功能
void Workers::Sort()
{
	buffer = NUM;
	this->Num();
	if (NUM == 0)
	{
		cout << "没有职工信息存入，系统将返回主菜单" << endl;
		NUM = buffer;
		return;
	}
	else
	{
		cout << "请选择排序方式：" << endl;
		cout << "               ***********************************************" << endl;
		cout << "               **            1.按工号排序（升序）         **" << endl;
		cout << "               **            2.按工号排序（降序）          **" << endl;
		cout << "               **            3.按姓名排序（升序）          **" << endl;
		cout << "               **            4.按姓名排序（降序）          **" << endl;
		cout << "               **            5.按工资排序（升序）          **" << endl;
		cout << "               **            6.按工资排序（降序）          **" << endl;
		cout << "               **            0.返回主菜单                  **" << endl;
		cout << "               ***********************************************" << endl;
		cout << endl;
		cout << "请选择数字编号0~6" << endl;
		int choice2;
		cin >> choice2;
		while (choice2 < 0 || choice2>6)
		{
			cout << "输入有误，请重新输入：" << endl;
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
			cout << "按工号升序后的信息如下：" << endl;
			cout << "工号\t姓名\t性别\t学历\t年龄\t地址\t电话\t\t实际收入" << endl;
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
			cout << "按工号降序后的信息如下：" << endl;
			cout << "工号\t姓名\t性别\t学历\t年龄\t地址\t电话\t\t实际收入" << endl;
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
			cout << "按姓名升序后的信息如下：" << endl;
			cout << "工号\t姓名\t性别\t学历\t年龄\t地址\t电话\t\t实际收入" << endl;
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
			cout << "按姓名降序后的信息如下：" << endl;
			cout << "工号\t姓名\t性别\t学历\t年龄\t地址\t电话\t\t实际收入" << endl;
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
			cout << "按工资升序后的信息如下：" << endl;
			cout << "工号\t姓名\t性别\t学历\t年龄\t地址\t电话\t\t实际收入" << endl;
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
			cout << "按工资降序后的信息如下：" << endl;
			cout << "工号\t姓名\t性别\t学历\t年龄\t地址\t电话\t\t实际收入" << endl;
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
	cout << "文件正在保存......请稍候！！" << endl;
	cout << "数据保存成功！！！" << endl;
	for (int i = 0; i < NUM; i++)
	{
		fout << w[i].ID << '\t' << w[i].name << '\t' << w[i].sex << '\t' << w[i].edu << '\t' << w[i].age;
		fout << '\t' << w[i].address << '\t' << w[i].tel << '\t' << w[i].salary << '\t' << w[i].tax << '\t' << w[i].pay << endl;
	}
	cout << "系统返回主菜单：" << endl;
	fout.close();
	NUM = buffer;
}
// 职工信息删除功能
void Workers::Delete()
{
	if (NUM == 0)
	{
		cout << "没有职工信息输入，系统将返回主菜单" << endl;
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
		cout << "文件正在保存......请稍候！！" << endl;
		cout << "数据保存成功！！！" << endl;
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
		cout << "没有职工信息存入，系统将返回主菜单" << endl;
		NUM = buffer0;
		return;
	}
	cout << "请输入需要删除信息职工的工号：" << endl;
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
			cout << "不存在此员工，请重新输入：" << endl;
			cin >> delid;
		}
	}
	cout << "你选择的职工的信息为：" << endl;
	cout << "工号\t姓名\t性别\t学历\t年龄\t地址\t电话\t\t实际收入" << endl;
	cout << w[k].ID << '\t' << w[k].name << '\t' << w[k].sex << '\t' << w[k].edu << '\t' << w[k].age;
	cout << '\t' << w[k].address << '\t' << w[k].tel << '\t' << w[k].pay << endl;
	cout << "确认请输入Y\t返回主菜单请输入N " << endl;
	string p;
	cin >> p;
	while (1)
	{
		if (p == "y" || p == "Y")
		{
			cout << "员工信息已删除！" << endl;
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
			cout << "文件正在保存......请稍候！！" << endl;
			cout << "数据保存成功！！！" << endl;
			for (int i = 0; i < NUM; i++)
			{
				fout << w[i].ID << '\t' << w[i].name << '\t' << w[i].sex << '\t' << w[i].edu << '\t' << w[i].age;
				fout << '\t' << w[i].address << '\t' << w[i].tel << '\t' << w[i].salary << '\t' << w[i].tax << '\t' << w[i].pay << endl;
				foutp << w[i].Pw << endl;
			}
			this->Showsaved();
			cout << "系统返回主菜单：" << endl;
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
			cout << "输入有误，请重新输入：";
			cin >> p;
		}
	}
	NUM = buffer0;
}
//职工信息显示函数（显示文件中的内容）
void Workers::Showsaved()
{
	buffer = NUM;
	this->Num();
	if (NUM==0)
	{
		cout << "职工文档为空，系统将返回主菜单" << endl;
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
		cout << "已保存的职工信息如下：" << endl;
		cout << "工号\t姓名\t性别\t学历\t年龄\t地址\t电话\t\t实际收入" << endl;
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
//获得职工工号
string Workers::GetID(int i)
{
	return w[i].ID;
}
//用户登录时显示当前用户信息
void Workers::Show(int i)
{
	w[i].Show();
}
//获取某个职工旧密码
char * Workers::GetPw(int l)
{
	return w[l].Pw;
}
//统计信息并且显示
void Workers::Total()
{
	buffer = NUM;
	this->Num();
	for (int i = 0; i < NUM; i++)
	{
		tsalary += w[i].salary;
		ttax += w[i].tax;
	}
	cout << "\n职工总数\t工资总数\t税金总数" << endl;
	cout << NUM << "\t\t"<< tsalary << "\t\t" << ttax << endl;
	NUM = buffer;
}
//用户修改密码
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
			cout << "\n请输入修改前的密码：" << endl;
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
					cout << "\n请输入新密码(注：密码长度至少6位，但不得超过20位）：" << endl;
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
						cout << "\n密码过长，请重新输入：" << endl;
					else if (strlen(p) < 6)
						cout << "\n密码过短，请重新输入：" << endl;
					else
						break;
				}
				while (1){
					cout << "\n请再次输入新密码：" << endl;
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
						cout << "\n密码修改成功！" << endl;
						Sleep(1000);
						break;
					}
					else{
						cout << "\n两次密码不相同 " << endl;
						cout << "是否需要返回？" << endl;
						cout << "是(Y)      否(N)" << endl;
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
								cout << "\n输入有误，请输入Y/N(y/n):" << endl;
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
						cout << "     **密码错误3次，系统" << setw(2) << i << "秒后自动退出，请稍后重新登录**" << endl;
						cout << "     *******************************************************" << endl;
						Sleep(1000);
					}
					exit(1);
				}
				cout << "\n密码错误！请重新输入" << endl;
				Sleep(1000);
			}
		} while (error < 3&&!out);
	} while (back);
	NUM = buffer;
	cout << endl;
}
//main函数调用执行函数Execute()
int main()
{
	system("COLOR 30");
	Execute();
	SetFileAttributes(L"E:\\password.txt", FILE_ATTRIBUTE_HIDDEN);
	return 0;
}