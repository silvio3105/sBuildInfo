/**
 * @file sBuildInfo.h
 * @author silvio3105 (www.github.com/silvio3105)
 * @brief Simple Build Info library header file.
 * 
 * @copyright Copyright (c) 2023, silvio3105
 * 
 */

/*
License

Copyright (c) 2023, silvio3105 (www.github.com/silvio3105)

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


/** \addtogroup sBuildInfo 
 * Simple Build Info library
 * 
 * Library can be used only with GCC toolchain.
 * 
 * If \c SBI_NO_FIX is not defined during build, application build info is placed inside \c sBuildInfo section. User must ensure it exists in linker script.
 * 
 * Define \c SBI_NO_FIX in build and build info will not be placed at fixed location in flash memory.
 * 
 * Set maximum length of build info by providing \c SBI_APP_NAME_LEN, \c SBI_APP_VER_LEN and \c SBI_APP_HW_LEN defines during build. Default length for info is 16 chars and 8 chars for application tag and variant.
 * 
 * @{
*/

// ----- DEFINES
#define SBI_VERSION					"v1.0r2" /**< @brief Library version string. */

#ifndef SBI_APP_NAME_LEN
#define SBI_APP_NAME_LEN			16 /**< @brief Maximum length of application name. */
#endif // SBI_APP_NAME_LEN

#ifndef SBI_APP_VER_LEN
#define SBI_APP_VER_LEN				16 /**< @brief Maximum length of application version. */
#endif // SBI_APP_VER_LEN

#ifndef SBI_APP_HW_LEN
#define SBI_APP_HW_LEN				16 /**< @brief Maximum length of hardware version. */
#endif // SBI_APP_HW_LEN



// ----- CODE SNIPPETS
#ifndef SBI_NO_FIX
/**
 * @brief Code snippet for creating application build info in flash memory.
 * 
 * Application build info will be placed on fixed location in flash memory with user-defined \c sBuildInfo section within linker script.
 * 
 * @param _name Application name. Max \c SBI_APP_NAME_LEN chars.
 * @param _ver Application version. Max \c SBI_APP_VER_LEN chars.
 * @param _rev Hardware revision. Max \c SBI_APP_HW_LEN chars.
 */
#define __SBI(_name, _ver, _rev) \
	static volatile const build_info_t __buildInfo __attribute__((section(".sBuildInfo"))) = { \
		_name, \
		_ver, \
		_rev, \
		__DATE__ \
	}

/**
 * @brief Code snippet for creating extended application build info in flash memory.
 * 
 * Application build info will be placed on fixed location in flash memory with user-defined \c sBuildInfo section within linker script.
 * With this snippet, application name is replaced with application tag and variant, both \c SBI_APP_NAME_LEN/2 characters long.
 * 
 * @param _tag Application tag. Max \c SBI_APP_NAME_LEN/2 chars.
 * @param _variant Application variant. Max \c SBI_APP_NAME_LEN/2 chars.
 * @param _ver Application version. Max \c SBI_APP_VER_LEN chars.
 * @param _rev Hardware revision. Max \c SBI_APP_HW_LEN chars.
 * 
 * @warning GCC 11.3+ is required for this snippet.
 */
#define __SBI_EXT(_tag, _variant, _ver, _rev) \
	static volatile const build_info_t __buildInfo __attribute__((section(".sBuildInfo"))) = \
	{ \
		{ \
			.tag = _tag, \
			_variant \
		}, \
		_ver, \
		_rev, \
		__DATE__ \
	}
#else // SBI_NO_FIX
/**
 * @brief Code snippet for creating application build info in flash memory.
 * 
 * @param _name Application name. Max \c SBI_APP_NAME_LEN chars.
 * @param _ver Application version. Max \c SBI_APP_VER_LEN chars.
 * @param _rev Hardware revision. Max \c SBI_APP_HW_LEN chars.
 */
#define __SBI(_name, _ver, _rev) \
	static volatile const build_info_t __buildInfo = { \
		_name, \
		_ver, \
		_rev, \
		__DATE__ \
	}

/**
 * @brief Code snippet for creating extended application build info in flash memory.
 * 
 * With this snippet, application name is replaced with application tag and variant, both \c SBI_APP_NAME_LEN/2 characters long.
 * 
 * @param _tag Application tag. Max \c SBI_APP_NAME_LEN/2 chars.
 * @param _variant Application variant. Max \c SBI_APP_NAME_LEN/2 chars.
 * @param _ver Application version. Max \c SBI_APP_VER_LEN chars.
 * @param _rev Hardware revision. Max \c SBI_APP_HW_LEN chars.
 * 
 * @warning GCC 11.3+ is required for this snippet.
 */
#define __SBI_EXT(_tag, _variant, _ver, _rev) \
	static volatile const build_info_t __buildInfo = \
	{ \
		{ \
			.tag = _tag, \
			_variant \
		}, \
		_ver, \
		_rev, \
		__DATE__ \
	}
#endif // SBI_NO_FIX


#define __SBI_NAME()			__buildInfo.app.name /**< @brief Getter for application name. */
#define __SBI_TAG()				__buildInfo.app.tag /**< @brief Getter for application tag. */
#define __SBI_VARIANT()			__buildInfo.app.variant /**< @brief Getter for application variant. */
#define __SBI_VER()				__buildInfo.appVer /**< @brief Getter for application version. */
#define __SBI_HW()				__buildInfo.hwRev /**< @brief Getter for application hardware revision. */
#define __SBI_DATE()			__buildInfo.buildDate /**< @brief Getter for application build date. Example date: \c Aug \c  8 \c 2019 (day is padded). */
#define __SBI_USED				(void)(__SBI_NAME()) /**< @brief Code snippet for preventing compiler from removing build info from flash memory. */


// ----- STRUCTS
/**
 * @brief Build info struct.
 * 
 */
struct build_info_t
{
	/**
	 * @brief Union of application name, tag and variant.
	 * 
	 */
	union
	{
		const char name[SBI_APP_NAME_LEN]; /**< @brief C-string for application name. */
		struct
		{
			const char tag[SBI_APP_NAME_LEN / 2]; /**< @brief C-string for application tag. */
			const char variant[SBI_APP_NAME_LEN / 2]; /**< @brief C-string for application variant name. */
		};
	} app;
	const char appVer[SBI_APP_VER_LEN]; /**< @brief C-string for application version. */
	const char hwRev[SBI_APP_HW_LEN]; /**< @brief C-string for hardware revision. */
	const char buildDate[12]; /**< @brief C-string for build date. */
};


// ----- EXTERNS
extern const build_info_t __buildInfo;


/** @} */


#endif // _SBUILDINFO_H_

// END WITH NEW LINE
