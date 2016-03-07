#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGlutWindow.h"


//--------------------------
/*
#ifndef OF_MAIN  
#define OF_MAIN  
*/

// for windows open file dialog  
#include <windows.h>  

 
// utils  
#include "ofConstants.h"  
#include "ofMath.h"  
#include "ofUtils.h"  
#include "ofTypes.h"  

//-------------------------- 

//========================================================================
int main( ){
    
    ofAppGlutWindow window;
    ofSetupOpenGL(&window, 1920,1080/2, OF_WINDOW);			// <-------- setup the GL context
    
    // this kicks off the running of my app
    // can be OF_WINDOW or OF_FULLSCREEN
    // pass in width and height too:
    ofRunApp( new testApp());
    
}
