/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// framework.h
//
//  ■ Role of this header
//    Common aggregated include header for the helper tools.
//    A lighter configuration than the one used by the main encryption code
//    (encodeDummy / decodeDummy / spanToUint64_tDll);
//    it does not include <random> / <span> / <immintrin.h>.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define WIN32_LEAN_AND_MEAN        
#include <windows.h>
#include <commctrl.h>
//
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
//
#include <thread>
#include <iostream>
#include <string>
#include <time.h>
#include <cstdio>
#include <io.h>
#include <sstream>
#include <fstream>
#include <fcntl.h>
#include <stddef.h>
#include <vector>
#include <iomanip>
#include <chrono>
#include <shellapi.h>
#include <cstdint>
#include <regex>
#include <bitset> 
#include <cstdlib>
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
