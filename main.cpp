#include"BF.h"
#include"KMP.h"
#include"BM.h"
#include"Sunday.h"



//我所写的字符串匹配函数，皆是以数组下标为操作数，而非字符位置！！！
int main()
{

	/*std::string e("abcabcdefjkbc");

	const int i = e.size();
	int a[13], b[13];

	BM bm;

	clock_t n = clock();

	
	bm.suffixes("BABAAB", a);

	clock_t p = clock();

	int d1=p-n;

	n = clock();

	for (int i = 0; i < 50000; i++)
	bm.simply_suffixes(e, b);

	p = clock();

	int d2 = p - n;

	for (int i = 0; i < 13; i++)
	{
		std::cout << a[i] << " ";
	}

	std::cout <<d1<< std::endl;
	for (int i = 0; i < 13; i++)
	{
		std::cout << b[i] << " ";
	}
	std::cout << d2 << std::endl;*/


	std::string S("maba66o");

	std::string T("a6");

	BF bf;

	KMP kmp;

	BM bm;

	Sunday sunday;

	std::cout << "S:" << S << std::endl;

	std::cout << "T:" << T << std::endl;

	std::cout << bf.index(S, T, 0) << std::endl;

	std::cout << kmp.index(S, T, 0) << std::endl;

	std::cout << bm.index(S, T, 0) << std::endl;

	std::cout << sunday.index(S, T, 0) << std::endl;

	system("Pause");
}