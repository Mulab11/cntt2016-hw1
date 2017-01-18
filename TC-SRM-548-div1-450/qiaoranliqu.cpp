#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<bitset>

#define ls (t<<1)
#define rs ((t<<1)+1)
#define mid ((l+r)>>1)
#define fi first
#define se second
#define mk make_pair
#define pb push_back

#define N 55
#define M 200005
#define seed 23333
#define Mo 998244353

using namespace std;
int i,j,m,n,p,k,cnt,T,A[N*2],sz;
bitset<N*N>f[N*2][N];
struct Seg{int len,sum;}seg[N*2]; 
class KingdomAndDice{
		public:
			double newFairness(vector <int> F, vector <int> s, int X)
			{
				   n=F.size(); m=s.size();
				   for (i=0;i<n;++i) if (F[i]) //处理已经有的答案. 
				   {
				   		A[++A[0]]=F[i];
				   		for (j=0;j<m;++j)
				   			if (F[i]>s[j]) ++T;
				   }
				   else ++cnt;
				   for (i=0;i<m;++i) A[++A[0]]=s[i];
				   A[++A[0]]=-100000; A[++A[0]]=X+1; 
				   sort(A+1,A+A[0]+1); 
				   for (i=2;i<=A[0];++i) if (A[i]-A[i-1]>1) //处理在B中贡献相同的一段 
				   {
				   		sz++;
				   		seg[sz].len=A[i]-A[i-1]-1;
				   		for (j=0;j<m;++j) if (A[i-1]+1>s[j]) ++seg[sz].sum;
				   }
				   f[0][0][T]=1; //f[i][j][k]表示前i段选了j个当前概率为K/N*N的方案是否存在 
				   for (i=1;i<=sz;++i)
				   	 for (j=0;j<=min(cnt,seg[i].len);++j) 
				   	   for (k=0;j+k<=cnt;++k)
				   	   	  f[i][k+j]|=(f[i-1][k]<<(j*seg[i].sum));
				   int Ans=T;
				   for (k=0;k<N*N;++k) 
				   		if (f[sz][cnt][k]&&abs(k*2-n*n)<abs(Ans*2-n*n)) Ans=k;
				   return 1.*Ans/(n*n); 
			}
}FFT;

int main()
{
		vector<int> A,B;
		A.pb(0); A.pb(0); B.pb(5); B.pb(8);
		FFT.newFairness(A,B,47);
} 
