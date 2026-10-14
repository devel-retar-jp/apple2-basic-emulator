/// ------------------------------------------------------------------
/// 
/// 6502 BASIC Emulator /libRun.c
/// 
/// 
/// 
///	
///   History	
///   2026/09/11 V1.00 First
///
///
///                        Copyright(c) 2026, Retar.jp, All Rights Reserved.
///                        http://www.retar.jp/
/// 
/// ------------------------------------------------------------------
#include "fake6502.h"
//
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// -------------------------------------------------------------------
#include "libRun.h"
// ---------------------------------------------------------------
void initRotorROM(const char* filename, int mem)
{
	//const char* filename = "USERROM.bin";
	FILE* fpIn = fopen(filename, "rb");
	int fEx = (fpIn != NULL);
	if (fpIn)
	{
		fclose(fpIn);
	}
	//
	//Write / read the file
	if (fEx)
	{
		loadRotorFromFile(filename, mem);
	}
	else
	{
		// FOR APPLE 2 ROM
		saveRotorToFile6502(filename);
		loadRotorFromFile(filename, mem);
		saveReverseRotorToFile(filename);
	}
	//
	return;
}
// -------------------------------------------------------------------
void loadRotorFromFile(const char* filename, int mem)
{
	FILE* fp = fopen(filename, "rb");
	if (!fp) return;
	//
	// 10 sets x 96 bytes
	uint8_t buf[96 * 10];
	fread(buf, 1, 96 * 10, fp);
	fclose(fp);
	//
	for (int i = 0; i < 96 * 10; i++)
	{
		memory[mem + i] = buf[i];
	}
}
// -------------------------------------------------------------------
// FOR APPLE 2 ROM
void saveRotorToFile6502(const char* filename)
{
	FILE* fp = fopen(filename, "wb");
	if (!fp) return;
	//
	uint8_t rotor[96] = { 0xFF };
	memset(rotor, 0xFF, sizeof(rotor));
	for (int X = 0; X < 10; X++)
	{
		//APPLE 2 PLUS CHARS
		shuffleRotorMore(rotor, 61);	// 95 -> 61 CHARS		
		// ★ Save in 96-byte steps (matches Apple II)
		fwrite(rotor, 1, 96, fp);
	}
	//
	fclose(fp);
}
// -------------------------------------------------------------------
//FULL ASCII CHARS ROM
void saveRotorToFile(const char* filename)
{
	FILE* fp = fopen(filename, "wb");
	if (!fp) return;
	//
	uint8_t rotor[96] = { 0xFF };
	memset(rotor, 0xFF, sizeof(rotor));
	for (int X = 0; X < 10; X++)
	{
		shuffleRotorMore(rotor, 95);
		// ★ Save in 96-byte steps (matches Apple II)
		fwrite(rotor, 1, 96, fp);
	}
	//
	fclose(fp);
}
// -------------------------------------------------------------------
void saveReverseRotorToFile(const char* filename)
{
	// Build XXX_REV.bin from the original file name
	char filename_rev[256];
	{
		// Strip the .bin extension
		char base[256];
		strcpy_s(base, sizeof(base), filename);
		char* p = strrchr(base, '.');
		if (p)
		{
			*p = '\0';
		}
		//
		// Generate XXX_REV.bin
		sprintf_s(filename_rev, sizeof(filename_rev), "%s_REV.bin", base);
	}
	//
	// Load the original forward ROM
	FILE* fpIn = fopen(filename, "rb");
	if (!fpIn) return;
	//
	uint8_t forward[96 * 10];
	fread(forward, 1, 96 * 10, fpIn);
	fclose(fpIn);
	//
	// Reverse ROM area
	uint8_t reverse[96 * 10];
	memset(reverse, 0xFF, sizeof(reverse));
	//
	// ★ Generate the inverse mapping
	for (int block = 0; block < 10; block++)
	{
		uint8_t* F = &forward[block * 96];
		uint8_t* R = &reverse[block * 96];
		//
		//  95 -> 61 CHARS
		for (int i = 0; i < 61; i++)
		{
			uint8_t v = F[i];
			// v is in the range 0-255, so write i at that position
			R[v] = i;
		}
	}
	//
	// ★ Save to XXX_REV.bin
	FILE* fpOut = fopen(filename_rev, "wb");
	if (!fpOut)
	{
		return;
	}
	fwrite(reverse, 1, 96 * 10, fpOut);
	fclose(fpOut);
	//
	return;
}
// -------------------------------------------------------------------
void shuffleRotor(uint8_t* rotor, int n)
{
	for (int i = 0; i < n; i++)
	{
		rotor[i] = i;   // Initialize 0 to n-1
	}
	//
	for (int i = n - 1; i > 0; i--)
	{
		int j = rand() % (i + 1);  // Random number 0 to i
		uint8_t tmp = rotor[i];
		rotor[i] = rotor[j];
		rotor[j] = tmp;
	}
}
// -------------------------------------------------------------------
void shuffleRotorMore(uint8_t* rotor, int n)
{
	// Initialize
	for (int i = 0; i < n; i++) {
		rotor[i] = i;
	}

	// Stage 1: Fisher-Yates
	for (int i = n - 1; i > 0; i--) {
		int j = getJitterByte(0, i);   // ★ Drop rand()
		uint8_t tmp = rotor[i];
		rotor[i] = rotor[j];
		rotor[j] = tmp;
	}

	// Stage 2: extra scrambling (add chaos)
	for (int k = 0; k < 200; k++) {
		int a = getJitterByte(0, n - 1);
		int b = getJitterByte(0, n - 1);
		uint8_t tmp = rotor[a];
		rotor[a] = rotor[b];
		rotor[b] = tmp;
	}
}
// -------------------------------------------------------------------
unsigned char getJitterByte(int min, int max)
{
	static unsigned int seed = 0;

	if (seed == 0) {
		seed = (unsigned int)time(NULL);   /* Jitter at one-second resolution */
	}

	seed = seed * 1103515245 + 12345;
	unsigned int r = (seed >> 16) & 0x7FFF;
	return (unsigned char)(min + (r % (max - min + 1)));
}
// -------------------------------------------------------------------
/* Read from Basic Script */
static char* inBASIC = NULL;
char* readFromBasic(int argc, char** argv)
{
	//Check arguments
	if (argc < 2)
	{
		printf("Usage: apple2emu <script.bas>\n");
		exit(1);
	}
	//
	const char* filename = argv[1];
	FILE* fp = fopen(filename, "r");
	if (!fp) {
		printf("Cannot open %s\n", filename);
		exit(1);
	}
	//
	// Get the file size
	fseek(fp, 0, SEEK_END);
	long fsize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	if (fsize == 0)
	{
		exit(0);
	}
	//
	/* Allocate the read buffer */
	char* buf = (char*)malloc(fsize + 1);
	memset(buf, 0, fsize + 1);
	fread(buf, 1, fsize, fp);
	buf[fsize] = '\0';
	fclose(fp);
	//
	// Convert newlines -> CR to make a single line
	// The maximum size is unchanged, so the buffer can be reused as is
	for (long i = 0; i < fsize; i++)
	{
		if (buf[i] == '\n') buf[i] = '\r';
	}
	//
	// Append a trailing CR (needed after RUN)
	inBASIC = (char*)malloc(fsize + 2);
	memset(inBASIC, 0, fsize + 2);
	strcpy_s(inBASIC, fsize + 2, buf);
	strcat_s(inBASIC, fsize + 2, "\r");
	//
	free(buf);
	//
	return inBASIC;
}
// -------------------------------------------------------------------
//ROM FileName
static char* inROMFileName = NULL;
const char* inROMFileNameDef = "USERROM.bin";
char* getROMFileName(int argc, char** argv)
{
	// Use the second argument if it is given
	if (argc >= 3 && argv[2] && argv[2][0] != '\0')
	{
		size_t len = strlen(argv[2]);
		inROMFileName = (char*)malloc(len + 1);
		strcpy_s(inROMFileName, len + 1, argv[2]);
		return inROMFileName;
	}
	//
	// Otherwise use the default 
	size_t len = strlen(inROMFileNameDef);
	inROMFileName = (char*)malloc(len + 1);
	strcpy_s(inROMFileName, len + 1, inROMFileNameDef);
	//
	return inROMFileName;
}
// -------------------------------------------------------------------
uint8_t fake6502_mem_read(fake6502_context* c, uint16_t addr)
{
	// Keyboard read: $C000
	if (addr == 0xC000)
	{
		if (!key_pressed && c->script[script_pos] != '\0')
		{
			kbd_data = ((uint8_t)c->script[script_pos]) | 0x80;
			key_pressed = 1;
		}
		return key_pressed ? kbd_data : 0x00;
	}
	//
	// Strobe clear: $C010
	if (addr == 0xC010) {
		if (key_pressed) {
			key_pressed = 0;
			script_pos++;
		}
		return 0x00;
	}
	//
	return ((host_state_share*)c->state_host)->memory[addr];
}
// -------------------------------------------------------------------
void fake6502_mem_write(fake6502_context* c, uint16_t addr, uint8_t val)
{
	// Strobe clear: $C010
	if (addr == 0xC010) {
		if (key_pressed) {
			key_pressed = 0;
			script_pos++;
		}
		return;
	}
	//
	// ★ RAM write
	((host_state_share*)c->state_host)->memory[addr] = val;
}
// -------------------------------------------------------------------
unsigned char read6502(unsigned short address) {
	return memory[address];
}
// -------------------------------------------------------------------
