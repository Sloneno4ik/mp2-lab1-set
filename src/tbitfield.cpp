// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	BitLen = len;
	MemLen = BitLen / (8 * sizeof(TELEM)) + 1;
	pMem = new TELEM[MemLen];
}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = bf.pMem[i];
	}
}

TBitField::~TBitField()
{
	delete[]pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return n / 32;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	int v;
	v = n % 32;
	TELEM tmp = 1;
	tmp = tmp << v;
	return tmp;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	int i = GetMemIndex(n);
	pMem[i] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	int i = GetMemIndex(n);
	pMem[i] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	int i = GetMemIndex(n);
	if ((pMem[i] & GetMemMask(n)) != 0)
		return 1;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
	return *this;
}

bool TBitField::operator==(const TBitField& bf) const // сравнение
{
	if (BitLen != bf.BitLen)
	{
		return false;
	}
	for (int i = 0; i < MemLen - 1; i++)
	{
		if (pMem[i] != bf.pMem[i])
			return false;
	}
	for (int i = (MemLen - 1) * 32; i < BitLen; i++)
	{
		if (GetBit(i) != bf.GetBit(i))
			return false;
	}
	return true;
}

bool TBitField::operator!=(const TBitField& bf) const // сравнение
{
	if (BitLen != bf.BitLen)
	{
		return true;
	}
	for (int i = 0; i < MemLen - 1; i++)
	{
		if (pMem[i] != bf.pMem[i])
			return true;
	}
	for (int i = (MemLen - 1) * 32; i < BitLen; i++)
	{
		if (GetBit(i) != bf.GetBit(i))
			return true;
	}
	return false;
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
	int max = bf.BitLen;
	if (BitLen > bf.BitLen)
	{
		max = BitLen;
	}
	TBitField tmp(max);
	if (BitLen < bf.BitLen)
	{
		for (int i = 0; i < MemLen - 1; i++)
		{
			tmp.pMem[i] = pMem[i];
		}
		for (int i = (MemLen - 1) * 32; i < BitLen; i++)
		{
			if (GetBit(i))
				tmp.SetBit(i);
		}
		for (int i = 0; i < tmp.MemLen; i++)
		{
			tmp.pMem[i] |= bf.pMem[i];
		}
	}
	else
	{
		for (int i = 0; i < bf.MemLen - 1; i++)
		{
			tmp.pMem[i] = bf.pMem[i];
		}
		for (int i = (bf.MemLen - 1) * 32; i < bf.BitLen; i++)
		{
			if (bf.GetBit(i))
				tmp.SetBit(i);
		}
		for (int i = 0; i < tmp.MemLen; i++)
		{
			tmp.pMem[i] |= pMem[i];
		}
	}
	return tmp;
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
	int max = bf.BitLen;
	if (BitLen > bf.BitLen)
	{
		max = BitLen;
	}
	TBitField tmp(max);
	if (BitLen < bf.BitLen)
	{
		for (int i = 0; i < MemLen - 1; i++)
		{
			tmp.pMem[i] = pMem[i];
		}
		for (int i = (MemLen - 1) * 32; i < BitLen; i++)
		{
			if (GetBit(i))
				tmp.SetBit(i);
		}
		for (int i = 0; i < tmp.MemLen; i++)
		{
			tmp.pMem[i] &= bf.pMem[i];
		}
	}
	else
	{
		for (int i = 0; i < bf.MemLen - 1; i++)
		{
			tmp.pMem[i] = bf.pMem[i];
		}
		for (int i = (bf.MemLen - 1) * 32; i < bf.BitLen; i++)
		{
			if (bf.GetBit(i))
				tmp.SetBit(i);
		}
		for (int i = 0; i < tmp.MemLen; i++)
		{
			tmp.pMem[i] &= pMem[i];
		}
	}
	return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField bf(BitLen);
	for (int i = 0; i < MemLen; i++)
	{
		bf.pMem[i] = ~pMem[i];
	}
	return bf;
}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) // ввод
{
	char c;
	int k = 0;
	do
	{
		istr >> c;
		if (c == '1')
		{
			bf.SetBit(k);
		}
		if (c == '0')
		{
			bf.ClrBit(k);
		}
		k++;
	} while ((c == '1') || (c == '0'));
	return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
	for (int i = 0; i < bf.BitLen; i++)
	{
		if (bf.GetBit(i) != 0)
		{
			ostr << 1;
		}
		else
		{
			ostr << 0;
		}
	}
	return ostr;
}