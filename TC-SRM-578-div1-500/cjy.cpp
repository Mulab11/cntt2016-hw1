#include <algorithm>
using namespace std;
int P=1e9+7,i,n,m,l[333],r[333],f[333][333],S,k,x,j;//f[i][j]表示最后两个在j和k
string s,t;
class WolfInZooDivOne
{
	public:
		int count(int N,vector<string> L,vector<string> R)
		{
			for(auto x : L)s+=x;
			for(auto x : s)x==' '?n++:l[n]=l[n]*10+x-48;
			for(auto x : R)t+=x;
			for(auto x : t)x==' '?m++:r[m]=r[m]*10+x-48;
			for(f[i=0][0]=1;i<=N;i++)for(j=i;j<=N;j++)
			{
				for(S=(S+f[i][j])%P,x=j+1,k=0;k<=m;k++)if(l[k]<i)x=max(x,r[k]+2);
				for(k=x;k<=N;k++)f[j][k]=(f[j][k]+f[i][j])%P;
			}
			return S;
		}
};
