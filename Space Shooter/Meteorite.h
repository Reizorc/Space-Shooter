#ifndef METEROITE_H
#define METEROITE_H

#include "Entity.h"

class Meteroite : public Entity
{
public:
	Meteroite();
	void updatePosition();
	bool isAlive = true;
	int moveSpeed = 5;
	int hp;
protected:
private:
};

#endif // METEROITE_H
