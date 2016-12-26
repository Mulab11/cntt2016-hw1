#include <algorithm>
#include <memory.h>
using namespace std;
int num[2][28];
class LittleElephantAndString
{
public:
	int getNumber(string a, string b)
	{
		int alen = a.length(), blen = b.length();
		memset(num, 0, sizeof(num));
		if(alen != blen) 
			return -1;
		for(int i = 0; i < alen; i++)
			num[0][a[i] - 'A']++;
		for(int i = 0; i < alen; i++)
			num[1][b[i] - 'A']++;
		for(int i = 0; i < 26; i++)
		{
			if(num[0][i] != num[1][i]) 
				return -1;
		}
		for(int i = 0; i < blen; i++)
		{
			int np = i;
			for(int j = 0; j < alen; j++)
			{
				if(np < blen && a[j] == b[np])
				   	np++;
			}
			if(np == alen) 
				return i;
		 } 
		 return -1;
	}
};