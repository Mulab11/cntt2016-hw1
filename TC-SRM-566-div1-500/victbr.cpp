#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 360,mod = 1e9+7;

struct Ans{
	int a[N],len;
};
Ans operator * (const Ans &a,const Ans &b){
	Ans c;
	memset(c.a,0,sizeof(c.a));c.len = a.len;
	for (int i = 0;i < a.len;i++)
		 for (int j = 0;j < a.len;j++)
		 	c.a[(i+j)%a.len] = (c.a[(i+j)%a.len]+(ll)a.a[i]*b.a[j]%mod)%mod;
	return c;
}

class PenguinEmperor{
	public:
		long long step;
		int f[N][N];
		Ans ans,g;
		int countJourneys(int numCities, long long daysPassed){
			memset(f,0,sizeof(f));
			memset(ans.a,0,sizeof(ans.a));
			memset(g.a,0,sizeof(g.a));
			f[0][0] = 1;
			for (int i = 1;i <= numCities;i++)
				for (int j = 0;j < numCities;j++){
					if ((j+i)%numCities == (numCities+j-i)%numCities)
						f[i][j] = f[i-1][(j+i)%numCities];
					else
						f[i][j] = add(f[i-1][(j+i)%numCities],f[i-1][(numCities+j-i)%numCities]);			
				}
			if (numCities >= daysPassed)
				return f[daysPassed][0];
			ans.len = numCities;
			ans.a[0] = 1;
			g.len = numCities;
			for (int i = 0;i < numCities;i++)
				g.a[i] = f[numCities][i];
			step = daysPassed/numCities;
			while (step){
				if (step&1) ans = ans * g;
				g = g * g;
				step >>= 1;
			}
			
			step = daysPassed%numCities;
			for (int i = 0;i < numCities;i++)
				g.a[i] = f[step][i];
			ans = ans * g;
			return ans.a[0];			
		}
		int add(int x,int y){
			x += y;
			while (x >= mod) x -= mod;
			return x;
		}
};
