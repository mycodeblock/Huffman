#include"Huffman.cpp"

void compress(string inname, string outname)
{
    unordered_map<unsigned char,string> mapcode;  //���ڴ�Ź��������룬������ٶȽ�map��
    map<unsigned char, unsigned int> mapcount; //�����ַ�Ƶ�ʵ�ͳ��
    priority_queue<treeNode,vector<treeNode>,cmp> NODEpq;  //���ȶ��У��������ɹ�������
    string code = "";
    unsigned int num = count(mapcount, inname.c_str());  //ͳ�Ʋ����ػ��ֽ�����
    sortNode(mapcount, NODEpq); //���ɽڵ�
    makeHuffmanTree(NODEpq);    //���ɹ�������
    makemapping(mapcode, NODEpq.top(), code);   //����������
    deletetree(NODEpq.top());   //ɾ����������

    ifstream infile;
    infile.open(inname,ios::binary);    //�Զ����ƴ��ļ�
    ofstream outfile;
    outfile.open(outname,ios::binary|ios::trunc);
    if(!infile.good() || !outfile.good())   //�ж��ļ���״̬
    {
        cout<<"Open files fail!"<<endl;
        return;
    }
    outfile<<inname<<' '; //д��ԭ�ļ�����
    outfile<<mapcount.size()<<' '<<num<<' ';    //д���������Լ����ֽ���
    auto end = mapcount.end();
    for(auto iter = mapcount.begin();iter != end;iter++)  //д����뼰���Ӧ��Ƶ��
    {
        outfile<<iter->first<<' ';
        outfile<<iter->second<<' ';
    }
    unsigned char tempchar;
    int j = 0;
    unsigned char temp;
    temp = 0;   //�����ݴ����
    while(!infile.eof())    //���ζ����ַ�����д�����Ӧ�Ĺ���������
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
    if(j <= 7)  //�������һ���ֽ�
    {
        while(j < 7)
        {
            temp = temp<<1;
            ++j;
        }
        outfile.write((char*)&temp,1);
    }
}