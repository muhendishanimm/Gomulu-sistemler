/**********************************************
 * *Dosya          :lcd.h
 * *Amaç           :4x20 LCD kullanma
 * *Yazar          :Salih GÖRGÜNOĞLU
 * *Versiyon       :V1.0
 * * LCD Pin bağlantısı :
 * *  PB1   LCD_EN
 * *  PB0   LCD_RS
 * *  PB4   LCD_D4
 * *  PB5   LCD_D5
 * *  PB6   LCD_D6
 * *  PB7   LCD_D7
 * *  RW    ->Toprak
 * ************************************************/

#ifndef __LCD_H // Daha once tanımlı değil ise
#define __LCD_H // lcd.h kullan

#define lcddelay 200

void delay_us(uint16_t n) {
  uint16_t j;
  while (n--) { for (j = 0; j < 7; j++); } //48Mhz de 7 olursa  1.1 mikrosaniye
}


void delay_ms(uint16_t n) { //48Mhz
	uint16_t j;
	while (n--) { for(j=0;j<222;j++); }  //48Mhz de 1 milisaniye 2666
}

void clock() {
  GPIOB -> BSRR = GPIO_PIN_0;
  delay_us(100);
  GPIOB -> BRR = GPIO_PIN_0;
  delay_us(100);
}

void yuklelcd(unsigned char deger)
{
  HAL_Delay(2);
  if((deger & 0x10) == 0x10) GPIOB -> BSRR = GPIO_PIN_4; else GPIOB -> BRR = GPIO_PIN_4;
  if((deger & 0x20) == 0x20) GPIOB -> BSRR = GPIO_PIN_5; else GPIOB -> BRR = GPIO_PIN_5;
  if((deger & 0x40) == 0x40) GPIOB -> BSRR = GPIO_PIN_6; else GPIOB -> BRR = GPIO_PIN_6;
  if((deger & 0x80) == 0x80) GPIOB -> BSRR = GPIO_PIN_7; else GPIOB -> BRR = GPIO_PIN_7;

}

void sendCmdLcd(uint16_t cmd) {
  yuklelcd(cmd);
  GPIOB -> BRR = GPIO_PIN_1; //RS=0
  clock();
  yuklelcd(cmd<<4);
  clock();
  delay_ms(lcddelay);
}

void sendDataLcd(uint16_t veri)
{
  yuklelcd(veri);
  GPIOB -> BSRR = GPIO_PIN_1; //RS=1
  clock();
  yuklelcd(veri<<4);
  clock();
  delay_ms(lcddelay);
}

void writeStr(uint16_t sat, uint16_t sut, char * str)
{
	uint16_t adr = 0;

	if (sat == 1) adr = 0x80 + sut;
	if (sat == 2) adr = 0xC0 + sut;
	if (sat == 3) adr = 0x94 + sut;
	if (sat == 4) adr = 0xD4 + sut;
	sendCmdLcd(adr);
	while ( * str != 0) {
	  sendDataLcd( * str++);
	}
}

void writeStr1(uint16_t sat, uint16_t sut, char * str)
{
	uint16_t adr = 0, j = 0;

	if (sat == 1) adr = 0x80 + 0x00 + sut;
	if (sat == 2) adr = 0x80 + 0x40 + sut;
	if (sat == 3) adr = 0x80 + 0x14 + sut;
	if (sat == 4) adr = 0x80 + 0x54 + sut;
	sendCmdLcd(adr); //while(*str!='\0'){ String sonununa 0 konursa "merhaba\0" gibi
	while(str[j]!=0)
	{
		sendDataLcd(str[j]);
		j++;
	}
}

void clearLcd(void) {
  sendCmdLcd(0x01);
  delay_us(lcddelay);
}

void clearLcd2(void) {
  writeStr(1, 0, "                    ");
  writeStr(2, 0, "                    ");
  writeStr(3, 0, "                    ");
  writeStr(4, 0, "                    ");
}

void setCursor(uint16_t sat, uint16_t sut)
{
  uint16_t adr = 0;
  if (sat == 1) adr = 0x80 + 0x00 + sut;
  if (sat == 2) adr = 0x80 + 0x40 + sut;
  if (sat == 3) adr = 0x80 + 0x14 + sut;
  if (sat == 4) adr = 0x80 + 0x54 + sut;
  sendCmdLcd(adr);
  delay_us(lcddelay);
}

void cursorOn(void) {
  sendCmdLcd(0x0F); //0x0E display control:turn display on, cursor on, no blinking
  delay_us(lcddelay);
}

void cursorOn2(uint16_t sat, uint16_t sut) {
	uint16_t adr = 0;
	if (sat == 1) adr = 0x80 + sut;
	if (sat == 2) adr = 0xC0 + sut;
	if (sat == 3) adr = 0x94 + sut;
	if (sat == 4) adr = 0xD4 + sut;
	sendCmdLcd(adr);
	sendCmdLcd(0x0F); //0x0E display control:turn display on, cursor on, no blinking
	delay_us(lcddelay);
}


void cursorOf(void) {
	sendCmdLcd(0x0C); //0x0E display control:turn display on, cursor of, no blinking
	delay_us(lcddelay);
}

