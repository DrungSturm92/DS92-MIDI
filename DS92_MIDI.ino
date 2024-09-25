#include <MIDI.h>
#include "Controller.h"
#include <LiquidCrystal.h>		// importa libreria para lcd

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);	// pines RS, E, D4, D5, D6, D7 de modulo 1602A

/*************************************************************
  MIDI CONTROLLER

  by Notes and Volts
  www.notesandvolts.com

  Version 1.2 **Arduino UNO ONLY!**
 *************************************************************/

MIDI_CREATE_DEFAULT_INSTANCE();

//************************************************************
//***SET THE NUMBER OF CONTROLS USED**************************
//************************************************************
//---How many buttons are connected directly to pins?---------
byte NUMBER_BUTTONS = 3;
//---How many potentiometers are connected directly to pins?--
byte NUMBER_POTS = 5;
//---How many buttons are connected to a multiplexer?---------
byte NUMBER_MUX_BUTTONS = 0;
//---How many potentiometers are connected to a multiplexer?--
byte NUMBER_MUX_POTS = 0;
//************************************************************

//***ANY MULTIPLEXERS? (74HC4067)************************************
//MUX address pins must be connected to Arduino UNO pins 2,3,4,5
//A0 = PIN2, A1 = PIN3, A2 = PIN4, A3 = PIN5
//*******************************************************************
//Mux NAME (OUTPUT PIN, , How Many Mux Pins?(8 or 16) , Is It Analog?);


//Mux M1(10, 16, false); //Digital multiplexer on Arduino pin 10
//Mux M2(A5, 8, true); //Analog multiplexer on Arduino analog pin A0
//*******************************************************************


//***DEFINE DIRECTLY CONNECTED POTENTIOMETERS************************
//Pot (Pin Number, Command, CC Control, Channel Number)
//**Command parameter is for future use**

Pot PO1(A0, 0, 11, 1);
Pot PO2(A1, 0, 12, 1);
Pot PO3(A2, 0, 13, 1);
Pot PO4(A3, 0, 14, 1);
Pot PO5(A4, 0, 15, 1);
//Pot PO6(A5, 0, 31, 1);
//*******************************************************************
//Add pots used to array below like this->  Pot *POTS[] {&PO1, &PO2, &PO3, &PO4, &PO5, &PO6};
Pot *POTS[]{&PO1, &PO2, &PO3, &PO4, &PO5};
//*******************************************************************


//***DEFINE DIRECTLY CONNECTED BUTTONS*******************************
//Button (Pin Number, Command, Note Number, Channel, Debounce Time)
//** Command parameter 0=NOTE  1=CC  2=Toggle CC **

Button BU1(9, 2, 36, 1, 5);
Button BU2(10, 0, 38, 1, 5);
Button BU3(11, 0, 42, 1, 5);
// Button BU4(5, 0, 46, 10, 5);
// Button BU5(6, 0, 39, 10, 5);
// Button BU6(7, 0, 41, 10, 5);
// Button BU7(8, 0, 43, 10, 5);
// Button BU8(9, 0, 45, 10, 5);
// Button BU9(10, 0, 49, 10, 5);
// Button BU10(11, 0, 51, 10, 5);
// Button BU11(12, 0, 52, 10, 5);
// Button BU12(13, 0, 54, 10, 5);
//*******************************************************************
//Add buttons used to array below like this->  Button *BUTTONS[] {&BU1, &BU2, &BU3, &BU4, &BU5, &BU6, &BU7, &BU8};
Button *BUTTONS[]{ &BU1, &BU2, &BU3}; // &BU4, &BU5, &BU6, &BU7, &BU8, &BU9, &BU10, &BU11, &BU12 };
//*******************************************************************


//***DEFINE BUTTONS CONNECTED TO MULTIPLEXER*************************
//Button::Button(Mux mux, byte muxpin, byte command, byte value, byte channel, byte debounce)
//** Command parameter 0=NOTE  1=CC  2=Toggle CC **

