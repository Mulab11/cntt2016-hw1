#include<bits/stdc++.h>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
typedef long long LL;
const int N=250;
//向量模板
struct po{
    int x,y;
    inline po(int _x=0,int y_=0){
        x=_x;y=y_;
    }
}a[N],b[N];
int n,m;
inline LL operator *(const po &a,const po &b){return a.x*1ll*b.y-a.y*1ll*b.x;}
inline po operator -(const po &a,const po &b){return po(a.x-b.x,a.y-b.y);}
inline po operator +(const po &a,const po &b){return po(a.x+b.x,a.y+b.y);}
string Main(){
    rep(i,1,n)rep(j,i+1,n){
        //大力出奇迹！n^4出奇迹
        rep(k,1,m)if((b[k]-a[i])*(a[j]-a[i])<0)
        rep(l,1,m)if((b[l]-a[i])*(a[j]-a[i])>0){
            //枚举四个点，注意优化，可以优化枚举顺序来卡常数
            //比如这里大概除了8的常数
            if(((a[i]-b[k])*(b[l]-b[k])<0&&(a[j]-b[k])*(b[l]-b[k])>0)||((a[i]-b[k])*(b[l]-b[k])>0&&(a[j]-b[k])*(b[l]-b[k])<0))
            return "NO";
        }
    }
    return "YES";
}
class CheckerFreeness{
public:
    string isFree(vector <string> whiteX, vector <string> whiteY, vector <string> blackX, vector <string> blackY){
        //预处理，将一堆vector<string>转化成vector<int>
        //这是本题主要的难点
        string wx="";rep(i,0,whiteX.size()-1)wx=wx+whiteX[i];wx=wx+" ";
        string wy="";rep(i,0,whiteY.size()-1)wy=wy+whiteY[i];wy=wy+" ";
        string bx="";rep(i,0,blackX.size()-1)bx=bx+blackX[i];bx=bx+" ";
        string by="";rep(i,0,blackY.size()-1)by=by+blackY[i];by=by+" ";
        int now;
        //先将vector<string>串起来成为一个string，然后手动读入优化
        now=0;
        rep(i,0,wx.size()-1){
            if(wx[i]==' '){
                a[++n].x=now;
                now=0;
            }
            else{
                now=now*10+wx[i]-'0';
            }
        }
        n=0;
        rep(i,0,wy.size()-1){
            if(wy[i]==' '){
                a[++n].y=now;
                now=0;
            }
            else{
                now=now*10+wy[i]-'0';
            }
        }

        rep(i,0,bx.size()-1){
            if(bx[i]==' '){
                b[++m].x=now;
                now=0;
            }
            else{
                now=now*10+bx[i]-'0';
            }
        }
        m=0;
        rep(i,0,by.size()-1){
            if(by[i]==' '){
                b[++m].y=now;
                now=0;
            }
            else{
                now=now*10+by[i]-'0';
            }
        }

        return Main();
    }
};
