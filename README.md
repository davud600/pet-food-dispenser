# Arduino Pet Food Dispenser

Code for Arduino controlling a pet food dispenser timer and start/stop.

- **Board:** Arduino Uno (changeable in `platformio.ini`)
- **Servos:** `motor1` on D11, `motor2` on D10
- **Buttons:** Start/Stop on D13, Time-Select on D12
- **LEDs:** D7, D6, D5, D4, D3 (indicates selected delay)
- **Status:** D8 (HIGH while running)

## Delays
Cycle with the time-select button when **stopped**:

- 1500 ms
- 3000 ms
- 4000 ms
- 8000 ms

## Build & Upload (PlatformIO)

```bash
# install once
pip install platformio

# build
pio run

# upload (USB connected)
pio run -t upload

# monitor serial
pio device monitor -b 9600
```
