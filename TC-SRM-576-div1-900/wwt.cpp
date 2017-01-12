#include <bits/stdc++.h>

using namespace std;

const int mo = int(1e9) + 9;

class CharacterBoard
{
public:
	set<int> T; //to save the relevant w

	int pow(int a,int b)
	{
		int tmp = 1;
		for(;b;b >>= 1,a = a * 1ll * a % mo)
			if (b & 1) tmp = tmp * 1ll * a % mo;
		return tmp;
	}

	int calc(int w,vector<string> &f,int sx,int sy,int W)
	{
		int n = f.size(),m = f[0].length();
		map<int,char> fixed;
		fixed.clear();
		for(int i = 0;i < n;i ++)
			for(int j = 0;j < m;j ++)
			{
				int cv = ((sx + i) * 1ll * W + sy + j) % w;
				if (fixed[cv] && f[i][j] != fixed[cv]) return 0;
				fixed[cv] = f[i][j]; 
			}
		return pow(26,w - fixed.size());
	}

	int countGenerators(vector<string> fragment,int W,int i0,int j0)
	{
		int n = fragment.size(),m = fragment[0].length();
		T.clear();
		vector<long long> a;
		a.clear();
		for(int i = 0;i < n;i ++)
			for(int j = 0;j < m;j ++) a.push_back((i0 + i) * 1ll * W + j0 + j);
		sort(a.begin(),a.end());
		map<long long,bool> apear;
		apear.clear();
		for(int i = 0;i < a.size();i ++)
			for(int j = i + 1;j < a.size();j ++)
			{
				long long v = a[j] - a[i];
				if (apear[v]) continue; //avoid useless work
				apear[v] = 1;
				for(int d = 1;d * 1ll * d <= v;d ++) //only v's divisor will make effects on (i,j)
					if (v % d == 0)
					{
						if (d <= W) T.insert(d);
						if (v / d <= W) T.insert(v / d);
					}
			}
		//initial answer is equal to 26^0+26^1+....+26^(w-n*m)
		int ans = 0;
		if (W >= n * m)
			ans = (pow(26,W - n * m + 1) - 1 + mo) % mo * 1ll * pow(25,mo - 2) % mo;
		for(auto p : T)
		{
			ans = (ans + calc(p,fragment,i0,j0,W)) % mo;
			if (p >= n * m)
				ans = (ans - pow(26,p - n * m) + mo) % mo;//minus extra counts
		}
		return ans;
	}
};
