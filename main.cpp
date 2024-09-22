#include"BF.h"
#include"KMP.h"





int main()
{
	std::string S("maba66o");

	std::string T("aba");

	BF bf;

	KMP kmp;

	std::cout << "S:" << S << std::endl;

	std::cout << "T:" << T << std::endl;

	std::cout << bf.index(S, T, 0) << std::endl;

	std::cout << kmp.index(S, T, 0) << std::endl;

	system("Pause");
}