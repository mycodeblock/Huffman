#include"Huffman.cpp"

void decompress(string inname, string& outname)
{
    map<unsigned char,unsigned int> mapcount;
    unsigned int num, sum;
    char space;
    unsigned char test[8] = {128,64,32,16,8,4,2,1}; //用于测试某一位是否为1
    string suffix;
    ifstream infile;
    infile.open(inname,ios::binary);
    infile>>suffix;     //读取文件名称
    infile.get(space);
    if(outname == "")
        outname = suffix;  //若没有输入指定名称，则按照原文件的名称
    ofstream outfile;
    outfile.open(outname,ios::binary|ios::trunc);
    if(!infile.good() || !outfile.good())
    {
        cout<<"Open files fail!"<<endl;
        return;
    }
    infile>>num;    //字符个数
    infile.get(space);
    infile>>sum;    //文件字节总数
    //cout<<sum<<endl;
    infile.get(space);
    unsigned char ch;
    unsigned int amount;
    for(int i = 0;i < num;++i)     //读取统计结果
    {
        ch = infile.get();
        infile.get(space);
        infile>>amount;
        infile.get(space);
        mapcount[ch] = amount;
    }

    priority_queue<treeNode,vector<treeNode>,cmp> NODEpq;  //用于生成哈夫曼树
    sortNode(mapcount, NODEpq); //生成节点
    makeHuffmanTree(NODEpq);    //生成哈夫曼树

    Huffman *root = NODEpq.top();
    unsigned char tempchar;
    while(sum)      //根据编码写出原有字符。
    {
        tempchar = infile.get();
        for(int i = 0; i < 8; ++i)
        {
            if(tempchar& test[i])
            {
                root = root->right;
            }
            else
            {
                root = root->left;
            }
            if(root->isleaf)
            {
                if(sum--)
                {
                    outfile.write((char*)&root->ch, 1);  //outfile<<NODEpq->ch;
                    root = NODEpq.top();
                }
                if(sum == 0) break;
            }
        }
    }
    deletetree(NODEpq.top());   //删除哈夫曼树
}