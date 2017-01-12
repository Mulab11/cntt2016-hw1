#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
const int mo=1000000009;
int work1(const vector<int>&a){//一个点 
	LL ret=1;
	for(int i=1,j=0;i<a.size();++i){
		while(a[j]<a[i])++j;
		ret=ret*j%mo;
	}
	return (int)ret;
}
int work2(vector<pair<int,int> >&a){//已知点的位置和伸出去的长度 
	sort(a.begin(),a.end());
	vector<int>b;
	b.push_back(a[0].second);
	LL ret=1;
	for(int i=1;i<a.size();++i)
	if(a[i].first==a[i-1].first)b.push_back(a[i].second);
	else {
		if(b[0])return 0;
		ret=ret*work1(b)%mo;
		b.clear();
		b.push_back(a[i].second);
	}
	if(b[0])return 0;//!!!!! 
	ret=ret*work1(b)%mo;
	return (int)ret;
}
int work3(const vector<int>&a,const vector<int>&b,const vector<int>&c,int db,int dc){//B---A---C
	if(!db)return 0;
	if(!dc)return 0;
	vector<pair<int,int> >s;
	s.push_back(make_pair(0,0));
	s.push_back(make_pair(db,0));
	s.push_back(make_pair(db+dc,0));
	for(int i=0,j,k;i<a.size();++i)
	if(c[i]-a[i]==dc){//在AB上 
		if((a[i]+b[i]-db)&1)return 0;
		k=(a[i]+b[i]-db)>>1;
		j=b[i]-k;
		if(j<0||j>db)return 0;
		s.push_back(make_pair(j,k));
	}else if(b[i]-a[i]==db){//在AC上 
		if((a[i]+c[i]-dc)&1)return 0;
		k=(a[i]+c[i]-dc)>>1;
		j=db+dc-(c[i]-k);
		if(j<db||j>db+dc)return 0;
		s.push_back(make_pair(j,k));
	}else return 0;
	return work2(s);
}
int work4(const vector<int>&a,const vector<int>&b,const vector<int>&c){
	int ret=0,p=-1,mix=2147483647;
	for(int i=0;i<a.size();++i)if(a[i]<mix)mix=a[p=i];
	if(c[p]>a[p])ret=(ret+work3(a,b,c,a[p]+b[p],c[p]-a[p]))%mo;//在AB上 
	if(b[p]>a[p])ret=(ret+work3(a,b,c,b[p]-a[p],a[p]+c[p]))%mo;//在AC上 
	ret=(ret+work3(a,b,c,abs(b[p]-a[p]),abs(c[p]-a[p])))%mo;//延长线上！！！！ 
	return ret;
}
int work5(const vector<int>&a,const vector<int>&b,const vector<int>&c,int x){//以x为中心 
	int da=a[x],db=b[x],dc=c[x];
	vector<pair<int,int> >sa,sb,sc;
	sa.push_back(make_pair(0,0));
	sb.push_back(make_pair(0,0));
	sc.push_back(make_pair(0,0));
	for(int i=0,j,k;i<a.size();++i)
	if(a[i]-b[i]==da-db){//xC上 
		if((b[i]+c[i]-db-dc)&1)return 0;
		k=(b[i]+c[i]-db-dc)>>1;
		j=c[i]-k;
		if(j<0||j>dc)return 0;
		sc.push_back(make_pair(j,k));
	}else if(a[i]-c[i]==da-dc){//xB上 
		if((a[i]+b[i]-da-db)&1)return 0;
		k=(a[i]+b[i]-da-db)>>1;
		j=b[i]-k;
		if(j<0||j>db)return 0;
		sb.push_back(make_pair(j,k));
	}else if(b[i]-c[i]==db-dc){//xA上 
		if((a[i]+c[i]-da-dc)&1)return 0;
		k=(a[i]+c[i]-da-dc)>>1;
		j=a[i]-k;
		if(j<0||j>da)return 0;
		sa.push_back(make_pair(j,k));
	}else return 0;
	LL ret=1;
	ret=ret*work2(sa)%mo;
	ret=ret*work2(sb)%mo;
	ret=ret*work2(sc)%mo;
	return ret;
}

class UnknownTree {
public:
	int getCount(vector <int> distancesA, vector <int> distancesB, vector <int> distancesC) {
		int ans=0;
		ans=(ans+work4(distancesA,distancesB,distancesC))%mo;
		ans=(ans+work4(distancesB,distancesA,distancesC))%mo;
		ans=(ans+work4(distancesC,distancesA,distancesB))%mo;
		for(int i=0;i<distancesA.size();++i)
			ans=(ans+work5(distancesA,distancesB,distancesC,i))%mo;
		return ans;
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
