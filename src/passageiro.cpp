#include <iostream>
#include <string>
#include <vector>
#include "voo.h"

using namespace std;

//---------------------------------------------------------------------------------------
//                         FUNCOES DE PASSAGEIROS NORMAIS
//---------------------------------------------------------------------------------------

Passageiro::Passageiro(){

}

Passageiro::Passageiro(string nome, int id){
	this->nome = nome;
	this->id = id;
}

string Passageiro::getNome() const{
	return nome;
}

int Passageiro::getId() const {
	return id;
}

float Passageiro::calculaPreco(int preco) const{
	return preco;
}

void Passageiro::operator = (Passageiro p){
	nome = p.getNome();
	id = p.getId();
}


//---------------------------------------------------------------------------------------
//                         FUNCOES DE PASSAGEIROS COM CARTAO
//---------------------------------------------------------------------------------------

PassageiroCartao::PassageiroCartao(string nome, string profissao, Data dataNascimento, float nMedAno, int id, Data ultimoVoo) : Passageiro(nome, id){
	this->profissao = profissao;
	this->dataNascimento = dataNascimento;
	this->nMedAno = nMedAno;
	this->ultimoVoo = ultimoVoo;
}

string PassageiroCartao::getProfissao() const{
	return profissao;
}

Data PassageiroCartao::getDataNascimento() const{
	return dataNascimento;
}

int PassageiroCartao::getNMedAno() const{
	return nMedAno;
}

Data PassageiroCartao::getDataUltimoVoo() const{
	return ultimoVoo;
}

float PassageiroCartao::calculaPreco(int preco) const{
	if(nMedAno >= 100)
		return 0;
	else
		return preco * ((100 - nMedAno) / 100);
}

void PassageiroCartao::incrementaNMedAno(){
	nMedAno++;
}

void PassageiroCartao::decrementaNMedAno() {
	nMedAno--;
}

void PassageiroCartao::operator = (PassageiroCartao p){
	nome = p.getNome();
	profissao = p.getProfissao();
	dataNascimento = p.getDataNascimento();
	nMedAno = p.getNMedAno();
}

void PassageiroCartao::alteraPassageiroCartao(){
	int opcao;
	bool valid;
	string dataN;
	Data data;
	string dataV;

	do{
		valid = false;
		cout << "+------------------------------------------------------------------------------+\n";
		cout << "| Qual elemento deseja alterar?                                                |\n";
		cout << "| 1) Nome                                                                   	|\n";
		cout << "| 2) Profissao                                                                 |\n";
		cout << "| 3) Data Nascimento                                                           |\n";
		cout << "| 4) Numero Medio Viagens por Ano                                              |\n";
		cout << "| 5) Data Ultimo Voo                                                           |\n";
		cout << "| 6) Terminar                                                                  |\n";
		cout << "+------------------------------------------------------------------------------+\n";

		opcao = opcaoMenu(6);
		cout << endl;
		switch(opcao)
		{
		case 1:
				cout << "Introduza o nome do passageiro : ";
				getline(cin, nome);
				break;

		case 2:
				cout << "Introduza a profissao do passageiro : ";
				getline(cin,profissao);
				break;

		case 3:
				while(!valid){
					cout << "Introduza a data de nascimento do passageiro : ";
					valid = true;
					cin >> dataN;
					try{
						data = Data(dataN);
					}
					catch (DataInvalida &datai){
						valid = false;
						cout << datai;
					}
				}

				dataNascimento = data;
				break;

		case 4:
			cout << "Introduza o numero medio de viagens por ano do passageiro : ";
			nMedAno = Valid_Cin();
			break;

		case 5:
			cout << "Introduza a data do ultimo voo do passageiro : ";
			while(!valid){
				valid = true;
				cin >> dataV;
				try{
					data = Data(dataV);
				}
				catch (DataInvalida &datai){
					valid = false;
					cout << datai;
				}
			}

			ultimoVoo = data;
			break;

		}
	}while (opcao != 6);
}

