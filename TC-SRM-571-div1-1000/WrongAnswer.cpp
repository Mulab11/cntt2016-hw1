#include <vector>
#include <string>
#include <cmath>
using namespace std;
class CandyOnDisk{
public:
	int n,x[55],y[55],r[55];
	long double L[55],R[55],d[55][55];
	bool vis[55];
	long double dist(int x1,int y1,int x2,int y2){
		long long dx=x1-x2,dy=y1-y2;
		return sqrtl(dx*dx+dy*dy);
	}
	long double max(long double a,long double b){return a>b?a:b;}
	long double min(long double a,long double b){return a<b?a:b;}
	bool upd(int i,int j){
		bool c=0;
		long double ll=max(d[i][j]-r[i],0),rr=min(r[j],d[i][j]+r[i]);
		if(!vis[j])c=vis[j]=1,L[j]=ll,R[j]=rr;
		else{
			if(ll<L[j])c=1,L[j]=ll;
			if(rr>R[j])c=1,R[j]=rr;
		}	
		return c;
	}
	bool solve(int sx,int sy,int tx,int ty){
		if(sx==tx&&sy==ty)return 1;
		bool changed=0;
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)d[i][j]=dist(x[i],y[i],x[j],y[j]);
		for(int i=0;i<n;i++)
			if(dist(x[i],y[i],sx,sy)<=r[i])vis[i]=1,L[i]=R[i]=dist(x[i],y[i],sx,sy),changed=1;
		while(changed)
			for(int i=changed=0;i<n;i++)if(vis[i])
				for(int j=0;j<n;j++)if(j!=i)
					if(R[i]+r[j]>=d[i][j]&&L[i]-r[j]<=d[i][j])changed|=upd(i,j),changed|=upd(j,i);
		for(int i=0;i<n;i++)if(vis[i]&&dist(x[i],y[i],tx,ty)>=L[i]&&dist(x[i],y[i],tx,ty)<=R[i])return 1;
		return 0;
	}
	string ableToAchieve(vector <int> x, vector <int> y, vector <int> r, int sx, int sy, int tx, int ty){
		for(int i=0;i<x.size();i++){
			bool find=0;
			for(int j=0;j<n&&!find;j++)if(this->x[j]==x[i]&&this->y[j]==y[i])find=1,r[i]>this->r[j]?this->r[j]=r[i]:1;
			if(!find)this->x[n]=x[i],this->y[n]=y[i],this->r[n++]=r[i];
		}
		return solve(sx,sy,tx,ty)?"YES":"NO";
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
