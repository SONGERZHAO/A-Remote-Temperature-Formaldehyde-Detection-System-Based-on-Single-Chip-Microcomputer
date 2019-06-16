#include <iostream>
#include "save_db.h"
#include <vector>
#include <string>
#include <sstream>
#include "mytime.h"
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::stringstream;

int  DealTemp(int temp)
{
    float tmp;
    int i = 1;
    if(temp < 0)
    {
        temp -= 1;
        temp = ~temp;
        i = -1;
    }
    tmp = temp;
    return (int)(tmp*0.0625*100);
}


void DealArgv(char * buff,vector<string> * dbData)
{
    unsigned char p1,p2;
    int id = 0x00;
    int data = 0x00;
    int num = 0;
    int tem;
    int ch2o = 0;

    num = buff[0] - '0';

    p1 = buff[1];
    p2 = buff[2];
    if(p1 == 0xff)
        p1 = ~p1;
    if(p2 == 0xff)
        p2 = ~p2;
    id |= p2;
    id <<= 8;
    id |= p1;
    
    p1 = buff[3];
    p2 = buff[4];
    if(p1 == 0xff)
        p1 = ~p1;
    if(p2 == 0xff)
        p2 = ~p2;
    data |= p2;
    data <<= 8;
    data |= p1;

    tem = DealTemp(data);

    if(num == 7)
    {
        data = 0x00;
        p1 = buff[5];
        p2 = buff[6];
        if(p1 == 0xff)
            p1 = ~p1;
        if(p2 == 0xff)
            p2 = ~p2;
        data |= p1;
        data << 8;
        data |= p2;
        ch2o = data/66.64*0.08*10000;
    }


    cout<<GetTime() <<"    ID = "<< id <<" Tem = "<< tem <<" ch2o = " << ch2o <<endl;
    stringstream ss;
    ss << id;
    (*dbData).push_back(ss.str());
    stringstream dat;
    dat << tem;
    dat << '.';
    dat << ch2o;
    (*dbData).push_back(dat.str());
    //cout <<"dbdata[1]" <<(*dbData)[1] <<endl;

}
int main (int argc, char* argv[])
{
    //cout << "argc:"<<argc <<endl;
    //cout <<"argv[0]:" <<argv[0] <<endl;
    string dbuser = "root";
    string password = "Songerzhao123.";
    string databaseName = "mydata";
    string tableName = "tem_ch2o_data";
    MySqlDB p (dbuser,password,databaseName,tableName);
    vector<string> dbData;
    DealArgv(argv[0],&dbData);
    p.SaveDB(dbData);
    return 0;
}
