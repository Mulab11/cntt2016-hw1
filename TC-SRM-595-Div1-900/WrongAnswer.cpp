#include <cmath>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;
int n,dx[55],dy[55],S[55];
int dis(int i){return(dx[i]<0?-dx[i]:dx[i])+(dy[i]<0?-dy[i]:dy[i]);}
int type(int i){return dy[i]<0||!dy[i]&&dx[i]<0;}
bool chk(int i,int j){
	int d=dx[i]*dy[j]-dx[j]*dy[i];
	if(d)return d>0;
	return dx[i]*dx[j]<0||dy[i]*dy[j]<0?0:dis(i)>dis(j);
}
bool cmp(int i,int j){
	int ti=type(i),tj=type(j);
	return ti!=tj?ti<tj:chk(i,j);
}
double P[55];
class Constellation{
public:
	double expectation(vector <int> x, vector <int> y, vector <int> prob){
		double s=0,pro=1;int zcnt=0;n=x.size()-1;
		for(int i=0;i<=n;i++)P[i]=1-prob[i]*1e-3,prob[i]==1000?zcnt++:pro*=P[i];
		for(int i=0;i<=n;i++){
			for(int j=0,tot=0;j<=n;j++)dx[j]=x[j]-x[i],dy[j]=y[j]-y[i],j!=i?S[tot++]=j:0;
			sort(S,S+n,cmp);
			double p=pro;
			int z=zcnt;
			prob[i]==1000?z--:p/=P[i];
			for(int l=0,r=0;l<n;prob[S[l]]==1000?z++:p*=P[S[l]],l++){
				if(r==l)prob[S[r]]==1000?z--:p/=P[S[r]],r=(r+1)%n;
				while(r!=l&&chk(S[l],S[r]))prob[S[r]]==1000?z--:p/=P[S[r]],r=(r+1)%n;
				if(!z)s+=5e-7*prob[i]*prob[S[l]]*p*(x[i]*y[S[l]]-y[i]*x[S[l]]);
			}
		}
		return s;
	}
};
