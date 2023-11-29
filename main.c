/*
 * Embutidora_firmware.c
 *
 * Created: 18/08/2022 10:49:35
 * Author : Eplimin.sac
 */ 

#include "Proyect_Defines.h"

uint8_t ADC_lecture = 0;
char ADC_lecture_char[3];
uint32_t counter =  0;
uint8_t counterError = 0;
uint8_t counterErrorMessage = 0; 


eSystemState ePreviousState = Initial_Screen_State;
eSystemState eNextState = Initial_Screen_State;
eSystemEvent eNewEvent;

uint8_t alarmBuzzer = 0; 


ISR (INT0_vect)          //External interrupt_zero ISR
{	
	if((eNextState == Automatic_Mode_Screen_State) || (eNextState == Manual_Mode_Screen_State) || (eNextState == Automatic_Process_State) || (eNextState == Manual_Process_State))
	{
		if ( PIN_ENC_B & (1 << ENC_B)){
			counter++;
			if (counter > 999999){
				counter = 0;
			}
		}
		else{
			if (counter == 0)
			{
				counter = 0;
			}
			else{
				counter--;
			}
		}
	 }
}


ISR (TIMER3_COMPA_vect)    // Timer1 ISR
{
	/*	Turn On Buzzer, discontinued tone */
	if (alarmBuzzer == 1){
		PORT_BUZZ ^= (1 << BUZZ);
		counterError++;
		if (counterError == 3){
			counterErrorMessage++;
			if (counterErrorMessage > 3){
				counterErrorMessage = 0;
			}
		}
		
		if (counterError > 4){
			counterError = 0;
		}

	}
	/* Turn off Buzzer*/
	if (alarmBuzzer == 0){
		PORT_BUZZ &= ~(1 << BUZZ);
	}

	

}



int main(void){
	
	uint16_t value=0;
	uint8_t i = 0;
	
    GPIO_Driver_Initialize();
	//ADC_Driver_Initialize();
	//PWM1_Driver_Initialize();  
	PWM2_Driver_Initialize();
	//Encoder_Driver_Initialize();
	//Interrupt_Initialize();
	//
	//LCD_Init_4_Bits();
//
	//sei();
	//
	//LCD_Tx_Command(LCD_CLEAR);
	//LCD_Tx_Command(LCD_HOME);
	//LCD_Goto_XY(1, 1);
	//LCD_Put_String("     BIENVENIDO     ");
	//LCD_Goto_XY(1, 2);
	//LCD_Put_String(" VEMAG - Embutidora ");
	//
	//_delay_ms(2000);
	//LCD_Tx_Command(LCD_CLEAR);
	//
	//LCD_Goto_XY(1, 1);
	//LCD_Put_String("     EPLIMIN.SAC    ");
	//LCD_Goto_XY(1, 2);
	//LCD_Put_String(" Telefono: 326-2298 ");
	//
	//_delay_ms(2000);
	//LCD_Tx_Command(LCD_CLEAR);
	PWM2_Start();
	
	while (1)
	{	//value = ((float)ADC_Driver_Read(CH_AI1));
		if(TIFR2 & (1<<OCF2B))
		{	
			TIFR2 &= ~(1<<OCF2B);
			if(i<255)
			{
				i++;
			}
			else
			{
				i=0;
			}
			
			PWM2_Update_Duty_Hex(200);	
		}
	}
	
    //while (1) 
    //{	
		//
		//eNewEvent = ReadEvent();
		//switch(eNextState)
		//{
			//case Initial_Screen_State:
			//{
				//InitialScreenState_Actions();
				//InitialScreenState_Transitions();
			//}
			//break;
			//case Automatic_Mode_Screen_State:
			//{
				//AutomaticModeScreen_Actions();
				//AutomaticModeScreen_Transitions();
			//}
			//break;
			//case Manual_Mode_Screen_State:
			//{
				//ManualModeScreen_Actions();
				//ManualModeScreen_Transitions();
				//
			//}
			//break;
			//case Automatic_Process_State:
			//{
				//AutomaticProcessState_Actions();
				//AutomaticProcessState_Transitions();
			//}
			//break;
			//case Manual_Process_State:
			//{
				//ManualProcessState_Actions();
				//ManualProcessState_Transitions();
			//}
			//break;
			//case Reset_Count_State:
			//{
				//ResetCountState_Actions();
				//ResetCountState_Transitions();
			//}
			//break;
			//case Sensors_Alarm_State:
			//{
				//SensorsAlarmState_Actions();
				//SensorsAlarmState_Transitions();
			//}
			//break;
			//default:
			//;
			//break;
		//}
	//}

}



