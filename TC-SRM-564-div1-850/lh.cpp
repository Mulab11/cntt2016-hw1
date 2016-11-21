#include<cstdio>
#include<vector>
#include<string>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class DefectiveAddition{
	public:
	static const int maxn=55,mod=1000000007;
	long long dp[maxn][2];

	int count(vector<int> cards, int aim){
        int n=cards.size();
        sort(cards.begin(),cards.end());
        int t=1;
        while (2*t<=cards[n-1]+1) t*=2;
        if (aim>=2ll*t){
//        	printf("t=%d,aim=%lld\n",t,aim);
//        	printf("return %d\n",0);
			return 0;
		}
        
        memset(dp,0,sizeof(dp));
        dp[0][0]=1;
        for (int i=0;i<n-1;i++){
            for(int j=0;j<2;j++){
                dp[i+1][j]=(dp[i+1][j]+dp[i][j]*min(cards[i]+1,t))%mod;
                dp[i+1][j^1]=(dp[i+1][j^1]+dp[i][j]*max(cards[i]-t+1,0))%mod;
            }
        }
        long long ans=0;
        if (aim>=0&&aim<t) ans=dp[n-1][0];
        else ans=dp[n-1][1];
        
        if(cards[n-1]>=t){
//        	puts("xxxxxxxxx");
            vector<int> nn=cards;
			nn[n-1]^=t;
			ans=(ans+count(nn,aim^t))%mod;
        }
//        printf("return %lld\n",ans);
        return (int)(ans%mod);
    }
};
