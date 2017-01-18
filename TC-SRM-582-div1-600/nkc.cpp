#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
long long mod=1e9+9;
struct ColorfulBuilding
{
	long long P[201][201],cnt;
	long long c[1601],t[1601];
	long long f[1601][1601],tot[1601];
	long long count(vector <string> color1, vector <string> color2, long long L)
	{
		string S1,S2;
		long long i,j,k,l;
		for(i=0;i<color1.size();i++)
		S1+=color1[i];
		for(i=0;i<color2.size();i++)
		S2+=color2[i];
		long long n=S1.size();
		for(i=0;i<n;i++)
		{
			if(!P[S1[i]][S2[i]])
			{
				cnt++;
				P[S1[i]][S2[i]]=cnt;
			}
			c[n-i]=P[S1[i]][S2[i]];
		}
		for(j=1;j<=cnt;j++)
		t[j]=1;
		f[1][c[1]]=1;
		tot[1]=1;
		for(i=2;i<=n;i++)
		{
			long long cur=c[i];
			for(j=1;j<=cnt;j++)
			{
				if(j!=cur) (t[j]*=i-1)%=mod;
				else
				{
					for(k=1;k<=n;k++)
					(f[k][j]*=t[j])%=mod;
					t[j]=1;
				}
			}
			for(j=n;j>=1;j--)
			{
				(tot[j]*=i-1)%=mod;
				(tot[j]+=tot[j-1]+f[j][cur]-f[j-1][cur])%=mod; 
				(f[j][cur]*=i)%=mod;
				(f[j][cur]+=tot[j-1]-f[j-1][cur])%=mod;
			}
		}
		long long ans=0;
		for(i=1;i<=cnt;i++)
		(ans+=f[L][i]*t[i])%=mod;
		ans=(ans+mod)%mod;
		return ans;
	}
};
/*ColorfulBuilding P;
long long main()
{
	vector<string> V1,V2;
	V1.push_back("aaba");
	V2.push_back("aaaa");
	cout<<P.count(V1,V2,3);
}*/