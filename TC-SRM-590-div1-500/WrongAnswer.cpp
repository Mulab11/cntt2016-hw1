#include <vector>
using namespace std;
class XorCards{
public:
	int n,k[55];long long a[55];
	long long dfs(int i,long long x,long long l){
		if(i==n||!k[i])return x<=l?1ll<<n-i:0;
		if((x>>k[i])<(l>>k[i]))return 1ll<<n-i;
		if((x>>k[i])>(l>>k[i]))return 0;
		return dfs(i+1,x,l)+dfs(i+1,x^a[i],l);
	}
	long long numberOfWays(vector<long long> number, long long limit){
		for(int i=n=number.size();i--;)a[i]=number[i];
		for(int i=k[n]=0;i<n;i++){
			for(int j=i;j<n;j++)if(a[j]>a[i]){long long t=a[j];a[j]=a[i];a[i]=t;}
			for(int j=i+1;j<n;j++)if((a[j]^a[i])<a[j])a[j]^=a[i];
		}
		for(int i=n;i--;)for(k[i]=k[i+1];a[i]>>k[i];k[i]++);
		return dfs(0,0,limit);
	}
};
