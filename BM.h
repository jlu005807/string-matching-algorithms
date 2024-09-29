#pragma once
#include"Index.h"


//当你分清楚了好和坏，你才会走得更快 --BM


//坏字符规则：当文本串中的某个字符跟模式串的某个字符不匹配时，
//我们称文本串中的这个失配字符为坏字符，此时模式串需要向右移动，
//移动的位数 = 坏字符在模式串中的位置 - 坏字符在模式串中最右出现的位置。此外，如果"坏字符"不包含在模式串之中，则最右出现位置为 - 1。

//好后缀规则
//当匹配失败时候，已经匹配成功的子字符串称为好后缀，这个时候同样向右滑动模式串
//移动的位数 = 好后缀起始与模式串匹配位置 - 好后缀在模式串中上一次出现位置的起始位置，如果好后缀不在模式串中出现，上一次位置为 - 1


class BM :public Index
{

public:
	//生成坏字符偏移表
	void preBmBc(std::string T, int Bmbc[])
	{
		int CHAR_SIZE = 256;//字符集范围，此处为ASIZE
		
		int lenT = T.size();
		
		for (int i = 0; i < CHAR_SIZE; i++)
		{
			Bmbc[i] = lenT;//未出现在T中的字符位置初始化为T的长度
		}

		for (int i = 0; i < lenT; i++)
		{
			Bmbc[int(T[i])] = lenT - i - 1;//记录字符集里出现在T中且最靠右的此种字符和T最后一个字符的距离
		}

	}

	//生成suffix表辅助接下来生成好后缀偏移表
	//suffix[ i ] = shift 表示以 i 为右边界，与模式串T后缀匹配的最大长度，
	//亦即T[i - shift + 1 , i] = T[len - shift , len - 1]
	//此法较难理解，有简单实现
	void suffixes(std::string T, int suffix[])
	{
		int lenT = T.size();

		suffix[lenT - 1] = lenT;//最后一个字符的匹配长度就是T本身长度

		int g = lenT - 1;//表示当前右边界

		int f=lenT-2;//当前后缀起始位置(从左往右）

		for (int i = lenT - 2; i >= 0; i--)//从最后第二个字符往前回溯
		{
			if (i > g && suffix[i + lenT - 1 - f] < i - g)
			{
				//当i>g时，T[g+1,f]已经是匹配了T[lenT-1-f+g+1,lenT-1]
				//
				/*std::cout << i << " " << g << " " << f << " ";
				system("Pause");*/
				suffix[i] = suffix[i + lenT - 1 - f];//继承之前计算的值
			}
			else
			{

				if (i < g)g = i;//如果回溯到边界左边，则更新右边界

				f = i;//更新当前后缀的起始位置

				while (g >= 0 && T[g] == T[g + lenT - 1 - f])--g;

				suffix[i] = f - g;
			}

		}
	}

	//简单生成suffix辅助表
	void simply_suffixes(std::string T, int suffix[])
	{
		int lenT = T.size();
		
		//同理，最后一个字符的匹配长度就是T本身长度
		suffix[lenT - 1] = lenT;

		//两次循环
		for (int i = lenT - 2; i >= 0; i--)
		{
			int j = 0;//记录已经匹配长度
			for (j; j <= i && T[i - j] == T[lenT - j - 1]; j++) {}
			suffix[i] = j;
		}

	}

	
	int index(std::string S, std::string T, int pos)
	{
		return 0;
	}


};