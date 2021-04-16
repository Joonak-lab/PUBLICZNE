#pragma once

#ifndef punkt_h
#define punkt_h

class punkt /// klasa abstrakcyjna 
{
protected:
	int x; /// sk³adowa x punktu

	int y; /// sk³adowa y punktu
public:
	virtual void set_x(int liczba) = 0; /// metoda wirtualna ustawiaj¹ca sk³adow¹ x

	virtual void set_y(int liczba) = 0; /// metoda wirtualna ustawiaj¹ca sk³adow¹ y

	virtual int get_x() = 0;  /// metoda wirtualna zwracaj¹ca sk³adow¹ x

	virtual int get_y() = 0; /// metoda wirtualna zwracaj¹ca sk³adow¹ y

	virtual ~punkt() {} /// destruktor wirtualny klasy punkt

};
#endif