//Button MBU1(M1, 0, 0, 70, 1, 5);
//Button MBU2(M1, 1, 1, 71, 1, 5);
//Button MBU3(M1, 2, 2, 72, 1, 5);
//Button MBU4(M1, 3, 0, 73, 1, 5);
//Button MBU5(M1, 4, 0, 74, 1, 5);
//Button MBU6(M1, 5, 0, 75, 1, 5);
//Button MBU7(M1, 6, 0, 76, 1, 5);
//Button MBU8(M1, 7, 0, 77, 1, 5);
//Button MBU9(M1, 8, 0, 78, 1, 5);
//Button MBU10(M1, 9, 0, 79, 1, 5);
//Button MBU11(M1, 10, 0, 80, 1, 5);
//Button MBU12(M1, 11, 0, 81, 1, 5);
//Button MBU13(M1, 12, 0, 82, 1, 5);
//Button MBU14(M1, 13, 0, 83, 1, 5);
//Button MBU15(M1, 14, 0, 84, 1, 5);
//Button MBU16(M1, 15, 0, 85, 1, 5);
//*******************************************************************
////Add multiplexed buttons used to array below like this->  Button *MUXBUTTONS[] {&MBU1, &MBU2, &MBU3, &MBU4, &MBU5, &MBU6.....};
Button *MUXBUTTONS[]{};

//*******************************************************************


//***DEFINE POTENTIOMETERS CONNECTED TO MULTIPLEXER*******************
//Pot::Pot(Mux mux, byte muxpin, byte command, byte control, byte channel)
//**Command parameter is for future use**

//Pot MPO1(M2, 0, 0, 1, 1);
//Pot MPO2(M2, 1, 0, 7, 1);
//Pot MPO3(M2, 2, 0, 50, 1);
//Pot MPO4(M2, 3, 0, 55, 2);
//Pot MPO5(M2, 4, 0, 50, 1);
//Pot MPO6(M2, 5, 0, 55, 2);
//Pot MPO7(M2, 6, 0, 50, 1);
//Pot MPO8(M2, 7, 0, 55, 2);
//Pot MPO9(M2, 8, 0, 50, 1);
//Pot MPO10(M2, 9, 0, 55, 2);
//Pot MPO11(M2, 10, 0, 50, 1);
//Pot MPO12(M2, 11, 0, 55, 2);
//Pot MPO13(M2, 12, 0, 50, 1);
//Pot MPO14(M2, 13, 0, 55, 2);
//Pot MPO15(M2, 14, 0, 50, 1);
//Pot MPO16(M2, 15, 0, 55, 2);
//*******************************************************************
//Add multiplexed pots used to array below like this->  Pot *MUXPOTS[] {&MPO1, &MPO2, &MPO3, &MPO4, &MPO5, &MPO6.....};
Pot *MUXPOTS[]{};
//*******************************************************************

//Init LCD variables
int lcd_time = 0;
char lcd_message1[17];
char lcd_message2[17];
// int lcd_CHN;
// int lcd_VAL;


void setup() {

  //MIDI
  MIDI.begin(MIDI_CHANNEL_OFF);
  Serial.begin(115200);

  //LCD
  lcd.begin(16, 2);			// inicializa a display de 16 columnas y 2 lineas
}

