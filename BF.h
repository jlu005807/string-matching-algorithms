#pragma once
#include"Index.h"


//只要每次都前进一点点，我相信一定会到达终点
//                                      --BF


//使用数组下标，而非字符的位置
//朴素字符串匹配
//返回模式T在主串s中第pos个字符开始第一次出现的位置。若不存在， 则返回值为-1
class BF:public Index
{
public:
	int index(std::string S, std::string T, int pos)
	{

	if (pos<0)
	{
		return -1;//pos错误
	}

	//初始化
	int i = pos;
	int j = 0;

	while (i < S.size()-T.size()+1 && j < T.size())//两个串均未比较到串尾
	{
		/*std::cout << i << " " << j << std::endl;*/
		if (S[i] == T[j])//相等前移
		{
			i++;
			j++;
		}
		else//失败回溯
		{
			i = i - j + 1;
			j = 0;
		}
	}

	//匹配成功
	if (j >= T.size())
	{
		return i - T.size();
	}
	else//匹配失败
	{
		return -1;
	}
	}
};
