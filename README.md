# TorqueRig

Arduino firmware for a DIY USB racing wheel with force feedback, running on an **Arduino Pro Micro**
(ATmega32U4). It shows up in Windows as a DirectInput game controller with FFB, a steering axis,
three pedals and a button matrix.

Derived from [AFFBWheel](https://github.com/vsulako/AFFBWheel) by Sulako (MIT). See `NOTICE.md`.

## Hardware

| Part | Used for |
|---|---|
| Arduino Pro Micro | Controller and USB interface |
| 2x RF300A DC motors | Force feedback |
| TB6612FNG | Motor driver |
| 600 PPR rotary encoder (ProRange) | Steering position |
| 3x 10 kOhm potentiometers | Accelerator, brake and clutch pedals |
| Tactile buttons in a matrix | Gear up/down, left/right indicators, 5 spare buttons |

The button matrix keeps the number of used pins low. Pin numbers and options are set in `config.h`.

Encoder setting: `ENCODER_PPR` in `config.h` is the number of counts per revolution after 4x quadrature
decoding, i.e. 4 x the encoder's PPR. A 600 PPR encoder therefore uses `2400` (the current value).

## Build and upload

1. Install Arduino IDE 1.8.19 (later versions may have errors with this code).
2. Install the libraries listed in `NOTICE.md`.
3. Open `TorqueRig.ino` (the folder name must stay `TorqueRig`, matching the .ino file).
4. Check `config.h` for your encoder resolution, motor driver pins, pedal pins and button matrix.
5. Select **Tools > Board > Arduino Leonardo** (or Pro Micro) and the correct port, then upload.

## Configuration tool

Settings (wheel range, FFB gains, axis limits, button mapping) can be changed with serial commands or
with the original [AFFBWheel GUI](https://github.com/vsulako/AFFBWHeelGUI). The firmware still
reports the handshake id `AFFBW` so that the GUI recognizes the device.
