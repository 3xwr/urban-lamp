#include <cstdlib>
#include <stdlib.h>
#include <stdint.h>
#include <iostream>
#include "conio.h"

using namespace std;

void display(char c);
void display(int i);
void display(float f);
void display(union number_4b n);
void display(double d);
void display(union number_8b n);

bool yesOrNo(char* string)
{
	cout << "\n" << string << '\n';
	cout << "Y/N?\n";
	char c;
	do
	{
		c=toupper(_getch());
		if(c == 'Y' || c=='N')
		{
			cout << c;
			if(c == 'Y')
			{
				return true;
			}
			return false;
		}
	}while(c != 'Y' || c!='N');
}

union number_4b
{
	int i;
	float f;
};

union number_8b
{
	uint64_t i;
	double d;
};

void display(char c)
{
	int base = 1;
	cout << "Char - ";
	for(int i = 7; i >= 0; i--)
	cout << (c >> i & base);
	cout << endl;
}

void display(int i)
{
	union number_4b num;
	num.i = i;
	int base = 1;
	cout << "Int - ";
	for(int i = 31; i >= 0; i--) 
	cout << (num.i >> i & base);
	cout << endl;
}

void display(float f)
{
	union number_4b num;
	num.f = f;
	display(num);
	cout << endl;
}

void display(double d)
{
	union number_8b num;
	num.d = d;
	display(num);
	cout << endl;
}

void display(union number_4b n)
{
	int i;
	int base = 1;

	cout << "Float - ";
	cout << (n.i & (base << 31)) << " ";

	for (i = 30; i > 22; --i)
	{
		cout << ((n.i & (base << i)) >> i);
	}

	cout << " ";

	for(; i >= 0; --i)
	{
		cout << ((n.i & (base << i)) >> i);
	}
}

void display(union number_8b n)
{
    int i;
    uint64_t base = 1;

	cout << "Double - ";
    
    cout << (n.i & (base << 63)) << " ";
    
    for (i = 62; i > 51; --i)
	{
        cout << ((n.i & (base << i)) >> i);
    }
    
    cout << " ";
    
    for (; i >= 0; --i)
	{
        cout << ((n.i & (base << i)) >> i);
    }
}

char* CheckedInput(char* s,int sys)
{
    int i = 0;
	int len = 0;
	char* s2 = new char;
    char klaviha;
    do
    {
        klaviha =_getch();
        klaviha = toupper(klaviha);
        if((klaviha >= '0') && ( klaviha < (sys+'0')))
        {
            cout << klaviha;
            s[i] = klaviha;
            ++i;
        }
        else if((klaviha >= 'A') && (klaviha < ('A'+sys-10)))
        {
            cout << klaviha;
            s[i] = klaviha;
            ++i;
        }
        if(klaviha == 8 && i!=0)
        {
            i--;
            cout << "\b \b";
        }
    } while(klaviha!=13);
	for(int j = 0; j <= i; j++)
		s2[j] = s[j];
    cout << endl;
    return s2;
}

int MyAtoi(char *s, int rad)
{
   int n = 0;
   int k;
   for(; *s!='\0'; s++) 
   {
     if (*s <= '9' && *s>='0') k = *s - '0';
     else if (*s >= 'a' && *s<= 'z') k = *s - 'a' + 10;
     else if (*s >= 'A' && *s<= 'Z') k = *s - 'A' + 10;
     else continue;
     n = rad*n + k;
   }
   return n;
}

char* binaryInput(int len)
{
	int i = 0;
	char klaviha;
	char* s = new char[len];
	char* s2 = new char[len];
	do
	{
		klaviha = _getch();
		if(((klaviha == '0') || (klaviha == '1')) && i <= len)
		{
			cout << klaviha;
			s[i] = klaviha;
			i++;
		}
		if(klaviha == 8 && i!=0)
        {
            i--;
            cout <<"\b \b";
        }
	}while(klaviha != 13);
	for(int j = 0; j <=len; j++)
		s2[j] = s[j];
	return s2;
}

int binaryToDecimal(char* s) 
{ 
	int num = atoi(s); 
    int dec_value = 0; 
  
    int base = 1; 
  
    int temp = num; 
    while (temp) { 
        int last_digit = temp % 10; 
        temp = temp / 10; 
  
        dec_value += last_digit * base; 
  
        base = base * 2; 
    } 
  
    return dec_value; 
} 

int mirror(int x, int c, int n)
{
	int shift =  n;
    unsigned int mask = ((1 << c) - 1) << shift;
    unsigned int ext = (x & mask) >> shift;
    unsigned int rev_ext = 0;
    int i;
    for (i = 0; i < c; ++i) {
        rev_ext <<= 1;
        rev_ext |= ext & 1;
        ext >>= 1;
    }
    rev_ext <<= shift;
    return (x & ~mask) | rev_ext;
}

