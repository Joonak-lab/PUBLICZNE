#pragma once

#ifndef punkt_h
#define punkt_h

class punkt /// klasa abstrakcyjna 
{
protected:
	int x; /// sk�adowa x punktu

	int y; /// sk�adowa y punktu
public:
	virtual void set_x(int liczba) = 0; /// metoda wirtualna ustawiaj�ca sk�adow� x

	virtual void set_y(int liczba) = 0; /// metoda wirtualna ustawiaj�ca sk�adow� y

	virtual int get_x() = 0;  /// metoda wirtualna zwracaj�ca sk�adow� x

	virtual int get_y() = 0; /// metoda wirtualna zwracaj�ca sk�adow� y

	virtual ~punkt() {} /// destruktor wirtualny klasy punkt

};
#endif