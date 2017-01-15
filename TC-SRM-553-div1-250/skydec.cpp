#include<stdio.h>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<cmath>
#include<ctime>
#include<set>
#include<map>
#include<string>
#include<vector>
#include<bitset>
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define SZ(x) ((int)((x).size()))
#define rep(i,j,k) for(int i=(int)j;i<=(int)k;i++)
#define per(i,j,k) for(int i=(int)j;i>=(int)k;i--)
using namespace std;
typedef long long LL;
typedef double DB;
const DB pi=acos(-1.0);
int n;
class Suminator{
    public:
    int findMissing(vector<int> a, int res){
        vector<bitset<55> >q;
        q.clear();
        n=a.size();
        bitset<55> aa;
        aa.reset();
        rep(i,1,100)q.pb(aa);
        //way1
        //显然我们可以用一个bitset表示这个数是栈里哪些数的和
        //先考虑-1填0的情况
        rep(i,0,n-1){
            if(a[i]<=0){
                if(q.size()>1){
                    //弹栈求和时，直接把两个bitset or一下
                    bitset<55> gt=q.back();
                    q.pop_back();
                    bitset<55> gt2=q.back();
                    q.pop_back();
                    //当一个数被求和后，肯定被弹出，所以一个数不会出现在多个bitset里
                    //所以or一下是对的
                    q.push_back(gt|gt2);
                }
            }
            else{
                bitset<55> gt;
                gt.reset();
                gt[i]=1;
                q.push_back(gt);
            }
        }
        LL ret=0;
        bitset<55> gt=q.back();
        //由于假设-1是0，所以求和一下看是否和答案一样
        rep(i,0,n-1)if(gt[i])ret+=1ll*a[i];
        if(ret==res)return 0;
        
        
        //way2
        //假设-1是一个大于0的数
        //和上一个讨论一样先求答案
        q.clear();
        rep(i,0,n-1){
            if(a[i]==0){
                if(q.size()>1){
                    //bitset or 一下
                    bitset<55> gt=q.back();
                    q.pop_back();
                    bitset<55> gt2=q.back();
                    q.pop_back();
                    q.push_back(gt|gt2);
                }
            }
            else{
                bitset<55> gt;
                gt.reset();
                gt[i]=1;
                q.push_back(gt);
            }
        }
        gt=q.back();
        //这里最后要check一下
        int fu=-1;
        rep(i,0,n-1)if(a[i]!=-1){
            if(gt[i]){
                //先减去所有确定的值
                res-=a[i];
                if(res<=0)return -1;
            }
        }
        else fu=i;
        
        //然后-1填的就是剩余的值，注意要特判剩余的值是不是0，因为这题里是不能填0的
        if(res==0&&(gt[fu]))return 1;
        if(res>0&&(!gt[fu]))return -1;
        return res;
    }
}gt;




