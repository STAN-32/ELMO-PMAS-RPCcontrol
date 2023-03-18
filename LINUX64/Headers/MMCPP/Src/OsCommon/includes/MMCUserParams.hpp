// *
// * MMCUserParams.hpp
// *
// * Created on: 09/04/2013
// *     Update: 30Oct2013
// *     Update: 30Jul2017  Update D_MIN D_MAX LONG_MIN LONG_MAX
// *     Author: HaimH
// *     Update: Haim H. 03Mar2015 Changes for support Multi type of OS.
// *
// * Description:
// * ============
// * Group of methods for save and retrieve GMAS data (E.g. GMAS Parameters: Velocity, Acceleration, Location-points...).
// * An XML concept are using for managing this Gmas data.
// * Synopsis for the using XML structure:
// *        XML tree structure,
// *            highest element are absolutly predefine,
// *            first (highest) element define the XML version should use for point how to read the tree.
// *            Second elemet is the root of the tree and describe the XML Schema origin used for build the tree.
// *            This second element has user define name for point on the XMD file.
// *        Two above elements should always exist even them data are not in use and not interesting the user,
// *        in such case the names of XMD file for second element are "just and only name".
// *        The next Element NAME (under the "root") is fix and is CATEGORY, it has user define Value (ATTRIBUTE Value).
// *      Element NAME under CATEGORY elements name is RESOURCES, it has user define Value (ATTRIBUTE Value)
// *        Element NAME under RESOURCES elements name is a user define and its Data is also user deliver Value.
// *
// * Using concept:
// * ==============
// * The packages methodss are working on Ram's XML tree.
// * Ram's XML tree can be builds by in two different ways:
// *    1. Reading "well format XML file" [use the Open() function] 
// *    2. From scratch [use PutXmlFileRoot() function].
// * Once XML tree exist in Ram the package methods are ready for retrieve (Read(), ReadAr() functions) or update, modify,
// * add-new elements [Write(), WriteAr() functions].
// * Along every state of XMLs lives tree, its possible print the tree to STD OUT [by PrintTreeToStdout() function]
// * or save it to file [by Save() function].
// * When XML tree is not interesting anymore it's resource should free by calling Close() only then it possible call
// * again to open (create Ram tree from file) or PutXmlFileRoot (create Ram tree from scratch).
// * After Close() there is no Ram XML tree anymore and Open() or PutXmlFileRoot() function should be call.
// * Many functions parameters have default value.
// * When calling to 'Write/Arr(level1Val, level2Val, level3Name, level3Val)' functions:
// *        if element /CATEGORY='level1Val' is missing it creating and under it adding /RESOURCES=level2Val/level3Name=level3Val/
// *      else if missing .../RESOURCES='level2Val'/, RESOURCES='level2Val'/level3Name=level3Val/ is creating,
// *        else if missing /level3Name=..., /level3Name=level3Val is creating.
// *        else if .../level3Name=XYZ is exist it modifay to /level3Name=level3Val/
// * 
// * Tips:
// * =====
// *    1. Default Open() file name is different from default files name for Save(), both are hard coded
// *        and pointing by DEFAULT_XML_RFILE_NAME and DEFAULT_XML_WFILE_NAME symbols.
// *        this files default path define by DEFAULT_XML_RFILE_PATH and DEFAULT_XML_WFILE_PATH (also hard coded).
// *  2. "Speak level" for trace and debug can be set in consteructor or by emplicied call to setSpeakDbgLvl(uiSpeak_lvl)
// *  3. PutXmlFileDescrp(pAtt1, pAtt2) / GetXmlFileDescrp(pAtt1, pAtt2) are for set and retrive user element has user data
// *        <FILE_DESCRIPTION NAME="pAtt1" VERSION="pAtt2" />
// *  4. Special meaning character are converting to sequnce of character, E.g: apostrophe=' convert to &apos; the full convert
// *        table apear in RAPID XML definitions.
// *  5. Boolean variable value apear in XML file as /true/false/
// *    6. XML file used in open is close just after the open and its ups to the user to deliver this same file in Save()
// *        which cause over write on origin read from file.
// * 
// * XML Data file Example:
// * ======================
// * <?xml version="1.0" encoding="utf-8"?>
// * <root xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:noNamespaceSchemaLocation="proposed.xsd">
// *    <FILE_DESCRIPTION NAME="Parameters" VERSION="NovaScan 1236" />
// *    <CATEGORY NAME="Profiler">        
// *        <RESOURCES NAME="a01">        
// *            <DC>10000000</DC>
// *            <JERK>1073742336</JERK>
// *            <DRIVE_ID>'81'</DRIVE_ID>
// *        </RESOURCES>
// *        <RESOURCES NAME="a02">        
// *            <AXIS_MODE>0</AXIS_MODE>
// *            <OP_MODE>8</OP_MODE>
// *        </RESOURCES>
// *    </CATEGORY >        
// *    <CATEGORY NAME="Communication">        
// *        <RESOURCES NAME="a01">        
// *            <TIMEOUT>0</TIMEOUT>
// *        </RESOURCES>
// *        <RESOURCES NAME="a02">        
// *            <TIMEOUT>0</TIMEOUT>
// *            <NUM_VARS>8</NUM_VARS>
// *        </RESOURCES>
// *    </CATEGORY >        
// * </root>
// *
// * Example 1: Scenario sequence - builds, read, print and save XML file from scrach:
// * =================================================================================
// * {
// *  MMCUserParams up;
// *
// *  lvl1AttVal = LVL1ATTVAL;
// *  lvl2AttVal = LVL2ATTVAL;
// *
// *                    /* Create new XML ram tree */
// *  ErrId = up.PutXmlFileRoot(XMLSchema, SchemaLocation);
// *                  /* Add to element with file discription and file version */
// *  ErrId = up.PutXmlFileDescrp("FileDiscrip HH file",    "Elmo ver 1234");
// *  ErrId = up.GetXmlFileDescrp (bufPrt_val, bufPrt_val1, bufPrt_valSize);
// *  printf("\n FileDescrp: =120===ErrId=%d ======<%s><%s> \n",  ErrId, bufPrt_val, bufPrt_val1);
// *
// *  pStr = "abc def";
// *  ErrId = up.Write (lvl1AttVal, lvl2AttVal, "S-AB", pStr, (long)(strlen(pStr)+1));
// *  ErrId = up.Read  (lvl1AttVal,     lvl2AttVal, "S-AB", bufPrt_val, bufPrt_valSize);
// *  printf("\n buf: =130===ErrId=%d =====Str=<%s> \n",  ErrId, bufPrt_val);
// * 
// *  ErrId = up.Write (lvl1AttVal, lvl2AttVal, "S-AB", 56.78);
// *  ErrId = up.Read  (lvl1AttVal,     lvl2AttVal, "S-AB", bufPrt_val, bufPrt_valSize);
// *  printf("\n buf: =131===ErrId=%d =====Str=<%s> \n",  ErrId, bufPrt_val);
// * 
// *  pStr = "GHI JKLM";
// *  ErrId = up.Write (lvl1AttVal, lvl2AttVal, "S-AB", pStr, (long)(strlen(pStr)+1));
// *  ErrId = up.Read  (lvl1AttVal,     lvl2AttVal, "S-AB", bufPrt_val, bufPrt_valSize);
// *  printf("\n buf: =132===ErrId=%d =====Str=<%s> \n",  ErrId, bufPrt_val);
// * 
// *  ErrId = up.Write (lvl1AttVal, lvl2AttVal, "S-AB", 34.786);
// *  ErrId = up.Read  (lvl1AttVal,     lvl2AttVal, "S-AB", bufPrt_val, bufPrt_valSize);
// *  printf("\n buf: =131===ErrId=%d =====Str=<%s> \n",  ErrId, bufPrt_val);
// *
// *                            /* Write/read array element of double values */
// *  lvl3Name   = LVL3NAME;
// *  dVal[0] = 12.34;
// *  dVal[1] = 56.78;
// *  dVal[2] = 90.12;
// *  dVal[3] = 34.56;
// *  iReqRdElm = 4;
// *  ErrId = up.WriteArr(lvl1AttVal,lvl2AttVal,  lvl3Name, dVal,  iReqRdElm);
// *  ErrId = up.Read    (lvl1AttVal, lvl2AttVal, lvl3Name, bufPrt_val, bufPrt_valSize);
// *  ErrId = up.ReadArr(lvl1AttVal,    lvl2AttVal, lvl3Name, dVal, (double)def, iActRdElm, iReqRdElm, (double)min, (double)max);
// *  printf("\n buf (Array) : =190-1=ErrId=%d ===%s=<%s> \n",  ErrId, lvl3Name, bufPrt_val);
// *  printf("\n Array double: =190-2 #Act=%d, #Req=%d =ErrId=%d =====%s=", iActRdElm, iReqRdElm, ErrId, lvl3Name);
// *  for (ind=0; ind < (int)iReqRdElm; ind++)
// *    printf("<%f> ", dVal[ind]);
// *  printf("\n");
// *                    /* Print the current XML tree to screen under tile */
// *  up.PrintTreeToStdout("\n\t Current state of XML tree(B4 ) \n\t ============================== \n");
// *                    /* Save the builds tree to default file */
// *  ErrId = up.Save();
// *                    /* Close XML tree and release its resource */
// *  ErrId = up.Close();
// * }
// *  
// *  
// *  
// *  
// * Example 2: Scenario sequence - read Exist XMLs file, modifay, print and save it:
// *  ===============================================================================
// * {
// *  lvl1AttVal = LVL1ATTVAL;
// *  lvl2AttVal = LVL2ATTVAL;
// *  lvl3Name   = LVL3NAME;
// *   
// *  ErrId = up.Open(paramFileName, UPXML_SET_DEF_REQ_FLG);
// *                  /* Change Speak Level from def. init. */
// *  up.setSpeakDbgLvl(SPK_LVL_INFO);
// *                    /* print the original XML file to screen */
// *  up.PrintTreeToStdout("\n\t Current state of XML tree(B4 ) \n\t ============================== \n");
// *                    /* Retrive original roots values */
// *  ErrId = up.GetXmlFileRoot (bufPrt_val, bufPrt_val1, bufPrt_valSize);
// *  printf("\n Root: =260===ErrId=%d ======<%s><%s> \n",  ErrId, bufPrt_val, bufPrt_val1);
// *                    /* Retrive original file Description */
// *  ErrId = up.GetXmlFileDescrp (bufPrt_val, bufPrt_val1, bufPrt_valSize);
// *  printf("\n FileDescrp: =270===ErrId=%d ======<%s><%s> \n",  ErrId, bufPrt_val, bufPrt_val1);
// *
// *  ErrId = up.Read  (lvl1AttVal,     lvl2AttVal, lvl3Name, bufPrt_val, bufPrt_valSize);
// *  printf("\n buf: =280===ErrId=%d ======%s=<%s> \n",  ErrId, lvl3Name, bufPrt_val);
// *                    /* Modifay the Ram tree */
// *  ErrId = up.Write (lvl1AttVal, lvl2AttVal, lvl3Name,   33.44);
// *  ErrId = up.Read  (lvl1AttVal,     lvl2AttVal, lvl3Name, bufPrt_val, bufPrt_valSize);
// *  printf("\n buf: =290===ErrId=%d ======%s=<%s> \n",  ErrId, lvl3Name, bufPrt_val);
// *                    /* Modifay exist element value */
// *  pStr = "Haim Hillel";
// *  ErrId = up.Write (lvl1AttVal, lvl2AttVal, lvl3Name, pStr, (long)(strlen(pStr)+1));
// *  ErrId = up.Read  (lvl1AttVal,     lvl2AttVal, lvl3Name, bufPrt_val, bufPrt_valSize);
// *  printf("\n buf: =300===ErrId=%d ======%s=<%s> \n",  ErrId, lvl3Name, bufPrt_val);
// *
// *                    /* Modifay exist element value */
// *  pStr = "1234.5678901234";
// *  ErrId = up.Write (lvl1AttVal, lvl2AttVal, lvl3Name,   pStr, (long)(strlen(pStr)+1));
// *  dVal[0] = -1;
// *  ErrId = up.Read  (lvl1AttVal,     lvl2AttVal, lvl3Name, dVal[0], (double)def,  (double)min, (double)max);
// *  printf("\n double: 310=ErrId=%d ======%s=<%f> \n",  ErrId, lvl3Name, dVal[0]);
// *
// *  lVal[0] = -1;
// *  ErrId = up.Read  (lvl1AttVal,     lvl2AttVal, lvl3Name, lVal[0], (long)def, (long)min, (long)max);
// *  printf("\n long: =320===ErrId=%d ======%s=<%ld> \n",  ErrId, lvl3Name, lVal[0]);
// *
// *  ErrId = up.Write (lvl1AttVal, lvl2AttVal, lvl3Name, 234L);
// *  ErrId = up.Read  (lvl1AttVal,     lvl2AttVal, lvl3Name, lVal[0], (long)def, (long)min, (long)max);
// *  printf("\n long: =340===ErrId=%d ======%s=<%ld> \n",  ErrId, lvl3Name, lVal[0]);
// *
// *  ErrId = up.Read  (lvl1AttVal,     lvl2AttVal,     lvl3Name, bVal, 0);
// *  printf("\n Boolean: =350 def 0 =ErrId=%d =====%s=<%d> \n",  ErrId, lvl3Name, bVal);
// *
// *  ErrId = up.Read  (lvl1AttVal,     lvl2AttVal,     lvl3Name, bVal, 1);
// *  printf("\n Boolean: =360 def 1 =ErrId=%d =====%s=<%d> \n",  ErrId, lvl3Name, bVal);
// *
// *  ErrId = up.Write(lvl1AttVal,  lvl2AttVal,     lvl3Name,   (bool)0);
// *  ErrId = up.Read  (lvl1AttVal,     lvl2AttVal,     lvl3Name, bVal, (bool)1);
// *  printf("\n Boolean: =370 def 1 =ErrId=%d =====%s=<%d> \n",  ErrId, lvl3Name, bVal);
// *
// *  up.PrintTreeToStdout("\n\t Current state of XML tree(Aft) \n\t ============================== \n");
// *
// *  iReqRdElm = 4;
// *  ErrId = up.ReadArr(lvl1AttVal,    lvl2AttVal, lvl3Name, dVal, (double)def, iActRdElm, iReqRdElm, (double)min, (double)max);
// *  printf("\n Array double: =380 #Act=%d, #Req=%d =ErrId=%d =====%s=", iActRdElm, iReqRdElm, ErrId, lvl3Name);
// *  for (ind=0; ind < (int)iReqRdElm; ind++)
// *        printf("<%f> ", dVal[ind]);
// *  printf("\n");
// *
// *  dVal[0] = 12.34;
// *  dVal[1] = 56.78;
// *  dVal[2] = 90.12;
// *  dVal[3] = 34.56;
// *  ErrId = up.WriteArr(lvl1AttVal,   lvl2AttVal, lvl3Name, dVal,  iReqRdElm);
// *  ErrId = up.ReadArr(lvl1AttVal,    lvl2AttVal, lvl3Name, dVal, (double)def, iActRdElm, iReqRdElm, (double)min, (double)max);
// *  printf("\n Array double: =390 #Act=%d, #Req=%d =ErrId=%d =====%s=", iActRdElm, iReqRdElm, ErrId, lvl3Name);
// *  for (ind=0; ind < (int)iReqRdElm; ind++)
// *        printf("<%f> ", dVal[ind]);
// *  printf("\n");
// *
// *  up.PrintTreeToStdout("\n 520 0000000000000000 \n ==================== \n ");
// *  ErrId = up.Save();
// *
// *  up.Close();
// * }
// *
// *
//
#ifndef MMCUSERPARAMS_HPP_
#define MMCUSERPARAMS_HPP_
//
//
//
#include "MMCPPGlobal.hpp"
                                            /* Min & Max values for Double number.      */
