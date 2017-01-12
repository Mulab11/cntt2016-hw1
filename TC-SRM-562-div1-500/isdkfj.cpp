#include <bits/stdc++.h>

using namespace std;

const double pi=acos(-1);
struct info{
	int x,y;
	info(){}
	info(int x,int y):x(x),y(y){}
	info operator-(info&rhs){
		return info(x-rhs.x,y-rhs.y);
	}
}p1[555],p2[555];
double qz[555];
double cha(info&a,info&b){//叉积 
	return 1.*a.x*b.y-1.*b.x*a.y;
}
double dia(info&a,info&b){//点积 
	return 1.*a.x*b.x+1.*a.y*b.y;
}
double mo(info&a){//模长 
	return sqrt(1.*a.x*a.x+1.*a.y*a.y);
}
struct orz{
	double t1,t2;
	bool operator<(const orz&rhs)const{
		return t1<rhs.t1;
	}
}q1[555],q2[555];
int n,m;
bool work(info a,info b){
	info v=b-a;int l1=0,l2=0;
	double d;
	for(int i=1;i<=m;++i){
		info v2=p2[i]-a;
		if(cha(v2,v)>0){
			++l1;d=dia(v2,v);
			q1[l1].t1=acos(d/mo(v)/mo(v2));//角CAB 
			v2=b-p2[i];d=dia(v2,v);
			q1[l1].t2=acos(d/mo(v)/mo(v2));//角CBA 
		} else {
			++l2;d=dia(v2,v);
			q2[l2].t1=acos(d/mo(v)/mo(v2));//角DAB 
			v2=b-p2[i];d=dia(v2,v);
			q2[l2].t2=acos(d/mo(v)/mo(v2));//角DBA 
		}
	}
	sort(q1+1,q1+l1+1);//排序 
	sort(q2+1,q2+l2+1);//排序 
	qz[0]=233333;
	for(int i=1;i<=l2;++i)qz[i]=min(qz[i-1],q2[i].t2);//前缀最小值 
	for(int i=1,j=l2;i<=l1&&j>=1;++i){
		d=pi-q1[i].t1;
		while(j>=1&&q2[j].t1>d)--j;//角CAB+角DAB小于π 
		if(j==0)break;
		if(qz[j]<pi-q1[i].t2)return 1;//角CBA+角DBA小于π 
	}
	return 0;
}

class CheckerFreeness {
public:
	string isFree(vector <string> whiteX, vector <string> whiteY, vector <string> blackX, vector <string> blackY) {
		string a,b,c,d;
		for(int i=0;i<whiteX.size();++i)a+=whiteX[i];
		for(int i=0;i<whiteY.size();++i)b+=whiteY[i];
		for(int i=0;i<blackX.size();++i)c+=blackX[i];
		for(int i=0;i<blackY.size();++i)d+=blackY[i];
		stringstream sa(a),sb(b),sc(c),sd(d);
		int tmp;
		while(sa>>tmp)p1[++n].x=tmp;
		n=0;
		while(sb>>tmp)p1[++n].y=tmp;
		while(sc>>tmp)p2[++m].x=tmp;
		m=0;
		while(sd>>tmp)p2[++m].y=tmp;//读入 
		if(!n||!m)return "YES";
		for(int i=1;i<=n;++i)
			for(int j=i+1;j<=n;++j)
			if(work(p1[i],p1[j]))return "NO";
		return "YES";
	}
};


//<%:testing-code%>
//Powered by KawigiEdit 2.1.8 (beta) modified by pivanof!
