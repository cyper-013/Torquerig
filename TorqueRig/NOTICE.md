# Notice and attribution

TorqueRig is a derivative of **AFFBWheel** by Sulako (MIT License):
https://github.com/vsulako/AFFBWheel

AFFBWheel in turn uses USB HID and force feedback code from the **VNWheel** project by hoantv, and
earlier work by Jaka Simonic and Tero Loimuneva. The original copyright and permission notices are
kept in the headers of the source files (`TorqueRig.ino`, `FfbEngine.h`, `FfbReportHandler.h`,
`HIDReportType.h`, `WHID.h`, `WHID.cpp`) and must stay there. The MIT License requires this
whenever the code is copied, modified or redistributed.

Arduino libraries used (installed separately):
- digitalWriteFast: https://github.com/NicksonYap/digitalWriteFast
- avdweb_AnalogReadFast: https://github.com/avandalen/avdweb_AnalogReadFast
- Encoder (Paul Stoffregen): https://github.com/PaulStoffregen/Encoder

Compatible configuration GUI (original project): https://github.com/vsulako/AFFBWHeelGUI

Modifications in this version: project renamed, hardware configuration in `config.h` set for
the build described in README.md.

Modifications copyright (c) YEAR YOUR NAME
