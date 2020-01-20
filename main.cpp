#include<bits/stdc++.h>
#include"compress.cpp"
#include"decompress.cpp"

using namespace std;

int main(int argc,char *argv[])
{
    //unsigned long long time1 = clock();
    string a = argv[1]; //option(compress/decompress)
    if(a == "compress")
    {
        string desti = argv[2]; //input file
        if(argc == 3) desti = desti.substr(0, desti.find('.'));
        else desti = argv[3];
        desti += ".yz";     //generate the name of output file
        compress(argv[2],desti);    //compress
        //unsigned long long time2 = clock();
        //cerr<<time2 - time1<<endl;
        cout<<"Compression Successful"<<endl;
    }
    else if(a == "decompress")
    {
        string inname = argv[2];    //input file
        if(inname.substr(inname.find('.')+1, inname.size()) != "yz")    //determine if it is a yz file
        {
            cout<<"The file can't be decompressed"<<endl;
            exit(8);
        }
        string outname = "";
        if(argc == 4)
            outname = argv[3];  //output file
        decompress(inname,outname); //decompress
        //unsigned long long time2 = clock();
        //cerr<<time2 - time1<<endl;
        cout<<"Decompression Successful"<<endl;
    }
    else
    {
        cout<<"INPUT ERROR!"<<endl;
    }
}