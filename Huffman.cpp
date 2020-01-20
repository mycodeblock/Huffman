#ifndef ____Huffman____
#define ____Huffman____
#include <bits/stdc++.h>
#include <fstream>

using namespace std;

struct Huffman
{
    Huffman(): num(0),ch(0),left(NULL),right(NULL),isleaf(false){}
    Huffman(unsigned char c,unsigned int n,bool f):isleaf(f),num(n),ch(c),left(NULL),right(NULL) {}
    unsigned int num;   //�ַ����ֵ�Ƶ��
    unsigned char ch;   //�ַ�
    bool isleaf;        //�ж��Ƿ�Ϊ��Ҷ
    Huffman *left;
    Huffman *right;
};

typedef Huffman* treeNode;

//���ΰ��ֽڶ����ļ��������ַ�����ͳ��
unsigned int count(map<unsigned char,unsigned int>& mapcount, const char *name)
{
    ifstream infile;
    infile.open(name,ios::binary);  //�Զ����ƴ��ļ�
    if(!infile.good()){
        cout<<"OPEN FAIL"<<endl;
        exit(8);
    }
    unsigned char tempchar;
    unsigned int testnum = 0;
    while(!infile.eof())
    {
        tempchar = infile.get();    //���ΰ��ַ������ļ�
        if(!infile.eof())
        {
            mapcount[tempchar]++;
            testnum++;
        }
    }
    //cout<<testnum<<endl; //�ֽڵ��ܸ���
    return testnum;
}

//�Ƚ��࣬���ȶ������������
class cmp
{
  public:
    bool operator()(const treeNode& node1, const treeNode& node2) const
    {
        return node1->num > node2->num;
    }
};

//��ͳ�Ƶõ��Ľ�����ɽڵ㲢�����NODEpq��
void sortNode(map<unsigned char,unsigned int>& mapcount, priority_queue<treeNode, vector<treeNode>, cmp> &NODEpq)
{
    auto iter = mapcount.begin();
    auto end = mapcount.end();
    for(iter = mapcount.begin();iter != end;iter++)
    {
        treeNode Node = new Huffman(iter->first,iter->second,true);
        NODEpq.push(Node);
    }
}

//���ɹ�������
void makeHuffmanTree(priority_queue<treeNode,vector<treeNode>,cmp>&NODEpq)
{
    while(NODEpq.size() > 1)
    {
        treeNode Node1 = NODEpq.top();
        NODEpq.pop();
        treeNode Node2 = NODEpq.top();
        NODEpq.pop();
        treeNode Node = new Huffman(0, Node1->num+Node2->num, false);
        Node->left  = Node1;
        Node->right = Node2;
        NODEpq.push(Node);
    }
}

//ʹ�õݹ麯�����ɹ���������
void makemapping(unordered_map<unsigned char,string>&mapcode, treeNode root, string code)
{
    if(root == NULL)
    {
        return;
    }
    else
    {
        if(root->isleaf == true)
        {
            mapcode[root->ch] = code;
        }
        if(root->left)
            makemapping(mapcode, root->left, code+"0");
        if(root->right)
            makemapping(mapcode, root->right, code+"1");
    }
}

//ɾ����������
void deletetree(treeNode root)
{
    if(root != NULL)
    {
        deletetree(root->left);
        deletetree(root->right);
        delete root;
    }
}
#endif