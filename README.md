# DCC++

codice pescato dal sito di Luca Dentella (grazie Luca!) e adattato per mie esigenze

- il codice per 2 solenoidi include già gli indirizzi giusti per il plastico (7 e 8) e 500ms di attivazione per ogni uscita
- il codice per 2 solenoidi è scritto per comandare una scheda relè classica con optoisolatori e attivazioni a massa (ACTIVE LOW); quindi pin HIGH appena prima della definizione pinmode OUTPUT... funziona: nessuna attivazione non voluta dei relè all'accensione o reset di arduino
- da includere libreria nmradcc (si trova nella lista libreria di Arduino IDE)
- da includere libreria ezLED (sempre in lista libreria...) per il codice "signal"

il codice dcc-signal è un codice di test per gestire segnali a una o più vele e contemporaneamente diverse funzioni per ogni vela (ad esempio il lampeggio); ho assegnato un indirizzo per le vele a luce fissa e un altro indirizzo per le vele a luci lampeggianti. Praticamente si può fare tutto: un indirizzo può gestire 2 stati e basta decidere cosa far fare ad arduino per ogni stato; accendere o spegnere uno o più led, farli lampeggiare, attivare un'uscita ad un driver motore, un servo, ecc....
per scelta NON ho implementato la gestione delle CV per non complicare inutilmente il codice - credo che i decoder che farò saranno ad indirizzi e funzioni fisse già predisposte; dovessi cambiare qualcosa attacco il pc ad arduino e semplicemente lo riprogrammo al volo.

schema per il collegamento ad arduino del segnale DCC (usare resistore da 1kohm almeno 1/2 watt):
https://arduino.stackexchange.com/questions/19686/optocouplers-for-arduino-dcc-decoder-explain

-------------------
> [!NOTE]
> nella scheda prototipo che ho fatto e che finirà sotto al mio plastico NON ho previsto nulla che impedisca al 5v di arduino ALIMENTATO CON USB di finire sull'uscita del regolatore 7805: inserirò un diodo di protezione (1n4001) all'ingresso INPUT del regolatore per proteggere anche dalla corrente di scarica di ritorno dei condensatori
> - thread esaustivo: https://forum.arduino.cc/t/using-diodes-in-lm7805-design-circuits/921152/9
