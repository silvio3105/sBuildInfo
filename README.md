
# About

Simple Build Info is library which provides easy way to write build info into flash memory. Build info is useful when verifying new application before application update via (custom) bootloader.
If build info have to be at fixed location in flash memory, `sBuildInfo` section in GCC linker script has to be created. It is recommended to place `sBuildInfo` section right after vector table.

It is recommended to define build info in main translation unit. Use [sPostBuild](https://github.com/silvio3105/sPostBuild) tool to write build size and hash.

Library documentation is available at `Documentation/html/index.html`.
Example applications are available at `Examples` folder.


# Linker script example

```
SECTIONS
{
	/* The startup code goes first into FLASH */
	.isr_vector :
	{
		. = ALIGN(4);
		KEEP(*(.isr_vector)) /* Startup code */
		. = ALIGN(4);
	} >FLASH

	/* Simple Build Info */
	.sBuildInfo :
	{
		. = ALIGN(4);
		KEEP(*(.sBuildInfo))
		. = ALIGN(4);
	} >FLASH

	(...)
}
```


# License

Copyright (c) 2026, silvio3105 (www.github.com/silvio3105)

Access and use of this Project and its contents are granted free of charge to any Person.
The Person is allowed to copy, modify and use The Project and its contents only for education and DIY purposes.
Commercial use of the Project, in whole or in part, is prohibited without prior written permission from the Author.
This License may not be modified and no sublicense may be granted.

THE PROJECT AND ITS CONTENTS ARE PROVIDED "AS IS" WITH ALL FAULTS AND WITHOUT EXPRESS OR IMPLIED WARRANTY.
THE AUTHOR KEEPS ALL RIGHTS TO CHANGE OR REMOVE THE CONTENTS OF THIS PROJECT WITHOUT PRIOR NOTICE.
IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY CLAIM, DAMAGES, OR OTHER LIABILITY ARISING FROM THE USE OF THE PROJECT.

A copy of this License must be included with all copies and substantial portions of the Project.

---

Copyright (c) 2026, silvio3105
