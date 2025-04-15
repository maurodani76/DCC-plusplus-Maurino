// codice test per arduino decoder accessori dcc++
// led bicolore comandato a luce fissa o lampeggiante mediante due indirizzi dcc
// utilizzo della libreria ezLED, pare che sia perfettamente compatibile con nmradcc

#include <NmraDcc.h>
#include <ezLED.h>

#define DCC_PIN 2
// #define ACK_PIN 3

#define DECODER_1ADDR 7       // i due indirizzi utilizzati per la funzione luce fissa o lampeggiante
#define DECODER_2ADDR 8

ezLED led1(9);                // creazione dei due oggetti led per la libreria ezLED
ezLED led2(10);

NmraDcc Dcc;                  // creazione dell'oggetto Dcc per la libreria NmraDcc

void notifyDccAccTurnoutOutput(uint16_t Addr, uint8_t Direction, uint8_t OutputPower) {

  if(Addr == DECODER_1ADDR) {   // gestione del primo indirizzo
    if(Direction == 0) {
      
      led1.cancel();           // disattivazione del primo led e attivazione a luce fissa del secondo
      led2.turnON();
    
    } else {
      
      led2.cancel();           // viceversa...
      led1.turnON();    
    }
  }

  if(Addr == DECODER_2ADDR) {   // gestione del secondo indirizzo
    if(Direction == 0) {
      
      led2.cancel();            // disattivazione dell'eventuale lampeggio o luce fissa del secondo led e attiva lampeggiamento del primo, ciclo di 1000ms
      led1.blink(1000, 1000);   

    } else {

      led1.cancel();            // viceversa
      led2.blink(1000, 1000); 

    }
  }
  
}

void setup() {

  Dcc.pin(digitalPinToInterrupt(DCC_PIN), DCC_PIN, false);
  Dcc.init(MAN_ID_DIY, 1, FLAGS_DCC_ACCESSORY_DECODER | FLAGS_OUTPUT_ADDRESS_MODE, 0);    // inizializzazione dell'oggetto DCC
  Dcc.setCV(CV_ACCESSORY_DECODER_ADDRESS_LSB, DECODER_1ADDR & 0xFF);                      // definizione degli indirizzi ascoltati
  Dcc.setCV(CV_ACCESSORY_DECODER_ADDRESS_MSB, DECODER_1ADDR >> 8);
  Dcc.setCV(CV_ACCESSORY_DECODER_ADDRESS_LSB, DECODER_2ADDR & 0xFF);
  Dcc.setCV(CV_ACCESSORY_DECODER_ADDRESS_MSB, DECODER_2ADDR >> 8);
}

void loop() {

  Dcc.process();      // la funzione che tiene attiva la decodifica del segnale dcc
  led1.loop();        // la funzione che tiene attiva la gestione dei led
  led2.loop();        // ne serve una per ogni led definito
}  