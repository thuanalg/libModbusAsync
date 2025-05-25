mv trigger_serial.txt trigger_serial.txt_
export LD_LIBRARY_PATH=./:$LD_LIBRARY_PATH:/usr/local/lib
./test_main --is_baudrate=9600 --is_cfg=modbus.cfg --is_port=/dev/ttyUSB2
