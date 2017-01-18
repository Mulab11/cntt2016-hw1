#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<bitset>

#define ls (t<<1)
#define rs ((t<<1)+1)
#define fi first
#define se second
#define mk make_pair
#define pb push_back

#define N 55
#define M 200005
#define seed 23333
#define Mo 998244353

using namespace std;
typedef long long ll;
const ll inf=(ll)1e11;
int i,j,m,n,p,k,vis[N],cnt[N],Q[M*10];
pair<ll,ll>dis[N]; 
vector<pair<int,pair<long long,int> > >v[N];
pair<ll,ll> check(ll length,vector <int> s1, vector <int> t1, vector <int> l1, vector <int> s2, vector <int> t2, vector <int> l2)
{
	if (length==2)
	  length=2;
	memset(vis,0,sizeof(vis));
	memset(cnt,0,sizeof(cnt));
	Q[0]=0;
	for (i=0;i<=n;++i) dis[i]=mk(inf,0),cnt[i]=1,Q[++Q[0]]=i,vis[i]=1;
	dis[0]=mk(0,0);
	for (i=0;i<=n;++i) v[i].clear();
	int l=1;
	for (i=0;i<n;++i) v[i+1].pb(mk(i,mk(-1,0)));
	//建边 
	v[n].pb(mk(0,mk(-length,-1)));
	v[0].pb(mk(n,mk(length,1)));
	for (i=0;i<(int)s1.size();++i)
	{
			if (s1[i]<t1[i])
				v[t1[i]].pb(mk(s1[i],mk(-l1[i],0)));
			else v[t1[i]].pb(mk(s1[i],mk(length-l1[i],1)));
	}
	for (i=0;i<(int)s2.size();++i)
	{
			if (s2[i]<t2[i])
				v[s2[i]].pb(mk(t2[i],mk(l2[i],0)));
			else v[s2[i]].pb(mk(t2[i],mk(-length+l2[i],-1)));
	}
	//用spfa来做差分约束,顺便可以求出当某个数<0时L前面的系数 
	for (l=1;l<=Q[0];++l)
	{
			int p=Q[l];
			if (dis[p].fi==inf) { vis[p]=0; continue; }
			for (i=0;i<(int)v[p].size();++i)
			{
					int k=v[p][i].fi;
					if (dis[p].fi+v[p][i].se.fi<dis[k].fi)
					{
							dis[k].fi=dis[p].fi+v[p][i].se.fi;
							dis[k].se=dis[p].se+v[p][i].se.se;
							if (dis[k].fi<0) return mk(0ll,dis[k].se);
							if (!vis[k])
							{
									vis[k]=1;
									++cnt[k];
									//存在一个负环,要直接判掉,否则可能来回走很多遍 
									if (cnt[k]>100) return mk(0ll,dis[k].se);
									Q[++Q[0]]=k;
							}
					}
			}
			vis[p]=0;
	}
	return mk(1ll,0);
}
class YamanoteLine{
	public:
	long long howMany(int n, vector <int> s1, vector <int> t1, vector <int> l1, vector <int> s2, vector <int> t2, vector <int> l2)
	{
		 ::n=n;
		 long long DOWN=inf,UP=-1;
		 long long l=0,r=inf,mid=0;
		 while ((l+r)>>1!=mid) //二分上界 
		 {
		 		mid=(l+r)>>1;
		 		pair<ll,ll> x=check(mid,s1,t1,l1,s2,t2,l2);
		 		if (x.fi) DOWN=r=mid;
		 		else if (x.se==0) return 0;
		 		else if (x.se>0) l=mid;
		 		else r=mid;
		 }
		 l=0; r=inf; //二分下界 
		 while ((l+r)>>1!=mid) 
		 {
		 		mid=(l+r)>>1;
		 		pair<ll,ll> x=check(mid,s1,t1,l1,s2,t2,l2);
		 		if (x.fi) UP=l=mid;
		 		else if (x.se==0) return 0;
		 		else if (x.se>0) l=mid;
		 		else r=mid;
		 }
		 if (UP>inf-5) return -1; if (UP==-1) return 0;
		 return UP-DOWN+1;
	}
}FFT;

int main()
{
	 cout<<FFT.howMany(7, {1, 3, 6, 4, 2, 4, 5, 1, 5, 2, 5, 5, 0, 0, 5, 1, 6, 1, 2, 4, 5, 6, 3}, {4, 2, 1, 2, 0, 5, 4, 5, 6, 5, 2, 1, 2, 3, 6, 2, 3, 0, 6, 5, 4, 3, 5}, {536477, 947899, 178928, 724586, 963817, 239114, 939275, 789295, 211532, 713004, 471517, 393454, 223264, 455674, 217586, 81481, 476463, 1045502, 926258, 244861, 941222, 491485, 475836}, {5, 1, 4, 3, 2, 0, 2, 1, 3, 4, 6, 1, 4, 6, 2, 0, 1}, {4, 2, 6, 0, 4, 4, 3, 0, 1, 3, 1, 0, 3, 2, 0, 6, 0}, {937903, 78534, 455914, 732223, 466737, 678325, 223494, 1045758, 875109, 948016, 171545, 1048632, 941740, 256309, 956402, 1146000, 1046372});
}
