#include <bits/stdc++.h>

using namespace std;

class TomekPhone
{
public:
	int minKeystrokes(vector <int> f, vector <int> key)
	{
		vector<int> ava;
		ava.clear();
		sort(f.begin(),f.end());
		reverse(f.begin(),f.end());
		//直接贪心，根据排序原理得到正确性。
		for(int i = 0;i < key.size();i ++)
			for(int j = 1;j <= key[i];j ++) ava.push_back(j);
		sort(ava.begin(),ava.end());
		if (f.size() > ava.size()) return -1;
		int ans = 0;
		for(int i = 0;i < f.size();i ++)
			ans += f[i] * ava[i];
		return ans;
	}
};
