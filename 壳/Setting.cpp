#include <iostream>
#include <fstream>
#include "Head.h"

void Edit_Setting()
{
	using std::cout;
	using std::cin;
	using std::endl;

	bool editing = true;
	int now_Position = 0;
	int input_Length = default_Input_Length;
	char* input = new char[input_Length];

	cout << "修改启动参数" << endl
		<< "最大输入长度:" << input_Length << endl
		<< "输入 help 获取帮助" << endl;
	while (editing)
	{
		cout << endl;
		if (EXE_Number > 0)
		{
			cout << now_Position + 1 << '/' << EXE_Number << endl
				<< "键码:" << EXE_Key[now_Position] << endl
				<< "路径:" << EXE_Path[now_Position] << endl;
		}
		else
		{
			cout << "什么都没有，使用add添加" << endl;
		}
		cout << '<' << input_Length << "> ";
		cin >> input;

		if_streq(input, "help")
		{
			cout << "help:帮助" << endl
				<< "input:修改最大输入长度" << endl
				<< "down:向下移动" << endl
				<< "up:向上移动" << endl
				<< "add:添加启动参数" << endl
				<< "del:删除启动参数" << endl
				<< "exit:退出" << endl;
		}
		else if (strcmp(input, "d") == 0 || strcmp(input, "down") == 0)
		{
			if (now_Position + 1 < EXE_Number) now_Position++;
			else cout << "最后一个" << endl;
		}
		else if (strcmp(input, "u") == 0 || strcmp(input, "up") == 0)
		{
			if (now_Position > 0) now_Position--;
			else cout << "第一个" << endl;
		}
		else_streq(input, "input")
		{
			cout << "请输入修改后的最大输入长度:";
			cin >> input;

			input_Length = atoi(input);
			if (input_Length < 10) input_Length = 10;
			if (input_Length > 1000) input_Length = 1000;

			DELETE_PTR(input);
			input = new char[input_Length];
		}
		else_streq(input, "add")
		{
			int EXE_Number_Sub = EXE_Number;
			//扩大空间
			{
				int sub_Position = now_Position;
				int EXE_Sub_Position = EXE_Number - sub_Position;
				now_Position++;
				EXE_Number++;

				if (EXE_Number_Sub == 0) now_Position = 0;

				int* temp_EXE_Key = new int[EXE_Number];
				int* temp_EXE_Path_Length = new int[EXE_Number];
				char** temp_EXE_Path = new char* [EXE_Number];

				//前半段
				if (now_Position > 0)//原先有数值
				{
					memcpy_s(temp_EXE_Key, sizeof(int) * EXE_Number,
						EXE_Key, sizeof(int) * now_Position);
					memcpy_s(temp_EXE_Path_Length, sizeof(int) * EXE_Number,
						EXE_Path_Length, sizeof(int) * now_Position);
					memcpy_s(temp_EXE_Path, sizeof(char*) * EXE_Number,
						EXE_Path, sizeof(char*) * now_Position);
				}

				//后半段
				if (EXE_Sub_Position > 0)
				{
					memcpy_s(temp_EXE_Key + now_Position, sizeof(int) * EXE_Sub_Position,
						EXE_Key + sub_Position, sizeof(int) * EXE_Sub_Position);
					memcpy_s(temp_EXE_Path_Length + now_Position, sizeof(int) * EXE_Sub_Position,
						EXE_Path_Length + sub_Position, sizeof(int) * EXE_Sub_Position);
					memcpy_s(temp_EXE_Path + now_Position, sizeof(char*) * EXE_Sub_Position,
						EXE_Path + sub_Position, sizeof(char*) * EXE_Sub_Position);
				}

				DELETE_PTR(EXE_Key);
				DELETE_PTR(EXE_Path_Length);
				DELETE_PTR(EXE_Path);

				EXE_Key = temp_EXE_Key;
				EXE_Path_Length = temp_EXE_Path_Length;
				EXE_Path = temp_EXE_Path;//指针数据已经拷贝
			}//扩大空间

			cout << "请输入键码:"; cin >> input;
			EXE_Key[now_Position] = atoi(input);

			cout << "请输入路径:"; cin.ignore(); cin.getline(input, input_Length);
			EXE_Path_Length[now_Position] = (int)strlen(input) + 1;// '\0'
			EXE_Path[now_Position] = new char[EXE_Path_Length[now_Position]];
			strcpy_s(EXE_Path[now_Position], EXE_Path_Length[now_Position], input);
		}
		else_streq(input, "del")
		{
			if (EXE_Number > 0)
			{
				//拷贝
				{
					int EXE_Number_Add = EXE_Number;
					EXE_Number--;
					int EXE_Sub_Position = EXE_Number - now_Position;
					int now_Position_Add = now_Position + 1;

					int* temp_EXE_Key = new int[EXE_Number];
					int* temp_EXE_Path_Length = new int[EXE_Number];
					char** temp_EXE_Path = new char* [EXE_Number];

					//前半段
					if (now_Position > 0)
					{
						memcpy_s(temp_EXE_Key, sizeof(int) * EXE_Number,
							EXE_Key, sizeof(int) * now_Position);
						memcpy_s(temp_EXE_Path_Length, sizeof(int) * EXE_Number,
							EXE_Path_Length, sizeof(int) * now_Position);
						memcpy_s(temp_EXE_Path, sizeof(char*) * EXE_Number,
							EXE_Path, sizeof(char*) * now_Position);
					}

					//后半段
					if (EXE_Sub_Position > 0)
					{
						memcpy_s(temp_EXE_Key + now_Position, sizeof(int) * EXE_Sub_Position,
							EXE_Key + now_Position_Add, sizeof(int) * EXE_Sub_Position);
						memcpy_s(temp_EXE_Path_Length + now_Position, sizeof(int) * EXE_Sub_Position,
							EXE_Path_Length + now_Position_Add, sizeof(int) * EXE_Sub_Position);
						memcpy_s(temp_EXE_Path + now_Position, sizeof(char*) * EXE_Sub_Position,
							EXE_Path + now_Position_Add, sizeof(char*) * EXE_Sub_Position);
					}

					//删除中间的内存
					DELETE_PTR(EXE_Path[now_Position]);

					DELETE_PTR(EXE_Key);
					DELETE_PTR(EXE_Path_Length);
					DELETE_PTR(EXE_Path);

					EXE_Key = temp_EXE_Key;
					EXE_Path_Length = temp_EXE_Path_Length;
					EXE_Path = temp_EXE_Path;//指针数据已经拷贝
				}//拷贝

				if (now_Position >= EXE_Number) now_Position = EXE_Number - 1;//防止越界
				if (now_Position < 0) now_Position = 0;//防止没有数据
			}
			else
			{
				cout << "没有数据" << endl;
			}
		}
		else_streq(input, "exit")
		{
			setting_File_Changed = true;
			editing = false;
			continue;
		}
		else
		{
			cout << "未知指令" << input <<
				endl << "输入help获取帮助" << endl;
		}
	}
}

