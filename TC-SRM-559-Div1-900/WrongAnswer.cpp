#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
class CircusTents{
public:
	double PI;
	vector<int>X,Y,R;
	struct item{
		double pos;int add;
		bool operator<(const item&it)const{return pos<it.pos;}
	}items[210],*iter;
	void ins(double l,double r){
		while(l<0)l+=2*PI,r+=2*PI;
		while(l>=2*PI)l-=2*PI,r-=2*PI;
		*(iter++)=(item){l,1};
		if(r<2*PI)*(iter++)=(item){r,-1};
		else *(iter++)=(item){2*PI,-1},*(iter++)=(item){0,1},*(iter++)=(item){r-2*PI,-1};
	}
	bool check(double M){
		iter=items;
		*(iter++)=(item){0,0};
		*(iter++)=(item){2*PI,0};
		for(int i=1;i<X.size();i++){
			double D=sqrt((X[i]-X[0])*(X[i]-X[0])+(Y[i]-Y[0])*(Y[i]-Y[0]));
			if(M<=D-R[0]-R[i])continue;
			double L=sqrt(D*D-R[0]*R[0]),a=acos(R[0]/D);
			if(M>=L-R[i]+R[0]*(PI-a))return 0;
			double t=atan2(Y[i]-Y[0],X[i]-X[0]);
			if(M<L-R[i])a=acos((R[0]*R[0]+D*D-(M+R[i])*(M+R[i]))/(2*R[0]*D));
			else a+=(M-L+R[i])/R[0];
			ins(t-a,t+a);
		}
		std::sort(items,iter);
		int tot=0;
		for(item*it=items;it<iter-1;it++){
			tot+=it->add;
			if(!tot&&(it+1)->pos>it->pos+1e-14)return 1;
		}
		return 0;
	}
	double findMaximumDistance(vector <int> x, vector <int> y, vector <int> r){
		PI=acos(-1);X=x;Y=y;R=r;
		double left=0,right=80000,mid;
		for(int t=0;t<60;t++){
			mid=(left+right)/2;
			if(check(mid))left=mid;
			else right=mid;
		}
		return left;
	}
};
