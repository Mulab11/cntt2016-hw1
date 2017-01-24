#include <vector>
using namespace std;
class XorAndSum{
public:
	long long maxSum(vector<long long> number){
		int n=number.size();
		long long a[60],x,t,ans=0;
		for(int i=n-1;i>=0;i--){ // 高斯消元
			for(int j=0;j<i;j++)number[j]>number[i]?t=number[i],number[i]=number[j],number[j]=t:1;
			for(int j=0;j<i;j++)(number[j]^number[i])<number[j]?number[j]^=number[i]:1;
		}
		for(int i=0,l,r;i<n;i++){ // 用拟阵的思想，每次贪心选取最大的独立集
			a[i]=x=t=l=0; // a[i]:选哪些数xor x:xor的结果 t:a[i]被a[0,i)消的结果
			for(r=1;r<=i&&a[i-r]<(1ll<<r);r++);r--; // r:用a[0,i)可以组合成2^r以内的所有数
			for(int j=n-1;j>=0;j--){ // 从大到小决定a[i]的每一位
				if((x^number[j])>x)x^=number[j],a[i]|=1ll<<j; // 贪心取尽可能大
				while(l<i&&a[l]>=(1ll<<j+1))l++; // l:a[l]的最高位不超过j
				if(l==i||a[l]<(1ll<<j)){ // j这一位为空
					if(j==r&&(a[i]>>j)==(t>>j))x^=number[j],a[i]^=1ll<<j; // 如果不改变决策就会不独立（t=x），就改变决策
				}
				else if((a[i]>>j&1)!=(t>>j&1))t^=a[l]; // j这一位不为空，用a[l]消使得t和x这一位相同
			}
			ans+=x; // 将最大的可选的x加入答案
			for(int j=0;j<i;j++)if((a[i]^a[j])<a[i])a[i]^=a[j]; // 前面部分消元
			for(int j=i;j&&a[j-1]<a[j];j--)t=a[j],a[j]=a[j-1],a[j-1]=t;
		}
		return ans;
	}
};
 i=n;i--;)for(int j=n;--j>i;)
				if(bridges[i][j]!='X')solver.link(i+2,j+2,bridges[i][j]=='N'?1<<30:2,bridges[i][j]=='N'?1<<30:2);
			if(solver.maxflow()<an+bn<<1)return"No";
		}
		return"Yes";
	}
};
n+bn<<1)return"No";
		}
		return"Yes";
	}
};
.a[P(s,j)][P(t,j-d)]=(A.a[P(s,j)][P(t,j-d)]+p)%MOD;
		}
		else for(to[i]=0;to[i]<=m;to[i]++){
			if(to[i]==m)c?dfs(s,i+1,m+1,c-1,p*c%MOD,k),1:1;
			else dfs(s,i+1,m,c,p,k);
		}
	}
	int find(int C, int K, long long H){
		// 构造矩阵 
		A.N=M.N=S.N=7*(K+1);
		for(int s=0;s<7;s++)if(spl[s][3]+1<=C)dfs(s,0,spl[s][3]+1,C-spl[s][3]-1,1,K);
		// 计算答案
		solve(H);
		long long ans=0,v[56]={0},w[56]={0}; // ans为答案，v为系数，w为初始向量 
		for(int s=0;s<7;s++)if(spl[s][3]+1<=C){
			v[s]=rot[s];
			for(int i=0;i<=spl[s][3];i++)(v[s]*=C-i)%=MOD;
			w[P(s,dig[s])]=1;
		}
		for(int s=0;s<7;s++)if(spl[s][3]+1<=C)
			for(int k=0;k<=K;k++)
				for(int i=0;i<A.N;i++)(ans+=S.a[P(s,k)][i]*w[i]%MOD*v[s])%=MOD;
		return ans; 
	}
};
ight;
	}
};
�的一层
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
