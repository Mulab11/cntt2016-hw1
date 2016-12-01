#include<cstdio>
#include<string>
#include<vector>
#include<string>
#include<iostream>
#include<algorithm>
using namespace std;

class GooseTattarrattatDiv1{
	static const int maxn=30;
	int fa[maxn],size[maxn];
	
	int find(int x){return (x==fa[x])?x:fa[x]=find(fa[x]);}
	int merge(int a,int b){
		if (a==b) return 0;
		if (size[a]<size[b]) swap(a,b);
		fa[b]=a;
		return size[b];
	}
	
	public:
		int getmin(string S){
			int ans=0;
			for (int i=0;i<26;++i) fa[i]=i;
			for (auto &x:S) size[x-'a']++;
			for (int i=0,j=S.length()-1;i<j;++i,--j)
				ans+=merge(find(S[i]-'a'),find(S[j]-'a'));
			return ans;
		}
};
