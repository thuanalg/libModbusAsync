###1. Modbus RTU Frame (via RS-232/RS-485):  

| Slave Address | Function Code|   Data                 | CRC Checksum       |   Silent    |  
| ------------- | ------------ | ---------------------- | ------------------ | ----------- |  
|   (1 byte)    |   (1 byte)   | (N bytes)              |   (2 bytes)        | Interval(s) |  
|   [11]        |   [03]       | [00] [6B] [00] [03]    |   [CRC_L] [CRC_H]  | Interval(s) |  
  
[11] [03] [00] [6B] [00] [03] [CRC_L] [CRC_H]  
|-----|----|---------|----------└─ CRC-16 (Low byte first)  
|-----|----|---------└──────── Quantity = 3 registers  
|-----|----|  
|-----|----|  
|-----|----└───────────── Start address = 0x006B  
|-----└────────────────── Function Code = 0x03 (Read Holding Registers)  
|  
└─────────────────────── Slave Address = 0x11  
  
- RTU: Remote Termimal Unit.  
  
###2. Function code:   
| Function Code | Name                         | Description                               | Access Type     |
| ------------- | ---------------------------- | ----------------------------------------- | --------------- |
| `0x01`        | **Read Coils**               | Read 1-bit digital outputs (coils)        | Read (Discrete) |
| `0x02`        | **Read Discrete Inputs**     | Read 1-bit digital inputs                 | Read (Discrete) |
| `0x03`        | **Read Holding Registers**   | Read 16-bit registers (read/write memory) | Read (Analog)   |
| `0x04`        | **Read Input Registers**     | Read 16-bit read-only input registers     | Read (Analog)   |
| `0x05`        | **Write Single Coil**        | Write a single digital output (coil)      | Write           |
| `0x06`        | **Write Single Register**    | Write to one 16-bit holding register      | Write           |
| `0x0F`        | **Write Multiple Coils**     | Write multiple digital outputs            | Write           |
| `0x10`        | **Write Multiple Registers** | Write multiple 16-bit holding registers   | Write           |


