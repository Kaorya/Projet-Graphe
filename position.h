#ifndef position_h
#define position_h

#include <iostream>

class Position
{
   int m_x;
   int m_y;

public :
        Position(int x, int y);
        //Position(const Position &p);
        Position();

   	int getX() const;
   	int getY() const;
   	void setX(int x);
   	void setY(int y);

};

#endif
