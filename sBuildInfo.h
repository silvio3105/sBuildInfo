/**
 * @file sBuildInfo.hpp
 * @author silvio3105 (www.github.com/silvio3105)
 * @brief Simple Build Info library header file.
 * 
 * @copyright Copyright (c) 2026, silvio3105
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

#ifndef _SBUILDINFO_H_
#define _SBUILDINFO_H_

// ----- INCLUDE FILES
#include			<stdint.h>


/** \addtogroup sBuildInfo 
 * Simple Build Info library
 * 
 * Only GCC and ARM compilers are supported.
 * Build info is placed inside \c sBuildInfo section if \c SBI_NO_FIX is not defined during build. Define \c SBI_NO_FIX to place build info at random location.
 * Set maximum length of build info by providing \c SBI_NAME_LEN, \c SBI_VER_LEN, \c SBI_HW_LEN and \c SBI_FLAGS_LEN defines during build. Default length for info is 16 chars, 4 for build flags.
 * Build date and time are taken from \c __DATE__ and \c __TIME__ defines.
 * Build size and hash are set to \c 0xFFFFFFFF. To write size and hash use sPostBuild tool.
 * 
 * @{
*/

// ----- DEFINES
#define SBI_VERSION					"v4.0r1" /**< @brief Library version string. */

#ifndef SBI_NAME_LEN
#define SBI_NAME_LEN				16 /**< @brief Maximum length of build name in bytes. */
#endif // SBI_NAME_LEN

#ifndef SBI_VER_LEN
#define SBI_VER_LEN					16 /**< @brief Maximum length of application version in bytes. */
#endif // SBI_VER_LEN

#ifndef SBI_HW_LEN
#define SBI_HW_LEN					16 /**< @brief Maximum length of hardware version in bytes. */
#endif // SBI_HW_LEN

#ifndef SBI_FLAGS_LEN
#define SBI_FLAGS_LEN				4 /**< @brief Maximum length of build flags in bytes. */
#endif // SBI_FLAGS_LEN


// ----- CODE SNIPPETS
#if defined(__GNUC__) || defined(__CC_ARM) || defined(__ARMCC_VERSION)
	#ifndef SBI_NO_FIX
		#define __SECTION(name) \
			__attribute__((used, section(name)))
	#else
		#define __SECTION(name) \
			__attribute__((used))
	#endif // SBI_NO_FIX
#elif 
    #error "sBuildInfo is not supported with selected toolchain."
#endif 

/**
 * @brief Code snippet for creating build info.
 * 
 * If \c SBI_NO_FIX not defined, build info will be placed on fixed location in flash memory with user-defined \c sBuildInfo section in linker script.
 * 
 * @param _name Application name. Max \c SBI_NAME_LEN chars.
 * @param _version Application version. Max \c SBI_VER_LEN chars.
 * @param _hardware Hardware revision. Max \c SBI_HW_LEN chars.
 * @param _flags Build flags. Max \c SBI_FLAGS_LEN bytes.
 */
#define __SBI(_name, _version, _hardware, _flags) \
	volatile const sBuildInfo_s __sBuildInfo __SECTION(".sBuildInfo") = \
	{ \
		0xFFFFFFFF, \
		0xFFFFFFFF \
		_name, \
		_version, \
		_hardware, \
		__DATE__, \
		__TIME__, \
		_flags \
	}

#define SBI_NAME					__sBuildInfo.name /**< @brief Macro for build name. */
#define SBI_VERSION					__sBuildInfo.version /**< @brief Macro for build version. */
#define SBI_HARDWARE				__sBuildInfo.hardware /**< @brief Macro for build hardware version. */
#define SBI_DATE					__sBuildInfo.date /**< @brief Macro for build date. Example date: \c Aug \c  8 \c 2019 (day is padded). */
#define SBI_TIME					__sBuildInfo.time /**< @brief Macro for build time. */
#define SBI_FLAGS					__sBuildInfo.flags /**< @brief Macro for build flags. Example: \c 0b10 flag for debug build. */
#define SBI_SIZE					__sBuildInfo.size /**< @brief Macro for build size in bytes. */
#define SBI_HASH					__sBuildInfo.hash /**< @brief Macro for build hash. */
#define SBI_USED					(void)(SBI_NAME) /**< @brief Code snippet for preventing compiler from removing build info from flash memory. */


// ----- STRUCTS
/**
 * @brief Simple build info struct.
 * 
 */
struct sBuildInfo_s
{
	const uint32_t size; /**< @brief Placeholder for build size. Set to \c 0xFFFFFFFF. */
	const uint32_t hash; /**< @brief Placeholder for build hash. Set to \c 0xFFFFFFFF. */	
	const char name[SBI_NAME_LEN]; /**< @brief C-string for build name. */
	const char version[SBI_VER_LEN]; /**< @brief C-string for build version. */
	const char hardware[SBI_HW_LEN]; /**< @brief C-string for build hardware version. */
	const char date[12]; /**< @brief C-string for build date. */
	const char time[10]; /**< @brief C-string for build time. */
	const uint8_t flags[SBI_FLAGS_LEN]; /**< @brief Bytes for build flags. */
};


// ----- EXTERNS
extern volatile const sBuildInfo_s __sBuildInfo;


/** @} */


#endif // _SBUILDINFO_H_

// END WITH NEW LINE