int mirror(float f, int c, int n)
{
	union number_4b x;
	x.f = f;
	int shift =  n;
    unsigned int mask = ((1 << c) - 1) << shift;
    unsigned int ext = (x.i & mask) >> shift;
    unsigned int rev_ext = 0;
    int j;
    for (j = 0; j < c; ++j) {
        rev_ext <<= 1;
        rev_ext |= ext & 1;
        ext >>= 1;
    }
    rev_ext <<= shift;
    return (x.i & ~mask) | rev_ext;
}

uint64_t mirror(double d, int c, int n)
{
	union number_8b x;
	x.d = d;
	int shift =  n;
    uint64_t mask = ((1 << c) - 1) << shift;
    uint64_t ext = (x.i & mask) >> shift;
    uint64_t rev_ext = 0;
    int j;
    for (j = 0; j < c; ++j) {
        rev_ext <<= 1;
        rev_ext |= ext & 1;
        ext >>= 1;
    }
    rev_ext <<= shift;
    return (x.i & ~mask) | rev_ext;
}

char mirror(char x, int c, int n)
{
	int shift =  n;
    unsigned int mask = ((1 << c) - 1) << shift;
    unsigned int ext = (x & mask) >> shift;
    unsigned int rev_ext = 0;
    int i;
    for (i = 0; i < c; ++i) {
        rev_ext <<= 1;
        rev_ext |= ext & 1;
        ext >>= 1;
    }
    rev_ext <<= shift;
    return (x & ~mask) | rev_ext;
}

void menu()
{
	union number_4b fp;
	union number_8b dp;
	int numofbytes;
	int leastsignificantbit;
	int i;
	double d;
	float f;
	char c;
	int osn;
	int char_code;
	char choice;
	do
	{
	char* s = new char;
	system("cls");
	cout << "1.Int\n2.Float\n3.Double\n4.Char\n";
	choice = _getch();
	switch(choice)
	{
	case('1'):
		cout << "\nВведите основание системы счисления: ";
		cin >> osn;
		cout << "\nВведите число: ";
		s = CheckedInput(s, osn);
		i = MyAtoi(s, osn);
		display(i);
		if(yesOrNo("Выполнить отзеркаливание бит для данного числа?"))
		{
			cout << "\nВведите количество разрядов: ";
			cin >> numofbytes;
			cout << "\nВведите младший разряд: ";
			cin >> leastsignificantbit;
			cout << endl;
			i = mirror(i, numofbytes, leastsignificantbit);
			cout << "\nЧисло в десятичной системе после отзеркаливания битов: " << i << endl;
			display(i);
		}
		_getch();
		break;
	case('2'):
		//cout << "\nВведите основание системы счисления: ";
		//cin >> osn;
		cout << "\nВведите число: ";
		cin >> f;
		display(f);
		if(yesOrNo("Выполнить отзеркаливание бит для данного числа?"))
		{
			cout << "\nВведите количество разрядов: ";
			cin >> numofbytes;
			cout << "\nВведите младший разряд: ";
			cin >> leastsignificantbit;
			cout << endl;
			fp.i = mirror(f, numofbytes, leastsignificantbit);
			cout << "\nЧисло после отзеркаливания битов: " << fp.f << endl;
			display(fp.f);
		}
		_getch();
		break;
	case('3'):
		//cout << "\nВведите основание системы счисления: ";
		cout << "\nВведите число: ";
		cin >> d;
		display(d);
		if(yesOrNo("Выполнить отзеркаливание бит для данного числа?"))
		{
			cout << "\nВведите количество разрядов: ";
			cin >> numofbytes;
			cout << "\nВведите младший разряд: ";
			cin >> leastsignificantbit;
			cout << endl;
			dp.i = mirror(d, numofbytes, leastsignificantbit);
			cout << "\nЧисло после отзеркаливания битов: " << dp.d << endl;
			display(dp.d);
		}
		_getch();
		break;
	case('4'):
		system("cls");
		cout << "1.Ввод символа\n2.Ввод кода символа\n";
		c = _getch();
		switch(c)
		{
		case('1'):
			cout << "\nВведите символ: ";
			c = _getch();
			cout << c;
			cout << '\n';
			display(c);
			if(yesOrNo("Выполнить отзеркаливание бит для данного числа?"))
			{
				cout << "\nВведите количество разрядов: ";
				cin >> numofbytes;
				cout << "\nВведите младший разряд: ";
				cin >> leastsignificantbit;
				cout << endl;
				c = mirror(c, numofbytes, leastsignificantbit);
				cout << "\nСимвол после отзеркаливания битов: " << c << endl;
				display(c);
			}
			_getch();
			break;
		case('2'):
			cout << "Введите код символа: ";
			s = binaryInput(7);
			char_code = binaryToDecimal(s);
			cout << "\nСимвол - " << (char)char_code;
			_getch();
			break;
		}
		break;
	}
	}
	while(choice!=27);

}

int main()
{
	setlocale(LC_ALL, "RUSSIAN");
	menu();
}
