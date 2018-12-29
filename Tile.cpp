#include "Tile.h"

Tile::Tile(): d(0.2), hw(0.25f), hh(0.5f), hd(d/2) {

/*	vertices[] = {

		//back
		-hw, -hh, -d,  0.0f, 0.0f,
		hw, -hh,  -d,  0.3f, 0.0f,
		hw,  hh,  -d,  0.3f, 0.6f,
		hw,  hh,  -d,  0.3f, 0.6f,
		-hw,  hh, -d,  0.0f, 0.6f,
		-hw, -hh, -d,  0.0f, 0.0f,

		//left side
		-hw,  hh,  hd,  1.0f, 0.0f,
		-hw,  hh, -hd,  1.0f, 1.0f,
		-hw, -hh, -hd,  0.0f, 1.0f,
		-hw, -hh, -hd,  0.0f, 1.0f,
		-hw, -hh,  hd,  0.0f, 0.0f,
		-hw,  hh,  hd,  1.0f, 0.0f,

		//right side
		hw,  hh,  hd,  1.0f, 0.0f,
		hw,  hh, -hd,  1.0f, 1.0f,
		hw, -hh, -hd,  0.0f, 1.0f,
		hw, -hh, -hd,  0.0f, 1.0f,
		hw, -hh,  hd,  0.0f, 0.0f,
		hw,  hh,  hd,  1.0f, 0.0f,

		//bottom
		-hw, -hh, -hd,  0.0f, 1.0f,
		hw, -hh, -hd,  1.0f, 1.0f,
		hw, -hh,  hd,  1.0f, 0.0f,
		hw, -hh,  hd,  1.0f, 0.0f,
		-hw, -hh,  hd,  0.0f, 0.0f,
		-hw, -hh, -hd,  0.0f, 1.0f,

		//side
		-hw,  hh, -hd,  0.0f, 1.0f,
		hw,  hh, -hd,  1.0f, 1.0f,
		hw,  hh,  hd,  1.0f, 0.0f,
		hw,  hh,  hd,  1.0f, 0.0f,
		-hw,  hh,  hd,  0.0f, 0.0f,
		-hw,  hh, -hd,  0.0f, 1.0f


		//front lower half
		-hw,  -hh,  d,  0.0f, 0.0f,
		hw,  0,		d,  1.0f, 0.0f,
		hw,  -hh,   d,  1.0f, 1.0f,
		hw,  0,		d,  1.0f, 1.0f,
		-hw,  0,	d,  0.0f, 1.0f,
		-hw,  -hh,  d,  0.0f, 0.0f,

		//front upper half
		-hw,  -hh,  d,  0.0f, 0.0f,
		hw,  0,		d,  1.0f, 0.0f,
		hw,  -hh,   d,  1.0f, 1.0f,
		hw,  0,		d,  1.0f, 1.0f,
		-hw,  0,	d,  0.0f, 1.0f,
		-hw,  -hh,  d,  0.0f, 0.0f,
	}; */
}

float * Tile::getVertices()
{
	return vertices;
}

void Tile::setTex(int highDots, int lowDots) {
	for (int i = 150; i < 180; i = i + 5) {

		}

	for (int i = 180; i < 210; i = i + 5) {

	}
}
