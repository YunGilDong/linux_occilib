//------------------------------------------------------------------------------
//
// Project:		General
// Target:		libGeneral.a
// Filename:	ClsOcci.h
// Version:		1.1.1.0
// History:		Date		By		Content
//				----------	------	--------------------------------------------
// 
//------------------------------------------------------------------------------
#ifndef	ClsOcciH
#define	ClsOcciH
//------------------------------------------------------------------------------
#include <iostream>
#include <occi.h>
#include <streambuf>
#include <sstream>
//------------------------------------------------------------------------------
using namespace oracle::occi;
using namespace std;
//------------------------------------------------------------------------------
// Costant
//------------------------------------------------------------------------------
#define BLOB_BUF_SIZE   1024
//------------------------------------------------------------------------------
// Type Definition
//------------------------------------------------------------------------------
// DB_STATE
//------------------------------------------------------------------------------
typedef enum {dsDisconnected_occi = 0, dsConnected_occi, dsConnecting_occi}	DB_STATE_OCCI;
//------------------------------------------------------------------------------
// OCCIDB_DESC
//------------------------------------------------------------------------------
typedef struct
{	
	string	user;		// user id
	string	password;	// user password
	string	sid;	    // database SID
} OCCIDB_DESC;

#define	OCCIDB_DESC_SIZE		sizeof(OCCIDB_DESC)
//------------------------------------------------------------------------------
// Class
//------------------------------------------------------------------------------
class ClsOcci
{
private:
    OCCIDB_DESC	m_desc;
    DB_STATE_OCCI	m_state;
    Environment *env;
    Connection *conn;

    // void Close(void);
    void ProcessException(string msg, SQLException e);    
public:
    ResultSet *rset;
    Statement *stmt;
    std::stringstream strExcepMsg1; 
    std::stringstream strExcepMsg2; 
    std::stringstream strErrCode;

    ClsOcci(void);
    ClsOcci(const char *pName, OCCIDB_DESC *pDesc);
    ClsOcci(const char *pName, string user, string password, string sid, bool connect = true);
    virtual ~ClsOcci(void);

    bool Init(OCCIDB_DESC *pDesc, bool connect = false); 
    bool Connect(void);
    void Disconnect(void);
    bool Execute();
    void SetStatement(string query);

    void SetBlob(int index, unsigned char* buf, int size);
    void SetFloat(int index, float value);
    void SetDouble(int index, double value);
    void SetInt(int index, int value);
    void SetNull(int index, Type type);
    void SetString(int index, const char *value);

    void Close(void);
    void ClearResultSet(void);
    void ClearStatement(void);
};
#endif  // ClsOcciH
//------------------------------------------------------------------------------
// End of ClsOcci.h
//------------------------------------------------------------------------------