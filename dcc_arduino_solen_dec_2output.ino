// DCC Decoder for solenoid motors, 1 outputs
// Luca Dentella
//
// Playlist of my tutorials: https://youtube.com/playlist?list=PL45uNmSXju7mn3bMtVVPlFQmpD3mUI5mi


#include <NmraDcc.h>

#define DCC_PIN 2
// #define ACK_PIN 3

#define DECODER_1ADDR 7
#define DECODER_2ADDR 8

#define IMPULSE_DURATION 500
#define PIN_1STRAIGHT  9
#define PIN_1DIVERGING 10
#define PIN_2STRAIGHT  11
#define PIN_2DIVERGING 12

NmraDcc Dcc;

void notifyDccAccTurnoutOutput(uint16_t Addr, uint8_t Direction, uint8_t OutputPower) {

  if(Addr == DECODER_1ADDR) {
    if(Direction == 0) {
      digitalWrite(PIN_1STRAIGHT, LOW);
      delay(IMPULSE_DURATION);
      digitalWrite(PIN_1STRAIGHT, HIGH);
    } else {
      digitalWrite(PIN_1DIVERGING, LOW);
      delay(IMPULSE_DURATION);
      digitalWrite(PIN_1DIVERGING, HIGH);    
    }
  }

  if(Addr == DECODER_2ADDR) {
    if(Direction == 0) {
      digitalWrite(PIN_2STRAIGHT, LOW);
      delay(IMPULSE_DURATION);
      digitalWrite(PIN_2STRAIGHT, HIGH);
    } else {
      digitalWrite(PIN_2DIVERGING, LOW);
      delay(IMPULSE_DURATION);
      digitalWrite(PIN_2DIVERGING, HIGH);    
    }
  }
  // Serial.print("Output moved to position ");
  // Serial.println(Direction);
}

/* void notifyCVAck(void) {

  digitalWrite(ACK_PIN, HIGH);
  delay(8);  
  digitalWrite(ACK_PIN, LOW);
}
*/

void setup() {

  // Serial.begin(9600);
  // pinMode(ACK_PIN, OUTPUT);
  
  digitalWrite(PIN_1STRAIGHT, HIGH);
  pinMode(PIN_1STRAIGHT, OUTPUT);
  digitalWrite(PIN_1DIVERGING, HIGH);
  pinMode(PIN_1DIVERGING, OUTPUT); 

  digitalWrite(PIN_2STRAIGHT, HIGH);
  pinMode(PIN_2STRAIGHT, OUTPUT);
  digitalWrite(PIN_2DIVERGING, HIGH);
  pinMode(PIN_2DIVERGING, OUTPUT); 

  Dcc.pin(digitalPinToInterrupt(DCC_PIN), DCC_PIN, false);
  Dcc.init(MAN_ID_DIY, 1, FLAGS_DCC_ACCESSORY_DECODER | FLAGS_OUTPUT_ADDRESS_MODE, 0);
  Dcc.setCV(CV_ACCESSORY_DECODER_ADDRESS_LSB, DECODER_1ADDR & 0xFF);
  Dcc.setCV(CV_ACCESSORY_DECODER_ADDRESS_MSB, DECODER_1ADDR >> 8);
  Dcc.setCV(CV_ACCESSORY_DECODER_ADDRESS_LSB, DECODER_2ADDR & 0xFF);
  Dcc.setCV(CV_ACCESSORY_DECODER_ADDRESS_MSB, DECODER_2ADDR >> 8);
}

void loop() {

  Dcc.process();
}