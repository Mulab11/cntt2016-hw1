#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

class SweetFruits{
	static const int maxn=44,mod=1000000007;
	int num[maxn],A[maxn][maxn],n,k,lim,mul[maxn];
	int use[maxn],sum1[1<<21],pre[1<<21];
	int cnt[maxn],C[maxn][maxn];
	vector<int> val[22];
	
	long long power(long long a,int b){
		long long ret=1;
		while(b){
			if (b&1) ret=ret*a%mod;
			a=a*a%mod;
			b>>=1;
		}
		return ret;
	}
	
	int build(int tmp){
		memset(A,0,sizeof(A));
		for (int i=tmp+1;i<=n;++i)
		for (int j=tmp+1;j<=n;++j) A[i][j]=mod-1;
		for (int i=1;i<=tmp;++i)
		for (int j=k+1;j<=n;++j) A[i][j]=A[j][i]=mod-1;
		for (int i=1;i<=tmp;++i) A[i][i]=n-k;
		for (int i=tmp+1;i<=k;++i) A[i][i]=n-tmp-1;
		for (int i=k+1;i<=n;++i) A[i][i]=n-1;
//		for (int i=1;i<=n;++i,puts(""))
//		for (int j=1;j<=n;++j) printf("%d ",A[i][j]);
		
		int ans=1;
		for (int i=1;i<n;++i){
			int j=i;
			for (;j<n;++j) if (A[j][i]) break;
			if (j==n) return 0;
			if (j!=i){
				for (int t=i;t<n;++t) swap(A[j][t],A[i][t]);
				ans=(mod-ans)%mod;
			}
//			printf("solve(%d):  %d\n",i,A[i][i]);
//			printf("power(%d,%d)=%lld\n",A[i][i],mod-2,power(A[i][i],mod-2));
			tmp=power(A[i][i],mod-2);
//			printf("tmp=%d\n",tmp);
			ans=(long long)ans*A[i][i]%mod;
			for (j=i;j<n;++j) A[i][j]=(long long)tmp*A[i][j]%mod;
//			for (int ii=1;ii<n;++ii,puts(""))
//			for (int jj=1;jj<n;++jj) printf("%d ",A[ii][jj]);
//			puts("");
			for (j=i+1;j<n;++j) if (A[j][i]){
				for (int t=i+1;t<n;++t) A[j][t]=(A[j][t]-(long long)A[i][t]*A[j][i]%mod+mod)%mod;
				A[j][i]=0;
			}
//			for (int ii=1;ii<n;++ii,puts(""))
//			for (int jj=1;jj<n;++jj) printf("%d ",A[ii][jj]);
//			puts("------------------------");
		}
		return ans;
	}
	
	int find(vector<int> &a,int top,int x){
		if (top==0) return 0;
		if (a[0]>x) return 0;
		int l=0,r=top-1,mid;
		while(l<r){
			mid=(l+r+1)/2;
			if (a[mid]>x) r=mid-1;
			else l=mid;
		}
		return l+1;
	}
	
	public:
		int countTrees(vector<int> s, int m){
			
			memset(mul,0,sizeof(mul));
			n=s.size();
			C[0][0]=1;
			for (int i=1;i<=n;++i){
				C[i][0]=1;
				for (int j=1;j<=i;++j) C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
			}
			for (int i=0;i<n;++i){
				num[i]=s[i];
				if (num[i]!=-1) use[k++]=num[i];
			}
//			cout<<build(0)<<endl;
//			return 0;
			for (int i=0;i<=k;++i) mul[i]=build(i);
			for (int i=0;k-i>i;++i) swap(mul[i],mul[k-i]);
			for (int i=1;i<=k;++i){
				for (int j=0;j<i;++j) mul[i]=(mul[i]-(long long)mul[j]*C[i][j]%mod+mod)%mod;
			}
//			for (int i=0;i<=k;++i) printf("mul[%d]=%d\n",i,mul[i]);
			int ans=0;
			int t1=(k+1)/2;
			for (int i=0;i<t1;++i) sum1[1<<i]=use[i];
			pre[0]=sum1[0]=0;
			for (int i=0;i<(1<<t1);++i){
				if (i&1) pre[i]=pre[i^1]+1;
				else pre[i]=pre[i>>1];
				int tmp=i&(-i);
				sum1[i]=sum1[tmp]+sum1[i^tmp];
				val[pre[i]].push_back(sum1[i]);
				++cnt[pre[i]];
//				if (sum1[i]<=m) ans=(ans+mul[pre[i]])%mod;
			}
//			return ans;
			for (int i=0;i<=t1;++i){
				sort(val[i].begin(),val[i].end());
//				printf("%d:",i);
//				for (int j=0;j<cnt[i];++j) printf(" %d",val[i][j]);
//				puts("");
			}
			int t2=k-t1;
			for (int i=0;i<t2;++i){
//				printf("%d\n",use[i+t1]);
				sum1[1<<i]=use[i+t1];
			}
			for (int i=0;i<(1<<t2);++i){
				int tmp=i&(-i);
				sum1[i]=sum1[tmp]+sum1[i^tmp];
				for (int j=0;j<=t1;++j){
//					int tt=find(val[j],cnt[j],m-sum2[i]);
//					printf("sum=%d,tt=%d,j=%d,pre=%d\n",sum2[i],tt,j,pre[i]);
					ans=(ans+(long long)mul[j+pre[i]]*find(val[j],cnt[j],m-sum1[i]))%mod;
//					printf("ans=%d\n",ans);
				}
			}
			return ans;
		}
};
