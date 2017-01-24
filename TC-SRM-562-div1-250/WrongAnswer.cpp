#include <vector>
#include <string>
using namespace std;
class PastingPaintingDivOne{
public:
	int min(int a,int b){return a<b?a:b;}
	int max(int a,int b){return a>b?a:b;}
	int f(char c){return c=='R'?0:c=='G'?1:2;}
	void solve(string line,int T,vector<long long>&ans){
		int n=line.length();
		vector<int> next(n);next[n-1]=n-1;
		for(int i=n-2;i>=0;i--)next[i]=line[i]!='.'?i:next[i+1];
		if(line[next[0]]=='.')return;
		if(T>n){
			for(int i=0;i<n;i++)
				if(next[i]<n&&line[next[i]]!='.')ans[f(line[next[i]])]++;
			ans[f(line[next[0]])]+=T-next[0]-1;
		}
		else for(int i=0;i<n+T-1;i++){
			int l=max(i-T+1,0),r=min(i,n-1);
			if(next[l]<=r&&line[next[l]]!='.')ans[f(line[next[l]])]++;
		}
	}
	vector<long long> countColors(vector <string> clipboard, int T){
		vector<long long> ans;
		for(int i=0;i<3;i++)ans.push_back(0);
		for(int b=-clipboard[0].length()+1;b<(int)clipboard.size();b++){
			string line;
			for(int x=max(-b,0),y=x+b;x<clipboard[0].length()&&y<clipboard.size();x++,y++)
				line.push_back(clipboard[y][x]);
			solve(line,T,ans);
		}
		return ans;
	}
};
ans);
		}
		return ans;
	}
};
){
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
