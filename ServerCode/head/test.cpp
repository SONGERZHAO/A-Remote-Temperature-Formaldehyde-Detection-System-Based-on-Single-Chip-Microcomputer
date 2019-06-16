#include <iostream>
#include <string>
#include <vector>
#include "save_db.h"

using std::string;
using std::vector;
using std::cout;
using std::endl;
int main (void)
{
    string dbUser = "root";
    string password = "Songerzhao123.";
    string databasesName = "mydata";
    string tableName = "tem_ch2o_data";
    MySqlDB p (dbUser,password,databasesName,tableName); 
    string id = "3";
    string data = "'sadf'";
    vector<string> arr;
    arr.push_back(id);
    arr.push_back(data);
    cout << "Star" <<endl;
    p.SaveDB(arr);

    cout <<"-----read------"<<endl;
    string rdid = "20";
    vector<string> rddata;
    p.ReadDB(rdid,&rddata);
    for(int i=0; i<rddata.size(); i++)
    {
        cout << "rddara"<<i<<"=="<<rddata[i]<<endl;
    }   
}
