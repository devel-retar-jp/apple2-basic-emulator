/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// 
/// dumpTool.cpp
/// Dump Tool
/// 
///	
///   History	
///   2026/06/28 V1.00 First
///
///
///                        Copyright(c) 2026, Retar.jp, All Rights Reserved.
///                        http://www.retar.jp/
/// 
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///
///  ■ Usage
///
///     dumpTool.exe -f <target file> [-b|-h|-d]
///
///     -b : bit string  -> <target file name>_BYTE.txt
///     -h : hex         -> <target file name>_HEX.txt
///     -d : decimal     -> <target file name>_DEC.txt
///     (none)       -> output all three of the above
///
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "framework.h"
#include "getoptCMD.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Function that converts a file name
//
//   Returns the input path without its extension, with conv appended.
//   e.g. data.bin + "_HEX.txt" -> data_HEX.txt
std::string make_conv_filename(
	const std::string& path,
	const std::string& conv
)
{
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Path separator (Windows)
	const char sep[] = "\\";
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Split into the directory part and the file name part
	size_t pos_sep = path.find_last_of(sep);
	std::string dir;
	std::string fname;
	//
	// If there is no directory, set dir to an empty string
	if (pos_sep == std::string::npos)
	{
		dir = "";
		fname = path;
	}
	else
	{
		dir = path.substr(0, pos_sep + 1);
		fname = path.substr(pos_sep + 1);
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Find the position of the extension
	size_t pos_dot = fname.find_last_of('.');
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// If there is no extension, use the whole file name as base
	std::string base;
	if (pos_dot == std::string::npos)
	{
		// No extension
		base = fname;
	}
	else
	{
		// A leading '.' (e.g. ".gitignore") is not treated as an extension
		if (pos_dot == 0) {
			base = fname;  // ".gitignore" -> ".gitignore_CONV.bin"
		}
		else {
			base = fname.substr(0, pos_dot);
		}
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// New file name
	std::string convStr = base + conv;// L"_CONV.bin";
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Join the directory and the new file name and return it
	return dir + convStr;
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Write to the specified path in 8-bit units
//
//   The notation is switched by write_mode.
//   16 bytes per line, with the serial index range at the start of each line.
bool save_ascii_file(
	const std::string& path,
	const std::vector<uint8_t>& data,
	const int write_mode = 1  // 1: hex, 2: decimal, 3: binary (bit string)
)
{
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Open the path safely using the Win32 API fopen_s
	FILE* fp = nullptr;
	errno_t err = fopen_s(&fp, path.c_str(), "w");
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Error handling when the file cannot be opened
	if (err != 0 || fp == nullptr)
	{
		// Could not open
		std::cerr << "[ERROR] Cannot open file: " << path << std::endl;
		return false;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Write //2^64-1=18446 74407 37095 51615
	size_t index = 0;
	//
	// Write out, inserting a newline every 16 bytes
	for (const auto& byte : data)
	{
		// Show the position (index) at the start of the line
		if (index % 16 == 0)
		{
			// Output in the form 0000000000 - 0000000016
			size_t start = index;
			size_t end = index + 15;  // 16 bytes

			if (fprintf(fp, "%020zu - %020zu : ", start, end) < 0)
			{
				std::cerr << "[ERROR] Write failed: " << path << std::endl;
				fclose(fp);
				return false;
			}
		}
		//
		// Write according to write_mode
		if (write_mode == 2)
		{
			// Write in decimal
			if (fprintf(fp, "%d ", byte) < 0)
			{
				std::cerr << "[ERROR] Write failed: " << path << std::endl;
				fclose(fp);
				return false;
			}
		}
		else if (write_mode == 3)
		{
			// Write in binary (bit string)
			//
			//  Note that bits are ordered LSB first.
			//  This is the same order as the bit handling on the encryption side (encodeCPU.cpp),
			//  and this format is easier to read when tracing how the bitmap takes effect.
			uint8_t b = byte;
			std::bitset<8> bits(b);
			if (
				fprintf(fp, "%d", bits[0] ? 1 : 0) < 0 ||
				fprintf(fp, "%d", bits[1] ? 1 : 0) < 0 ||
				fprintf(fp, "%d", bits[2] ? 1 : 0) < 0 ||
				fprintf(fp, "%d", bits[3] ? 1 : 0) < 0 ||
				fprintf(fp, "%d", bits[4] ? 1 : 0) < 0 ||
				fprintf(fp, "%d", bits[5] ? 1 : 0) < 0 ||
				fprintf(fp, "%d", bits[6] ? 1 : 0) < 0 ||
				fprintf(fp, "%d ", bits[7] ? 1 : 0) < 0
				)
			{
				std::cerr << "[ERROR] Write failed: " << path << std::endl;
				fclose(fp);
				return false;
			}
		}
		else
		{
			// By default, write in hex
			if (fprintf(fp, "%02X ", byte) < 0)
			{
				std::cerr << "[ERROR] Write failed: " << path << std::endl;
				fclose(fp);
				return false;
			}
		}
		//
		// Update the index
		index++;
		//
		// Insert a newline every 16 bytes
		if (index % 16 == 0)
		{
			if (fprintf(fp, "\n") < 0)
			{
				std::cerr << "[ERROR] 16 Bytes : Write failed : " << path << std::endl;
				fclose(fp);
				return false;
			}
		}
	}
	//
	// If the last line is shorter than 16 bytes, add a newline (optional)
	if (index % 16 != 0)
	{
		fprintf(fp, "\n");
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Close the file
	fclose(fp);
	return true;
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
	//printf("argc = %d\n", argc);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Read the file and parse the options
	std::cout << "------------------------------------------------------------------------------------------------" << std::endl;
	auto [contents, opt_f, opt_b, opt_h, opt_d] = readFromFile(argc, argv);
	std::cout << "------------------------------------------------------------------------------------------------" << std::endl;
	std::cout << "Contents Size : " << contents.size() << std::endl;
	std::cout << "In File : " << opt_f << std::endl;
	std::cout << "Bytes : " << std::to_string(opt_b) << std::endl;
	std::cout << "Hex : " << std::to_string(opt_h) << std::endl;
	std::cout << "Decimal : " << std::to_string(opt_d) << std::endl;
	std::cout << "------------------------------------------------------------------------------------------------" << std::endl;
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Switch the console to SJIS
	SetConsoleOutputCP(CP_ACP);
	setvbuf(stdout, nullptr, _IOFBF, 4096);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Set the console title / start
	SetConsoleTitleA("Dump Tool");
	std::cout << "Dump Tool Start : \n";
	std::cout << "------------------------------------------------------------------------------------------------" << std::endl;
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//std::string conv_filename = make_conv_filename("test", "_CONV.bin");
	//std::cout << "Converted Filename : " << conv_filename << std::endl;
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Build the output file names
	auto byte_data = make_conv_filename(opt_f, "_BYTE.txt");
	auto hex_data = make_conv_filename(opt_f, "_HEX.txt");
	auto decimal_data = make_conv_filename(opt_f, "_DEC.txt");
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Byte Dump
	if (opt_b == TRUE && opt_h == FALSE && opt_d == FALSE)
	{
		std::cout << "Byte Dump : \n";
		save_ascii_file(byte_data, contents, 3);
		std::cout << "Saved files :" << byte_data << "\n";
	}
	else if (opt_b == FALSE && opt_h == TRUE && opt_d == FALSE)
	{
		std::cout << "Hex Dump : \n";
		save_ascii_file(hex_data, contents, 1);
		std::cout << "Saved files :" << hex_data << "\n";
	}
	else if (opt_b == FALSE && opt_h == FALSE && opt_d == TRUE)
	{
		std::cout << "Decimal Dump : \n";
		save_ascii_file(decimal_data, contents, 2);
		std::cout << "Saved files :" << decimal_data << "\n";
	}
	else
	{
		std::cout << "ALL Dump : \n";
		save_ascii_file(byte_data, contents, 3);
		save_ascii_file(hex_data, contents, 1);
		save_ascii_file(decimal_data, contents, 2);
		//
		std::cout << "Saved files :" << byte_data << "\n";
		std::cout << "Saved files :" << hex_data << "\n";
		std::cout << "Saved files :" << decimal_data << "\n";
	}
	std::cout << "------------------------------------------------------------------------------------------------" << std::endl;
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Set the console title / end
	std::cout << "Dump Tool End : \n";
	std::cout << "------------------------------------------------------------------------------------------------" << std::endl;
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
