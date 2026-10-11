# PIC16F876A UART Password Authentication System

## Project Overview
This project implements a password authentication system using the PIC16F876A microcontroller. The user enters a password through a UART Virtual Terminal. The microcontroller checks the password and displays the authentication result on a 16×2 LCD.

Password characters are masked with asterisks (`*`) in the terminal.

## Components Used
- PIC16F876A microcontroller
- 16×2 LCD (LM016L)
- Virtual Terminal
- 4 MHz crystal
- Two 22 pF capacitors
- 10 kΩ resistor for MCLR
- 10 kΩ potentiometer for LCD contrast
- 220 Ω resistor for LCD backlight, if required

## Software Used
- MPLAB X IDE
- XC8 Compiler
- Proteus Design Suite

## Pin Connections

### LCD to PIC16F876A
| LCD Pin | PIC Connection |
|---|---|
| RS (pin 4) | RB0 (pin 21) |
| E (pin 6) | RB1 (pin 22) |
| D4 (pin 11) | RB2 (pin 23) |
| D5 (pin 12) | RB3 (pin 24) |
| D6 (pin 13) | RB4 (pin 25) |
| D7 (pin 14) | RB5 (pin 26) |
| RW (pin 5) | GND |

### UART Connections
- PIC RC6/TX (pin 17) → Virtual Terminal RXD
- Virtual Terminal TXD → PIC RC7/RX (pin 18)

## Working Principle
1. The LCD displays the password prompt.
2. The user enters a password through the Virtual Terminal.
3. The PIC receives the characters and sends `*` for each character.
4. The PIC compares the entered password with the predefined password.
5. The LCD displays `ACCESS GRANTED` for a correct password or `ACCESS DENIED` for an incorrect password.

## Test Password
`123`

## Project Status
Simulation-based learning project using Proteus.

## Important Note
The password is hardcoded for demonstration. This project is not intended for securing real-world equipment.

