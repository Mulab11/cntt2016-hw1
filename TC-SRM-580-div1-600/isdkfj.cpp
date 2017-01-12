#include <bits/stdc++.h>

using namespace std;

string lianjie(vector<string>a){
	string ret="";
	for(int i=0;i<a.size();++i)ret+=a[i];
	return ret;
}

class ShoutterDiv1 {
public:
	int count(vector <string> s1000, vector <string> s100, vector <string> s10, vector <string> s1, vector <string> t1000, vector <string> t100, vector <string> t10, vector <string> t1) {
		vector<pair<int,int> >a;
		string S1000,S100,S10,S1,T1000,T100,T10,T1;
		S1000=lianjie(s1000);
		S100=lianjie(s100);
		S10=lianjie(s10);
		S1=lianjie(s1);
		T1000=lianjie(t1000);
		T100=lianjie(t100);
		T10=lianjie(t10);
		T1=lianjie(t1);
		int n=S1000.size();
		for(int i=0;i<n;++i){
			int x=(S1000[i]-48)*1000+(S100[i]-48)*100+(S10[i]-48)*10+S1[i]-48;
			int y=(T1000[i]-48)*1000+(T100[i]-48)*100+(T10[i]-48)*10+T1[i]-48;
			a.push_back(make_pair(x,y));//把数据转换成正常的格式 
		}
		sort(a.begin(),a.end());
		int minr=99999999,ret=0;
		for(int i=0;i<n;++i)minr=min(minr,a[i].second);//从右端点最靠左的区间开始合并 
		for(int i=0;i<n;++i){
			int r=minr,j=0;
			while(j<n){
				if(a[i].first<=r)r=max(r,a[i].second);//当前区间被合并 
				int tmp=r;
				while(j<n&&a[j].first<=tmp){
					r=max(r,a[j].second);
					++j;//扩展一次 
				}
				if(j==n)break;
				if(r==tmp)return -1;//还没到但是无法扩展 
				++ret;
			}
		}
		return ret;
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
