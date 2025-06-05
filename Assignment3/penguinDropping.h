
class penguinDropping
{
public:
	penguinDropping();
	~penguinDropping();
	bool getLive() { return live; }
	int getX() { return x; }
	int getY() { return y; }
	int getBoundx() { return boundx; }
	int getBoundy() { return boundy; }
private:
	bool live;
	int x;
	int y;
	int boundx;
	int boundy;
	int speed;
};

