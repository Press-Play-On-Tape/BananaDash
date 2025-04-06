#pragma once
#include "../../fxdata/fxdata.h"
#include "../../fxdata/images/Images.h"

#define DEBUG_PRINT    Serial.print
#define DEBUG_PRINTLN  Serial.println
#define DEBUG_BREAK    asm volatile("break\n");

#define _DEBUG


namespace Constants {

	constexpr uint8_t StackSize_Player = 20;
	constexpr uint8_t StackSize_Enemy = 20;
	
	constexpr uint8_t Item_Count = 5;
	constexpr uint8_t Enemy_Count = 5;
	
//	constexpr uint8_t Puff_Max = 7 * 16;
	constexpr uint8_t Puff_Max = 7 * 8;


	constexpr uint8_t Level_30 = 14;
	constexpr uint8_t Level_25 = 22;
	constexpr uint8_t Level_20 = 30;
	constexpr uint8_t Level_15 = 38;
	constexpr uint8_t Level_10 = 46;

}

