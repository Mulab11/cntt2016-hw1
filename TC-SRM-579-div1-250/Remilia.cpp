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
#define mod 1000007
const int maxn=52;
string buf;
int n,hd[mod],to[maxn*maxn],nx[maxn*maxn],cnt;
void add(int u,int x){
	cross(i,u){
		int v=to[i];
		if (v==x) return;
	}
	to[cnt]=x;nx[cnt]=hd[u];hd[u]=cnt++;
}
bool find(int u,int x){
	cross(i,u){
		int v=to[i];
		if (v==x) return 1;
	}
	return 0;
}

/*
使用操作3。那么一定会撤销到先前出现过的最长前缀，然后一直使用操作1。

不使用操作3。那么一定是从上一个字符串一直使用操作1。(此时要求上一个字符串是这个字符串的前缀)

由于这两种方法产生的撤销历史记录是等价的，直接贪心选取最优的即可。
*/

class UndoHistory{
public:
	int minPresses(vector<string>lns){
		n=lns.size();
		int ans=0,hs1=0,hs2=0;
		memset(hd,-1,sizeof hd);
		add(0,0);
		rep(i,0,n-1){
			int need=2,nh1=0,nh2=0;
			if (nh1==hs1&&nh2==hs2) need=0;
			rep(j,0,lns[i].size()-1){
				need++;
				nh1=((ll)nh1*23+lns[i][j]-'a'+1)%mod;
				nh2=((ll)nh2*2333+lns[i][j]-'a'+1)%1000000007;
				if (nh1==hs1&&nh2==hs2) need=0;
				if (find(nh1,nh2)) need=min(need,2);
				add(nh1,nh2);
			}
			hs1=nh1,hs2=nh2;
			ans+=need+1;
		}
		return ans;
	}
};
