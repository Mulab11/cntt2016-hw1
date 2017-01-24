#include <vector>
#include <string>
using namespace std;
class BoundedOptimization{
public:
	int n,Max,lb[13],ub[13],k[13][13],ty[13],del[13];
	double x[13],ans;
	void dfs(int i,int cnt,int sum){
		if(!cnt&&sum<0)return;
		if(i==n){
			double s=0;
			for(i=n;i--;){
				if(!ty[i]){
					if(lb[i]*cnt<=sum+cnt*del[i]&&sum+cnt*del[i]<=ub[i]*cnt)x[i]=sum*1.0/cnt+del[i];
					else return;
				}
				for(int j=n;--j>i;)k[i][j]?s+=x[i]*x[j]:1;
			}
			if(s>ans)ans=s;return;
		}
		for(ty[i]=0;ty[i]<3;ty[i]++){
			if(!ty[i]){
				del[i]=0;
				int s=sum;
				bool flag=1;
				for(int j=i,t;j--;){
					if(k[i][j]&&ty[j])s-=(t=ty[j]==1?lb[j]:ub[j]),del[i]+=t;
					if(!k[i][j]&&!ty[j])flag=0;
				}
				if(flag)dfs(i+1,cnt+1,s);
				for(int j=i;j--;){
					if(k[i][j]&&ty[j])del[i]+=ty[j]==1?lb[j]:ub[j];
				}
			}
			else{
				int*t=ty[i]==1?lb:ub,s=sum-t[i];
				for(int j=i;j--;)if(k[i][j]&&!ty[j])s-=t[i],del[j]+=t[i];
				x[i]=t[i];dfs(i+1,cnt,s);
				for(int j=i;j--;)if(k[i][j]&&!ty[j])del[j]-=t[i];
			}
		}
	}
	double maxValue(vector <string> expr, vector <int> lowerBound, vector <int> upperBound, int maxSum){
		n=lowerBound.size();
		for(int i=0,l='+',c;i<expr.size();i++)
			for(int j=0;j<expr[i].length();j++)(c=expr[i][j])!='+'&&l!='+'?k[c-'a'][l-'a']=k[l-'a'][c-'a']=1:1,l=c;
		int sum=0;
		for(int i=0;i<n;i++)lb[i]=lowerBound[i],sum+=(ub[i]=upperBound[i]);
		if(maxSum>=sum){
			sum=0;
			for(int i=0;i<n;i++)for(int j=i+1;j<n;j++)
				sum+=k[i][j]*upperBound[i]*upperBound[j];
			return sum;
		}
		dfs(0,0,maxSum);
		return ans;
	}
};
urn sum;
		}
		dfs(0,0,maxSum);
		return ans;
	}
};
se{
					link(0,P(i,j),U+dec(cost[i][j])),link(P(i,j),1,U); // 偶数格割0表示选，割1表示不选
					for(int d=0,x,y;d<4;d++)
						if((x=i+vx[d])>=0&&x<R&&(y=j+vy[d])>=0&&y<C)link(Q(i,j),P(x,y),INF);
					ans+=dec(benefit[i][j]),link(P(i,j),Q(i,j),dec(benefit[i][j])); // 默认得到利益，如果没被占据则取消利益
				}
			}
		}
		return ans-maxflow();
	}
};
g ans=0,v[56]={0},w[56]={0}; // ans为答案，v为系数，w为初始向量 
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
