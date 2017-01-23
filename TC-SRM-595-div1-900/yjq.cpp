#include<bits/stdc++.h>
using namespace std;typedef double _float;const int MAXN=110;int X[MAXN][2];class Constellation{public:_float Abs(_float a){return a>=0?a:-a;}_float expectation(vector<int>x,vector<int>y,vector<int>prob){_float ans=0;int n=x.size();for(int i=0;i<n;i++)X[i][0]=x[i]-210,X[i][1]=y[i]-210;for(int i=0;i<n;i++)for(int j=0;j<n;j++){if(i==j)continue;int dir=-1;if(X[i][0]<X[j][0])dir=1;if(X[i][0]==X[j][0]&&X[i][1]>X[j][1])dir=1;_float posi=((_float)(prob[i]*prob[j]))/1.0e6;_float a,b,c;if(X[i][0]==X[j][0])a=1,b=0,c=-X[i][0];else a=((_float)(X[i][1]-X[j][1]))/(X[i][0]-X[j][0]),b=-1,c=X[i][1]-X[i][0]*a;_float o=c;for(int k=0;k<n;k++){if(k==i||k==j)continue;_float nowX=a*X[k][0]+b*X[k][1]+c;bool flag=true;if(abs(nowX)<=1.0e-10){if(b!=0){if((X[k][0]-X[i][0])*(X[k][0]-X[j][0])<0)flag=false;}else if((X[k][1]-X[i][1])*(X[k][1]-X[j][1])<0)flag=false;}else if((nowX*o*dir)<0)flag=false;if(!flag)posi*=(1000-prob[k]),posi/=1000;}_float nans=posi*dir;_float l1,l2,l3;l1=sqrt(X[i][0]*X[i][0]+X[i][1]*X[i][1]);l2=sqrt(X[j][0]*X[j][0]+X[j][1]*X[j][1]);l3=sqrt((X[j][0]-X[i][0])*(X[j][0]-X[i][0])+(X[j][1]-X[i][1])*(X[j][1]-X[i][1]));_float p=(l1+l2+l3)/2;_float area=sqrt(p*(p-l1)*(p-l2)*(p-l3));ans+=area*nans;}return ans;}} sol ;

vector<int> a, b, c ; 

int x[] = {0 ,0, 1}, y[] = {0, 1, 0}, z[] = {500, 500, 500} ; 
int main() { 
		for (int i = 0; i < 3; i ++) a.push_back(x[i]), b.push_back(y[i]), c.push_back(z[i]) ; 
		printf("%.10f\n", sol.expectation(a, b, c)) ;
}

