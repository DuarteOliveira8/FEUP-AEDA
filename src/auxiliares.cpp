#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "auxiliares.h"

using namespace std;


//---------------------------------------------------------------------------------------
//                                  DATA ATUAL
//---------------------------------------------------------------------------------------

Data dataHoje = Data("8/1/2018");


//---------------------------------------------------------------------------------------
//                              FUNCOES AUXILIARES
//---------------------------------------------------------------------------------------

bool verify2dias(Data dataVoo) {
	if (dataHoje.ano == dataVoo.ano - 1 )
	{
		if ((dataVoo.mes == 1) && (dataHoje.ano == 12))
		{
			if (dataVoo.dia == 2)
			{
				return dataHoje.dia == 31;
			}
			else if (dataVoo.dia == 1)
			{
				return dataHoje.dia >= 30;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	else if (dataHoje.ano == dataVoo.ano)
	{
		if (dataHoje.mes == dataVoo.mes -1)
		{
			if (dataVoo.dia == 2)
			{
				return dataHoje.dia == 31;
			}
			else if (dataVoo.dia == 1)
			{
				return dataHoje.dia >= 30;
			}
			else
			{
				return false;
			}
		}
		else if (dataHoje.mes == dataVoo.mes)
		{
			return dataHoje.dia >= (dataVoo.dia - 2);
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

bool verifyInativo(Data dataUltimoVoo){
	if (dataUltimoVoo.ano == (dataHoje.ano - 1))
		if (dataUltimoVoo.mes == dataHoje.mes)
			return dataUltimoVoo.dia < dataHoje.dia;
		else
			return dataUltimoVoo.mes < dataHoje.mes;
	else
		return dataUltimoVoo.ano < (dataHoje.ano - 1);
}

int Valid_Cin() // Garantir que os cin do tipo int nao causem erros no programa
{
	int input = 0;
	bool valid = false;

	while (!valid)  //enquanto o cin nao e valido, continua a pedir o input
	{
		cin >> input;
		valid = true;
		if (!cin)
		{
			cin.clear();
			cout << "O valor introduzido e invalido! Introduza de novo:\n";
			valid = false;
		}
		cin.ignore(10000, '\n');
	}

	return input;
}

int opcaoMenu(int opcoes) // garantir a escolha de uma opcao que exista nos menus
{
	int opcao = 0;
	bool valid = false;

	while (!valid)
	{
		cout << "Introduza aqui o numero da opcao: \n";
		opcao = Valid_Cin();
		if ((opcao >= 0) && (opcao <= opcoes))
		{
			valid = true;
		}
		else
		{
			cout << "Essa opcao nao existe!\n";
		}
	}
	return opcao;
}

char respostaSN(string frase){
	char resposta;

	while(true){
		try{
			cin >> resposta;
		}
		catch(...){
			cout << "Input invalido!\n" << frase;
			continue;
		}

		if (resposta == 'S')
			return 'S';
		else if (resposta == 'N')
			return 'N';
		else
			cout << "Input invalido!\n" << frase;
	}
}

void clearScreen(){
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}


//---------------------------------------------------------------------------------------
//                          FUNÇOES DA CLASSE AUXILIAR DATA
//---------------------------------------------------------------------------------------

Data::Data(string data){
	string temp = data;
	try{
		dia = stoi(data.substr(0, data.find('/')));
	}
	catch (...){
		throw DataInvalida(temp);
	}
	if(dia < 1 || dia > 31)
		throw DataInvalida(temp);

	data = data.substr(data.find('/') + 1);

	try{
		mes = stoi(data.substr(0, data.find('/')));
	}
	catch(...){
		throw DataInvalida(temp);
	}
	if(mes < 1 || mes > 12)
		throw DataInvalida(temp);

	data = data.substr(data.find('/') + 1);

	try{
		ano = stoi(data);
	}
	catch(...){
		throw DataInvalida(temp);
	}
	if(ano < 0 || ano > 2020)
		throw DataInvalida(temp);
}

Data::Data(int dia, int mes, int ano){
	this->dia = dia;
	this->mes = mes;
	this->ano = ano;
}

Data::Data(){
	dia = 1;
	mes = 1;
	ano = 1;
}

string Data::getData(){
	stringstream data;

	data << dia << "/" << mes << "/" << ano;
	return data.str();
}

void Data::operator = (Data data){
	dia = data.dia;
	mes = data.mes;
	ano = data.ano;
}

bool Data::operator == (Data data){
	return (dia == data.dia) && (mes == data.mes) && (ano == data.ano);
}

bool Data::operator < (const Data data) const{
	if (ano == data.ano)
	{
		if (mes == data.mes)
			return dia < data.dia;
		else
			return mes < data.mes;
	}
	else
		return ano < data.ano;
}
