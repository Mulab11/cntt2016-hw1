#include <vector>
#include <string>
using namespace std;
class History{
public:
	void cmin(int&a,int b){b<a?a=b:1;}
	string verifyClaims(vector <string> dynasties, vector <string> battles, vector <string> queries){
		int n=dynasties.size(),t[n][11],G[n][n],c,x,y,p,q,d;
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++)G[i][j]=i==j?0:23333333;
			for(int j=0,m=t[i][0]=0;j<dynasties[i].length();j++)(c=dynasties[i][j])==' '?t[i][++m]=0:(t[i][m]*=10)+=c-'0';
		}
		for(int i=0,tot=0;i<battles.size();i++)
			for(int j=0;j<battles[i].length();j++)
				c=battles[i][j],++tot%6==1?x=c-'A':tot%6==2?p=c-'0':tot%6==4?y=c-'A':tot%6==5?
					cmin(G[x][y],t[x][p+1]-t[x][0]-t[y][q=c-'0']+t[y][0]-1),cmin(G[y][x],t[y][q+1]-t[y][0]-t[x][p]+t[x][0]-1),1:1;
		for(int k=0;k<n;k++)
			for(int i=0;i<n;i++)
				for(int j=0;j<n;j++)cmin(G[i][j],G[i][k]+G[k][j]);
		string ans;
		for(int i=0;i<queries.size();i++){
			x=queries[i][0]-'A',y=queries[i][3]-'A',p=queries[i][1]-'0',q=queries[i][4]-'0',d=t[x][p]-t[x][0]-t[y][q]+t[y][0];
			ans.push_back(G[x][y]<=d-t[y][q+1]+t[y][q]||-G[y][x]>=d+t[x][p+1]-t[x][p]?'N':'Y');
		}
		return ans;
	}
};
],S[pr]))pr=(pr+s-1)%s;
			while(l[i]<m&&!S[pl].onright(R[i],R[l[i]]))++l[i];
			while(r[i]<m&&S[pr].onleft(R[i],R[r[i]]))++r[i];
		}
		long long ans=*sum=0;
		for(int i=0;i<m;i++)sum[i+1]=sum[i]+l[i];
		for(int i=0,p=0;i<m;i++){
			while(p<=i||p<l[i]&&l[p]<=r[i])++p;
			ans+=sum[l[i]]-sum[p]-r[i]*(long long)(l[i]-p);
			if(r[i]<l[i]&&p<l[i])ans--;
		}
		return ans;
	}
};
0;i<n;i++){
			solver.link(i*9+1,0,0);
			for(int j=2;j<=9;j++)solver.link(i*9+j,i*9+j-1,0);
		}
		int s[12],l=0;
		for(int i=0;i<courseInfo.size();i++)
			for(int j=0,x;j<courseInfo[i].length();j++)
				(x=courseInfo[i][j])==' '?add(s),l=0:s[l++]=x;
		add(s);
		return solver.solve();
	}
};
es[y][2]);
			}
		}
		return ans;
	}
};
ej=first[E[j].to];ej;ej=ej->next)if(!ej->del&&ej!=E[j].rev)solver.w[solver.nx][solver.ny++]=f[ei->to][ej-E];
			solver.nx++;
		}
		f[i][j]+=solver.match();
	}
	int getmax(vector <int> a, vector <int> b){
		N=a.size()+1;ne=E;
		for(int i=0;i<N-1;i++)link(a[i],b[i]);
		now=0;dfs(0,-1);
		int ans=0,tmp;
		for(int i=1;i<N;i++){
			fe[i]->del=fe[i]->rev->del=1;
			memset(f,0,sizeof(f));
			for(int j=0;j<N;j++)if(pre[j]<pre[i]||pre[j]>=pos[i]){
				for(edge*ei=first[i];ei;ei=ei->next)if(!ei->del)
					for(edge*ej=first[j];ej;ej=ej->next)if(!ej->del)calc(ei->to,ej-E);
				solver.nx=0;
				for(edge*ei=first[i];ei;ei=ei->next)if(!ei->del){
					solver.ny=0;
					for(edge*ej=first[j];ej;ej=ej->next)if(!ej->del)solver.w[solver.nx][solver.ny++]=f[ei->to][ej-E];
					solver.nx++;
				}
				if((tmp=1+solver.match())>ans)ans=tmp;
			}
			fe[i]->del=fe[i]->rev->del=0;
		}
		return ans;
	}
};
ver.match())>ans)ans=tmp;
			}
			fe[i]->del=fe[i]->rev->del=0;
		}
		return ans;
	}
};
ep+1,ff);
	}
	int getCount(vector <int> edge1, vector <int> edge2, int k){
		this->n=edge1.size()+1;this->k=k;ne=E;ans=0;
		for(int i=0;i<edge1.size();i++)link(edge1[i],edge2[i]),link(edge2[i],edge1[i]);
		init();
		if(k==1)return fac[n];
		if(2*k>n){
			init(0,-1);
			dfs1(0,-1,1);
			return ans*fac[2*k-n]%MOD*fac[n-k]%MOD*fac[n-k]%MOD;
		}
		for(int i=0;i<n;i++){
			init(i,-1);
			dfs2(i,-1,0,inv[k]);
		}
		return ans*fac[k]%MOD*fac[k]%MOD;
	}
};
