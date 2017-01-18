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

#define N 305
#define M 200005
#define seed 23333
#define Mo 998244353

using namespace std;
const int inf=(int)1e9;
vector<int>v[N];
int i,j,m,n,p,k,f[N][N];	
class History{
	public:
	string verifyClaims(vector <string> dynasties, vector <string> battles, vector <string> queries)
	{ 
		for (i=0;i<N;++i)
		{
				for (j=0;j<N;++j) f[i][j]=-inf;
				f[i][i]=0;
		}
				n=(int)dynasties.size();
				for (i=0;i<(int)dynasties.size();++i)
				{
						int now=0;
						for (j=0;j<(int)dynasties[i].length();++j)
						{
								if (dynasties[i][j]==' ') v[i].pb(now),now=0;
								else now=now*10+dynasties[i][j]-'0';
						}
						v[i].pb(now);
				}
				string S;
				for (i=0;i<(int)battles.size();++i) S+=battles[i];
				for (i=0;i<S.size();i+=6)
				{
						int A=S[i]-'A', B=S[i+1]-'0',
						   AA=S[i+3]-'A',BB=S[i+4]-'0',
						   ta=v[A][B],tb=v[A][B+1]-1,
						   tA=v[AA][BB],tB=v[AA][BB+1]-1;
						   f[A][AA]=max(f[A][AA],tA-tb);
						   f[AA][A]=max(f[AA][A],ta-tB);
				}
				for (k=0;k<n;++k)
					for (i=0;i<n;++i)
						for (j=0;j<n;++j)
							f[i][j]=max(f[i][j],f[i][k]+f[k][j]);
				string s;
				for (i=0;i<(int)queries.size();++i)
				{
						int A=queries[i][0]-'A', B=queries[i][1]-'0',
						   AA=queries[i][3]-'A',BB=queries[i][4]-'0',
						   ta=v[A][B],tb=v[A][B+1]-1,
						   tA=v[AA][BB],tB=v[AA][BB+1]-1;
						   if (f[AA][A]>-tA+tb||f[A][AA]>-ta+tB)
						   	s+='N';
						   	else s+='Y';
				}
				return s;
		}
}MRT;

int main()
{
	 cout<<MRT.verifyClaims({
 "600 650 2000",
 "1 1001 20001"},
{"A1-B0 A1-B1"},
{"B1-A0"}); 
}
