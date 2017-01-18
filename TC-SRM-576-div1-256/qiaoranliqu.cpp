#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<bitset>
#include<cmath>
#include<string>

#define ls (t<<1)
#define rs ((t<<1)+1)
#define mid ((l+r)>>1)
#define fi first
#define se second
#define mk make_pair
#define pb push_back

#define N 100005
#define M 105
#define seed 23333
#define Mo 998244353

using namespace std;
int i,j,m,n,p,k,fa[N],ID[M][M],tot,l;
int get(int x)
{
		return fa[x]==x?x:fa[x]=get(fa[x]);
}
void Merge(int x,int y)
{
	fa[get(x)]=get(y);
}
class ArcadeManao{
	public:
		int shortestLadder(vector <string> level, int coinRow, int coinColumn)
		{
				coinRow--; coinColumn--;
				n=level.size(); m=level[0].length();
				for (i=0;i<n;++i)
					for (j=0;j<m;++j) if (level[i][j]=='X') ID[i][j]=++tot;
				for (i=1;i<=tot;++i) fa[i]=i;
				for (i=0;i<n;++i) //先把左右移动能到达的合并起来 
					for (j=0;j<m-1;++j)
						if (level[i][j]=='X'&&level[i][j+1]=='X') Merge(ID[i][j],ID[i][j+1]);
				if (get(ID[n-1][m-1])==get(ID[coinRow][coinColumn])) return 0;
				for (l=1;l<=n;++l) //枚举一个长度为i的梯子,然后将当前能合并的点合并起来,不断询问起始点和终点是否连通 
				{
					for (j=l;j<n;++j)
						for (k=0;k<m;++k)
							if (level[j][k]=='X'&&level[j-l][k]=='X') 
							 	Merge(ID[j][k],ID[j-l][k]);
					if (get(ID[n-1][m-1])==get(ID[coinRow][coinColumn])) return l;
				}
				return -1;
		}
};

