#include <bits/stdc++.h>

using namespace std;

class StringGame
{
public:
	vector<int> getWinningStrings(vector<string> S)
	{
		static int co[100][300];
		static bool exi[100],use[300];
		vector<int> out;
		memset(co,0,sizeof co);
		//比较大小就等价于谁最小的字母更多（相同就比下一个字母）
		for(int i = 0;i < S.size();i ++)
			for(auto p:S[i]) co[i][p] ++;
		for(int i = 0;i < S.size();i ++)
		{
			bool ok = 1;
			//exist[i]表示第i个字母当前是否已经被打败了
			memset(exi,1,sizeof exi);
			memset(use,0,sizeof use);
			for(int j = 0;j < 26;j ++)
			{
				int ch = -1;
				for(int c = 'a';c <= 'z';c ++)
					if (!use[c])
					{
						bool fal = 0;
						for(int k = 0;k < S.size();k ++)
							if (i != k && exi[k] && co[k][c] > co[i][c]) {fal = 1;break;} //假如存在一个exist[i]=1且count[i][c]>当前串，那么这个c当前就是不合法的
						if (!fal) {ch = c;break;}
					}
				if (ch == -1) {ok = 0;break;}
				use[ch] = 1;
				for(int k = 0;k < S.size();k ++)
					if (co[k][ch] < co[i][ch]) exi[k] = 0;
			}
			//最后输掉的情况就是：最后有exist[i]=1或字母表不能确定完。
			for(int k = 0;k < S.size();k ++)
				if (i != k && exi[k]) {ok = 0;break;}
			if (!ok) continue;
			out.push_back(i);
		}
		return out;
	}
};
