/*
 * MMCMessage.hpp
 *
 *  Created on: 7/8/2011
 *      Author: dmitryb
 *      Update: Haim H. 03Mar2015 Changes for support Multi type of OS.
 *              0.4.0 Updated 11Sep2017 Haim H.
 */

#ifndef CMMCMESSAGE_HPP_
#define CMMCMESSAGE_HPP_
//
#include "MMC_definitions.h"
//
#define MAX_CHARACTERS_IN_LINE      400

//#define DEFAULT_MESSAGE_FILE_NAME   "/var/MMC/config/resources/Personality.xml\0"
static char default_message_file_name[] = "/var/MMC/config/resources/Personality.xml\0";
#define DEFAULT_MESSAGE_FILE_NAME &default_message_file_name[0]

using namespace std;
//
typedef enum
{
    MT_UNKNOWN_ERROR,
    MT_GMAS_ERROR,
    MT_LIB_ERROR,
    MT_PROFILER_ERROR,
    MT_PROFILER_WARNING,
    MT_GMAS_WARNING,
} MMCPP_MESSAGE_TYPE;
//
typedef enum
{
    HT_UNKNOWN_HEADER,
    HT_ERROR_STRING_HEADER,
    HT_ID_HEADER,
    HT_TEXT_HEADER,
    HT_RESOLUTION_HEADER,
    HT_FINISH_HEADER,
    HT_ERROR_IN_XML
} MMCPP_HEADER_TYPE;
//
typedef enum
{
    CT_UNKNOWN,
    CT_IPC,
    CT_RPC
} MMCPP_CONN_TYPE;
//
//
class DLLMMCPP_API CMMCMessage {
    //
public:
    //
    CMMCMessage()
    {
        bFOUND = false;
        iErrorID = 0;
        iRetval = 0;
        eConnectionType = CT_UNKNOWN;
        eCurrentHeaderType = HT_UNKNOWN_HEADER;
        eCurrentMessageType = MT_UNKNOWN_ERROR;
    }
    ~CMMCMessage()
    {
    }
    //
    string  GetMessage(){return sMessageFileName;}
    string  GetMessageFileName(){return sMessageFileName;}
    void    SetMessageFileName(string sMessageFileName_IN){sMessageFileName = sMessageFileName_IN;}
    void    SetMessageFileName(ELMO_PINT8 cMessageFileName_IN){sMessageFileName.insert(0,cMessageFileName_IN,strlen(cMessageFileName_IN));}  
    //
    void    MessageHandler(int iRetval,int iErrorID);
    //

private:
    // Internal variables for message throw mechanism
    string              sMessageFileName;
    string              sMessage;
    ELMO_BOOL            bFOUND;
    ELMO_INT32           iErrorID;
    ELMO_INT32           iRetval;
    MMCPP_CONN_TYPE     eConnectionType;
    MMCPP_HEADER_TYPE   eCurrentHeaderType;
    MMCPP_MESSAGE_TYPE  eCurrentMessageType;
    //
    //
    void    GetAndPrintMessage(fstream &pFile);
    void    ParseMessage(fstream &pFile);
    void    UpdateMessageType();
    void    OpenMessageFile(fstream &pFile, ELMO_PINT8 cFileName = DEFAULT_MESSAGE_FILE_NAME);
    void    CloseMessageFile(fstream &pFile);
    //
};
//
#endif /* CMMCMESSAGE_HPP_ */

