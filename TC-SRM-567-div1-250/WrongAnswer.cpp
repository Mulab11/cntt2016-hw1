#include <cmath>
class TheSquareRootDilemma{
public:
	bool f[77778]; // f[i]表示i是否不含平方因子
	int countPairs(int N, int M){
		for(int i=1;i<=N&&i<=M;i++)f[i]=1;
		for(int i=2;i*i<=N&&i*i<=M;i++)if(f[i*i])
			for(int j=i*i;j<=N&&j<=M;j+=i*i)f[j]=0;
		// A,B满足的条件是去掉平方因子后相同
		// 枚举去掉平方因子后的数
		int ans=0;
		for(int i=1;i<=N&&i<=M;i++)if(f[i])ans+=int(sqrt(N/i+0.5))*int(sqrt(M/i+0.5));
		return ans;
	}
};
