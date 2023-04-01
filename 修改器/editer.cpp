#include <iostream>
#include <windows.h>
#include "Head.h"

int EXE_Number = 0;
int* EXE_Key = nullptr;
int* EXE_Path_Length = nullptr;
char** EXE_Path = nullptr;
char* EXE_Param = nullptr;
int EXE_Param_Length = 0;

bool setting_File_Changed = false;

int main(int argc,char* argv[])
{
#ifdef _DEBUG
	std::cout << "DEBUG°æ±¾" << std::endl;
#endif
	std::cout << "°æ±¾:" << version << std::endl;

	Read_Setting();
	Edit_Setting();
	Write_Setting();
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