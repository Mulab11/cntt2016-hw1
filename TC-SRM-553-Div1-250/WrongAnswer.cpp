#include <vector>
using namespace std;
class Suminator{
public:
	long long S[100];
	long long run(vector<int> prog){ // 模拟程序
		int top=*S=0;
		for(int i=0;i<prog.size();i++){
			if(prog[i])S[++top]=prog[i];
			else{
				long long a=S[top?top--:top];
				a+=S[top?top--:top];
				S[++top]=a;
			}
		}
		return S[top];
	}
	int findMissing(vector <int> program, int wantedResult){
		int i=0;for(;program[i]!=-1;i++);
		// 情况1：输入0可行
		program[i]=0;
		if(run(program)==wantedResult)return 0; 
		// 情况2：输入0不可行，需输入正整数x
		program[i]=1;
		long long a=run(program),b;
		if(a==wantedResult)return 1;
		program[i]=2;
		if(a==run(program))return -1; // 答案和输入的数x无关
		b=1+wantedResult-a;
		return b>0?b:-1; // 答案和输入的数x有关，一定是x+c的形式（c为常数）
	}
};
