


#include <xc.h>
#define _XTAL_FREQ 4000000

// Configuration bits
#pragma config FOSC = XT
#pragma config WDTE = OFF
#pragma config PWRTE = ON
#pragma config BOREN = ON
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config CP = OFF

// LCD connections
// RS = RB0, E = RB2
// D4 = RB3, D5 = RB4
// D6 = RB5, D7 = RB6
// LCD R/W connected to GND

#define RS PORTBbits.RB0
#define EN PORTBbits.RB2

// LCD enable pulse
void lcd_pulse(void)
{
    EN = 1;
    __delay_ms(2);
    EN = 0;
    __delay_ms(2);
}

// Send 4 bits to LCD
void lcd_nibble(unsigned char data)
{
    PORTB = (PORTB & 0x87) | ((data & 0x0F) << 3);
    lcd_pulse();
}

// Send LCD command
void lcd_command(unsigned char cmd)
{
    RS = 0;
    lcd_nibble(cmd >> 4);
    lcd_nibble(cmd & 0x0F);
    __delay_ms(2);
}

// Send character to LCD
void lcd_data(char ch)
{
    RS = 1;
    lcd_nibble(ch >> 4);
    lcd_nibble(ch & 0x0F);
    __delay_ms(2);
}

// Display string on LCD
void lcd_string(const char *s)
{
    while(*s != '\0')
    {
        lcd_data(*s);
        s++;
    }
}

// Initialize LCD
void lcd_init(void)
{
    TRISB = 0x00;
    PORTB = 0x00;

    __delay_ms(20);

    RS = 0;
    lcd_nibble(0x03);
    __delay_ms(5);
    lcd_nibble(0x03);
    __delay_ms(2);
    lcd_nibble(0x03);
    lcd_nibble(0x02);

    lcd_command(0x28);  // 4-bit, 2-line mode
    lcd_command(0x0C);  // Display ON
    lcd_command(0x06);  // Cursor moves forward
    lcd_command(0x01);  // Clear display
}

// Initialize UART
void uart_init(void)
{
    TRISC = 0x80;       // RC6 output, RC7 input

    TXSTA = 0x24;       // Asynchronous mode, TX enabled
    RCSTA = 0x90;       // Serial port and receiver enabled
    SPBRG = 25;         // Approximately 9600 baud at 4 MHz
}

// Transmit one character
void uart_transmit(char ch)
{
    while(TRMT == 0);
    TXREG = ch;
}

// Transmit string to Virtual Terminal
void uart_string(const char *s)
{
    while(*s != '\0')
    {
        uart_transmit(*s);
        s++;
    }
}

// Receive one character
char uart_receive(void)
{
    while(RCIF == 0);
    return RCREG;
}

// Main program
void main(void)
{
    char password[20];
    char ch;
    unsigned char i;
    unsigned char correct;

    ADCON1 = 0x06;

    lcd_init();
    uart_init();

    while(1)
    {
        lcd_command(0x01);
        lcd_string("Enter Password");

        uart_string("\r\nENTER PASSWORD: ");

        i = 0;

        // Receive password
        while(1)
        {
            ch = uart_receive();

            if(ch == '\r' || ch == '\n')
            {
                break;
            }

            if(i < 19)
            {
                password[i] = ch;
                i++;
                uart_transmit('*');
            }
        }

        password[i] = '\0';

        // Check password
        correct = 0;

        if(password[0] == '1' &&
           password[1] == '2' &&
           password[2] == '3' &&
           password[3] == '\0')
        {
            correct = 1;
        }

        // Display result
        lcd_command(0x01);

        if(correct == 1)
        {
            lcd_string("ACCESS GRANTED");
            //uart_string("\r\nACCESS GRANTED\r\n");
        }
        else
        {
            lcd_string("ACCESS DENIED");
            // No denial message sent to Virtual Terminal
        }

        __delay_ms(2000);
    }
}
