#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
//#include <ArduinoJson.h>
#include "Fonts.h"

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define  MAX_DEVICES 4 
#define CLK_PIN     14  //D5 // or SCK
#define DATA_PIN    13   //D7 // or MOSI
#define CS_PIN      15  // D8 // or SS

MD_Parola P = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
#define ARRAY_SIZE(x)  (sizeof(x)/sizeof(x[0]))

static uint16_t rnd; 
String Text;
char buf[256];

// Global data
typedef struct
{
  uint16_t      countt;
  textEffect_t  effect;   // text effect to display
  char *        psz;      // text string nul terminated
  uint16_t      speed;    // speed multiplier of library default
  uint16_t      pause;    // pause multiplier for library default
} sCatalog;

sCatalog  catalog[] =
{
  { 0, PA_SLICE,            "SLICE",  1, 1 },
  { 1, PA_MESH,              "MESH",  10,1 },
  { 2, PA_FADE,              "FADE",  20,1 },
  { 3, PA_WIPE,              "WIPE",  5, 1 },
  { 4, PA_WIPE_CURSOR,       "WPE_C", 4, 1 },
  { 5, PA_OPENING, "OPEN",            3, 1 },
  { 6, PA_OPENING_CURSOR, "OPN_C",    4, 1 },
  { 7, PA_CLOSING, "CLOSE",           3, 1 },
  { 8, PA_CLOSING_CURSOR, "CLS_C",    4, 1 },
  { 9, PA_BLINDS, "BLIND",            7, 1 },
  { 10, PA_DISSOLVE, "DSLVE",         7, 1 },
  { 11, PA_SCROLL_UP, "SC_U",         5, 1 },
  { 12, PA_SCROLL_DOWN, "SC_D",       5, 1 },
  { 13, PA_SCROLL_LEFT, "SC_L",       5, 1 },
  { 14, PA_SCROLL_RIGHT, "SC_R",      5, 1 },
  { 15, PA_SCROLL_UP_LEFT, "SC_UL",   7, 1 },
  { 16, PA_SCROLL_UP_RIGHT, "SC_UR",  7, 1 },
  { 17, PA_SCROLL_DOWN_LEFT, "SC_DL", 7, 1 },
  { 18, PA_SCROLL_DOWN_RIGHT, "SC_DR",7, 1 },
  { 19, PA_SCAN_HORIZ, "SCANH",       4, 1 },
  { 20, PA_SCAN_VERT, "SCANV",        3, 1 },
  { 21, PA_GROW_UP, "GRW_U",          7, 1 },
  { 22, PA_GROW_DOWN, "GRW_D",        7, 1 },
};


extern "C" {
#include "user_interface.h"
}



void loop() {
   static uint8_t i = 0;  // text effect index
/*
 if (P.displayAnimate()) {
    if (i == ARRAY_SIZE(catalog))i = 0;  // reset loop index

   P.displayText(catalog[i].psz, PA_CENTER, 30, 3000, catalog[i].effect, catalog[i].effect);   //чем меньше тем бестрее
    i++;   // then set up for next text effect
   delay(500);
   }
*/

  if  (P.displayAnimate()){
    Text="привет helo привет time";
  utf8rus(Text).toCharArray(buf, 256);
  P.displayScroll(buf, PA_LEFT, PA_SCROLL_RIGHT, 40);
   
  //if (!P.displayAnimate()) {disp = 5;}
  }




}


String utf8rus(String source)
{
  int i,k;
  String target;
  unsigned char n;
  char m[2] = { '0', '\0' };

  k = source.length(); i = 0;

  while (i < k) {
    n = source[i]; i++;

    if (n >= 0xC0) {
      switch (n) {
        case 0xD0: {
          n = source[i]; i++;
          if (n == 0x81) { n = 0xA8; break; }
          if (n >= 0x90 && n <= 0xBF) n = n + 0x30;
          break;
        }
        case 0xD1: {
          n = source[i]; i++;
          if (n == 0x91) { n = 0xB8; break; }
          if (n >= 0x80 && n <= 0x8F) n = n + 0x70;
          break;
        }
      }
    }
    m[0] = n; target = target + String(m);
  }
return target;
}
