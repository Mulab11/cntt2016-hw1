#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
LL Mod=1e9+9;
const LL inf=(1ULL<<63)-1;
const int K=16+3,B=10+3;
LL coe1[K][K],coe2[K][K],coe3[K][K],tmp[K][K];
//coe1是用来倍增的矩阵， coe2是用来由p^t转移到p^{t+1}，coe3是答案矩阵。 
inline void merge(LL a[K][K],LL b[K][K],int k)//矩阵乘 
{
	memset(tmp,0,sizeof(tmp));
	for(int i=0;i<=k;++i)
		for(int j=i;j<=k;++j)
			if(a[i][j])
				for(int o=j;o<=k;++o)
					if(b[j][o])
						(tmp[i][o]+=a[i][j]*b[j][o])%=Mod;
	memcpy(b,tmp,sizeof(tmp));
}
inline void init(LL a[K][K],int k)//构建一个单位矩阵 
{
	memset(a,0,sizeof(tmp));
	for(int i=k;i>=0;--i)a[i][i]=1;
}
class MegaFactorial
{
	public:
		inline int countTrailingZeros(int n,int k,int b)
		{
			//找到b中最大的质因子dvs，以及它的指数ind 
			int prm[4]={2,3,5,7};
			int dvs,ind=0;
			for(int i=4;i--;)
				if(b%prm[i]==0)
				{
					dvs=prm[i];
					while(b%dvs==0)++ind,b/=dvs;
					break;
				}
			Mod*=ind;
			
			//初始化矩阵 
			coe1[0][0]=1;
			for(int i=1;i<=k;++i)
				for(int j=i;j<=k;++j)
					coe1[i][j]=1;
			init(coe3,k);
			for(;n;n/=dvs)
			{
				//倍增 
				int dx=dvs,dn=n%dvs;
				init(coe2,k);
				for(;dn||dx;dn>>=1,dx>>=1)
				{
					if(dx&1)merge(coe1,coe2,k);
					if(dn&1)merge(coe1,coe3,k);
					merge(coe1,coe1,k);
				}
				memcpy(coe1,coe2,sizeof(coe1));
				for(int i=k;i;--i)(++coe1[0][i])%=Mod;//将线性表示的常数项+1 
			}
			LL ans=(coe3[0][k]+Mod)%Mod/ind;
			return ans;
		}
};