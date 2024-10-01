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
	void preBmBc(std::string T, int Bmbc[],int CHAR_SIZE=256)
	{
		//CHAR_SIZEΪ�ַ�����Χ���˴�ΪASIZE
		
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
				//���ݶԳ��ԣ���ʱT[i]����T[i+lenT-1-f],
				//��suffix[i+lenT-1-f]<i-gʱ������suffix�ĺ��壬T[i+lenT-1-f]Ϊ�ұ߽����ƥ����ַ�������T[i]��ƥ����ַ�����
				//����suffix[i+lenT-1-f]<i-g���Ϳ���ֱ��ӳ��suffix[i] = suffix[i + lenT - 1 - f]
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
			for (j; j <= i && T[i - j] == T[lenT - j - 1]; j++);
			suffix[i] = j;
		}

	}



	//���ɺú�׺ƫ�Ʊ�
	//BmGs[i]��ʾ�����ú�׺ʱ��ģʽ��Ӧ���ƶ��ľ��룬i ָ��ú�׺����һ��λ�ã�Ҳ���ǻ��ַ���λ��
	void preBmGs(std::string T,int BmGs[])
	{
		int j;

		int lenT = T.size();

		int* suffix = new int[T.size()];

		suffixes(T, suffix);//����suffix������

		for (int i = 0; i < lenT; i++)
		{
			BmGs[i] = lenT;//��ʼ��BmGs����ʼ״̬ʱû���Ӵ��ͺú�׺ƥ�������ƶ�����Ϊ����ģʽ���ĳ���
		}


		for (int i = lenT - 1; i >= 0; i--)
		{
			if (suffix[i] == i + 1)
			{
				//suffix[i] == i + 1 ˵��0��i��i + 1���ַ�ǰ׺�ͺ�׺ƥ��
				// ����ǰ׺ƥ�们�������
				//��ôlenT-i-2�������ַ���λ�ã�����[0,lenT-i-2]��������ת������ΪlenT-i-1
				for (int j=0; j < lenT - 1 - i; j++)
				{
					if (BmGs[j] == lenT)
					{
						BmGs[j] = lenT - 1 - i;
					}
				}
			}
		}

		//GS[i]�ĺ����Ǻú�׺�Ŀ�ͷ��ǰһ���ַ�Ҳ���ǻ��ַ�λ�ö�Ӧ�Ļ������룬
		//��ôGS[len - 1 - suffix[i]]�е�len - 1 - suffix[i]��Ӧ��һ����һ�����ַ���λ��
		for (int i = 0; i <= lenT - 2; i++)
		{
			BmGs[lenT - 1 - suffix[i]] = lenT - 1 - i;
		}

		delete suffix;//ɾ��suffix

	}

	
	int index(std::string S, std::string T, int pos)
	{
		//Ԥ��������ƫ�Ʊ�
		int CHAR_SIZE = 256;
		int i,j;
		int *BmGs = new int[T.size()];//�ú�׺
		int *BmBc = new int[CHAR_SIZE];//���ַ�,ע�⻵�ַ��Ƕ���S����˵��

		int n = S.size(), m = T.size();

		preBmGs(T, BmGs);
		preBmBc(T, BmBc);


		//����ƥ��
		j = pos;//j��¼S��ƥ�����ʼλ��
		while (j <= n - m)
		{
			for (i = m - 1; i >= 0 && T[i] == S[i + j]; --i);
			if (i < 0)
			{
				//ƥ��ɹ�
				
				delete BmBc;
				delete BmGs;

				return j;

				//j += BmGs[0];//???
			}
			else
			{
				//ƥ��ʧ�ܣ�j���󻬶�BmBc��BmGs���������д���Ǹ�����
				auto max = [&]()->int {
					return BmGs[i] > BmBc[S[i + j]] - m + 1 + i ? BmGs[i] : BmBc[S[i + j]] - m + 1 + i;
				};

				j += max();

			}
		}

		//ƥ��ʧ��

		delete BmBc;
		delete BmGs;

		return -1;

	}


};