/**
 * @file Main.cpp
 * @author silvio3105 (www.github.com/silvio3105)
 * @brief Main source file.
 * 
 * @copyright Copyright (c) 2026, silvio3105 (www.github.com/silvio3105)
 * 
 */

/*
	Copyright (c) 2026, silvio3105 (www.github.com/silvio3105)

	Access and use of this Project and its contents are granted free of charge to any Person.
	The Person is allowed to copy, modify and use The Project and its contents only for education and DIY purposes.
	Commercial use of the Project, in whole or in part, is prohibited without prior written permission from the Author.
	This License may not be modified and no sublicense may be granted.

	THE PROJECT AND ITS CONTENTS ARE PROVIDED "AS IS" WITH ALL FAULTS AND WITHOUT EXPRESS OR IMPLIED WARRANTY.
	THE AUTHOR KEEPS ALL RIGHTS TO CHANGE OR REMOVE THE CONTENTS OF THIS PROJECT WITHOUT PRIOR NOTICE.
	IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY CLAIM, DAMAGES, OR OTHER LIABILITY ARISING FROM THE USE OF THE PROJECT.

	A copy of this License must be included with all copies and substantial portions of the Project.
*/

// ----- INCLUDE FILES
#include			"SEGGER_RTT.h"
#include			"sBuildInfo.h"

#include			<stdio.h>


// ----- VARIABLES
__SBI("Test_FW", "v1.0.0rc1", "v4.2.0", "");


// ----- FUNCTION DEFINITIONS
/**
 * @brief Application main function.
 * 
 * @return No return value.
 */
int main(void)
{
	char tmp[86];
	uint8_t len = snprintf(tmp, sizeof(tmp), "\n\nBuild %s %s\nHW %s\n%s %s\n%luB\nHash %08lX\n---",
	SBI_NAME, SBI_VERSION,
	SBI_HARDWARE,
	SBI_DATE,
	SBI_TIME,
	SBI_SIZE,
	SBI_HASH);

	SEGGER_RTT_Init();
	
	while(1)
	{
		SEGGER_RTT_Write(0, tmp, len);
		for (uint32_t i = 0; i < 0xFFFFFF; i++)
		{
			(void)i;
		}
	}
}


// END WITH NEW LINE
