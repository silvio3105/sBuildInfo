
# Simple Build Info library

Simple Build Info is library that provides easy way to write build info into flash memory. Build info is useful when verifying new application before application update via (custom) bootloader.
User must create `sBuildInfo` section in GCC linker script. Recommendation is to place `sBuildInfo` section right after vector table.

It is recommended to define build info in `main.c` and place `SBI_USED` somewhere in `main()` so compiler does not remove build info from flash.

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

  .sBuildInfo :
  {
    . = ALIGN(4);
    KEEP(*(.sBuildInfo)) /* Build info */
    . = ALIGN(4);
  } >FLASH

  (...)
}
```


# License

Copyright (c) 2023, silvio3105 (www.github.com/silvio3105)

Access and use of this Project and its contents are granted free of charge to any Person.
The Person is allowed to copy, modify and use The Project and its contents only for non-commercial use.
Commercial use of this Project and its contents is prohibited.
Modifying this License and/or sublicensing is prohibited.

THE PROJECT AND ITS CONTENT ARE PROVIDED "AS IS" WITH ALL FAULTS AND WITHOUT EXPRESSED OR IMPLIED WARRANTY.
THE AUTHOR KEEPS ALL RIGHTS TO CHANGE OR REMOVE THE CONTENTS OF THIS PROJECT WITHOUT PREVIOUS NOTICE.
THE AUTHOR IS NOT RESPONSIBLE FOR DAMAGE OF ANY KIND OR LIABILITY CAUSED BY USING THE CONTENTS OF THIS PROJECT.

This License shall be included in all functional textual files.

---

Copyright (c) 2023, silvio3105