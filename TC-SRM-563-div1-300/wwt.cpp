/*
逐位确定。判合法时这样判：令need[i]表示这个字母还需要放多少进ans串里。那么首先，因为前bit位已经确定，那么我们只能先让前bit位全部出现，
接下来，对于一个字符c，假如need[c]>0，那么我们显然把他放进ans里能保证合法性，放完所有字符后判断是否有need[i]>0的情况或前bit位不能全部出现。
*/
#include <bits/stdc++.h>

using namespace std;

class FoxAndHandle
{
public:
	string __S;
	char st[100];
	int co[300],ok[300];

	bool test(int bit)
	{
		int need[300];
		for(char a = 'a';a <= 'z';a ++)
			need[a] = co[a] / 2;		
		int pos = 0;
		for(int i = 0;i < __S.length();i ++)
		{
			if (pos <= bit)
			{
				if (__S[i] == st[pos]) pos ++,need[__S[i]] --;
			} else
			{
				if (need[__S[i]]) ++ pos,need[__S[i]] --;
				if (pos == __S.length()) break;
			}
		}
		if (pos <= bit) return 0;
		for(char a = 'a';a <= 'z';a ++)`
			if (need[a]) return 0;
		return 1;
	}

	string lexSmallestName(string S)
	{
		__S = S;
		memset(co,0,sizeof co);
		for(int i = 0;i < S.length();i ++)
			co[S[i]] ++;
		for(char a = 'a';a <= 'z';a ++) ok[a] = co[a] / 2;
		for(int i = 0;i < S.length() / 2;i ++)
			for(char a = 'a';a <= 'z';a ++)
				if (ok[a])  //逐位确定
				{
					ok[a] --;
					st[i] = a;
					if (test(i)) break;
					ok[a] ++;
				}
		string tmp = "";
		for(int i = 0;i < S.length() / 2;i ++)
			tmp = tmp + st[i];
		return tmp;
	}
};
