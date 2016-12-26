#include<bits/stdc++.h>

#define rep(x,a,b) for (int x=a;x<=(int)b;x++)
#define drp(x,a,b) for (int x=a;x>=(int)b;x--)
#define cross(x,a) for (int x=hd[a];~x;x=nx[x])
#define ll long long
#define inf (1<<29)
#define PII pair<int,int>
#define PDD pair<double,double>
#define mk(a,b) make_pair(a,b)
#define fs first
#define sc second
#define pb push_back
#define VI vector<int>
using namespace std;
const int maxk=1000005;
string s;
int n;
double f[maxk],g[maxk];

/*
期望线性性罗上去就好了
选一个点的概率是i*(n-i+1)/binom(n,2)
然后上面的值的期望就直接枚举最后一次操作它的时间，然后等比数列搞搞就好了
*/

struct TheSwapsDivOne{
	double find(vector<string>seq,int k){
		rep(i,0,seq.size()-1) s+=seq[i];
		puts(s.c_str());
		n=s.size();
		g[0]=1;
		rep(i,1,k){
			f[i]=(f[i-1]*(+n*(n-1)/2-1)+g[i-1])/(n*(n-1)/2);
			g[i]=1-f[i]*(n-1);
		}
		double ans=0;
		int sum=0;
		rep(i,0,n-1) sum+=s[i]-'0';
		rep(i,0,n-1){
			double prob=1.0*(i+1)*(n-i)/(n*(n-1)/2+n);
			ans+=prob*(g[k]*(s[i]-'0')+f[k]*(sum-s[i]+'0'));
		}
		return ans;
	}
};
