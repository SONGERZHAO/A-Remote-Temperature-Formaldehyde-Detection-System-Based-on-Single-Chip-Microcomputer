#include <iostream>
#include <net_sock.h>
#include <save_db.h>
#include <string>
#include <vector>
#include <sstream>
#include <mytime.h>
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::stringstream;
void SplitString(const string& s, vector<string>& v, const string& c)
{
    string::size_type pos1, pos2;
    pos2 = s.find(c);
    pos1 = 0;
    while(string::npos != pos2)
    {
        v.push_back(s.substr(pos1, pos2-pos1));
        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    if(pos1 != s.length())
    v.push_back(s.substr(pos1));
}


void * ThreadFunc(void *arg)
{
    int sockfd = *(int*)arg;
    string id = "1";
    string p1 = ".";
    vector <string> arr;
    string html2 = "HTTP/1.0 200 OK\r\nContent-Type: text/html;charset=utf-8\r\nContent_Length: ";
    string html = "<html><head><h1> MrSong's Test<br/></h1><head/>";
    html += "<h2>检测器ID:"+id+"<br/></h2>";
    string dbuser = "root";
    string password = "Songerzhao123.";
    string databaseName = "mydata";
    string tableName = "tem_ch2o_data";
    MySqlDB dbfd (dbuser,password,databaseName,tableName);
    
    dbfd.ReadDB(id,&arr);
    cout <<GetTime() <<"    ReadDB" << endl;
    for(int i=0; i<arr.size();i++)
    {
        vector<string> strarr;
        SplitString(arr[i],strarr,p1);
        strarr[0].insert(strarr[0].length()-2,p1);
        string p2 = "0.0000";
        p2.insert(6-strarr[1].length(),strarr[1]);
        html += "<h2> 温度:"+strarr[0]+ "<br/></h2>";
        html += "<h2> 甲醛浓度:"+p2+"<br/></h2>";
    }
    html += "<a href = 'javascript:location.reload();'>点击刷新</a><html>";
    //cout << html << endl;
    int length = html.length();
    stringstream ss;
    ss<< length;
    html2 +=ss.str()+"\r\n\r\n";
    html = html2+html;
   // cout << html << endl;
    send(sockfd,html.c_str(),html.length(),0);
    close(sockfd);
}

int main (void)
{
    NetSock fd (9000,ThreadFunc);
}
