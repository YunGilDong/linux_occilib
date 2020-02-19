//------------------------------------------------------------------------------
//
// Project:		General
// Target:		libGeneral.a
// Filename:	ClsOcci.cpp
// Version:		1.1.1.0
//
// History:
//	Date		Who	Rev		Content
//	----------	---	-------	------------------------------------------------
//
//------------------------------------------------------------------------------
// Include
//------------------------------------------------------------------------------
#pragma	hdrstop
#include "ClsOcci.h"
//------------------------------------------------------------------------------
// ClsOcci
//------------------------------------------------------------------------------
ClsOcci::ClsOcci(void)
{
    Init(NULL);
}
//------------------------------------------------------------------------------
ClsOcci::ClsOcci(const char *pName, OCCIDB_DESC *pDesc)
{
    Init(pDesc);
}
//------------------------------------------------------------------------------
ClsOcci::ClsOcci(const char *pName, string user, string password, string sid, bool connect)
{
    OCCIDB_DESC	desc;
	
	desc.user = user;
	desc.password = password;
	desc.sid = sid;
	Init(&desc, connect);
}
//------------------------------------------------------------------------------
// ClsOcci
//------------------------------------------------------------------------------
ClsOcci::~ClsOcci(void)
{
    Disconnect();
}
//------------------------------------------------------------------------------
// ClsOcci
//------------------------------------------------------------------------------
bool ClsOcci::Init(OCCIDB_DESC *pDesc, bool connect)
{
    rset = NULL;
    stmt = NULL;

    if (pDesc != NULL)
	{
	    m_desc.sid = pDesc->sid;
	    m_desc.user = pDesc->user;
	    m_desc.password = pDesc->password;		
	}
	else
	{
	    m_desc.sid = "";
	    m_desc.user = "";
	    m_desc.password = "";		
	}
    m_state = dsDisconnected_occi;

   	return(connect ? Connect() : true);
}
//------------------------------------------------------------------------------
// ClsOcci
//------------------------------------------------------------------------------
bool ClsOcci::Connect(void)
{
    bool ok = true;
    try
    {
        env = Environment::createEnvironment (Environment::DEFAULT);
        conn = env->createConnection (m_desc.user, m_desc.password, m_desc.sid);
        cout<<"Database connection success"<<endl;
        m_state = dsConnected_occi;
    }
    catch(SQLException ex)
    {
        strErrCode.clear();
        
        ok = false;        
        m_state = dsDisconnected_occi;              
        std::stringstream strSqlExcep;
        strErrCode<<ex.getErrorCode();
        strSqlExcep<< "# ERR: SQLException in " << __FILE__<< "(" << __FUNCTION__ << ") on line "<< __LINE__;
        ProcessException(strSqlExcep.str(), ex);
        throw ex;
    } 
  
    return (ok);

}
//------------------------------------------------------------------------------
// ClsOcci
//------------------------------------------------------------------------------
void ClsOcci::Disconnect(void)
{
    if(m_state == dsDisconnected_occi)
        return ;

    //Close();      
    env->terminateConnection (conn);
    Environment::terminateEnvironment (env);    
}
//------------------------------------------------------------------------------
// ClsOcci
//------------------------------------------------------------------------------
bool ClsOcci::Execute()
{
    bool ok  = true;
    // if(rset != NULL)
    // {
    //     stmt->closeResultSet (rset);
    //     rset = NULL;
    // }
    try
    {
        rset = stmt->executeQuery();
    }
    catch(SQLException ex)
    {
        strErrCode.clear();
        
        ok = false;        
        std::stringstream strSqlExcep;
        strErrCode<<ex.getErrorCode();
        strSqlExcep<< "# ERR: SQLException in " << __FILE__<< "(" << __FUNCTION__ << ") on line "<< __LINE__;
        ProcessException(strSqlExcep.str(), ex);
        throw ex;
    } 
    return (ok);
}
//------------------------------------------------------------------------------
// ClsOcci
//------------------------------------------------------------------------------
void ClsOcci::SetStatement(string query)
{    
    try
    {
        stmt = conn->createStatement (query);     
    }
    catch(SQLException ex)
    {
        strErrCode.clear();
        
        std::stringstream strSqlExcep;
        strErrCode<<ex.getErrorCode();
        strSqlExcep<< "# ERR: SQLException in " << __FILE__<< "(" << __FUNCTION__ << ") on line "<< __LINE__;
        ProcessException(strSqlExcep.str(), ex);
        throw ex;
    } 
}
//------------------------------------------------------------------------------
// SetBlob
//------------------------------------------------------------------------------
void ClsOcci::SetBlob (int index, unsigned char* buf, int size)
{
    //Blob blob = new Blob(conn);
    Blob blob(conn);
    blob.open(OCCI_LOB_READWRITE);
    blob.writeChunk(BLOB_BUF_SIZE, buf, size);

    stmt->setBlob(index, blob);
}
//------------------------------------------------------------------------------
// SetFloat
//------------------------------------------------------------------------------
void ClsOcci::SetFloat(int index, float value)
{
    stmt->setFloat(index, value);
}
//------------------------------------------------------------------------------
// SetDouble
//------------------------------------------------------------------------------
void ClsOcci::SetDouble (int index, double value)
{
    stmt->setDouble(index, value);
}
//------------------------------------------------------------------------------
// SetInt
//------------------------------------------------------------------------------
void ClsOcci::SetInt (int index, int value)
{
    stmt->setInt(index, value);
}
//------------------------------------------------------------------------------
// SetNull
//------------------------------------------------------------------------------
void ClsOcci::SetNull (int index, Type type)
{
    stmt->setNull(index, type);
}
//------------------------------------------------------------------------------
// SetString
//------------------------------------------------------------------------------
void ClsOcci::SetString (int index, const char *value)
{
    stmt->setString(index, value);
}
//------------------------------------------------------------------------------
// Close
//------------------------------------------------------------------------------
void ClsOcci::Close(void)
{
    stmt->closeResultSet (rset);  
    conn->terminateStatement (stmt);    
}
//------------------------------------------------------------------------------
// ClearResultSet
//------------------------------------------------------------------------------
void ClsOcci::ClearResultSet(void)
{
    stmt->closeResultSet (rset);
}
//------------------------------------------------------------------------------
// ClearStatement
//------------------------------------------------------------------------------
void ClsOcci::ClearStatement(void)
{
    conn->terminateStatement (stmt);    
}
//------------------------------------------------------------------------------
// ProcessException
//------------------------------------------------------------------------------
void ClsOcci::ProcessException(string msg,SQLException e)
{
    strExcepMsg1.clear();
    strExcepMsg2.clear();

    strExcepMsg1<<msg;
    strExcepMsg2<< "# ERR: " << e.what()<< " (oracle error code: " <<"Error number: "<<  e.getErrorCode() <<")"<<endl;
}
//------------------------------------------------------------------------------
// End of ClsOcci.cpp
//------------------------------------------------------------------------------