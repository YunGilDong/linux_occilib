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
#include <typeinfo>


using namespace oracle::occi;
using namespace std;

#ifdef __GNUG__ // GCC

#include <cxxabi.h>
#include <cstdlib>

static std::string readable_name( const char* mangled_name )
{
    int status ;
    char* temp = __cxxabiv1::__cxa_demangle( mangled_name, nullptr, nullptr, &status ) ;
    if(temp)
    {
        std::string result(temp) ;
        std::free(temp) ;
        return result ;
    }
    else return mangled_name ;
}

#else // not GCC

inline std::string readable_name( const char* mangled_name ) { return mangled_name ; }

#endif // __GNUG__

template < typename T > std::string type_to_string()
{ return readable_name( typeid(T).name() ) ; }

template < typename T > std::string type_to_string( const T& obj )
{ return readable_name( typeid(obj).name() ) ; }

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
int occiPrcProcd(void)
{
    bool ok = true;
    int o_rst=0;
    string o_msg="";
    double dval;
    char ch1;
    unsigned char uch1;

    string strType = "";
    strType = typeid(dval).name();
    cout<<type_to_string(1234)<<endl;
    cout<<type_to_string("1234")<<endl;
    cout<<type_to_string(string("1234"))<<endl;
    cout<<type_to_string(dval)<<endl;
    cout<<type_to_string(ok)<<endl;
    cout<<type_to_string(o_msg)<<endl;
    cout<<type_to_string(ch1)<<endl;
    cout<<type_to_string(uch1)<<endl;



    cout<<"OCCI PrcPrcd"<<endl;
    // 1(tramID): in, [2, 3] : out , 2:rstCode, 3:message
    string query="BEGIN PRC_TEST01(:1, :2, :3); END;";
    ResultSet *rset;
    try
    {        
        stmt = conn->createStatement (query);    
        stmt->setInt (1, 100000001);        
        // stmt->registerOutParam(2, OCCIINT, sizeof(o_rst), "TRAMTEST");     // out param (rst code)
        // stmt->registerOutParam(3, OCCISTRING, sizeof(o_msg), "TRAMTEST");     // out param (rst msg)
        stmt->registerOutParam(2, OCCIINT, sizeof(o_rst));     // out param (rst code)
        stmt->registerOutParam(3, OCCISTRING, 1024);     // out param (rst msg)
                
        rset = stmt->executeQuery ();
        cout<<"query : "<<query<<endl;        
        if(!stmt->isNull(2))    cout <<"rst code : "<< stmt->getInt(2) << endl;
        if(!stmt->isNull(3))
        {
            string msg = stmt->getString(3);
            cout <<"rst msg  : "<< msg <<", LEN : "<<msg.length()<< endl;    
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
        occiPrcProcd();
    }


    // oracle db disconnection
    env->terminateConnection (conn);
    Environment::terminateEnvironment (env);
    return 0;
}