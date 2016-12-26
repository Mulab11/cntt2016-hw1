#include <bits/stdc++.h>

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
const int maxn=55;
int prex[maxn],num[maxn];
int n,m,need[maxn],mns[maxn],cnt[maxn];
string ans;

/*
简单来说，两个监测数量不同的摄像头不可能完全重合，因此只要把相同的放在一起考虑即可。
如此一来可以求出哪些区间符合要求，然后check一下每个点的状态即可
*/

class SurveillanceSystem{
public:
	string getContainerInfo(string ctn,vector<int>rpt,int L){
		n=ctn.size(),m=rpt.size();
		rep(i,0,m-1) need[rpt[i]]++;
		prex[0]=0;
		rep(i,1,n) prex[i]=prex[i-1]+(ctn[i-1]=='X');
		rep(i,1,n-L+1) num[i]=prex[i+L-1]-prex[i-1],cnt[num[i]]++;
		rep(i,1,n){
			bool bjs=0;
			rep(j,max(1,i-L+1),min(i,n-L+1)) if (need[num[j]]){bjs=1;break;}
			if (!bjs){ans+='-';continue;}
			memset(mns,0,sizeof mns);
			rep(j,max(1,i-L+1),min(i,n-L+1)) mns[num[j]]++;
			rep(j,0,n) if (mns[j]+need[j]>cnt[j]){bjs=0;break;}
			if (!bjs) ans+='+';
				else ans+='?';
		}
		return ans;
	}
};
