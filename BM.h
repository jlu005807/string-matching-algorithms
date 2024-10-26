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
	void preBmBc(std::string T, int Bmbc[],int CHAR_SIZE=256)
	{
		//CHAR_SIZE为字符集范围，此处为ASIZE
		
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
				//根据对称性，此时T[i]等于T[i+lenT-1-f],
				//当suffix[i+lenT-1-f]<i-g时，根据suffix的含义，T[i+lenT-1-f]为右边界的所匹配的字符串等于T[i]所匹配的字符串，
				//所以suffix[i+lenT-1-f]<i-g，就可以直接映射suffix[i] = suffix[i + lenT - 1 - f]
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
			for (j; j <= i && T[i - j] == T[lenT - j - 1]; j++);
			suffix[i] = j;
		}

	}



	//生成好后缀偏移表
	//BmGs[i]表示遇到好后缀时，模式串应该移动的距离，i 指向好后缀的下一个位置，也就是坏字符的位置
	void preBmGs(std::string T,int BmGs[])
	{
		int j;

		int lenT = T.size();

		int* suffix = new int[T.size()];

		suffixes(T, suffix);//生成suffix辅助表

		for (int i = 0; i < lenT; i++)
		{
			BmGs[i] = lenT;//初始化BmGs，初始状态时没有子串和好后缀匹配所以移动距离为整个模式串的长度
		}


		for (int i = lenT - 1; i >= 0; i--)
		{
			if (suffix[i] == i + 1)
			{
				//suffix[i] == i + 1 说明0到i的i + 1个字符前缀和后缀匹配
				// 并且前缀匹配滑动距离最长
				//那么lenT-i-2处即坏字符的位置，所以[0,lenT-i-2]区间内跳转都可以为lenT-i-1
				for (int j=0; j < lenT - 1 - i; j++)
				{
					if (BmGs[j] == lenT)
					{
						BmGs[j] = lenT - 1 - i;
					}
				}
			}
		}

		//GS[i]的含义是好后缀的开头的前一个字符也就是坏字符位置对应的滑动距离，
		//那么GS[len - 1 - suffix[i]]中的len - 1 - suffix[i]对应的一定是一个坏字符的位置
		for (int i = 0; i <= lenT - 2; i++)
		{
			BmGs[lenT - 1 - suffix[i]] = lenT - 1 - i;
		}

		delete suffix;//删除suffix

	}

	
	int index(std::string S, std::string T, int pos)
	{
		//预处理生成偏移表
		int CHAR_SIZE = 256;
		int i,j;
		int *BmGs = new int[T.size()];//好后缀
		int *BmBc = new int[CHAR_SIZE];//坏字符,注意坏字符是对于S串来说的

		int n = S.size(), m = T.size();

		preBmGs(T, BmGs);
		preBmBc(T, BmBc);


		//查找匹配
		j = pos;//j记录S串匹配的起始位置
		while (j <= n - m)
		{
			for (i = m - 1; i >= 0 && T[i] == S[i + j]; --i);
			if (i < 0)
			{
				//匹配成功
				
				delete BmBc;
				delete BmGs;

				return j;

				//j += BmGs[0];//???
			}
			else
			{
				//匹配失败，j往后滑动BmBc和BmGs滑动距离中大的那个距离
				auto max = [&]()->int {
					return BmGs[i] > BmBc[S[i + j]] - m + 1 + i ? BmGs[i] : BmBc[S[i + j]] - m + 1 + i;
				};

				j += max();

			}
		}

		//匹配失败

		delete BmBc;
		delete BmGs;

		return -1;

	}


};