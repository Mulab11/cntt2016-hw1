#include <string>
using namespace std;
class LeftRightDigitsGame2{
public:
	// 倒过来将digits拼在串s的首尾
	string f[52][52][2]; // f[l][r][k]:剩下[l,r)未确定，s[0,l)=lowerBound[0,l)，s[r,n)<lowerBound[r,n)（k=0）或s[r,n)>=lowerBound[r,n)，s[l,r)的最小字典序，不存在则为空串
	string g[52]; // g[i]:用digits的前i个字符构成最小字典序
	// 特判空串为不存在方案
	string min(string a,string b){return a==""||b==""?a+b:a<b?a:b;}
	string con(string a,string b){return a==""||b==""?"":a+b;}
	string minNumber(string digits, string lowerBound){
		g[0]="";
		for(int i=0;i<digits.length();i++)g[i+1]=min(g[i]+digits[i],digits[i]+g[i]);
		for(int l=digits.length()-1;l>=0;l--){
			for(int r=l+1;r<=digits.length();r++){
				for(int k=0;k<2;k++){
					char c=digits[r-l-1],L=lowerBound[l],R=lowerBound[r-1];
					string d;d.push_back(c);
					if(r-l==1)f[l][r][k]=c<L||(c==L&&!k)?"":d; // 边界为只含一个字符
					else f[l][r][k]=min(con(f[l][r-1][c!=R?c>R:k],d),c>L?d+g[r-l-1]:c==L?con(d,f[l+1][r][k]):""); // 转移时枚举放左边还是右边
				}
			}
		}
		return f[0][digits.length()][1];
	}
};
;i++)ans+=dfs(i,S[i]);
			return ans;
		}
		return make(0,m,0);
	}
};
0;
			if(f)return s;
		}
	}
	// 枚举s划分的所有转移to并计算方案数，以构造矩阵 
	void dfs(int s,int i,int m,int c,long long p,int k){ // i:枚举to[i]颜色 m:已出现颜色种数 c:剩余颜色种数 p:组成to的方案数 k:相同数对最大个数 
		if(i==4){
			int t=find(),d=dig[s];
			for(int j=0;j<4;j++)d+=(spl[s][j]==to[j]);
			for(int j=d;j<=k;j++)A.a[P(s,j)][P(t,j-d)]=(A.a[P(s,j)][P(t,j-d)]+p)%MOD;
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