void loop() {
  int time = millis()/1000;		// seconds.

  //LCD
  if (time < 4) {			// Mensaje de bienvenida
   lcd.setCursor(6, 0);			// ubica cursor en columna 6, linea 0
   lcd.print("DS92");			
   lcd.setCursor(0, 1);			// ubica cursor en columna 0, linea 1
   lcd.print("PROPATO - T.MIDI");	// escribe el texto en pantalla 
  } else if (time == 4){
    lcd.clear();
  } else if (time > lcd_time + 2) {	// 
    lcd.setCursor(0, 0);
    //lcd.print("Han pasado");	// escribe el texto en pantalla
    snprintf(lcd_message1, 17, "%-17s", "Han pasado"); // lcd_message1 = han pasado pero rellena con espacios en blanco a la derecha.
    lcd.print(lcd_message1);
    lcd.setCursor(0, 1);			// ubica cursor en columna 0, linea 1
    snprintf(lcd_message2, 17, "%i %-17s",time, "seg."); //  lcd_message2 = time seg. pero rellena con espacios en blanco a la derecha. 
    lcd.print(lcd_message2);		
    //lcd.print(" seg.");			// imprime a continuacion segundos
  }

  //MIDI
  if (NUMBER_BUTTONS != 0) updateButtons();
  if (NUMBER_POTS != 0) updatePots();
  if (NUMBER_MUX_BUTTONS != 0) updateMuxButtons();
  if (NUMBER_MUX_POTS != 0) updateMuxPots();


/*  
  for (int i = 0; i < NUMBER_POTS; i = i + 1) {
   if (POTS[i]->getValue() != 255) {
     byte lcd_message = POTS[i]->getValue();
     lcd.clear();
     lcd.setCursor(0, 0);
     lcd.print("POT:");
     lcd.print(i + 1); // escribe el número de pote
     lcd.print("--CHN:");
     lcd.print(POTS[i]->Pchannel);
     lcd.setCursor(0, 1);
     lcd.print("CTRL:");
     lcd.print(POTS[i]->Pcontrol);
     lcd.print("--VAL:");
     lcd.print(lcd_message);	// escribe la variable en pantalla
     }
  }
*/  
}

