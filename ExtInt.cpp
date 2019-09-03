
#include "ExtInt.h"

void ExtInt_Initialize(){

  LPC_SC->EXTINT      =  (1<<SBIT_EINT1);	    // Clear Pending interrupts 
  LPC_PINCON->PINSEL4 =  (1<<PINSEL_EINT1);  	// Configure P2_10,P2_11 as EINT0/1 
  LPC_SC->EXTMODE     =  (1<<SBIT_EXTMODE1);  	// Configure EINTx as Edge Triggered
  LPC_SC->EXTPOLAR    =  (1<<SBIT_EXTPOLAR1);	// Configure EINTx as Falling Edge 
	
  NVIC_EnableIRQ(EINT1_IRQn); 

}

void EINT1_IRQHandler(void){
    //LPC_SC->EXTINT = (1<<SBIT_EINT1);  /* Clear Interrupt timerflag */
		GPIO_PinWrite(1,23,1);
}

