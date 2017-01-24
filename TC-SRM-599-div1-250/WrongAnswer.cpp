class BigFatInteger{
public:
	int minOperations(int A, int B){
		int a=0,b=0;
		for(int i=2;i*i<=A;i++)if(A%i==0){
			int t=0;a++;
			while(A%i==0)A/=i,t++;
			if(t>b)b=t;
		}
		if(A>1)a++,b<1?b=1:1;
		b*=B;
		for(int i=0;;i++)if(b<=(1<<i))return a+i;
	}
};
a+i;
	}
};
ã
	void cmin(int&a,int b){b<a?a=b:1;}
	void init(int i,int fa){ // Ô¤´¦ÀíupºÍch
		for(int e=0,j;e<to[i].size();e++)
			if((j=to[i][e])!=fa)ch[i].push_back(j),init(j,i);
		down[i]=!ch[i].size()||ch[i].size()==1&&down[ch[i][0]];
	}
	void dfs(int i){ // ¼ÆËãdownºÍf
		for(int c=0,j;c<ch[i].size();c++){
			j=ch[i][c];
			if(i)up[j]=up[i]&&ch[i].size()==1;
			else up[j]=ch[i].size()==1||ch[i].size()==2&&down[ch[i][!c]];
			dfs(j);
		}
		if(down[i]){f[i]=1;return;}
		f[i]=1<<30;
		// ±ê¼Çi£¬Ôòi×î¶à1¸ö×ÓÊ÷²»Ñ¡£¬ÇÒ±ØÐëÊÇÁ´
		int fmax=0,fsum=0;
		for(int c=0;c<ch[i].size();fsum+=f[ch[i][c++]])if(down[ch[i][c]])cmin(fmax,-f[ch[i][c]]);
		cmin(f[i],fsum+(ch[i].size()<1)); // ËùÓÐ×ÓÊ÷¶¼Ñ¡
		cmin(f[i],fsum+fmax+(ch[i].size()<2)); // 1¸ö×ÓÊ÷²»Ñ¡
	}
	int minimalBeacons(vector <string> linked){
		if((N=linked.size())==1)return 0;
		for(int i=0;i<N;i++)for(int j=0;j<N;j++)if(linked[i][j]=='Y')to[i].push_back(j);
		init(0,-1);dfs(0);
		int ans=1<<30;
		for(int i=1;i<N;i++)if(up[i]){ // Ã¶¾ÙÊ÷µÄ¸ùi£¬iµÄÃ¿¸ö×ÓÊ÷¶¼±ØÐëÈ¡
			// Èç¹ûi²»Ñ¡£¬ÒªÇóÖÁÉÙ2¸ö×ÓÊ÷
			int sum=ch[i].size()<2;
			for(int c=0;c<ch[i].size();c++)sum+=f[ch[i][c]];
			cmin(ans,sum);
		}
		// ¸ùÎª0£¬×î¶àÒ»¸ö×ÓÊ÷²»Ñ¡£¬ÇÒ±ØÐëÊÇÁ´ 
		int sum=0,fmax=0;
		for(int c=0;c<ch[0].size();sum+=f[ch[0][c++]])if(down[ch[0][c]])cmin(fmax,-f[ch[0][c]]);
		cmin(ans,sum+(ch[0].size()<2));
		cmin(ans,sum+fmax+(ch[0].size()<3));
		return ans;
	}
};
fmax+(ch[0].size()<3));
		return ans;
	}
};
fo[i][j])==' '?add(s),l=0:s[l++]=x;
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
