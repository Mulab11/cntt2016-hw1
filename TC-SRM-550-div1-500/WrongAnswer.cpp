#include <vector>
#include <string>
using namespace std;
class CheckerExpansion{
public:
	vector <string> resultAfter(long long t, long long x0, long long y0, int w, int h){
		t=t*2-2; // 限制所有点x+y<=t
		vector<string> ans;
		for(int i=0;i<h;i++){
			string str="";
			for(int j=0;j<w;j++){
				long long x=x0+j,y=y0+h-1-i;
				int k=50;
				if(x+y<=t&&y<=x){
					bool f=1;
					while(x+y>2){ // 递归求出(x,y)位置的符号
						while(x+y<=(1ll<<k)-2)--k;
						if(y>=1ll<<k-1)x-=1ll<<k-1,y-=1ll<<k-1; // 位于上方三角形
						else if(x-y>=1ll<<k)x-=1ll<<k; // 位于右下方三角形
						else{f=0;break;} // 位于中间三角形
					}
					// 递归边界
					if(!f)str+='.';
					else if(!x&&!y)str+='A';
					else if(x==1&&!y)str+='.';
					else str+='B';
				}
				else str+='.';
			}
			ans.push_back(str);
		}
		return ans;
	}
};
