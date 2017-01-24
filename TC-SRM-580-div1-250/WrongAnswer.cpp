#include <vector>
#include <algorithm>
using namespace std;
class EelAndRabbit{
public:
	int nums[60],cnt,sum[60],max[60];
	struct range{int L,R;bool operator<(const range&r)const{return R<r.R;}}a[60];
	int getmax(vector <int> l, vector <int> t){
		for(int i=0;i<l.size();i++)nums[cnt++]=t[i];
		sort(nums,nums+cnt);cnt=unique(nums,nums+cnt)-nums;
		for(int i=0;i<l.size();i++)a[i]=(range){lower_bound(nums,nums+cnt,t[i])-nums,upper_bound(nums,nums+cnt,t[i]+l[i])-nums};
		sort(a,a+l.size());
		for(int i=0,r=1;r<=cnt;r++)
			for(max[r]=max[r-1];i<l.size()&&a[i].R<=r;i++)
				for(int j=a[i].L;j<a[i].R;j++)++sum[j]>max[r]?max[r]=sum[j]:1;
		int ans=0;
		for(int i=0;i<=cnt;i++)sum[i]+max[i]>ans?ans=sum[i]+max[i]:1;
		return ans;
	}
};
eturn ans;
	}
};
+b<N;b++)
				for(int c=0;a+b+c<N;c++)ans+=cost(f[a+1][b][c]*(a+1),f[a][b+1][c]*(b+1),f[a][b][c+1]*(c+1))/(a+b+c+1);
		return ans;
	}
};
	return ans;
	}
};
int a,int b){return a>b?a:b;}
	void cmin(int&a,int b){b<a?a=b:1;}
	int maxStores(int N, vector <string> interestingStores, vector <string> roads){
		this->N=N;read(interestingStores,stores,M);read(roads,this->roads,E);ne=edges;
		for(int i=0;i<E;i++)link(this->roads[i][0],this->roads[i][1],this->roads[i][2]);
		for(int S=0;S<(1<<M);S++)
			for(int x=0;x<M;x++)f[S][x]=INF;
		for(int i=0;i<M;i++){
			shortest_path(i);
			for(int j=0;j<M;j++)dis[i][j]=D[j];
			if(D[N-1]<=stores[i][1])cmin(f[1<<i][i],max(D[N-1],stores[i][0])+stores[i][2]);
		}
		int ans=0;
		for(int S=1;S<(1<<M);S++){
			popc[S]=popc[S&(S-1)]+1;
			for(int x=0;x<M;x++)if((S>>x&1)&&f[S][x]<INF){
				if(popc[S]>ans)ans=popc[S];
				for(int y=0;y<M;y++)if(!(S>>y&1)&&f[S][x]+dis[x][y]<=stores[y][1])cmin(f[S|1<<y][y],max(f[S][x]+dis[x][y],stores[y][0])+stores[y][2]);
			}
		}
		return ans;
	}
};
][0])+stores[y][2]);
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
