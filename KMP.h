#pragma once
#include"Index.h"
#include"assert.h"
//һ���������ߵĶ�Զ����������˳��ʱ���ߵĶ�죬�����������澳ʱ������ҵ��������Լ���
//                                                                          --KMP

//KMP�㷨��ȫ��ΪKnuth - Morris - Pratt�㷨����һ�ָ�Ч���ַ���ƥ���㷨��
//��ͨ��Ԥ����ģʽ�����Ӵ���������һ������ƥ���Ҳ��Ϊnext���飩��
//ʹ�����ı�������������ƥ��ʱ����������ƥ���������ܹ�������ƥ��Ĳ�����Ϣ����ģʽ���������󻬶��������ͷ��ʼƥ�䣬�Ӷ����ƥ��Ч�ʡ�

//����ʹ�������±�
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

		
		//���j = -1�����ߵ�ǰ�ַ�ƥ��ɹ�����S[i] == P[j]��������i++��j++
		while (i < sl && j < tl)
		{
			if (j == -1 || S[i] == T[j])
			{
				i++;
				j++;
			}
			else
			{
				//���j != -1���ҵ�ǰ�ַ�ƥ��ʧ�ܣ���S[i] != P[j]�������� i ���䣬j = next[j]    
			    //next[j]��Ϊj����Ӧ��nextֵ 
				j = next[j];
			}

			/*std::cout << S.size() << " " << T.size() << std::endl;

			std::cout << i << " " << j << std::endl;

			if (j <T.size()) { std::cout << "ozy";
			}

			system("Pause");*/
			//ע��string��size()���ص���size_t�޷����������޷�ֱ���븺���Ƚϣ�����

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
		int j = 0;//����j�±�ǰT��������ǰ��׺
		while (j < T.size() - 1)
		{
			//p[k]��ʾǰ׺��p[j]��ʾ��׺
			if (k == -1 || T[j] == T[k])
			{
				++k;
				++j;
				next[j] = k;
			}
			else
			{
				//�ݹ���������ǰ��׺
				k = next[k];
			}
		}
	}
	

	//����ƥ��ʧ��λ�ú���ת����λ�ñȽϣ��Ż�next����
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
				//��֮ǰnext�����󷨣��Ķ�������4��
				if (T[j] != T[k])
					next[j] = k;   //֮ǰֻ����һ��
				else
					//��Ϊ���ܳ���p[j] = p[ next[j ]]�����Ե�����ʱ��Ҫ�����ݹ飬k = next[k] = next[next[k]]
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