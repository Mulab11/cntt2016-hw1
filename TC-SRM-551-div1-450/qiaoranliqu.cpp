#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<bitset>
#include<queue>

#define ls (t<<1)
#define rs ((t<<1)+1)
#define mid ((l+r)>>1)
#define fi first
#define se second
#define mk make_pair
#define pb push_back

#define N 55
#define M 200005
#define seed 23333
#define Mo 998244353

using namespace std;
int i,j,m,n,p,k,fox[N],dis[N],k1,vis[N];
struct Node{int ed,before,cost;}s[M];
priority_queue<pair<int,int> >Q;
void add(int x,int y,int cost)
{
		s[++k1].ed=y; s[k1].before=fox[x]; fox[x]=k1; s[k1].cost=cost;
}
class ColorfulWolves{
	public:
		int getmin(vector <string> colormap)
		{
				memset(dis,60,sizeof(dis));
				for (i=0;i<n;++i)
				{
						int cnt=0;
						for (j=0;j<n;++j) if (colormap[i][j]=='Y') 
							  add(i,j,cnt++);
				}
				dis[0]=0;
				Q.push(mk(0,0));
				while (!Q.empty())
				{
						int x=Q.top().se; Q.pop();
						if (vis[x]) continue;
						vis[x]=1;
						for (i=fox[x];i;i=s[i].before)
						{
								int p=s[i].ed;
								if (dis[p]>dis[x]+s[i].cost)
									dis[p]=dis[x]+s[i].cost,Q.push(mk(-dis[p],p));
						}
				}
				if (dis[n-1]<(int)1e9) return dis[n-1];
				return -1;
		}
}FFT;

int main()
{
	 FFT.getmin(vector<string>{"NYN","YNY","NNN"});
}
