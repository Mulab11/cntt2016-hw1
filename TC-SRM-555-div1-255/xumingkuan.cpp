#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <sstream>
#include <typeinfo>
#include <fstream>
#include <cctype>
#include <queue>
#include <map>
using namespace std;
const int oo = 101010;
class CuttingBitString
{
	private:
	string str[40];
	int f[60];//f[i]: substring [0, i) answer
	void init(int maxlen)//get powers of 5 ("101"(2))
	{
		str[0] = "1";
		int lastlen = 1, i = 1;
		for(i = 1; lastlen <= maxlen; i++)
		{
			str[i] = str[i - 1] + "00";//"100"(2)
			for(int j = 0; j < lastlen; j++)
				if(str[i - 1][j] == '1')
					str[i][j + 2]++;//"1"(2)
			for(int j = lastlen + 1; j >= 1; j--)
				if(str[i][j] >= '2')
					str[i][j] -= 2, str[i][j - 1]++;
			if(str[i][0] >= '2')
			{
				str[i][0] -= 2;
				str[i] = "1" + str[i];
			}
			lastlen = str[i].size();
		}
	}
	public:
	int getmin(string S)
	{
		const int len = S.size();
		init(len);
		f[0] = 0;
		for(int i = 1; i <= len; i++)
		{
			f[i] = oo;
			for(int j = 0; str[j].size() <= i; j++)//dp: enumerate the power of 5 of the bit string to cut
				if(f[i - str[j].size()] + 1 < f[i] && S.substr(i - str[j].size(), str[j].size()) == str[j])
					f[i] = f[i - str[j].size()] + 1;
		}
		return f[len] >= oo ? -1 : f[len];
	}
};