#define L_DBL_MAX               (1E+37)
#define L_DBL_MIN               (-L_DBL_MAX)

#define L_LONG_MAX              2147483647L
#define L_LONG_MIN              (-L_LONG_MAX - 1L)

											/* Max allow write array size - 16M */
#define MAX_WRITE_ARR_SIZE		(0x1000000)

                                            /* Max file name len including path (read or write) */
#define MAX_XML_FILE_NAME_LEN   64
                                            /* Default file name for Read/Write from/To */
#define DEFAULT_XML_RFILE_NAME  "UserParamsR.xml"
#define DEFAULT_XML_WFILE_NAME  "UserParamsW.xml"
                                            /* Default path for Read/Write from/To file */
#define DEFAULT_XML_RFILE_PATH  "/mnt/jffs/usr/"
#define DEFAULT_XML_WFILE_PATH   DEFAULT_XML_RFILE_PATH
//
#define UPXML_DEF_ROOT_ATT1     "http://www.w3.org/2001/XMLSchema-instance"
#define UPXML_DEF_ROOT_ATT2     "proposed.xsd"
//
#define TAG_NAME_LVL1           "CATEGORY"
#define TAG_NAME_LVL2           "RESOURCES"
#define ATTRIBUTE_LVL1_NAME     "NAME"
#define ATTRIBUTE_LVL2_NAME     "NAME"
//
#define TRUE_FILE_STRING        "true"
#define FALSE_FILE_STRING       "false"
//
                                            /* BitWise Flag for open 'uiFlags' param    */
                                            /* Requst Setting default Val.              */
                                            /* When entry entry not found or when not   */
                                            /* in range.                                */
