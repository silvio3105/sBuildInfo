/**
 * @file Main.cpp
 * @author silvio3105 (www.github.com/silvio3105)
 * @brief Main source file.
 * 
 * @copyright Copyright (c) 2023, silvio3105
 * 
 */

/*
	Copyright (c) 2023, silvio3105 (www.github.com/silvio3105)

	Access and use of this Project and its contents are granted free of charge to any Person.
	The Person is allowed to copy, modify and use The Project and its contents only for non-commercial use.
	Commercial use of this Project and its contents is prohibited.
	Modifying this License and/or sublicensing is prohibited.

	THE PROJECT AND ITS CONTENT ARE PROVIDED "AS IS" WITH ALL FAULTS AND WITHOUT EXPRESSED OR IMPLIED WARRANTY.
	THE AUTHOR KEEPS ALL RIGHTS TO CHANGE OR REMOVE THE CONTENTS OF THIS PROJECT WITHOUT PREVIOUS NOTICE.
	THE AUTHOR IS NOT RESPONSIBLE FOR DAMAGE OF ANY KIND OR LIABILITY CAUSED BY USING THE CONTENTS OF THIS PROJECT.

	This License shall be included in all functional textual files.
*/


// ----- INCLUDE FILES
#include			"sBuildInfo.h"

// Build info (will be placed at 0x10C, right after vector table)
__SBI("SBI_FW", "v1.13.08rc5", "BluePill", "E");


// ----- APP ENTRY
int main(void)
{
	// Just to make sure compiler does not remove build info
	SBI_APP_USED;

	// Print example:
	// printf("FW version %s\nBuild date %s\n", SBI_APP_VER, SBI_APP_DATE);

	while (1);
}


// END WITH NEW LINE
