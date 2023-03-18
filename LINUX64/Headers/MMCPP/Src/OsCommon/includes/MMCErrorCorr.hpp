/*
 * CMMCErrorCore.hpp
 *
 *  Created on: 05/07/2011
 *      Author: yuvall
 *      Update: Haim H. 03Mar2015 Changes for support Multi type of OS.
 *      Update: Haim H. 05Sep2017 Update for the new functions APIs.
 */

#ifndef CMMCERRORCORE_HPP_
#define CMMCERRORCORE_HPP_

#include "MMCPPGlobal.hpp"
/*
 *
 */
class DLLMMCPP_API CMMCErrorCorr {
public:
    CMMCErrorCorr():m_uiConnHndl(0) {}
    CMMCErrorCorr(MMC_CONNECT_HNDL uiConnHndl):m_uiConnHndl(uiConnHndl) {}
    virtual ~CMMCErrorCorr();

    void SetConnectionHndl(MMC_CONNECT_HNDL uiConnHndl){m_uiConnHndl = uiConnHndl;}
    MMC_CONNECT_HNDL GetConnectionHndl(){return m_uiConnHndl;}

	/**
	 * \fn	LoadErrorCorrTable(MMC_LOADERRORTABLE_IN& stInParams)
	 * \brief	this method loads an error correction table.
	 * \param	stInParams	table parameters
	 * \param	iErrLineNum out address to retrieve line number in case of loading error (failure).
	 * 			default is NULL for backward compatibility.
	 * \return	0 on success, otherwise error or exception thrown.
	 */
	ELMO_INT32 LoadErrorCorrTable(MMC_LOADERRORTABLE_IN& stInParams, ELMO_PINT32 iErrLineNum=NULL) throw (CMMCException);

	/**
	 * \fn	LoadErrorCorrTable(char pPathToETFile[NC_MAX_ET_FILE_PATH_LENGTH], NC_ERROR_TABLE_NUMBER eETNumber, double dMaxCorrectionDelta = 0)
	 * \brief	this method loads an error correction table.
	 * \param	pPathToETFile path to table file on target controller.
	 * \param	eETNumber table  index in journal.
	 * \param	dMaxCorrectionDelta maximum allowed aberration(error delta).  default is 0 as for no aberration allowed.
	 * \param	iErrLineNum out address to retrieve line number in case of loading error (failure).
	 * 			default is NULL for backward compatibility.
	 * \return	0 on success, otherwise error or exception thrown.
	 */
	void LoadErrorCorrTable(ELMO_INT8 pPathToETFile[NC_MAX_ET_FILE_PATH_LENGTH], NC_ERROR_TABLE_NUMBER eETNumber, ELMO_DOUBLE dMaxCorrectionDelta = 0, ELMO_PINT32 iErrLineNum=NULL) throw (CMMCException);

	/**
	 * \fn	LoadErrorCorrTable(NC_ERROR_TABLE_NUMBER eETNumber, double dMaxCorrectionDelta = 0, int* iErrLineNum=NULL)
	 * \brief	this method loads an error correction table.
	 * \param	eETNumber table  index in journal.
	 * \param	dMaxCorrectionDelta maximum allowed aberration(error delta). default is 0 as for no aberration allowed.
	 * \param	iErrLineNum out address to retrieve line number in case of loading error (failure).
	 * 			default is NULL for backward compatibility.
	 * \return	0 on success, otherwise error or exception thrown.
	 */
	void LoadErrorCorrTable(NC_ERROR_TABLE_NUMBER eETNumber, ELMO_DOUBLE dMaxCorrectionDelta = 0, ELMO_PINT32 iErrLineNum=NULL) throw (CMMCException);

    ELMO_INT32 UnloadErrorCorrTable (NC_ERROR_TABLE_NUMBER eTableNumber) throw (CMMCException);
    ELMO_INT32 EnableErrorCorrTable (NC_ERROR_TABLE_NUMBER eTableNumber) throw (CMMCException);
    ELMO_INT32 DisableErrorCorrTable(NC_ERROR_TABLE_NUMBER eTableNumber) throw (CMMCException);

    void GetErrorTableStatus(NC_ERROR_TABLE_NUMBER eTableNumber, MMC_GETERRORTABLESTATUS_OUT &stOutParams);
    ELMO_BOOL IsTableEnabled(NC_ERROR_TABLE_NUMBER eETNumber) throw (CMMCException);
    ELMO_BOOL  IsTableLoaded(NC_ERROR_TABLE_NUMBER eETNumber) throw (CMMCException);      

private:
    MMC_CONNECT_HNDL m_uiConnHndl;
};

#endif /* CMMCERRORCORE_HPP_ */
