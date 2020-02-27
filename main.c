//CPSC 359
//Name: Mohammed rakeeb
//UCID: 30019515



// This program sets up GPIO pin 4 ,17 ,27 as an output pin, which is assumed to
// be connected to an LED on a breadboard. The program then blinks the LED
// on and off in an infinite loop. The program also writes ON and OFF to
// the console terminal as the program runs.

// code used form tut#1 and tut# 5  week 5 and 6 and 7
// and tut 1 and 2 example codes given in D2L
// systimer used from MANZArA supplementary materials
#include "irq.h"
#include "sysreg.h"
#include "uart.h"
#include "gpio.h"

unsigned int sharedValue = 1;


// Function prototypes
// Functions for pins
void init_GPIO4_to_output();
void set_GPIO4();
void clear_GPIO4();

void init_GPIO17_to_output();
void set_GPIO17();
void clear_GPIO17();

void init_GPIO27_to_output();
void set_GPIO27();
void clear_GPIO27();

//Function for interrupts
void init_GPIO23_to_risingEdgeInterrupt();
void init_GPIO22_to_risingEdgeInterrupt();

// function for the systemtimer
void microsecond_delay(unsigned int interval);




////////////////////////////////////////////////////////////////////////////////
//
//  Function:       main
//
//  Arguments:      none
//
//  returns:        void
//
//  Description:    This function initializes GPIO pin 23 to an output pin
//                  without a pull-up or pull-down resistor. It then turns
//                  the output pin on and off (1 and 0) in an infinite loop.
//
////////////////////////////////////////////////////////////////////////////////

void main()
{
  enableIrQ();

  // Set up the UArT serial port
	uart_init();

  // Set up GPIO pin  for output
	init_GPIO4_to_output();
	init_GPIO17_to_output();
	init_GPIO27_to_output();



  // Loop forever, blinking the LED on and off
	while (1) {
    //for 123 pattern
    if( sharedValue == 1){
      //initalises pin 23
      init_GPIO22_to_risingEdgeInterrupt();

      //set up pin 4 for LED1 For on using set and off using clear and delay in on and off using systemtimer for 123 pattern
      set_GPIO4();
      microsecond_delay(500000/2);
      clear_GPIO4();
      microsecond_delay(500000); // 0.5 s delay

      //set up pin 17 for LED1 For on using set and off using clear and delay in on and off using systemtimer for 123 pattern
      set_GPIO17();
      microsecond_delay(500000/2);
      clear_GPIO17();
      microsecond_delay(500000); // 0.5 s delay

      //set up pin 27 for LED1 For on using set and off using clear and delay in on and off using systemtimer for 123 pattern
      set_GPIO27();
      microsecond_delay(500000/2);
      clear_GPIO27();
      microsecond_delay(500000); // 0.5 s delay
    }
    //For 321 pattern
    else{
      //Initalises pin 22
      init_GPIO23_to_risingEdgeInterrupt();

      //set up pin 27 for LED1 For on using set and off using clear and delay in on and off using systemtimer for 321 pattern
      set_GPIO27();
      microsecond_delay(250000/2);
      clear_GPIO27();
      microsecond_delay(250000); // 0.25 s delay

      //set up pin 17 for LED1 For on using set and off using clear and delay in on and off using systemtimer for 321 pattern
      set_GPIO17();
      microsecond_delay(250000/2);
      clear_GPIO17();
      microsecond_delay(250000);  // 0.25 s delay

      //set up pin 4 for LED1 For on using set and off using clear and delay in on and off using systemtimer for 321 pattern
      set_GPIO4();
      microsecond_delay(250000/2);
      clear_GPIO4();
      microsecond_delay(250000);  // 0.25 s delay
    }
  }
}

