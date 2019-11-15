// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

/*TSet::TSet(int mp) : BitField(-1)
{
}*/

// конструктор копирования
TSet::TSet(const TSet &s) : MaxPower
{
	(s.MaxPower)
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf)
MaxPower(bf.Getlength())
{

}

TSet::operator TBitField()
{
	return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
}

bool TSet::IsMember(int Elem) const // элемент множества?
{
    return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
}

int TSet::operator==(const TSet &s) const // сравнение
{
    return 0;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
}

TSet TSet::operator+(const TSet &s) // объединение
{
	return(s.BitField(BitField));
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	TSet res(BitField);
		res.InsElem(Elem);
		return TSet;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
}

TSet TSet::operator*(const TSet &s) // пересечение
{
}

TSet TSet::operator~(void) // дополнение
{
	TSet res(~BitField);
	return res;

}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	int i; istr >> i;
	while(i >= 0)
	{
		s.InsElem(i);
		istr >> i;
	}
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	for (int i = 0; i < s.MaxPower; i++)
	{
		if (s.BitField.GetBit(i))
		{
			ostr << i << "_";
		}
	}
	return ostr;
}
