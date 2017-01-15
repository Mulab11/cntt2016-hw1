#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<set>
#include<map>
#include<vector>
#define pii pair<int,int>
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
typedef long long LL;
typedef double db;
const int N=55;
int n;
int is[N];bool has[N];
pii a[N];
class NextAndPrev{
    public:
    int getMinimum(int Add, int Minus, string start, string goal){
        if(start==goal)return 0;
        rep(i,0,goal.size()-1)has[goal[i]-'a']=1;
        int gg=0;
        rep(i,0,25)gg+=has[i];
        //判断非法情况
        if(gg==26)return -1;
        
        memset(is,-1,sizeof is);
        rep(i,0,start.length()-1){
            //判断非法情况
            if(is[start[i]-'a']!=-1){
                if(is[start[i]-'a']!=goal[i]-'a')return -1;
            }
            else{
                is[start[i]-'a']=goal[i]-'a';
            }
        }
        rep(i,0,25)if(is[i]!=-1){
            a[++n]=pair<int,int>(i,is[i]);
        }
        sort(a+1,a+1+n);
        int ans=1e9;
        //枚举整体往右移动的幅度为step
        //可以证明移动最多2*n次
        rep(step,0,2*n){
            bool ok=1;
            rep(i,1,n-1)if(a[i].second>a[i+1].second)ok=0;
            //计算贡献
            if(ok){
                rep(st,-2,2){
                    rep(i,1,n)a[i].second+=st*26;
                    int ret=0;
                    rep(i,1,n){
                        int j=i;
                        int low=min(a[i].first,a[i].second);
                        int high=max(a[i].second,a[i].first);
                        while(j<n&&a[j+1].second==a[i].second){
                            ++j;
                            if(a[j].first<low)low=a[j].first;
                            if(a[j].first>high)high=a[j].first;
                        }
                        
                        ret+=(high-a[i].second)*Minus+(a[i].second-low)*Add;
                        i=j;
                    }
                    if(ret<ans)ans=ret;
                    rep(i,1,n)a[i].second-=st*26;
                }
            }
            //注意最后a[1].first还要+26
            a[1].first+=26;
            sort(a+1,a+1+n);
        }
        if(ans>=(1e9))ans=-1;
        return ans;
    }
};


