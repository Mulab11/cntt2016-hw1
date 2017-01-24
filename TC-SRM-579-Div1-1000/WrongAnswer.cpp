#include <vector>
using namespace std;
class RockPaperScissors{
public:
	double x[51],y[51],z[51],f[51][51][51];
	double max(double a,double b){return a>b?a:b;}
	double cost(double a,double b,double c){return max(max(3*a+b,3*b+c),3*c+a);}
	double bestScore(vector <int> rockProb, vector <int> paperProb, vector <int> scissorsProb){
		int N=rockProb.size();
		for(int i=0;i<N;i++)x[i]=rockProb[i]/300.0,y[i]=paperProb[i]/300.0,z[i]=scissorsProb[i]/300.0;
		f[0][0][0]=1;
		for(int i=1;i<=N;i++)
			for(int a=i;a>=0;a--)
				for(int b=i-a;b>=0;b--)
					for(int c=i-a-b;c>=0;c--)f[a][b][c]=((i-a-b-c)*f[a][b][c]+(a+b+c)*((a?f[a-1][b][c]*x[i-1]:0)+(b?f[a][b-1][c]*y[i-1]:0)+(c?f[a][b][c-1]*z[i-1]:0)))/i;
		double ans=0;
		for(int a=0;a<N;a++)
			for(int b=0;a+b<N;b++)
				for(int c=0;a+b+c<N;c++)ans+=cost(f[a+1][b][c]*(a+1),f[a][b+1][c]*(b+1),f[a][b][c+1]*(c+1))/(a+b+c+1);
		return ans;
	}
};