void lcdInit(void)
{
	HAL_Delay(20); //LCD Power ON Initialization time >15ms
	sendCmdLcd(0x02); //4bit mode
	HAL_Delay(10);
	sendCmdLcd(0x28); //Initialization of LCD in 4bit mode
	HAL_Delay(10);
	sendCmdLcd(0x06); //entry mode set: increment automatically, no display shift
	HAL_Delay(5);
	sendCmdLcd(0x0C); //0x0E display control:turn display on, cursor on, no blinking
	HAL_Delay(5);
	sendCmdLcd(0x01); //clear display, set cursor position to zero
	HAL_Delay(5);
}

void displayDigit(uint16_t sat, uint16_t sut, uint8_t x) //0-9 arası degerleri gosterir
{
	uint8_t s0;

	uint16_t adr = 0;
	if (sat == 1) adr = 0x80 + sut;
	if (sat == 2) adr = 0xC0 + sut;
	if (sat == 3) adr = 0x94 + sut;
	if (sat == 4) adr = 0xD4 + sut;

	sendCmdLcd(adr);
	s0 = x + 48;
	sendDataLcd(s0);
}

void displayInt(uint16_t sat, uint16_t sut, int32_t x) //-99999 .... +99999 degerleri gosterir
{
	uint32_t sayix;
	uint16_t s4,s3,s2,s1,s0;  // 5 hane yazar

	uint16_t adr = 0;
	if (sat == 1) adr = 0x80 + sut;
	if (sat == 2) adr = 0xC0 + sut;
	if (sat == 3) adr = 0x94 + sut;
	if (sat == 4) adr = 0xD4 + sut;

	sendCmdLcd(adr);
	HAL_Delay(2);
	if (x < 0) {
	  x = -x;
	  sendDataLcd('-');
	} //gelen sayi - ise;
	sayix=x;           s4=sayix/10000;
	sayix=sayix%10000; s3=sayix/1000;
	sayix=sayix%1000;  s2=sayix/100;
	sayix=sayix%100;   s1=sayix/10;
	sayix=sayix%10;    s0=sayix;
	if (x < 100) {
	  sendDataLcd(s1 + 48);
	  sendDataLcd(s0 + 48);
	}
	if (x >= 100 && x < 1000) {
	  sendDataLcd(s2 + 48);
	  sendDataLcd(s1 + 48);
	  sendDataLcd(s0 + 48);
	}
	if (x >= 1000 && x < 10000) {
	  sendDataLcd(s3 + 48);
	  sendDataLcd(s2 + 48);
	  sendDataLcd(s1 + 48);
	  sendDataLcd(s0 + 48);
	}
	if (x >= 10000 && x < 100000) {
	  sendDataLcd(s4 + 48);
	  sendDataLcd(s3 + 48);
	  sendDataLcd(s2 + 48);
	  sendDataLcd(s1 + 48);
	  sendDataLcd(s0 + 48);
	}
}

      //---------------------------------------------------------------------------
void displayFloat(uint16_t sat, uint16_t sut, float x)//9999.999 degerini gosterir
{
	uint32_t sayix;
	uint16_t s5,s4,s3,s2,s1,s0;
	uint16_t adr=0;
	if(sat==1) adr=0x80+sut;
	if(sat==2) adr=0xC0+sut;
	if(sat==3) adr=0x94+sut;
	if(sat==4) adr=0xD4+sut;

	sendCmdLcd(adr);

	if (x < 0) { //gelen sayi - ise;
		x = -x;
		sendDataLcd('-');
	}

	sayix = x * 100;        s5 = sayix / 100000;
	sayix = sayix % 100000; s4 = sayix / 10000;
	sayix = sayix % 10000;  s3 = sayix / 1000;
	sayix = sayix % 1000;   s2 = sayix / 100;
	sayix = sayix % 100;    s1 = sayix / 10;
	sayix = sayix % 10;     s0 = sayix;
	sut = sut + 1;

	if (x >= 0 && x < 10) //9.99
	{
		sendDataLcd(s2+48);
		sendDataLcd('.');
		sendDataLcd(s1+48);
		sendDataLcd(s0+48);
	}
	if (x >= 10 && x < 100) //99.99
	{
		sendDataLcd(s3+48);
		sendDataLcd(s2+48);
		sendDataLcd('.');
		sendDataLcd(s1+48);
		sendDataLcd(s0+48);
	}
	if (x >= 100 && x < 1000) //999.99
	{
		sendDataLcd(s4+48); sendDataLcd(s3+48); sendDataLcd(s2+48);
		sendDataLcd('.');
		sendDataLcd(s1+48); sendDataLcd(s0+48);
	}

	if (x >= 1000 && x < 10000) //9999.99
	{
		sendDataLcd(s5+48); sendDataLcd(s4+48); sendDataLcd(s3+48); sendDataLcd(s2+48);
		sendDataLcd('.');
		sendDataLcd(s1 + 48);
		sendDataLcd(s0 + 48);
	}
}

//---------------------------------------------------------------------------

# endif
