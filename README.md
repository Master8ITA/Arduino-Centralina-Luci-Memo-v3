# Arduino-Centralina-Luci-Memo-v3
Centralina luci per modello Rc con funzione memo dei parametri CH1, CH2, CH3

La centralina luci acquisisce il segnale PWM della ricevente e lo elabora per creare gli effetti.

Effetti disponibili:
1) Tutto spento
2) Effetto reale:
   * Simulazione frecce
   * Simulazione abbaglianti e fuoco marmitta quando si accellera al massimo
   * Simulazione stop quando si frena
   * Simulazione luce retromarcia
   * Simulazione 4 frecce quando si sta fermi per 10 secondi
3) Effetto polizia
   * I led si accendono e spengono in modo casuale
5) Effetto dissolvenza
   * I led si accendono e spengono in modo casuale con un effetto dissolvenza
6) Effetto devil
   * I led si accendono progressivamente con il gas e lo sterzo
  
Premendo il bottone di MEMO si memorizzano i parametri dello sterzo, del gas e del 3 canale (che serve ad impostare i vari effetti).

Premendo il bottone MEMO si accendono le 4 frecce che indica la modalità MEMORIZZAZIONE PARAMETRI (da fare solo una volta o se si cambia ricenvente / trasmittente)
Per memorizzare i parametri seguire questa procedura:
  * accendere la centralina con tutti i collegamenti effettuati
  * premere il bottone MEMO e aspettare che si accendono solo le 4 frecce
  * girare tutto a sinistra
  * girare tutto a destra
  * riportare in posizione centrale lo sterzo
  * accellerare al massimo
  * frenare al massimo
  * riportare in posizione centrale il gas
  * impostare il canale 3 tutto a sinistra
  * impostare il canale 3 tutto a destra
  * riportare il canale 3 in posizione centrale
  * premere il bottone MEMO
A fine procedura la centralina si riavvia e avrà memorizzato tutte le impostazioni (minimo e massimo di ogni canale)

Per scegliere i vari effetti si dovrà comandare il canale 3
