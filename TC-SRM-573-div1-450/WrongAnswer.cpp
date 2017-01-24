#include <vector>
#include <string>
#include <algorithm>
#define INF 100000000000000ll
using namespace std;
class SkiResorts{
public:
	int N,a[51];
	long long G[51][51],D[51];
	bool vis[51];
	long long diff(long long x,long long y){return x>y?x-y:y-x;}
	long long minCost(vector <string> road, vector <int> altitude){
		N=road.size();
		for(int i=0;i<N;i++)a[i]=altitude[i],D[i]=INF;
		sort(a,a+N);
		long long ans=INF;
		for(int T=0;T<N;T++){
			for(int i=0;i<N;i++)
				for(int j=0;j<N;j++)G[i][j]=road[i][j]=='Y'?diff(altitude[i],a[T]):INF;
			for(int i=0;i<N;i++)
				D[i]<G[N-1][i]?G[N-1][i]=D[i]:1,D[i]=INF,vis[i]=0;
			D[N-1]=0;
			for(int t=N;t--;){
				int i=0;for(int j=1;j<N;j++)!vis[j]&&D[j]<D[i]?i=j:1;
				vis[i]=1;for(int j=0;j<N;j++)!vis[j]&&D[i]+G[i][j]<D[j]?D[j]=D[i]+G[i][j]:1;
			}
			if(vis[0]&&D[0]+diff(altitude[0],a[T])<ans)ans=D[0]+diff(altitude[0],a[T]);
		}
		return ans==INF?-1:ans;
	}
};
turn ans==INF?-1:ans;
	}
};
'0'==x%10)rtot->x[i>>4]+=1ull<<i%16*4;
		sort(L,ltot);
		sort(R,rtot);
		for(int i=0;i<bulls.size();i++)G.x[i>>4]|=(1ull*bulls[i])<<i%16*4;
		item*ans1=0,*ans2=0;
		for(item*lp=ltot-1,*rp=R;lp>=L;lp--){
			while(rp<rtot&&*lp+*rp<G)rp++;
			for(item*p=rp;p<rtot&&!(G<*lp+*p);p++){
				if(!ans1)ans1=lp,ans2=p;
				else return"Ambiguity";
			}
		}
		if(ans1){
			string ans;
			for(int i=0;i<l;i++)ans.push_back(ans1->a%10+'0'),ans1->a/=10;
			for(int i=0;i<r;i++)ans.push_back(ans2->a%10+'0'),ans2->a/=10;
			return ans;
		}
		else return"Liar";
	}
};
		return ans;
		}
		else return"Liar";
	}
};
e(sx,sy,tx,ty)?"YES":"NO";
	}
};
	return solve(sx,sy,tx,ty)?"YES":"NO";
	}
};
k(i,j,0,0,0,-2,2,0);
				for(int z=1;z<3;z++)for(int c=0;c<2;c++)link(i,j,z,i,j,0,1,c*(field[i][j]=='C'));
			}
			cnt++;
		}
		int f,c;mincost(f,c);
		return f==cnt?c:-1;
	}
};
s2(i+1))return 1; // 每条边内同类点必须偶数个 
			if(!t)select[id[i]]=0;undo(old);
		}
		return 0;
	}
	string getPossibility(vector <int> labels){
		for(int i=ecnt=top=opcnt=0;i<labels.size();i++) // 预处理边集
			if(labels[i]==-1)list[top++]=i;
			else for(int j=i+1;j<labels.size();j++)if(labels[i]==labels[j])ex[ecnt]=i,ey[ecnt++]=j;
		init(labels.size());
		for(int i=0;i<ecnt;i++)
			for(int j=i+1;j<ecnt;j++)if(cross(i,j)&&!link(i,j,1))return"IMPOSSIBLE"; // 输入的不合法则退出
		if(top<=12)return dfs1(0)?"POSSIBLE":"IMPOSSIBLE"; // 搜索1
		for(int j=0;j<ecnt;j++)id[j]=find_fa(j),type[j]=find_val(j),select[j]=0;
		init(labels.size());link(0,labels.size(),0);
		return dfs2(0)?"POSSIBLE":"IMPOSSIBLE"; // 搜索2
	}
};
1ll*P*(p-l)%MOD;
				}
			}
			ans=(ans+P)%MOD;
		}
		return ans; 
	}
};

			for(edge*e=first[i];e;e=e->next){
				if(siz[e->to]==n-k)dfs2(e->to,i,dep+1,ff*fv[e->to]%MOD);
			}
		}
		else for(edge*e=first[i];e;e=e->next)
			if(e->to!=fa)dfs2(e->to,i,dep+1,ff);
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
