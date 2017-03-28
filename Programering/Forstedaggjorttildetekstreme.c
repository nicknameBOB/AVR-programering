/*
 * Dag1komplett.c
 *
 * Created: 11.03.2017 15:07:20
 * Author : Jørgen Steen
 * Laget for ATtiny817 Xplained Pro
 */ 
 /*

 ALLE OPPGAVER ER SKREVET INN I HVER SIN FUNKSJON SÅ DET ER LETT Å FINNE FRAM IKKE NOE ANNEN GRUNN. 
FUNKSJON: Trykke på knapper og så skjer stuff

sw0: Slå på alle led
sw1: Slå av alle led
BUTTON 1:
BUTTON 2:
BUTTON 3: 


 */
#define F_CPU 3333333UL // Det er en 20Mhz klokke på brettet, men den forhånds prescalet med en faktor på 6. 20/6 = 3.333333Mhz
#include <avr/io.h> //Denne tar man alltid med
#include <util/delay.h> //Tar med denne for første dagen

//defines
#define led1 0b00000001  // PINB0 LED 1 på OLED
#define led2 0b00000010  //PINB1 Led 2 på OLED
#define led3 0b00010000  //PINB4 LED 4 på OLED og LED0 på brettet

#define button0 0b00100000 //PINB5 knapp 0 på brettet
#define button1 0b00100000 //PINA5 knapp 1 på OLED
#define button2 0b01000000 //PINA6 knapp 2 på OLED
#define button3 0b10000000 //PINA7 knapp 3 på OLED
#define button4 0b00100000 //PINC5 knapp 1 på brettet 

#define TRUE 1
#define FALSE 0

//Flagger knappen etter trykt for å ungå at et trykk teller som flere
//Disse er det kun et poeng å bruke hvis man toggler noe i dette eksempelet
uint8_t buttonflag0 = FALSE;
uint8_t buttonflag1 = FALSE;
uint8_t buttonflag2 = FALSE;
uint8_t buttonflag3 = FALSE;
uint8_t buttonflag4 = FALSE;
uint8_t blinkon = FALSE;
void ledgjennomgang(void)
{
	//slår på ledene
	PORTB.OUT &= ~(led1);
	_delay_ms(1000);
	PORTB.OUT &= ~(led2);
	_delay_ms(1000);
	PORTB.OUT &= ~(led3);
	_delay_ms(1000);

	//slår de av
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
	//Kan også skrives for hver utgang PORTB.DIR |= led1; osv
	
	//starter de avslått
	PORTB.OUT = led1 | led2 | led3;


}
//initierer buttons
void buttoninit(void)
{
   //Setter knappene som inngang, selv om han egentlig ikke trenger det. 
   //Derfor kan man hoppe over det hvis det skaper forvirring

   //knappene i B registeret
   PORTB.DIR &= ~(button0); //Knapp 0 på brettet

   //knappene i A registeret
   PORTA.DIR &= ~(button1); //Knapp 1 på brettet
   PORTA.DIR &= ~(button2); //Knapp 2 på brettet
   PORTA.DIR &= ~(button3); //Knapp 3 på brettet
   //knappene i C registeret
   PORTC.DIR &= ~(button0); //Knapp 4 på brettet

   //Slå på pullupmotstandene og alle måtene man kan gjøre det

	//Knapp 0
   	PORTB.PIN5CTRL |= (1 << PORT_PULLUPEN_bp); //ryddig men lite pedagogisk
	//knapp 1-3
	PORTA.PIN5CTRL |= 0b00001000; //mest pedagogisk siden du ser hvilke bit i registere man snakker med, men binært kan bli surrete
	PORTA.PIN6CTRL |= 0x08; //samme som over hvis man kan hexa.
	PORTA.PIN7CTRL |= 8;  //Ikke gjøre dette. Ikke pedagosik og uoversiktlig
	//knapp 4
	PORTB.PIN5CTRL |= (1 << 3); //skifter bit 3 til 1 i registeret
}

//Her alt med knappene skjer
void buttonles(void)
{
	//Siden alle knappene er koblet til Pull-up Motstander så de høye til man trykker på de.
	//derfor ønsker vi å sjekke når pinnen ikke er høy.

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
		buttonflag0 = FALSE; //slår av flagget så man kan gå inn på kanppefunksjonen
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
		buttonflag1 = FALSE; //slår av flagget så man kan gå inn på kanppefunksjonen
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
		buttonflag2 = FALSE; //slår av flagget så man kan gå inn på kanppefunksjonen
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
		buttonflag3 = FALSE; //slår av flagget så man kan gå inn på kanppefunksjonen
	}
	
	//Knapp 4	----------------------------------------------------
	if(!(PORTC.IN & button4))
	{
		if (buttonflag4 == 0)
		{
			PORTB.OUT = led1 | led2 | led3; //slår alle led av
			buttonflag4 = TRUE; //setter flaget
			_delay_ms(500);
		}
	}
	else
	{
		buttonflag4 = FALSE; //slår av flagget så man kan gå inn på kanppefunksjonen
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
	return(0); //SÅ den ikke klager
}

