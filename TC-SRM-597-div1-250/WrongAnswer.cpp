#include <string>
using namespace std;
class LittleElephantAndString{
public:
	int getNumber(string A, string B){
		int l=A.length(),cnt[26]={0};
		for(int i=0;i<l;i++)cnt[A[i]-'A']++,cnt[B[i]-'A']--;
		for(int i=0;i<26;i++)if(cnt[i])return-1;
		for(int i=l-1,j=l-1;j>=0;j--){
			while(i>=0&&A[i]!=B[j])--i;
			if(i--<0)return j+1;
		}
		return 0;
	}
};
