//============================================================================
// Author       : Sun YaoFeng
//============================================================================

#include<set>
#include<map>
#include<cmath>
#include<queue>
#include<bitset>
#include<string>
#include<cstdio>
#include<cctype>
#include<cassert>
#include<cstdlib>
#include<cstring>
#include<sstream>
#include<iostream>
#include<algorithm>

#define For(i,x,y) for (int i=x;i<y;i++)
#define pb push_back
#define mp make_pair
#define fi first
#define se second

#define dprintf(...) fprintf(stderr,__VA_ARGS__)
using namespace std;

typedef long long ll;
typedef double db;
typedef pair<int,int> pii;
typedef vector<int> Vi;
typedef vector<string> Vs;

const int N=50+3;

int fa[N],sz[26];
int n,res;

int getf(int x){
	return fa[x]==x?x:fa[x]=getf(fa[x]);
}
void Union(int x,int y){
	x=getf(x),y=getf(y);
	if (x!=y) fa[x]=y;
}

class GooseTattarrattatDiv1{
public:
	int getmin(string s){
		n=s.length();
		For(i,0,26) fa[i]=i;
		For(i,0,n) sz[s[i]-'a']++;
		For(i,0,n) Union(s[i]-'a',s[n-1-i]-'a');	//用并查集将相同的点并起来
		For(i,0,26)
			if (fa[i]==i){	//在每一个连通块里面取出现次数最多的
				int tmp=0,mx=0;
				For(j,0,26)
					if (getf(j)==i){
						tmp+=sz[j];
						mx=max(mx,sz[j]);
					}
				res+=tmp-mx;
			}
		return res;
	}
} T;