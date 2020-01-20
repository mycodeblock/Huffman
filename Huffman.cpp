#ifndef ____Huffman____
#define ____Huffman____
#include <bits/stdc++.h>
#include <fstream>

using namespace std;

struct Huffman
{
    Huffman(): num(0),ch(0),left(NULL),right(NULL),isleaf(false){}
    Huffman(unsigned char c,unsigned int n,bool f):isleaf(f),num(n),ch(c),left(NULL),right(NULL) {}
    unsigned int num;   //字符出现的频数
    unsigned char ch;   //字符
    bool isleaf;        //判断是否为树叶
    Huffman *left;
    Huffman *right;
};

typedef Huffman* treeNode;

//依次按字节读入文件，并对字符进行统计
unsigned int count(map<unsigned char,unsigned int>& mapcount, const char *name)
{
    ifstream infile;
    infile.open(name,ios::binary);  //以二进制打开文件
    if(!infile.good()){
        cout<<"OPEN FAIL"<<endl;
        exit(8);
    }
    unsigned char tempchar;
    unsigned int testnum = 0;
    while(!infile.eof())
    {
        tempchar = infile.get();    //依次按字符读入文件
        if(!infile.eof())
        {
            mapcount[tempchar]++;
            testnum++;
        }
    }
    //cout<<testnum<<endl; //字节的总个数
    return testnum;
}

//比较类，优先队列排序的依据
class cmp
{
  public:
    bool operator()(const treeNode& node1, const treeNode& node2) const
    {
        return node1->num > node2->num;
    }
};

//将统计得到的结果生成节点并存放在NODEpq中
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

//生成哈夫曼树
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

//使用递归函数生成哈夫曼编码
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

//删除哈夫曼树
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