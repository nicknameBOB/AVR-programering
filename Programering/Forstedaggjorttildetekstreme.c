/*
 * Dag1komplett.c
 *
 * Created: 11.03.2017 15:07:20
 * Author : J�rgen Steen
 * Laget for ATtiny817 Xplained Pro
 */ 
 /*

 ALLE OPPGAVER ER SKREVET INN I HVER SIN FUNKSJON S� DET ER LETT � FINNE FRAM IKKE NOE ANNEN GRUNN. 
FUNKSJON: Trykke p� knapper og s� skjer stuff

sw0: Sl� p� alle led
sw1: Sl� av alle led
BUTTON 1:
BUTTON 2:
BUTTON 3: 


 */
#define F_CPU 3333333UL // Det er en 20Mhz klokke p� brettet, men den forh�nds prescalet med en faktor p� 6. 20/6 = 3.333333Mhz
#include <avr/io.h> //Denne tar man alltid med
#include <util/delay.h> //Tar med denne for f�rste dagen

//defines
#define led1 0b00000001  // PINB0 LED 1 p� OLED
#define led2 0b00000010  //PINB1 Led 2 p� OLED
#define led3 0b00010000  //PINB4 LED 4 p� OLED og LED0 p� brettet

#define button0 0b00100000 //PINB5 knapp 0 p� brettet
#define button1 0b00100000 //PINA5 knapp 1 p� OLED
#define button2 0b01000000 //PINA6 knapp 2 p� OLED
#define button3 0b10000000 //PINA7 knapp 3 p� OLED
#define button4 0b00100000 //PINC5 knapp 1 p� brettet 

#define TRUE 1
#define FALSE 0

//Flagger knappen etter trykt for � ung� at et trykk teller som flere
//Disse er det kun et poeng � bruke hvis man toggler noe i dette eksempelet
uint8_t buttonflag0 = FALSE;
uint8_t buttonflag1 = FALSE;
uint8_t buttonflag2 = FALSE;
uint8_t buttonflag3 = FALSE;
uint8_t buttonflag4 = FALSE;
uint8_t blinkon = FALSE;
void ledgjennomgang(void)
{
	//sl�r p� ledene
	PORTB.OUT &= ~(led1);
	_delay_ms(1000);
	PORTB.OUT &= ~(led2);
	_delay_ms(1000);
	PORTB.OUT &= ~(led3);
	_delay_ms(1000);

	//sl�r de av
	PORTB.OUT |= led3;
	_delay_ms(1000);
	PORTB.OUT |= led2;
	_delay_ms(1000);
	PORTB.OUT |= led1;
	_delay_ms(1000);




}
//initierer ledene
void ledinit(void)
{
	//sette ledene som utganger som utganger
	PORTB.DIR = led1 | led2 | led3;
	//Kan ogs� skrives for hver utgang PORTB.DIR |= led1; osv
	
	//starter de avsl�tt
	PORTB.OUT = led1 | led2 | led3;


}
//initierer buttons
void buttoninit(void)
{
   //Setter knappene som inngang, selv om han egentlig ikke trenger det. 
   //Derfor kan man hoppe over det hvis det skaper forvirring

   //knappene i B registeret
   PORTB.DIR &= ~(button0); //Knapp 0 p� brettet

   //knappene i A registeret
   PORTA.DIR &= ~(button1); //Knapp 1 p� brettet
   PORTA.DIR &= ~(button2); //Knapp 2 p� brettet
   PORTA.DIR &= ~(button3); //Knapp 3 p� brettet
   //knappene i C registeret
   PORTC.DIR &= ~(button0); //Knapp 4 p� brettet

   //Sl� p� pullupmotstandene og alle m�tene man kan gj�re det

	//Knapp 0
   	PORTB.PIN5CTRL |= (1 << PORT_PULLUPEN_bp); //ryddig men lite pedagogisk
	//knapp 1-3
	PORTA.PIN5CTRL |= 0b00001000; //mest pedagogisk siden du ser hvilke bit i registere man snakker med, men bin�rt kan bli surrete
	PORTA.PIN6CTRL |= 0x08; //samme som over hvis man kan hexa.
	PORTA.PIN7CTRL |= 8;  //Ikke gj�re dette. Ikke pedagosik og uoversiktlig
	//knapp 4
	PORTB.PIN5CTRL |= (1 << 3); //skifter bit 3 til 1 i registeret
}

//Her alt med knappene skjer
void buttonles(void)
{
	//Siden alle knappene er koblet til Pull-up Motstander s� de h�ye til man trykker p� de.
	//derfor �nsker vi � sjekke n�r pinnen ikke er h�y.

	//Knapp 0	-------------------------------------------
	if(!(PORTB.IN & button0))
	{
		if (buttonflag0 == 0)
		{
			PORTB.OUT = ~(led1) & ~(led2) & ~(led3); 
			buttonflag0 = TRUE; //setter flaget
			_delay_ms(500);
		}
	}
	else
	{
		buttonflag0 = FALSE; //sl�r av flagget s� man kan g� inn p� kanppefunksjonen
	}
	
	//Knapp 1	---------------------------------------	
	if(!(PORTA.IN & button1))
	{
		if (buttonflag1 == 0)
		{
			ledgjennomgang();
			buttonflag1 = TRUE; //setter flaget
			_delay_ms(500);
		}
	}
	else
	{
		buttonflag1 = FALSE; //sl�r av flagget s� man kan g� inn p� kanppefunksjonen
	}

	//Knapp 2	-------------------------------------------
	if(!(PORTA.IN & button2))
	{
		if (buttonflag2 == 0)
		{
			blinkon = !blinkon;
			buttonflag2 = TRUE; //setter flaget
			_delay_ms(500);
		}
	}
	else
	{
		buttonflag2 = FALSE; //sl�r av flagget s� man kan g� inn p� kanppefunksjonen
	}

	//Knapp 3	---------------------------------------------
	if(!(PORTA.IN & button3))
	{
		if (buttonflag3 == 0)
		{
			PORTB.OUT ^= led3;
			buttonflag3 = TRUE; //setter flaget
			_delay_ms(500);
		}
	}
	else
	{
		buttonflag3 = FALSE; //sl�r av flagget s� man kan g� inn p� kanppefunksjonen
	}
	
	//Knapp 4	----------------------------------------------------
	if(!(PORTC.IN & button4))
	{
		if (buttonflag4 == 0)
		{
			PORTB.OUT = led1 | led2 | led3; //sl�r alle led av
			buttonflag4 = TRUE; //setter flaget
			_delay_ms(500);
		}
	}
	else
	{
		buttonflag4 = FALSE; //sl�r av flagget s� man kan g� inn p� kanppefunksjonen
	}		
}


int main(void)
{
	ledinit();
	buttoninit();
    /* Replace with your application code */
    while (1) 
    {
		buttonles();
		if (blinkon == TRUE)
		{
			PORTB.OUT ^= led1 | led2 | led3;
			_delay_ms(500);
		}
		_delay_ms(100); //litt end delay 
    }
	return(0); //S� den ikke klager
}

