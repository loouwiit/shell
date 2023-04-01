#include <string.h>

/// <summary>
/// ���������ַ�������
/// </summary>
/// <param name="String">�����ܵ��ַ���</param>
/// <param name="Key">������Կ</param>
/// <param name="Length">�ַ�������</param>
/// <returns>�ɸ��ַ����Ľ���ļ�����Կ</returns>
int Encryption(char String[], int Key, int Length)
{
	char Now_Char = '\0';//����
	if (Length == -1) Length = (int)strlen(String);
	for (int Position = 0; Position < Length; Position++)
	{
		Now_Char = String[Position];//����

		//����
		String[Position] ^= (Key >> (Position % 26)) & 0x7F;

		Key += (Now_Char & 0x7) << (int)(Position % 32 / 4) * 4;//�����ĸı�Key �Ȼ�ȡ3λ��Ȼ��ƫ��0~7*4�Ρ�
	}
	return Key;
}

/// <summary>
/// ���������ַ�������
/// </summary>
/// <param name="String">�����ܵ��ַ���</param>
/// <param name="Key">������Կ</param>
/// <param name="Length">�ַ�������</param>
/// <returns>�ɸ��ַ����Ľ���ļ�����Կ</returns>
int Decrypt(char String[], int Key, int Length)
{
	if (Length == -1) Length = (int)strlen(String);
	for (int Position = 0; Position < Length; Position++)
	{
		String[Position] ^= (Key >> (Position % 26)) & 0x7F;

		Key += (String[Position] & 0x7) << (int)(Position % 32 / 4) * 4;//�����ĸı�Key �Ȼ�ȡ4λ��Ȼ��ƫ��0~7*4�Ρ�
	}
	return Key;
}

/// <summary>
/// ���ַ�����Կת��Ϊ������Կ
/// </summary>
/// <param name="Key_String">�ַ���Կ</param>
/// <returns>������Կ</returns>
int Get_Key(const char Key_String[])
{
	int Return_Number = 0x55555555;//0101......
	unsigned Position = 0;
	unsigned String_Lenght = (int)strlen(Key_String);
	while (Position < String_Lenght || Position < 8)
	{
		//һ�����ؽ�����ȫ������
		Return_Number ^= (Key_String[Position % String_Lenght] & 0xF) << ((String_Lenght - Position) % 8 * 4);//1111
		Position++;
	}
	return Return_Number;
}
