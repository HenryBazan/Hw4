#include <iostream>
#include <string>
#include "autocompleter.h"

using namespace std;


Autocompleter::Autocompleter()
{
    root = nullptr;

}

void Autocompleter::insert(string x, int freq)
{
    Entry entry;
    entry.s =  x;
    entry.freq = freq;

    insert_recurse(entry, root);
}

int Autocompleter::size()
{
    return size_recurse(root);
}

int Autocompleter::size_recurse(Node* p)
{
    if(p==nullptr)
    {
        return 0;
    }

    int leftSize =  size_recurse(p->left);
    int rightSize = size_recurse(p->right);

    return leftSize + rightSize + 1;
}

void Autocompleter::completions(string x, vector<string> &T)
{
    T.clear();

    vector<Entry> entryResults;
    completions_recurse(x,root,entryResults);
}

void Autocompleter::completions_recurse(string x, Node* p, vector<Entry> &C)
{
    if(p == nullptr)
    {
        return;
    }
    int compareResult = x.compare(p->e.s);

    if(compareResult < 0)
    {
        completions_recurse(x, p->left, C);
    }
    else if(compareResult > 0)
    {
        completions_recurse(x, p->right, C);
    }
    else
    {
        completions_recurse(x,p->left, C);
    }
}

void Autocompleter::insert_recurse(Entry e, Node*& p)
{
    if(p ==  nullptr)
    {
        p = new Node(e);
        return;
    }

    int compareResult = e.s.compare(p->e.s);
    if(compareResult < 0)
    {
        insert_recurse(e, p->left);
    }

    else if( compareResult > 0)
    {
        insert_recurse(e, p->right);
    }

    else
    {
        return;
    }

    update_height(p);

    rebalance(p);

}

