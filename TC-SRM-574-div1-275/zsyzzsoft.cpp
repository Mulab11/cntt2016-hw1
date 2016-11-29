#include <algorithm>
#include <string.h>
using namespace std;
class TheNumberGame
{
public:
	char sa[10], sb[10];
	string determineOutcome(int a, int b)
	{
		sprintf(sa, "%d", a);
		sprintf(sb, "%d", b);
		int n = strlen(sa), m = strlen(sb);
		for(int i = 0; i + m <= n; i++) //匹配a的一个字串 
		{
			bool match = true;
			for(int j = 0; j < m && match; j++)
				match &= sa[i + j] == sb[j];
			if(match)
				return "Manao wins";
		}
		for(int i = 0; i + m <= n; i++) //翻转再匹配 
		{
			bool match = true;
			for(int j = 0; j < m && match; j++)
				match &= sa[i + j] == sb[m - j - 1];
			if(match)
				return "Manao wins";
		}
		return "Manao loses";
	}
};