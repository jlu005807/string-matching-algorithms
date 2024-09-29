#pragma once
#include"Index.h"


//���������˺úͻ�����Ż��ߵø��� --BM


//���ַ����򣺵��ı����е�ĳ���ַ���ģʽ����ĳ���ַ���ƥ��ʱ��
//���ǳ��ı����е����ʧ���ַ�Ϊ���ַ�����ʱģʽ����Ҫ�����ƶ���
//�ƶ���λ�� = ���ַ���ģʽ���е�λ�� - ���ַ���ģʽ�������ҳ��ֵ�λ�á����⣬���"���ַ�"��������ģʽ��֮�У������ҳ���λ��Ϊ - 1��

//�ú�׺����
//��ƥ��ʧ��ʱ���Ѿ�ƥ��ɹ������ַ�����Ϊ�ú�׺�����ʱ��ͬ�����һ���ģʽ��
//�ƶ���λ�� = �ú�׺��ʼ��ģʽ��ƥ��λ�� - �ú�׺��ģʽ������һ�γ���λ�õ���ʼλ�ã�����ú�׺����ģʽ���г��֣���һ��λ��Ϊ - 1


class BM :public Index
{

public:
	//���ɻ��ַ�ƫ�Ʊ�
	void preBmBc(std::string T, int Bmbc[])
	{
		int CHAR_SIZE = 256;//�ַ�����Χ���˴�ΪASIZE
		
		int lenT = T.size();
		
		for (int i = 0; i < CHAR_SIZE; i++)
		{
			Bmbc[i] = lenT;//δ������T�е��ַ�λ�ó�ʼ��ΪT�ĳ���
		}

		for (int i = 0; i < lenT; i++)
		{
			Bmbc[int(T[i])] = lenT - i - 1;//��¼�ַ����������T������ҵĴ����ַ���T���һ���ַ��ľ���
		}

	}

	//����suffix�������������ɺú�׺ƫ�Ʊ�
	//suffix[ i ] = shift ��ʾ�� i Ϊ�ұ߽磬��ģʽ��T��׺ƥ�����󳤶ȣ�
	//�༴T[i - shift + 1 , i] = T[len - shift , len - 1]
	//�˷�������⣬�м�ʵ��
	void suffixes(std::string T, int suffix[])
	{
		int lenT = T.size();

		suffix[lenT - 1] = lenT;//���һ���ַ���ƥ�䳤�Ⱦ���T������

		int g = lenT - 1;//��ʾ��ǰ�ұ߽�

		int f=lenT-2;//��ǰ��׺��ʼλ��(�������ң�

		for (int i = lenT - 2; i >= 0; i--)//�����ڶ����ַ���ǰ����
		{
			if (i > g && suffix[i + lenT - 1 - f] < i - g)
			{
				//��i>gʱ��T[g+1,f]�Ѿ���ƥ����T[lenT-1-f+g+1,lenT-1]
				//
				/*std::cout << i << " " << g << " " << f << " ";
				system("Pause");*/
				suffix[i] = suffix[i + lenT - 1 - f];//�̳�֮ǰ�����ֵ
			}
			else
			{

				if (i < g)g = i;//������ݵ��߽���ߣ�������ұ߽�

				f = i;//���µ�ǰ��׺����ʼλ��

				while (g >= 0 && T[g] == T[g + lenT - 1 - f])--g;

				suffix[i] = f - g;
			}

		}
	}

	//������suffix������
	void simply_suffixes(std::string T, int suffix[])
	{
		int lenT = T.size();
		
		//ͬ�����һ���ַ���ƥ�䳤�Ⱦ���T������
		suffix[lenT - 1] = lenT;

		//����ѭ��
		for (int i = lenT - 2; i >= 0; i--)
		{
			int j = 0;//��¼�Ѿ�ƥ�䳤��
			for (j; j <= i && T[i - j] == T[lenT - j - 1]; j++) {}
			suffix[i] = j;
		}

	}

	
	int index(std::string S, std::string T, int pos)
	{
		return 0;
	}


};