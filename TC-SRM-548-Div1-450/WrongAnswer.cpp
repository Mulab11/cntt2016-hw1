// FST:题意看错，不知道可以填0
#include <vector>
#include <algorithm>
using namespace std;
class KingdomAndDice{
public:
	// N:不同段个数 K:firstDie中需填的0的个数 S:size^2 Q:已确定部分的答案
	// num[i]:第i个段每选1个数增加的答案 cnt[i]:第i个段可选数的个数
	// g[i][j][k]: 从前i个段中取j个数使得答案为k，第i个段至少取多少个数
	int N,K,S,Q,num[52],cnt[52],g[52][52][2610];
	bool cmp(int a,int b){
		if(b<0)return 1;
		int da=2*a-S,db=2*b-S;
		if(da<0)da=-da;
		if(db<0)db=-db;
		if(da!=db)return da<db;
		return a<b;
	}
	double newFairness(vector <int> firstDie, vector <int> secondDie, int X){
		S=firstDie.size();S*=S;
		sort(firstDie.begin(),firstDie.end());
		sort(secondDie.begin(),secondDie.end());
		firstDie.push_back(X+1);
		secondDie.push_back(X+1);
		int f=0;
		while(!firstDie[f])f++;
		K=f;
		for(int s=0;s<secondDie.size();s++){
			num[N]=s;
			cnt[N]=secondDie[s]-(s?secondDie[s-1]:0)-1;
			while(firstDie[f]<secondDie[s])f++,Q+=s,cnt[N]--;
			N++;
		}
		for(int i=0;i<=N;i++){
			for(int j=0;j<=K;j++){
				for(int k=0;k<=S;k++){
					if(i==0)g[i][j][k]=j||k!=Q?1<<30:0; // 边界：仅j=0且k=Q时为0，否则为INF（不存在方案）
					else if(g[i-1][j][k]<=(i==1?0:cnt[i-2]))g[i][j][k]=0; // 第i段不取
					else if(j&&k>=num[i-1])g[i][j][k]=g[i][j-1][k-num[i-1]]+1; // 第i段取至少1个
					else g[i][j][k]=1<<30; // 不存在方案则为INF
				}
			}
		}
		int ans=-1;
		for(int j=0;j<=K;j++)
			for(int k=0;k<=S;k++)if(g[N][j][k]<=cnt[N-1]&&cmp(k,ans))ans=k;
		return ans*1.0/S;
	}
};
