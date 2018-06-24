#ifndef WORDTREE
#define WORDTREE
#define FIRSTLETTER (int)('a')
#define MAXLENGTH 100
#define AlphLength 'z'-'a'+1
#include <iostream>
struct MyTreeStruct
{
	MyTreeStruct* next[AlphLength];
	MyTreeStruct* prev;
	int  value;
};

class WordTree
{
public:
	WordTree();
	~WordTree();

	bool AddElem(char Word[], int value);
	int ReadElem(char* Word);
	void ReadValue(int value,char word[]);
	void FindMore(char *word);
	void Print();
private:
	MyTreeStruct *Tree;
	MyTreeStruct *MoreThen(char* Word, MyTreeStruct *tr_tmp);
	void AddLeaf(MyTreeStruct *branch, char alph);
	void AddLeaf(MyTreeStruct *branch, char alph, int value);
	MyTreeStruct *FindValue(MyTreeStruct *tr, int value);
	char *TreeWord(MyTreeStruct *tr);
	void cleanTree(MyTreeStruct *tr);
	void cleanValue(MyTreeStruct *tr, int value);
	MyTreeStruct* NewTree();
	bool isLeaf(MyTreeStruct *tr);
	int getBranchNumber(MyTreeStruct *tr);
	char getBranchChar(MyTreeStruct *tr);
	bool mergeBranches(MyTreeStruct *parent, MyTreeStruct *child);
	void PrintTree(MyTreeStruct *tree);
	void LeafWord(MyTreeStruct *tree, char  word[]);
};


#endif // !WORDTREE