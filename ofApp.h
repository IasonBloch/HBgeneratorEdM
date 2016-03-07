#pragma once

#include "ofMain.h"
#include "Tetragon.h"
#include "ofxXmlSettings.h"

class testApp : public ofBaseApp{
    
public:

	/*
	testApp() {
		
	}
	*/

	//	Methods
    void setup();
    void update();
    void draw();
    //	Update events
    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

	//	My Methods
	void newHitBox(int x, int y, int w, int h);

	void switchEditMode();
	void switchNegativeMode();

	void scaleAllHitBoxes(int pixel);
	void scaleSelectedHitBox(int pixel);

	void saveWindowToJPG();

	void drawHitBoxes(ofTexture t);
	void drawHitBoxes(ofTexture unselected, ofTexture selected);

	void deleteSelectedHitBox();

	void saveXMLSettings();
	void loadXMLSettings();

	void clear();

	bool isInHitBox(int x, int y, Tetragon hitBox);

	int findHitBoxIndex(Tetragon *hitBox);

	void updateClosestSelectedPointTo(int mX, int mY);

	void updateSelectedHitBox(int x, int y);
	

	//	Atributes
	ofxXmlSettings		hitBoxesSettings;
	ofImage				screenShot;

	string				feedBackMessage;	///////////////////////// TODO : afficher
	

    ofTexture           textureNoire;
	ofTexture           textureBlanche;

    vector<Tetragon>	hitBoxes;
	Tetragon			*selectedHitBox;
	int					selectedHitBoxIndex;

    bool                editModeState;
	bool				negativeModeState;

	int					defaultHitboxWith;
	int					defaultHitboxHight;
	
	int					pointEdtionSensibility;

	//	Not Used
	string			windowsPath;
	int				scalingFactor;
	int				scale;
};
