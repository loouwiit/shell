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

	Run(-1);//С��0:�����ж�
	Enedze();
	return return_Number;
}

void Initialize()
{
#ifdef _DEBUG
	std::cout << "DEBUG�汾" << std::endl;
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

	//�����е���

	//�������
	if (argv[1][0] != '_' || argv[1][1] != '-' || argv[1][2] != '_')
	{
		//��ͨ����
		Get_Param(argc - 1, argv + 1);
		Run(0);

		return true;
	}

	//�Կǵĵ���
	using std::cout;
	using std::cin;
	using std::endl;

	cout << "�ǳ��������е���" << endl;

	if_streq(argv[1], "_-_edit")
	{
		system(".\\�޸���.exe");
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
				cout << "������" << Run_Number + 1 << "������:" << EXE_Path[Run_Number] << endl
					<< "����:" << EXE_Param << endl;
				Run(Run_Number);
			}
			else
			{
				cout << "��" << Run_Number + 1 << "�����򲻴���" << endl;
			}
		}
		else
		{
			cout << "_-_run:��������" << endl
				<< "_-_run�Ĳ���: ������� [��������]" << endl;
		}
	}
	else_streq(argv[1], "_-_version")
	{
		cout << "�汾:" << version << endl;
	}
	else_streq(argv[1], "_-_help")
	{
		cout << "_-_help:����" << endl
			<< "_-_version:�汾" << endl
			<< "_-_edit:�޸������ļ�" << endl
			<< "_-_run:����ָ������" << endl
			<< endl;
	}
	else
	{
		cout << "δ֪����:" << argv[1] << endl
			<< "����_-_help��ȡ����" << endl;
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

	param_Length = EXE_Path_Length[Start_Number] + EXE_Param_Length + 10;//������\0������һ�����˿ո� +10�Է���һ
	param = new char[param_Length];
	sprintf_s(param, param_Length, "%s %s", EXE_Path[Start_Number], EXE_Param);

	return_Number = system(param);//���ó���

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

	//���㳤��
	for (int i = 0; i < argc; i++)
	{
		str_Length[i] = (int)strlen(argv[i]);
		EXE_Param_Length += str_Length[i] + 1;//���㳤�� 1:�ո��'\0'
	}
	EXE_Param_Length += 1;//�Է���һ
	EXE_Param = new char[EXE_Param_Length];

	//����
	for (int i = 0; i < argc; i++)
	{
		strcpy_s(EXE_Param + Param_Position, EXE_Param_Length - Param_Position, argv[i]);
		Param_Position += str_Length[i];//����ƫ��

		EXE_Param[Param_Position] = ' ';
		Param_Position++;//�ո�ָ�
	}
	EXE_Param[Param_Position - 1] = '\0';//��ʱParam_Position == EXE_Param_Length

	delete[]str_Length;
}
