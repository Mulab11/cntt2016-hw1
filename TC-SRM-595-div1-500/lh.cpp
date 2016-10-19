#include<cstdio>
#include<string>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class LittleElephantAndRGB{
	private:
		static const int maxn=2510;
		string S;
		int dp[maxn][maxn],f[maxn];
	public:
		long long getNumber(vector <string> list, int m){
			int n=list.size();
			for (int i=0;i<n;++i) S+=list[i];
			n=S.size();
			int k=0,x=n;
			
			//递推g数组。 
			for (int i=n-1;i>=0;--i){
				if (S[i]=='G') ++k;
				else k=0;
				if (k>=m){
					x=i+m-1;
					k=m;
				}
				else if (k==0) dp[i][0]=dp[i+1][0]+n-i;
				else dp[i][k]=dp[i+1][k]+x-(i+k-1);
				for (int j=1;j<k;++j) dp[i][j]=dp[i+1][j]+1;
				for (int j=k+1;j<m;++j) dp[i][j]=dp[i+1][j];
				f[i]=f[i+1]+n-x;
			}
			
			//计算dp数组。 
			for (int i=0;i<n;++i) for (int j=m-1;j>=0;--j) dp[i][j]+=dp[i][j+1]; 
			
			//统计答案。 
			long long ans=0;
			for (int a=0;a<n;++a){
				k=0;
				x=0;
				for (int b=a;b<n;++b){
					if (S[b]=='G') ++k;
					else k=0;
					if (k>=m) x=1;
					if (x) ans+=(n-b-1)*(n-b-2)/2+(n-b-1);
					else ans+=f[b+1]+dp[b+1][m-k];
				}
			}
			return ans;
		}
};
