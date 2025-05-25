#include <ModbusAsync.h>
#include <stdint.h>
/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/
static MDBA_USHORT
mdba_crc16(const MDBA_UCHAR *data, MDBA_USHORT length);
/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/
static MDBA_USHORT
mdba_crc16(const MDBA_UCHAR *data, MDBA_USHORT length)
{
	MDBA_USHORT crc = 0xFFFF;
	MDBA_USHORT pos = 0, i = 0;

	for (pos = 0; pos < length; pos++) {
		crc ^= data[pos];

		for (i = 0; i < 8; i++) {
			if (crc & 0x0001) {
				crc >>= 1;
				crc ^= 0xA001;
			} else {
				crc >>= 1;
			}
		}
	}

	return crc;
}

/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/
int
mdba_slav_scan(char *port)
{
	int ret = 0;
	do {
	} while (0);
	return ret;
}
/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/
const char *
mdba_err_txt(int i)
{
	return "";
}
/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/
void
mdba_dump_byte(MDBA_UCHAR *data, int len)
{
	int i = 0;
	int n = 0;
	char buff[256 + 1] = {0};
	int step = 0;

	for (i = 0; i < len; ++i) {
		step +=
		    snprintf(buff + step, 256 - step, "0x%.2x ", (int)data[i]);
	}
	spllog(0, "%s", buff);
}
/*+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+*/
