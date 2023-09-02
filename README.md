Fork from the [Picopad Games](https://github.com/tvecera/picopad-playground/tree/main/picopad-sdk/games).

---

**⚠️ WARNING ⚠️**

Please DO NOT directly upload the build to Pico / Picopad. The build is specifically designed for the custom
bootloader, which will load it from the SD card into flash memory behind the main bootloader. You must upload the 
contents of the /build directory to an SD card.

Please note, the build does NOT include a BOOT2 section. Directly uploading the build to the Picopad / Pico will
brick your Pico / Picopad.
