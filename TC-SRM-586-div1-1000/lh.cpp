#include<queue>
#include<cstdio>
#include<string>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class StringWeight{
	private:
		static const int maxn=53,maxm=27,inf=1000000000;
		int n;
		int dp[maxn][maxm][maxm];//  可启用， 已启用。 
		bool vis[maxn][maxm][maxm];
		queue<int> qa,qb;
	
	public:
		int getMinimum(vector <int> L){
			n=L.size();
			for (int i=0;i<=n;++i)
			for (int j=0;j<=26;++j)
			for (int k=0;k<=26;++k) dp[i][j][k]=inf;
			dp[0][26][0]=0;
			qa.push(26);
			qb.push(0);
			int su=0;
			for (int cas=1;cas<=n;++cas){
				int sz=qa.size(),len=min(26,L[cas-1]);
				int tr=su+L[cas-1];
				while(sz--){
					int canuse=qa.front(),had=qb.front();
					int tmp=dp[cas-1][canuse][had];
					qa.pop();
					qb.pop();
//					printf("dp[%d][%d][%d]=%d\n",cas-1,canuse,had,tmp);
					for (int i=0;i<=len&&i<=canuse;++i)//i开头，j结尾，k单独，t中间 
					for (int k=0;i+k<=len&&i+k<=canuse;++k) if (len-i-k<=had)
					for (int j=0;i+j+k<=len;++j)
					{
						int t=(len-i-j-k);
						int a=canuse-i-k,b=had+i-j;
						int ad=0;
						//tr,tr-1,...,tr-i+1
						if (i) ad-=(tr+tr-i+1)*i/2;
						//su+1,su+2,...,su+j
						if (j) ad+=(su+su+j+1)*j/2;
						if (t==0) ad+=L[cas-1]-i-j-k;
						
						dp[cas][a][b]=min(dp[cas][a][b],tmp+ad);
						if (!vis[cas][a][b]){
							vis[cas][a][b]=true;
							qa.push(a);
							qb.push(b);
						}
					}
				}
				su=tr;
			}
			int ans=inf;
			while(!qa.empty()){
				int a=qa.front(),b=qb.front();
				qa.pop();
				qb.pop();
				if (b==0&&dp[n][a][b]<ans) ans=dp[n][a][b];
			}
			return ans;
		}
};

