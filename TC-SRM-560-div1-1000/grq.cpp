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

const int N=22,M=1<<13;
const double inf=1e9,eps=1e-9;
int n;
int go[N],al[M][N],au[M][N];
bool can[M];

void pre(vector<string> ss){
	string s="";
	memset(go,0,sizeof(go));
	for(int i=0;i<ss.size();i++) s+=ss[i];
	int L=-1,R=-1;
	for(int i=0;i<s.length();i++)
		if(s[i]>='a'){if(~L) R=s[i]-'a'; else L=s[i]-'a';}
		else if(s[i]=='+') go[L]|=1<<R,go[R]|=1<<L,L=R=-1;
	go[L]|=1<<R;go[R]|=1<<L;
}

class BoundedOptimization{
public:
	double maxValue(vector <string> ss, vector <int> lb, vector <int> ub, int ms){
		n=lb.size();pre(ss);
		memset(al,0,sizeof(al));
		memset(au,0,sizeof(au));
		for(int i=0;i<(1<<n);i++){
			can[i]=1;
			for(int j=0;j<n;j++)
				if((i&(1<<j))&&(go[j]|i)!=(go[j]|1<<j)) can[i]=0;
			for(int j=0;j<n;j++)
				if(i&(1<<j))
					for(int k=0;k<n;k++)
						if(go[j]&(1<<k)) al[i][k]+=lb[j],au[i][k]+=ub[j];
		}
		double ans=0.0;
		int u=(1<<n)-1;
		for(int i=0;i<(1<<n);i++){
			if(!can[i]) continue;
//			debug(i);
			int l[N],r[N],m=0,si[N];
			memset(si,0,sizeof(si));
			for(int j=0;j<n;j++)
				if(i&(1<<j)) l[m++]=j; else r[j-m]=j;
//			for(int j=0;j<n-m;j++) printf("%d ",r[j]);puts("");
			for(int j=u^i;;j=(j-1)&(u^i)){
				double res=0,mt;
				int t=ms;
				for(int k=0;k<n;k++)
					si[k]=al[j][k]+au[u^i^j][k];
				for(int k=0;k<n-m;k++)
					if(j&(1<<r[k])) res+=lb[r[k]]*si[r[k]],t-=lb[r[k]]; else res+=ub[r[k]]*si[r[k]],t-=ub[r[k]];
				res/=2.0;
//				if(t>=0) printf("%d %d %d %.1f\n",j,u^i^j,t,res);
				mt=(1-m/2.0)*t;
				bool isok=1;
				for(int k=0;k<m;k++) mt-=si[l[k]];
				for(int k=0;k<m;k++){
					double tmp=(double)t/2.0+si[l[k]]+mt/(double)m;
//					if(i==3&&j==4) printf("%.3f ",tmp);
					if(tmp+eps<lb[l[k]]||tmp>ub[l[k]]+eps) isok=0;
					res+=tmp*(t/2.0+si[l[k]]-tmp/2.0);
				}
//				if(i==3&&j==4) printf("%.3f\n",res);
				if(isok&&t>=0) ans=max(ans,res);
				if(!j) break;
			}
		}
		return ans;
	}
};
