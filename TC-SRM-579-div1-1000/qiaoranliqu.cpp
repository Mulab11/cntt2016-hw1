#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>

#define N 51

using namespace std;

int i,j,m,n,p,k,t,a,b,c;
double f[N][N][N][N];
class RockPaperScissors{
        public:
		double bestScore(vector<int> A,vector<int> B,vector<int> C)
		{
			    n=A.size();
			   for (i=1;i<=n;++i) //令f_{i,a,b,c}为出现{a,b,c}个三种手势且i依旧没有使用过的期望. 
			   {
			   	      f[i][0][0][0]=1.;
			   	       for (t=1;t<=n;++t) //考虑枚举每个骰子,然后考虑其是否会出现在最终的答案里 
			   	         for (m=t;m>=0;--m)
			   	           for (a=0;a<=m;++a) 
			   	             for (b=0;a+b<=m;++b)
			   	             {
			   	             	   c=m-a-b;  //枚举一个状态,然后计算出骰子t在和不在的概率,如果在,还要乘上它掷出每种手势的概率来加入答案 
			   	             	   double sum=0.,gai=1.*m/t;
			   	             	   if (a) sum+=f[i][a-1][b][c]*A[t-1]/300.;
			   	             	   if (b) sum+=f[i][a][b-1][c]*B[t-1]/300.;
			   	             	   if (c) sum+=f[i][a][b][c-1]*C[t-1]/300.;
			   	             	   f[i][a][b][c]*=(1-gai);
								   if (i!=t) f[i][a][b][c]+=sum*gai; 
			   	             }
			   }
			   double ans=0;
			   for (a=0;a<n;++a) //预处理出上述期望后,我们可以单独的对每种局面中使用三种手势计算出一个期望的胜率,在三个胜率中取一个最大值累加即可. 
			     for (b=0;a+b<n;++b)
			       for (c=0;a+b+c<n;++c)
			       {
			       	     double SA=0,SB=0,SC=0;
			       	     for (i=1;i<=n;++i) 
			       	     {
			       	     	  double gg=f[i][a][b][c]/(n-a-b-c);
			       	     	  SA+=gg*A[i-1]/300.;
			       	     	  SB+=gg*B[i-1]/300.;
							  SC+=gg*C[i-1]/300.; 
			       	     }
			       	     ans+=max(3*SA+SB,max(3*SB+SC,3*SC+SA));
				   }
		  return ans;
	    }
}E;
int main()
{
	  vector<int> A,B,C;
	  A.push_back(100); A.push_back(100); A.push_back(100);
	  B.push_back(100); B.push_back(100); B.push_back(100);
	  C.push_back(100); C.push_back(100); C.push_back(100);
	  printf("%.10lf\n",E.bestScore(A,B,C));
}
