#include <iostream>
#include <map>
#include <deque>
#include <vector>
#include <string>
#include <cstdio>
#include <ctime>  
#include <fstream>  
#include <sstream>  
#include <stdlib.h>  
using namespace std;

enum {
     NPREF  =  2 ,           //ǰ׺�ĸ���
     MAXGEN  =  10000  //�������ô�����
};  

typedef deque<string> Prefix; 
map<Prefix,vector<string> > statetab; // ʹ��duque ��Ϊ��һ���ǰ׺������չ�͸ı䣬����statetab��ǰ׺�ͺ�׺��������

char  NONWORD[] = "\n"; //αǰ׺����������������Ϊ���ĺ�׺

void add(Prefix &prefix, const string &s)
{
     if(prefix.size() == NPREF) //��ǰ׺��Ŀ�ﵽָ������֮�󣬸ı�ǰ׺��Ҳ����w1 w2 ��� w2 w3
     {
          statetab[prefix].push_back(s);
          prefix.pop_front();
     }
     prefix.push_back(s);
}

void build(Prefix &prefix, istream &in)//����ͳ�Ʊ�
{
     string buf;
     while(in >> buf)
          add(prefix,buf);
}

void generate(int nwords)
{
     Prefix prefix;
     int i;
     srand(time(NULL));
	 string str1,str2;
	 cout<<"print prefix 1";
	 cin>>str1;
     add(prefix,str1);//����αǰ׺
	 cout<<"print prefix 2";
	 cin>>str2;
     add(prefix,str2);//����αǰ׺
     //cout<<"NOW prefix: "<<prefix[0]<<" "<<prefix[1]<<endl;
     for(i = 0; i < nwords; i++)
     {
          vector<string> & suf = statetab[prefix];
          //cout<<"prefix:"<<prefix[0]<<" suf "<<suf[0]<<endl;
          const string &w = suf[rand() % suf.size()];//�����п��ܵĺ�׺�������ѡ��һ����
          if(w == str1 || w == str2)
               break;
          cout << w <<" ";
          prefix.pop_front();//�ı�ǰ׺
          prefix.push_back(w);
     }
     cout<<endl;
}

string readFileIntoString(char * filename)  
{  
ifstream ifile(filename);  
//���ļ����뵽ostringstream����buf��  
ostringstream buf;  
char ch;  
while(buf&&ifile.get(ch))  
buf.put(ch);  
//������������buf�������ַ���  
return buf.str();  
}  
  

int main()
{
     int nwords = MAXGEN;
     Prefix prefix;
	 char * fn = "example.txt";
	 string str;
	 str = readFileIntoString(fn);
	 cout<<"read:"<<str<<endl;
     //string sentence = "Show your flowchars and conceal your tables and I will be mystified. Show your tables and your flowcharts will be obvious. (end)";
     istringstream in(str);
     //freopen("mkov.txt","r",stdin);
     for(int i = 0; i < NPREF; i++)
          add(prefix,NONWORD);
     build(prefix,in);
     add(prefix,NONWORD);
     generate(nwords);
     return 0;
}