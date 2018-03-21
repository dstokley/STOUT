#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>



char Read_Temperature(void)
{
char get[10];
char temp_lsb,temp_msb;
int k;
char temp_f,temp_c;
ow_reset();
write_byte(0xCC); //Skip ROM
write_byte(0x44); // Start Conversion
delay(5);
ow_reset();
write_byte(0xCC); // Skip ROM
write_byte(0xBE); // Read Scratch Pad
for (k=0;k<9;k++){get[k]=read_byte();}
printf("\n ScratchPAD DATA = %X%X%X%X%X\n",get[8],get[7],get[6],get[5],get[4],get[3],get[2],get[1],get[0]);
temp_msb = get[1]; // Sign byte + lsbit
temp_lsb = get[0]; // Temp data plus lsb
if (temp_msb <= 0x80){temp_lsb = (temp_lsb/2);} // shift to get whole degree
temp_msb = temp_msb & 0x80; // mask all but the sign bit
if (temp_msb >= 0x80) {temp_lsb = (~temp_lsb)+1;} // twos complement
if (temp_msb >= 0x80) {temp_lsb = (temp_lsb/2);}// shift to get whole degree
if (temp_msb >= 0x80) {temp_lsb = ((-1)*temp_lsb);} // add sign bit
printf( "\nTempC= %d degrees C\n", (int)temp_lsb ); // print temp. C
temp_c = temp_lsb; // ready for conversion to Fahrenheit
temp_f = (((int)temp_c)* 9)/5 + 32;
printf( "\nTempF= %d degrees F\n", (int)temp_f ); // print temp. F
return temp_c;
}
