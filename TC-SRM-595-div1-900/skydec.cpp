#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
#include<map>
#include<vector>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
typedef long long LL;
typedef double db;
inline int cha(int x1,int y1,int x2,int y2){
    return x1*y2-x2*y1;
}
int sqr(int x,int y){return x*x+y*y;}
class Constellation{
    public:
    double expectation(vector<int>x, vector<int>y, vector<int>prob){
        long double ans=0;
        rep(i,0,x.size()-1)rep(j,0,x.size()-1)if(i^j){
            long double pro=1;
            pro*=prob[i]/1000.;
            pro*=prob[j]/1000.;
            long double p1=1;
            rep(k,0,x.size()-1){
                int bb=cha(x[k]-x[i],y[k]-y[i],x[j]-x[i],y[j]-y[i]);
                if(bb==0){
                    if(sqr(x[k]-x[i],y[k]-y[i])<sqr(x[j]-x[i],y[j]-y[i]))
                    if((x[k]-x[i])*(x[j]-x[i])+(y[k]-y[i])*(y[j]-y[i])>0){
                        p1*=(long double)(1.-(prob[k]/1000.));
                    }
                }
                else
                if(bb<0){
                    p1*=(long double)(1.-(prob[k]/1000.));
                }
            }
            ans+=pro*p1*cha(x[i],y[i],x[j],y[j]);
        }
        return (double)-ans/2.;
    }
};