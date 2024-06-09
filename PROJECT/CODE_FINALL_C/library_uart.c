#include <string.h>

#define BUFFER_SIZE 16

char receivedString[BUFFER_SIZE]="";
volatile unsigned int index = 0;
volatile int stringComplete = 0;
volatile unsigned int indexComplete = 0;

#int_rda
void read_uart(){
   if(kbhit()){
//!   Read the received character
      char receivedChar = getch();  
       
       if (receivedChar == '\r' || receivedChar == '\n') {
//!        End of string (carriage return detected)
           receivedString[index] = '\0';  // Null-terminate the string
           indexComplete = index;
           stringComplete = 1;  // Set the flag to indicate string reception complete
       } else {
          // Store the received character
           if (index < BUFFER_SIZE - 1) {
               receivedString[index++] = receivedChar;
           } else {
               // Handle buffer overflow
               index = BUFFER_SIZE - 1;  // Prevent overflow
           }
       }
   }
}
