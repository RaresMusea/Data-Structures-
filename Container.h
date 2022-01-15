//Fisier Container.h-> Contine clasa virtuala cu acelasi nume, care face referire la expresia unei colectii numarabile de elemente, ce ulterior va fi utilizata in implementarea structurilor de stiva, coada, etc.
#pragma once

class Container {
protected:

	//Dimensiunea
	unsigned int count;

	//Constructorul implicit inline-initializeaza instanta clasei cu dimensiunea 0
	Container():count(0){}

public:
	//Metode virtuale pure:

	//Accesor ce permite obtinerea numarului de elemente din colectie
	virtual unsigned int getCount() const=0;

	//Metoda care verifica daca o colectie este sau nu goala
	virtual bool isEmpty() const=0;

	//Metoda care verifica daca o colectie este sau nu plina
	virtual bool isFull() const=0;




};