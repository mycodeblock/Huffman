#include"Huffman.cpp"

void decompress(string inname, string& outname)
{
    map<unsigned char,unsigned int> mapcount;
    unsigned int num, sum;
    char space;
    unsigned char test[8] = {128,64,32,16,8,4,2,1}; //���ڲ���ĳһλ�Ƿ�Ϊ1
    string suffix;
    ifstream infile;
    infile.open(inname,ios::binary);
    infile>>suffix;     //��ȡ�ļ�����
    infile.get(space);
    if(outname == "")
        outname = suffix;  //��û������ָ�����ƣ�����ԭ�ļ�������
    ofstream outfile;
    outfile.open(outname,ios::binary|ios::trunc);
    if(!infile.good() || !outfile.good())
    {
        cout<<"Open files fail!"<<endl;
        return;
    }
    infile>>num;    //�ַ�����
    infile.get(space);
    infile>>sum;    //�ļ��ֽ�����
    //cout<<sum<<endl;
    infile.get(space);
    unsigned char ch;
    unsigned int amount;
    for(int i = 0;i < num;++i)     //��ȡͳ�ƽ��
    {
        ch = infile.get();
        infile.get(space);
        infile>>amount;
        infile.get(space);
        mapcount[ch] = amount;
    }

    priority_queue<treeNode,vector<treeNode>,cmp> NODEpq;  //�������ɹ�������
    sortNode(mapcount, NODEpq); //���ɽڵ�
    makeHuffmanTree(NODEpq);    //���ɹ�������

    Huffman *root = NODEpq.top();
    unsigned char tempchar;
    while(sum)      //���ݱ���д��ԭ���ַ���
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
    deletetree(NODEpq.top());   //ɾ����������
}