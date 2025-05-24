/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/
/* Email:
*		<nguyenthaithuanalg@gmail.com> - Nguyễn Thái Thuận
* Mobile:
*		<+084.799.324.179>
* Whatsapp:
*		<+084.799.324.179>
* Date:
*		<2025-May-24>
* The lasted modified date:
* Decription:
*		The (only) main header file to export 5 APIs: [mdba_module_init,
mdba_module_finish, mdba_inst_open, mdba_inst_close, mdba_inst_write].
*/
/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/
#ifndef ___SIMPLE_MODBUS_ASYNC__
#define ___SIMPLE_MODBUS_ASYNC__ 
#include <stdlib.h>
#include <simplelog.h>

#if 0
#ifndef UNIX_LINUX
#define UNIX_LINUX                
#endif
#endif

#if 0
#ifndef _EPOLL__
#define _EPOLL__            
#endif
#endif

#if 0
#if 1
#ifndef __ADD_SIMPLE_LOG__
#define __ADD_SIMPLE_LOG__        
#endif
#endif

#ifdef __ADD_SIMPLE_LOG__
#include <simplelog.h>
#else
#define spllog                    mdba_console_log
#endif
#endif

#ifndef __SP_FILLE__
#define __SP_FILLE__(__p__)                                                    \
	do {                                                                   \
		__p__ = strrchr(__FILE__, '/');                                \
		if (__p__) {                                                   \
			++__p__;                                               \
			break;                                                 \
		}                                                              \
		__p__ = strrchr(__FILE__, '\\');                               \
		if (__p__) {                                                   \
			++__p__;                                               \
			break;                                                 \
		}                                                              \
		__p__ = __FILE__;                                              \
	} while (0);
#endif

