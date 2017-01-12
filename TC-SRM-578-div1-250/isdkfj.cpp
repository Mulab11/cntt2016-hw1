#include <bits/stdc++.h>

using namespace std;

const int mo=1000000007;
int fa[2505],sz[2505];
int get(int x){
	return x==fa[x]?x:fa[x]=get(fa[x]);
}

class GooseInZooDivOne {
public:
	int count(vector <string> field, int dist) {
		int n=field.size(),m=field[0].size();
		for(int i=0;i<n*m;++i)fa[i]=i;//并查集初始化 
		for(int i=0;i<n;++i)
			for(int j=0;j<m;++j)
			if(field[i][j]=='v')
				for(int a=0;a<n;++a)
					for(int b=0;b<m;++b)if(field[a][b]=='v'){
						int d=abs(i-a)+abs(j-b);
						if(d<=dist){
							int x=get(i*m+j),y=get(a*m+b);
							if(x!=y)fa[y]=x;//距离小于dist就并在一起 
						}
					}
		int ans=1,js=0;
		for(int i=0;i<n;++i)
			for(int j=0;j<m;++j)if(field[i][j]=='v')++sz[get(i*m+j)];//每个联通块大小 
		for(int i=0;i<n*m;++i)if(sz[i]){
			if(sz[i]&1){
				if(js)ans=ans*2%mo;//2^(奇数-1)
				++js;
			}
			else ans=ans*2%mo;
		}
		ans=(ans-1+mo)%mo;
		return ans;
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
