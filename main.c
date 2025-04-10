#define F_CPU   16000000
#include <util/delay.h>
#include <avr/io.h>

int main(void) 
{
	// Configura PB1 e PB2 como entradas com pull-up
	DDRB &= ~((1<<2)|(1<<1));
	PORTB |= ((1<<2)|(1<<1));

	// Define PB3, PB4 e PB5 como saídas
	DDRB |= ((1<<3)|(1<<4)|(1<<5));
	
	// Inicializa saídas em nível baixo
	PORTB &= ~((1<<3)|(1<<4)|(1<<5));

	int estado = 0;
	int tempo = 0;
	
    while (1) 
    {
		if (estado == 0)
		{
			// Reset de saídas
			PORTB &= ~((1<<3)|(1<<4)|(1<<5));

			// Transição de estado se PB2 for pressionado
			if (!(PINB & (1<<2)))
			{
				estado = 1;
			}
		}

		if (estado == 1)
		{
			// Tempo base de contagem
			tempo = 5000;

			// Ativa PB5 e PB4
			PORTB |= (1<<5) | (1<<4);

			estado = 2;
		}

		if (estado == 2)
		{
			// Contagem com atraso de 1 ms
			--tempo;
			_delay_ms(1);

			if (tempo == 0)
			{
				estado = 3;
			}
		}

		if (estado == 3)
		{
			// Desliga PB4 e ativa PB3
			PORTB &= ~(1<<4);
			PORTB |= (1<<3);

			estado = 4;
		}

		if (estado == 4)
		{
			// Retorna ao estado inicial se PB1 for pressionado
			if (!(PINB & (1<<1)))
			{
				estado = 0;
			}
		}

		// Interrupção do processo se PB1 for pressionado durante a contagem
		if ((!(PINB & (1<<1))) && (estado == 2))
		{
			estado = 0;
		}
    }
}