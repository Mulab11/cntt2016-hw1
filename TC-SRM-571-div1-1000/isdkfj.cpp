#include <bits/stdc++.h>

using namespace std;

int n,flag[55][55];
double ll[55],rr[55];
map<pair<int,int>,int>mp;

class CandyOnDisk {
public:
	string ableToAchieve(vector <int> x, vector <int> y, vector <int> r, int sx, int sy, int tx, int ty) {
		for(int i=0;i<x.size();++i){
			pair<int,int>tmp=make_pair(x[i],y[i]);
			if(mp.find(tmp)!=mp.end())mp[tmp]=max(mp[tmp],r[i]);//把同一个圆心的圆变成半径最大的 
			else mp[tmp]=r[i];
		}
		x.clear();y.clear();r.clear();
		for(map<pair<int,int>,int>::iterator it=mp.begin();it!=mp.end();++it){
			x.push_back(it->first.first);
			y.push_back(it->first.second);
			r.push_back(it->second);
		}
		n=x.size();
		for(int i=0;i<n;++i)ll[i]=1e15,rr[i]=-1e15;
		for(int i=0;i<n;++i){//初始化 
			double d=sqrt(1.*(x[i]-sx)*(x[i]-sx)+1.*(y[i]-sy)*(y[i]-sy));
			if(d<=r[i])ll[i]=d-1e-9,rr[i]=d+1e-9;//精度 
		}
		while(1){
			int work=0;
			for(int i=0;i<n;++i)
				for(int j=0;j<n;++j)
				if(i!=j&&!flag[i][j]){
					double d=sqrt(1.*(x[i]-x[j])*(x[i]-x[j])+1.*(y[i]-y[j])*(y[i]-y[j]));
					if(rr[i]<d-r[j]||ll[i]>d+r[j])continue;//不相交 
					work=1;flag[i][j]=1;
					ll[i]=min(ll[i],max(0.0,d-r[j]));
					rr[i]=max(rr[i],min(1.*r[i],d+r[j]));//j更新i 
					ll[j]=min(ll[j],max(0.0,d+r[i]));
					rr[j]=max(rr[j],min(1.*r[j],d+r[i]));//i更新j 
				}
			if(!work)break;
		}
		for(int i=0;i<n;++i){
			double d=sqrt(1.*(x[i]-tx)*(x[i]-tx)+1.*(y[i]-ty)*(y[i]-ty));
			if(ll[i]<d&&d<rr[i])return "YES";
		}
		if(sx==tx&&sy==ty)return "YES";//起点和终点相同，要特判 
		return "NO";
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
