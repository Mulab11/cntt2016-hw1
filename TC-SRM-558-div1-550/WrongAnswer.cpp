#include <vector>
#include <string>
#include <algorithm>
using namespace std;
class Ear{
public:
	int R,B,rx[310],bx[310],by[310];
	void read(vector<string> s,int&n,int*a){
		n=*a=0;
		for(int i=0;i<s.size();i++)for(int j=0;j<s[i].length();j++){
			if(s[i][j]==' ')a[++n]=0;
			else a[n]=a[n]*10+s[i][j]-'0';
		}
		n++;
	}
	long long getCount(vector <string> redX, vector <string> blueX, vector <string> blueY){
		read(redX,R,rx);
		read(blueX,B,bx);
		read(blueY,B,by);
		long long ans=0;
		sort(rx,rx+R);
		for(int i=0;i<B;i++){
			int l1=std::lower_bound(rx,rx+R,bx[i])-rx,r1=rx+R-upper_bound(rx,rx+R,bx[i]),l2,r2;
			for(int j=0;j<B;j++)if(by[j]>by[i]){
				if(bx[j]>bx[i])l2=lower_bound(rx,rx+R,bx[i]-by[i]*(bx[j]-bx[i])/(by[j]-by[i]))-rx,r2=rx+R-upper_bound(rx,rx+R,bx[j]);
				else l2=lower_bound(rx,rx+R,bx[j])-rx,r2=rx+R-upper_bound(rx,rx+R,bx[i]+by[i]*(bx[i]-bx[j])/(by[j]-by[i]));
				ans+=l2*(2*l1-l2-1ll)*r2*(2*r1-r2-1ll)/4;
			}
		}
		return ans;
	}
};
