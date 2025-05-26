/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/
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
/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/
#ifndef ___SIMPLE_MODBUS_ASYNC__
#define ___SIMPLE_MODBUS_ASYNC__ 
#include <stdlib.h>
#include <serialmodule.h>

#if 1
#ifndef UNIX_LINUX
#define UNIX_LINUX               
#endif
#endif

#define mdba_malloc(__nn__, __obj__, __type__)                                 \
	{                                                                      \
		(__obj__) = (__type__ *)malloc(__nn__);                        \
		if (__obj__) {                                                 \
			spllog(0, "[MEM] Malloc-mdba: 0x%p.", (__obj__));      \
			memset((__obj__), 0, (__nn__));                        \
		} else {                                                       \
			spllog(0, "Malloc-mdba: error.");                      \
		}                                                              \
	}

#define mdba_free(__obj__)                                                     \
	{                                                                      \
		if (__obj__) {                                                 \
			spllog(0, "[MEM] Free-mdba: 0x%p.", (__obj__));        \
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

/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/
#define MDBA_PORT_LEN            32
#define MDBA_KEY_LEN             (MDBA_PORT_LEN)
#ifndef MDBA_LLU
#define MDBA_LLU                 unsigned long long
#endif
#ifndef MDBA_UNIT
#define MDBA_UNIT                unsigned int
#endif

#ifndef MDBA_UCHAR
#define MDBA_UCHAR               unsigned char
#endif

#ifndef MDBA_USHORT
#define MDBA_USHORT              unsigned short
#endif

#ifndef MDBA_RESERVE
#define MDBA_RESERVE             4
#endif
/*CRC 16 bit, big-endian*/
#ifndef MDBA_CRC16
#define MDBA_CRC16               2
#endif

typedef struct __MDBA_FRAME_ST__ {
	int total;
	MDBA_UCHAR slave_id;
	MDBA_UCHAR fcode;
	char data[0];
} MDBA_FRAME_ST;
/*total = sizeof(MDBA_FRAME_ST) + sizeof(data) +  MDBA_CRC2 + MDBA_RESERVE;*/
#define mdba_malloc_frame(__nn__, __obj__)                                     \
	{                                                                      \
		int __tsz__ =                                                  \
		    __nn__ + sizeof(MDBA_FRAME_ST) + MDBA_CRC2 + MDBA_RESERVE; \
		(__obj__) = (MDBA_FRAME_ST *)malloc(__tsz__);                  \
		if (__obj__) {                                                 \
			spllog(0, "[MEM] Malloc-mdba: 0x%p.", (__obj__));      \
			memset((__obj__), 0, (__tsz__));                       \
			__obj__->total = __tsz__;                              \
		} else {                                                       \
			spllog(0, "Malloc-mdba: error.");                      \
		}                                                              \
	}

/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/
const MDBA_UCHAR mdba_byte_ON[] = {
    0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};

const MDBA_UCHAR mdba_byte_OFF[] = {0xFF - 0x01, 0xFF - 0x02, 0xFF - 0x04,
    0xFF - 0x08, 0xFF - 0x10, 0xFF - 0x20, 0xFF - 0x40, 0xFF - 0x80};
/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/

/*Must be started before using. Thread-safe, but should be at a start of main
 * function.*/
DLL_API_MODBUS_ASYNC MDBA_USHORT
mdba_crc16(const MDBA_UCHAR *data, MDBA_USHORT length);

DLL_API_MODBUS_ASYNC const char *
mdba_err_txt(int);

DLL_API_MODBUS_ASYNC void
mdba_dump_byte(MDBA_UCHAR *data, int len);
/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/
#ifdef __cplusplus
}
#endif
/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/
#endif
