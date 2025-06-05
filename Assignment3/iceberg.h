#include "penguinDropping.h"
class iceberg
{
public:
	iceberg();
	~iceberg();
	int getHealth() { return health; }
	int getX() { return x; }
	int getY() { return y; }
	int getBoundx() { return boundx; }
	int getBoundy() { return boundy; }
private:
	int health;
	int x;
	int y;
	int boundx;
	int boundy;
};

