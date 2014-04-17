#include "position.h"

Position::Position(int x, int y):m_x(x),m_y(y)
{
	std::cout << "Position x y cree" << std::endl;
}
/*
Position::Position(const Position &p):m_x(p.m_x),m_y(p.m_y)
{
	std::cout << "Position par recopie cree" << std::endl;
}
*/
Position::Position()
{
	std::cout << "Position vide cree" << std::endl;
}

int Position::getX() const
{
	return m_x;
}
int Position::getY() const
{
	return m_y;
}
void Position::setX(int x)
{
	m_x = x;
}
void Position::setY(int y)
{
	m_y = y;
}