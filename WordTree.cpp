#include "WordTree.h"



WordTree::WordTree()
{
	Tree = NewTree();
}


WordTree::~WordTree()
{
	cleanTree(Tree);
}

bool WordTree::AddElem(char Word[], int value)
{
	if  (value<0) return false;
	if (FindValue(Tree, value)) cleanValue(FindValue(Tree, value), value);
	MyTreeStruct *tr_tmp;
	tr_tmp = Tree;
	for (int i=0;(int)Word[i];i++)
	{
		if (tr_tmp->next[(int)(Word[i])-FIRSTLETTER] == nullptr)
		{
			AddLeaf(tr_tmp, Word[i]);
		}
		if (!Word[i+1]) tr_tmp->next[(int)(Word[i]) - FIRSTLETTER]->value = value;
		tr_tmp = tr_tmp->next[(int)(Word[i]) - FIRSTLETTER];
	}
	return true;
}

void WordTree::ReadValue(int value, char Word[])
{
	MyTreeStruct *tr_tmp = FindValue(Tree, value);
	if (tr_tmp != nullptr)
	{
		LeafWord(tr_tmp, Word);
	}
	else *Word = '\0';
}

MyTreeStruct* WordTree::MoreThen(char * Word, MyTreeStruct *tr_tmp)
{
	char* ch_tmp=Word;
	MyTreeStruct *tree = NewTree();
	/*if (!(*ch_tmp) && isLeaf(tr_tmp))
	{
		char c = getBranchChar(tr_tmp);
		if (!c) return tree;
		AddLeaf(tree, c, tr_tmp->value);
		return tree;
	}
	if (isLeaf(tr_tmp)) return tree; //errorcheck
	if (!(*ch_tmp))
	{
		for (int i = 0; i < AlphLength; i++)
			if (tr_tmp->next[i] != nullptr) mergeBranches(tree,  MoreThen(ch_tmp, tr_tmp->next[i]));
	}
	else if (*ch_tmp && !isLeaf(tr_tmp))
	{
		for (int i = (int)*ch_tmp-FIRSTLETTER+1; i < AlphLength; i++)
			if (tr_tmp->next[i] != nullptr) mergeBranches(tree, MoreThen(++ch_tmp, tr_tmp->next[i]));
	}
	return tree;*/
	for (int i = (*ch_tmp )-FIRSTLETTER+ 1;(-1< i)&&(i < AlphLength); i++)
		if (tr_tmp->next[i] != nullptr) 
			mergeBranches(tree, tr_tmp->next[i]);
	ch_tmp++;
	if (ch_tmp&&tr_tmp->next[(*ch_tmp) - FIRSTLETTER]!=nullptr)
		mergeBranches(tree->next[(*ch_tmp) - FIRSTLETTER],MoreThen(ch_tmp, tree->next[(*ch_tmp )- FIRSTLETTER]));
	if (!ch_tmp)
		for (int i = 0; i < AlphLength; i++)
			if (tr_tmp->next[i] != nullptr) mergeBranches(tree, tr_tmp->next[i]);
	return tree;
}

void WordTree::AddLeaf(MyTreeStruct *branch, char alph)
{

	branch->next[(int)(alph) - FIRSTLETTER] = NewTree();
	//for (int j = 0; j < AlphLength; j++) branch->next[(int)(alph)-FIRSTLETTER]->next[j] = nullptr;
	branch->next[(int)(alph)-FIRSTLETTER]->prev = branch;
	branch->next[(int)(alph)-FIRSTLETTER]->value = -1;
}
void WordTree::AddLeaf(MyTreeStruct *branch, char alph, int value)
{

	branch->next[(int)(alph)-FIRSTLETTER] = NewTree();
	//for (int j = 0; j < AlphLength; j++) branch->next[(int)(alph)-FIRSTLETTER]->next[j] = nullptr;
	branch->next[(int)(alph)-FIRSTLETTER]->prev = branch;
	branch->next[(int)(alph)-FIRSTLETTER]->value = value;
}

MyTreeStruct *WordTree::FindValue(MyTreeStruct *tr, int value)
{
	if (tr->value == value) return tr;
	else for (int i = 0; i < AlphLength; i++)
	{
		if (tr->next[i] != nullptr)
		{
				if (FindValue(tr->next[i], value)!=nullptr) return FindValue(tr->next[i], value);
		}
		
	}
	return nullptr;
}