void init_GPIO23_to_risingEdgeInterrupt()
{
  register unsigned int r;


    // Get the current contents of the GPIO Function Select register 1
  r = *GPFSEL2;

    // Clear bits 21 - 23. This is the field FSEL17, which maps to GPIO pin 17.
    // We clear the bits by ANDing with a 000 bit pattern in the field. This
    // sets the pin to be an input pin
  r &= ~(0x7 << 9);

    // Write the modified bit pattern back to the
    // GPIO Function Select register 1
  *GPFSEL2 = r;

    // Disable the pull-up/pull-down control line for GPIO pin 17. We follow the
    // procedure outlined on page 101 of the BCM2837 ArM Peripherals manual. We
    // will pull down the pin using an external resistor connected to ground.

    // Disable internal pull-up/pull-down by setting bits 0:1
    // to 00 in the GPIO Pull-Up/Down register
  *GPPUD = 0x0;

    // Wait 150 cycles to provide the required set-up time
    // for the control signal
  r = 150;
  while (r--) {
      asm volatile("nop");
  }

    // Write to the GPIO Pull-Up/Down Clock register 0, using a 1 on bit 17 to
    // clock in the control signal for GPIO pin 17. Note that all other pins
    // will retain their previous state.
  *GPPUDCLK0 = (0x1 << 23);

    // Wait 150 cycles to provide the required hold time
    // for the control signal
  r = 150;
  while (r--) {
      asm volatile("nop");
  }

    // Clear all bits in the GPIO Pull-Up/Down Clock register 0
    // in order to remove the clock
  *GPPUDCLK0 = 0;

    // Set pin 17 to so that it generates an interrupt on a rising edge.
    // We do so by setting bit 17 in the GPIO rising Edge Detect Enable
    // register 0 to a 1 value (p. 97 in the Broadcom manual).
  *GPrEN0 = (0x1 << 23);

    // Enable the GPIO IrQS for ALL the GPIO pins by setting IrQ 52
    // GPIO_int[3] in the Interrupt Enable register 2 to a 1 value.
    // See p. 117 in the Broadcom Peripherals Manual.
  *IrQ_ENABLE_IrQS_2 = (0x1 << 20);
}


void init_GPIO22_to_risingEdgeInterrupt()
{
  register unsigned int r;


    // Get the current contents of the GPIO Function Select register 1
  r = *GPFSEL2;

    // Clear bits 21 - 23. This is the field FSEL17, which maps to GPIO pin 17.
    // We clear the bits by ANDing with a 000 bit pattern in the field. This
    // sets the pin to be an input pin
  r &= ~(0x7 << 6);

    // Write the modified bit pattern back to the
    // GPIO Function Select register 1
  *GPFSEL2 = r;

    // Disable the pull-up/pull-down control line for GPIO pin 17. We follow the
    // procedure outlined on page 101 of the BCM2837 ArM Peripherals manual. We
    // will pull down the pin using an external resistor connected to ground.

    // Disable internal pull-up/pull-down by setting bits 0:1
    // to 00 in the GPIO Pull-Up/Down register
  *GPPUD = 0x0;

    // Wait 150 cycles to provide the required set-up time
    // for the control signal
  r = 150;
  while (r--) {
      asm volatile("nop");
  }

    // Write to the GPIO Pull-Up/Down Clock register 0, using a 1 on bit 17 to
    // clock in the control signal for GPIO pin 17. Note that all other pins
    // will retain their previous state.
  *GPPUDCLK0 = (0x1 << 22);

    // Wait 150 cycles to provide the required hold time
    // for the control signal
  r = 150;
  while (r--) {
      asm volatile("nop");
  }

    // Clear all bits in the GPIO Pull-Up/Down Clock register 0
    // in order to remove the clock
  *GPPUDCLK0 = 0;

    // Set pin 17 to so that it generates an interrupt on a rising edge.
    // We do so by setting bit 17 in the GPIO rising Edge Detect Enable
    // register 0 to a 1 value (p. 97 in the Broadcom manual).
  *GPrEN0 = (0x1 << 22);

    // Enable the GPIO IrQS for ALL the GPIO pins by setting IrQ 52
    // GPIO_int[3] in the Interrupt Enable register 2 to a 1 value.
    // See p. 117 in the Broadcom Peripherals Manual.
  *IrQ_ENABLE_IrQS_2 = (0x1 << 20);
}




