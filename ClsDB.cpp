#include "ClsOcci.h"

using namespace std;
OCCIDB_DESC db_desc = {"TRAMTEST", "TRAMTEST", "TRdb"};

int main(void)
{
    ClsOcci MDB("MDB", &db_desc);
    
    cout << endl;
    cout << "OCCI CLSDB test..." << endl;

    try
    {
        MDB.Connect();

        char blobaa[10];
        MDB.SetStatement("SELECT * FROM TRAM");               
        cout<<"SELECT * FROM TRAM"<<endl;
        if(MDB.Execute())
        {
            while (MDB.rset->next()) {         
                cout <<"ID : "<< MDB.rset->getInt(1) << endl;
                cout <<"NM : "<< MDB.rset->getString(10).c_str() << endl;
            }            
            MDB.ClearResultSet();        
        }
        MDB.ClearStatement();
        

        MDB.SetStatement("SELECT * FROM TRAM WHERE TRAM_ID = 100000001");
        cout<<"SELECT * FROM TRAM WHERE TRAM_ID = 100000001"<<endl;
        if(MDB.Execute())
        {
            while (MDB.rset->next()) {         
                cout <<"ID    : "<< MDB.rset->getInt(1) << endl;
                cout <<"RMARK : "<< MDB.rset->getString(10) << endl;
            }
            MDB.ClearResultSet();        
        }
        MDB.ClearStatement();

        MDB.SetStatement("SELECT * FROM TRAM WHERE TRAM_ID = 100000002");
        cout<<"SELECT * FROM TRAM WHERE TRAM_ID = 100000002"<<endl;
        if(MDB.Execute())
        {
            while (MDB.rset->next()) {         
                cout <<"ID    : "<< MDB.rset->getInt(1) << endl;
                cout <<"RMARK : "<< MDB.rset->getString(10) << endl;
            }
        }

        // string sqlIns = "INSERT INTO TRAMTEST.TRAM ( \
        //                 TRAM_ID, UPDATE_DATE, RMARK) \
        //                 VALUES (:pid, sysdate, :prmark)";
        // MDB.SetStatement(sqlIns);         
        
        // MDB.SetInt (1, 9999);
        // MDB.SetString (2, "TEST01");         
        // if(MDB.Execute())
        // {
        //     cout<<"insert success\n";
        //     MDB.ClearResultSet();
        // }      
        // MDB.ClearStatement();

        string sqlupd = "UPDATE TRAM \
                        SET    UPDATE_DATE  = sysdate \
                               ,TRAM_NUM     = :TRAM_NUM \
                        WHERE  TRAM_ID      = :TRAM_ID";
        MDB.SetStatement(sqlupd);         
        
        MDB.SetInt (1, 9999);
        MDB.SetInt (2, 9999);
        if(MDB.Execute())
        {
            cout<<"update success\n";
            MDB.ClearResultSet();
        }      
        MDB.ClearStatement();


        cout<<"OCCI PrcPrcd"<<endl;
        int o_rst;
        // 1(tramID): in, [2, 3] : out , 2:rstCode, 3:message
        string query="BEGIN PRC_TEST01(:1, :2, :3); END;";
        MDB.SetStatement(query);    
        MDB.SetInt (1, 100000001);        
        MDB.stmt->registerOutParam(2, OCCIINT, sizeof(o_rst));     // out param (rst code)
        MDB.stmt->registerOutParam(3, OCCISTRING, 1024);     // out param (rst msg)

        if(MDB.Execute())
        {
            if(!MDB.stmt->isNull(2))    cout <<"rst code : "<< MDB.stmt->getInt(2) << endl;
            if(!MDB.stmt->isNull(3))
            {
                string msg = MDB.stmt->getString(3);
                cout <<"rst msg  : "<< msg <<", LEN : "<<msg.length()<< endl;    
            }    
        }
        MDB.ClearStatement();


        MDB.SetStatement("SELECT * FROM TRAM");               
        cout<<"SELECT * FROM TRAM"<<endl;
        if(MDB.Execute())
        {
            while (MDB.rset->next()) {         
                cout <<"ID : "<< MDB.rset->getInt(1) << endl;
                cout <<"NM : "<< MDB.rset->getString(10).c_str() << endl;
            }            
            MDB.ClearResultSet();        
        }
        MDB.ClearStatement();

    }
    catch(SQLException ex)    
    {     
        cout<<MDB.strExcepMsg1.str()<<endl;
        cout<<MDB.strExcepMsg2.str()<<endl;
        
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line "<< __LINE__ << endl;
        cout << ex.what() << '\n';
        cout<<"Error number: "<<  ex.getErrorCode() << endl;
    }    

    return 0;
}