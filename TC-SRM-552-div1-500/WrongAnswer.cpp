#include <vector>
#include <string>
using namespace std;
class FoxAndFlowerShopDivOne{
public:
	// n,m:矩阵大小 diff:最大差值 D[i][j]:(1,1)到(i,j)中L和P的个数差 S[i][j]:(1,1)到(i,j)中L和P的个数和
	int n,m,diff,D[31][31],S[31][31],
		up_a[31][1801],*up[31], // up[i][j]:前i行L和P个数差为j的矩形最大个数和
		down_a[31][1801],*down[31], // down[i][j]:上边界在第i行且L和P个数差为j的矩形最大个数和
		Q[1801]; // 单调队列
	void cmax(int&a,int b){b>a?a=b:1;}
	int solve(){ // 求两个矩形能被水平线分隔时的答案
		for(int i=0;i<=n;i++){ // 预处理数组
			up[i]=up_a[i]+n*m;down[i]=down_a[i]+n*m;
			for(int j=-n*m;j<=n*m;j++)up[i][j]=down[i][j]=-100000000;
		}
		for(int u=0;u<n;u++)for(int d=u+1;d<=n;d++){
			for(int l=0;l<m;l++)for(int r=l+1;r<=m;r++){
				int i=D[d][r]-D[u][r]-D[d][l]+D[u][l],
					j=S[d][r]-S[u][r]-S[d][l]+S[u][l];
				cmax(up[d][i],j);cmax(down[u][i],j);
			}
		}
		int ans=-1;
		for(int i=1;i<=n;i++){
			int h=0,t=-1,r=-n*m-1,*a=down[i];
			for(int j=n*m;j>=-n*m;j--){
				while(h<=t&&j+Q[h]<-diff)++h;
				while(r<n*m&&j+r<diff){
					for(++r;h<=t&&a[Q[t]]<=a[r];--t);
					Q[++t]=r;
				}
				cmax(up[i][j],up[i-1][j]);
				cmax(ans,up[i][j]+a[Q[h]]);
			}
		}
		return ans;
	}
	int theMaxFlowers(vector <string> flowers, int maxDiff){
		n=flowers.size();m=flowers[0].length();diff=maxDiff;
		int ans=-1,tmp;
		// 预处理前缀和
		for(int i=0;i<=n;i++){
			for(int j=0;j<=m;j++){
				if(!i||!j)D[i][j]=S[i][j]=0;
				else{
					D[i][j]=D[i-1][j]+D[i][j-1]-D[i-1][j-1];
					S[i][j]=S[i-1][j]+S[i][j-1]-S[i-1][j-1];
					if(flowers[i-1][j-1]=='L')D[i][j]++,S[i][j]++;
					if(flowers[i-1][j-1]=='P')D[i][j]--,S[i][j]++;
				}
			}
		}
		if((tmp=solve())>ans)ans=tmp;
		// 交换矩形行列
		tmp=n;n=m;m=tmp;
		for(int i=0;i<=n||i<=m;i++){
			for(int j=i+1;j<=n||j<=m;j++){
				tmp=D[i][j];D[i][j]=D[j][i];D[j][i]=tmp;
				tmp=S[i][j];S[i][j]=S[j][i];S[j][i]=tmp;
			}
		}
		return (tmp=solve())>ans?tmp:ans;
	}
};
		x[i]=calc(N-i);
			for(int j=i;j;j--)(C[j]+=C[j-1])%=MOD;
			for(int j=0;j<i;j++)x[i]=(x[i]+(MOD-C[j])*1ll*x[j])%MOD;
			ans=(ans+x[i]*1ll*s[i])%MOD;
		}
		return ans;
	}
};
��足条件就退出
		if(!rest){ // 枚举完所有点，判断是否可行
			init_ways();
			int w=ways((1<<N)-1);
			return w>=Min&&w<=Max;
		}
		int cnt=0;
		// i放新的一层
		if(cur!=-1)for(int i=0;i<N;i++)if(rest>>i&1){
			L[++top]=1<<i;
			for(G[i]=L[top-1];G[i];G[i]=(G[i]-1)&L[top-1]) // 枚举上一层向i连的边
				cnt+=count_graph(i,rest-(1<<i));
			top--;
		}
		// i放同一层
		for(int i=cur+1;i<N;i++)if(rest>>i&1){
			L[top]|=1<<i;
			if(top)for(G[i]=L[top-1];G[i];G[i]=(G[i]-1)&L[top-1]) // 枚举上一层向i连的边
				cnt+=count_graph(i,rest-(1<<i));
			else G[i]=0,cnt+=count_graph(i,rest-(1<<i));
			L[top]-=1<<i;
		}
		return cnt;
	}
	int getNumOrders(vector <int> blockTypes, int minWays, int maxWays){
		N=blockTypes.size();Min=minWays;Max=maxWays;
		for(int i=0;i<N;i++)cnt[i]=blockTypes[i],G[i]=0;
		*L=top=0;
		return count_graph(-1,(1<<N)-1);
	}
};
