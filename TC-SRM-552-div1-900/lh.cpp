#include<map>
#include<cstdio>
#include<string>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class HolyNumbers{
	static const int maxn=1000010;
	int pr[maxn],tot;
	bool notp[maxn];
	
	void pre(int lim){
		for (int i=2;i<=lim;++i){
			if (!notp[i]){
				pr[tot++]=i;
			}
			for (int j=0;j<tot;++j){
				int k=pr[j]*i;
				if (k>lim) break;
				notp[k]=true;
				if (i%pr[j]==0){
					break;
				}
			}
		}
		return;
	}
	
	int find(int *a,int num,long long x){
		int l=0,r=num-1,mid;
		while(l<r){
			mid=(l+r+1)/2;
			if (x>=a[mid]) l=mid;
			else r=mid-1;
		}
		return l+1;
	}
	
	long long dfs(int pos,long long lft){
		if (pos>=tot) return 1;
		if (lft<pr[pos]) return 1;
		if (lft<(long long)pr[pos]*pr[pos+1]){
			return find(pr+pos,tot-pos,lft)+1;
		}
//		printf("%d,%lld\n",pos,lft);
//		long long &ret=sav[pos][lft];
//		if (ret) return ret;
		long long ret=dfs(pos+1,lft);
		long long pp=(long long)pr[pos]*pr[pos];
		lft/=pr[pos];
		do{
			ret+=dfs(pos+1,lft);
			lft/=pp;
		}while(lft>0);
		return ret;
	}
	
	public:
	long long count(long long n, int mp){
		pre(mp);
		cout<<tot<<endl;
		return dfs(0,n);
	}
};
