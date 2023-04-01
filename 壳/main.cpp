#include <iostream>
#include <windows.h>
#include "Head.h"

int EXE_Number = 0;
int* EXE_Key = nullptr;
int* EXE_Path_Length = nullptr;
char** EXE_Path = nullptr;
char* EXE_Param = nullptr;
int EXE_Param_Length = 0;

int return_Number = 0;
bool setting_File_Changed = false;

int main(int argc, char* argv[])
{
	Initialize();
	if (CMD_Check(argc, argv))
	{
		Enedze();
		return return_Number;
	}

	Run(-1);//小于0:自行判断
	Enedze();
	return return_Number;
}

void Initialize()
{
#ifdef _DEBUG
	std::cout << "DEBUG版本" << std::endl;
#endif

	DELETE_PTR(EXE_Param);
	EXE_Param_Length = 1;
	EXE_Param = new char[EXE_Param_Length];
	EXE_Param[0] = '\0';

	Read_Setting();
	Sleep(100);
}

void Enedze()
{
	if (setting_File_Changed) Write_Setting();

	Delete_Heap();

	EXE_Number = 0;
	EXE_Param_Length = 0;
}

bool CMD_Check(int& argc, char* argv[])
{
	//argc	1		2	3	...
	//	i	0		1	2	...
	//argv	Path	P1	P2	...

	if (argc == 1) return false;

	//命令行调用

	//程序调用
	if (argv[1][0] != '_' || argv[1][1] != '-' || argv[1][2] != '_')
	{
		//普通调用
		Get_Param(argc - 1, argv + 1);
		Run(0);

		return true;
	}

	//对壳的调用
	using std::cout;
	using std::cin;
	using std::endl;

	cout << "壳程序命令行调用" << endl;

	if_streq(argv[1], "_-_edit")
	{
		system(".\\修改器.exe");
	}
	if_streq(argv[1], "_-_run")
	{
		if (argc > 2)
		{
			//argc	1		2		3	...
			//	i	0		1		2	...
			//argv	Path	-_-Run	P1	...
			int Run_Number = atoi(argv[2]) - 1;

			if (0 <= Run_Number && Run_Number < EXE_Number)
			{
				Get_Param(argc - 3, argv + 3);
				cout << "启动第" << Run_Number + 1 << "个程序:" << EXE_Path[Run_Number] << endl
					<< "参数:" << EXE_Param << endl;
				Run(Run_Number);
			}
			else
			{
				cout << "第" << Run_Number + 1 << "个程序不存在" << endl;
			}
		}
		else
		{
			cout << "_-_run:参数错误" << endl
				<< "_-_run的参数: 启动编号 [启动参数]" << endl;
		}
	}
	else_streq(argv[1], "_-_version")
	{
		cout << "版本:" << version << endl;
	}
	else_streq(argv[1], "_-_help")
	{
		cout << "_-_help:帮助" << endl
			<< "_-_version:版本" << endl
			<< "_-_edit:修改启动文件" << endl
			<< "_-_run:启动指定程序" << endl
			<< endl;
	}
	else
	{
		cout << "未知参数:" << argv[1] << endl
			<< "输入_-_help获取帮助" << endl;
	}

	return true;
}

void Run(int Start_Number)
{
	if (Start_Number < 0) for (int i = 0; i < EXE_Number; i++)
		if (GetAsyncKeyState(EXE_Key[i])) Start_Number = i;

	if (Start_Number < 0) Start_Number = 0;
	int param_Length = 0;
	char* param = nullptr;

	param_Length = EXE_Path_Length[Start_Number] + EXE_Param_Length + 10;//两倍的\0其中有一个给了空格 +10以防万一
	param = new char[param_Length];
	sprintf_s(param, param_Length, "%s %s", EXE_Path[Start_Number], EXE_Param);

	return_Number = system(param);//调用程序

	DELETE_PTR(param);
}

void New_Heap()
{
	Delete_Heap();

	EXE_Key = new int[EXE_Number];
	EXE_Path_Length = new int[EXE_Number];

	EXE_Path = new char* [EXE_Number];
	for (int i = 0; i < EXE_Number; i++)
	{
		EXE_Path[i] = nullptr;
	}
}

void Delete_Heap()
{
	DELETE_PTR(EXE_Key);
	DELETE_PTR(EXE_Path_Length);
	DELETE_PTR(EXE_Param);

	if (EXE_Path != nullptr)
	{
		for (int i = 0; i < EXE_Number; i++) DELETE_PTR(EXE_Path[i]);

		EXE_Path = nullptr;
	}
}

void Get_Param(int argc, char* argv[])
{
	if (argc <= 0)
	{
		DELETE_PTR(EXE_Param);
		EXE_Param_Length = 1;
		EXE_Param = new char[EXE_Param_Length];
		EXE_Param[0] = '\0';
		return;
	}

	DELETE_PTR(EXE_Param);
	EXE_Param_Length = 0;

	int Param_Position = 0;
	int* str_Length = new int[argc];

	//计算长度
	for (int i = 0; i < argc; i++)
	{
		str_Length[i] = (int)strlen(argv[i]);
		EXE_Param_Length += str_Length[i] + 1;//计算长度 1:空格和'\0'
	}
	EXE_Param_Length += 1;//以防万一
	EXE_Param = new char[EXE_Param_Length];

	//拷贝
	for (int i = 0; i < argc; i++)
	{
		strcpy_s(EXE_Param + Param_Position, EXE_Param_Length - Param_Position, argv[i]);
		Param_Position += str_Length[i];//拷贝偏移

		EXE_Param[Param_Position] = ' ';
		Param_Position++;//空格分割
	}
	EXE_Param[Param_Position - 1] = '\0';//此时Param_Position == EXE_Param_Length

	delete[]str_Length;
}
