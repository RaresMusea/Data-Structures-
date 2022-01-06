//Fisier header Matrix.h->implementarea intr-o forma liniara a tablourilor bidimensionale, cat si a operatiilor cu aceste structuri de date.
//Clasa Matrix mosteneste clasa Array2D,definita in header file-ul cu acelasi nume.
#pragma once

#include "Array2D.h"

//Clasa generica Matrix, mosteneste toate campurile si metodele clasei Array2D

template <class T>
class Matrix:public Array2D<T> {

public:

	//Constructorul implicit
	Matrix() {}
	
	//Constructorul inline de initializare, apeleaza constructorul superclasei pentru a initializa matricea cu numarul de linii, respectiv coloane pasate drept argumente.
	Matrix(unsigned int r, unsigned int c) :Array2D<T>(r, c){}
	
	//Metode:
	//Supraincarcarea operatorului de inmultire permite calculul produsului a doua matrice
	Matrix<T> operator* (Matrix<T> const& param) const;

	//Supraincarcarea operatorului de insumare permite calculul sumei a doua matrice
	Matrix<T> operator+ (Matrix<T> const& param)const;

	//Supraincarcarea operatorului de egalitate, permite verificarea egalitatii dintre doua matrice (true, daca matricele sunt egale, false, in caz contrar).
	bool operator == (Matrix<T> param);
	
	//Metoda ce calculeaza transpusa unei matrice 
	Matrix<T> transpose();

	//Metoda responsabila de citirea de la tastatura a unei matrice
	void read();

	//Metoda responsabila de afisarea pe ecran a matricei
	void print();

	//Returneaza numarul de linii
	unsigned int getRows() {
		return this->rows;
	}

	//Returneaza numarul de coloane
	unsigned int getCols() {
		return this->cols;
	}

	//Metoda responsabila de calculul determinantului
	int MatrixDet();

	//Supraincarcarea operatorului de scriere in fluxul de intrare, permite citirea de la tastatura a unei instante a clasei Matrix
	friend istream& operator >> (istream& istr, Matrix<T>& arg) {
		
		cout << "Cate linii? "; istr >> arg.rows;
		cout << "Cate coloane? "; istr >> arg.cols;

		arg = Matrix<T>(arg.rows, arg.cols);

		arg.arr.setSize((arg.rows * arg.cols));


		for (int i = 0; i < arg.rows; i++) {
			for (int j = 0; j < arg.cols; j++) {
				int val;
				cout << "Elementul (" << i + 1 << " , " << j + 1 << "):";
				istr >> val;
				arg[i][j] = val;
			}
		}

		return istr;
	}


	//Supraincarcarea operatorului de scriere in fluxul de iesire->Afisarea unei matrice pe cran
	friend ostream& operator<<(ostream& ostr, Matrix<T>& arg) {
		for (int i = 0; i < arg.rows; i++) {
			for (int j = 0; j < arg.cols; j++)
				ostr << arg[i][j] << "\t";
			ostr << endl;
		}
		cout << endl;
		return ostr;
	}

};

//Metode:

//Calculeaza produsul a 2 matrice:
template <class T>
Matrix<T> Matrix<T>::operator*(Matrix<T> const& param)const {

	//Posibilitatea introducerii unor valori care depasesc limitele tabloului
	if (this->cols != param.rows)
		cout << "Matrice incompatibile!\n Nu se poate efectua inmultirea!\n";
	
	//Matricea rezultata
	Matrix<T> result(this->rows, param.cols);
	
	for (int i=0;i<this->rows;i++)
		for (int j = 0; j < param.cols; j++) {
			T sum = 0;
			for (int k = 0; k < this->cols; k++)
				sum += (*this)[i][k] * param[k][j];
			result[i][j] = sum;
		}
	return result;
}

//Calculeaza suma a 2 matrice
template <class T>
Matrix<T> Matrix<T>::operator+(Matrix<T> const& param) const {
	
	//Posibilitatea ca matricele sa nu poata fi insumate
	if (this->rows != param.rows)
		cout << "Matrici incompatibile \n";

	if (this->cols != param.cols)
		cout << "Matrici incompatibile \n";

	Matrix<T> result(this->rows, this->cols);
	for (int i = 0; i < this->rows; i++)
		for (int j = 0; j < this->cols; j++)
			result[i][j] = (*this)[i][j] + param[i][j];
	
	return result;
}

//Calculeaza transpusa unei matrice 
template<class T>
Matrix<T> Matrix<T>::transpose() {

	int size = (this->rows > this->cols) ? this->rows : this->cols;
	
	Matrix<T> result(size,size);
	for (int i = 0; i < this->cols; i++)
		for (int j = 0; j < this->rows; j++)
			result[i][j] = 0;
	for (int i = 0; i < this->rows; i++)
		for (int j = 0; j < this->cols; j++)
			result[j][i] =( * this)[i][j];
	return result;
	
}

//Citeste o matrice
template <class T>
void Matrix<T>::read() {
	
	cout << "Cate linii? "; cin >> this->rows;
	cout << "Cate coloane? "; cin >> this->cols;

	(*this) = Matrix<T>(this->rows, this->cols);

	for (int i = 0; i < this->rows; i++) {
		for (int j = 0; j < this->cols; j++) {
			int val;
			cout << "Elementul (" << i + 1 << " , " << j + 1 << "):";
			cin >>val;
			(*this)[i][j] = val;
		}
	}
}

//Afiseaza matricea pe ecran
template <class T>
void Matrix<T>::print() {

	for (int i = 0; i < this->rows; i++) {
		for (int j = 0; j < this->cols; j++)
			cout << (*this)[i][j] << "\t";
		cout << endl;
	}
	cout << endl;
}

