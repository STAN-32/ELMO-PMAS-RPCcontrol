#ifndef __GCODE_LIB_HDR__
#define __GCODE_LIB_HDR__


#define GC_INACTIVE_ERR			-1400
#define GC_INITCON_ERR			-1401
#define GC_LOADLIB_ERR			-1410
#define GC_START_ERR			-1411
#define GC_STOP_ERR				-1412
#define GC_PERFORM_ERR			-1413
#define GC_STATUS_ERR			-1414

#define GC_STARTSYM_ERR			-1420
#define GC_STOPSYM_ERR			-1421
#define GC_PERFORMSYM_ERR		-1422
#define GC_STATUSYM_ERR			-1423

#define GC_MSMMISSING_ERR		-1500
#define GC_WRKRSTRT_ERR			-1504
#define GC_UNDEFSPINDLE_ERR		-1505
#define GC_AXESNUM_MISMATCH_ERR	-1506

//#ifdef WIN32
#if   ((OS_PLATFORM == WIN32_PLATFORM) || (OS_PLATFORM == WIN32_PLATFORM))
	#ifdef GC_LIB_EXPORTS
		#define	GC_LIB_API __declspec(dllexport)
	#else
		#define GC_LIB_API __declspec(dllimport)
	#endif
#else
		#define GC_LIB_API
#endif

#define GC_IPADDR_LEN 15

/* definition to expand macro then apply to pragma message */
#define VALUE_TO_STRING(x) #x
#define VALUE(x) VALUE_TO_STRING(x)
#define VAR_NAME_VALUE(var) #var "="  VALUE(var)

#define GC_PATH_MAX_LEN	120		//max length for file full path
#define GC_AXES_ORDER_MAX 5 	//max lenght for axes order string
#define GC_LOOKUP_TABLE "lookup.gc"

/*!
 * \enum e_gc_status
 * \brief statuses list of g-code thread.
 */
typedef enum {eGC_STATUS_INACTIVE,	/*!< g-code is not active. 			*/
	eGC_STATUS_ACTIVE,				/*!< g-code is active on idle state */
	eGC_STATUS_RUN,					/*!< g-code is running (state run).	*/
	eGC_STATUS_DEBUG,				/*!< g-code is on stepping mode (g-code command).*/
	eGC_STATUS_STEPPING,			/*!< g-code is on stepping mode (breakpoint).*/
	eGC_STATUS_DONE,				/*!< g-code completed				*/
	eGC_STATUS_STOPPED,				/*!< g-code stopped	as a results stop	*/
	eGC_STATUS_ABORTED,				/*!< g-code aborted	(as a results of error)	*/
	eGC_STATUS_SUSPENDED,			/*!< g-code suspended as a results of pause	*/
} e_gc_status;	//used by gc_get_status API

/*!
 * \enum e_apimsg_t
 * \brief these are the type of messages one can specifies via gc_perform api.
 */
typedef enum {e_msg_nomsg,
	e_msg_start,			/*!< starts idle mode & initializations.*/
	e_msg_run,				/*!< activates g-code process.			*/
	e_msg_stop,				/*!< stop g-code process.				*/
	e_msg_pause,			/*!< pause g-code process.				*/
	e_msg_next,				/*!< step to next command.				*/
	e_msg_break,			/*!< set a breakpoint.					*/
	e_msg_continue,			/*!< continue g-code process.			*/
	e_msg_debug,			/*!< enable/disable debug mode.			*/
	e_msg_status,			/*!< get status of g-code process.		*/
	e_msg_rmbreak,			/*!< remove a breakpoint.				*/
	} e_apimsg_t;

typedef e_apimsg_t GC_APIMSG_ENUM;

/*!
 * \struct gc_status_data_t
 * \brief data, which client pulls periodically to track  status of g-code thread.
 */
typedef struct _gc_status_data
{
	ELMO_UINT32		_prt_id;		/*!< line index in prt*/
	ELMO_UINT32		_gc_id;			/*!< line index in g-code list.*/
	e_gc_status		_status;		/*!< g-code status run/debug/...*/
	ELMO_UINT16		usStatus;		/*!< api status */
	ELMO_UINT16		usErrorID;		/*!< api error id */
	ELMO_UINT8		_agent_id;		/*!< two g-code tasks are available (0 or 1)*/
	ELMO_INT8		_signature[15];	/*!< signature is a date string + null.		*/
	ELMO_UINT8		_reserve[32];	/*!< for future use. */
} gc_status_data_t;

typedef gc_status_data_t* pgc_status_data_t;
typedef gc_status_data_t MMC_GCSTATUS_OUT;

/*!
 * \struct gc_data_init_t
 * \brief initial setup data. user inputs (carrenly some defaults)
 */
