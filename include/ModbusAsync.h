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
#if 1
    0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};
#else
    1 << 0, 1 << 1, 1 << 2, 1 << 3, 1 << 4, 1 << 5, 1 << 6, 1 << 7};
#endif

const MDBA_UCHAR mdba_byte_OFF[] = {
	~0x01, 
	~0x02, 
	~0x04,
    ~0x08, 
	~0x10, 
	~0x20, 
	~0x40, 
	~0x80
};

const MDBA_UCHAR MDBA_BIT_REVERSE_TABLE[256] = {
	0x00, 0x80, 0x40, 0xC0, 0x20, 0xA0,
    0x60, 0xE0, 0x10, 0x90, 0x50, 0xD0, 0x30, 0xB0, 0x70, 0xF0, 0x08, 0x88,
    0x48, 0xC8, 0x28, 0xA8, 0x68, 0xE8, 0x18, 0x98, 0x58, 0xD8, 0x38, 0xB8,
    0x78, 0xF8, 0x04, 0x84, 0x44, 0xC4, 0x24, 0xA4, 0x64, 0xE4, 0x14, 0x94,
    0x54, 0xD4, 0x34, 0xB4, 0x74, 0xF4, 0x0C, 0x8C, 0x4C, 0xCC, 0x2C, 0xAC,
    0x6C, 0xEC, 0x1C, 0x9C, 0x5C, 0xDC, 0x3C, 0xBC, 0x7C, 0xFC, 0x02, 0x82,
    0x42, 0xC2, 0x22, 0xA2, 0x62, 0xE2, 0x12, 0x92, 0x52, 0xD2, 0x32, 0xB2,
    0x72, 0xF2, 0x0A, 0x8A, 0x4A, 0xCA, 0x2A, 0xAA, 0x6A, 0xEA, 0x1A, 0x9A,
    0x5A, 0xDA, 0x3A, 0xBA, 0x7A, 0xFA, 0x06, 0x86, 0x46, 0xC6, 0x26, 0xA6,
    0x66, 0xE6, 0x16, 0x96, 0x56, 0xD6, 0x36, 0xB6, 0x76, 0xF6, 0x0E, 0x8E,
    0x4E, 0xCE, 0x2E, 0xAE, 0x6E, 0xEE, 0x1E, 0x9E, 0x5E, 0xDE, 0x3E, 0xBE,
    0x7E, 0xFE, 0x01, 0x81, 0x41, 0xC1, 0x21, 0xA1, 0x61, 0xE1, 0x11, 0x91,
    0x51, 0xD1, 0x31, 0xB1, 0x71, 0xF1, 0x09, 0x89, 0x49, 0xC9, 0x29, 0xA9,
    0x69, 0xE9, 0x19, 0x99, 0x59, 0xD9, 0x39, 0xB9, 0x79, 0xF9, 0x05, 0x85,
    0x45, 0xC5, 0x25, 0xA5, 0x65, 0xE5, 0x15, 0x95, 0x55, 0xD5, 0x35, 0xB5,
    0x75, 0xF5, 0x0D, 0x8D, 0x4D, 0xCD, 0x2D, 0xAD, 0x6D, 0xED, 0x1D, 0x9D,
    0x5D, 0xDD, 0x3D, 0xBD, 0x7D, 0xFD, 0x03, 0x83, 0x43, 0xC3, 0x23, 0xA3,
    0x63, 0xE3, 0x13, 0x93, 0x53, 0xD3, 0x33, 0xB3, 0x73, 0xF3, 0x0B, 0x8B,
    0x4B, 0xCB, 0x2B, 0xAB, 0x6B, 0xEB, 0x1B, 0x9B, 0x5B, 0xDB, 0x3B, 0xBB,
    0x7B, 0xFB, 0x07, 0x87, 0x47, 0xC7, 0x27, 0xA7, 0x67, 0xE7, 0x17, 0x97,
    0x57, 0xD7, 0x37, 0xB7, 0x77, 0xF7, 0x0F, 0x8F, 0x4F, 0xCF, 0x2F, 0xAF,
    0x6F, 0xEF, 0x1F, 0x9F, 0x5F, 0xDF, 0x3F, 0xBF, 0x7F, 0xFF
};

/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/
// === BIT MACROS ===
#define MDBA_SET_BIT(__x__, __n__)       ((__x__) |=  (1U << (__n__)))
#define MDBA_SET_BIT_T(__x__, __n__)       ((__x__) |=  mdba_byte_ON[__n__])

#define CLEAR_BIT(__x__, __n__)     ((__x__) &= ~(1U << (__n__)))
#define CLEAR_BIT_T(__x__, __n__) ((__x__) &= mdba_byte_OFF[__n__])

#define TOGGLE_BIT(__x__, __n__)    ((__x__) ^=  (1U << (__n__)))
#define TOGGLE_BIT(__x__, __n__) ((__x__) ^= mdba_byte_ON[__n__])

#define IS_BIT_SET(__x__, __n__)    (((__x__) >> (__n__)) & 1U)
#define IS_BIT_SET_T(__x__, __n__) ((__x__) & mdba_byte_ON[__n__])

#define IS_BIT_CLEAR(__x__, __n__)  (!(((__x__) >> (__n__)) & 1U))
#define IS_BIT_CLEAR_T(__x__, __n__) ((__x__) & mdba_byte_OFF[__n__])

// === BIT FIELD MACRO ===
// Set bit n to val (0 or 1)
#define ASSIGN_BIT(__x__, __n__, val) (__x__ = ((__x__ & ~(1U << (__n__))) | ((!!(val)) << (__n__))))
#define ASSIGN_BIT_T(__x__, __n__, val)                                        \
	{                                                                      \
		(__x__) =                                                      \
		    ((val) ? ((__x__) | mdba_byte_ON[__n__])             \
				 : ((__x__) & mdba_byte_OFF[__n__]));             \
	}

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
