#include <string>
using namespace std;
class Stamp{
public:
	int f[60];
	bool vis[128];
	void cmin(int&a,int b){b<a?a=b:1;}
	int getMinimumCost(string desiredColor, int stampCost, int pushCost){
		int n=desiredColor.length(),ans=1<<30;
		for(int L=1;L<=n;L++){
			f[0]=L*stampCost;
			for(int i=1;i<=n;i++){
				f[i]=1<<30;
				vis['R']=vis['G']=vis['B']=0;
				for(int j=i-1,s=0;j>=0;j--){
					if(desiredColor[j]!='*'&&!vis[desiredColor[j]])s++,vis[desiredColor[j]]=1;
					if(s==2)break;
					if(i-j>=L)cmin(f[i],f[j]+(i-j+L-1)/L*pushCost);
				}
			}
			if(f[n]<ans)ans=f[n];
		}
		return ans;
	}
};
