#define KEY_PRT   PORTC
#define KEY_DDR   DDRC
#define KEY_PIN   PINC
int pait;




//unsigned char keypad[4][4] = {  {'1','4','7',' '},
//        {'2','5','8','*'},
//        {'3','6','9','='},
//        {'/','*','-','+'}};


unsigned char keypad[4][4] = {  {'7','8','9','A'},
        {'4','5','6','B'},
        {'1','2','3','C'},
        {' ','0','=','+'}};
unsigned char colloc, rowloc;



char paitin()
{
  while(1)
  {
      KEY_DDR = 0xF0;           /* set port direction as input-output */
      KEY_PRT = 0xFF;

      do
      {
    KEY_PRT &= 0x0F;      /* mask PORT for column read only */
    asm("NOP");
    colloc = (KEY_PIN & 0x0F); /* read status of column */
      }while(colloc != 0x0F);
    
      do
      {
    do
    {
              _delay_ms(20);             /* 20ms key debounce time */
        colloc = (KEY_PIN & 0x0F); /* read status of column */
    }while(colloc == 0x0F);        /* check for any key press */
      
    _delay_ms (40);             /* 20 ms key debounce time */
    colloc = (KEY_PIN & 0x0F);
      }while(colloc == 0x0F);

     /* now check for rows */
      KEY_PRT = 0xEF;            /* check for pressed key in 1st row */
      asm("NOP");
      colloc = (KEY_PIN & 0x0F);
      if(colloc != 0x0F)
            {
    rowloc = 0;
    break;
      }

      KEY_PRT = 0xDF;   /* check for pressed key in 2nd row */
      asm("NOP");
      colloc = (KEY_PIN & 0x0F);
      if(colloc != 0x0F)
      {
    rowloc = 1;
    break;
      }
    
      KEY_PRT = 0xBF;   /* check for pressed key in 3rd row */
      asm("NOP");
            colloc = (KEY_PIN & 0x0F);
      if(colloc != 0x0F)
      {
    rowloc = 2;
    break;
      }

      KEY_PRT = 0x7F;   /* check for pressed key in 4th row */
      asm("NOP");
      colloc = (KEY_PIN & 0x0F);
      if(colloc != 0x0F)
      {
    rowloc = 3;
    break;
      }
  }

  if(colloc == 0x0E)
     return(keypad[rowloc][0]);
  else if(colloc == 0x0D)
     return(keypad[rowloc][1]);
  else if(colloc == 0x0B)
     return(keypad[rowloc][2]);
  else
     return(keypad[rowloc][3]);
}


int getpait()
{
   pait;
  char paitstr = paitin();

  if (paitstr == '1') pait =1;
  else if (paitstr == '2') pait =2;
  else if (paitstr == '3') pait =3;
  else if (paitstr == '4') pait =4;
  else if (paitstr == '5') pait =5;
  else if (paitstr == '6') pait =6;
  else if (paitstr == '7') pait =7;
  else if (paitstr == '8') pait =8;
  else if (paitstr == '9') pait =9;
  else if (paitstr == '0') pait =0;

  return pait;
  
  }
