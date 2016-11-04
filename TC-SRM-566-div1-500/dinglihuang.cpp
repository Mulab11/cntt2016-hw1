#include<cstring>
#include<cstdio>
#define M 1000000007
using namespace std;

typedef long long int64;
class PenguinEmperor{
	public:
		int64 a[400],b[400],x[400],c[400];
		int n;
		void mult(int64 a[],int64 b[],int64 x[]){
			memset(c,0,sizeof(c));
			for(int i=0;i<n;i++)for(int j=0;j<n;j++)(c[(i+j)%n]+=a[i]*b[j])%=M;
			memcpy(x,c,sizeof(c));
		}
		int countJourneys(int num, long long d){
			memset(a,0,sizeof(a));memset(b,0,sizeof(b));a[0]=b[0]=1;
			n=num;
			for(int i=1;i<=n;i++){
				memset(x,0,sizeof(x));
				x[i%n]++;if(i%n!=n-i)x[n-i]++;
				mult(a,x,a);
//				for(int j=0;j<n;j++)printf("%lld ",a[j]);printf("\n");
				if(i==d%n)memcpy(b,a,sizeof(b));
			}
			d/=n;
			for(;d;d>>=1){
				if(d&1)mult(b,a,b);
				mult(a,a,a);
			}
			return b[0];
		}
};