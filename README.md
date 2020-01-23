# WIP: TTGO T-Wristband Example

First steps with TTGO T-Wristband. [Product page](https://es.aliexpress.com/item/4000527495064.html).

Developed with PlatformIO

Includes a paged interface framework.

User interface:

- Single touch: change page
- Long touch: page action
- Led: Charging status

Currently available pages:

- CET/CEST time, action: connect to wifi and update via NTP
- UTC time, action: connect to wifi and update via NTP
- Battery status (no action in this page)
- Compass, action: calibrate magnetometer. (Still working on it)
- OTA: long touch to enter OTA mode, to load firmware from PlatformIO

Follow repo to get more updates

### ToDo list

- [x] UTC Time
- [ ] Port ADC calibration from Lilygo example
- [x] Finish compass
- [x] Add magnetometer calibration action
- [x] Add MPU temperature measurement page
- [ ] Refactor page framework to work with RTOS tasks
- [ ] Charging animation
- [ ] Prevent deep sleep when charging to feedback the charging status (via LED)
- [ ] Bluetooth
