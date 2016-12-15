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

class FoxAndHandle
{
	private:
	int n, cnt[300], cnt2[300];//count letters
	public:
	string lexSmallestName(string S)
	{
		n = S.size();
		string name(n >> 1, 'a');
		memset(cnt, 0, sizeof(cnt));
		for(int i = 0; i < n; i++)
			cnt[S[i]]++;
		for(char i = 'a'; i <= 'z'; i++)
			cnt[i] >>= 1;
		int now = 0;//name[0,i) --- S[0,now)
		for(int i = 0; i < (n >> 1); i++)//name[i]
			for(char &j = name[i]; j <= 'z'; j++)//try letter j
			{
				if(!cnt[j])//there is no letter j in name
					continue;
				int tmp = now;
				while(tmp < n && S[tmp] != j)
					tmp++;
				if(tmp == n)//there is no letter j in S
					continue;
				memcpy(cnt2, cnt, sizeof(cnt));
				const int tmp2 = tmp + 1;
				cnt2[j]--;
				bool ok = true;
				for(int ii = i + 1; ii < (n >> 1); ii++)
				{
					while(tmp < n && !cnt2[S[tmp]])
						tmp++;
					if(tmp == n)//invalid name
					{
						ok = false;
						break;
					}
					cnt2[S[tmp++]]--;
				}
				if(ok)//choose letter j
				{
					cnt[j]--;
					now = tmp2;
					break;
				}
			}
		return name;
	}
};

