#include "ofApp.h"

//--------------------------------------------------------------
void testApp::setup() {
	ofLoadImage(textureNoire, "noir.jpg");
	ofLoadImage(textureBlanche, "Blanc.jpg");
	ofBackground(255, 255, 255, 0);
	defaultHitboxWith = 50;
	defaultHitboxHight = 50;
	editModeState = false;
	negativeModeState = false;
	//	ToDo : Change to closest point
	pointEdtionSensibility = 20;
	scalingFactor = 1;
	//	scale = 0;
}

//--------------------------------------------------------------
void testApp::update() {
	//	No dynamics
}
//--------------------------------------------------------------
void testApp::draw() {
	//	Display Mask
	if (editModeState) {
		//	Edit Mask
		//	Set back Ground to grey
		ofBackground(128, 128, 128, 0);
		//	Unselected HitBox and selected HitBox
		drawHitBoxes(textureNoire, textureBlanche);
	}
	else {
		if (negativeModeState) {
			//	Set back Ground to Black
			ofBackground(0, 0, 0, 0);
			drawHitBoxes(textureBlanche);
		}
		else {
			//	Set back Ground to White
			ofBackground(255, 255, 255, 0);
			drawHitBoxes(textureNoire);
		}
	}
}

//--------------------------------------------------------------
//--------------------------------------------------------------
void testApp::keyPressed(int key) {
	//	TODO : Switch to case use
	if (key == 'r') {
		//	Rescale
		newHitBox(mouseX, mouseY, defaultHitboxWith, defaultHitboxHight);
	}
	else if (key == 'e') {
		//	Edit
		switchEditMode();
	}
	else if (key == 's') {
		//	Save mask to jpg
		if (!editModeState) {
			saveWindowToJPG();
		}
	}
	else if (key == 'n') {
		switchNegativeMode();
	}
	else if (key == 'x') {
		//	Save setings to xml
		saveXMLSettings();
	}
	else if (key == 'd') {
		//	Delete selected HitBox
		if (editModeState) {
			deleteSelectedHitBox();
		}
	}
	else if (key == 'l') {
		//	load xml settings
		loadXMLSettings();
	}
	else if (key == 'c') {
		//	Clear
		clear();
	}
	else if (key == '+') {
		//	Scale up
		if (editModeState) {
			scaleSelectedHitBox(scalingFactor);
		}
		else {
			scaleAllHitBoxes(scalingFactor);
		}
		
	}
	else if (key == '-') {
		//	Scale down
		if (editModeState) {
			scaleSelectedHitBox(-scalingFactor);
		}
		else {
			scaleAllHitBoxes(-scalingFactor);
		}
	}
}
//--------------------------------------------------------------
void testApp::keyReleased(int key) {

}
//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y) {

}
//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button) {
	if (editModeState) {
		
		updateClosestSelectedPointTo(x, y);
	}
	else {
		//	updateClosestHitBox(x,y)
	}
}
//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button) {
	if (editModeState) {
		updateSelectedHitBox(x, y);
	}
	else if (!editModeState) {
		newHitBox(x, y, defaultHitboxWith, defaultHitboxHight);
	}
}
//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button) {

}
//--------------------------------------------------------------
void testApp::windowResized(int w, int h) {

}
//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg) {

}
//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo) {

}
//--------------------------------------------------------------
//	My own Functions
//--------------------------------------------------------------
void testApp::newHitBox(int x, int y, int w, int h)
{
	//	Create New HitBox
	Tetragon newrect = Tetragon(
		ofVec2f(x, y),
		ofVec2f(x + w, y),
		ofVec2f(x + w, y + h),
		ofVec2f(x, y + h)
		);

	//	Addnew HitBox to HitBoxes table
	hitBoxes.push_back(newrect);
}

void testApp::switchEditMode()
{
	if (editModeState) {
		editModeState = false;
	}
	else {
		editModeState = true;
	}
}

void testApp::switchNegativeMode()
{
	if (negativeModeState) {
		negativeModeState = false;
	}
	else {
		negativeModeState = true;
	}
}

void testApp::scaleAllHitBoxes(int pixel)
{
	for (int i = 0; i < hitBoxes.size(); i++) {
		hitBoxes[i].scale(pixel);
	}
}

void testApp::scaleSelectedHitBox(int pixel)
{
	if (selectedHitBox->isInit) {
		selectedHitBox->scale(pixel);
	}
}

void testApp::saveWindowToJPG()
{
	screenShot.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
	if (negativeModeState) {
		screenShot.save("NegativeHitBoxScreenShot" + to_string(ofGetUnixTime()) + ".jpg");
	}
	else {
		screenShot.save("HitBoxScreenShot" + to_string(ofGetUnixTime()) + ".jpg");
	}

}


