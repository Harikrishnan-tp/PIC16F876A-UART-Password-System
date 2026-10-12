PIC16F876A UART Password Authentication System

#Project Overview

This project implements a simple password authentication system using the PIC16F876A microcontroller, a 16×2 LCD, and UART serial communication.

The user enters a password through the Proteus Virtual Terminal. The PIC microcontroller receives the password, checks it against a predefined password, and displays the authentication result on the LCD.

If the password is correct (123), the LCD displays ACCESS GRANTED.

If the password is incorrect, the LCD displays ACCESS DENIED.

The system uses UART to receive password characters from the Virtual Terminal. The LCD displays the result, while the program does not transmit the access result back to the terminal.

#Project Objectives

Interface a 16×2 LCD with the PIC16F876A.

Implement UART serial communication.

Receive password input through the Proteus Virtual Terminal.

Validate the entered password using conditional statements.

Display authentication results on the LCD.

#Hardware and Software Requirements

Hardware / Proteus Components

PIC16F876A microcontroller

16×2 character LCD

Crystal oscillator (4 MHz)

Two 22 pF capacitors

10 kΩ potentiometer for LCD contrast

Virtual Terminal

Power supply and ground connections

Software

MPLAB X IDE

XC8 C Compiler

Proteus Design Suite

#Pin Connections

LCD Interface — 4-bit Mode

LCD Pin

PIC16F876A Pin

Function

RS

RB0 (Pin 21)

Command/data selection

R/W

GND

Write mode

E

RB2 (Pin 23)

Enable signal

D4

RB3 (Pin 24)

Data bit 4

D5

RB4 (Pin 25)

Data bit 5

D6

RB5 (Pin 26)

Data bit 6

D7

RB6 (Pin 27)

Data bit 7

VSS

GND

Ground

VDD

+5 V

Power supply

VEE/V0

Potentiometer wiper

Contrast adjustment

UART Interface

PIC16F876A Pin

Virtual Terminal Pin

RC6/TX (Pin 17)

RXD

RC7/RX (Pin 18)

TXD

UART Configuration:

Baud rate: Approximately 9600 bps

Data bits: 8

Parity: None

Stop bits: 1

Communication mode: Asynchronous UART

⚙️ Working Principle

The PIC16F876A initializes the LCD and UART peripherals.

The LCD displays Enter Password.

The Virtual Terminal prompts the user to enter a password.

The PIC receives the characters through UART.

The received password is stored in an array.

When the user presses Enter, the program compares the password with 123.

The LCD displays the authentication result.

The system waits for two seconds and repeats the process.

#Password Validation

The predefined password is:

123

Input

LCD Output

123

ACCESS GRANTED

124

ACCESS DENIED

111

ACCESS DENIED

12

ACCESS DENIED

#Important Embedded C Concepts Used

GPIO configuration using TRIS and PORT registers

LCD interfacing in 4-bit mode

UART initialization and serial communication

UART transmit and receive registers

Arrays and character strings

while and for loops

Conditional statements (if-else)

String termination using '\0'

Bitwise operations and register configuration

#Simulation Procedure

Create the circuit in Proteus using the pin connections listed above.

Write the embedded C program in MPLAB X IDE.

Compile the program using the XC8 compiler.

Load the generated HEX file into the PIC16F876A component in Proteus.

Set the Virtual Terminal to 9600 baud, 8-N-1.

Run the simulation.

Enter 123 or another password and press Enter.

Observe the authentication result on the LCD.
