#include "Entity.h"

class Enemy : public Entity
{
public:
	Enemy(int a);
	void updatePosition();
	bool isAlive = true;
	int moveSpeed = 3;
	int hp;
protected:
private:
};

