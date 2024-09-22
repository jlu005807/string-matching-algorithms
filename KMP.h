#pragma once
#include"Index.h"
#include"assert.h"
//一个人能能走的多远不在于他在顺境时能走的多快，而在于他在逆境时多久能找到曾经的自己。
//                                                                          --KMP

//KMP算法，全称为Knuth - Morris - Pratt算法，是一种高效的字符串匹配算法。
//它通过预处理模式串（子串），构建一个部分匹配表（也称为next数组），
//使得在文本串（主串）中匹配时，当遇到不匹配的情况，能够利用已匹配的部分信息，将模式串合理地向后滑动，避免从头开始匹配，从而提高匹配效率。

//依旧使用数组下标
class KMP :public Index
{
public:


	int index(std::string S, std::string T, int pos)
	{
	    std::shared_ptr<int[]> next(new int[T.size()], std::default_delete<int[]>());

		get_next(T, next);

		/*for (int k = 0; k < T.size(); k++)
		{
			std::cout << next[k] << " ";
		}*/

		/*std::cout << std::endl;*/

		int i = 0;
		int j = 0;

		int sl = S.size();
		int tl = T.size();

		
		//如果j = -1，或者当前字符匹配成功（即S[i] == P[j]），都令i++，j++
		while (i < sl && j < tl)
		{
			if (j == -1 || S[i] == T[j])
			{
				i++;
				j++;
			}
			else
			{
				//如果j != -1，且当前字符匹配失败（即S[i] != P[j]），则令 i 不变，j = next[j]    
			    //next[j]即为j所对应的next值 
				j = next[j];
			}

			/*std::cout << S.size() << " " << T.size() << std::endl;

			std::cout << i << " " << j << std::endl;

			if (j <T.size()) { std::cout << "ozy";
			}

			system("Pause");*/
			//注意string的size()返回的是size_t无符号整数，无法直接与负数比较！！！

		}

		if (j == T.size())
		{
			return i - T.size();
		}
		else
		{
			return -1;
		}

	}

	void get_next(std::string T,std::shared_ptr<int[]>& next)
	{
		next[0] = -1;
		int k = -1;
		int j = 0;//计算j下标前T的最大相等前后缀
		while (j < T.size() - 1)
		{
			//p[k]表示前缀，p[j]表示后缀
			if (k == -1 || T[j] == T[k])
			{
				++k;
				++j;
				next[j] = k;
			}
			else
			{
				//递归求最大相等前后缀
				k = next[k];
			}
		}
	}
	

	//根据匹配失败位置和跳转到的位置比较，优化next数组
	void get_valnext(std::string T, std::shared_ptr<int[]>& next)
	{
		next[0] = -1;
		int k = -1;
		int j = 0;
		while (j < T.size() - 1)
		{
			if (k == -1 || T[j] == T[k])
			{
				++k;
				++j;
				//较之前next数组求法，改动在下面4行
				if (T[j] != T[k])
					next[j] = k;   //之前只有这一行
				else
					//因为不能出现p[j] = p[ next[j ]]，所以当出现时需要继续递归，k = next[k] = next[next[k]]
					next[j] = next[k];
			}
			else
			{
				k = next[k];
			}
		}
	}

	void next_to_valnext(std::string T, std::shared_ptr<int[]>& next)
	{
		for (int i = 0; i < T.size(); i++)
		{
			if (T[i]==T[next[i]])
			{
				next[i] = next[next[i]];
			}
		}
	}
};