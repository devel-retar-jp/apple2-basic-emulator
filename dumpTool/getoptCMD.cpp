/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// 
/// getopt custom file
/// 
/// 
/// 
///	
///   History	
///   2021/12/06 V1.00 First
///
///
///                        Copyright(c) 2021, Retar.jp, All Rights Reserved.
///                        http://www.retar.jp/
/// 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
///  ■ Role of this file
///
///  Command-line argument parsing for the dump tool.
///
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <time.h>       /* time */
#include <sstream>
#include <vector>
#include <regex>
#include <random>
#include <iomanip>
#include <cmath>
#include <limits>
#include "getopt.h"
#include "getoptCMD.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Read the file
// -f : input
// 
// -b : bit display
// -h : hexadecimal display
// -d : decimal display
//
//   Reads the whole specified file into memory
//   and returns it together with the display-format flags.
std::tuple <
	std::vector<uint8_t>,
	std::string,
	BOOLEAN,
	BOOLEAN,
	BOOLEAN
>
readFromFile(int argc, char* argv[])
{
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///Return value (file contents)
	std::vector<uint8_t> contents;
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//getopt
	auto opts = get_option(argc, argv);
	char* opt_f = opts[0];
	std::string opt_f_s = std::string(opt_f);
	BOOLEAN opt_b = *opts[1];
	BOOLEAN opt_h = *opts[2];
	BOOLEAN opt_d = *opts[3];
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Read the data file
	std::ifstream ifs(opt_f, std::ios::binary);
	if (!ifs)
	{
		std::wcerr << L"[ERROR] Cannot open file : " << opt_f << std::endl;
		exit(-1);
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Get the file size
	ifs.seekg(0, std::ios::end);
	std::streampos size = ifs.tellg();
	if (size <= 0)
	{
		std::wcerr << L"[ERROR] Invalid file size : " << opt_f << std::endl;
		exit(-1);
	}
	ifs.seekg(0, std::ios::beg);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Read
	contents.resize(static_cast<size_t>(size));
	if (!ifs.read(reinterpret_cast<char*>(contents.data()), size))
	{
		std::wcerr << L"[ERROR] Cannot read file : " << opt_f << std::endl;
		exit(-1);
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	return std::make_tuple(contents, opt_f, opt_b, opt_h, opt_d);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Extract the option values
std::vector<char*> get_option(int argc, char* argv[])
{
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//getopt
	//https://github.com/takamin/win-c
	//
	// Option definitions. Only f takes an argument
	// -f : input
	// 
	// -b : bit display
	// -h : hexadecimal display
	// -d : decimal display
	//
	char const* optstring = "f:bhd";
	char* opt_f = fDefault;
	char* opt_b = &bDefault;
	char* opt_h = &hDefault;
	char* opt_d = &dDefault;
	//
	// Return value
	std::vector<char*> rets;
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Parse the options
	int opt = 0;
	while ((opt = getopt(argc, argv, optstring)) != -1)
	{
		switch (opt)
		{
		case 'f':
			// -f : input file name
			opt_f = optarg;
			break;
		case 'b':
			// -b : bit display
			*opt_b = TRUE;
			break;
		case 'h':
			// -h : hexadecimal display
			*opt_h = TRUE;
			break;
		case 'd':
			// -d : decimal display
			*opt_d = TRUE;
			break;
		default:
			break;
		}
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Non-option parameters
	char* noptarg = argv[optind++];
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// -f : finalize the input file name
	if (opt_f == NULL)
	{
		std::cout << "opt_f Default : " << opt_f << std::endl;
	}
	else
	{
		std::cout << "opt_f : " << opt_f << std::endl;
	}
	rets.push_back(opt_f);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// -b -h -d : display format selection
	//
	//  If exactly one is given, that format is used;
	//  if several or none are given, all are set to FALSE.
	//  (the caller, dumpTool.cpp, interprets this as "output all formats")
	if (*opt_b == FALSE && *opt_h == FALSE && *opt_d == TRUE)
	{
		std::cout << "opt_b Default : " << std::to_string(*opt_b) << std::endl;
		std::cout << "opt_h Default : " << std::to_string(*opt_h) << std::endl;
		std::cout << "opt_d Default : " << std::to_string(*opt_d) << std::endl;
	}
	else if (*opt_b == FALSE && *opt_h == TRUE && *opt_d == FALSE)
	{
		std::cout << "opt_b Default : " << std::to_string(*opt_b) << std::endl;
		std::cout << "opt_h Default : " << std::to_string(*opt_h) << std::endl;
		std::cout << "opt_d Default : " << std::to_string(*opt_d) << std::endl;
	}
	else if (*opt_b == TRUE && *opt_h == FALSE && *opt_d == FALSE)
	{
		std::cout << "opt_b Default : " << std::to_string(*opt_b) << std::endl;
		std::cout << "opt_h Default : " << std::to_string(*opt_h) << std::endl;
		std::cout << "opt_d Default : " << std::to_string(*opt_d) << std::endl;
	}
	else
	{
		*opt_b = FALSE;
		*opt_h = FALSE;
		*opt_d = FALSE;
		//
		std::cout << "opt_b Default : " << std::to_string(*opt_b) << std::endl;
		std::cout << "opt_h Default : " << std::to_string(*opt_h) << std::endl;
		std::cout << "opt_d Default : " << std::to_string(*opt_d) << std::endl;
	}
	rets.push_back(opt_b);
	rets.push_back(opt_h);
	rets.push_back(opt_d);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	return rets;
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function that checks whether a string is an integer
bool isInteger(const char* s, long& out)
{
	// Check that the string is not empty
	if (s == nullptr || *s == '\0')
	{
		return false;
	}
	//
	// Convert the string to an integer
	char* endptr = nullptr;
	errno = 0;
	//
	// Convert as base 10
	long val = std::strtol(s, &endptr, 10);
	//
	// Check the conversion result
	if (endptr == s)            // Could not convert
		return false;

	if (*endptr != '\0')        // Trailing garbage characters remain
		return false;

	if (errno == ERANGE)        // Overflow
		return false;

	out = val;
	return true;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
