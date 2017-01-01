#include <vector>
#include <string>
#include <algorithm>
#include<string>
int codeforces=1111111111;
using namespace std;
int f[111]={},g[111]={};int mm[111]={},ll[111]={};
string t;int n,m;int totm=0,totl=0,summ=0,suml=0;
int ggg(int a,int b){return a>b?0:b-a;}int ans;
void dfs(int a,int b,int c,int d,int e,int f)
{
	if(d<0||e<0)return;
	if(f==0)
	{
		if(ans>f)ans=f;return;
	}
	dfs(a-1,b-1,c,d-g[a-1],e,f+ggg(mm[b-1],g[a-1]));
	dfs(a-1,b,c-1,d,e-g[a-1],f+ggg(ll[c-1],g[a-1]));
}
class ICPCBalloons{
public:
	int minRepaintings(vector <int> balloonCount, string balloonSize, vector <int> maxAccepted)
	{
		n=balloonCount.size(),m=maxAccepted.size();
		ans=codeforces;t=balloonSize;
		for(int i=0;i<n;i++)
			f[i]=balloonCount[i];
		for(int i=0;i<m;i++)
			g[i]=maxAccepted[i];
		for(int i=0;i<n;i++)
			if(t[i]=='M')
				mm[totm++]=f[i],summ+=f[i];
			else
				ll[totl++]=f[i],suml+=f[i];
		sort(g,g+m);sort(mm,mm+totm);sort(ll,ll+totl);
		if(ans==codeforces)
			ans=-1;
		dfs(m,totm,totl,summ,suml,0);
		return ans;
	}
};