void updateLCD() { //(int i, int lcd_CHN, int lcd_VAL) {
          lcd_time = millis()/1000;	//tiempo en que se envía un mensaje MIDI
          //snprintf(lcd_message1, 17, "CHN:%2i  VAL:%3i", lcd_CHN, lcd_VAL);
          //lcd.print(BUTTONS[i]->Bchannel);
          //lcd.setCursor(0, 1);
          //lcd.print(BUTTONS[i]->Bvalue);
	  if (lcd_time > 4) {	// sólo imprime pasados los 4 segundos del mensaje de bienvenida.
            //lcd.clear();
            lcd.setCursor(0,0);
            lcd.print(lcd_message1);
            lcd.setCursor(0,1);
            lcd.print(lcd_message2);
          }
}
//*****************************************************************
void updateButtons() {

  // Cycle through Button array
  for (int i = 0; i < NUMBER_BUTTONS; i = i + 1) {
    byte message = BUTTONS[i]->getValue();

    //  Button is pressed
    if (message == 0) {
      switch (BUTTONS[i]->Bcommand) {
        case 0:  //Note
          MIDI.sendNoteOn(BUTTONS[i]->Bvalue, 127, BUTTONS[i]->Bchannel);
          snprintf(lcd_message1, 17, "%-17s", "Note On");
          snprintf(lcd_message2, 17, "CHN:%2i  VAL:%3i", BUTTONS[i]->Bchannel, BUTTONS[i]->Bvalue);       
          updateLCD();
          break;
        case 1:  //CC
          MIDI.sendControlChange(BUTTONS[i]->Bvalue, 127, BUTTONS[i]->Bchannel);
          snprintf(lcd_message1, 17, "%-17s", "Ctrl. Change On");
          snprintf(lcd_message2, 17, "CHN:%2i  VAL:%3i", BUTTONS[i]->Bchannel, BUTTONS[i]->Bvalue);       
          updateLCD();
          break;
        case 2:  //Toggle
          if (BUTTONS[i]->Btoggle == 0) {
            MIDI.sendControlChange(BUTTONS[i]->Bvalue, 127, BUTTONS[i]->Bchannel);
            snprintf(lcd_message1, 17, "%-17s", "Ctrl. Change On");
            snprintf(lcd_message2, 17, "CHN:%2i  VAL:%3i", BUTTONS[i]->Bchannel, BUTTONS[i]->Bvalue);       
            updateLCD();
            BUTTONS[i]->Btoggle = 1;
          } else if (BUTTONS[i]->Btoggle == 1) {
            MIDI.sendControlChange(BUTTONS[i]->Bvalue, 0, BUTTONS[i]->Bchannel);
            snprintf(lcd_message1, 17, "%-17s", "Ctrl. Change Off");
            snprintf(lcd_message2, 17, "CHN:%2i  VAL:%3i", BUTTONS[i]->Bchannel, BUTTONS[i]->Bvalue);       
            updateLCD();
            BUTTONS[i]->Btoggle = 0;
          }
          break;
      }
    }

    //  Button is not pressed
    if (message == 1) {
      switch (BUTTONS[i]->Bcommand) {
        case 0:
          MIDI.sendNoteOff(BUTTONS[i]->Bvalue, 0, BUTTONS[i]->Bchannel);
          snprintf(lcd_message1, 17, "%-17s", "Note Off");
          snprintf(lcd_message2, 17, "CHN:%2i  VAL:%3i", BUTTONS[i]->Bchannel, BUTTONS[i]->Bvalue);       
          updateLCD();
          break;
        case 1:
          MIDI.sendControlChange(BUTTONS[i]->Bvalue, 0, BUTTONS[i]->Bchannel);
          snprintf(lcd_message1, 17, "%-17s", "Ctrl. Change Off");
          snprintf(lcd_message2, 17, "CHN:%2i  VAL:%3i", BUTTONS[i]->Bchannel, BUTTONS[i]->Bvalue);       
          updateLCD();
          break;
      }
    }
  }
}
//*******************************************************************
void updateMuxButtons() {

  // Cycle through Mux Button array
  for (int i = 0; i < NUMBER_MUX_BUTTONS; i = i + 1) {

    MUXBUTTONS[i]->muxUpdate();
    byte message = MUXBUTTONS[i]->getValue();

    //  Button is pressed
    if (message == 0) {
      switch (MUXBUTTONS[i]->Bcommand) {
        case 0:  //Note
          MIDI.sendNoteOn(MUXBUTTONS[i]->Bvalue, 127, MUXBUTTONS[i]->Bchannel);
          break;
        case 1:  //CC
          MIDI.sendControlChange(MUXBUTTONS[i]->Bvalue, 127, MUXBUTTONS[i]->Bchannel);
          break;
        case 2:  //Toggle
          if (MUXBUTTONS[i]->Btoggle == 0) {
            MIDI.sendControlChange(MUXBUTTONS[i]->Bvalue, 127, MUXBUTTONS[i]->Bchannel);
            MUXBUTTONS[i]->Btoggle = 1;
          } else if (MUXBUTTONS[i]->Btoggle == 1) {
            MIDI.sendControlChange(MUXBUTTONS[i]->Bvalue, 0, MUXBUTTONS[i]->Bchannel);
            MUXBUTTONS[i]->Btoggle = 0;
          }
          break;
      }
    }
    //  Button is not pressed
    if (message == 1) {
      switch (MUXBUTTONS[i]->Bcommand) {
        case 0:
          MIDI.sendNoteOff(MUXBUTTONS[i]->Bvalue, 0, MUXBUTTONS[i]->Bchannel);
          break;
        case 1:
          MIDI.sendControlChange(MUXBUTTONS[i]->Bvalue, 0, MUXBUTTONS[i]->Bchannel);
          break;
      }
    }
  }
}
//***********************************************************************
void updatePots() {
  for (int i = 0; i < NUMBER_POTS; i = i + 1) {
    byte potmessage = POTS[i]->getValue();
    if (potmessage != 255) {
      MIDI.sendControlChange(POTS[i]->Pcontrol, potmessage, POTS[i]->Pchannel);
      snprintf(lcd_message1, 17, "POT:%2i  VAL:%3i ", i+1, potmessage);
      snprintf(lcd_message2, 17, "CHN:%2i  CC:%4i", POTS[i]->Pchannel, POTS[i]->Pcontrol);       
      updateLCD();
    }
  }
}
//***********************************************************************
void updateMuxPots() {
  for (int i = 0; i < NUMBER_MUX_POTS; i = i + 1) {
    MUXPOTS[i]->muxUpdate();
    byte potmessage = MUXPOTS[i]->getValue();
    if (potmessage != 255) MIDI.sendControlChange(MUXPOTS[i]->Pcontrol, potmessage, MUXPOTS[i]->Pchannel);
  }
}
