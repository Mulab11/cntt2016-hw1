#include <bits/stdc++.h>

using namespace std;

const int mo=1000000007;
int f[305][305],p[305][305];
inline void ad(int&x,int y){
	if((x+=y)>=mo)x-=mo;
}

class WolfInZooDivOne {
public:
	int count(int N, vector <string> L, vector <string> R) {
		string sb;
		vector<int>ll,rr;
		for(int i=0;i<L.size();++i)sb+=L[i];
		stringstream sl(sb);int x;
		while(sl>>x)ll.push_back(x+1);
		sb="";
		for(int i=0;i<R.size();++i)sb+=R[i];
		stringstream sr(sb);
		while(sr>>x)rr.push_back(x+1);//读入 
		f[0][0]=1;
		memset(p,0x3f,sizeof p);
		for(int i=1;i<=N;++i)
			for(int j=i+1;j<=N;++j)
				for(int k=0;k<ll.size();++k)
				if(ll[k]<=i&&j<=rr[k]&&ll[k]<p[i][j])p[i][j]=ll[k];
				//预处理出包含i,j的区间的左端点最小值 
		int ans=0;
		for(int i=0;i<=N;++i)//当前点 
			for(int j=0;j<=i;++j)//上一个点 
			if(f[i][j]){
				ad(ans,f[i][j]);
				for(int k=i+1;k<=N;++k)//下一个点 
				if(p[i][k]>j)ad(f[k][i],f[i][j]);
			}
		return ans;
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
