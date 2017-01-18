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

#define N 15
#define M 200005
#define seed 23333
#define Mo 998244353

using namespace std;
//设不为上下界的点集为S,通过调整法易发现点集S一定是一个完全图。
//然后利用拉格朗日乘数法,可以发现每个值的最优解均为X+C,求出C以后判断是否合法,若不合法则一定有其他值成为上下界. 
int i,j,m,n,p,k,e[N][N],ID[N],bit;
double val[N],E[N];
class BoundedOptimization{
		public:
		double maxValue(vector<string> expr, vector<int> lb, vector<int> ub, int sum)
		{
			  string s="";
			  n=lb.size();
			  for (i=0;i<(int)expr.size();++i) s+=expr[i];
			  for (i=0;i<(int)s.length();i+=3)
			  {
			  		int x=s[i]-'a',y=s[i+1]-'a';
			  		e[x][y]=e[y][x]=1;
			  }
			  double ans=-1;
			  for (i=0;i<(1<<n);++i)  //枚举点集S 
			  {
			  		ID[0]=0;
			  		for (j=0;j<n;++j)	
			  			if (i&(1<<j)) ID[++ID[0]]=j;
					for (j=1,k=ID[0]+1;j<=ID[0]&&k==ID[0]+1;++j)
						for (k=j+1;k<=ID[0];++k)
							if (!e[ID[j]][ID[k]]) break;
					if (j!=ID[0]+1) continue;
					int now=(1<<n)-1-i;
					for (bit=now;;bit=(bit-1)&now) //枚举其他点的上下界情况 
					{
							double rest=sum,all;
							for (j=0;j<n;++j) val[j]=-1,E[j]=0;
							for (j=0;j<n;++j)
								if (bit&(1<<j)) val[j]=lb[j]; else 
									if (now&(1<<j)) val[j]=ub[j];
							for (j=0;j<n;++j) if (val[j]!=-1) rest-=val[j];
							all=rest;
							if (rest<0)
							{
									if (!bit) break;
									continue; 
							}
							for (j=1;j<=ID[0];++j) //计算X和C 
							{
								  for (k=0;k<n;++k)
								  	if (e[ID[j]][k]&&(now&(1<<k)))
										E[ID[j]]+=val[k];
								  all-=E[ID[j]]; all-=rest/2.;
							}
							all/=ID[0];
							for (j=1;j<=ID[0];++j)
							val[ID[j]]=E[ID[j]]+rest/2.+all; 
							for (j=0;j<n;++j) //判断答案是否合法 
								if (val[j]<lb[j]||val[j]>ub[j]) break;
							if (j!=n)
							{
								 if (!bit) break;
								 continue;
							}
							double Ans=0;
							for (j=0;j<n;++j)
								for (k=0;k<n;++k)
									Ans+=e[j][k]*val[j]*val[k];
							Ans/=2;
							ans=max(ans,Ans);//更新答案 
							if (!bit) break;
					}
			  }
			  return ans;
		}
}G;

int main()
{
	 cout<<G.maxValue({"ba+cb"},{0,0,1},{1,2,1},3);
}
	

