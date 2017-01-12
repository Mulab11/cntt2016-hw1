#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
int r[305],m,px[305],py[305],n;

class Ear {
public:
	long long getCount(vector <string> redX, vector <string> blueX, vector <string> blueY) {
		string a,b,c;
		for(int i=0;i<redX.size();++i)a+=redX[i];
		for(int i=0;i<blueX.size();++i)b+=blueX[i];
		for(int i=0;i<blueY.size();++i)c+=blueY[i];
		stringstream sa(a),sb(b),sc(c);
		int x;
		while(sa>>x)r[++m]=x;
		while(sb>>x)px[++n]=x;
		n=0;while(sc>>x)py[++n]=x;//黑科技读入 
		sort(r+1,r+m+1);//排序 
		LL ret=0;
		for(int i=1;i<=n;++i)//P
			for(int j=1;j<=n;++j)//Q
			if(py[i]>py[j]){
				for(int k=1,cnt=0;k<=m;++k){//B
					if(r[k]>=px[j])break;
					int l=max(px[i],px[j]),lc,ld;
					double jd=-1.0*py[i]*(px[i]-px[j])/(py[i]-py[j])+px[i];//与x轴交点 
					l=max(l,int(jd+0.000001));
					lc=upper_bound(r+1,r+m+1,px[j])-r;
					ld=upper_bound(r+1,r+m+1,l)-r;//lc<=xc<=xd&&ld<=xd 
					ret+=1ll*cnt*(ld+m)*(m-ld+1)/2;
					ret-=1ll*cnt*lc*(m-ld+1);//统计答案 
					cnt+=r[k]<px[i]&&r[k]<jd-0.000001;//点A是否合法 
				}
			}
			return ret;
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
