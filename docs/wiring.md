# Wiring

- D11 → Servo 1 signal
- D10 → Servo 2 signal
- D13 → Start/Stop button (to Vcc through button; add series resistor/debounce if needed)
- D12 → Time-Select button
- D8  → Status LED
- D7,D6,D5,D4,D3 → Delay indicator LEDs
- All grounds common. Power servos from a suitable 5V rail (don’t pull heavy servo current from the board’s 5V pin).