////////////////////////////////////////////////////////////////////////////////
//
//  Function:       init_GPIO23_to_output
//
//  Arguments:      none
//
//  returns:        void
//
//  Description:    This function sets GPIO pin 23 to an output pin without
//                  any pull-up or pull-down resistors.
//
////////////////////////////////////////////////////////////////////////////////

void init_GPIO4_to_output()
{
  register unsigned int r;


    // Get the current contents of the GPIO Function Select register 2
	r = *GPFSEL0;

    // Clear bits 9 - 11. This is the field FSEL23, which maps to GPIO pin 23.
    // We clear the bits by ANDing with a 000 bit pattern in the field.
  r &= ~(0x7 << 4*3);

    // Set the field FSEL23 to 001, which sets pin 23 to an output pin.
    // We do so by Oring the bit pattern 001 into the field.
  r |= (0x1 << 4*3);

    // Write the modified bit pattern back to the
    // GPIO Function Select register 2
  *GPFSEL0 = r;

    // Disable the pull-up/pull-down control line for GPIO pin 23. We follow the
    // procedure outlined on page 101 of the BCM2837 ARM Peripherals manual. The
    // internal pull-up and pull-down resistor isn't needed for an output pin.

    // Disable pull-up/pull-down by setting bits 0:1
    // to 00 in the GPIO Pull-Up/Down Register
  *GPPUD = 0x0;

    // Wait 150 cycles to provide the required set-up time
    // for the control signal
  r = 150;
  while (r--) {
    asm volatile("nop");
  }

    // Write to the GPIO Pull-Up/Down Clock Register 0, using a 1 on bit 23 to
    // clock in the control signal for GPIO pin 23. Note that all other pins
    // will retain their previous state.
  *GPPUDCLK0 = (0x1 << 4);

    // Wait 150 cycles to provide the required hold time
    // for the control signal
  r = 150;
  while (r--) {
    asm volatile("nop");
  }

    // Clear all bits in the GPIO Pull-Up/Down Clock Register 0
    // in order to remove the clock
  *GPPUDCLK0 = 0;
}


void init_GPIO17_to_output()
{
	register unsigned int r;


    // Get the current contents of the GPIO Function Select Register 2
  r = *GPFSEL1;

    // Clear bits 9 - 11. This is the field FSEL23, which maps to GPIO pin 23.
    // We clear the bits by ANDing with a 000 bit pattern in the field.
  r &= ~(0x7 << (17%10)*3);

    // Set the field FSEL23 to 001, which sets pin 23 to an output pin.
    // We do so by ORing the bit pattern 001 into the field.
  r |= (0x1 << (17%10)*3);

    // Write the modified bit pattern back to the
    // GPIO Function Select Register 2
  *GPFSEL1 = r;

    // Disable the pull-up/pull-down control line for GPIO pin 23. We follow the
    // procedure outlined on page 101 of the BCM2837 ARM Peripherals manual. The
    // internal pull-up and pull-down resistor isn't needed for an output pin.

    // Disable pull-up/pull-down by setting bits 0:1
    // to 00 in the GPIO Pull-Up/Down Register
	*GPPUD = 0x0;

    // Wait 150 cycles to provide the required set-up time
    // for the control signal
  r = 150;
  while (r--) {
    asm volatile("nop");
  }

    // Write to the GPIO Pull-Up/Down Clock Register 0, using a 1 on bit 23 to
    // clock in the control signal for GPIO pin 23. Note that all other pins
    // will retain their previous state.
  *GPPUDCLK0 = (0x1 << 17);

    // Wait 150 cycles to provide the required hold time
    // for the control signal
  r = 150;
  while (r--) {
  	asm volatile("nop");
  }

    // Clear all bits in the GPIO Pull-Up/Down Clock Register 0
    // in order to remove the clock
  *GPPUDCLK0 = 0;
}


