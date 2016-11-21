#include<map>
#include<cstdio>
#include<string>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class NewArenaPassword{
	private:
		static const int maxn=55;
		int n,fa[maxn],size[maxn];
		map<char,int> cnt[maxn];
		typedef map<char,int>::iterator mit;
		int find(int x){return (x==fa[x])?x:fa[x]=find(fa[x]);}
		void merge(int a,int b){
			if (a==b) return;
			if (size[a]<size[b]){
				fa[a]=b;
				size[b]+=size[a];
			}
			else{
				fa[b]=a;
				size[a]+=size[b];
			}
			return;
		}
		int ask(int p){
			int ret=0;
			for (mit it=cnt[p].begin();it!=cnt[p].end();++it){
				ret=max(ret,it->second);
			}
			return ret;
		}
	public:
		int minChange(string s, int K){
			n=s.size();
			for (int i=0;i<n;++i) fa[i]=i,size[i]=1;
			for (int i=0;i<K;++i) merge(find(i),find(n-K+i));
			for (int i=0;i<n;++i) cnt[find(i)][s[i]]++;
			int ans=0;
			for (int i=0;i<n;++i) if (fa[i]==i){
				ans+=size[i]-ask(i);
				//printf("i=%d,ans=%d\n",i,ans);
			}
			return ans;
		}
};