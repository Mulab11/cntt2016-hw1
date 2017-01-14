#include <bits/stdc++.h>

using namespace std;

const int maxn = 450005,factor_total = 1256365;

typedef long long ll;

vector<int> co[maxn];// co[i][j], \sum_{k=1}^j square_free[k*i]
int *factor[maxn],sav[factor_total]; //the memory limit is so strict,so we have to save the factors dirtily
bool prime[maxn],square_free[maxn],cube_free[maxn];//no x divides i,no x^2 divides i,no x^3 divides i
int factor_siz[maxn];

class SemiPerfectPower
{
public:
	ll cube(ll x)
	{
		return x * x * x;
	}

	void pre_treat()
	{
		int n = maxn - 5;
		for(int i = 1;i <= n;i ++) prime[i] = square_free[i] = cube_free[i] = 1;
		prime[1] = 0;
		for(int i = 2;i <= n;i ++)
			for(int j = 2;j <= n / i;j ++) prime[i * j] = 0;
		for(int i = 2;i * i <= n;i ++)
			for(int j = 1;j <= n / i / i;j ++)
				square_free[i * i * j] = 0;
		for(int i = 2;;i ++)
		{
			int v = cube(i);
			if (v > n) break;
			for(int j = 1;j <= n / v;j ++)
				cube_free[j * v] = 0;
		}
		for(int i = 2;i <= n;i ++)
			if (prime[i])
				for(int j = 1;j <= n / i;j ++)
					++ factor_siz[i * j];
		factor[1] = sav;
		for(int i = 2;i <= n;i ++) factor[i] = factor[i - 1] + factor_siz[i - 1];
		for(int i = 1;i <= n;i ++) factor_siz[i] = 0;
		for(int i = 2;i <= n;i ++)
			if (prime[i])
				for(int j = 1;j <= n / i;j ++)
					factor[i * j][factor_siz[i * j] ++] = i;
		for(int i = 1;i <= n;i ++)
			if (square_free[i])
			{
				co[i].push_back(0);
				for(int j = 1;j <= n / i;j ++)
				{
					co[i].push_back(co[i].back());
					co[i][j] += square_free[i * j];
				}
			}
	}

	ll calc(ll n)
	{
		ll ans = 0;
		for(ll a = 1;;a ++)
		{
			if (cube(a) > n) break;
			if (!square_free[a]) continue;
			//a*b^2<=n
			ll r = sqrt(n / a);
			for(;(r + 1) * (r + 1) * a <= n;r ++);
			for(;r * r * a > n;r --);
			ans += max(0ll,r - a);
		}
		for(ll x = 1;;x ++)
		{
			if (x * cube(x) > n) break;
			if (!cube_free[x]) continue;
			for(ll k = 1;cube(k) <= x;k ++)
			{
				//x = ax_2,k=sqrt(x_2y),k^2=x_2y,(a,y)=1->y=k^2/(x,k^2)
				ll p = __gcd(k * k,x);
				ll y = k * k / p,a = x / p;
				if (!square_free[a]) continue;
				ll p_low = x / y;//x<yp
				ll up = n / x / cube(y);
				ll p_up = ll(pow(up,1.0 / 3) + 1e-8); //n=x*(y*p)^3=x*y^3*p^3->p<=(n/x/y^3)^{1/3}
				for(;cube(p_up + 1) <= up;++ p_up);
				for(;cube(p_up) > up;-- p_up);
				if (p_low >= p_up) continue;
				for(int s = 0;s < (1 << factor_siz[a]);s ++) //inclusion-exclusion principle
				{
					int v = 1;
					for(int i = 0;i < factor_siz[a];i ++)
						if (s & (1 << i)) v *= factor[a][i];
					int add = co[v][p_up / v] - co[v][p_low / v];
					if (__builtin_popcount(s) & 1) ans -= add; else ans += add;
				}
			}
		}
		return ans;
	}

	ll count(ll L,ll R)
	{
		pre_treat();
		return calc(R) - calc(L - 1);
	}
};