char *WordTree::TreeWord(MyTreeStruct *tr)
{
	MyTreeStruct *tr_tmp = tr;
	char c[100];
	char *c_tmp=c;
	int j = 0;
	while (tr_tmp->prev!=nullptr)
	{
		int i = 0;
		while (tr_tmp->prev->next[i] != tr_tmp)
			i++;
		*c_tmp = i+FIRSTLETTER;
		c_tmp++;
		tr_tmp = tr_tmp->prev;
		j++;
	}
	*c_tmp = '\0';
	for (int i=0; i<j;i++) c_tmp--;
	return c_tmp;
}

void WordTree::cleanTree(MyTreeStruct *tr)
{
	
	if (tr->prev != nullptr)
	{
		int i = 0;
		while (tr->prev->next[i]!=tr)
		{
			i++;
		}
		tr->prev->next[i] = nullptr;
	}
	for (int i = 0; i < AlphLength; i++)
		if (tr->next[i] != nullptr)
			cleanTree(tr->next[i]);
	delete tr;
}

void WordTree::cleanValue(MyTreeStruct * tr, int value)
{
	bool lst_leaf = true;
	for (int i = 0; i < AlphLength && lst_leaf; i++)
	{
		if(tr->next[i]!=nullptr)  lst_leaf = false;
	}
	if (lst_leaf && (tr->value == value || tr->value == -1) && tr != Tree)
	{
		MyTreeStruct *cpy = tr->prev;
		cleanTree(tr);
		cleanValue(cpy, value);
	}
	else if (tr->value == value || tr->value == -1)
	{
		tr->value = -1;
	}
}

MyTreeStruct * WordTree::NewTree()
{
	MyTreeStruct* tree = new MyTreeStruct;
	tree->prev = nullptr;
	for (int i = 0; i < AlphLength; i++) tree->next[i] = nullptr;
	tree->value = -1;
	return tree;
}

bool WordTree::isLeaf(MyTreeStruct * tr)
{
	for (int i = 0; i < AlphLength; i++) if (tr->next[i] != nullptr) return false;
	return true;
}

int WordTree::getBranchNumber(MyTreeStruct * tr)
{
	if (!tr) return -1;
	if (tr->prev == nullptr) return -1;
	int i = 0;
	while (tr->prev->next[i] != tr)
		i++;
	return i;
}

char WordTree::getBranchChar(MyTreeStruct * tr)
{
	int i = getBranchNumber(tr);
	if (i == -1) return '\0';
	return (char)(i + FIRSTLETTER);
}

bool WordTree::mergeBranches(MyTreeStruct * parent, MyTreeStruct * child)
{
	if (isLeaf(child))
	{
		parent->next[getBranchNumber(child)] = NewTree();
		parent->next[getBranchNumber(child)]->value = child->value;
	}
	else
	{
		for (int i = 0; i < AlphLength; i++)
			if (child->next[i] != nullptr)
			{
				parent->next[i] = NewTree();
				mergeBranches(parent->next[i], child->next[i]);
			}
	}
	return true;
}

int WordTree::ReadElem(char* Word)
{
	MyTreeStruct *tr_tmp = Tree;
	char* c_tmp = Word;
	while (*c_tmp&&tr_tmp->next[(int)c_tmp[0]-FIRSTLETTER])
	{
		tr_tmp = tr_tmp->next[(int)c_tmp[0]-FIRSTLETTER];
		c_tmp++;
	}
	if (!*c_tmp) return tr_tmp->value;
	return -1;
}

void WordTree::PrintTree(MyTreeStruct * tree)
{
	if (tree)
	{
		char tmp_word[MAXLENGTH];
		if (tree->value != -1)
		{
			LeafWord(tree, tmp_word);
			std::cout << tmp_word << "; ";
		}
		for (int i = 0; i < AlphLength; i++)
			if (tree->next[i] != nullptr)
				PrintTree(tree->next[i]);
	}
}

void WordTree::Print()
{
	PrintTree(Tree);
}

void WordTree::LeafWord(MyTreeStruct * tree, char word[])
{
	MyTreeStruct *tr_tmp = tree;
	char Word[MAXLENGTH];
	char *c_tmp = Word, *c_tmp2 = word;
	while (tr_tmp != nullptr)
	{
		*c_tmp = getBranchChar(tr_tmp);
		c_tmp++;
		tr_tmp = tr_tmp->prev;
	}
	c_tmp--;
	for (int i=0; c_tmp!=Word;  i++)
	{
		c_tmp--;
		word[i] = *c_tmp;
		word[i+1] = '\0';
	}
	
}

void WordTree::FindMore(char *word)
{
	PrintTree(MoreThen(word, Tree));
}