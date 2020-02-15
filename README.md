# WIP: TTGO T-Wristband Example

First steps with TTGO T-Wristband. [Product page](https://es.aliexpress.com/item/4000527495064.html).

Developed with PlatformIO

Includes a paged interface framework.

**Disclaimer:** Still work in progress. Currently I'm facing issues regarding battery duration (You can follow the issue in the [manufacturer's repo](https://github.com/Xinyuan-LilyGO/LilyGO-T-Wristband/issues/2)). PRs are welcome.

## User interface

- Single touch: change page
- Long touch: page action
- Led: Charging status

## Currently available pages

- CET/CEST time, action: connect to wifi and update via NTP
- UTC time, action: connect to wifi and update via NTP
- Battery status. Action: OTA mode.
- Compass, action: calibrate magnetometer.
- Temperature: from the MPU9250 temp register.
- OTA: long touch to enter OTA mode, to load firmware from PlatformIO.

## Build and Flashing

First of all, install PlatformIO with your favourite IDE (i.e. VSCode). Follow [this](https://platformio.org/platformio-ide) instructions.

Clone the repo

```sh
git clone https://github.com/TioRuben/TTGO-T-Wristband.git
```

Open cloned folder with your PlatformIO IDE (in the example, with VSCode)

```shell
cd TTGO-T-Wristband
code .
```

In the first flash, edit `platformio.ini` and comment all upload config (upload_protocol, upload_port, upload_flags):

```conf
[...]
  -DLOAD_GFXFF=1
  -DSMOOTH_FONT=1
  -DSPI_FREQUENCY=27000000
;upload_protocol = espota
;upload_port = 192.168.0.46
;upload_flags =
;    --auth=wristbandpass
monitor_speed = 115200
lib_ldf_mode = deep+
lib_deps =
[...]
```

Connect wristband via USB with the supplied daughter board. In Windows 10, drivers are installed automatically. I guess with other OS will be automatically installed too.

After plugging wristband, press the arrow button at the bottom of VSCode

![Upload Button](https://docs.platformio.org/en/latest/_images/platformio-ide-vscode-build-project.png)

PlatformIO will build and upload the binaries to the TTGO T-Wristband.

## OTA Upload

After first flashing, you can use OTA upload. First of all, go to battery or OTA page in the wristband. Then maintain the wristband button pressed. If your Wifi is still not configured, you will see an screen asking you to connect to the wristband AP. Connect to It and follow the instructions in the captive portal to configure wifi (more info: [WifiManager](https://github.com/tzapu/WiFiManager#development)).

Once configured, you will see the "waiting for ota" message in the screen. Find your wristband IP Address, uncomment the `platformio.ini` lines you commented before and enter the IP address in the `upload_port` config.

```conf
[...]
  -DLOAD_GFXFF=1
  -DSMOOTH_FONT=1
  -DSPI_FREQUENCY=27000000
upload_protocol = espota
upload_port = [YOUR_IP_ADDRESS]
upload_flags =
    --auth=wristbandpass
monitor_speed = 115200
lib_ldf_mode = deep+
lib_deps =
[...]
```

It's supposed to work with hostnames, but sometimes fails.

Press again the upload button in PlatformIO

![Upload Button](https://docs.platformio.org/en/latest/_images/platformio-ide-vscode-build-project.png)

The project will compile and upload to the wristband.

## Follow repo to get more updates

## ToDo list

- [x] UTC Time
- [x] Port ADC calibration from Lilygo example
- [x] Finish compass
- [x] Add magnetometer calibration action
- [x] Add MPU temperature measurement page
- [x] Wake on motion interrupt. Wakes the wristband if big movements (ie when moving the arm to watch the time).
- [ ] Refactor page framework to work with RTOS tasks
- [ ] Charging animation
- [ ] Prevent deep sleep when charging to feedback the charging status (via LED)
- [ ] Bluetooth
- [ ] "Next appointment" page
- [ ] Change lcd brightness depending on day/night time
