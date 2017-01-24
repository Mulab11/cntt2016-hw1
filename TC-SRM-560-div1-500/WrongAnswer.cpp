#include <vector>
#include <cstring>
using namespace std;
class DrawingPointsDivOne{
public:
	vector<int>X,Y;
	int a[310][310],S[310][310];
	bool check(int M){
		memset(S,0,sizeof(S));
		for(int i=0;i<X.size();i++)
			S[X[i]+1][Y[i]+1]++,S[X[i]+1][Y[i]+M+1]--,S[X[i]+M+1][Y[i]+1]--,S[X[i]+M+1][Y[i]+M+1]++;
		for(int i=1;i<300;i++)
			for(int j=1;j<300;j++)S[i][j]+=S[i-1][j]+S[i][j-1]-S[i-1][j-1];
		for(int i=1;i<300;i++)
			for(int j=1;j<300;j++)S[i][j]=S[i-1][j]+S[i][j-1]-S[i-1][j-1]+!!S[i][j];
		for(int l=0,r=M;r<300;l++,r++)
			for(int d=0,u=M;u<300;d++,u++)if(!a[l][d]&&S[r][u]-S[r][d]-S[l][u]+S[l][d]==M*M)return 0;
		return 1;
	}
	int maxSteps(vector <int> x, vector <int> y){
		memset(a,0,sizeof(a));
		for(int i=0;i<x.size();i++)a[x[i]+=70][y[i]+=70]=1;
		X=x;Y=y;
		if(check(150))return -1;
		int left=0,right=150,mid;
		while(right-left>1){
			mid=left+right>>1;
			if(check(mid+1))left=mid;
			else right=mid;
		}
		return left;
	}
};
		std::sort(items,iter);
		int tot=0;
		for(item*it=items;it<iter-1;it++){
			tot+=it->add;
			if(!tot&&(it+1)->pos>it->pos+1e-14)return 1;
		}
		return 0;
	}
	double findMaximumDistance(vector <int> x, vector <int> y, vector <int> r){
		PI=acos(-1);X=x;Y=y;R=r;
		double left=0,right=80000,mid;
		for(int t=0;t<60;t++){
			mid=(left+right)/2;
			if(check(mid))left=mid;
			else right=mid;
		}
		return left;
	}
};
;i++){ // 预处理ls[i]和rs[i]
			if(i>=4<<j)++j;
			ls[i]=ls[i-1];rs[i]=rs[i-1];
			i<3<<j?++ls[i]:++rs[i];
		}
		for(int i=1;i<=n;i++)if(deg[i]==2) // 枚举根节点
			getsiz(i,0),ans+=dfs(i,0);
		return ans;
	}
};
�利益
				}
				else{
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
