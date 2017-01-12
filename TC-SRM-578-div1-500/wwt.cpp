#include <bits/stdc++.h>

using namespace std;

const int mo = int(1e9) + 7;

class WolfInZooDivOne
{
public:
	void decode(vector<string> a,vector<int> &b)
	{
		b.clear();
		int x = 0;
		bool exi = 0;
		for(auto i : a)
			for(auto j : i)
			{
				if (j == ' ')
				{
					if (exi) b.push_back(x);
					x = 0,exi = 0;
				} else x = x * 10 + j - 48,exi = 1;
			}
		if (exi) b.push_back(x);
	}

	int count(int N, vector <string> L, vector <string> R)
	{
		vector<int> l,r;
		decode(L,l),decode(R,r);
		static int mx[305];
		memset(mx,0,sizeof mx);
		for(int i = 0;i < l.size();i ++)
			mx[l[i] + 1] = max(mx[l[i] + 1],r[i] + 1); //define r[i] as i's rightmost matched point,mx[i]=max(j<=i,r[j])
		for(int i = 1;i <= N;i ++)
			mx[i] = max(mx[i - 1],mx[i]);
		static int f[2][305][305]; //to save some memory
		memset(f,0,sizeof f);
		f[0][0][0] = 1;
		int cr = 0;
		for(int i = 1;i <= N;i ++)
		{
			cr ^= 1;
			memset(f[cr],0,sizeof f[cr]);
			for(int j = 0;j < i;j ++)
				for(int k = 0;k <= j;k ++) //the last two wolves 
					if (f[cr ^ 1][j][k])
					{
						f[cr][j][k] = (f[cr][j][k] + f[cr ^ 1][j][k]) % mo;
						if (i <= mx[k]) continue; //no interval covers k->i
						f[cr][i][j] = (f[cr][i][j] + f[cr ^ 1][j][k]) % mo;
					}
		}	
		int ans = 0;
		for(int i = 0;i <= N;i ++)
			for(int j = 0;j <= N;j ++)
				ans = (ans + f[cr][i][j]) % mo;
		return ans;
	}
};