void init_GPIO27_to_output()
{
	register unsigned int r;


    // Get the current contents of the GPIO Function Select Register 2
  r = *GPFSEL2;

    // Clear bits 21 - 24. This is the field FSEL23, which maps to GPIO pin 27.
    // We clear the bits by ANDing with a 000 bit pattern in the field.
  r &= ~(0x7 << (27%10)*3);

    // Set the field FSEL23 to 001, which sets pin 27 to an output pin.
    // We do so by ORing the bit pattern 001 into the field.
  r |= (0x1 << (27%10)*3);

    // Write the modified bit pattern back to the
    // GPIO Function Select Register 2
  *GPFSEL2 = r;

    // Disable the pull-up/pull-down control line for GPIO pin 23. We follow the
    // procedure outlined on page 101 of the BCM2837 ARM Peripherals manual. The
    // internal pull-up and pull-down resistor isn't needed for an output pin.

    // Disable pull-up/pull-down by setting bits 0:1
    // to 00 in the GPIO Pull-Up/Down Register
  *GPPUD = 0x0;

    // Wait 150 cycles to provide the required set-up time
    // for the control signal
  r = 150;
  while (r--) {
    asm volatile("nop");
  }

    // Write to the GPIO Pull-Up/Down Clock Register 0, using a 1 on bit 23 to
    // clock in the control signal for GPIO pin 23. Note that all other pins
    // will retain their previous state.
  *GPPUDCLK0 = (0x1 << 27);

    // Wait 150 cycles to provide the required hold time
    // for the control signal
  r = 150;
  while (r--) {
    asm volatile("nop");
  }

    // Clear all bits in the GPIO Pull-Up/Down Clock Register 0
    // in order to remove the clock
  *GPPUDCLK0 = 0;
}



////////////////////////////////////////////////////////////////////////////////
//
//  Function:       set_GPIO23
//
//  Arguments:      none
//
//  Returns:        void
//
//  Description:    This function sets the GPIO output pin 23
//                  to a 1 (high) level.
//
////////////////////////////////////////////////////////////////////////////////

void set_GPIO4()
{
  register unsigned int r;

	  // Put a 1 into the SET23 field of the GPIO Pin Output Set Register 0
	r = (0x1 << 4);
	*GPSET0 = r;
}

void set_GPIO17()
{
	register unsigned int r;

	  // Put a 1 into the SET23 field of the GPIO Pin Output Set Register 0
	r = (0x1 << 17);
	*GPSET0 = r;
}

void set_GPIO27()
{
	register unsigned int r;

	  // Put a 1 into the SET23 field of the GPIO Pin Output Set Register 0
	r = (0x1 << 27);
	*GPSET0 = r;
}


////////////////////////////////////////////////////////////////////////////////
//
//  Function:       clear_GPIO23
//
//  Arguments:      none
//
//  Returns:        void
//
//  Description:    This function clears the GPIO output pin 23
//                  to a 0 (low) level.
//
////////////////////////////////////////////////////////////////////////////////

void clear_GPIO4()
{
	register unsigned int r;

	  // Put a 1 into the CLR23 field of the GPIO Pin Output Clear Register 0
	r = (0x1 << 4);
	*GPCLR0 = r;
}


void clear_GPIO17()
{
	register unsigned int r;

	  // Put a 1 into the CLR23 field of the GPIO Pin Output Clear Register 0
	r = (0x1 << 17);
	*GPCLR0 = r;
}

void clear_GPIO27()
{
	register unsigned int r;

	  // Put a 1 into the CLR23 field of the GPIO Pin Output Clear Register 0
	r = (0x1 << 27);
	*GPCLR0 = r;
}