typedef struct _gc_data_init
{
	ELMO_FLOAT	_fTransitionParameter[4];
	ELMO_INT32 	_eTransitionMode;
	ELMO_LINT32 _rb_threshold;			/*!< lower threshold for ring buffer */
	ELMO_LINT32 _q_threshold;			/*!< lower threshold for commands in node's queue */
	ELMO_UINT32 _q_bulk_size;			/*!<number of commands to read from buffer */
										/*!<and insert to node's queue when queue depth */
										/*!<goes below _q_threshold. */
	ELMO_UINT32 _rb_bulk_size;			/*!<number of commands to read from PRT */
										/*!<when the amount of commands in buffer */
										/*!<goes below _rb_threshold. */
	ELMO_UINT16	_group;				/*!<group axis reference */
	ELMO_UINT16	_spindle;			/*!<sindle axis reference */
	ELMO_INT8	_prt_name[GC_PATH_MAX_LEN+1];	/*!<prt file path */
	ELMO_UINT8	_axes_order[GC_AXES_ORDER_MAX+1];/*!<axes order in group (e.g. {'x','y','z'} */
										/*!<or {'x,'z','y} etc...). */
	ELMO_INT8	_host[GC_IPADDR_LEN+1];						/*!< local host ip address (relevant to rpc only) */
	ELMO_INT8 	_dest[GC_IPADDR_LEN+1];						/*!< destination ip address (relevant to rpc only) */
	ELMO_UINT8	_agent_id;			/*!< two g-code tasks are available (0 or 1)*/
	ELMO_UINT8	_reserve[32];		/*!<for future use. */
} gc_data_init_t;

typedef gc_data_init_t* pgc_data_init_t;

typedef gc_data_init_t MMC_GCINIT_IN;
typedef struct _mmc_gcinit_out
{
	ELMO_UINT16 usStatus;
	ELMO_UINT16 usErrorID;
}MMC_GCINIT_OUT;

/*!
* \struct GC_APIMSG_STRUCT
* \brief data structure transfers a command for g-code process.
*/
typedef struct _gc_apimsg_struct {
	ELMO_INT32		_value;			/*!< value to set by api (if relevant). */
	GC_APIMSG_ENUM	_type;			/*!< command (api) type. */
	ELMO_UINT8		_agent_id;		/*!< two g-code tasks are available (0 or 1)*/
	ELMO_UINT8		_reserve[32];	/*!<for future use. */
} GC_APIMSG_STRUCT;

typedef GC_APIMSG_STRUCT MMC_GCMSG_IN;
typedef struct _mmc_gcmsg_out
{
	ELMO_UINT16 usStatus;
	ELMO_UINT16 usErrorID;
} MMC_GCMSG_OUT;

typedef struct _mmc_gcstop_in
{
	ELMO_UINT8 _agent_id;
} MMC_GCSTOP_IN;
typedef MMC_GCSTOP_IN MMC_GCSTATUS_IN;

typedef struct _gc_stoprt_in
{
	ELMO_UINT8 _padding[16];
} gc_stoprt_in;

typedef gc_stoprt_in MMC_GCSTOPRT_IN;

typedef struct _mmc_gcstop_out
{
	ELMO_UINT16 usStatus;
	ELMO_UINT16 usErrorID;
} MMC_GCSTOP_OUT;

#ifdef __cplusplus
/*!
 * \class gc_apimsg
 * \brief this class defines the api message, which passses between two threads.
 *
 * in practical between the main thread and the thread which runs the g-code task manager.
 */
class gc_apimsg
{
private:
		ELMO_INT32	_value;
		e_apimsg_t	_type;
public:
    /*!
     * \func default constructor
     */
    gc_apimsg() : _value(0), _type(e_msg_nomsg) { }
    gc_apimsg(ELMO_INT32 value, e_apimsg_t type) : _value(value), _type(type) { }
    /*!
     * \fn copy constructor
     */
    gc_apimsg(const gc_apimsg& ref) : _value(ref._value), _type(ref._type) { }
    /*!
     * \fn destructor
     */
    virtual ~gc_apimsg() {}
    /*!
     * \fn assignment operator
     * \param src is the source for assignment.
     */
    gc_apimsg& operator=(const gc_apimsg& src)
    {
        // check for self-assignment
        if(&src == this)
           return *this;
        _value = src._value;
        _type = src._type;
        return *this;
    }
    ELMO_INT32 get_value() {return _value;}
    e_apimsg_t get_type() {return _type;}
    void set_value(ELMO_INT32 value) {_value=value;}
    void set_type(e_apimsg_t type) {_type=type;}
};
#endif



