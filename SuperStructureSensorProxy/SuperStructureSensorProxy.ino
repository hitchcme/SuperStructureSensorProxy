

// Port E, pins 2 & 3 Encoder Pins
// Port K, pins A8 & A9 Tie Down Sensor pins

const byte ENCFWD_I_PIN = 3;
const byte ENCREV_I_PIN = 2;
const byte TDS_P_I_PIN = A8;
const byte TDS_S_I_PIN = A9;

//Outputs
const byte ENCFWD_O_PIN = A1;
const byte ENCREV_O_PIN = A0;
const byte TDS_P_O_PIN = A2;
const byte TDS_S_O_PIN = A3;

int ENCFWD_STAT = 0;
int ENCREV_STAT = 0;
int TDS_P_STAT = 0;
int TDS_S_STAT = 0;
int ENC_POS = 0;
int ENC_POS_old = ENC_POS;
int TD_POS = 0;
int PORT_TD_POS = 0;
int STBD_TD_POS = 0;
//int COMBINED_POS = 0;
int DTD_POS = 0;
int DTD_POS_old = DTD_POS;
int FWD = 0;
int UPDATE = 1;
int COMBINED_POS_old = 0;
int OLD_VALS[5] = {0,0,0,0,0};
long int OVSCT[5] = {0,0,0,0,0};
long int SCT = 0;
long int SCT_old = SCT;


#define COMBINED_POS  (TD_POS*4)+ENC_POS
//#define ENC_POS       (PINE & ~0B1 & ~0B10 & ~0B100 & ~0B1000) / 16
//#define TD_POS        PINK & ~0B11111100
//#define DTD_POS       ~TD_POS & 0B11


void setup() {
  // put your setup code here, to run once:
  cli();
  pinMode(ENCFWD_I_PIN, INPUT_PULLUP);
  pinMode(ENCREV_I_PIN, INPUT_PULLUP);
  pinMode(TDS_P_I_PIN, INPUT_PULLUP);
  pinMode(TDS_S_I_PIN, INPUT_PULLUP);
  
  pinMode(ENCFWD_O_PIN, OUTPUT);
  pinMode(ENCREV_O_PIN, OUTPUT);
  pinMode(TDS_P_O_PIN, OUTPUT);
  pinMode(TDS_S_O_PIN, OUTPUT);

  
  attachInterrupt(digitalPinToInterrupt(ENCFWD_I_PIN), fwdpintrig, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENCREV_I_PIN), revpintrig, CHANGE);

  Serial.begin(230400);
  SCT = micros();
  sei();
}

void loop() {
  ENC_POS = (PINE & ~0B1 & ~0B10 & ~0B100 & ~0B1000) / 16;    
  TD_POS = PINK & ~0B11111100;
  //DTD_POS = ~TD_POS & 0B11;
  //COMBINED_POS = (TD_POS * 4) + ENC_POS;
  PORTF = COMBINED_POS & ~0B11110000;
  if (UPDATE < 100) {
      return_data();
      UPDATE++;
  }
  //delayMicroseconds(10);
  
}



void fwdpintrig() {
    cli();
    UPDATE = 0;
    COMBINED_POS_old = COMBINED_POS;
    SCT_old = SCT;
    ENC_POS = (PINE & ~0B1 & ~0B10 & ~0B100 & ~0B1000) / 16;    
    TD_POS = PINK & ~0B11111100;
    //DTD_POS = ~TD_POS & 0B11;
    //COMBINED_POS = (TD_POS * 4) + ENC_POS;
    PORTF = COMBINED_POS & ~0B11110000;
    SCT = micros();
    //return_data();
    //dp_Shiftnprint();
    //Serial.print('\n');
    //Serial.print(COMBINED_POS_old,BIN);
    //Serial.print('\n');
    //Serial.print(0B10000 + COMBINED_POS,BIN);
    //Serial.print('\n');
//    Serial.print(OLD_VALS);
//    Serial.print(OVSCT);
    //COMBINED_POS_old = COMBINED_POS + 0B10000;
    sei();
}

void revpintrig() {
    cli();
    UPDATE = 0;
    COMBINED_POS_old = COMBINED_POS;
    SCT_old = SCT;
    ENC_POS = (PINE & ~0B1 & ~0B10 & ~0B100 & ~0B1000) / 16;    
    TD_POS = PINK & ~0B11111100;
    //DTD_POS = ~TD_POS & 0B11;
    //COMBINED_POS = (TD_POS * 4) + ENC_POS;
    PORTF = COMBINED_POS & ~0B11110000;
    SCT = micros();
    //return_data();
    //dp_Shiftnprint();
    //Serial.print('\n');
    //Serial.print(COMBINED_POS_old,BIN);
    //Serial.print('\n');
    //Serial.print(0B10000 + COMBINED_POS,BIN);
    //Serial.print('\n');
//    Serial.print(OLD_VALS);
//    Serial.print(OVSCT);
    //COMBINED_POS_old = COMBINED_POS + 0B10000;
    sei();
}

void return_data() {
    Serial.print('\n');
    Serial.print(COMBINED_POS+16,HEX);
    Serial.print(",");
    Serial.print(SCT,HEX);
    Serial.print('\n');
    Serial.print(COMBINED_POS_old+16,HEX);
    Serial.print(",");
    Serial.print(SCT_old,HEX);
}

void dp_Shiftnprint() {
  Serial.print('\n');
  for ( int i = 0; i < 5; i++ ) {
      OLD_VALS[i] = OLD_VALS[i+1];
      OVSCT[i] = OVSCT[i+1];
      Serial.print("(P");
      Serial.print(OLD_VALS[i],HEX);
      Serial.print(",T");
      Serial.print(OVSCT[i],HEX);
      Serial.print("),");
  }
  OLD_VALS[5] = 0B10000 + COMBINED_POS;
  OVSCT[5] = micros();
  Serial.print("(P");
  Serial.print(OLD_VALS[5],HEX);
  Serial.print(",T");
  Serial.print(OVSCT[5],HEX);
  Serial.print("),");
}


