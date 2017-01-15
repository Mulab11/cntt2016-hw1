#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
using namespace std;
typedef long long LL;
struct po{
    int x,y;
    inline po(int _x=0,int _y=0){x=_x;y=_y;}
};
inline po operator +(const po &a,const po &b){return po(a.x+b.x,a.y+b.y);}
inline po operator -(const po &a,const po &b){return po(a.x-b.x,a.y-b.y);}
inline LL operator *(const po &a,const po &b){return a.x*1ll*b.y-a.y*1ll*b.x;}
vector<po> gtw;
map<pii,bool> hav;
bool add(po x){

    if(hav[pii(x.x,x.y)])return 1;
    if(gtw.size()>200006)return 0;
    if(gtw.size()<2){
        gtw.push_back(x);
        return 1;
    }
    gtw.push_back(x);
    return ((x-gtw[0])*(gtw[1]-gtw[0]))==0;
}
double calc(double x,po A,po B){
    return A.y+((B.y-A.y)*1./(B.x-A.x))*(x-A.x);
}
class ConvexPolygonGame{
public:
    string winner(vector <int> X, vector <int> Y){
        int l=100002;int r=-100002;
        int n=X.size();
        rep(i,0,n-1)hav[pii(X[i],Y[i])]=1;
        rep(i,0,X.size()-1){
            l=min(l,X[i]);
            r=max(r,X[i]);
        }
        rep(xx,l,r){
            int ma=-(100005);
            int mi=100005;

            rep(i,0,n-1){
                po A=po(X[i],Y[i]);
                po B=po(X[(i+1)%n],Y[(i+1)%n]);

                if(min(A.x,B.x)<=xx&&xx<=max(A.x,B.x)){
                    if(A.x==B.x)continue;

                    double val=calc(xx,A,B);

                    if(val<min(A.y,B.y) || val>max(A.y,B.y))continue;

                    if(A.x<=B.x){
                        mi=ceil(val);
                    }
                    else{
                        ma=floor(val);
                    }
                }
            }

            rep(i,mi,ma)if(!add(po(xx,i)))
                return "Masha";
        }
        return "Petya";
    }
}gt;