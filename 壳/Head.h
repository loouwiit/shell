/*
* �׿ǳ���
*
* 0.0.1.0 ���� .\sheller.txt ���������İ������ļ��� ��� Enigma Virtual Box�����׿�Ч��
* 0.0.1.1 �޸�����·��Ϊcin.getline()
* 0.0.1.2 �޸���������»����������bug Ĭ������»��Զ�������һ������ �Ƴ����ַǱ�Ҫ����
* 0.0.1.3 ɾ������Ҫ��if�ж� �����޸���ʹ��������ɹرտ���̨
* 
* Next �ֶ�����
*/

#pragma once
constexpr char version[] = "0.0.1.3";
constexpr int setting_Version = 1;
constexpr char setting_Path[] = ".\\sheller.txt";
constexpr int default_Input_Length = 100;

extern int EXE_Number;
extern int* EXE_Key;
extern int* EXE_Path_Length;
extern char** EXE_Path;

extern char* EXE_Param;
extern int EXE_Param_Length;

extern int return_Number;
extern bool setting_File_Changed;


#define DELETE_PTR(PTR) {if (PTR != nullptr) {delete[] PTR; PTR = nullptr;}}
#define if_streq(STR1,STR2) if (strcmp(STR1 , STR2) == 0)
#define else_streq(STR1,STR2) else if (strcmp(STR1 , STR2) == 0)


int main(int argc, char* argv[]);
void Initialize();
void Enedze();
bool CMD_Check(int& argc, char* argv[]);

void Get_Param(int argc, char* argv[]);
void Run(int Start_Number);
void New_Heap();
void Delete_Heap();

void Edit_Setting();
bool Read_Setting();
void Write_Setting();
