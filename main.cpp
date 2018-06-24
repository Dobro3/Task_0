#include "WordTree.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
	char c[MAXLENGTH];
	char* ch;
	string st;
	WordTree *tree = new WordTree();
	int k = 1;
	cout << "Entry key-value pairs, until value=0"<< endl;
	while (k > 0)
	{
		cin >> c;
		cin >> k;
		tree->AddElem(c, k);
	}
	cout << "entry value of looking key"<<endl;
	cin >> k;
	tree->ReadValue(k, c);
	
	cout << "word: " << c <<endl;
	cout << "entry key of looking value" << endl;
	cin >> c;
	k=tree->ReadElem(c);
	cout << k << endl;
	cout << "all tree:" << endl;
	tree->Print();
	//cin >> c;
	//tree->FindMore(c);
	system("pause");
}