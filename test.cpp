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
     NPREF  =  2 ,           //前缀的个数
     MAXGEN  =  10000  //最多有那么多个词
};  

typedef deque<string> Prefix; 
map<Prefix,vector<string> > statetab; // 使用duque 作为第一项方便前缀词数扩展和改变，这里statetab将前缀和后缀关联起来

char  NONWORD[] = "\n"; //伪前缀，将真正的输入作为它的后缀

void add(Prefix &prefix, const string &s)
{
     if(prefix.size() == NPREF) //当前缀数目达到指定词数之后，改变前缀，也就是w1 w2 变成 w2 w3
     {
          statetab[prefix].push_back(s);
          prefix.pop_front();
     }
     prefix.push_back(s);
}

void build(Prefix &prefix, istream &in)//构造统计表
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
     add(prefix,str1);//生成伪前缀
	 cout<<"print prefix 2";
	 cin>>str2;
     add(prefix,str2);//生成伪前缀
     //cout<<"NOW prefix: "<<prefix[0]<<" "<<prefix[1]<<endl;
     for(i = 0; i < nwords; i++)
     {
          vector<string> & suf = statetab[prefix];
          //cout<<"prefix:"<<prefix[0]<<" suf "<<suf[0]<<endl;
          const string &w = suf[rand() % suf.size()];//在所有可能的后缀中随机的选择一个词
          if(w == str1 || w == str2)
               break;
          cout << w <<" ";
          prefix.pop_front();//改变前缀
          prefix.push_back(w);
     }
     cout<<endl;
}

string readFileIntoString(char * filename)  
{  
ifstream ifile(filename);  
//将文件读入到ostringstream对象buf中  
ostringstream buf;  
char ch;  
while(buf&&ifile.get(ch))  
buf.put(ch);  
//返回与流对象buf关联的字符串  
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