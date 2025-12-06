/**
 * @file sBuildInfo.h
 * @author silvio3105 (www.github.com/silvio3105)
 * @brief Simple Build Info library header file.
 * 
 * @copyright Copyright (c) 2025, silvio3105
 * 
 */

/*
License

Copyright (c) 2025, silvio3105 (www.github.com/silvio3105)

Access and use of this Project and its contents are granted free of charge to any Person.
The Person is allowed to copy, modify and use The Project and its contents only for non-commercial use.
Commercial use of this Project and its contents is prohibited.
Modifying this License and/or sublicensing is prohibited.

THE PROJECT AND ITS CONTENT ARE PROVIDED "AS IS" WITH ALL FAULTS AND WITHOUT EXPRESSED OR IMPLIED WARRANTY.
THE AUTHOR KEEPS ALL RIGHTS TO CHANGE OR REMOVE THE CONTENTS OF THIS PROJECT WITHOUT PREVIOUS NOTICE.
THE AUTHOR IS NOT RESPONSIBLE FOR DAMAGE OF ANY KIND OR LIABILITY CAUSED BY USING THE CONTENTS OF THIS PROJECT.

This License shall be included in all methodal textual files.
*/


#ifndef _SBUILDINFO_H_
#define _SBUILDINFO_H_

// ----- INCLUDE FILES
#include			<stdint.h>


/** \addtogroup sBuildInfo 
 * Simple Build Info library
 * 
 * Library can be used only with GCC toolchain.
 * Build info is placed inside \c sBuildInfo section if \c SBI_NO_FIX is not defined during compile/build. Define \c SBI_NO_FIX and build info will not be placed at fixed location in flash memory.
 * Set maximum length of build info by providing \c SBI_NAME_LEN, \c SBI_VER_LEN, \c SBI_HW_LEN and \c SBI_FLAGS_LEN defines during build. Default length for info is 16 chars(10 for build flags).
 * Build flags example: \c DFT
 * - \c D for build with debug prints.
 * - \c F for build with enabled FPU.
 * - \c T for build with trace log system.
 * 
 * @{
*/

// ----- DEFINES
#define SBI_VERSION					"v3.0r1" /**< @brief Library version string. */

#ifndef SBI_NAME_LEN
#define SBI_NAME_LEN				16 /**< @brief Maximum length in bytes of application name. */
#endif // SBI_NAME_LEN

#ifndef SBI_VER_LEN
#define SBI_VER_LEN					16 /**< @brief Maximum length in bytes of application version. */
#endif // SBI_VER_LEN

#ifndef SBI_HW_LEN
#define SBI_HW_LEN					16 /**< @brief Maximum length in bytes of hardware version. */
#endif // SBI_HW_LEN

#ifndef SBI_FLAGS_LEN
#define SBI_FLAGS_LEN				10 /**< @brief Maximum length in bytes of build flags. */
#endif // SBI_FLAGS_LEN



// ----- CODE SNIPPETS
#ifndef SBI_NO_FIX

/**
 * @brief Code snippet for creating build info in flash memory.
 * 
 * Build info will be placed on fixed location in flash memory with user-defined \c sBuildInfo section within linker script.
 * 
 * @param _name Application name. Max \c SBI_NAME_LEN chars.
 * @param _version Application version. Max \c SBI_VER_LEN chars.
 * @param _hardware Hardware revision. Max \c SBI_HW_LEN chars.
 * @param _flags Build flags. Max \c SBI_FLAGS_LEN chars.
 */
#define __SBI(_name, _version, _hardware, _flags) \
	volatile const sBuildInfo_s __sBuildInfo __attribute__((section(".sBuildInfo"))) = \
	{ \
		_name, \
		_version, \
		_hardware, \
		__DATE__, \
		__TIME__, \
		_flags, \
		0xFFFFFFFF, \
		0xFFFFFFFF \
	}

#else // SBI_NO_FIX

	/**
	 * @brief Code snippet for creating build info in flash memory.
	 * 
	 * @param _name Application name. Max \c SBI_NAME_LEN chars.
	 * @param _version Application version. Max \c SBI_VER_LEN chars.
	 * @param _hardware Hardware revision. Max \c SBI_HW_LEN chars.
	 * @param _flags Build flags. Max \c SBI_FLAGS_LEN chars.
	 */
	volatile const sBuildInfo_s __sBuildInfo = \
	{ \
		_name, \
		_version, \
		_hardware, \
		__DATE__, \
		__TIME__, \
		_flags, \
		0xFFFFFFFF, \
		0xFFFFFFFF \
	}

#endif // SBI_NO_FIX

#define SBI_NAME					__sBuildInfo.name /**< @brief Macro for build name. */
#define SBI_VERSION					__sBuildInfo.version /**< @brief Macro for build version. */
#define SBI_HARDWARE				__sBuildInfo.hardware /**< @brief Macro for build hardware version. */
#define SBI_DATE					__sBuildInfo.date /**< @brief Macro for build date. Example date: \c Aug \c  8 \c 2019 (day is padded). */
#define SBI_TIME					__sBuildInfo.time /**< @brief Macro for build time. */
#define SBI_FLAGS					__sBuildInfo.flags /**< @brief Macro for build flags. Example: \c D flag for debug build. */
#define SBI_SIZE					__sBuildInfo.size /**< @brief Macro for build size in bytes. */
#define SBI_CHECKSUM				__sBuildInfo.checksum /**< @brief Macro for build checksum. */
#define SBI_USED					(void)(SBI_NAME) /**< @brief Code snippet for preventing compiler from removing build info from flash memory. */


// ----- STRUCTS
/**
 * @brief Simple build info struct.
 * 
 */
struct sBuildInfo_s
{
	const char name[SBI_NAME_LEN]; /**< @brief C-string for build name. */
	const char version[SBI_VER_LEN]; /**< @brief C-string for build version. */
	const char hardware[SBI_HW_LEN]; /**< @brief C-string for build hardware version. */
	const char date[12]; /**< @brief C-string for build date. */
	const char time[10]; /**< @brief C-string for build time. */
	const char flags[SBI_FLAGS_LEN]; /**< @brief C-string for build flags. */
	const uint32_t size; /**< @brief Placeholder for build size in bytes. Set to \c 0xFFFFFFFF. */
	const uint32_t checksum; /**< @brief Placeholder for build checksum. Set to \c 0xFFFFFFFF. */
};


// ----- EXTERNS
extern volatile const sBuildInfo_s __sBuildInfo;


/** @} */


#endif // _SBUILDINFO_H_

// END WITH NEW LINE
