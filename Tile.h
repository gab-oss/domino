#pragma once

#include <cstdlib>
class Tile 
{

public:
	Tile();
	float* getVertices();
	void setTex(int highDots, int lowDots);

private:
	float d; //depth
	float hw; //half of the width
	float hh; //...height
	float hd; //...depth
	float vertices[];
};