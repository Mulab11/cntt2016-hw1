#include<cstdio>
#include<algorithm>
#include<cstring>
#include<string>

using namespace std;

#define N 8
const int Mo=(int)1e9+9;
long long f[N][N][1<<N][1<<N],i,j,k,l;
void jia(long long &x,long long y) { x+=y; if (x>=Mo) x-=Mo; } 
class StringPath{
	  public:
	  	int countBoards(int n,int m,string A,string B)
	  	{
	  		  if (A[0]!=B[0]) return 0;
			  int Maxn=1<<m; 
	  		  f[0][0][1<<(m-1)][1<<(m-1)]=1;
	  		  for (i=0;i<n;++i)
	  		  {
	  		      for (j=0;j<m-1;++j)
	  		        for (k=0;k<Maxn;++k)
	  		          for (l=0;l<Maxn;++l)
	  		             if (f[i][j][k][l])
	  		             {
	  		             	   int cnt1=(k&(1<<(m-1)))+(k&1),cnt2=(l&(1<<(m-1)))+(l&1);
	  		             	   if (A[i+j+1]==B[i+j+1])
							   {
							   	      if (cnt1&&cnt2)
							   	      jia(f[i][j+1][(k>>1)|(1<<(m-1))][(l>>1)|(1<<(m-1))],f[i][j][k][l]);
							   	      else if (cnt1)
							   	      jia(f[i][j+1][(k>>1)|(1<<(m-1))][l>>1],f[i][j][k][l]);
									  else if (cnt2)
									  jia(f[i][j+1][k>>1][(l>>1)|(1<<(m-1))],f[i][j][k][l]);
									  else jia(f[i][j+1][k>>1][l>>1],f[i][j][k][l]);
									  jia(f[i][j+1][k>>1][l>>1],1ll*f[i][j][k][l]*25%Mo); 
						       }
						       else 
						       {
                                      if (cnt1)
							   	      jia(f[i][j+1][(k>>1)|(1<<(m-1))][l>>1],f[i][j][k][l]);
							   	      else jia(f[i][j+1][k>>1][l>>1],f[i][j][k][l]);
									  if (cnt2)
									  jia(f[i][j+1][k>>1][(l>>1)|(1<<(m-1))],f[i][j][k][l]);
							   	      else jia(f[i][j+1][k>>1][l>>1],f[i][j][k][l]);
									  jia(f[i][j+1][k>>1][l>>1],1ll*f[i][j][k][l]*24%Mo);
							   }
	  		             }
	  		      j=m-1;
	  		       if(i<n-1)
					  for (k=0;k<Maxn;++k)
					    for (l=0;l<Maxn;++l)
						   if (f[i][j][k][l])
						   {
						   	    int cnt1=k&1,cnt2=l&1;
						   	    if (A[i+1]==B[i+1])
							   {
							   	      if (cnt1&&cnt2)
							   	      jia(f[i+1][0][(k>>1)|(1<<(m-1))][(l>>1)|(1<<(m-1))],f[i][j][k][l]);
							   	      else if (cnt1)
							   	      jia(f[i+1][0][(k>>1)|(1<<(m-1))][l>>1],f[i][j][k][l]);
									  else if (cnt2)
									  jia(f[i+1][0][k>>1][(l>>1)|(1<<(m-1))],f[i][j][k][l]);
									  else jia(f[i+1][0][k>>1][l>>1],f[i][j][k][l]);
									  jia(f[i+1][0][k>>1][l>>1],1ll*f[i][j][k][l]*25%Mo); 
						       }
						       else 
						       {
                                      if (cnt1)
							   	      jia(f[i+1][0][(k>>1)|(1<<(m-1))][l>>1],f[i][j][k][l]);
							   	      else jia(f[i+1][0][k>>1][l>>1],f[i][j][k][l]);
									  if (cnt2)
									  jia(f[i+1][0][k>>1][(l>>1)|(1<<(m-1))],f[i][j][k][l]);
							   	      else jia(f[i+1][0][k>>1][l>>1],f[i][j][k][l]);
									  jia(f[i+1][0][k>>1][l>>1],1ll*f[i][j][k][l]*24%Mo);
							   }
					       }
	  	        }
	  	        long long ans=0;
	  	        for (i=0;i<Maxn;++i)
	  	          for (j=0;j<Maxn;++j)
	  	            if ((i&(1<<(m-1)))&&(j&(1<<(m-1))))
					    jia(ans,f[n-1][m-1][i][j]);
				return (int)ans;
		}
}A;
int main()
{
   string s="ABBBBCBBBBA",s1="ABBBBBBBBBA";
   printf("%d\n",A.countBoards(5,7,s,s1));
}
