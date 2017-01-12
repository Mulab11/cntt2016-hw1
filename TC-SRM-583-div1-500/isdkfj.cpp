#include <bits/stdc++.h>

using namespace std;

int fa[55],n,cnt[55];
int get(int x){
	return x==fa[x]?x:fa[x]=get(fa[x]);
}

class TurnOnLamps {
public:
	int minimize(vector <int> roads, string initState, string isImportant) {
		n=roads.size()+1;
		for(int i=0;i<n;++i)fa[i]=i;
		for(int i=0;i<n-1;++i)if(isImportant[i]=='0'){
			int x=get(roads[i]),y=get(i+1);
			if(x!=y)fa[y]=x;//把没用的边缩起来 
		}
		for(int i=0;i<n-1;++i)if(initState[i]=='0'){
			int x=get(roads[i]),y=get(i+1);
			if(x!=y)++cnt[x],++cnt[y];
		}
		int ans=0;
		for(int i=0;i<n;++i)ans+=cnt[i]&1;//度数为奇数 
		return ans/2;
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
