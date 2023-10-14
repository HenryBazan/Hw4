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

    return 1 + size_recurse(p->left) + size_recurse(p->right);
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
        C.push_back(p->e);
        if(C.size()>2)
        {
            C.pop_back();
        }
        completions_recurse(x,p->right,C);
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

void Autocompleter::rebalance(Node*& p)
{
    int balance = height(p->left)-height(p->right);

    if (balance > 1)
    {
        int leftBalance = height(p->left->left) - height(p->left->right);

        if (leftBalance < 0 )
        {
            left_rotate(p->left);
        }
        right_rotate(p);
    }

    else if (balance < -1)
    {
        int rightBalance = height(p->right->left) - height(p->right->right);
        if (rightBalance > 0)
        {
            right_rotate(p->right);
        }
        left_rotate(p);
    }

    update_height(p);
}

void Autocompleter::right_rotate(Node*& p)
{
    Node* newRoot = p->left;
    p->left = newRoot->right;
    newRoot->right = p;
    p = newRoot;

    update_height(p->right);
    update_height(p);
}

void Autocompleter::left_rotate(Node*& p)
{
    Node* newRoot = p->right;
    p->right = newRoot->left;
    newRoot->left = p;
    p = newRoot;

    update_height(p->left);
    update_height(p);
}

