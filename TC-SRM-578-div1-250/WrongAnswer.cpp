// FST:é˜Ÿåˆ—é•¿åº¦åº”å¼€50^2*101ï¼Œä¸¤æ¬¡FSTéƒ½å› é˜Ÿåˆ—é•¿åº¦å¼€å°ï¼Œç¬¬ä¸€æ¬¡åªå¼€äº†50^3ï¼Œç¬¬äºŒæ¬¡åªå¼€äº†50^2*100
#include <vector>
#include <string>
#define MOD 1000000007
using namespace std;
class GooseInZooDivOne{
public:
	struct item{int x,y,z;}Q[252510];
	bool vis[51][51][101];
	void push(int&t,item it){if(!vis[it.x][it.y][it.z])vis[it.x][it.y][it.z]=1,Q[t++]=it;}
	int count(vector <string> field, int dist){
		int R=field.size(),C=field[0].length(),tot,s=0,e=0;
		for(int x=0;x<R;x++)for(int y=0;y<C;y++)if(!vis[x][y][0]&&field[x][y]=='v'){
			Q[0]=(item){x,y,0};vis[x][y][0]=1;tot=0;
			for(int h=0,t=1;h<t;h++){
				item it=Q[h];
				if(it.z){
					push(t,(item){it.x,it.y,it.z-1});
					if(it.x)push(t,(item){it.x-1,it.y,it.z-1});
					if(it.y)push(t,(item){it.x,it.y-1,it.z-1});
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
				// ¸î0±íÊ¾ÊôÓÚV¼¯£¬ÉÏÏÂ²»Í¬µÄ¸ñ×ÓÓĞ1´ú¼Û
				link(0,P(i,j),U+!u+!d);
				if(u)link(P(i-1,j),P(i,j),1);
				if(d)link(P(i+1,j),P(i,j),1);
				// ¸î1±íÊ¾ÊôÓÚH¼¯£¬×óÓÒ²»Í¬µÄ¸ñ×ÓÓĞ1´ú¼Û
				link(P(i,j),1,U+!l+!r);
				if(l)link(P(i,j),P(i,j-1),1);
				if(r)link(P(i,j),P(i,j+1),1);
				s++;
			}
		}
		return (maxflow()-U*s)/2; // ´ğ°¸=¶ËµãÊı/2
	}
};

		return (maxflow()-U*s)/2; // ´ğ°¸=¶ËµãÊı/2
	}
};
;
	}
};
¬·ÇµÚÒ»ĞĞÇÒĞĞ²î²»´óÊ±×ªÎªL->D
				else if(ty==C-1)sx==tx?is_line[sx]=1:left_in[sx]=right_out[tx]=1; // L->R£¬¿ÉÄÜÔÚÍ¬Ò»ĞĞ
				else if(!tx)ans++,left_out[sx]=1; // L->U£¬×ªÎªU->L
				else left_in[sx]=1; // L->D
			}
			else if(sy==C-1){
				if(!ty)right_in[sx]=left_out[tx]=1; // R->L
				else if(ty==C-1)right_in[sx]=1,!sx||tx>sx+1?right_out[tx]=1:1; // R->R£¬·ÇµÚÒ»ĞĞÇÒĞĞ²î²»´óÊ±×ªÎªR->D
				else right_in[sx]=1; // R->D
			}
			else if(!sx){
				ans++;
				if(!ty)left_out[tx]=1; // U->L
				else if(ty==C-1)right_out[tx]=1; // U->R
			}
			else if(!ty)left_in[tx]=1; // D->L£¬×ªÎªL->D
			else if(ty==C-1)right_in[tx]=1; // D->R£¬×ªÎªR->D
		}
		return ans+dfs(0,R,0,0);
	}
};
1; // D->R£¬×ªÎªR->D
		}
		return ans+dfs(0,R,0,0);
	}
};
j),type[j]=find_val(j),select[j]=0;
		init(labels.size());link(0,labels.size(),0);
		return dfs2(0)?"POSSIBLE":"IMPOSSIBLE"; // æœç´¢2
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
