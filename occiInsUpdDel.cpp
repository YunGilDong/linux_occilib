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
// occiInset
//------------------------------------------------------------------------------
int occiInset(void)
{
    string sqlStmt = "INSERT INTO TRAMTEST.TRAM ( \
                        TRAM_ID, UPDATE_DATE, RMARK) \
                        VALUES (:pid, sysdate, :prmark)";

                       
    
    try{
        stmt=conn->createStatement (sqlStmt);
        stmt->setInt (1, 9999); // pid
        stmt->setString (2, "TEST01");  // 
        stmt->executeUpdate ();
        cout << "insert - Success" << endl;
    }catch(SQLException ex)
    {
        cout<<"Exception thrown for insert"<<endl;
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line "<< __LINE__ << endl;
        cout << ex.what() << '\n';
        cout<<"Error number: "<<  ex.getErrorCode() << endl;
    }

    conn->terminateStatement (stmt);
}
//------------------------------------------------------------------------------
// occiUpdate
//------------------------------------------------------------------------------
int occiUpdate(void)
{
    string sqlStmt = "UPDATE TRAM \
                        SET    UPDATE_DATE  = sysdate \
                               ,TRAM_NUM     = :TRAM_NUM \
                        WHERE  TRAM_ID      = :TRAM_ID";
    
    try{
        stmt=conn->createStatement (sqlStmt);
        stmt->setInt (1, 9999);
        stmt->setInt (2, 9999);        
        stmt->executeUpdate ();
        cout << "update - Success" << endl;
    }catch(SQLException ex)
    {
        cout<<"Exception thrown for update"<<endl;
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line "<< __LINE__ << endl;
        cout << ex.what() << '\n';
        cout<<"Error number: "<<  ex.getErrorCode() << endl;
    }

    conn->terminateStatement (stmt);
    
}
//------------------------------------------------------------------------------
// occiDelete
//------------------------------------------------------------------------------
int occiDelete(void)
{
    string sqlStmt = "DELETE FROM TRAM WHERE TRAM_ID = :TRAM_ID";
    
    try{
        stmt=conn->createStatement (sqlStmt);
        stmt->setInt (1, 9999);    
        stmt->executeUpdate ();
        cout << "delete - Success" << endl;
    }catch(SQLException ex)
    {
        cout<<"Exception thrown for delete"<<endl;
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line "<< __LINE__ << endl;
        cout << ex.what() << '\n';
        cout<<"Error number: "<<  ex.getErrorCode() << endl;
    }

    conn->terminateStatement (stmt);
    
}
//------------------------------------------------------------------------------
// main
//------------------------------------------------------------------------------
int main(void)
{
    cout<<"OCCI TEST(¿À¶óÅ¬ 12c)"<<endl;
    bool ok = false;
    ok = connect();
    if(ok)
    {
        //occiInset();
        occiUpdate();
        //occiDelete();
    }


    // oracle db disconnection
    env->terminateConnection (conn);
    Environment::terminateEnvironment (env);
    return 0;
}