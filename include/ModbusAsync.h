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
 *		The (only) main header file to export 5 APIs: [].
 */
/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/
#ifndef ___SIMPLE_MODBUS_ASYNC__
#define ___SIMPLE_MODBUS_ASYNC__ 
#include <stdlib.h>
#include <serialmodule.h>

#if 0
#ifndef UNIX_LINUX
#define UNIX_LINUX               
#endif
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
#endif /*! UNIX_LINUX */

/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/
#define MDBA_PORT_LEN            32
#define MDBA_KEY_LEN             (MDBA_PORT_LEN)
#ifndef MDBA_LLU
#define MDBA_LLU                 unsigned long long
#endif
#ifndef MDBA_UNIT
#define MDBA_UNIT                unsigned int
#endif

/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/

/*Must be started before using. Thread-safe, but should be at a start of main
 * function.*/
DLL_API_MODBUS_ASYNC int
mdba_slav_scan(char *port);

DLL_API_MODBUS_ASYNC const char *
mdba_err_txt(int);
/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/
#ifdef __cplusplus
}
#endif
/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/
#endif
