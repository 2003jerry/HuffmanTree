#include<iostream>
#include<fstream>
using namespace std;
struct TreeNode {
	int lchild = -1;
	int rchild = -1;
	int parent = -1;
	char name = '#';
	int weight = 0;
};
struct CodeType {
	char code[10] = {'*'};//这一行写的是每一个字符编码后的长相
	int cnt;//因为需要倒着
	char type;


};
//静态链表存储哈夫曼树，数组需要开辟的大小是2n-1
class HuffmanTree {
public:
	void initialization(int n,int* arr1,char *b);//传入字符串可以解决空格不能输入的问题
	void encoding(string s,int n);
	void decoding(string s);
	//HuffmanTree(string i);//这种写法必须在这块就定义了哈夫曼树的长度，不然没有办法开辟空间
	CodeType* codetype;
	string finalAnswer;
private:
	TreeNode* arr;//结点数组存放哈夫曼结点
	string input;//外界输入的等待编码的字符串
	string outcome;//译码后得到的结果
	int length = 0;
	
	
};
void HuffmanTree::initialization(int n,int* arr1,char*b) {
	 arr = new TreeNode[2*n];//设置了哨兵,为什么在这初始化不会报错
	 codetype = new CodeType[n+1];//因为有一位设置的是空格的编码
	
	for (int i = 1;i <= n;i++) {
		arr[i].weight= arr1[i - 1];
		arr[i].name = b[i - 1];
	}
	//初始化HuffmanTree
	//找到当前的最小值和次小值，然后将下标是这俩哥们的东西合并
	for (int i = n+1;i < 2*n ;i++) {//每个哈夫曼树建立固定的循环次数？
		int min = 99999;//最小值
		int cmin = 99999;//次小值
		int m = 0;
		int c = 0;//分别是最小值和次小值的下标
		for (int j = 1;j < i;j++) {
			if (arr[j].parent == -1) {//没有被调用过才会使用
				if (arr[j].weight < min)
				{
					c = m;
					cmin = min;//次小值先刷新
					min = arr[j].weight;
					m = j;//最小值指针更新
				}
				else if (arr[j].weight < cmin)
				{
					cmin = arr[j].weight;
					c = j;//次小值指针更新
				}
				

			}
		}//查找到这一轮所需要的次小值和最小值指针，然后开始合并。
		arr[i].lchild = c;
		arr[i].rchild = m;
		arr[c].parent = arr[m].parent = i;
		arr[i].weight = arr[c].weight + arr[m].weight;

	}
	/*for (int i = 1;i <= 2 * n - 1;i++) {
		cout << arr[i].name<<" " << arr[i].weight<<" " << arr[i].parent <<" " << arr[i].lchild <<" " << arr[i].rchild;
	}*/
	//这段是全部输出，检查树是否建好
	length = 2 * n - 1;
	fstream outFile("e:\\happy",ios::out|ios::binary);//文件在这里可以查找
	if (!outFile) {
		cerr << "open file error!";
	}
	for (int i = 1;i <= 2 * n - 1;i++) {
		outFile.write((char*)&arr[i], sizeof(TreeNode));
	}
	outFile.close();
};
void HuffmanTree::encoding(string s,int n) {//传入的string是需要编码的内容
	//，这一个函数需要先将编码字典写出来，然后才能编码
	/*利用已建好的霍夫曼树（如不在内存，则从文件hfmTree中读入），
		对文件ToBeTran中的正文进行编码，然后将结果存入文件CodeFile中。*/
	int i, p,c;
	
	
	for( i=1;i<=n;i++){//需要编码这么多次
		    CodeType ct;//这个如果写在前边，表示是对同一个操作后进行传递操作，不会进行刷新，就很抽象
		    int start = 0;
			c = i;//意思是将树中的第一个字符的下标给c暂存
			ct.type = arr[c].name;//将这个type的对应的name输入
			p = arr[c].parent;//找得到c下标字符的双亲（是地址）给p暂存
			ct.cnt = n;//把cnt的值初始化为N，后续再用数组(S->code[])存字符的编码时,倒着存
			while (p != -1)//要将第i个字符从它自身找到它的双亲为止
			{
				if (arr[p].lchild == c)//第i个字符是双亲p的左孩子，S.code[]中存‘0’；
					ct.code[start++] = '0';
				else//否则存‘1’
					ct.code[start++] = '1';
				c = p;
				p = arr[c].parent;
			}
			//cout << start << endl;
			/*while (start - 1 != -1) {
				codetype[i].code[start-1]
			}*/
			codetype[i] = ct;
			char temp[10] = { '*' };
			int a = start;
			for (int j = 0;j < start;j++) {
				temp[j] = ct.code[a-1];
				a--;
			}	
			//cout << temp << endl;
			for (int j = 0;j < start;j++) {
				ct.code[j] = temp[j];
			}
			//ct.code = temp;
			codetype[i] = ct;
			
	}
	/*for (int i = 1;i <= n;i++) {
		cout << codetype[i].type<<codetype[i].code<<" " << endl;
	}*/
	//已经确定好了每个字符对应的编码值，现在开始进行编码，并且存入到文件中
	cout << "现在对文件进行编码，源文件是：";
	cout << s<<endl;
	string answer="";
	for (int i = 0;i < s.length();i++) {
		for (int j = 1;j <= n;j++) {
			if (s[i] == codetype[j].type) {
				answer += codetype[j].code;
			}
				}
	}
	cout << "最后编码结果是" << answer << endl;;
	finalAnswer = answer;
};
void HuffmanTree::decoding(string s) {
	/*译码（Decoding）。利用已建好的霍夫曼树将文件CodeFile中的代码进行译码，结果存入文件Textfile中。*/
	cout << "现在对文件进行译码" << endl;
	int head = 0;
	for (int i = 1;i <= length;i++) {
		if (arr[i].parent == -1) {
			head = i;
		}
	}//找到头指针所在位置
	int p = head;
	string answer = "";
	for (int j = 0;j < s.length();j++) {
		if (s[j] == '0') {
			p = arr[p].lchild;//如果是0则向左走
		}else if (s[j] == '1') {
			p = arr[p].rchild;
		}
	    if (arr[p].name != '#') {
			answer += arr[p].name;
			p = head;
		}

	}
	cout << "译码后输入的内容原来是：" << s<<endl;
	cout << "译码之后结果是:" << answer;

};
//HuffmanTree::HuffmanTree(string i) {
//};
//需要写一个界面来使用这几个方法
void menu(char *a,int*b) {
	HuffmanTree myTree;
	cout << "***欢迎使用哈夫曼树系统***" << endl;
	cout << "***请选择您需要做的操作***" << endl;
	cout << "**功能一：初始化**********" << endl;
	cout << "**功能二：编码************" << endl;
	cout << "**功能一：译码**********" << endl;
	cout << "按0退出程序" << endl;
	int choice=0;
	bool ifWhile=1;
	while (ifWhile) {
		cout << "输入您的选择" << endl;
		cin >> choice;
		string s = "aabbbc";
		switch (choice) {
		case 1:
			myTree.initialization(27, b, a);//这里有个bug即我不知道如何确定输入的字符的数量
			break;
		case 2:
			myTree.encoding("THIS PROGRAME  IS  MY  FAVORITE", 27);//bug同上
			break;
		case 3:
			myTree.decoding(myTree.finalAnswer);
			break;
		case 0:
			ifWhile = 0;
			break;
		}
		
	}
   
	cout << "程序结束，欢迎下次再次使用本程序" << endl;


}
int main() {
	//省去了读入的操作直接使用数组
	char a[27] = { ' ','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	int b[27] = { 186,64,13,22,32,103,21,15,47,57,1,5,32,20,57,63,15,1,48,51,80,23,8,18,1,16,1 };
	menu(a, b);
	return 0;
}