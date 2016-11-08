# TheBrickTowerHardDivOne
作者：徐懿

关键词：动态规划 状态表示 矩阵乘法

## 题目简述
现在有$$C$$种颜色不同的，大小均为$$1\times 1\times 1$$的，个数均无限个的方块。你需要用这些方块搭一座$$2\times 2\times X$$的长方体的塔，也就是说会用$$2\times 2\times X$$个方块。

我们定义一个塔是泉岭的的，当且仅当：

1.这座塔最多有$$K$$对有公共面且颜色相同的方块。
1.这座塔高度为$$[1,H]$$中的整数。

给定$$C,K,H$$，球泉岭的塔的数量对1234567891取模。

$$C$$为$$[1,4747]$$中的整数。

$$k$$为$$[0,7]$$中的整数。

$$H$$为$$[1,474747474747474747]$$中的整数。

## 后记
大家好我是来自湖北襄樊十堰中学的bx2k。（哪有后记写在这种鬼地方啊

顺便一提这个中学是我编的，如有雷同，纯属巧合。

一如既往地，后记中不会有题解的剧透（所以说写这个东西的意义在哪啊

这题写起来真是爽啊……还好在机房关门之前写完了（其实是你代码能力太差啦

汝之纯明，吾之出铳！

## 状态表示
我们注意到，一个方块的具体颜色对转移并没有太大影响，只要处理相邻颜色相同的就可以了（也可以理解为相对颜色）。

我们定义状态$$dp_{i,k,a}$$为高度为$$i$$，已经有$$k$$对相邻方块颜色相同，顶面相对颜色序列为$$a$$的方案数。

对于这里的序列$$a$$，我们以如下方法构造。先为顶层的方块编号，编号为$$1$$的方块的相对颜色定义为$$1$$。

然后以编号从小到大顺序枚举，如果当前方块的颜色在之前没有出现过，便将其编号为之前所有编号的最大值$$+1$$如果当前方块的具体颜色在以前出现过，就用以前出现的编号。

## 转移
枚举最上面一层以及第二层的相对颜色，计算并更新相邻方块颜色相同的个数，直接叠加即可。

## 矩阵乘法
由于$$H$$过大，上文的算法显然会超时，因此我们要挖掘一些性质。

我们发现，转移方程是线性的，且$$i$$不会影响转移方程的形式。因此我们使用矩阵乘法+快速幂优化。

设$$m=a的种类数\times(K+1)+1$$。

我们可以构造$$1\times m$$矩阵$$a$$为每种状态初始的方案数，再定义$$m\times m$$矩阵$$b$$为动态规划中任意两种状态转移的常数，并用最后一个位置记录每一种高度的方案的和。

答案显然为$$a\times b^h$$的最后一项。

具体细节参见代码。

```C++
#include<bits/stdc++.h>
const long long mod=1234567891;
const int N=2333,M=122;
int m;

class TheBrickTowerHardDivOne
{
	public:


		struct gungnir
		{
			long long a[M][M];

			gungnir operator * (const gungnir &b)
			{
				gungnir c;
				for(int i=1;i<=m;i++)
				{
					for(int j=1;j<=m;j++)
					{
						c.a[i][j]=0;
						for(int k=1;k<=m;k++)
						{
							(c.a[i][j]+=a[i][k]*b.a[k][j])%=mod;
						}
					}
				}
				return c;
			}
		}dp,ini;

		int a[N],c[N];
		long long b[N],e[N];

		int shanquan(int a[])
		{
			int b[9],ans=0,j=1,k=1;
			memset(b,0,sizeof(b));
			b[a[1]]=1;
			for(int i=2;i<5;i++)
			{
				k=std::max(k,a[i]);
				ans=ans*10+(b[a[i]]?b[a[i]]:b[a[i]]=++j);
			}
			return ans;
		}

		long long yamaizumi(int a[],int n,int c)
		{
			int j=0;
			for(int i=1;i<=n;i++)
			{
				if(a[i]>j+1)return 0;
				j=std::max(j,a[i]);
			}
			long long ans=1;
			for(int i=0;i<j;i++)
			{
				(ans*=(c-i))%=mod;
			}
			return ans;
		}

		gungnir moko(gungnir a,long long b)
		{
			gungnir ans;
			memset(ans.a,0,sizeof(ans.a));
			for(int i=1;i<=m;i++)
			{
				ans.a[i][i]=1;
			}
			for(;b;b>>=1)
			{
				if(b&1)ans=ans*a;
				a=a*a;
			}
			return ans;
		}

		long long moko(long long a,long long b)
		{
			long long ans=1;
			for(;b;b>>=1)
			{
				if(b&1)(ans*=a)%=mod;
				(a*=a)%=mod;
			}
			return ans;
		}

		int find(int C, int K, long long H)
		{
			for(int i=0;i<9;i++)
			{
				a[i]=1;
			}
			for(;a[0]<2;)
			{
				int j=shanquan(a);
				b[j]=std::max(b[j],yamaizumi(a,4,C));
				int i;
				for(i=4;a[i]==i;i--)
				{
					a[i]=1;
				}
				a[i]++;
			}
			int n=0;
			memset(c,0,sizeof(c));
			for(int i=1;i<=1000;i++)if(b[i])
			{
				c[i]=++n;
				e[n]=b[i];
			}
			m=n*(K+1)+1;
			for(int i=0;i<9;i++)
			{
				a[i]=1;
			}
			memset(ini.a,0,sizeof(ini.a));
			memset(dp.a,0,sizeof(dp.a));
			for(;a[0]<2;)
			{
				int j=c[shanquan(a)],k=c[shanquan(a+4)],d[9];
				if(j && k)
				{
					long long o=yamaizumi(a,8,C)*moko(e[j],mod-2)%mod;
					int y=j+((a[1]==a[2])+(a[1]==a[3])+(a[4]==a[2])+(a[4]==a[3]))*n;
					if(y<m)ini.a[1][y]=e[j];
					int sum=(a[5]==a[6])+(a[5]==a[7])+(a[8]==a[6])+(a[8]==a[7]);
					for(int i=1;i<5;i++)
					{
						sum+=(a[i]==a[i+4]);
					}
					for(int z=0;z<=K-sum;z++)
					{
						(dp.a[j+z*n][k+(z+sum)*n]+=o)%=mod;
					}
				}
				int i;
				for(i=8;a[i]==i;i--)
				{
					a[i]=1;
				}
				a[i]++;
			}
			for(int i=1;i<=m;i++)
			{
				dp.a[i][m]=1;
			}
			return (ini*moko(dp,H)).a[1][m];
		}
};
```