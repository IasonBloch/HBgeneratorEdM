#include "Tetragon.h"

Tetragon::Tetragon(ofPoint points[4])
{
	isInit = true;
	for (int i = 0; i < 4; i++)
	{
		vertexes[i] = points[i];
	}

}

Tetragon::Tetragon(ofPoint p1, ofPoint p2, ofPoint p3, ofPoint p4)
{
	isInit = true;

	vertexes[0] = p1;
	vertexes[1] = p2;
	vertexes[2] = p3;
	vertexes[3] = p4;

}

Tetragon::Tetragon(int coorXp1, int coorYp1, int coorXp2, int coorYp2, int coorXp3, int coorYp3, int coorXp4, int coorYp4)
{
	isInit = true;

	vertexes[0].x = coorXp1;
	vertexes[0].y = coorYp1;

	vertexes[1].x = coorXp2;
	vertexes[1].y = coorYp2;

	vertexes[2].x = coorXp3;
	vertexes[2].y = coorYp3;

	vertexes[3].x = coorXp4;
	vertexes[3].y = coorYp4;
}

Tetragon::~Tetragon()
{
}

//
void Tetragon::scale(int pixel)
{
	vertexes[0].x = vertexes[0].x - pixel;
	vertexes[0].y = vertexes[0].y - pixel;

	vertexes[1].x = vertexes[1].x + pixel;
	vertexes[1].y = vertexes[1].y - pixel;

	vertexes[2].x = vertexes[2].x + pixel;
	vertexes[2].y = vertexes[2].y + pixel;

	vertexes[3].x = vertexes[3].x - pixel;
	vertexes[3].y = vertexes[3].y + pixel;
}

//
void Tetragon::translatePoint(int newX, int newY, int pointIndex)
{
	vertexes[pointIndex].x = newX;
	vertexes[pointIndex].y = newY;
}

void Tetragon::translatePoint(int newX, int newY, int pointIndex, float range)
{
	//	Find Distance 
	int index = closestPointTo(newX, newY, range);
	//	Update if in range
	if (index <= 0) {
		translatePoint(newX, newY, index);
	}
}

void Tetragon::translate(int xFactor, int yFactor)
{
	for (int i = 0; i < 4; i++)
	{
		translatePoint(xFactor, yFactor, i);
	}
}

bool Tetragon::isEqual(Tetragon t)
{

	for (int i = 0; i < 4; i++)
	{
		if (!((vertexes[i].x == t.vertexes[i].x) && (vertexes[i].y == t.vertexes[i].y))) {
			return false;
		}
	}

	return true;
}

int Tetragon::closestPointTo(int x, int y)
{
	int result = 0;
	float dx = abs(x - vertexes[0].x);
	float dy = abs(y - vertexes[0].y);
	float d1 = dx + dy;
	float tmpD;

	for (int i = 1; i < 4; i++)
	{
		dx = abs(x - vertexes[i].x);
		dy = abs(y - vertexes[i].y);
		tmpD = dx + dy;

		if (tmpD < d1) {
			d1 = tmpD;
			result = i;
		}
	}
	return result;
}

int Tetragon::closestPointTo(int x, int y, float range)
{
	int result = -1;
	float dx;
	float dy;
	float d;
	float tmp = range;

	for (int i = 0; i < 4; i++)
	{
		dx = abs(x - vertexes[i].x);
		dy = abs(y - vertexes[i].y);
		d = dx + dy;

		if (d < tmp) {
			tmp = d;
			result = i;
		}
	}
	return result;
}

ofPoint Tetragon::baryCentre()
{
	return ofPoint();
}





