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
        cout << ex.what() << '\n';
        cout<<"Error number: "<<  ex.getErrorCode() << endl;
    } 
  
    return (ok);
}

//------------------------------------------------------------------------------
// main
//------------------------------------------------------------------------------
int main(void)
{
    cout<<"OCCI TEST"<<endl;
    connect();

    // oracle db disconnection
    env->terminateConnection (conn);
    Environment::terminateEnvironment (env);
    return 0;
}