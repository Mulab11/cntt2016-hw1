#include <vector>
#include <cstring>
using namespace std;
class DrawingPointsDivOne{
public:
	vector<int>X,Y;
	int a[310][310],S[310][310];
	bool check(int M){
		memset(S,0,sizeof(S));
		for(int i=0;i<X.size();i++)
			S[X[i]+1][Y[i]+1]++,S[X[i]+1][Y[i]+M+1]--,S[X[i]+M+1][Y[i]+1]--,S[X[i]+M+1][Y[i]+M+1]++;
		for(int i=1;i<300;i++)
			for(int j=1;j<300;j++)S[i][j]+=S[i-1][j]+S[i][j-1]-S[i-1][j-1];
		for(int i=1;i<300;i++)
			for(int j=1;j<300;j++)S[i][j]=S[i-1][j]+S[i][j-1]-S[i-1][j-1]+!!S[i][j];
		for(int l=0,r=M;r<300;l++,r++)
			for(int d=0,u=M;u<300;d++,u++)if(!a[l][d]&&S[r][u]-S[r][d]-S[l][u]+S[l][d]==M*M)return 0;
		return 1;
	}
	int maxSteps(vector <int> x, vector <int> y){
		memset(a,0,sizeof(a));
		for(int i=0;i<x.size();i++)a[x[i]+=70][y[i]+=70]=1;
		X=x;Y=y;
		if(check(150))return -1;
		int left=0,right=150,mid;
		while(right-left>1){
			mid=left+right>>1;
			if(check(mid+1))left=mid;
			else right=mid;
		}
		return left;
	}
};
