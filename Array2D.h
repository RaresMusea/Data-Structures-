
//Header file Array2D.h->contine clasa Array2D, ce va fi utilizata in implementarea structurii de matrice bidimensionala.
#pragma once

#include "Array.h"

//Clasa generica Array2D, foloseste clasa Array
template <class T>
class Array2D {
protected:
	//Numarul de linii
	unsigned int rows;
	//Numarul de coloane
	unsigned int cols;

	//Tabloul in care se vor stoca elementele (forma unidimensionala)
	Array<T>arr;

public:

	//Clasa interna a clasei Array2D, utilizata pentru a defini o linie din array-ul bidimensional
	class Row {
	public:
		//Referinta la un obiect de tipul array2D.
		Array2D& array2D;

		//Linia curenta
		unsigned int row;

		//Constructor inline  de initializare
		Row(Array2D &arr2D, unsigned int r):
			array2D(arr2D),row(r){}

		//Supraincarcarea operatorului de indexare- permite accesarea elementului din tabloul bidimensional, linia row, coloana (pasata ca si parametru de intrare)
		T& operator[] (unsigned int col) {
			return array2D.select(row, col);
		}
	};

	//Constructori:
	//Constructorul implicit
	Array2D(){
		rows = 0;
		cols = 0;
	}

	//Constructor inline de initializare a tabloului cu numarul de linii, respectiv coloane
	Array2D(unsigned int r, unsigned int c) :rows(r), cols(c),arr(r*c) {

	}


	//Metode:
	//Permite accesarea elementului de pe linia row, coloana column
	T& select(unsigned int row, unsigned int column){
		
		//Posibilitatea depasirii limitelor de dimensiune ale tabloului bidimensional

		if (row >= rows)
			cout << "Linia " << row << " nu este valida!\n";

		if(column>=cols)
			cout << "Coloana " << column<< " nu este valida!\n";

		return arr[row * cols + column]; // operatorul de indexare utilizat in cadrul clasei Array
	}

	//Supraincarcarea operatorului de indexare- permite accesul la linia row a array-ului 2D.
	Row operator[] (unsigned int row){
		return Row(*this, row);

	}


	//Destructori:
	//Destructor-reseteaza tabloul
	~Array2D(){
		rows = 0;
		cols = 0;
		arr.setSize(0);
	}
};






