#pragma once
#include"Index.h"


//类似于BM算法，但是从前往后匹配，
//在匹配失败时关注的是主串中参加匹配的最末位字符的下一位字符。
//如果该字符没有在模式串中出现则直接跳过，即移动位数 = 模式串长度 + 1
//否则，其移动位数 = 模式串长度 - 该字符最右出现的位置(以0开始) = 模式串中该字符最右出现的位置到尾部的距离 + 1。


class Sunday :public Index
{
public:

	//同理，先生成坏字符偏移表
	void preBmBc(std::string T, int Bmbc[], int CHAR_SIZE = 256)
	{
		//CHAR_SIZE为字符集范围，此处为ASIZE

		int lenT = T.size();

		for (int i = 0; i < CHAR_SIZE; i++)
		{
			Bmbc[i] = lenT + 1;//未出现在T中的字符位置初始化为T的长度+1即偏移的长度
		}
		// 模式串P中每个字母出现的最后的下标
	// 所对应的主串参与匹配的最末位字符的下一位字符移动到该位，所需要的移动位数
		for (int i = 0; i < lenT; i++)
		{
			Bmbc[int(T[i])] = lenT - i;
		}

	}

	int index(std::string S, std::string T, int pos)
	{
		//预处理
		int n = S.size(), m = T.size();
		int CHAR_SIZE = 256;//字符集大小
		int* Bad_shift = new int[CHAR_SIZE];
		
		preBmBc(T, Bad_shift);

		//查找
		int s = pos;//记录主串开始位置
		int j;
		while (s <= n - m)
		{
			j = 0;
			while (S[s + j] == T[j])
			{
				j++;
				if (j >= m)//匹配成功
				{
					return s;
				}
			}
			//找到主串中当前跟模式串匹配的最末字符的下一个字符
			//在模式串中出现最后的位置
			//所需要从(模式串末尾+1)移动到该位置的步数
				s += Bad_shift[S[s + m]];
		}

		//匹配失败
		return - 1;
	}
};