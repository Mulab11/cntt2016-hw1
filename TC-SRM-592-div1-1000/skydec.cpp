#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define eps (1e-3)
using namespace std;
typedef long long LL;
typedef double DB;
const DB pi=acos(-1.0);
const int N=35;
struct com{
    DB re,im;
    inline com(DB _re=0.0,DB _im=0.0){re=_re;im=_im;}
};
inline com operator +(const com &a,const com &b){return com(a.re+b.re,a.im+b.im);}
inline com operator -(const com &a,const com &b){return com(a.re-b.re,a.im-b.im);}
inline com operator *(const com &a,const com &b){return com(a.re*b.re-a.im*b.im,a.re*b.im+a.im*b.re);}
inline com operator /(const com &a,const DB &b){return com(a.re/b,a.im/b);}

com ou(int n,int i){
    return com(cos(2*pi*i/n),sin(2*pi*i/n));
}
com res[N];
inline void FFT(com *A,int n,int f){
    rep(i,0,n-1)res[i]=com(0,0);
    rep(i,0,n-1)rep(j,0,n-1){
        res[i]=res[i]+A[j]*ou(n,(f*(i*j%n)+n)%n);
    }

    if(f==-1){
        rep(i,0,n-1)res[i].re/=n;
    }
}
int a[N];
int b[N],n;
int c[N];
com A[N],B[N];
bool kaigen(com X,com &R1,com &R2){
    DB gt=X.re*X.re+X.im*X.im;

    gt=sqrt(gt);

    DB A2=(gt+X.re)/2;

    DB B2=(gt-X.re)/2;

    if(A2<(-eps))return 0;
    if(B2<(-eps))return 0;

    A2=sqrt(A2);
    B2=sqrt(B2);

    if(fabs(A2*B2*2-X.im)<1e-5){
        R1=com(A2,B2);
        R2=com(-A2,-B2);
    }
    else{
        R1=com(A2,-B2);
        R2=com(-A2,B2);
    }

    return 1;
}
vector<int> Main(){
    b[0]=1000000000;

    rep(i,0,n-1)A[i]=com(a[i],0);
    FFT(A,n,1);
    rep(i,0,n-1)A[i]=res[i];
    rep(S,0,(1<<(n/2+1))-1){
        rep(j,0,n/2){
            com X,Y;
            if(!kaigen(A[j],X,Y)){
                vector<int> ans;ans.clear();ans.push_back(-1);return ans;
            }

            if(S&(1<<j))B[j]=B[(n-j)%n]=X;
            else B[j]=B[(n-j)%n]=Y;
        }

        FFT(B,n,-1);
        rep(i,0,n-1)B[i]=res[i];
        bool flag=1;

        rep(i,0,n-1)if((fabs(B[i].im)<eps)&&(!(B[i].re<(-eps)))){
            int xx=(int)(B[i].re+0.001);
            if(fabs(xx-B[i].re)<eps){c[i]=xx;}
            else flag=0;
        }
        else flag=0;


        if(!flag)continue;



        rep(i,0,n-1)if(c[i]!=b[i]){
            if(c[i]<b[i])break;
            else{
                flag=0;break;
            }
        }



        if(!flag)continue;
        rep(i,0,n-1)b[i]=c[i];
    }
    if(b[0]>10000000){
        vector<int> ans;ans.clear();ans.push_back(-1);return ans;
    }
    vector<int> ans;ans.clear();
    rep(i,0,n-1)ans.push_back(b[i]);
    return ans;
}
class SplittingFoxes2{
public:
    vector<int> getPattern(vector <int> amount){
        n=amount.size();
        rep(i,0,n-1){
            a[i]=amount[i];
        }
        return Main();
    }
}gt;