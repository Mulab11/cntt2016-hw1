#include <vector>
#include <string>
using namespace std;
class ConvexPolygonGame{
public:
	int ymin[200010],ymax[200010],xs[200010],ys[200010];
	int fl(long long a,long long b){return a>0||a%b==0?a/b:a/b-1;}
	int ce(long long a,long long b){return a<0||a%b==0?a/b:a/b+1;}
	string winner(vector <int> X, vector <int> Y){
		int cnt=0;
		for(int i=0;i<=200000;i++)ymax[i]=-(ymin[i]=233333);
		for(int i=0;i<X.size();i++)X[i]+=100000,Y[i]+=100000;
		for(int i=0,j;j=(i+1)%X.size(),i<X.size();i++){
			if(X[i]>X[j]){
				ymax[X[i]]=Y[i]-1;ymax[X[j]]=Y[j]-1;
				for(int x=X[j]+1;x<X[i];x++)ymax[x]=Y[j]+fl((x-X[j])*1ll*(Y[i]-Y[j]),X[i]-X[j]);
			}
			else if(X[i]<X[j]){
				ymin[X[i]]=Y[i]+1;ymin[X[j]]=Y[j]+1;
				for(int x=X[i]+1;x<X[j];x++)ymin[x]=Y[i]+ce((x-X[i])*1ll*(Y[j]-Y[i]),X[j]-X[i]);
			}
		}
		for(int i=0;i<=200000&&cnt<200002;i++){
			for(int j=ymin[i];j<=ymax[i]&&cnt<200002;j++)xs[cnt]=i,ys[cnt++]=j;
		}
		if(cnt<3)return"Petya";
		if(cnt>200001)return"Masha";
		for(int i=2;i<cnt;i++)if((ys[i]-ys[0])*1ll*(xs[1]-xs[0])!=(xs[i]-xs[0])*1ll*(ys[1]-ys[0]))return"Masha";
		return"Petya";
	}
};