void testApp::updateClosestSelectedPointTo(int newX, int newY)
{
	if (selectedHitBox->isInit) {

		int pointIndex = hitBoxes[selectedHitBoxIndex].closestPointTo(newX, newY, pointEdtionSensibility);

		hitBoxes[selectedHitBoxIndex].translatePoint(newX, newY, pointIndex);
	}
}


bool testApp::isInHitBox(int x, int y, Tetragon hitBox)
{
	//	TODO :	perfect hitBox recognition
	if (
		// Rectangle bidon
		x >= hitBox.vertexes[0].x &&
		y >= hitBox.vertexes[0].y &&
		x <= hitBox.vertexes[2].x &&
		y <= hitBox.vertexes[2].y
		)
	{
		return true;
	}
	else
	{
		return false;
	}

}

// findHitBoxIndex(Tetragon *hitBox)
/*
int testApp::findHitBoxIndex(Tetragon *hitBox)
{
	for (int i = 0; i < hitBoxes.size(); i++) {
		if (hitBoxes[i].isEqual(hitBox)) {
			return i;
		}
	}
	return -1;
}
*/

void testApp::updateSelectedHitBox(int x, int y)
{
	for (int i = 0; i < hitBoxes.size(); i++) {
		if (isInHitBox(x, y, hitBoxes[i])) {
			selectedHitBox = &hitBoxes[i];
			selectedHitBoxIndex = i;
		}
	}
}

void testApp::drawHitBoxes(ofTexture t)
{
	for (int i = 0; i < hitBoxes.size(); i++) {
		t.draw(
			hitBoxes[i].vertexes[0],
			hitBoxes[i].vertexes[1],
			hitBoxes[i].vertexes[2],
			hitBoxes[i].vertexes[3]
			);
	}
}

void testApp::drawHitBoxes(ofTexture unselected, ofTexture selected)
{
	for (int i = 0; i < hitBoxes.size(); i++) {
		if (selectedHitBoxIndex == i) {
			selected.draw(
				hitBoxes[i].vertexes[0],
				hitBoxes[i].vertexes[1],
				hitBoxes[i].vertexes[2],
				hitBoxes[i].vertexes[3]
				);
		}
		else {
			unselected.draw(
				hitBoxes[i].vertexes[0],
				hitBoxes[i].vertexes[1],
				hitBoxes[i].vertexes[2],
				hitBoxes[i].vertexes[3]
				);
		}
	}
}

void testApp::deleteSelectedHitBox()
{
	if (selectedHitBox->isInit) {
		selectedHitBox->isInit = false;		
		hitBoxes.erase(hitBoxes.begin() + selectedHitBoxIndex);
		selectedHitBoxIndex = -1;
	}
}

void testApp::saveXMLSettings()
{
	hitBoxesSettings.setValue("settings_HitBoxes_Number",
		to_string(hitBoxes.size()));

	for (int i = 0; i < hitBoxes.size(); i++)
	{
		for (int j = 0; j < 4; j++)
		{
			hitBoxesSettings.setValue("settings_HitBox_nb_" + to_string(i) + "_point_nb_" + to_string(j) + "_X_coordinate",
				hitBoxes[i].vertexes[j].x);
			hitBoxesSettings.setValue("settings_HitBox_nb_" + to_string(i) + "_point_nb_" + to_string(j) + "_Y_coordinate",
				hitBoxes[i].vertexes[j].y);
		}
	}

	hitBoxesSettings.saveFile("HitBoxes_Settings" + to_string(ofGetUnixTime()) + ".xml");

	//	FeedBack 
	feedBackMessage = "settings saved to xml!";
}

void testApp::loadXMLSettings()
{
	clear();

	hitBoxesSettings.loadFile(ofSystemLoadDialog("Load xml file please", false, "\of_v0.9.2_vs_release\apps\myApps\hitboxMaskGernerator\bin").getPath());

	int buffer = hitBoxesSettings.getValue("settings_HitBoxes_Number", 0);

	hitBoxes = vector<Tetragon>(buffer);

	//	Apply loaded settings
	for (int i = 0; i < buffer; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			hitBoxes[i].vertexes[j].x = hitBoxesSettings.getValue("settings_HitBox_nb_" + to_string(i) + "_point_nb_" + to_string(j) + "_X_coordinate", 0.0);
			hitBoxes[i].vertexes[j].y = hitBoxesSettings.getValue("settings_HitBox_nb_" + to_string(i) + "_point_nb_" + to_string(j) + "_Y_coordinate", 0.0);
		}
	}
	//	FeedBack 
	feedBackMessage = "settings loaded from :" + ofFileDialogResult().getPath();
}

void testApp::clear()
{
	ofBackground(255, 255, 255, 0);
	editModeState = false;
	negativeModeState = false;
	hitBoxes.clear();
	selectedHitBox->isInit = false;
	//	hitBoxesSettings.clear();
}



