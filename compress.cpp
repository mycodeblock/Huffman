#include"Huffman.cpp"

void compress(string inname, string outname)
{
    unordered_map<unsigned char,string> mapcode;  //用于存放哈夫曼编码，其查找速度较map快
    map<unsigned char, unsigned int> mapcount; //用于字符频率的统计
    priority_queue<treeNode,vector<treeNode>,cmp> NODEpq;  //优先队列，用于生成哈夫曼树
    string code = "";
    unsigned int num = count(mapcount, inname.c_str());  //统计并返回回字节总数
    sortNode(mapcount, NODEpq); //生成节点
    makeHuffmanTree(NODEpq);    //生成哈夫曼树
    makemapping(mapcode, NODEpq.top(), code);   //哈夫曼编码
    deletetree(NODEpq.top());   //删除哈夫曼树

    ifstream infile;
    infile.open(inname,ios::binary);    //以二进制打开文件
    ofstream outfile;
    outfile.open(outname,ios::binary|ios::trunc);
    if(!infile.good() || !outfile.good())   //判断文件打开状态
    {
        cout<<"Open files fail!"<<endl;
        return;
    }
    outfile<<inname<<' '; //写入原文件名称
    outfile<<mapcount.size()<<' '<<num<<' ';    //写入编码个数以及总字节数
    auto end = mapcount.end();
    for(auto iter = mapcount.begin();iter != end;iter++)  //写入编码及其对应的频数
    {
        outfile<<iter->first<<' ';
        outfile<<iter->second<<' ';
    }
    unsigned char tempchar;
    int j = 0;
    unsigned char temp;
    temp = 0;   //用于暂存编码
    while(!infile.eof())    //依次读入字符，并写入相对应的哈夫曼编码
    {
        tempchar = infile.get();
        if(!infile.eof())
        {
            string code = mapcode[tempchar];
            int size = mapcode[tempchar].size();
            for(int i = 0; i < size; ++i)
            {
                if(j < 8)
                {
                    if(code[i] == '1')
                    {
                        temp = temp|1;
                    }
                    if(j != 7)  temp = temp<<1;
                    ++j;
                    if(j == 8)
                    {
                        outfile.write((char*)&temp,1);
                        temp = 0;
                        j = 0;
                    }
                }
            }
        }
    }
    if(j <= 7)  //处理最后一个字节
    {
        while(j < 7)
        {
            temp = temp<<1;
            ++j;
        }
        outfile.write((char*)&temp,1);
    }
}