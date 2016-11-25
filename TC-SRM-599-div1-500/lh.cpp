#include<cmath>
#include<cstdio>
#include<string>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const double eps=1e-10;

struct sav{
	int a,b,c;
	sav(int x=0,int y=0,int z=0):a(x),b(y),c(z){};
	bool operator < (const sav &x)const{
		return c<x.c;
	}
};

class FindPolygons{
	sav use[200000];
	int tot;
	bool filter(double a){
		if (a>eps) return true;
		else if (a<-eps) return true;
		else return false;
	}
	double sqr(double a){return a*a;}
	public:
		double minimumPolygon(int L){
			bool fl=false;
			double ans=1e100;
			int t=L/2;
			tot=0;
			for (int i=1;i<=t;++i)
			for (int j=1;j<=t;++j){
				int tmp=sqrt(i*i+j*j);
				if (!filter(sqrt(i*i+j*j)-tmp)){
					if (tmp<=t)
					use[tot++]=sav(i,j,tmp);
				}
				if (!filter(i+j+sqrt(i*i+j*j)-L)){
					if (!fl) fl=true;
					ans=min(ans,sqrt(i*i+j*j)-min(i,j));
				}
			}
			sort(use,use+tot);
			for (int i=0;i<tot;++i){
				for (int j=i;j<tot;++j){
					if (use[j].c+use[i].c>=L) break;
					double tmp=sqrt(sqr(use[i].a-use[j].a)+sqr(use[i].b-use[j].b));
					if (use[i].a*use[j].b!=use[i].b*use[j].a) if (!filter((int)tmp-tmp)){
						if (tmp+use[i].c+use[j].c==L){
							if (!fl) fl=true;
							ans=min(ans,(double)max({use[i].c,use[j].c,(int)tmp})-min({use[i].c,use[j].c,(int)tmp}));
//							printf("%d %d %d  %d %d %d   %d  %lf\n",use[i].a,use[i].b,use[i].c,use[j].a,use[j].b,use[j].c,(int)tmp,ans);
						}
					}
					tmp=sqrt(sqr(use[i].a-use[j].a)+sqr(use[i].b+use[j].b));
					if (!filter((int)tmp-tmp)){
						if (tmp+use[i].c+use[j].c==L){
							if (!fl) fl=true;
							ans=min(ans,(double)max({use[i].c,use[j].c,(int)tmp})-min({use[i].c,use[j].c,(int)tmp}));
							
						}
					}
				}
			}
			if (fl) return ans;
			if (L==2) return -1.0;
			if (~L&1){
				int tmp=L>>1;
				if (tmp&1){
					ans=1;
					fl=true;
				}
				else{
					ans=0;
					fl=true;
				}
			}
			if (fl) return ans;
			else return -1.0;
		}
};
