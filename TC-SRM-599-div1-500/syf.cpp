//============================================================================
// Author       : Sun YaoFeng
//============================================================================

#include<set>
#include<map>
#include<ctime>
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

const int N=20000;
const int Top=2503*2503+19;
const int oo=(1<<30)-1;

int x[N],y[N],dis[N];
int Sqrt[Top],res=oo,cnt;

class FindPolygons{
public:
	db minimumPolygon(int L){
		memset(Sqrt,-1,sizeof(Sqrt));
		for (int i=1;i*i<Top;i++) Sqrt[i*i]=i;
		if (L%2==1||L<=2) return -1;
		For(i,0,L+1) For(j,0,L+1)	//将所有合法的预处理
			if (i||j){
				int tmp=i*i+j*j;
				if (tmp>=Top||Sqrt[tmp]==-1) continue;
				if (2*Sqrt[tmp]<L){
					cnt++;
					x[cnt]=i;
					y[cnt]=j;
					dis[cnt]=Sqrt[tmp];
				}
			}
		For(i,1,cnt+1)
			For(j,i+1,cnt+1){	//枚举这两个点，判断合法性
				int tmp=(x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]);
				if (tmp>=Top||Sqrt[tmp]==-1) continue;
				if (Sqrt[tmp]+dis[i]+dis[j]==L){
					res=min(res,max(max(dis[i],dis[j]),Sqrt[tmp])-min(min(dis[i],dis[j]),Sqrt[tmp]));
				}
			}
		if (res!=oo) return res;
		return L/2-L/4*2;
	}
} T;