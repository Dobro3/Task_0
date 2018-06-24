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
	while (k > 0)
	{
		cin >> c;
		cin >> k;
		tree->AddElem(c, k);
	}
	cin >> k;
	tree->ReadValue(k, c);
	
	cout << "word: " << c <<endl;
	cin >> c;
	k=tree->ReadElem(c);
	cout << k << endl;
	tree->Print();
	cin >> c;
	tree->FindMore(c);
	system("pause");
}