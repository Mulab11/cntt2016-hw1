#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define N 27
using namespace std;
struct StringWeight
{
	int f[51][N][N];
	//f[i][j][k]表示前i段序列，启用了j种字母，并用完了k种字母（以后再也不会出现） 
	int getMinimum(vector <int> L)
	{
		int n=L.size();
		int i,j,k,l,o,p;
		memset(f,0x3f,sizeof(f));
		f[0][0][0]=0;
		for(i=0;i<n;i++)
		for(j=0;j<=26;j++)
		for(k=0;k<=j;k++)
		{
			for(l=max(0,min(L[i],26)-(j-k));l+j<=26;l++)
			for(o=0;o+k<=j+l;o++)
			{
				//表示在第i段序列中，新启用了l种字母，并完结了o种字母 ，其中包含在这里开始在这里终结的字母 
				int tmp=0;
				p=min(j-k,o);
				tmp+=(1+p)*p/2;//计算在之前的某段开始，在这段结束的贡献 
				if(j-k>o) tmp+=(j-k-o)*L[i];//这种情况说明有在之前某段开始，在之后某段结束的情况，那么整段长度都需要被记入答案，并且可以用它们来填充不中间够的地方 
				else if(L[i]>26) tmp+=L[i]-26;//这种情况说明没有上述情况，则长出来部分需要被某个相邻的字母填充 
				p=min(l,j+l-k-o);
				tmp+=p*(p-1)/2;//计算从这段开始的贡献，需要刨除在这段开始在这段结束的方案数 
				f[i+1][j+l][k+o]=min(f[i+1][j+l][k+o],tmp+f[i][j][k]);
			}
		}
		int ans=707185547;
		for(i=0;i<=26;i++)
		ans=min(ans,f[n][i][i]);//i表示一共用了多少种字母 
		return ans;
	} 
};