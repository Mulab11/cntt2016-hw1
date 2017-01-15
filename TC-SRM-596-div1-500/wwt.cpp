#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

class BitwiseAnd
{
public:
	bool legal(vector<ll> s)
	{
		for(int i = 0;i < s.size();i ++)
			for(int j = i + 1;j < s.size();j ++)
				if (!(s[i] & s[j])) return 0; else
					for(int k = j + 1;k < s.size();k ++)
						if (s[i] & s[j] & s[k]) return 0;
		return 1;
	}

	vector<ll> lexSmallest(vector<ll> s, int n)
	{
		sort(s.begin(),s.end());
		if (!legal(s)) return {};
		if (s.size() == n) return s;
		ll new_v = 0,put_new_bit = 0;
		static bool match[55];//new_v & s[i] > 0
		memset(match,0,sizeof match);
		for(int i = 0;i < 60;i ++) //new_v should be < 2^60
		{
			int a = -1,b = -1;//save a,b where s[a] & (1 << i),s[b] & (1 << i)
			for(int j = 0;j < s.size();j ++)
				if (s[j] & (1ll << i)) b = a,a = j;
			if (a == -1) //a new bit
			{
				if (put_new_bit < n - s.size() - 1) //extra bits for the remaining numbers
					new_v |= (1ll << i),put_new_bit ++;
			} else
				if (b == -1 && !match[a]) //s[a] & s[b] & new_v = 0,no need to match the same s[a] twice
					match[a] = 1,new_v |= (1ll << i);
		} 
		for(int i = 0;i < s.size();i ++)
			if (!match[i]) return {};
		if (put_new_bit < n - s.size() - 1) return {};
		s.push_back(new_v);
		return lexSmallest(s,n);
	}
};
