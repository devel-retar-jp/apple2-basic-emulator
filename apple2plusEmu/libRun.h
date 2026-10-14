/// ------------------------------------------------------------------
/// 
/// 6502 BASIC Emulator /libRun.h
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
#pragma once
// -------------------------------------------------------------------
#include "fake6502.h"
//
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// -------------------------------------------------------------------
// Memory
unsigned char memory[65536];
// -------------------------------------------------------------------
typedef struct host_state {
	uint8_t* memory;
} host_state_share;
// -------------------------------------------------------------------
static int script_pos = 0;
static uint8_t kbd_data = 0;
static int key_pressed = 0;
// -------------------------------------------------------------------
unsigned char getJitterByte(int min, int max);
// -------------------------------------------------------------------
void initRotorROM(const char* filename, int mem);
void loadRotorFromFile(const char* filename, int mem);
void saveRotorToFile(const char* filename);
void saveRotorToFile6502(const char* filename);
void saveReverseRotorToFile(const char* filename);
// -------------------------------------------------------------------
void shuffleRotor(uint8_t* rotor, int n);
void shuffleRotorMore(uint8_t* rotor, int n);
// -------------------------------------------------------------------
