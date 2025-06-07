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

#if 0
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
// === BIT MACROS ===
#define MDBA_SET_BIT(__x__, __n__)       ((__x__) |=  (1U << (__n__)))
#define MDBA_SET_BIT_ARR(__x__, __n__)       ((__x__) |=  mdba_byte_ON[__n__])

#define CLEAR_BIT(__x__, __n__)     ((__x__) &= ~(1U << (__n__)))
#define CLEAR_BIT_ARR(__x__, __n__) ((__x__) &= mdba_byte_OFF[__n__])

#define TOGGLE_BIT(__x__, __n__)    ((__x__) ^=  (1U << (__n__)))

#define IS_BIT_SET(__x__, __n__)    (((__x__) >> (__n__)) & 1U)
#define IS_BIT_SET_ARR(__x__, __n__) ((__x__) & mdba_byte_ON[__n__])

#define IS_BIT_CLEAR(__x__, __n__)  (!(((__x__) >> (__n__)) & 1U))
#define IS_BIT_CLEAR_ARR(__x__, __n__) ((__x__) & mdba_byte_OFF[__n__])

// === BIT FIELD MACRO ===
// Set bit n to val (0 or 1)
#define ASSIGN_BIT(__x__, __n__, val) (__x__ = ((__x__ & ~(1U << (__n__))) | ((!!(val)) << (__n__))))

// Extract bit range [start, start+len)
#define EXTRACT_BITS(val, start, len) (((val) >> (start)) & ((1U << (len)) - 1))

// === BYTE SWAP / ENDIAN ===
//static inline uint16_t swap16(uint16_t x) {
//    return (x << 8) | (x >> 8);
//}
//
//static inline uint32_t swap32(uint32_t x) {
//    return ((x & 0x000000FFU) << 24) |
//           ((x & 0x0000FF00U) << 8)  |
//           ((x & 0x00FF0000U) >> 8)  |
//           ((x & 0xFF000000U) >> 24);
//}
//
//// === BIT COUNT ===
//static inline uint8_t count_bits(uint8_t x) {
//    uint8_t count = 0;
//    while (x) {
//        count += x & 1U;
//        x >>= 1;
//    }
//    return count;
//}
//
//// === BIT REVERSE ===
//static inline uint8_t reverse_bits(uint8_t b) {
//    b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
//    b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
//    b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
//    return b;
//}
//
//// === MAKE UINT32 FROM 4 BYTES ===
//static inline uint32_t make_uint32_be(uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3) {
//    return ((uint32_t)b0 << 24) | ((uint32_t)b1 << 16) |
//           ((uint32_t)b2 << 8)  | (uint32_t)b3;
//}
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
