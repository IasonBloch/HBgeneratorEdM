#pragma once

#include "ofMain.h"

class Tetragon
{
public:
	Tetragon(){}
	~Tetragon();
	Tetragon(ofPoint points[4]);
	Tetragon(ofPoint p1, ofPoint p2, ofPoint p3, ofPoint p4);
	Tetragon(int coorXp1, int coorYp1, int coorXp2, int coorYp2, int coorXp3, int coorYp3, int coorXp4, int coorYp4 );
	//
	ofPoint	vertexes[4];
	bool	isInit;
	//
	bool	isEqual(Tetragon t);
	int		closestPointTo(int x, int y);
	int		closestPointTo(int x, int y, float range);
	ofPoint	baryCentre();
	void	translatePoint(int newX, int newY, int pointIndex);
	void	translatePoint(int newX, int newY, int pointIndex, float range);
	void	translate(int xFactor, int yFactor);
	void	scale(int pixel);


	

};

