#include<cstdio>
#include<string>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class MapGuessing{
	static const int maxn=36,bas=100;
	int res[200],aim[maxn];
	bool vis[maxn];
	string op;
	long long rec[maxn],ans;
	int tot,n;
	
	long long cont(long long sta){
		long long ret=1;
		while(sta){
			ret<<=1;
			sta^=sta&(-sta);
		}
		return ret;
	}
	
	void dfs(int de,int p,long long sta,int num){
		if (p==tot){
			if (num){
				if (num&1) ans+=cont(sta);
				else ans-=cont(sta);
			}
			return;
		}
		if (!sta) return;
		dfs(de,p+1,sta,num);
		dfs(de|(1<<p),p+1,sta&rec[p],num+1);
		return;
	}
	
	bool check(){
		for (int i=0;i<n;++i) if (res[i]){
			if (res[i]==1&&aim[i]==1) return false;
			if (res[i]==2&&aim[i]==0) return false;
		}
		return true;
	}
	
	public:
	long long countPatterns(string goal, vector<string> code){
		memset(rec,0,sizeof(rec));
		
		for (auto &x:code) op+=x;
		int pos=bas,l=bas,r=bas;
		for (auto &a:op){
			if (a=='<'){
				--pos;
				if (pos<l) l=pos;
			}
			else if (a=='>'){
				++pos;
				if (pos>r) r=pos;
			}
		}
		l-=bas;
		r-=bas;
		n=goal.length();
		for (int i=0;i<n;++i) if (goal[i]=='0') aim[i]=0;
		else aim[i]=1;
		
		tot=0;
		for (int i=abs(l);i<n-r;++i){
			long long tmp=0;
			memset(res,0,sizeof(res));
			int pos=i;
			for (auto &a:op){
				if (a=='<') --pos;
				else if (a=='>') ++pos;
				else{
					tmp|=(1LL<<pos);
					if (a=='0') res[pos]=1;
					else res[pos]=2;
				}
				if (check()) rec[tot]=tmp;
			}
			++tot;
		}
		ans=0;
		dfs(0,0,(1LL<<n)-1,0);
		return ans;
	}
};
