#include <string.h>

/// <summary>
/// 将待加密字符串加密
/// </summary>
/// <param name="String">待加密的字符串</param>
/// <param name="Key">加密密钥</param>
/// <param name="Length">字符串长度</param>
/// <returns>由该字符串改进后的加密密钥</returns>
int Encryption(char String[], int Key, int Length)
{
	char Now_Char = '\0';//明文
	if (Length == -1) Length = (int)strlen(String);
	for (int Position = 0; Position < Length; Position++)
	{
		Now_Char = String[Position];//储存

		//加密
		String[Position] ^= (Key >> (Position % 26)) & 0x7F;

		Key += (Now_Char & 0x7) << (int)(Position % 32 / 4) * 4;//以明文改变Key 先获取3位，然后偏移0~7*4次。
	}
	return Key;
}

/// <summary>
/// 将待解密字符串解密
/// </summary>
/// <param name="String">待解密的字符串</param>
/// <param name="Key">解密密钥</param>
/// <param name="Length">字符串长度</param>
/// <returns>由该字符串改进后的加密密钥</returns>
int Decrypt(char String[], int Key, int Length)
{
	if (Length == -1) Length = (int)strlen(String);
	for (int Position = 0; Position < Length; Position++)
	{
		String[Position] ^= (Key >> (Position % 26)) & 0x7F;

		Key += (String[Position] & 0x7) << (int)(Position % 32 / 4) * 4;//以明文改变Key 先获取4位，然后偏移0~7*4次。
	}
	return Key;
}

/// <summary>
/// 将字符串密钥转换为数字密钥
/// </summary>
/// <param name="Key_String">字符密钥</param>
/// <returns>数字密钥</returns>
int Get_Key(const char Key_String[])
{
	int Return_Number = 0x55555555;//0101......
	unsigned Position = 0;
	unsigned String_Lenght = (int)strlen(Key_String);
	while (Position < String_Lenght || Position < 8)
	{
		//一个来回结束且全部经过
		Return_Number ^= (Key_String[Position % String_Lenght] & 0xF) << ((String_Lenght - Position) % 8 * 4);//1111
		Position++;
	}
	return Return_Number;
}
