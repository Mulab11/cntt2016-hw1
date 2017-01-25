#include <vector>
#include <string>
using namespace std;
struct node{node*fa,*ch[26];}nodes[2510],*newnode,*root;
class UndoHistory{
public:
	int minPresses(vector <string> lines){
		root=nodes;newnode=nodes+1;
		int ans=lines.size();
		node*cur=root;
		for(int i=0;i<lines.size();i++){
			node*it=root,*x=it;
			for(int j=0;j<lines[i].length();j++){
				if(!it->ch[lines[i][j]-'a'])newnode->fa=it,it=it->ch[lines[i][j]-'a']=newnode++,ans++;
				else it=x=x->ch[lines[i][j]-'a'];
			}
			if(cur==x->fa)ans++;
			else if(cur!=x)ans+=2;
			cur=it;
		}
		return ans;
	}
};
