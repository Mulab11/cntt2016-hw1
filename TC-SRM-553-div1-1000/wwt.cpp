/*
令a[i]表示0->i的长度，那么我们可以根据a[i]列不等式，具体而言，就是a[i]<=a[i+1]-1，对于上界和下界同样可以列出这样的不等式，
但是在后者中，我们会涉及a[n]的值，三个变量我们是做不了差分约束的，不妨考虑，假如我们枚举了a[n]，怎么知道这个a[n]是否合法？
注意到假如系统中存在负环，那么这就是不合法的，两者互为充要。暴力显然太慢。我们考虑二分，什么时候能知道a[n]是变大，还是变小？
因为要判负环，所以我们考虑用bellman-ford，假如松弛了n^2次，那么必然有负环。对于每个i，我们维护x[i],y[i]，表示d[i]=x[i]+y[i]*a[n]，
那么假如某个时候d[i]<=0,x[i]<=0且y[i]<=0,显然无论a[n]取什么值都是不合法的，假如x[n]<=0,y[n]>0，那么当前的a[n]太小了，x[n]>=0,y[n]<0，
那么a[n]太大了，当然，有可能结束松弛时我们的环还没绕完，也就是说没有d是负数，但我们知道他肯定是个负环，
我们直接看最后一次被更新的v的y[v]来判断就好了。这样就能套二分。
*/
#include <bits/stdc++.h>
#define fe first
#define se second

using namespace std;

typedef vector<int> vi;
typedef long long ll;
typedef pair<ll,ll> pi;

class YamanoteLine
{
public:
	vector< pair<int,pi> > lk[55]; 
	int n;

	void link(int u,int v,int x,int y)
	{
		lk[u].push_back(make_pair(v,pi(x,y)));
	}

	int calc(ll an,vi &s2,vi &t2,vi &l2,vi &s1,vi &t1,vi &l1) //I make a reverse order here
	{
		for(int i = 0;i <= n;i ++) lk[i].clear();
		link(0,n,0,1),link(n,0,0,-1);
		for(int i = 0;i < n;i ++) link(i + 1,i,-1,0);
		for(int i = 0;i < s1.size();i ++)
		{
			int s = s1[i],t = t1[i],l = l1[i];
			if (s < t) link(s,t,l,0); else
				link(s,t,l,-1);
		}
		for(int i = 0;i < s2.size();i ++)
		{
			int s = s2[i],t = t2[i],l = l2[i];
			if (s < t) link(t,s,-l,0); else
				link(t,s,-l,1);
		}
		int edge_cnt = 0;
		for(int i = 0;i <= n;i ++) edge_cnt += lk[i].size();
		static pi nd[55];
		static ll d[55];
		d[0] = 0,nd[0] = pi(0,0);
		for(int i = 1;i <= n;i ++) d[i] = (1ll << 60);
		bool update;
		pi fin;
		for(int turn = 0;turn < n * n;turn ++) //bellman-ford
		{
			update = 0;
			for(int i = 0;i <= n;i ++)
				if (d[i] < (1ll << 60))
				for(int j = 0;j < lk[i].size();j ++)
				{
					int v = lk[i][j].fe;
					ll ndis = d[i] + lk[i][j].se.fe + an * 1ll * lk[i][j].se.se;
					if (ndis < d[v])
					{
						d[v] = ndis,nd[v].fe = nd[i].fe + lk[i][j].se.fe,nd[v].se = nd[i].se + lk[i][j].se.se;
						if (d[v] <= 0)//出现某个d[v]<=0，那么对于v就不合法
						{
							if (nd[v].fe <= 0 && nd[v].se <= 0) return 0; 
							if (nd[v].fe <= 0 && nd[v].se > 0) return 1;
							if (nd[v].fe > 0 && nd[v].se < 0) return 2;
						}
						update = 1;
						fin = nd[v];
					}
				}
		}
		if (!update) return 3; //假如不存在负环，那么必然合法
		if (fin.se > 0) return 1;//最后一个更新的点必然在负环上
		if (fin.se < 0) return 2;
	}

	long long howMany(int __n,vi s1,vi t1,vi l1,vi s2,vi t2,vi l2)
	{
		n = __n;
		ll l = 0,r = (1ll << 50),tmp = r + 1; //二分上界
		for(ll mid;l <= r;)
		{
			mid = l + r >> 1;
			int sig = calc(mid,s1,t1,l1,s2,t2,l2);
			if (!sig) return 0;
			if (sig == 3) {tmp = mid,l = mid + 1;continue;}
			if (sig == 1) l = mid + 1; else r = mid - 1;
		}
		if (tmp == (1ll << 50) + 1) return 0;
		l = 0,r = (1ll << 50);
		ll dow = -1;//二分下界
		for(ll mid;l <= r;)
		{
			mid = l + r >> 1;
			int sig = calc(mid,s1,t1,l1,s2,t2,l2);
			if (!sig) return 0;
			if (sig == 3) {dow = mid,r = mid - 1;continue;}
			if (sig == 1) l = mid + 1; else r = mid - 1;
		}
		if (dow == -1) return 0;
		if (!dow || tmp == (1ll << 50)) return -1;
		return tmp - dow + 1;
	}
};