#ifndef __UNIX_LINUX_CPP11_AND_NEWERS__
#define mdba_console_log(__lv__, ___fmttt___, ...)                             \
	{                                                                      \
		;                                                              \
		const char *pfn = 0;                                           \
		__SP_FILLE__(pfn);                                             \
		;                                                              \
		fprintf(stdout,                                                \
		    "[%d - %s - %s] [%s:%s:%d] "___fmttt___                    \
		    "\n",                                                      \
		    (__lv__), __DATE__, __TIME__, (char *)pfn,                 \
		    (char *)__FUNCTION__, (int)__LINE__, ##__VA_ARGS__);       \
	}
#else
#define mdba_console_log(__lv__, ___fmttt___, ...)                             \
	{                                                                      \
		;                                                              \
		std::string __c11fmt__ = "[%d - %s - %s] [%s:%s:%d] ";         \
		__c11fmt__ += ___fmttt___;                                     \
		__c11fmt__ += "\n";                                            \
		const char *pfn = 0;                                           \
		__FILLE__(pfn);                                                \
		;                                                              \
		fprintf(stdout, __c11fmt__.c_str(), (__lv__), __DATE__,        \
		    __TIME__, (char *)pfn, (char *)__FUNCTION__,               \
		    (int)__LINE__, ##__VA_ARGS__);                             \
	}
#endif

#define mdba_malloc(__nn__, __obj__, __type__)                                 \
	{                                                                      \
		(__obj__) = (__type__ *)malloc(__nn__);                        \
		if (__obj__) {                                                 \
			spllog(0, "[MEM] Malloc: 0x%p.", (__obj__));           \
			memset((__obj__), 0, (__nn__));                        \
		} else {                                                       \
			spllog(0, "Malloc: error.");                           \
		}                                                              \
	}

#define mdba_free(__obj__)                                                     \
	{                                                                      \
		if (__obj__) {                                                 \
			spllog(0, "[MEM] Free: 0x%p.", (__obj__));             \
			free(__obj__);                                         \
			(__obj__) = 0;                                         \
		}                                                              \
	}

#ifdef __cplusplus
extern "C" {
#endif

#ifndef UNIX_LINUX
#ifndef __SIMPLE_STATIC_MODBUS_ASYNC__
#ifdef EXPORT_DLL_API_MODBUS_ASYNC
#define DLL_API_MODBUS_ASYNC     __declspec(dllexport)
#else
#define DLL_API_MODBUS_ASYNC     __declspec(dllimport)
#endif
#else
#define DLL_API_MODBUS_ASYNC     
#endif
#else
#define DLL_API_MODBUS_ASYNC     
#ifndef _EPOLL__
#define MDBA_MAINKEY              "main"
#define MDBA_MAINKEY_MACH         "main_mach"
#endif
#endif /*! UNIX_LINUX */

/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/
#define MDBA_PORT_LEN             32
#define MDBA_KEY_LEN              (MDBA_PORT_LEN)
#ifndef MDBA_LLU
#define MDBA_LLU                  unsigned long long
#endif
#ifndef MDBA_UNIT
#define MDBA_UNIT                 unsigned int
#endif

typedef enum {
	MDBA_CMD_STORAGE_INPUT_INFO_ARR,
	MDBA_CMD_ADD,
	MDBA_CMD_REM,
	MDBA_CMD_WRITE,

	MDBA_CMD_PEAK
} MDBA_CMD_TYPE;

typedef int (*MDBA_module_cb)(void *);

typedef enum {
	MDBA_PORT_OK,
	MDBA_PORT_INFO_NULL,
	MDBA_PORT_INPUT_NULL,
	MDBA_IDD_NULL,
	MDBA_OUTPUT_NULL,
	MDBA_PORT_OPEN,
	MDBA_PORT_OPEN_UNIX,
	MDBA_PORT_CLOSE_UNIX,
	MDBA_PORT_COMMSTATE,
	MDBA_PORT_GETCOMMSTATE,
	MDBA_PORT_SETCOMMSTATE,
	MDBA_PORT_CREATEEVENT,
	MDBA_PORT_SETCOMMTIMEOUTS,
	MDBA_PORTMUTEX_CREATE,
	MDBA_PORTSEM_CREATE,
	MDBA_PORT_BAUDRATE_ERROR,
	MDBA_PORT_NAME_ERROR,
	MDBA_MTX_CREATE,
	MDBA_SEM_CREATE,
	MDBA_GEN_IDD,
	MDBA_MEM_NULL,
	MDBA_MUTEX_NULL_ERROR,
	MDBA_SEM_NULL_ERROR,
	MDBA_SEM_POST_ERROR,
	MDBA_SEM_UNLINK,
	MDBA_SEM_CLOSE,
	MDBA_INPUT_NULL_ERROR,
	MDBA_THREAD_W32_CREATE,
	MDBA_NOT_FOUND_IDD,
	MDBA_REALLOC_ERROR,
	MDBA_MALLOC_ERROR,
	MDBA_INFO_NULL,
	MDBA_PARAM_NULL,
	MDBA_ITEM_NOT_FOUND,
	MDBA_CREATE_THREAD_ERROR,
	MDBA_SHUTDOWN_SOCK,
	MDBA_CLOSE_SOCK,
	MDBA_CREATE_SOCK,
	MDBA_FCNTL_SOCK,
	MDBA_BIND_SOCK,
	MDBA_EPOLL_CREATE,
	MDBA_EPOLL_CTL,
	MDBA_BUFF_EXCEED,
	MDBA_UNIX_OPEN_PORT,
	MDBA_UNIX_GET_ATTR,
	MDBA_UNIX_SET_ATTR,
	MDBA_UNIX_EPOLL_CTL,
	MDBA_PORTNAME_EXISTED,
	MDBA_HASH_NOTFOUND,
	MDBA_CALLBACK_NULL,
	MDBA_PX_ITEM_NULL,
	MDBA_PX_CB_NULL,
	MDBA_PX_POLLFD_NULL,
	MDBA_PX_PRANGE_NULL,
	MDBA_PX_EPOLL_DEL,
	MDBA_PX_POLL_NOT_FOUND,
	MDBA_PX_MALINFO_FD,
	MDBA_PX_MAL_HASH_FD,
	MDBA_HASH_NOT_FOUND,
	MDBA_REM_NOT_FOUND,
	MDBA_WIN32_OBJ_NULL,
	MDBA_WIN32_BUF_NULL,
	MDBA_WIN32_BWRITE_NULL,
	MDBA_WIN32_OVERLAP_NULL,
	MDBA_WIN32_EVTCB_NULL,
	MDBA_WIN32_NOT_PENDING,
	MDBA_WIN32_OVERLAP_ERR,
	MDBA_PORT_NULL,
	MDBA_PORT_EMPTY,
	MDBA_OBJ_NULL,
	MDBA_PORTNAME_NONEXISTED,
	MDBA_PX_FD_NOT_FOUND,
	MDBA_WIN32_RL_MTX,
	MDBA_WIN32_LK_MTX,
	MDBA_PX_LK_MTX,
	MDBA_PX_RL_MTX,
	MDBA_PX_RL_SEM,
	MDBA_PX_WAIT_SEM,
	MDBA_WIN32_WAIT_SEM,
	MDBA_WIN32_RL_SEM,
	MDBA_MINI_SIZE,
	MDBA_PX_READ,
	MDBA_PX_UNCONNECTED,
	MDBA_WIN32_UNCONNECTED, 
	MDBA_PX_FD_CLOSED,
	MDBA_WIN32_FD_CLOSED,
	MDBA_WIN32_CLEARCOMM,
	MDBA_WIN32_STILL_INQUE,
	

	MDBA_PORT_PEAK,
} MDBA_PORT_ERR;

typedef enum {
	MDBA_EVENT_READ_BUF,
	MDBA_EVENT_READ_ERROR,
	MDBA_EVENT_WRITE_OK,
	MDBA_EVENT_WRITE_ERROR,
	MDBA_EVENT_OPEN_DEVICE_OK,
	MDBA_EVENT_OPEN_DEVICE_ERROR,
	MDBA_EVENT_CLOSE_DEVICE_OK,
	MDBA_EVENT_CLOSE_DEVICE_ERROR,

	MDBA_EVENT_PEAK,
} MDBA_MODULE_EVENT;

typedef struct _GENERIC_ST__ {
	int total;
	int range;
	int pl;
	int pc;
	int type;
	int err_code;
	char data[0];
} MDBA_GENERIC_ST;

typedef struct _INPUT_ST__ {
	int baudrate;
	char port_name[MDBA_PORT_LEN];
	MDBA_module_cb cb_evt_fn;
	void *cb_obj;

	int t_delay;

} MDBA_INPUT_ST;

typedef struct _INFO_ST__ {
	int t_delay;
	char isoff;
	char is_retry;
	int baudrate;
	char port_name[MDBA_PORT_LEN];

#ifndef UNIX_LINUX
	void *hEvent;

	void *
#else
	int
#endif
	    handle;

	void *mtx_off;
	void *sem_off; /*It need to wait for completing.*/
#ifdef UNIX_LINUX
#endif
	MDBA_module_cb cb_evt_fn;
	void *cb_obj;
	MDBA_GENERIC_ST *buff;

} MDBA_INFO_ST;

typedef struct _ARR_LIST_LINED__ {
	MDBA_INFO_ST *item;
	/* struct _ARR_LIST_LINED__* prev; */
	struct _ARR_LIST_LINED__ *next;
} MDBA_ARR_LIST_LINED;

typedef struct _ROOT_TYPE__ {
	int count;
	void *mutex;
	void *sem;
	int mdba_off; /* Check off.*/
#ifndef UNIX_LINUX
#else

	void *sem_spsr; /* Check off.*/
	MDBA_GENERIC_ST *cmd_buff; /* Command list .*/
#ifndef _EPOLL__
	char sem_key[MDBA_KEY_LEN]; /*It need to wait for UNIX_LINUX --->>>
				       Mach.*/
#endif
#endif
	MDBA_ARR_LIST_LINED *init_node;
	MDBA_ARR_LIST_LINED *last_node;
} MDBA_ROOT_TYPE;
/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/

/*Must be started before using. Thread-safe, but should be at a start of main
 * function.*/
DLL_API_MODBUS_ASYNC int
mdba_module_init();

/*Should be invoked to complete using. Thread-safe, but should be at an end of
 * main function.*/
DLL_API_MODBUS_ASYNC int
mdba_module_finish();

/*Open a COM port for using. Thread-safe.*/
/*MDBA_INPUT_ST: port_name, baudrate, callback, ...*/
DLL_API_MODBUS_ASYNC int
mdba_inst_open(MDBA_INPUT_ST *input);

/*Close the COM port after using. Thread-safe.*/
DLL_API_MODBUS_ASYNC int
mdba_inst_close(char *portname);

/*Close the COM port after using. Thread-safe.*/
DLL_API_MODBUS_ASYNC int
mdba_inst_write(char *portname, char *data, int sz);

DLL_API_MODBUS_ASYNC const char *
mdba_err_txt(int);
/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/
#ifdef __cplusplus
}
#endif
/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/
#endif
