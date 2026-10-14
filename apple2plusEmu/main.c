/// ------------------------------------------------------------------
/// 
/// 6502 BASIC Emulator /main.c
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
// -------------------------------------------------------------------
#include "libRun.h"
// -------------------------------------------------------------------
int main(int argc, char** argv)
{
	//
	//Initialize memory
	memset(memory, 0, sizeof(memory));
	//
	//ROM Load
	FILE* fb = fopen("basic.bin", "rb");
	if (fb == NULL) {
		fprintf(stderr, "Error: Cannot open ROM file 'basic.bin'\n");
		fprintf(stderr, "  Reason: %s\n", strerror(errno));
		return 0; 
	}
	fread(&memory[0xD000], 1, 0x2800, fb);  // BASIC 10KB
	fclose(fb);
	//
	FILE* fm = fopen("monitor.bin", "rb");
	if (fm == NULL) {
		fprintf(stderr, "Error: Cannot open ROM file 'monitor.bin'\n");
		fprintf(stderr, "  Reason: %s\n", strerror(errno));
		return 0;
	}
	fread(&memory[0xF800], 1, 0x0800, fm);  // Monitor 2KB
	fclose(fm);
	//
	host_state_share host;
	memset(&host, 0, sizeof(host));
	host.memory = memory;
	//
	//System reset
	fake6502_context ctx;
	ctx.state_host = &host;
	fake6502_reset(&ctx);
	//
	/* Script setting -> hard-coded in source */
	//const char* scriptStr = "10 PRINT 123\r20 PRINT 234\r30 PRINT 345\r40 PRINT 456\r50 PRINT 567\r60 PRINT 678\r70 PRINT 789\r80 PRINT 890\r90 END\rRUN\r";
	//ctx.script = scriptStr;
	//
	/* Script execution function */
	ctx.script = readFromBasic(argc, argv);
	//
	// ---------------------------------------------------------------
	//ROM FileName
	char* filename = getROMFileName(argc, argv);
	// ---------------------------------------------------------------
	///* Ten sets of 95-byte shuffled characters starting at 0x3000 */
	int mem = 0x3000;
	initRotorROM(filename, mem);
	// ---------------------------------------------------------------
	/* Inject jitter into $0300 after BASIC initialization */
	/* SEED for RND */
	memory[0x300] = getJitterByte(20, 200);
	// ---------------------------------------------------------------
	for (int i = 0; i < 10000000; ++i) 
	{
		fake6502_step(&ctx);
	}
	//
	printf("----------------------------------------\n");
	// ---------------------------------------------------------------
	for (int row = 0; row < 24; row++)
	{
		// Apple II row-interleaved layout
		int base = 0x0400
			+ (row & 0x07) * 0x80
			+ (row >> 3) * 0x28;
		//
		for (int col = 0; col < 40; col++)
		{
			int addr = base + col;
			//
			unsigned char ch = memory[addr] & 0x7F;
			//
			// Apple II control codes -> convert to uppercase
			if (ch < 0x20)
			{
				ch += 0x40;
			}
			//
			putchar(ch);
		}
		putchar('\n');
	}
	printf("----------------------------------------\n");
	return 0;
}
// -------------------------------------------------------------------
