
# shyiko's [corne](https://github.com/foostan/crkbd) setup

This document describes how to flash Elite C v3.0+/Micro Pro for corne.  

> See [this](https://github.com/shyiko/dotfiles/blob/master/CORNE.md) for the list of parts.

## Quickstart

```bash
git clone --recurse-submodules https://github.com/qmk/qmk_firmware.git &&
  cd qmk_firmware
util/qmk_install.sh
```

## Flashing firmware (on Linux)

```bash
# if you have Elite C v3.0+
# connect one side of the keyboard (TRRS cable may stay plugged in / no need to disconnect the other side)
# short GND & RST on a microcontroller OR press reset button
make crkbd:shyiko:dfu-split-left
# repeat the same process for the other side
make crkbd:shyiko:dfu-split-right

# if you have Pro Micro
# connect one side of the keyboard (TRRS cable may stay plugged in / no need to disconnect the other side)
# short GND & RST on a microcontroller OR press reset button
make crkbd:shyiko:avrdude-split-left
# repeat the same process for the other side
make crkbd:shyiko:avrdude-split-right
```

### If the above doesn't work (e.g. stuck on "Detecting USB port, reset your controller now...")

#### Setup udev rules

> You may want to `sudo apt remove modemmanager`. See [how to prevent modem manager from grabbing device](https://askubuntu.com/questions/399263/udev-rules-seem-ignored-can-not-prevent-modem-manager-from-grabbing-device) for alternatives.

```bash
# start watching kernel ring buffer
dmesg -w
# connect left side of the keyboard (keep TRRS cable disconnected)
# short GND & RST on a microcontroller OR press reset button (twice!)
# you should see something like

# [56297.493613] usb 1-2: new full-speed USB device number 52 using xhci_hcd
# [56297.643065] usb 1-2: New USB device found, idVendor=2341, idProduct=0037, bcdDevice= 0.01 # bootloader mode
# [56297.643067] usb 1-2: New USB device strings: Mfr=2, Product=1, SerialNumber=0
# [56297.643068] usb 1-2: Product: Arduino Micro
# [56297.643069] usb 1-2: Manufacturer: Arduino LLC
#
# [56297.644364] cdc_acm 1-2:1.0: ttyACM0: USB ACM device
# [56305.289599] usb 1-2: USB disconnect, device number 52
#
# [56305.597431] usb 1-2: new full-speed USB device number 53 using xhci_hcd
# [56305.748706] usb 1-2: New USB device found, idVendor=2341, idProduct=8037, bcdDevice= 1.00
# [56305.748708] usb 1-2: New USB device strings: Mfr=1, Product=2, SerialNumber=0
# [56305.748709] usb 1-2: Product: Arduino Micro
# [56305.748710] usb 1-2: Manufacturer: Arduino LLC

# from the output above we can see that Pro Micro identifies itself as 2341:8037
# during normal operation and as 2341:0037 in a bootloader mode (we'll need to
# enter the latter to flash)

# take idVendor/idProduct from the above and put them in /etc/udev/rules.d/..., e.g.
echo $'
# Pro Micro
SUBSYSTEMS=="usb", ATTRS{idVendor}=="2341", ATTRS{idProduct}=="0037", MODE:="0666"
# Elite C v3.0
SUBSYSTEMS=="usb", ATTRS{idVendor}=="03eb", ATTRS{idProduct}=="2ff4", MODE:="0666"
' > /etc/udev/rules.d/50-custom.rules
# reload udev rules
sudo udevadm control --reload-rules

# diconnect keyboard
```

#### Flash

> For Pro Micro's, you'll need to install avrdude (`sudo apt install avrdude`).

```bash
# start watching USB devices
watch -n.1 lsusb

# connect left side of the keyboard (keep TRRS cable disconnected)
# short GND & RST on a microcontroller OR press reset button (twice!)
# microcontroller should enter bootloader mode (but only for a short while so be quick!)

# as soon as you see board in a bootloader mode (e.g. 2341:0037 in case of Pro Micro)
# execute one of the commands below

# if you have Pro Micro*
# left side
make crkbd:shyiko:avrdude-split-left
# right side
make crkbd:shyiko:avrdude-split-right

# if you have Elite C v3.0
# left side
make crkbd:shyiko:dfu-split-left
# right side
make crkbd:shyiko:dfu-split-right
```

> \* alternatively, `make crkbd:shyiko` and then `avrdude -p atmega32u4 -P /dev/ttyACM0 -c avr109 -U flash:w:crkbd_rev1_shyiko.hex`.

## OS-specific setup

### Linux

```bash
# change key repeat delay/rate after plugging in the keyboard
# (default key repeat delay is 660ms, rate - 40Hz (1s/40Hz = every 25ms))
xset r rate 330 40

# if you want values to persist use
printf '#!/bin/sh\nexec /usr/bin/X -ardelay 330 -arinterval 25 -nolisten tcp "$@"\n' > ~/.xserverrc
# (note that arinterval is in ms not Hz)
```

## References

- [foostan's build guide (in Japanese)](https://github.com/foostan/crkbd/blob/master/corne-cherry/doc/buildguide_jp.md).
- [QMK Hand-Wiring Guide](https://github.com/qmk/qmk_firmware/blob/master/docs/hand_wire.md) (make sure to read "How a Keyboard Matrix Works (and [why we need diodes](https://deskthority.net/wiki/Rollover,_blocking_and_ghosting))")
