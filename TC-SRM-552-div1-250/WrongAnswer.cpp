#define min(a,b) ((a)<(b)?(a):(b))
class FoxPaintingBalls{
public:
	long long theMax(long long R, long long G, long long B, int N){
		long long x=N*(N+1ll)/2,y=x/3;
		return y?min(min(R/y,G/y),min(B/y,(R+G+B)/x)):R+G+B;
	}
};
	struct item{
		bool type;int siz,sum;
		bool operator<(const item&it)const{return sum<it.sum||(sum==it.sum&&type<it.type);}
	}items[1<<21];
	int make(int L,int R,bool ty,int l){ // 求{a[L],...,a[R-1]}的所有子集和并从小到大排序
		if(L==R){items[l]=(item){ty,0,ty?Max:0};return l+1;}
		int m=make(L,R-1,ty,l),r=m;
		for(int i=l;i<m;i++)items[r++]=(item){ty,items[i].siz+1,items[i].sum+(ty?-a[R-1]:a[R-1])};
		inplace_merge(items+l,items+m,items+r);
		return r;
	}
	long long inv(int a,int p){return a==1?1:(1+p*(a-inv(p%a,a)))/a%p;}
	int calc(int k){ // 已确定k个点只和-1相连的生成树个数
		int A[50][50],n=N+M-1;
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)A[i][j]=i==j?i<k?M:i<N?n-k:n:(i<k?j>=N:j<k?i>=N:1)*(MOD-1);
		// 矩阵树定理
		int det=1;
		for(int i=0,j,t;i<n;i++){
			for(j=i;j<n&&!A[j][i];j++);
			if(j==n)return 0;
			if(j>i){
				det=(MOD-det)%MOD;
				for(int k=i;k<n;k++)t=A[i][k],A[i][k]=A[j][k],A[j][k]=t;
			}
			det=1ll*det*A[i][i]%MOD;
			long long I=inv(MOD-A[i][i],MOD),r;
			for(j=i+1;j<n;j++)if(A[j][i]){
				r=A[j][i]*I%MOD;
				for(int k=i;k<n;k++)A[j][k]=(A[j][k]+A[i][k]*r)%MOD;
			}
		}
		return det;
	}
	int countTrees(vector <int> sweetness, int maxSweetness){
		Max=maxSweetness;
		for(int i=0;i<sweetness.size();i++)sweetness[i]>=0?a[N++]=sweetness[i]:++M;
		int L=make(0,N>>1,0,0),R=make(N>>1,N,1,L); // meet-in-the middle
		inplace_merge(items,items+L,items+R);
		int cur[50]={0},s[50]={0}; // s[i]:大小为i的truly sweet子集个数
		for(int i=0;i<R;i++){ // 求所有的s[i]
			if(items[i].type)
				for(int j=N>>1;j>=0;j--)(s[j+items[i].siz]+=cur[j])%=MOD;
			else cur[items[i].siz]++;
		}
		int C[50]={1},x[50],ans=0;
		for(int i=0;i<=N;i++){ // 容斥原理计算恰有i个点和至少一个非-1相连的方案数
			x[i]=calc(N-i);
			for(int j=i;j;j--)(C[j]+=C[j-1])%=MOD;
			for(int j=0;j<i;j++)x[i]=(x[i]+(MOD-C[j])*1ll*x[j])%MOD;
			ans=(ans+x[i]*1ll*s[i])%MOD;
		}
		return ans;
	}
};
��足条件就退出
		if(!rest){ // 枚举完所有点，判断是否可行
			init_ways();
			int w=ways((1<<N)-1);
			return w>=Min&&w<=Max;
		}
		int cnt=0;
		// i放新的一层
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
