/* Copyright (c) 2001, 2010, Oracle and/or its affiliates. 
All rights reserved. */
/*
   NAME
     occidml.cpp - Basic DML Operations demo

   DESCRIPTION
     To exhibit the insertion, selection, updating and deletion of
     a row using OCCI interface

   MODIFIED   (MM/DD/YY)
   mvasudev   09/27/10 - remove HR schema and user SCOTT
   mvasudev   05/22/08 - Add try/catch blocks
   sudsrini   10/22/06 - Username/Password lower case
   lburgess   04/14/06 - lowercase passwords 
   sudsrini   07/23/04 - Copyright Info
   idcqe      03/05/01 - Creation

*/

#include <iostream>
#include <occi.h>

using namespace oracle::occi;
using namespace std;
//------------------------------------------------------------------------------
// Local
//------------------------------------------------------------------------------
Environment *env;
Connection *conn;
Statement *stmt;
//------------------------------------------------------------------------------
// connect
//------------------------------------------------------------------------------
bool connect(void)
{
    bool ok = true;
    try
    {
        env = Environment::createEnvironment (Environment::DEFAULT);
        conn = env->createConnection ("TRAMTEST", "TRAMTEST", "TRdb");
        cout<<"Database connection success"<<endl;
    }
    catch(SQLException ex)
    {
        ok = false;        
        cout<<"Exception thrown for connect"<<endl;
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line "<< __LINE__ << endl;
        cout << ex.what() << '\n';
        cout<<"Error number: "<<  ex.getErrorCode() << endl;
    } 
  
    return (ok);
}
//------------------------------------------------------------------------------
// occiSelect
//------------------------------------------------------------------------------
int occiSelect(void)
{
    bool ok = true;
    int entry = 0;
    cout<<"OCCI select"<<endl;
    string query="select * from tram";
    ResultSet *rset;
    try
    {
        stmt = conn->createStatement (query);    
        rset = stmt->executeQuery ();
        while(rset->next())
        {
            cout <<"ID : "<< rset->getInt(1) << endl;
            cout <<"ADMIN : "<< rset->getString(7) << endl;
            cout <<"RMARK : "<< rset->getString(10) << endl;
            entry++;
        }
    
    }
    catch(SQLException ex)
    {
        ok = false;        
        cout<<"Exception thrown for select"<<endl;
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line "<< __LINE__ << endl;
        cout << ex.what() << '\n';
        cout<<"Error number: "<<  ex.getErrorCode() << endl;
    } 
    if(ok)
        stmt->closeResultSet (rset);
    conn->terminateStatement (stmt);    
}
//------------------------------------------------------------------------------
// occiSelect
//------------------------------------------------------------------------------
int occiSelect2(void)
{
    bool ok = true;
    int entry = 0;
    cout<<"OCCI select"<<endl;
    //string query="select * from tram where TRAM_ID = :pTramID";
    string query="select * from tram where TRAM_ID = :pTramID";
    ResultSet *rset;
    try
    {        
        stmt = conn->createStatement (query);         
        stmt->setNumber (1, 100000001);
        
        rset = stmt->executeQuery ();
        while(rset->next())
        {
            cout <<"ID : "<< rset->getInt(1) << endl;
            cout <<"ADMIN : "<< rset->getString(7) << endl;
            cout <<"RMARK : "<< rset->getString(10) << endl;
            entry++;
        }
    
    }
    catch(SQLException ex)
    {
        ok = false;        
        cout<<"Exception thrown for select"<<endl;
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line "<< __LINE__ << endl;
        cout << ex.what() << '\n';
        cout<<"Error number: "<<  ex.getErrorCode() << endl;
    } 
    if(ok)
        stmt->closeResultSet (rset);
    conn->terminateStatement (stmt);    
}
//------------------------------------------------------------------------------
// main
//------------------------------------------------------------------------------
int main(void)
{
    cout<<"OCCI TEST"<<endl;
    bool ok = false;
    ok = connect();
    if(ok)
    {
        occiSelect();
        occiSelect2();
    }


    // oracle db disconnection
    env->terminateConnection (conn);
    Environment::terminateEnvironment (env);
    return 0;
}