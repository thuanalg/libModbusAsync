cmake_minimum_required(VERSION 3.15)
project(modbus_async_project)

# === Sources ===
set(SOURCE_LIB_MODBUS_ASYNC_FILES src/ModbusAsync.c)
set(SOURCE_TEST_MODULE_FILES tests/console/main.c)
#set(SOURCE_MFC_MODULE_FILES 
#	tests/testMFC/testSerialPort/testSerialPort/framework.h
#	tests/testMFC/testSerialPort/testSerialPort/pch.cpp
#	tests/testMFC/testSerialPort/testSerialPort/pch.h
#	tests/testMFC/testSerialPort/testSerialPort/resource.h
#	tests/testMFC/testSerialPort/testSerialPort/targetver.h
#	tests/testMFC/testSerialPort/testSerialPort/testSerialPort.cpp
#	tests/testMFC/testSerialPort/testSerialPort/testSerialPort.h
#	tests/testMFC/testSerialPort/testSerialPort/testSerialPort.rc
#	tests/testMFC/testSerialPort/testSerialPort/testSerialPortDlg.cpp
#	tests/testMFC/testSerialPort/testSerialPort/testSerialPortDlg.h
#	tests/testMFC/testSerialPort/testSerialPort/res/testSerialPort.ico
#	tests/testMFC/testSerialPort/testSerialPort/res/testSerialPort.rc2
#)

# === Include main headers ===
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# === Define shared library ===
add_library(ModbusAsync SHARED ${SOURCE_LIB_MODBUS_ASYNC_FILES})

# === Platform-specific defines ===
if(DEFINED UNIX_LINUX)
	target_compile_definitions(ModbusAsync PUBLIC UNIX_LINUX=1)
	if(DEFINED MACOSX)
		target_compile_definitions(ModbusAsync PUBLIC __MACH__=1)
	else()
#		target_compile_definitions(ModbusAsync PUBLIC __SPSR_EPOLL__=1)
	endif()
	set_target_properties(ModbusAsync PROPERTIES VERSION 1.0.0 SOVERSION 1)
else()
	target_compile_definitions(ModbusAsync PUBLIC EXPORT_DLL_API_MODBUS_ASYNC=1)
	target_compile_definitions(ModbusAsync PUBLIC _CRT_SECURE_NO_WARNINGS=1)
endif()

# === Link SimpleLog if not in embedded environment ===
if(NOT DEFINED META_OPENEMBEDDED)
	if(DEFINED HEADER_SIMPLELOG)
		message(STATUS "Using SimpleLog header at: ${HEADER_SIMPLELOG}")
		target_include_directories(ModbusAsync PUBLIC "${HEADER_SIMPLELOG}")
	else()
		message(FATAL_ERROR
			"\n[SimpleLog Missing]\n"
			"HEADER_SIMPLELOG is not defined.\n"
			"Please install SimpleLog-Topic from: https://github.com/thuanalg/simplelog-topic\n"
			"Then pass the header path using:\n"
			"  -DHEADER_SIMPLELOG=/path/to/simplelog/include"
		)
	endif()

	if(DEFINED LIB_PATH_SIMPLELOG)
		message(STATUS "Using SimpleLog library path: ${LIB_PATH_SIMPLELOG}")
		target_link_directories(ModbusAsync PUBLIC "${LIB_PATH_SIMPLELOG}")
	else()
		message(FATAL_ERROR
			"\n[SimpleLog Missing]\n"
			"LIB_PATH_SIMPLELOG is not defined.\n"
			"Please install SimpleLog-Topic from: https://github.com/thuanalg/simplelog-topic\n"
			"Then pass the library path using:\n"
			"  -DLIB_PATH_SIMPLELOG=/path/to/simplelog/lib"
		)
	endif()

	if(DEFINED HEADER_SERIALMODULE)
		message(STATUS "Using SerialModule header at: ${HEADER_SERIALMODULE}")
		target_include_directories(ModbusAsync PUBLIC "${HEADER_SERIALMODULE}")
	else()
		message(FATAL_ERROR
			"\n[SerialModule Missing]\n"
			"HEADER_SERIALMODULE is not defined.\n"
			"Please install libserialmodule from: https://github.com/thuanalg/libserialmodule\n"
			"Then pass the header path using:\n"
			"  -DHEADER_SERIALMODULE=/path/to/libserialmodule/include"
		)
	endif()

	if(DEFINED LIB_PATH_SERIALMODULE)
		message(STATUS "Using SimpleLog library path: ${LIB_PATH_SERIALMODULE}")
		target_link_directories(ModbusAsync PUBLIC "${LIB_PATH_SERIALMODULE}")
	else()
		message(FATAL_ERROR
			"\n[SimpleLog Missing]\n"
			"LIB_PATH_SERIALMODULE is not defined.\n"
			"Please install libserialmodule from: https://github.com/thuanalg/libserialmodule\n"
			"Then pass the library path using:\n"
			"  -DLIB_PATH_SERIALMODULE=/path/to/libserialmodule/lib"
		)
	endif()
endif()

# === Executable: test_ModbusAsync (pure C) ===
add_executable(test_ModbusAsync ${SOURCE_TEST_MODULE_FILES})
if(DEFINED UNIX_LINUX)
	target_compile_definitions(test_ModbusAsync PUBLIC UNIX_LINUX=1)
else()
	target_compile_definitions(test_ModbusAsync PUBLIC _CRT_SECURE_NO_WARNINGS=1 )
endif()

target_link_libraries(test_ModbusAsync 
	simplelog
	ModbusAsync
)

# === Visual Studio only: include existing .vcxproj ===
#if(MSVC)
#	add_executable(testMFCModbusAsync WIN32 ${SOURCE_MFC_MODULE_FILES})
#	target_compile_definitions(testMFCModbusAsync PUBLIC _CRT_SECURE_NO_WARNINGS=1 _AFXDLL=1)
#	target_link_libraries(testMFCModbusAsync 
#		simplelog
#		serialmodule
#		ModbusAsync
#	)	
#	# Enable MFC
#	set_target_properties(testMFCModbusAsync PROPERTIES
#	    USES_MFC 2
#	)	
#endif()

# === Installation section for Unix/Linux ===
if(DEFINED UNIX_LINUX)
	install(TARGETS ModbusAsync LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
	install(FILES include/ModbusAsync.h DESTINATION include)
endif()

# === Link for ModbusAsync ===
target_link_libraries(ModbusAsync 
	serialmodule
	simplelog
)
#cmake .. -DUNIX_LINUX=1 -DHEADER_SIMPLELOG=/usr/local/include -DLIB_PATH_SIMPLELOG=/usr/local/lib -DHEADER_SERIALMODULE=/usr/local/include -DLIB_PATH_SERIALMODULE=/usr/local/lib 
