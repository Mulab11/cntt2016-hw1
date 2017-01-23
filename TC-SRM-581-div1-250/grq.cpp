#include<bits/stdc++.h>
#define sqr(x) (x)*(x)
#define ll long long
#define ull unsigned long long
#define ui unsigned int
#define vi vector<int>
#define pb push_back
#define ld long double
#define mp make_pair
#define pii pair<int,int>
#define debuge puts("isok")
#define debug(x) cout<<#x<<"="<<x<<endl
#define SS second
#define FF first
using namespace std;

const int N=55;
int sum[N],s[N],si[N][N],tot[N],cnt[N];

class SurveillanceSystem{
public:
	string getContainerInfo(string c, vector<int> reports, int L){
		int n=c.size();
		memset(si,0,sizeof(si));
		memset(s,0,sizeof(s));
		memset(cnt,0,sizeof(cnt));
		memset(tot,0,sizeof(tot));
		string ans="";
		for(int i=0;i<n;i++) ans+='?';
		for(int i=0;i<n;i++) sum[i]=(i?sum[i-1]:0)+(c[i]=='X');
		for(int i=0;i<reports.size();i++) s[reports[i]]++;
		for(int i=0;i+L-1<n;i++){
			int k=sum[i+L-1]-(i?sum[i-1]:0);
			for(int j=0;j<L;j++) si[k][i+j]++;
			tot[k]++;
			if(!s[k]) for(int j=0;j<L;j++) cnt[i+j]++;
		}
		for(int i=0;i<n;i++) if(cnt[i]==min(min(i+1,n-i),L)) ans[i]='-';
				for(int i=0;i<n;i++)
			for(int j=0;j<=n;j++)
				if(tot[j]-si[j][i]<s[j]) ans[i]='+';
		return ans;
	}
};
