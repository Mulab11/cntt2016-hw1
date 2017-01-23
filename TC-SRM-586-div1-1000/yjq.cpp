#include<bits/stdc++.h>
#define INF 1000000007
using namespace std;const int MAXN=60;int dp[MAXN][MAXN][MAXN];int get(int l,int r){return(l+r-1)*(r-l)/2;}class StringWeight{public:int getMinimum(vector<int>l){int n=l.size(),sum[51]={0},ans=INF;for(int i=0;i<n;i++)sum[i+1]=sum[i]+l[i];for(int i=0;i<=n;i++){for(int j=0;j<=26;j++){for(int k=0;k<=26;k++)dp[i][j][k]=INF;}}dp[0][0][0]=0;for(int i=0;i<n;i++){for(int u=0;u<=26;u++){for(int v=0;v<=26;v++){if(dp[i][u][v]==INF)continue;int len=min(l[i],26);if(len>26-v)continue;for(int p=0;p<=26;p++){for(int q=v;q<=26;q++){int a=0,b=0;if(p>=u){a=p-u;if(a>26-u-v)continue;if(a+q-v>len)continue;b=min(min(len-(a+q-v),q-v),u);a+=b;}else{b=u-p;if(b>u||b>q-v)continue;if(q-v>len)continue;a=min(min(len-(q-v),q-v-b),u-b);b+=a;}if(a+q-v-b>26-u-v)continue;if(b+len-a-b-(q-v-b)>u)continue;int w=get(sum[i],sum[i]+b)-get(sum[i+1]-a,sum[i+1]);if(l[i]>len&&b==u)w+=l[i]-len;dp[i+1][p][q]=min(dp[i+1][p][q],dp[i][u][v]+w);}}}}}for(int i=0;i<=26;i++)ans=min(ans,dp[n][0][i]);return ans;}} sol ;

int a[] = {14, 6, 30, 2, 5, 61} ; 
vector<int> g ; 
int main() { 
		for (int i = 0; i < 6; i ++) 
		g.push_back(a[i]) ; 
		printf("%d\n", sol.getMinimum(g) ) ; 
}