#define UPXML_SET_DEF_REQ_FLG   0x00000001
                                            /* Values for 'setSpeakDbgLvl(uiSpeak_lvl)' */
                                            /* Flags (Hierarchy) for print to consol:   */
#define SPK_LVL_NONE            0x0000      /* Silince-No print, program not "speaking" */
#define SPK_LVL_ERROR           0x0010      /* Print error (only).                      */
#define SPK_LVL_INFO            0x0020      /* Print error and info.                    */
#define SPK_LVL_DBG             0x0040      /* Print error info and debug (max speaking)*/
//
                                            /* Whole possible data are printing.        */
                                            /* Also use as mask for get the SPK_LVL     */
#define SPK_LVL_WHOLE           0xffff
//
//COPIED from MMC_definitions.h:
//
//#define MMC_LIB_UPXML_ERROR                -3     ///< Error occurred on 'Get User Parameter from XML file'
//#define MMC_LIB_UPXML_WARNING              300    ///< Warning from 'get User Param from XML file library'
//
/////   Get User Parameter from XML file Errors code:
//#define   MMC_LIB_UPXML_FILE_FORMAT        (-3010)    /* XML file Syntax is not well form */
//#define MMC_LIB_UPXML_FAIL_ALLOC           (-3011)    /* Failed in allocation memory.     */
//#define MMC_LIB_UPXML_OPEN_FAILD           (-3012)    /* Failed in Open XML file.         */
//#define MMC_LIB_UPXML_LONG_NAME            (-3013)    /* File name (inc path) is too long */
//
//#define MMC_LIB_UPXML_NOT_FOUND            (-3020)    /* ENTRY NOT Found                  */   
//#define MMC_LIB_UPXML_UNEXP_CHR            (-3021)    /* Found but has Unexpected char    */
//#define MMC_LIB_UPXML_NOT_IN_RANGE         (-3022)    /* Found Value outside of Min Max   */
//
//
                                                        /* When changing this value concider it's effect on 'MAX_CHARS_FOR_NUM' */
