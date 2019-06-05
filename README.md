[![Thingiverse](https://img.shields.io/badge/Thingiverse-simplyRetro%20Z5-blue.svg)](https://www.thingiverse.com/thing:3671784)
[![Thingiverse](https://img.shields.io/badge/Github-simplyRetro%20Z5-brightgreen.svg)](https://github.com/geaz/simplyRetro-Z5)

# simplyRetro Z5

This repository contains everything to rebuild the *simplyRetro - Z5*.
The *Z5* is my first attempt to build a custom emulation handheld from scratch.

I maintained a really small [build log](https://www.3dgeeks.club/d/32-retro-boy-a-raspberry-pi-zero-handheld) in the 3DGeeks forum.

![simplyRetro Z5](https://raw.githubusercontent.com/geaz/simplyRetro-Z5/master/images/cover.jpg)

## Warning
This is my first self desinged retro handheld. So please be aware that it could contain some flaws. Furthermore you should be able to handle a soldering iron and you have to understand basic circuits, if you want to rebuild the Z5.

## Features
- Custom 3D printed shell
- Custom linux distribution for fast boot ([from button press to emulationstation in 10 seconds](https://imgur.com/a/TFRGUFs))
- Single press power on and long press power off
- Battery Monitor icon and safe shutdown
- Stereo Speakers, Audio Jack and Volume Control
- 12 Buttons
- 5 inch display
- Raspberry Pi Zero powered

The Pi Zero and the 5 inch display are the reason for the naming *Z5*.

## 3D Model
The model was designed in Fusion360. If you want to change the design, you can find the whole model [here](https://a360.co/2GZACGc). The STLs are in the Thingiverse downloads and the Github repository. Furthermore there are exported STEP and Fusion360 Archive Files ready to download.

## BOM
- 3D Printed Shell (STL folder for models)
- [Elecrow 5 inch Display](https://www.elecrow.com/5-inch-hdmi-800-x-480-capacitive-touch-lcd-display-for-raspberry-pi-pc-sony-ps4.html) (If you want to use another display, make sure to adapt the shell) 
- [12x Adafruit Softbuttons](https://www.adafruit.com/product/3101)
- 1x 5mm Tactile Button for the Power Button
- [1x Powerboost 1000c](https://www.adafruit.com/product/2465)
- [2x Speaker](https://www.reichelt.de/kleinlautsprecher-k-34-wp-1w-8ohm-vis-2981-p204642.html?&trstct=pos_0) (or similar, just make sure they are 1W, 8Ohm and have a diameter of 3.4 cm)
- Resistors (6,8K, 10K, 100K)
- [FPV HDMI Adapter](https://de.aliexpress.com/item/FPV-Micro-HDMI-Mini-HDMI-90-grad-Adapter-5-cm-100-cm-FPC-Band-Flache-Hdmi/32833580742.html?spm=a2g0x.search0104.3.1.562f67acdeKi5D&transAbTest=ae803_3&ws_ab_test=searchweb0_0%2Csearchweb201602_3_10065_10068_10547_319_317_10548_10696_10084_453_10083_454_10618_10304_10307_10820_10821_537_10302_536_10843_10059_10884_10887_321_322_10103%2Csearchweb201603_53%2CppcSwitch_0&algo_pvid=6dcfe960-6b93-4bfb-8be8-ffbdc195707f&algo_expid=6dcfe960-6b93-4bfb-8be8-ffbdc195707f-0) (1xA1, 1xC1 and 1xCable)
- 1x MCP3008 ADC
- 1x Volume potentiometer (I took a GameBoy Color replacement part)
- [1x Jack Plug PJ-307](https://de.aliexpress.com/item/Hot-10-Pcs-5-Pin-3-5mm-Weibliche-Audio-Stereo-Jack-Buchse-PJ-307-PJ307-3F07/32955627960.html?spm=a2g0x.search0104.3.47.2f06a574KeRuaT&transAbTest=ae803_3&ws_ab_test=searchweb0_0%2Csearchweb201602_3_10065_10068_10547_319_317_10548_10696_10084_453_10083_454_10618_10304_10307_10820_10821_537_10302_536_10843_10059_10884_10887_321_322_10103%2Csearchweb201603_53%2CppcSwitch_0&algo_pvid=bd63449e-32af-4e5b-b0f5-bb676c2d5100&algo_expid=bd63449e-32af-4e5b-b0f5-bb676c2d5100-6)
- 1x PAM8403 (Audio AMP)
- 1x 2500 mAh LiPo ([like this one](https://www.ebay.de/itm/LiPo-Akku-Lithium-Ion-Polymer-Batterie-3-7V-2500mAh-JST-PH-Connector-ZB07008/283213408497?ssPageName=STRK%3AMEBIDX%3AIT&_trksid=p2057872.m2749.l2649))
- Veroboard / Stripboard (if you want to use the same circuits as me for the battery monitoring and safe shutdown)
- Some M3x8mm screws (Mounts and Shell), M2.5x4mm screws (Electronics) and one M2.5x8mm screw (Top screw on the bottom shell, has to be smaller to get it fit)

## Build

I hope you got all you parts. Now it is time to assemble the Z5. Again, please be aware, that you should have basic soldering skills and you should be able to understand basic circuits.

### Buttons
This part is easy. Take all your printed button mounts and insert the *Adafruit SoftButtons* into them. It should be a tight fit. Use a pliers, if necessary and bend on of the four button pins to prevent it to fell out from the mount. Insert the printed DPad and buttons into the upper shell and screw the populated button mounts on top. **On the DPad please leave the upper right screw and on the button mount the upper left screw. These holes will be used to fasten the bottom half of the shell.** The *Shoulder Buttons* and *Shoulder Button Mounts* will be inserted into the shell before it gets closed. 

![simplyRetro Z5 - Buttons](https://raw.githubusercontent.com/geaz/simplyRetro-Z5/master/images/1.jpg)

### Display
**The display will be assembled upside down**. Otherwise we will get space problems with the HDMI connectors. 

To fit the display into the shell, you have to cut off half of the bottom display mounts. 
Please use the following two pictures as a reference.  
**Make sure you understand how to place the display, in the correct orientation, into the shell BEFORE you cut the mounts!**

![simplyRetro Z5 - Display cutted](https://raw.githubusercontent.com/geaz/simplyRetro-Z5/master/images/2.jpg)

![simplyRetro Z5 - Display assembled](https://raw.githubusercontent.com/geaz/simplyRetro-Z5/master/images/3.jpg)

If your display is fitting into the top shell, you can remove it to glue the *Display Frame* to the upper shell. I used super glue. Give it enough time to dry before you proceed.

### Electronic Mount
Now take the *Electronic Mount* and use for example a bit felt at the edge without mount holes (see the following picture). The felt just acts as a spacer between the display PCB and the *Electronic Mount*.

![simplyRetro Z5 - Electronic Mount Felt](https://raw.githubusercontent.com/geaz/simplyRetro-Z5/master/images/5.jpg)

Now take the printed spacers and two M3x8mm screws and attach the mount to the display.

![simplyRetro Z5 - Electronic Mount Spacers](https://raw.githubusercontent.com/geaz/simplyRetro-Z5/master/images/6.jpg)

![simplyRetro Z5 - Electronic Mount assembled](https://raw.githubusercontent.com/geaz/simplyRetro-Z5/master/images/7.jpg)

### Power
....

### Audio
....

### Battery Monitor
....

### Closing the shell
....

## Custom Distribution
The custom distribution can be downloaded [here](https://github.com/geaz/simplyRetro-Z5/releases).  
It is based on [BuildRoot](https://buildroot.org/) and just contains the packages needed to play on the *Z5*. 

**Please be aware, that the distribution was build for the Z5! It was not tested as a standalone distribution.**

The *Z5* uses Retroarch for all emulations. The following systems are supported at the moment (more can be added):

- Arcade (MAME2013-plus)
- Gameboy DMG / Color (Gambatte)
- NES (quicknes)
- SNES (snes9x2002)
- Meda Drive / Master System / Sega CD (picodrive)

If you want to use the distribution just use Etcher to copy the img file to a SD Card. The *boot* partition contains a *wpa_supplicant.conf* to configure the connection to your WLAN.

### Login
Start the system and login with:

User: root  
Pass: simplyretro

### Resize Root
To use the full size of you SD Card you should execute the following two scripts in order:

/root/reformat.sh (will reboot the system after execution)  
/root/resize.sh

### FTP
If you configured the *wpa_supplicant.conf* on the boot partition, you are able to connect via FTP to copy your roms to the system. 

### Config.txt
Please be aware, that the default config.txt will rotate the screen. This is necessary, if you are you using the same screen as me.

## Credits
Thanks to [NeoHorizon](https://github.com/NeonHorizon/lipopi) and [Craic](https://github.com/craic/pi_power) for the work on the power circuits. I took their work and reworked the circuit a bit and created a custom battery monitor in C.  
Thanks to [BuildRoot](https://buildroot.org/) for the creation of this great system which enabled me to create a custom linux distribution.  
Thanks to [RecalBox](https://www.recalbox.com/) for their work on the packages for BuildRoot. I took the RetroArch and LibRetro packages and reworked them a bit to work on my distribution.  
Thanks to [ehettervik](https://retropie.org.uk/forum/topic/4611/runcommand-system-splashscreens) for the emulator splashscreens.