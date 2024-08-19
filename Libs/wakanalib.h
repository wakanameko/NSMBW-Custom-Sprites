#ifndef WAKANALIB_H
#define WAKANALIB_H 
/*VERSION 1.0 SMV*/
#include <common.h>

// increase rests
extern "C" void addRest(int playerIDRest, int howMany, bool reallyAddRest);	// reallyAddRest is always true
extern "C" void incRestAll(bool reallyAddRest);	// reallyAddRest is always true

// stage funcs
extern "C" void oneUPPopup(Vec pos);   // set the position (x,y)
extern "C" void AddScore(int howMany, int color);
extern "C" void DisplayScoreAddPopup(Vec pos, int smallScoreID, int playerID, bool wantToShowThisForever);  // smallScoreID list is here -> https://note.com/reaz0n23/n/nb504e036da6d#143de39b-221f-4909-94f8-cc11e4dbdfdd

// zone settings
extern "C" float zoneZoomFloat;    // Default is 2.0

//
extern "C" char aP_rcha_2;     //"P_rcha"

// daEnDpakkunBase_c::
extern "C" void pakkunYoshiFumiJumpSet(dEn_c *apThis, daPlBase_c *unk);    // 2nd argument is unknown

#endif /* WAKANALIB_H */
