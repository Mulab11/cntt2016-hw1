//============================================================================
// Author       : Sun YaoFeng
//============================================================================

#include<string>
#include<cstdlib>
#include<iostream>
using namespace std;
int vis[100];
inline bool dis(int l,int r,int pos,int &mx){
    int v = min(abs(pos-l),abs(pos-r))-1;
    if(v < mx) {mx = v; return 1;}
    return 0;
}
const int inf = ~0u>>2;
class ColorfulChocolates{
    public : int maximumSpread(string ch, int ms){
        int n = ch.size(), ans = 0;
        for(int i=0;i<26;i++){	//枚举颜色
            char x = 'A'+i;
            bool flag = 0;
            int l,r, v = 0;
            for(int i=0;i<n;i++) {	//枚举每一格
                if(ch[i]==x) {
                    if(!flag) l = i, flag = 1;
                }
                //cout<<"i: "<<i<<" "<<l<<endl;
                int value =0;
                // block
                if(flag && (i == n-1 || ch[i+1]!=x)){
                //    cout<<"l: "<<l<<" "<<r<<endl;
                    flag = 0; r = i;
                    int tp = ms;
                    for(int i=0;i<n;i++) vis[i] = 0;
                    value = r-l+1;
                    while(1){	
                        int mx = inf,s=-1;
                        for(int j=0;j<n;j++)	//判断，取最值
                            if(j < l || j> r)
                                if(!vis[j]&&ch[j]==x && dis(l,r,j,mx)) {
                                //    cout<<j<<" ";
                                    s = j;
                                }
                        if(s==-1) break;
                        if(mx > tp) break;
                        tp -= mx; vis[s] = 1;
                        if(s > r) r ++; else l--;
                        value ++;
            //    cout<<s<<" "<<mx<<" "<<tp<<endl;
                    }
            //    cout<<l<<" "<<r<<" "<<value<<endl;
                }
                if(value > v) v = value;
            }
        //    cout<<x<<" "<<v<<endl;
            if(ans<v) ans = v;	//更新答案
        }
        return ans;
    }
};