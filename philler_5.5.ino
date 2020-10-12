#include <avr/io.h>   /* Include AVR std. library file */
#include <stdio.h>    /* Include std. library file */
#include <util/delay.h>

#include "keypad.h"
#define F_CPU 8000000UL
#include "LCD16x2_4bit.c"
int paitno;
int currentno;


int main(void)
{

  int state;
  DDRD = 0xff;
  DDRB = 0b11111100;
  PORTB = 0x00000011;
  DDRA = 0xFF;
  lcdinit();
  lcd_gotoxy(0, 0);
  lcd_print("THE PHILLER");
  _delay_ms(2000);


  paitno = 0;
  currentno = 0;
  _delay_ms(10);


  while (1)
  {

    state = getstate();
    if (state == 1)
    {
      while (1)
      { lcdinit();
        lcd_gotoxy(0, 0);
        lcd_clear();

        lcd_print("Filling Bot");

        fillbot();
        state = getstate();
        if ( state == 0)
          break;
      }
    }

    else if (state == 0)
    {
      while (1)
      {
        lcdinit();
        lcd_gotoxy(0, 0);
        lcd_clear();
        lcd_print("Filling Philler");
        inputmed();
        state = getstate();
        if ( state == 1)
          break;
      }
    }
  }
}


void seldos(char dos)
{
  DDRD |= (1 << PD5); /* Make OC1A pin as output */
  TCNT1 = 0;    /* Set timer1 count zero */
  ICR1 = 4999;    /* Set TOP count for timer1 in ICR1 register */

  /* Set Fast PWM, TOP in ICR1, Clear OC1A on compare match, clk/64 */
  TCCR1A = (1 << WGM11) | (1 << COM1A1);
  TCCR1B = (1 << WGM12) | (1 << WGM13) | (1 << CS10) | (1 << CS11);


  if (dos == 'A')
    OCR1A = 208;

   if (dos == 'B')
    OCR1A = 375;

   if (dos == 'C')
    OCR1A = 541;

}

void inputmed()
{
  lcd_clear();
  lcd_gotoxy(0, 0);
  lcd_print("Select the dosage");
  //_delay_ms(1000);
  char dosage = paitin();
_delay_ms(500);
  seldos(dosage);
  _delay_ms(500);
  lcd_clear();
  
  

//  if (dosage == 'A')
//    lcd_print("Morning");
//  else if (dosage == 'B')
//    lcd_print("Noon");
//  else if (dosage == 'C')
//    lcd_print("Evining");




  lcd_gotoxy(1, 0);
  lcd_print("Filling Philler");
  if (dosage == 'A' | dosage == 'B' | dosage == 'C')
  {
    while (1)
    {


      paitno = getpait();
      lcd_gotoxy(0, 0);
      lcd_clear();
      lcd_printint(paitno);
      //_delay_ms(10);

      if (paitno == 0) break;
      else if (currentno != paitno && paitno < 10)
      {
        rotatetray(paitno, currentno);
        // flip();
        // _delay_ms(1000);

      }
      lcd_gotoxy(0, 0);
      lcd_clear();
      lcd_print("Medicine taken");
      if (paitno != 0)
        currentno = paitno;
      //  paitno =0;
    }
  }
}


int getstate()
{
  if (!(PINB & (1 << PINB0)))
    return 1;
  else return 0;

}


void fillbot()
{
  DDRB = 0x00;
  PORTB = 0xff;
  //  while (1)
  //  {
  DDRA = 0xff;
  //    PORTD = 0x01;
  //    _delay_ms(100);
  if (!(PINB & (1 << PINB1)))
  {
    _delay_ms(300);
    PORTA = 0b00000000;
    for (int i = 1; i <= 3; i++)
    {
    
//      lcd_gotoxy(0, 0);
//      lcd_clear();
//      lcd_printint(i);

          PORTA = 0b00000000;
         
      
    

      if (i != currentno)
        getmed(i, currentno);
        
    }
    
  }
  //}


}



void getmed( int in, int cur)
{
  rotatetray(in, cur);
  PORTA = 0b00000000;
  flip();
  lcd_gotoxy(1, 0);
  lcd_clear();
  lcd_print("Medicine droped");
  _delay_ms(500);
  currentno = in;
  //PORTD = 0x01;
  // _delay_ms(100);

}



void flip()
{
  DDRA = 0xFF;
  int j, i;

  for (i = 0; i < 30; i++)
  {
    PORTA = 0x10;
    _delay_ms(2);
    PORTA = 0x00;
    _delay_ms(19);
  }
  _delay_ms(500);
  for (i = 0; i < 20; i++)
  {
    PORTA = 0x10;
    _delay_ms(1);
    PORTA = 0x00;
    _delay_ms(18);
  }

}





void rotatebck()
{
  DDRA = 0xff;
  int period = 10;
  for (int i = 0; i < 65; i++)
  {
    PORTA = 0x09;
    _delay_ms(period);
    PORTA = 0x08;
    _delay_ms(period);
    PORTA = 0x0C;
    _delay_ms(period);
    PORTA = 0x04;
    _delay_ms(period);
    PORTA = 0x06;
    _delay_ms(period);
    PORTA = 0x02;
    _delay_ms(period);
    PORTA = 0x03;
    _delay_ms(period);
    PORTA = 0x01;
    _delay_ms(period);
  }
}



void rotatefrt()
{
  DDRA = 0xff;
  int period = 10;
  for (int i = 0; i < 65; i++)
  {
    PORTA = 0x01;
    _delay_ms(period);
    PORTA = 0x03;
    _delay_ms(period);
    PORTA = 0x02;
    _delay_ms(period);
    PORTA = 0x06;
    _delay_ms(period);
    PORTA = 0x04;
    _delay_ms(period);
    PORTA = 0x0C;
    _delay_ms(period);
    PORTA = 0x08;
    _delay_ms(period);
    PORTA = 0x09;
    _delay_ms(period);

  }
}


int rotatetray (int in, int cur)
{

  if (cur < in )
  {
    for (int i = 0; i < (in - cur); i++)
    {
      rotatefrt();

      // _delay_ms(100);

    }
  }

  else if (cur > in )
  {
    for (int i = 0; i < (cur - in); i++)
    {
      rotatebck();

      // _delay_ms(100);
    }
  }


  return (0);
}
