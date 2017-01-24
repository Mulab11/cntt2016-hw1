#include <vector>
#include <string>
#define MOD 1000000007
using namespace std;
class WolfInZooDivOne{
public:
	int n,m,left[310],right[310];
	void read(vector<string>a,int*b,int&s){
		for(int i=s=*b=0;i<a.size();i++)
			for(int j=0;j<a[i].length();j++)a[i][j]==' '?b[++s]=0:b[s]=b[s]*10+a[i][j]-'0';
		s++;
	}
	int r[310],f[310][310];
	int calc(int i,int j){
		if(i==n)return 1;
		if(f[i][j=i>j?i:j])return f[i][j]-1;
		f[i][j]=(calc(i+1,j)+calc(i==j?i+1:j,r[i]))%MOD;
		return f[i][j]++;
	}
	int count(int N, vector <string> L, vector <string> R){
		n=N;read(L,left,m);read(R,right,m);
		for(int i=0;i<n;i++)r[i]=i+1;
		for(int i=0;i<m;i++)right[i]>=r[left[i]]?r[left[i]]=right[i]+1:1;
		for(int i=1;i<n;i++)r[i-1]>r[i]?r[i]=r[i-1]:1;
		return calc(0,0);
	}
};
return calc(0,0);
	}
};
-1,it.z-1});
					if(it.x+1<R)push(t,(item){it.x+1,it.y,it.z-1});
					if(it.y+1<C)push(t,(item){it.x,it.y+1,it.z-1});
				}
				else if(field[it.x][it.y]=='v')tot++,it.z+=dist,push(t,it);
			}
			s++;tot%2?e=1:1;
		}
		int S=0;
		for(e?--s:1;s--;)S=(S*2+1)%MOD;
		return S;
	}
};
2+1)%MOD;
		return S;
	}
};
r(int j=0;j<m;j++)if(target[i][j]=='#'){
				u=i&&target[i-1][j]=='#';d=i<n-1&&target[i+1][j]=='#';
				l=j&&target[i][j-1]=='#';r=j<m-1&&target[i][j+1]=='#';
				// 割0表示属于V集，上下不同的格子有1代价
				link(0,P(i,j),U+!u+!d);
				if(u)link(P(i-1,j),P(i,j),1);
				if(d)link(P(i+1,j),P(i,j),1);
				// 割1表示属于H集，左右不同的格子有1代价
				link(P(i,j),1,U+!l+!r);
				if(l)link(P(i,j),P(i,j-1),1);
				if(r)link(P(i,j),P(i,j+1),1);
				s++;
			}
		}
		return (maxflow()-U*s)/2; // 答案=端点数/2
	}
};

		return (maxflow()-U*s)/2; // 答案=端点数/2
	}
};
;
	}
};
堑谝恍星倚胁畈淮笫弊狶->D
				else if(ty==C-1)sx==tx?is_line[sx]=1:left_in[sx]=right_out[tx]=1; // L->R，可能在同一行
				else if(!tx)ans++,left_out[sx]=1; // L->U，转为U->L
				else left_in[sx]=1; // L->D
			}
			else if(sy==C-1){
				if(!ty)right_in[sx]=left_out[tx]=1; // R->L
				else if(ty==C-1)right_in[sx]=1,!sx||tx>sx+1?right_out[tx]=1:1; // R->R，非第一行且行差不大时转为R->D
				else right_in[sx]=1; // R->D
			}
			else if(!sx){
				ans++;
				if(!ty)left_out[tx]=1; // U->L
				else if(ty==C-1)right_out[tx]=1; // U->R
			}
			else if(!ty)left_in[tx]=1; // D->L，转为L->D
			else if(ty==C-1)right_in[tx]=1; // D->R，转为R->D
		}
		return ans+dfs(0,R,0,0);
	}
};
1; // D->R，转为R->D
		}
		return ans+dfs(0,R,0,0);
	}
};
j),type[j]=find_val(j),select[j]=0;
		init(labels.size());link(0,labels.size(),0);
		return dfs2(0)?"POSSIBLE":"IMPOSSIBLE"; // 鎼滅储2
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