//Calculeaza determinantul unei matrice patratice.
template <class T>
int Matrix<T>::MatrixDet() {

	//Caci; in care matricea nu este una patratica
	if (this->rows != this->cols) {
		cout << "Nu se poate efectua calculul determinantului, intrucat matricea nu este una patratica!\n";
		return -1;
	}

	//Daca matricea este patratica
	int size = this->rows;

	//Folosim un array de intregi pentru a stoca o linie
	Array<int> r(size,0);
	int idx,aux,D=1,total=1;

	//Parcurgem toate elementele diagonale
	for (int i = 0; i < size; i++) {
		idx = i;

		//In continuare, vom cauta index-ul ce corespunde unei valori nenule
		while ((*this)[idx][i] == 0 && idx < size)
			idx++;

		if (idx == size) //daca se va gasi un element nenul
			continue;

		if (idx != i)
		{
			//Iteram pentru a interschimba linia diagonala a elementului si indicele liniei
			for (int j = 0; j < size; j++)
			{
				aux =(*this)[idx][j];
				(*this)[idx][j] = (*this)[i][j];
				(*this)[i][j] = aux;
			}

			//Semnul determinantului se schimba de fiecare daca cand mutam liniile conform proprietatilor determinantilor
			D = D * pow(-1, idx - i);
		}

			//Stocam valorile de pe linia diagonala
			for (int j = 0; j < size; j++)
				r[j] = (*this)[i][j];

			//traversam fiecare linie de sub elementul de pe diagonala
			int diag, nextel;
			for (int j = i + 1; j < size; j++)
			{
				//valoarea elementului de pe diagonala
				diag = r[i];
				//Valoarea elementului de pe urmatoarea linie
				nextel = (*this)[j][i];

				//Traversam fiecare coloana si inmultim cu fiecare linie
				for (int k = 0; k < size; k++)
					//Inmultim pana cand elementul de pe diagonala si elementul de pe linie sunt egale

					(*this)[j][k] = (diag * (*this)[j][k]) - (nextel * r[k]);

				total = total * diag;

			}
		}
	
	//Se vor inmulti elementele diagonale si se va obtine valoarea determinantului
	for (int i = 0; i < size; i++)
	{
		D= D* (*this)[i][i];
	}

	//Returnam rezultatul obtinut
	return (D/ total); 
}

//Verifica daca doua matrice coincid
template <class T>
bool Matrix<T>::operator == (Matrix<T> param) {

	//Daca numarul de linii este egal cu cel de coloane, este posibil ca matricele sa poata coincida, si pentru aceasta le vom parcurge si vom verifica
	if (this->getCols() == param.getCols() && this->getRows() == param.getRows())
	{
		for (int i = 0; i < this->getRows(); i++)
			for (int j = 0; j < this->getCols(); j++)
				if ((*this)[i][j] != param[i][j])
					return false;

	}
	
	//Daca 2 matrice difera prin linii/coloane, este clar ca nu sunt identice
	else
		return false;
	//Matricele coincid
	return true;
}

//Functie care verifica daca o matrice de tip relatie este sau nu simetrica.
template <class T>
bool isSymmetrical(Matrix<T> m) {

	//Calculam transpusa
	Matrix<T>tr = m.transpose();
	//Relatia este simetrica
	if (m == tr)
		return true;

	//Relatia nu este simetrica
	return false;

}

//Functie care verifica daca o matrice de tip relatie este sau nu reflexiva.
template <class T>
bool isReflexive(Matrix<T> m) {

	//O matrice de tip relatie este reflexiva, daca elementele de pe diagonala principala sunt egale cu 1.

	int size = (m.getRows() < m.getCols()) ? m.getRows() : m.getCols();

	//Daca se va gasi cel putin un element nul pe diagonala principala, atunci matricea nu este reflexiva
	for (int i = 0; i < size; i++)
		if (m[i][i] != 1)
			return false;

	//Cazul contrar->Matricea este reflexiva.
	return true;

}

//Functie care verifica daca o matrice de tip relatie este sau nu tranzitiva
template <class T>
bool isTransistive(Matrix<T> m) {

	//O matrice poate fi tranzitiva doar daca numarul de linii si cel de coloane sunt egale

	//Tranzitivitate: Daca (a,b)=(b,c)=(a,c). Vom aplica acest principiu si pe matricea m:
	if (m.getRows() == m.getCols()) {

		for (int i = 0; i < m.getRows(); i++)
			for (int j = 0; j < m.getCols(); j++)
				for (int idx = 0; idx < m.getRows(); idx++)
					if (m[i][idx] == 1 && m[i][j] == 1 && m[j][idx] == 1)
						return true;


	}
	//Matricea nu este tranzitiva
	return false;
}

template <class T>
void verifyRelationships(Matrix<T> m) {

	
	//Simetria
	if (isSymmetrical(m))
		cout << "Matricea contine cel putin o relatie simetrica.\n";
	else
		cout << "Nu s-a gasit nicio relatie simetrica in matricea data.\n";

	//Reflexivitatea:
	if (isReflexive(m))
		cout << "Matricea contine cel putin o relatie reflexiva.\n";
	else
		cout << "Nu s-a gasit nicio relatie reflexiva in matricea data.\n";

	//Tranzitivitatea
	if (isTransistive(m))
		cout << "Matricea contine cel putin o relatie tranzitiva.\n";
	else
		cout << "Nu s-a gasit nicio relatie tranzitiva in matricea data.\n";

}