#ifdef __cplusplus
extern "C" {
#endif

class GC_LIB_API gcrpc_clnt
{
public:
	/*!
	* the constructor
	*/
	gcrpc_clnt();
	/*!
	* the destructor.
	*/
	virtual ~gcrpc_clnt();

	/*!
	 * \fn int create(const char* dest)
	 * \brief creates g-code client object.
	 * this routine allows C program to make procedure calls
	 * on other machines across the network.
	 * \param dest destination IP to remote host.
	 * \return 0 if completed successfully, otherwise error.
	 */
	ELMO_INT32 create(const ELMO_PINT8 dest);
	/*!
	* \fn int stoprt(MMC_GCSTOPRT_IN* i_params, MMC_GCSTATUS_OUT* o_params)
	* \brief calls remote prosedure to stop g-code runtime.
	* \param i_params	data structure as input parameters to stop g-code runtime.
	* \param o_params	data returns as output from g-code task.
	* \return 0 if completed successfully, otherwise error.
	*/
	ELMO_INT32 stoprt(MMC_GCSTOPRT_IN* i_params, MMC_GCSTATUS_OUT* o_params);
	/*!
	* \fn int create(unsigned int conn)
	* \brief creates g-code client object.
	* this routine allows C program to make procedure calls
	* on other machines across the network.
	* \param conn connection handler to remote host.
	* \return 0 if completed successfully, otherwise error.
	*/
	ELMO_INT32 create(ELMO_UINT32 conn);
	/*!
	* \fn int start(MMC_GCINIT_IN* msg)
	* \brief calls remote prosedure to start g-code task.
	* \param i_params	data structure to intiate and start the g-code task.
	* \param o_params	data returns as output from g-code task.
	* \return 0 if completed successfully, otherwise error.
	*/
	ELMO_INT32 start(MMC_GCINIT_IN* i_params, MMC_GCSTATUS_OUT* o_params);
	/*!
	* \fn int perform(MMC_GCMSG_IN* msg)
	* \brief calls remote prosedure to perform command on g-code task.
	* \param msg	command's specific data.
	* \return 0 if completed successfully, otherwise error.
	*/
	int perform(MMC_GCMSG_IN* i_params, MMC_GCSTATUS_OUT* o_params);
	/*!
	* \fn int status(MMC_GCSTATUS_OUT* status);
	* \brief calls remote prosedure to retrieve status from g-code task.
	* \param status returns status from remote g-code task.
	* \return 0 if completed successfully, otherwise error.
	*/
	ELMO_INT32 status(MMC_GCSTATUS_IN* i_params, MMC_GCSTATUS_OUT* o_params);
private:
	ELMO_PVOID	_client;			/*!< rpc client object					*/
	ELMO_UINT32 _conn;		/*! connection handler to remote host	*/
	ELMO_INT8	_host[16];		/*!< ip address of remote host			*/
};

/*!
 * \fn		char* gc_version()
 * \brief	retrieves the g-code library version.
 * \return  pointer to version string(C null terminated string)
 */
GC_LIB_API ELMO_PINT8 gc_version();

/*!
 * \fn	int gc_objcreate()
 * \brief creates instance of gc_objmngr and member of two instances of task manager (doing nothing).
 * \return 0 if completed successfully, otherwise error.
 */
GC_LIB_API ELMO_INT32 gc_objcreate();

/*!
 * \fn		int gc_start(int id, MMC_GCINIT_IN* data, unsigned int handler=0)
 * \brief	starts the g-code task.
 *
 * 		peform initialization and start g-code engine.
 * \param id	g-code engine id (0 or 1 are valid only)
 * \param data	initialization data.
 * \param handler connection handler for IPC. default 0 (RPC)
 * \return 0 if completed successfully, otherwise an error (< 0)
 */
GC_LIB_API ELMO_INT32 gc_start(ELMO_INT32 id, MMC_GCINIT_IN* data, ELMO_UINT32 handler=0);
/*!
 * \fn		int gc_stoprt(int id, MMC_GCSTOPRT_IN* data, unsigned int handler=0)
 * \brief	stops g-code runtime.
 *
 * \param data	input parameters (currently only dummy).
 * \param handler connection handler for IPC. default 0 (RPC)
 * \return 0 if completed successfully, otherwise an error (< 0)
 */
GC_LIB_API ELMO_INT32 gc_stoprt(MMC_GCSTOPRT_IN* data, ELMO_UINT32 handler=0);

/*!
 * \fn	int gc_stop(void)
 * \brief	terminates g-code task
* \param id	g-code task id (there might be multiple instances of g-code tasks).
 * \return 0 if completed successfully, otherwise error.
 */
GC_LIB_API ELMO_INT32 gc_stop(ELMO_INT32 id);

/*!
 * \fn	int gc_perform(gc_apimsg& msg)
 * \brief		perform gc command as specified by msg.
 * \param id	g-code task id (there might be multiple instances of g-code tasks).
 * \param msg	specified command to perform.
 * \return 0 if completed successfully, otherwise error.
 */
GC_LIB_API ELMO_INT32 gc_perform(ELMO_INT32 id, MMC_GCMSG_IN* msg);

/*!
 * \fn	int gc_getstatus(gc_status_data_t& data)
 * \brief		retrives status data of g-code task.
 * \param id	g-code task id (there might be multiple instances of g-code tasks).
 * \param data	retrieved status data if function has completed successfully.
 * \return 0 if completed successfully, otherwise error.
 */
GC_LIB_API ELMO_INT32 gc_getstatus(ELMO_INT32 id,  MMC_GCSTATUS_OUT* data);

#ifdef __cplusplus
}
#endif //__cplusplus


#endif //__GCODE_LIB_HDR__