bool Read_Setting()
{
	using File = std::ifstream;
	constexpr auto Mode = std::ios::in | std::ios::binary;

	File file{};

	file.open(setting_Path, Mode);

	//获取版本
	int read_Version = 0;
	file.read((char*)&read_Version, sizeof(read_Version));
	if (file.gcount() == 0 || read_Version != setting_Version)
	{
		//版本错误
#ifdef _DEBUG
		std::cout << "设置文件版本错误" << std::endl;
#endif
		return false;
	}

	//读取数量
	file.read((char*)&EXE_Number, sizeof(EXE_Number));//数量

	//分配空间
	New_Heap();

	//读取
	for (int i = 0; i < EXE_Number; i++)
	{
		file.read((char*)&EXE_Key[i], sizeof(EXE_Key[i]));//Key
		file.read((char*)&EXE_Path_Length[i], sizeof(EXE_Path_Length[i]));//Path_Length

		DELETE_PTR(EXE_Path[i]);//清空
		EXE_Path[i] = new char[EXE_Path_Length[i]];//分配Path的空间
		file.read(EXE_Path[i], EXE_Path_Length[i]);//Path
	}

	return true;
}

void Write_Setting()
{
	using File = std::ofstream;
	constexpr auto Mode = std::ios::out | std::ios::binary;
	int version = setting_Version;

	File file{};

	file.open(setting_Path, Mode);

	file.write((char*)&version, sizeof(version));//版本
	file.write((char*)&EXE_Number, sizeof(EXE_Number));//数量

	for (int i = 0; i < EXE_Number; i++)
	{
		file.write((char*)&EXE_Key[i], sizeof(EXE_Key[i]));//Key
		file.write((char*)&EXE_Path_Length[i], sizeof(EXE_Path_Length[i]));//Path_Length
		file.write(EXE_Path[i], EXE_Path_Length[i]);//Path
	}
}
