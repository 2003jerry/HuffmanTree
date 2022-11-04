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
	char code[10] = {'*'};//��һ��д����ÿһ���ַ������ĳ���
	int cnt;//��Ϊ��Ҫ����
	char type;


};
//��̬����洢����������������Ҫ���ٵĴ�С��2n-1
class HuffmanTree {
public:
	void initialization(int n,int* arr1,char *b);//�����ַ������Խ���ո������������
	void encoding(string s,int n);
	void decoding(string s);
	//HuffmanTree(string i);//����д�����������Ͷ����˹��������ĳ��ȣ���Ȼû�а취���ٿռ�
	CodeType* codetype;
	string finalAnswer;
private:
	TreeNode* arr;//��������Ź��������
	string input;//�������ĵȴ�������ַ���
	string outcome;//�����õ��Ľ��
	int length = 0;
	
	
};
void HuffmanTree::initialization(int n,int* arr1,char*b) {
	 arr = new TreeNode[2*n];//�������ڱ�,Ϊʲô�����ʼ�����ᱨ��
	 codetype = new CodeType[n+1];//��Ϊ��һλ���õ��ǿո�ı���
	
	for (int i = 1;i <= n;i++) {
		arr[i].weight= arr1[i - 1];
		arr[i].name = b[i - 1];
	}
	//��ʼ��HuffmanTree
	//�ҵ���ǰ����Сֵ�ʹ�Сֵ��Ȼ���±����������ǵĶ����ϲ�
	for (int i = n+1;i < 2*n ;i++) {//ÿ���������������̶���ѭ��������
		int min = 99999;//��Сֵ
		int cmin = 99999;//��Сֵ
		int m = 0;
		int c = 0;//�ֱ�����Сֵ�ʹ�Сֵ���±�
		for (int j = 1;j < i;j++) {
			if (arr[j].parent == -1) {//û�б����ù��Ż�ʹ��
				if (arr[j].weight < min)
				{
					c = m;
					cmin = min;//��Сֵ��ˢ��
					min = arr[j].weight;
					m = j;//��Сֵָ�����
				}
				else if (arr[j].weight < cmin)
				{
					cmin = arr[j].weight;
					c = j;//��Сֵָ�����
				}
				

			}
		}//���ҵ���һ������Ҫ�Ĵ�Сֵ����Сֵָ�룬Ȼ��ʼ�ϲ���
		arr[i].lchild = c;
		arr[i].rchild = m;
		arr[c].parent = arr[m].parent = i;
		arr[i].weight = arr[c].weight + arr[m].weight;

	}
	/*for (int i = 1;i <= 2 * n - 1;i++) {
		cout << arr[i].name<<" " << arr[i].weight<<" " << arr[i].parent <<" " << arr[i].lchild <<" " << arr[i].rchild;
	}*/
	//�����ȫ�������������Ƿ񽨺�
	length = 2 * n - 1;
	fstream outFile("e:\\happy",ios::out|ios::binary);//�ļ���������Բ���
	if (!outFile) {
		cerr << "open file error!";
	}
	for (int i = 1;i <= 2 * n - 1;i++) {
		outFile.write((char*)&arr[i], sizeof(TreeNode));
	}
	outFile.close();
};
void HuffmanTree::encoding(string s,int n) {//�����string����Ҫ���������
	//����һ��������Ҫ�Ƚ������ֵ�д������Ȼ����ܱ���
	/*�����ѽ��õĻ����������粻���ڴ棬����ļ�hfmTree�ж��룩��
		���ļ�ToBeTran�е����Ľ��б��룬Ȼ�󽫽�������ļ�CodeFile�С�*/
	int i, p,c;
	
	
	for( i=1;i<=n;i++){//��Ҫ������ô���
		    CodeType ct;//������д��ǰ�ߣ���ʾ�Ƕ�ͬһ����������д��ݲ������������ˢ�£��ͺܳ���
		    int start = 0;
			c = i;//��˼�ǽ����еĵ�һ���ַ����±��c�ݴ�
			ct.type = arr[c].name;//�����type�Ķ�Ӧ��name����
			p = arr[c].parent;//�ҵõ�c�±��ַ���˫�ף��ǵ�ַ����p�ݴ�
			ct.cnt = n;//��cnt��ֵ��ʼ��ΪN��������������(S->code[])���ַ��ı���ʱ,���Ŵ�
			while (p != -1)//Ҫ����i���ַ����������ҵ�����˫��Ϊֹ
			{
				if (arr[p].lchild == c)//��i���ַ���˫��p�����ӣ�S.code[]�д桮0����
					ct.code[start++] = '0';
				else//����桮1��
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
	//�Ѿ�ȷ������ÿ���ַ���Ӧ�ı���ֵ�����ڿ�ʼ���б��룬���Ҵ��뵽�ļ���
	cout << "���ڶ��ļ����б��룬Դ�ļ��ǣ�";
	cout << s<<endl;
	string answer="";
	for (int i = 0;i < s.length();i++) {
		for (int j = 1;j <= n;j++) {
			if (s[i] == codetype[j].type) {
				answer += codetype[j].code;
			}
				}
	}
	cout << "����������" << answer << endl;;
	finalAnswer = answer;
};
void HuffmanTree::decoding(string s) {
	/*���루Decoding���������ѽ��õĻ����������ļ�CodeFile�еĴ���������룬��������ļ�Textfile�С�*/
	cout << "���ڶ��ļ���������" << endl;
	int head = 0;
	for (int i = 1;i <= length;i++) {
		if (arr[i].parent == -1) {
			head = i;
		}
	}//�ҵ�ͷָ������λ��
	int p = head;
	string answer = "";
	for (int j = 0;j < s.length();j++) {
		if (s[j] == '0') {
			p = arr[p].lchild;//�����0��������
		}else if (s[j] == '1') {
			p = arr[p].rchild;
		}
	    if (arr[p].name != '#') {
			answer += arr[p].name;
			p = head;
		}

	}
	cout << "��������������ԭ���ǣ�" << s<<endl;
	cout << "����֮������:" << answer;

};
//HuffmanTree::HuffmanTree(string i) {
//};
//��Ҫдһ��������ʹ���⼸������
void menu(char *a,int*b) {
	HuffmanTree myTree;
	cout << "***��ӭʹ�ù�������ϵͳ***" << endl;
	cout << "***��ѡ������Ҫ���Ĳ���***" << endl;
	cout << "**����һ����ʼ��**********" << endl;
	cout << "**���ܶ�������************" << endl;
	cout << "**����һ������**********" << endl;
	cout << "��0�˳�����" << endl;
	int choice=0;
	bool ifWhile=1;
	while (ifWhile) {
		cout << "��������ѡ��" << endl;
		cin >> choice;
		string s = "aabbbc";
		switch (choice) {
		case 1:
			myTree.initialization(27, b, a);//�����и�bug���Ҳ�֪�����ȷ��������ַ�������
			break;
		case 2:
			myTree.encoding("THIS PROGRAME  IS  MY  FAVORITE", 27);//bugͬ��
			break;
		case 3:
			myTree.decoding(myTree.finalAnswer);
			break;
		case 0:
			ifWhile = 0;
			break;
		}
		
	}
   
	cout << "�����������ӭ�´��ٴ�ʹ�ñ�����" << endl;


}
int main() {
	//ʡȥ�˶���Ĳ���ֱ��ʹ������
	char a[27] = { ' ','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	int b[27] = { 186,64,13,22,32,103,21,15,47,57,1,5,32,20,57,63,15,1,48,51,80,23,8,18,1,16,1 };
	menu(a, b);
	return 0;
}