// BEGIN CUT HERE

// END CUT HERE
#line 5 "TheBrickTowerHardDivOne.cpp"

#include <bits/stdc++.h>
#define ll long long
using namespace std;
#define P 1234567891

const int maxm=233;

struct matrix{
	int x,y;
	int a[maxm][maxm];
	matrix(){}
	matrix(int _x,int _y):x(_x),y(_y){memset(a,0,sizeof(a));}
	matrix(int _x){
		x=y=_x;
		memset(a,0,sizeof(a));
		for (int i=1;i<=_x;++i) a[i][i]=1;
	}
	void print(){
		for (int i=1;i<=x;++i,puts(""))
			for (int j=1;j<=y;++j)
				printf("%d",a[i][j]);
	}
};
 
inline matrix operator *(matrix a,matrix b){
	if (a.y!=b.x) swap(a,b);
	matrix ret=matrix(a.x,b.y);
	int z=a.y;
	for (int i=1;i<=ret.x;++i)
		for (int j=1;j<=ret.y;++j){
			ret.a[i][j]=0;
			for (int k=1;k<=z;++k)
				ret.a[i][j]=(1LL*a.a[i][k]*b.a[k][j]+ret.a[i][j])%P;
		}
	return ret;
}
 
matrix fast_pow(matrix x,ll y){
	matrix ret=matrix(x.x);
	while (y){
		if (y&1) ret=ret*x;
		y/=2;
		x=x*x;
	}
	return ret;
}

const int maxstamp=25;

class TheBrickTowerHardDivOne {
	matrix A,B;
	int cost[maxstamp];
	int id[1][2][3][4],stamp;
	int f[maxstamp];
	int msk[maxstamp][4];
	bool eq[4][4];
	int m;
	public:
	int find(int C, int K, long long H){
		int stamp=0;
		for (int i[4]={0,0,0,0};i[0]<1;++i[0])
			for (i[1]=0;i[1]<2;++i[1])for (i[2]=0;i[2]<3;++i[2])for (i[3]=0;i[3]<4;++i[3]){
				bool valid=1;
				for (int k=0;valid&&k<4;++k) if(i[i[k]]!=i[k]) valid=0;
				if (!valid) continue;
				id[i[0]][i[1]][i[2]][i[3]]=++stamp;
				cost[stamp]=(i[0]==i[1])+(i[0]==i[2])+(i[1]==i[3])+(i[2]==i[3]);
				f[stamp]=0;
				for (int k=0;k<4;++k) msk[stamp][k]=i[k],f[stamp]+=(i[k]==k);
			}
		m=stamp*(K+1)+1;
		A=matrix(m,m);
		B=matrix(m,1);
		for (int i=1;i<=stamp;++i)if (cost[i]<=K){
			int _left=C,_count=1;
			for (int k=f[i];k;--k)
				_count=1LL*_count*(_left--)%P;
//			printf("%d :  ",i);
//			for (int k=0;k<4;++k) printf("%d ",msk[i][k]);
//			printf(" cost:%d  _count:%d\n",cost[i],_count);
			B.a[stamp*cost[i]+i][1]=_count;
			for (int j=1;j<=stamp;++j)
				for (int b=(1<<(f[i]*f[j]))-1;b>=0;--b){
//					printf("%d %d\n",j,b);
					bool debug=0;
//					if (i==9&&j==9&&b==6) debug=1;
					int tmp=b;
					int count_1=0;
					for (int k0=0;k0<4;++k0)if (msk[i][k0]==k0)
						for (int k1=0;k1<4;++k1)if (msk[j][k1]==k1){
							eq[k0][k1]=tmp&1;
							count_1+=(tmp&1);
							tmp>>=1;
						}
					for (int k0=0;k0<4;++k0)for (int k1=0;k1<4;++k1)
						if (msk[i][k0]!=k0||msk[j][k1]!=k1)
							eq[k0][k1]=eq[msk[i][k0]][msk[j][k1]];
					if (debug)for (int k0=0;k0<4;++k0,puts(""))for (int k1=0;k1<4;++k1)
						printf("%d",(int)eq[k0][k1]);
					bool valid=1;
					for (int k0=0;k0<4;++k0)for (int k1=0;k1<4;++k1)for (int k2=0;k2<4;++k2){
//						if (msk[i][k0]==msk[i][k1]&&(eq[k0][k2]^eq[k1][k2])){valid=0;break;}
//						if (msk[j][k1]==msk[j][k2]&&(eq[k0][k1]^eq[k0][k2])){valid=0;break;}
						if (msk[i][k0]!=msk[i][k1]&&eq[k0][k2]&&eq[k1][k2]){valid=0;break;}
						if (msk[j][k1]!=msk[j][k2]&&eq[k0][k1]&&eq[k0][k2]){valid=0;break;}
					}
					if (debug) puts(valid?"yjqakctsc":"wyzsb");
					if (!valid) continue;
					_count=1;_left=C-f[i];
					if (_left<0) continue;
					if (debug) printf("%d %d\n",_left,f[j]-count_1);
					for (int k=f[j]-count_1;k>0;--k)
						_count=1LL*_count*(_left--)%P;
					int _fee=cost[j];
					for (int k=0;k<4;++k) _fee+=eq[k][k];
					if (debug) printf("%d\n",_count);
					for (int k=0;k+_fee<=K;++k){
						A.a[stamp*(k+_fee)+j][stamp*k+i]=((ll)A.a[stamp*(k+_fee)+j][stamp*k+i]+_count)%P;
//						printf("%d %d %d\n",stamp*(k+_fee)+j,stamp*k+i,_count);
					}
				}
		}
		for (int i=1;i<=m;++i) A.a[m][i]=1;
//		A.print();
		A=fast_pow(A,H)*B;
		return A.a[m][1];
	}
};
