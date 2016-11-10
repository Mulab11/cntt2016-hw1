# FlippingBitsDiv1
作者：尤艺霖

关键词：算法复合 动态规划
## 题意简述
给出一个只包含字符`0`和字符`1`的字符串和数字 $$M$$。

允许两种操作：

1.将字符串的某一位取反。

2.将字符串的前 $$k\times M$$ 位全都取反。

设该字符串长度为N，要求在只用这两种操作的情况下，用最少的操作次数使得这个字符串的前 $$N-M$$ 位构成的字符串和后$$N-M$$ 位构成的字符串完全相同。

字符串通过输入它的各个部分的方式给出，要求输出最少的操作次数。

保证字符串的长度小于或等于 $$300$$。
## 算法
设 $$T=N/M$$ ，由于$$N$$的范围不超过300，所以$$T$$和$$M$$的较小值一定小于或等于17，可以分别解决$$T$$和$$M$$较小的情况。

考虑 $$M$$ 小于或等于17的情况：

可以发现，对于满足条件的字符串，它一定是由前M位不断循环获得，所以可以枚举前M位从而获得最终的字符串。

将最终的字符串与原先的字符串进行异或操作，所获得的新字符串中所有为1的就是需要改变的位置，问题转化为将这个新串清零。

可以发现，在 $$T\times M$$  之后的所有位只能通过第一种操作进行清零，可以单独考虑。

剩余的部分使用动态规划，考虑将剩余的部分按照第二种操作的范围分为 $$T$$ 个部分，每个部分清零所需要的第一种操作的操作次数由这个部分内1的个数和这个部分有没有被第二种操作取反过。可以从后往前进行动态规划，状态为二维，第一维表示进行到的部分编号，第二维表示上一块是否被第二种操作取反过。如果当前部分在第二种操作上的状态需要与上一个部分不同则需要增加1的代价，表示需要另一次第二种操作来取反。剩余的代价则是进行第一种操作所需要的代价。

这部分的实现细节参见代码：

```C++
inline int firstpart(int n,int m)// if m is less than or equal to 17
{
	int ans=n;
	for (int mask=0;mask<(1<<m);mask++)
	{
		int co=0;
		for (int i=1;i<=m;i++)
		{
			if((mask&(1<<(i-1)))!=0)tmp[i]=1;
			else tmp[i]=0;
		}
		for (int i=m+1;i<=n;i++)
		{
			tmp[i]=tmp[(i-1)%m+1];
		}
		for (int i=1;i<=n;i++)
		{
			tmp[i]=tmp[i]^str[i];
		}
		for (int i=(n/m)*m+1;i<=n;i++)
		{
			co+=tmp[i];
		}
		for (int i=1;i<=n/m+1;i++)
		{
			dp[i][0]=n;
			dp[i][1]=n;
		}
		dp[n/m+1][0]=0;
		for (int i=n/m;i>=1;i--)
		{
			int c0=0,c1=0;
			for (int j=i*m-m+1;j<=i*m;j++)
			{
				if(tmp[j]==0)c0++;
				else c1++;
			}
			dp[i][0]=min(dp[i+1][0],dp[i+1][1]+1)+c1;
			dp[i][1]=min(dp[i+1][0]+1,dp[i+1][1])+c0;
		}
		ans=min(ans,co+min(dp[1][0],dp[1][1]));
	}return ans;
}
```

考虑 $$T$$ 小于或等于17的情况：

显然的，对于第二种操作，$$k$$ 小于或等于 $$T$$ ，并且对于每一个不同的 $$k$$ ，最多只需要做一次第二种操作。

所以可以暴力枚举每一种 $$k$$ 的操作是否进行，从而排除第二种操作。

对于第一种操作，枚举位置对 $$M$$ 取模的不同余数，对于每个余数，它所对应的所有位置应当相同，可以通过计数抉择它应当是`0`还是`1`，从而统计答案。

这部分的实现细节参见代码：

```C++
inline int solve2(int n,int m)// solve the situation if we can only flip one bit
{
	int ans=0;
	for (int i=1;i<=m;i++)
	{
		int c0=0;
		int c1=0;
		for (int j=0;j<=n/m;j++)
		{
			if(j*m+i<=n)
			{
				if(tmp[j*m+i]==0)c0++;
				else c1++;
			}
		}
		ans+=min(c0,c1);
	}return ans;
}
inline int secondpart(int n,int m)// if n/m is less than or equal to 17
{
	int t=n/m,ans=n;
	for (int mask=0;mask<(1<<t);mask++)
	{
		for (int i=1;i<=n;i++)
		{
			tmp[i]=str[i];
		}
		for (int i=0;i<t;i++)
		{
			if((mask&(1<<i))!=0)
			{
				for (int j=i*m+1;j<=i*m+m;j++)
				{
					tmp[j]=1-tmp[j];
				}
			}
		}
		ans=min(ans,cnt[mask]+solve2(n,m));
	}return ans;
}
```