#define SPRINTF_DEF_DOUBLE_FORMAT            "%12.6f"
                                                        /* This value should be at least the size implied from 'SPRINTF_DEF_DOUBLE_FORMAT'  */
#define MAX_CHARS_FOR_NUM                    20
//
class DLLMMCPP_API MMCUserParams
// =============================
{
public:
       MMCUserParams(
           ELMO_UINT32 uiDefSetReqFlg=UPXML_SET_DEF_REQ_FLG,   /* Mark use def. val. when not found entry on XML data  */
           ELMO_UINT32 uiSpeakFlag=SPK_LVL_ERROR);             /* Mark speak to consol the set level and below it.     */
//
    virtual ~MMCUserParams();
//
    /* ======================= */
    /* Read / Retrive XML tree */
    /* ======================= */
                    /* 'uiFlags' holding bit for return defaults value if entry is      */
                    /* missing or entry value not in range.                             */
                    /* Be aware: 1. Default file name for read is different from defautl*/
                    /* name for save. 2. Even if file is open for update it not save    */
                    /* on exit (or close) but with explicit save command.               */
    ELMO_INT32 Open(ELMO_PINT8 cFileName=(ELMO_PINT8)DEFAULT_XML_RFILE_NAME, ELMO_UINT32 uiFlags=UPXML_SET_DEF_REQ_FLG, ELMO_PINT8 cFilePath=(ELMO_PINT8)DEFAULT_XML_RFILE_PATH) throw (CMMCException);
//                  /* Free XML resource */
    ELMO_INT32 Close();
                            /* Functions for Read Single parameter value *\
                            \* ========================================= */
//
                    /* Return ONE parameter of type Double */
    ELMO_INT32 Read  (   ELMO_PINT8   pLvl1Valu,      ELMO_PINT8   pLvl2Valu,      ELMO_PINT8 pLvl3Name,
                        ELMO_DOUBLE  &dRetVal,       ELMO_DOUBLE  dDefault,
                        ELMO_DOUBLE  dMin=L_DBL_MIN,   ELMO_DOUBLE  dMax=L_DBL_MAX)               throw (CMMCException);
//
                    /* Return ONE parameter of type Long */
    ELMO_INT32 Read  (   ELMO_PINT8   pLvl1Valu,      ELMO_PINT8   pLvl2Valu,      ELMO_PINT8 pLvl3Name,
                        ELMO_LINT32  &lRetVal,       ELMO_LINT32  lDefault,
                        ELMO_LINT32  lMin=L_LONG_MIN,  ELMO_LINT32  lMax=L_LONG_MAX )             throw (CMMCException);
//
                    /* Return ONE parameter of type bool.               */
                    /* Ignore white space, expect True / False.         */
    ELMO_INT32 Read  (   ELMO_PINT8   pLvl1Valu,      ELMO_PINT8   pLvl2Valu,      ELMO_PINT8 pLvl3Name,
                        ELMO_BOOL    &bRetVal,       ELMO_BOOL    bDefault=0)                     throw (CMMCException);
//
                    /* Return ONE parameter of type string */
    ELMO_INT32 Read  (   ELMO_PINT8   pLvl1Valu,      ELMO_PINT8   pLvl2Valu,      ELMO_PINT8 pLvl3Name,
                        ELMO_PINT8   pStr,           ELMO_LINT32  lLen)                           throw (CMMCException);
//
                            /* Functions for Read Array of parameters values *\
                            \* ============================================= */
//
                    /* Return Array of parameter of type Double */
    ELMO_INT32 ReadArr(  ELMO_PINT8   pLvl1Valu,      ELMO_PINT8    pLvl2Valu,      ELMO_PINT8 pLvl3Name,
                        ELMO_DOUBLE  dRetVal[],      ELMO_DOUBLE   dDefault,
                        ELMO_UINT32& iActRdElm,      ELMO_UINT32   iReqRdElm=1,
                        ELMO_DOUBLE  dMin=L_DBL_MIN,   ELMO_DOUBLE   dMax=L_DBL_MAX)              throw (CMMCException);
//
                    /* Return Array of parameter of type Long */
    ELMO_INT32 ReadArr(  ELMO_PINT8   pLvl1Valu,      ELMO_PINT8    pLvl2Valu,      ELMO_PINT8 pLvl3Name,
                        ELMO_LINT32  lRetVal[],      ELMO_LINT32   lDefault,
                        ELMO_UINT32& iActRdElm,      ELMO_UINT32   iReqRdElm=1,
                        ELMO_LINT32  lMin=L_LONG_MIN,  ELMO_LINT32   lMax=L_LONG_MAX)             throw (CMMCException);
//
                            /* Functions Return XML file identifier *\
                            \* ==================================== */
                    /* Return the XML file root (xsi ID values) pAtt1 & xsi Location*/
                    /* (pAtt2). Buffer size for return values are at least lLen     */
                    /* Eg, for XML file line:                                       */
                    /*  <root xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" */
                    /*          xsi:noNamespaceSchemaLocation="proposed.xsd">       */
                    /* return:                                                      */
                    /* pAtt1 = "http://www.w3.org/2001/XMLSchema-instance"          */
                    /* pAtt2 = "proposed.xsd"                                       */
    ELMO_INT32 GetXmlFileRoot    (   ELMO_PINT8  pAtt1,  ELMO_PINT8 pAtt2,    ELMO_LINT32    lLen)  throw (CMMCException);
                    /* Return the XML "file description name" (pAtt1) and XML file  */
                    /* ver (pAtt2), buffers size for return values are at least lLen*/
    ELMO_INT32 GetXmlFileDescrp  (   ELMO_PINT8  pAtt1,  ELMO_PINT8 pAtt2,    ELMO_LINT32    lLen)  throw (CMMCException);
                    /* Set the print report (speak) level.       */
    void      setSpeakDbgLvl    (   ELMO_UINT32 uiSpeak_lvl);
                    /* Print parsed XML tree to stdout stream                       */
    ELMO_INT32 PrintTreeToStdout (   ELMO_PINT8 pcTitle=NULL);
//
    /* ======================== */
    /* Update/add XML Tree data */
    /* ======================== */
                            /* Functions Write XML file identifier *\
                            \* =================================== */
                    /* Create new XML tree in Ram. E.g when no file nore open...    */
                    /* with this function the user start build XML tree from scrach.*/
                    /* Shuld be the first write in sequnce of build new TREE.       */
                    /*                                                              */
                    /* Write (null terminated string) to XML file root (xsi ID      */
                    /* values) pAtt1 & xsi Location (pAtt2),                        */
                    /* Eg:                                                          */
                    /*      pAtt1 = "http://www.w3.org/2001/XMLSchema-instance"     */
                    /*      pAtt2 = "proposed.xsd"                                  */
                    /* Write XML file lines:                                        */
                    /*  <root xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" */
                    /*          xsi:noNamespaceSchemaLocation="proposed.xsd">       */
    ELMO_INT32 PutXmlFileRoot    (ELMO_PINT8 pAtt1=(ELMO_PINT8)UPXML_DEF_ROOT_ATT1, ELMO_PINT8 pAtt2=(ELMO_PINT8)UPXML_DEF_ROOT_ATT2)              throw (CMMCException);
                    /* Write (null terminated string) to XML "file description name"*/
                    /* (pAtt1) and XML file ver (pAtt2).                            */
    ELMO_INT32 PutXmlFileDescrp  (ELMO_PINT8 pAtt1,  ELMO_PINT8 pAtt2)                                                     throw (CMMCException);
                    /* Be aware: 1. Default file name for read is different from defautl*/
                    /* name for save. 2. File is open for update but not save on exit   */
                    /* (or close)  but with explicit save command.                      */
    ELMO_INT32 Save              (ELMO_PINT8 cFileName=(ELMO_PINT8)DEFAULT_XML_WFILE_NAME, ELMO_PINT8 cFilePath=(ELMO_PINT8)DEFAULT_XML_WFILE_PATH)throw (CMMCException);
                    /* Not supporing Yet: Delete Element of any type (if array all of its values). */
    ELMO_INT32 RemoveElem        (ELMO_PINT8 pLvl1Valu, ELMO_PINT8   pLvl2Valu,  ELMO_PINT8 pLvl3Name)                      throw (CMMCException);
                    /* Write ONE parameter of type Double   */
    ELMO_INT32 Write             (ELMO_PINT8 pLvl1Valu, ELMO_PINT8   pLvl2Valu,  ELMO_PINT8 pLvl3Name,  ELMO_DOUBLE  dWrVal) throw (CMMCException);
                    /* Write ONE parameter of type Long     */
    ELMO_INT32 Write             (ELMO_PINT8 pLvl1Valu, ELMO_PINT8   pLvl2Valu,  ELMO_PINT8 pLvl3Name,  ELMO_LINT32  lWrVal) throw (CMMCException);
                    /* Write ONE parameter of type bool.    */
    ELMO_INT32 Write             (ELMO_PINT8 pLvl1Valu, ELMO_PINT8   pLvl2Valu,  ELMO_PINT8 pLvl3Name,  ELMO_BOOL    bWrVal) throw (CMMCException);
                    /* Write ONE parameter of type string   */
    ELMO_INT32 Write             (ELMO_PINT8 pLvl1Valu, ELMO_PINT8   pLvl2Valu,  ELMO_PINT8 pLvl3Name,  ELMO_PINT8   pStr, ELMO_LINT32 lLen) throw (CMMCException);
//
                            /* Functions for Write Array of parameters values *\
                            \* ============================================== */
//
                    /* Write Array of parameter of type Double  */
    ELMO_INT32 WriteArr          (ELMO_PINT8  pLvl1Valu,  ELMO_PINT8   pLvl2Valu,  ELMO_PINT8   pLvl3Name,
                                 ELMO_DOUBLE dWrVal[],   ELMO_UINT32  iActWrElm)   throw (CMMCException);
                    /* Write Array of parameter of type Long    */
    ELMO_INT32 WriteArr          (ELMO_PINT8  pLvl1Valu,  ELMO_PINT8   pLvl2Valu,  ELMO_PINT8 pLvl3Name,
                                 ELMO_LINT32 lWrVal[],   ELMO_UINT32  iActWrElm)   throw (CMMCException);
                    /* Format for write double / float nuber    */
                    /* E.g: iFieldSize=8 iFractionSize=3 =>     */
                    /* format be: "%8.3f"                       */
                    /* Limitation: iFractionSize+1 < iFieldSize */
                    /*             iFractionSize + iFieldSize < */
                    /*                      MAX_CHARS_FOR_NUM   */
                    /*   other limits are according to Compiler */
                    /*      sprintf.                            */
    ELMO_INT32 PutFloatFormat(ELMO_UINT32 iFieldSize, ELMO_UINT32 iFractionSize);
//
//
private:
                    /* Bitwise flags, directs how to use default if the requsted value not found.   */
    ELMO_UINT32    m_uiDefSetReqFlg;
                    /* Hierarchy value for consol print, see constant symbols SPK_LVL_*             */
    ELMO_UINT32    m_uiSpeakDbgFlg;
//
                    /* Pointer holds copy of XML file in Ram */
    ELMO_PINT8     m_pXmlRamFileBuffer;
                    /* Pointers to root node (level0) */
    ELMO_PVOID     m_pDeepLvl0Nodes;
//
    ELMO_INT8      m_sprintfDoubleFormat  [30];
    ELMO_INT8      m_sprintfDoubleFormatAr[30];
//
    ELMO_INT32     getTagValue(ELMO_PINT8  pLvl1Valu,                 ELMO_PINT8  pLvl2Valu,           ELMO_PINT8 pLvl3Name, ELMO_PINT8* pBufPrt,
                              ELMO_PVOID* ppLvl1Nodes,               ELMO_PVOID* ppLvl2Nodes,         ELMO_PVOID* ppLvl3Nodes,
                              ELMO_PINT8  pLvl1Name = (ELMO_PINT8)TAG_NAME_LVL1, ELMO_PINT8  pLvl2Name = (ELMO_PINT8)TAG_NAME_LVL2);
    
//
    ELMO_INT32     cmpAttrib           (ELMO_UINT32 uiDeepLvl, ELMO_PVOID  pNodeV,  ELMO_PINT8 pLookForAttrVal);
//
    ELMO_INT32     Save_pr             (ELMO_PINT8  cFileName, ELMO_PINT8 cFilePath, ELMO_UINT32 uiFlags)    throw (CMMCException);
//
    void          handleNodes         (ELMO_UINT32 uiDeepLvl, ELMO_PVOID  pNodeV);
    void          handleNodeAttribute (ELMO_UINT32 uiDeepLvl, ELMO_PVOID  pNodeV);
    void          handleNodeValue     (ELMO_UINT32 uiDeepLvl, ELMO_PVOID  pNodeV);
//
    ELMO_INT32     UpdDomTree          (ELMO_PINT8  pLvl1Valu, ELMO_PINT8  pLvl2Valu,   ELMO_PINT8  pLvl3Name,
                                      ELMO_PINT8   cPstr,     ELMO_INT32  cPstrSize);
};
//
#endif /* MMCUSERPARAMS_HPP_ */
