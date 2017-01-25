#include <string>
using namespace std;
class CuttingBitString{
public:
	// num[i],len[i]:5^i的值和长度 f[i]:S[0,i)至少分成多少段
	long long num[50];
	int len[50],cnt,f[51];
	int getmin(string S){
		// 预处理5^i
		int L=S.length();
		for(long long x=1,l=1;l<=L;){
			num[cnt]=x;len[cnt++]=l;
			x*=5;while((1ll<<l)<=x)l++;
		}
		long long x=0;
		for(int i=0;i<L;i++)x=x<<1|S[i]-'0';
		for(int i=1;i<=L;i++){ // DP求最少分段数
			f[i]=1<<30;
			for(int j=0;j<cnt&&len[j]<=i;j++){
				if((x>>L-i&((1ll<<len[j])-1))==num[j]&&f[i-len[j]]+1<f[i])f[i]=f[i-len[j]]+1;
			}
		}
		return f[L]>=(1<<30)?-1:f[L];
	}
};
