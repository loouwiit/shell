/*
* 套壳程序
*
* 0.0.1.0 根据 .\sheller.txt 决定启动的按键和文件名 结合 Enigma Virtual Box做到套壳效果
* 0.0.1.1 修改输入路径为cin.getline()
* 0.0.1.2 修复部分情况下缓冲区溢出的bug 默认情况下会自动启动第一个程序 移除部分非必要参数
* 0.0.1.3 删除不必要的if判断 分离修改器使得主程序可关闭控制台
* 
* Next 手动链接
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
