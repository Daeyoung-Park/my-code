#define F_CPU 16000000UL
#define ADCSRA  _SFR_IO8(0x06)
#define SFIOR   _SFR_IO8(0x30)

#include <avr/io.h>
#include <util/delay.h>
#include "LCD.h"  // LCD ���� �Լ� ��� ����
#include <stdlib.h>


float temp; 
int speed = 0;
unsigned char spd_1 = 0;
unsigned char spd_2 = 0;
unsigned char spd_3 = 0;

//��Ʈ�ʱ�ȭ �Լ� ����
void initPort()
{
	DDRA = 0xff;	//PortA�� ������� ���
	DDRB = 0xff;	//PortB�� ������� ���
	DDRC = 0xf0;	//PortC�� ������� ���
	DDRD = 0xff;	//PortD�� ������� ���		
	DDRF = 0x00;	//PortF�� �Է����� ���
	                // -> PortF0�� A/D �Է����� ��� (Step 1)
}

void start()
{
	int i=0;
	for(i=0; i<3; i++)
	{
		lcd_display_string(0,0,"adjust level");
		lcd_display_string(0,1,"using a/d");
		PORTA = 0x00;
		_delay_ms(2000);
		
		PORTA = 0xFF;
		lcd_init();
		_delay_ms(2000);
	}
	
	lcd_init();
}

int main(void)
{
	initPort( ) ;		//��Ʈ �ʱ�ȭ
	lcd_init( ) ;       // LCD �ʱ�ȭ
	
	unsigned char Led_table[8] = { 0b11111110, 0b11111101, 0b11111011, 0b11110111, 0b11101111, 0b11011111,
									0b10111111, 0b01111111 };
	int randomLed = random() % 8;
 
	PORTA = 0xFF ;
	PORTB = 0x00 ; // 7 Segment Off
	
	unsigned char Seg_table[16]={ 0x3F,0x06,0x5B,0x4F,
	                              0x66,0x6D,0x7D,0x07,
								  0x00,0x00,0x00,0x00,
								  0x00,0x00,0x00,0x00 }; //0~7������ ���
	
	unsigned char key_check[2] = { 0x70, 0xe0} ; //0b01110000, 0b11100000, 0b11010000, 0b10110000 0->1432
	unsigned char value = 0 ;
	unsigned char inp = 0, key = 0 ;
	int i = 0 ; unsigned char numOfClick = 0;
	
	ADMUX  = 0x60;	//Vref=AVcc, ADC0�� �������и��, �·�����
	ADCSRA = 0xa5;	//ADC enable, ���������Ϸ� 32, ���Ϻ�ȯ���, auto trigger
	SFIOR &= 0x1f;	//free running ���
	ADCSRA |= 0x40; //ADC ����
	
	start();
	
	while(1) {
		_delay_us(200);	//���ø� �Ⱓ
		ADCSRA |= 0x10; //clear ADIF
		while((ADCSRA & 0x10) == 0x00)	//ADIF=1�� ������ ����
		{
			randomLed = random() % 8;
			_delay_ms(speed); // ���� �߰�!  �� �ڵ� �ִ� ���� ����� �ν� ���� -> ���ͷ�Ʈ ����� ������ �� ������ ���� ��ư ������ �ν��� ���Ѵ�;;
			PORTA = Led_table[randomLed]; // ���� ��������: ��ǻ�Ͱ� LED �� �ѷ��ָ� �׿� �´� ������ ���� ����ߴٰ� Ű�е�� ���� ���ߴ� ��������
			
			for(i=0; i<2; i++) {
				PORTC = key_check[i] ;
				value = PINC ; // PORTC�κ��� �Է��� ����
				value &= 0x0f ;
			
				if(value != 0x0f) { // ���� �κ�: value�� Ű�� ���� �Ͱ� ������� ������ 0x0f�� �ƴϰ� �Ǿ Ű�е� �ȴ����� �� if���� ������ 
					inp = (~value)&0x0f ; // ���� �κ�:
					
					if(inp == 0x01){ key = 0 + 4*i ; _delay_ms(250); numOfClick++; }
					if(inp == 0x02){ key = 1 + 4*i ; _delay_ms(250); numOfClick++; } 
					if(inp == 0x04){ key = 2 + 4*i ; _delay_ms(250); numOfClick++; } 
					if(inp == 0x08){ key = 3 + 4*i ; _delay_ms(250); numOfClick++; } 
				
					PORTB = Seg_table[key] ;
				
					lcd_position(14,0);
					if(numOfClick>=10)
					{
						lcd_write_char( numOfClick/10 + '0');
						lcd_write_char( numOfClick%10 + '0');
					}
					else
						lcd_write_char( numOfClick + '0');
				}
			}
		}
		
		temp = ADCH;	//LED�� ǥ���ϱ����� ADCL�� ������ ������ �־��.
				
		speed=(temp*999)/255;
		spd_1 = speed/100 ;
		spd_2 = (speed/10)%10 ;
		spd_3 = speed%10 ;
		
		lcd_position(3,1);
		lcd_write_char(spd_1+'0');
		lcd_write_char('.');
		lcd_write_char(spd_2+'0');
		lcd_write_char(spd_3+'0');
		lcd_write_char('S');
		lcd_write_char('p');
		lcd_write_char('d');
	} 
}

