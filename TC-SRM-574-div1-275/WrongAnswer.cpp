#include <string>
class TheNumberGame{
public:
	bool check(int A,int B,int K){
		for(;A;A/=10)if(A%K==B)return 1;
		return 0;
	}
	std::string determineOutcome(int A, int B){
		int C=0,K=1;
		for(int x=B;x;x/=10)C=C*10+x%10,K*=10;
		return check(A,B,K)||check(A,C,K)?"Manao wins":"Manao loses";
	}
};
s";
	}
};
i;i--)ifac[i-1]=ifac[i]*i%MOD;
		for(int i=0;i<=m;i++)C[i]=fac[m]*ifac[i]%MOD*ifac[m-i]%MOD;
	}
	int calc(vector <int> x, int m){
		int xmin=1<<30,xmax=-xmin,s=0;
		for(int i=0;i<x.size();i++)x[i]<xmin?xmin=x[i]:1,x[i]>xmax?xmax=x[i]:1;
		for(int a=xmax-m;a<=xmin+m;a++){
			int p=1;
			for(int i=0;i<x.size()&&p;i++)p=(x[i]-a+m)%2?0:p*C[x[i]-a+m>>1]%MOD;
			(s+=p)%=MOD;
		}
		return s;
	}
	int calc(vector <int> x, vector <int> y, int m){
		init(m);
		for(int i=0,a;i<x.size();i++)a=x[i]+y[i],y[i]-=x[i],x[i]=a;
		return 1ll*calc(x,m)*calc(y,m)%MOD;
	}
};
x,m)*calc(y,m)%MOD;
	}
};
NF?-1:ans;
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
