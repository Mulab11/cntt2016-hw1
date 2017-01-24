#include <vector>
#define MOD 1000000007
using namespace std;
class WolfPack{
public:
	long long fac[100010],ifac[100010],C[100010];
	long long inv(int a,int p){return a==1?1:(1+p*(a-inv(p%a,a)))/a%p;}
	void init(int m){
		for(int i=*fac=1;i<=m;i++)fac[i]=fac[i-1]*i%MOD;
		ifac[m]=inv(fac[m],MOD);
		for(int i=m;i;i--)ifac[i-1]=ifac[i]*i%MOD;
		for(int i=0;i<=m;i++)C[i]=fac[m]*ifac[i]%MOD*ifac[m-i]%MOD;
	}
	int calc(vector <int> x, int m){
		int xmin=1<<30,xmax=-xmin,s=0;
		for(int i=0;i<x.size();i++)x[i]<xmin?xmin=x[i]:1,x[i]>xmax?xmax=x[i]:1;
		for(int a=xmax-m;a<=xmin+m;a++){
			int p=1;
			for(int i=0;i<x.size()&&p;i++)p=(x[i]-a+m)%2?0:p*C[x[i]-a+m>>1]%MOD;
			(s+=p)%=MOD;
		}
		return s;
	}
	int calc(vector <int> x, vector <int> y, int m){
		init(m);
		for(int i=0,a;i<x.size();i++)a=x[i]+y[i],y[i]-=x[i],x[i]=a;
		return 1ll*calc(x,m)*calc(y,m)%MOD;
	}
};
