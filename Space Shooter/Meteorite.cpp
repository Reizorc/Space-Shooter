#include "Meteorite.h"

Meteroite::Meteroite()
{
	circ.setRadius(20);
	circ.setFillColor(sf::Color::Red);
	hp = 10;
	isAlive = true;
}

void Meteroite::updatePosition() {
	if (circ.getPosition().y <600) {
		circ.move(0, moveSpeed);
	}
	else {
		isAlive = false;
	}

}
