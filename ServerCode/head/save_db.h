#ifndef __SAVE_DB_H__
#define __SAVE_DB_H__
#include <iostream>
#include <sstream>
#include <string>
#include <mysql.h>
#include <vector>
#include <assert.h>
#include <mytime.h>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::stringstream;
class MySqlDB
{
    private:
        vector<string> _dbData;
        string _databaseName;
        string _tableName;
        MYSQL _sqlfd;
        int _insertNum;
    public:
    MySqlDB(string dbUser,string password,string databaseName,string tableName)
    {
        mysql_init(&_sqlfd);
        _databaseName = databaseName;
        _tableName = tableName;
        _insertNum = 1;
        if(mysql_real_connect(&_sqlfd,"localhost",dbUser.c_str(),password.c_str(),databaseName.c_str(),0,NULL,CLIENT_FOUND_ROWS))
        {
            cout<<GetTime() << "    DS connect success " << endl;
        }
        else
        {
            cout<<GetTime() << "    DS connect error"  <<endl;
            assert(0);
        }
    }
    void SaveDB(vector<string> dbData)
    {
        int tmp;
        int i;
        int num;
        _dbData = dbData;
        MYSQL_RES* pRes;
        MYSQL_ROW row;
        string str = "select id from " + _tableName+" where id="+_dbData[0];
        cout <<GetTime()<<"    " <<str << endl;
        tmp = mysql_query(&_sqlfd,str.c_str());
        if(tmp != 0)
        {
            assert(0);
        }

        pRes = mysql_store_result(&_sqlfd);
        i = mysql_num_rows(pRes);
        //cout << "fist i=="<< i << endl;
        if(i == 0)
        {

            cout <<GetTime() <<"    Not have this id in the table" <<endl;
            stringstream ss;
            ss << _insertNum;
            string n = ss.str();
            str = "insert into " + _tableName + " (id,num,data"+n+") values(" + _dbData[0]+"," +n+"," + _dbData[1]+")";

            cout<<GetTime()<<"    " << str<<endl;
            tmp = mysql_query(&_sqlfd,str.c_str());
            assert(!tmp);
        }
        else if(i == 1)
        {
            cout <<GetTime() <<"    The data in the table"<<endl;
            str = "select num from "+ _tableName+" where id="+_dbData[0];
            //cout <<str<<endl;
            tmp = mysql_query(&_sqlfd,str.c_str());
            assert(!tmp);
            pRes = mysql_store_result(&_sqlfd);
            i = mysql_num_rows(pRes);
            if(i != 1)
            {
                cout <<GetTime()<<"    Error in 59"<<endl;
                assert(0);
            }
            row =  mysql_fetch_row(pRes);
            num = atoi(row[0]);
            cout <<GetTime()<<"    num:"<< num << endl;
            if(num >= 10)
            {
                num%=10;
            }
            num++;
            stringstream ss;
            ss << num;
            string n = ss.str();
            str = "update " + _tableName + " set num="+n+", data"+n+"="+_dbData[1]+" where id="+_dbData[0];
            cout <<GetTime()<<"    "<< str <<endl;
            tmp = mysql_query(&_sqlfd,str.c_str());
            assert(!tmp);
        }
        mysql_free_result(pRes);
    }
    void ReadDB(string id,vector<string> * p)
    {
        int tmp,line,column;
        MYSQL_RES* pRes;
        MYSQL_ROW Row;
        string str = "select * from "+_tableName + " where id=" + id;
        //cout << str << endl;
        tmp = mysql_query(&_sqlfd,str.c_str());
        //cout <<"tmp == "<< tmp <<endl; 
        assert(!tmp);
        pRes = mysql_store_result(&_sqlfd); 
        line = mysql_num_rows(pRes);
        column = mysql_num_fields(pRes);
        if(line != 1)
        {
            cout<<GetTime() << "    Error in mysql_num_rows()"<<endl;
            assert(0);
        }
        if(column < 3)
        {
            cout<<GetTime() << "    Error in mysql_num_fields()"<<endl;
            assert(0);
        }

        //cout << "column :"<<column <<endl;
        Row = mysql_fetch_row(pRes);
        for(int i=2; i<column; i++)
        {
            if(Row[i] == NULL)
            {
                (*p).push_back("");
            }
            else
            {
                (*p).push_back(Row[i]);
            }
        }
        mysql_free_result(pRes);
    }
    ~MySqlDB()
    {
        mysql_close(&_sqlfd);
    }
};

#endif
