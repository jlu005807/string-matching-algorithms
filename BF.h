#pragma once
#include"Index.h"


//ֻҪÿ�ζ�ǰ��һ��㣬������һ���ᵽ���յ�
//                                      --BF


//ʹ�������±꣬�����ַ���λ��
//�����ַ���ƥ��
//����ģʽT������s�е�pos���ַ���ʼ��һ�γ��ֵ�λ�á��������ڣ� �򷵻�ֵΪ-1
class BF:public Index
{
public:
	int index(std::string S, std::string T, int pos)
	{

	if (pos<0)
	{
		return -1;//pos����
	}

	//��ʼ��
	int i = pos;
	int j = 0;

	while (i < S.size()-T.size()+1 && j < T.size())//��������δ�Ƚϵ���β
	{
		/*std::cout << i << " " << j << std::endl;*/
		if (S[i] == T[j])//���ǰ��
		{
			i++;
			j++;
		}
		else//ʧ�ܻ���
		{
			i = i - j + 1;
			j = 0;
		}
	}

	//ƥ��ɹ�
	if (j >= T.size())
	{
		return i - T.size();
	}
	else//ƥ��ʧ��
	{
		return -1;
	}
	}
};
