
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
// RS = RB0, E = RB1
// D4 = RB2, D5 = RB3
// D6 = RB4, D7 = RB5

#define RS PORTBbits.RB0
#define EN PORTBbits.RB1

// ---------- LCD FUNCTIONS ----------

void lcd_pulse(void)
{
    EN = 1;
    __delay_ms(2);
    EN = 0;
    __delay_ms(2);
}

void lcd_send_nibble(unsigned char data)
{
    PORTB = (PORTB & 0xC3) | ((data & 0x0F) << 2);
    lcd_pulse();
}

void lcd_command(unsigned char cmd)
{
    RS = 0;
    lcd_send_nibble(cmd >> 4);
    lcd_send_nibble(cmd & 0x0F);
    __delay_ms(2);
}

void lcd_data(unsigned char data)
{
    RS = 1;
    lcd_send_nibble(data >> 4);
    lcd_send_nibble(data & 0x0F);
    __delay_ms(2);
}

void lcd_init(void)
{
    TRISB = 0x00;
    PORTB = 0x00;

    __delay_ms(20);

    RS = 0;
    lcd_send_nibble(0x03);
    __delay_ms(5);
    lcd_send_nibble(0x03);
    __delay_ms(2);
    lcd_send_nibble(0x03);
    lcd_send_nibble(0x02);

    lcd_command(0x28);  // 4-bit, 2-line mode
    lcd_command(0x0C);  // Display ON
    lcd_command(0x06);  // Cursor increment
    lcd_command(0x01);  // Clear display
}

void lcd_string(const char *str)
{
    while(*str != '\0')
    {
        lcd_data(*str);
        str++;
    }
}

void lcd_clear(void)
{
    lcd_command(0x01);
    __delay_ms(2);
}

// ---------- UART FUNCTIONS ----------

void uart_init(void)
{
    TRISCbits.TRISC6 = 0;  // TX output
    TRISCbits.TRISC7 = 1;  // RX input

    TXSTAbits.SYNC = 0;    // Asynchronous mode
    TXSTAbits.BRGH = 1;    // High-speed baud rate
    TXSTAbits.TXEN = 1;    // Enable transmitter

    RCSTAbits.SPEN = 1;    // Enable serial port
    RCSTAbits.CREN = 1;    // Enable receiver

    SPBRG = 25;            // Approx. 9600 baud at 4 MHz
}

void uart_transmit(char ch)
{
    while(TXSTAbits.TRMT == 0);
    TXREG = ch;
}

void uart_string(const char *str)
{
    while(*str != '\0')
    {
        uart_transmit(*str);
        str++;
    }
}

char uart_receive(void)
{
    if(RCSTAbits.OERR)
    {
        RCSTAbits.CREN = 0;
        RCSTAbits.CREN = 1;
    }

    while(PIR1bits.RCIF == 0);

    if(RCSTAbits.FERR)
    {
        volatile unsigned char dummy = RCREG;
        (void)dummy;
        return '\0';
    }

    return RCREG;
}

// ---------- MAIN PROGRAM ----------

void main(void)
{
    char password[20];
    unsigned char i;
    unsigned char correct;
    char ch;

    ADCON1 = 0x06;  // Configure analog-capable pins as digital

    lcd_init();
    uart_init();

    lcd_string("PASSWORD SYSTEM");
    uart_string("\r\nPASSWORD SYSTEM\r\n");
    __delay_ms(1500);

    while(1)
    {
        lcd_clear();
        lcd_string("Enter Password:");

        uart_string("\r\nEnter password: ");

        i = 0;

        // Receive password and send * for each character
        while(1)
        {
            ch = uart_receive();

            if(ch == '\r' || ch == '\n')
            {
                break;
            }

            if(ch != '\0')
            {
                if(i < sizeof(password) - 1)
                {
                    password[i] = ch;
                    i++;

                    // Mask the password in the terminal
                    uart_transmit('*');
                }
            }
        }

        password[i] = '\0';

        // Check whether password is 123
        correct = 0;

        if(password[0] == '1' &&
           password[1] == '2' &&
           password[2] == '3' &&
           password[3] == '\0')
        {
            correct = 1;
        }

        lcd_clear();

        if(correct)
        {
            lcd_string("ACCESS GRANTED");
            uart_string("\r\nACCESS GRANTED\r\n");
        }
        else
        {
            lcd_string("ACCESS DENIED");
            uart_string("\r\nACCESS DENIED\r\n");
        }

        __delay_ms(2000);
    }
}
