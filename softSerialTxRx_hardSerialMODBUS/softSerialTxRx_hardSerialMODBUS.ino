#include <SoftwareSerial.h>
#include <SimpleModbusSlave.h>

//Number of MODBUS HOLDING REGISTERS
#define   HOLDING_REGS_SIZE           3         
// RX = Pin No.10, TX = Pin No.11 on ArduinoUno
//SoftwareSerial mySerial(10, 11); 
// RX = Pin No.6, TX = Pin No.7 on ArduinoUno
SoftwareSerial mySerial(6, 7);                
// function 3 and 16 register array
unsigned int holdingRegs[HOLDING_REGS_SIZE];    

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  /* parameters(HardwareSerial* SerialPort,
                long baudrate, 
    unsigned char byteFormat,
                unsigned char ID, 
                unsigned char transmit enable pin, 
                unsigned int holding registers size,
                unsigned int* holding register array)
  */
  
  /* Valid modbus byte formats are:
     SERIAL_8N2: 1 start bit, 8 data bits, 2 stop bits
     SERIAL_8E1: 1 start bit, 8 data bits, 1 Even parity bit, 1 stop bit
     SERIAL_8O1: 1 start bit, 8 data bits, 1 Odd parity bit, 1 stop bit
     
     You can obviously use SERIAL_8N1 but this does not adhere to the
     Modbus specifications. That said, I have tested the SERIAL_8N1 option 
     on various commercial masters and slaves that were suppose to adhere
     to this specification and was always able to communicate... Go figure.
     
     These byte formats are already defined in the Arduino global name space. 
  */
  modbus_configure(&Serial, 9600, SERIAL_8N2, 1, 2, HOLDING_REGS_SIZE, holdingRegs);
  /* modbus_update_comms(baud, byteFormat, id) is not needed but allows for easy update of the
   port variables and slave id dynamically in any function.
  */
  modbus_update_comms(9600, SERIAL_8N2, 1);

  mySerial.begin(9600);
}

void loop() { // run over and over
  if (mySerial.available()) {
  holdingRegs[0] = mySerial.read();
  delay(1000); 
  Serial.println(holdingRegs[0]); 

  holdingRegs[1] = mySerial.read();
  delay(1000); 
  Serial.println(holdingRegs[1]); 
  }

  /* modbus_update() is the only method used in loop(). It returns the total error
   count since the slave started. You don't have to use it but it's useful
   for fault finding by the modbus master.
  */
  modbus_update();

  }

