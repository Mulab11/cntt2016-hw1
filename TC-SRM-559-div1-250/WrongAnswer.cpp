class HyperKnight{
public:
	long long countCells(int a, int b, int numRows, int numColumns, int k){
		if(a<b){int t=a;a=b;b=t;}
		if(k==2)return 4ll*b*b;
		if(k==3)return 8ll*b*(a-b);
		if(k==4)return 2ll*b*(numRows+numColumns-4ll*a)+4ll*(a-b)*(a-b);
		if(k==6)return 2ll*(a-b)*(numRows+numColumns-4ll*a);
		if(k==8)return (numRows-2ll*a)*(numColumns-2ll*a);
		return 0;
	}
};
,0,ne-1,first[b]};first[b]=ne++;
	}
	int Q[810],D[810];
	int dfs(int i,int c){
		if(i==1||!c)return c;
		int flow=0,f;
		for(edge*&e=cur[i];e;e=e->next)if(e->cap&&D[e->to]==D[i]-1&&(f=dfs(e->to,e->cap<c?e->cap:c))){
			flow+=f;e->cap-=f;e->rev->cap+=f;
			if(!(c-=f))return flow;
		}
		return flow;
	}
	int maxflow(){
		for(int f=0;;f+=dfs(0,INF)){
			memset(D,0,sizeof(D));
			memcpy(cur,first,sizeof(cur));
			for(int head=0,tail=Q[0]=D[1]=1;head<tail;head++)
				for(edge*e=first[Q[head]];e;e=e->next)
					if(e->rev->cap&&!D[e->to])D[Q[tail++]=e->to]=D[Q[head]]+1;
			if(!D[0])return f;
		}
	}
	int vx[4]={-1,0,0,1},vy[4]={0,-1,1,0};
	int dec(char c){return c<='9'?c-'0':c>='a'?c-'a'+10:c-'A'+36;}
	int maxScore(vector <string> cost, vector <string> benefit){
		int R=cost.size(),C=cost[0].length(),ans=U*R*C;ne=E;
		for(int i=0;i<R;i++){
			for(int j=0;j<C;j++){
				if((i+j)%2){
					link(0,P(i,j),U),link(P(i,j),1,U+dec(cost[i][j])); // 奇数格割0表示不选，割1表示选
					for(int d=0,x,y;d<4;d++)
						if((x=i+vx[d])>=0&&x<R&&(y=j+vy[d])>=0&&y<C)link(P(x,y),Q(i,j),INF);
					ans+=dec(benefit[i][j]),link(Q(i,j),P(i,j),dec(benefit[i][j])); // 默认得到利益，如果没被占据则取消利益
				}
				else{
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
