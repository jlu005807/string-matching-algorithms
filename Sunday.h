#pragma once
#include"Index.h"


//������BM�㷨�����Ǵ�ǰ����ƥ�䣬
//��ƥ��ʧ��ʱ��ע���������вμ�ƥ�����ĩλ�ַ�����һλ�ַ���
//������ַ�û����ģʽ���г�����ֱ�����������ƶ�λ�� = ģʽ������ + 1
//�������ƶ�λ�� = ģʽ������ - ���ַ����ҳ��ֵ�λ��(��0��ʼ) = ģʽ���и��ַ����ҳ��ֵ�λ�õ�β���ľ��� + 1��


class Sunday :public Index
{
public:

	//ͬ�������ɻ��ַ�ƫ�Ʊ�
	void preBmBc(std::string T, int Bmbc[], int CHAR_SIZE = 256)
	{
		//CHAR_SIZEΪ�ַ�����Χ���˴�ΪASIZE

		int lenT = T.size();

		for (int i = 0; i < CHAR_SIZE; i++)
		{
			Bmbc[i] = lenT + 1;//δ������T�е��ַ�λ�ó�ʼ��ΪT�ĳ���+1��ƫ�Ƶĳ���
		}
		// ģʽ��P��ÿ����ĸ���ֵ������±�
	// ����Ӧ����������ƥ�����ĩλ�ַ�����һλ�ַ��ƶ�����λ������Ҫ���ƶ�λ��
		for (int i = 0; i < lenT; i++)
		{
			Bmbc[int(T[i])] = lenT - i;
		}

	}

	int index(std::string S, std::string T, int pos)
	{
		//Ԥ����
		int n = S.size(), m = T.size();
		int CHAR_SIZE = 256;//�ַ�����С
		int* Bad_shift = new int[CHAR_SIZE];
		
		preBmBc(T, Bad_shift);

		//����
		int s = pos;//��¼������ʼλ��
		int j;
		while (s <= n - m)
		{
			j = 0;
			while (S[s + j] == T[j])
			{
				j++;
				if (j >= m)//ƥ��ɹ�
				{
					return s;
				}
			}
			//�ҵ������е�ǰ��ģʽ��ƥ�����ĩ�ַ�����һ���ַ�
			//��ģʽ���г�������λ��
			//����Ҫ��(ģʽ��ĩβ+1)�ƶ�����λ�õĲ���
				s += Bad_shift[S[s + m]];
		}

		//ƥ��ʧ��
		return - 1;
	}
};