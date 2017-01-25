#include <vector>
#include <string>
#include <cstdio>
#define MOD 1000000009
using namespace std;
class ColorfulBuilding{
public:
	int N,C[1300],f[1300],g[1300][2710],s[2710];
	long long fac[1300],ifac[1300];
	long long inv(int a,int p){return a==1?1:(1+p*(a-inv(p%a,a)))/a%p;}
	int trans(char x){return x<'a'?x-'A':x-'a'+26;}
	void read(vector<string>a){
		for(int i=N=0;i<a.size();i++)
			for(int j=0;j<a[i].length();j++)(C[++N]*=52)+=trans(a[i][j]);
	}
	int count(vector <string> color1, vector <string> color2, int L){
		read(color1);read(color2);C[0]=2704;f[0]=1;
		for(int i=*fac=*ifac=1;i<=N;i++)ifac[i]=inv(fac[i]=fac[i-1]*i%MOD,MOD);
		for(int i=1;i<=N;i++){
			for(int j=0;j<=i;j++)g[j][C[i-1]]=(g[j][C[i-1]]+f[j]*fac[N-i])%MOD,s[j]=(s[j]+f[j]*fac[N-i])%MOD;
			for(int j=0;j<=i;j++)f[j]=j?ifac[N-i]*(1ll*s[j-1]+MOD-g[j-1][C[i]]+g[j][C[i]])%MOD:0;
		}
		return f[L];
	}
};
