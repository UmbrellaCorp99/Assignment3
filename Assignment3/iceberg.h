#ifndef ICEBERGH
#define ICEBERGH

class iceberg
{
public:
	iceberg(int width, int HEIGHT);
	~iceberg();
	void drawIceberg();
	//various getter and setter methods for the iceberg class
	int getHealth() { return health; }
	int getX() { return x; }
	int getY() { return y; }
	int getBoundx() { return boundx; }
	void removeLife() {health--; }
	void updateScore() { score++; }
	int getScore() { return score; }
private:
	//the health of the iceberg
	int health;
	//the game score
	int score;
	int x;
	int y;
	int boundx;
	
	ALLEGRO_BITMAP* image;
};
#endif
