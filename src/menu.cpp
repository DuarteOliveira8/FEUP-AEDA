#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "menu.h"

//---------------------------------------------------------------------------------------
//                                 VARIAVEIS GLOBAIS
//---------------------------------------------------------------------------------------

string ficheiroAvioes;
string ficheiroPassageirosCartao;
string ficheiroVoos;
string ficheiroTecnicos;

//---------------------------------------------------------------------------------------
//                                    CONSTRUTORES
//---------------------------------------------------------------------------------------

Menu::Menu(){

}

//---------------------------------------------------------------------------------------
//                                 LEITURA DE FICEHIROS
//---------------------------------------------------------------------------------------

void Menu::leitura_ficheiroAvioes(){
	string line;
	int codAviao;
	string modelo;
	unsigned int lotacao;
	float precoPorLugar;
	int periodicidadeManutencao;

	cout << "Introduza o ficheiro dos avioes (e.g: nomeFicheiro.txt): ";
	//cin >> ficheiroAvioes;
	ficheiroAvioes = "src/avioes.txt";

	ifstream ficheiro;
	ficheiro.open(ficheiroAvioes);

	while (ficheiro.fail())
	{
		cerr << "A abertura do ficheiro falhou.\n";
		cout << "Introduza aqui o ficheiro de avioes (e.g: nomeFicheiro.txt):\n";
		cin >> ficheiroAvioes;
		ficheiro.open(ficheiroAvioes);
	}

	while(!ficheiro.eof())
	{
		getline(ficheiro, line);

		modelo = line.substr(0, line.find('-') - 1);
		line = line.substr(line.find('-') + 2);

		codAviao = stoi(line.substr(0, line.find('-') - 1));
		line = line.substr(line.find('-') + 2);

		lotacao = stoi(line.substr(0, line.find('-') - 1));
		line = line.substr(line.find('-') + 2);

		precoPorLugar = stoi(line.substr(0, line.find('-') - 1));
		line = line.substr(line.find('-') + 2);

		periodicidadeManutencao = stoi(line.substr(0, line.find('-') - 1));
		line = line.substr(line.find('-') + 2);

		Data dataProxManutencao(line);

		Aviao aviao(codAviao, modelo, lotacao, precoPorLugar, periodicidadeManutencao, dataProxManutencao);

		companhia.avioes.insert(aviao);
	}

	ficheiro.close();
}

void Menu::leitura_ficheiroPassageirosCartao(){
	string line, nome, profissao;
	int numMedAno, id, ativo;

	cout << "Introduza o ficheiro dos passageiros com cartao (e.g: nomeFicheiro.txt): ";
	//cin >> ficheiroPassageirosCartao;
	ficheiroPassageirosCartao = "src/passageirosCartao.txt";

	ifstream ficheiro;
	ficheiro.open(ficheiroPassageirosCartao);

	while (ficheiro.fail())
	{
		cerr << "A abertura do ficheiro falhou.\n";
		cout << "Introduza aqui o ficheiro de Passageiros com cartao (e.g: nomeFicheiro.txt):\n";
		cin >> ficheiroPassageirosCartao;
		ficheiro.open(ficheiroPassageirosCartao);
	}

	while(!ficheiro.eof())
	{
		getline(ficheiro, line);

		ativo = stoi(line.substr(0, line.find('-') - 1));
		line = line.substr(line.find('-') + 2);

		nome = line.substr(0, line.find('-') - 1);
		line = line.substr(line.find('-') + 2);

		id = stoi(line.substr(0, line.find('-') - 1));
		line = line.substr(line.find('-') + 2);

		profissao = line.substr(0, line.find('-') - 1);
		line = line.substr(line.find('-') + 2);

		Data dataNascimento(line.substr(0, line.find('-') - 1));
		line = line.substr(line.find('-') + 2);

		numMedAno = stoi(line.substr(0, line.find('-') - 1));
		line = line.substr(line.find('-') + 2);

		Data dataUltimoVoo(line);

		PassageiroCartao* pc = new PassageiroCartao(nome, profissao, dataNascimento, numMedAno, id, dataUltimoVoo);

		if (!ativo){
			companhia.passageirosInativos.insert(pc);
		}
		else{
			companhia.passageirosCartao.push_back(pc);
		}
	}

	ficheiro.close();
}

void Menu::leitura_ficheiroVoos(){
	string line, data, nome, destino;
	int vagas, id, codAviao;
	Passageiro passageiro;
	vector<Passageiro *> passageiros;
	bool exist = false;

	cout << "Introduza o ficheiro dos voos (e.g: nomeFicheiro.txt): ";
	//cin >> ficheiroVoos;
	ficheiroVoos = "src/voos.txt";

	ifstream ficheiro;
	ficheiro.open(ficheiroVoos);

	while (ficheiro.fail())
	{
		cerr << "A abertura do ficheiro falhou.\n";
		cout << "Introduza aqui o ficheiro de voos (e.g: nomeFicheiro.txt):\n";
		cin >> ficheiroVoos;
		ficheiro.open(ficheiroVoos);
	}

	while(!ficheiro.eof())
	{
		Aviao aviao;

		getline(ficheiro, line);
		codAviao = stoi(line.substr(0, line.find('-') - 1));
		BSTItrIn<Aviao> it(companhia.avioes);
		while(!it.isAtEnd())
		{
			if (codAviao == it.retrieve().getCodAviao())
			{
				aviao = it.retrieve();
				break;
			}
			it.advance();
		}
		line = line.substr(line.find('-') + 2);

		vagas = stoi(line.substr(0, line.find('-') - 1));
		line = line.substr(line.find('-') + 2);

		data = line.substr(0, line.find('-') - 1);
		Data dataVoo(data);
		line = line.substr(line.find('-') + 2);

		destino = line;

		getline(ficheiro, line);
		while (!((line == "-") || ficheiro.eof()))
		{
			getline(ficheiro, line);
			if (line == "-")
			{
				continue;
			}

			nome = line.substr(0, line.find('-') - 1);
			line = line.substr(line.find('-') + 2);

			id = stoi(line);

			exist = false;
			for (size_t i = 0; i < companhia.passageirosCartao.size(); i++)
			{
				if (id == companhia.passageirosCartao.at(i)->getId())
				{
					passageiros.push_back(companhia.passageirosCartao.at(i));

					exist = true;
					break;
				}
			}

			if (!exist)
			{
				Passageiro* p = new Passageiro(nome, id);
				passageiros.push_back(p);
			}
		}

		Voo* v = new Voo(aviao, vagas, dataVoo, passageiros, destino);

		companhia.voos.push_back(v);
		passageiros.clear();
	}

	ficheiro.close();
}

void Menu::leitura_ficheiroTecnicos(){
	string line, especialidade;
	int id;
	int codAviao;
	Aviao aviao;
	vector<string> especialidades;

	cout << "Introduza o ficheiro dos tecnicos (e.g: nomeFicheiro.txt): ";
	//cin >> ficheiroTecnicos;
	ficheiroTecnicos = "src/tecnicos.txt";

	ifstream ficheiro;
	ficheiro.open(ficheiroTecnicos);

	while (ficheiro.fail())
	{
		cerr << "A abertura do ficheiro falhou.\n";
		cout << "Introduza aqui o ficheiro dos tecnicos (e.g: nomeFicheiro.txt):\n";
		cin >> ficheiroTecnicos;
		ficheiro.open(ficheiroTecnicos);
	}

	while(!ficheiro.eof())
	{
		getline(ficheiro, line);

		id = stoi(line.substr(0, line.find('-') - 1));
		line = line.substr(line.find('-') + 2);

		codAviao = stoi(line);
		BSTItrIn<Aviao> it(companhia.avioes);
		while(!it.isAtEnd())
		{
			if (codAviao == it.retrieve().getCodAviao())
			{
				aviao = it.retrieve();
				break;
			}
			it.advance();
		}

		getline(ficheiro, line);
		while (!((line == "-") || ficheiro.eof()))
		{
			getline(ficheiro, line);
			if (line == "-")
			{
				break;
			}

			especialidade = line;
			especialidades.push_back(especialidade);
		}

		Tecnico tecnico(especialidades, id, aviao);

		companhia.tecnicos.push(tecnico);
		especialidades.clear();
	}

	ficheiro.close();
}


//---------------------------------------------------------------------------------------
//                                   MENU PRINCIPAL
//---------------------------------------------------------------------------------------

void Menu::menu_principal() {
	int opcao;

	do {
		clearScreen();
		cout << "+------------------------------------------------------------------------------+\n";
		cout << "|                               MENU PRINCIPAL                                 |\n";
		cout << "| 1) Menu de avioes                                                            |\n";
		cout << "| 2) Menu de voos                                                              |\n";
		cout << "| 3) Menu de passageiros                                                       |\n";
		cout << "| 4) Menu de tecnicos                                                          |\n";
		cout << "| 5) Menu de Reservas                                                          |\n";
		cout << "| 6) Terminar                                                                  |\n";
		cout << "+------------------------------------------------------------------------------+\n";

		opcao = opcaoMenu(6);
		cout << endl;
		switch (opcao)
		{
		case 1:
			menu_avioes();
			break;

		case 2:
			menu_voos();
			break;

		case 3:
			menu_passageiros();
			break;

		case 4:
			menu_tecnicos();
			break;

		case 5:
			menu_reservas();
			break;

		case 6:
			cout << "As suas alteracoes foram guardadas com sucesso! Volte sempre!\n";
			break;
		}
	}while (opcao != 6);
}


//---------------------------------------------------------------------------------------
//                                     MENU AVIOES
//---------------------------------------------------------------------------------------

void Menu::menu_avioes() {
	int opcao;

	do {
		clearScreen();
		cout << "+------------------------------------------------------------------------------+\n";
		cout << "|                                 MENU AVIOES                                  |\n";
		cout << "| 1) Adicionar aviao                                                           |\n";
		cout << "| 2) Alterar aviao                                                             |\n";
		cout << "| 3) Eliminar aviao                                                            |\n";
		cout << "| 4) Menu de visualizacao de avioes                                            |\n";
		cout << "| 5) Voltar atras                                                              |\n";
		cout << "+------------------------------------------------------------------------------+\n";

		opcao = opcaoMenu(5);
		cout << endl;
		switch (opcao)
		{
		case 1:
			companhia.adicionaAviao();
			break;

		case 2:
			companhia.alteraAviao();
			break;

		case 3:
			companhia.removeAviao();
			break;

		case 4:
			menu_visualizacao_avioes();
			break;

		case 5:
			break;
		}
	} while(opcao != 5);
}

void Menu::menu_visualizacao_avioes(){
	int opcao;

	do {
		clearScreen();
		cout << "+------------------------------------------------------------------------------+\n";
		cout << "|                         MENU PASSAGEIROS COM CARTAO                          |\n";
		cout << "| 1) Visualizacao de avioes existentes                                         |\n";
		cout << "| 2) Visualizacao das proximas manutencoes                                     |\n";
		cout << "| 3) Voltar atras                                                              |\n";
		cout << "+------------------------------------------------------------------------------+\n";

		opcao = opcaoMenu(3);
		cout << endl;
		switch (opcao)
		{
		case 1:
			companhia.visualizaAvioes();
			break;

		case 2:
			companhia.visualizaProximasManutencoes();
			break;

		case 3:
			break;
		}
	} while (opcao != 3);
}


//---------------------------------------------------------------------------------------
//                                  MENU PASSAGEIROS
//---------------------------------------------------------------------------------------

void Menu::menu_passageiros(){
	int opcao;

	do {
		clearScreen();
		cout << "+------------------------------------------------------------------------------+\n";
		cout << "|                         MENU PASSAGEIROS COM CARTAO                          |\n";
		cout << "| 1) Adicionar passageiro                                                      |\n";
		cout << "| 2) Alterar passageiro                                                        |\n";
		cout << "| 3) Eliminar passageiro                                                       |\n";
		cout << "| 4) Visualizacao de passageiros                                               |\n";
		cout << "| 5) Menu de passageiros inativos                                              |\n";
		cout << "| 6) Voltar atras                                                              |\n";
		cout << "+------------------------------------------------------------------------------+\n";

		opcao = opcaoMenu(6);
		cout << endl;
		switch (opcao)
		{
		case 1:
			companhia.adicionaPassageiroCartao();
			break;

		case 2:
			companhia.alteraPassageiroCartao();
			break;

		case 3:
			companhia.removePassageiroCartao();
			break;

		case 4:
			companhia.visualizaPassageirosCartao();
			break;

		case 5:
			menu_passageiros_inativos();
			break;

		case 6:
			break;
		}
	} while (opcao != 6);
}

void Menu::menu_passageiros_inativos(){
	int opcao;

	do {
		clearScreen();
		cout << "+------------------------------------------------------------------------------+\n";
		cout << "|                     MENU PASSAGEIROS COM CARTAO INATIVOS                     |\n";
		cout << "| 1) Alterar passageiro inativos                                               |\n";
		cout << "| 2) Visualizar passageiros inativos                                           |\n";
		cout << "| 3) Remover passageiros inativos                                              |\n";
		cout << "| 4) Voltar atras                                                              |\n";
		cout << "+------------------------------------------------------------------------------+\n";

		opcao = opcaoMenu(4);
		cout << endl;
		switch (opcao)
		{
		case 1:
			companhia.alteraPassageiroInativo();
			break;

		case 2:
			companhia.visualizaPassageirosInativos();
			break;

		case 3:
			companhia.removePassageiroInativo();
			break;

		case 4:
			break;
		}
	} while (opcao != 4);
}


//---------------------------------------------------------------------------------------
//                                    MENU VOOS
//---------------------------------------------------------------------------------------

void Menu::menu_voos(){
	int opcao;

	do {
		clearScreen();
		cout << "+------------------------------------------------------------------------------+\n";
		cout << "|                                 MENU VOOS                                    |\n";
		cout << "| 1) Adicionar voo                                                             |\n";
		cout << "| 2) Alterar voo                                                               |\n";
		cout << "| 3) Eliminar voo                                                              |\n";
		cout << "| 4) Visualizacao de voos                                                      |\n";
		cout << "| 5) Voltar atras                                                              |\n";
		cout << "+------------------------------------------------------------------------------+\n";

		opcao = opcaoMenu(5);
		cout << endl;
		switch (opcao)
		{
		case 1:
			companhia.adicionaVoo();
			break;

		case 2:
			companhia.alteraVoo();
			break;

		case 3:
			companhia.removeVoo();
			break;

		case 4:
			companhia.visualizaVoos();
			break;

		case 5:
			break;
		}
	} while (opcao != 5);
}


//---------------------------------------------------------------------------------------
//                                   MENU TECNICOS
//---------------------------------------------------------------------------------------

void Menu::menu_tecnicos(){
	int opcao;

	do {
		clearScreen();
		cout << "+------------------------------------------------------------------------------+\n";
		cout << "|                                 MENU VOOS                                    |\n";
		cout << "| 1) Adicionar tecnico                                                         |\n";
		cout << "| 2) Alterar tecnico                                                           |\n";
		cout << "| 3) Eliminar tecnico                                                          |\n";
		cout << "| 4) Visualizacao de tecnicos                                                  |\n";
		cout << "| 5) Voltar atras                                                              |\n";
		cout << "+------------------------------------------------------------------------------+\n";

		opcao = opcaoMenu(5);
		cout << endl;
		switch (opcao)
		{
		case 1:
			companhia.adicionaTecnico();
			break;

		case 2:
			companhia.alteraTecnico();
			break;

		case 3:
			companhia.removeTecnico();
			break;

		case 4:
			companhia.visualizaTecnicos();
			break;

		case 5:
			break;
		}
	} while (opcao != 5);
}


//---------------------------------------------------------------------------------------
//                                   MENU RESERVAS
//---------------------------------------------------------------------------------------

void Menu::menu_reservas(){
	int opcao;

	do {
		clearScreen();
		cout << "+------------------------------------------------------------------------------+\n";
		cout << "|                               MENU RESERVAS                                  |\n";
		cout << "| 1) Reservar lugar em voo comercial                                           |\n";
		cout << "| 2) Alugar voo                                                                |\n";
		cout << "| 3) Devolucao                                                                 |\n";
		cout << "| 4) Voltar atras                                                              |\n";
		cout << "+------------------------------------------------------------------------------+\n";

		opcao = opcaoMenu(4);
		cout << endl;
		switch (opcao)
		{
		case 1:
			companhia.reservaComercial();
			break;

		case 2:
			companhia.alugaVoo();
			break;

		case 3:
			companhia.devolucao();
			break;

		case 4:
			break;
		}
	} while (opcao != 4);
}


//---------------------------------------------------------------------------------------
//                                ESCRITA DE FICEHIROS
//---------------------------------------------------------------------------------------

void Menu::escrita_ficheiroAvioes(){
	ofstream ficheiro;
	stringstream line;

	ficheiro.open(ficheiroAvioes);

	BSTItrIn<Aviao> it(companhia.avioes);
	while(!it.isAtEnd())
	{
		line << it.retrieve().getModelo();
		line << " - ";
		line << it.retrieve().getCodAviao();
		line << " - ";
		line << it.retrieve().getLotacao();
		line << " - ";
		line << it.retrieve().getPrecoPorLugar();
		line << " - ";
		line << it.retrieve().getPeriodicidadeManutencao();
		line << " - ";
		line << it.retrieve().getDataProxManutencao();
		it.advance();
		if (!it.isAtEnd())
		{
			line << endl;
		}

		ficheiro << line.str();
		line.str("");
	}

	ficheiro.close();
}

void Menu::escrita_ficheiroPassageirosCartao(){
	ofstream ficheiro;
	stringstream line;

	ficheiro.open(ficheiroPassageirosCartao);

	for (size_t i = 0; i < companhia.passageirosCartao.size(); i++)
	{
		line << "1";
		line << " - ";
		line << companhia.passageirosCartao.at(i)->getNome();
		line << " - ";
		line << companhia.passageirosCartao.at(i)->getId();
		line << " - ";
		line << companhia.passageirosCartao.at(i)->getProfissao();
		line << " - ";
		line << companhia.passageirosCartao.at(i)->getDataNascimento().getData();
		line << " - ";
		line << companhia.passageirosCartao.at(i)->getNMedAno();
		line << " - ";
		line << companhia.passageirosCartao.at(i)->getDataUltimoVoo().getData();

		if (!companhia.passageirosInativos.empty() || (i != companhia.passageirosCartao.size() - 1))
			line << endl;

		ficheiro << line.str();
		line.str("");
	}

	unordered_set<PassageiroCartao*,hstr,eqstr>::iterator it = companhia.passageirosInativos.begin();
	while (it != companhia.passageirosInativos.end())
	{
		line << "0";
		line << " - ";
		line << (*it)->getNome();
		line << " - ";
		line << (*it)->getId();
		line << " - ";
		line << (*it)->getProfissao();
		line << " - ";
		line << (*it)->getDataNascimento().getData();
		line << " - ";
		line << (*it)->getNMedAno();
		line << " - ";
		line << (*it)->getDataUltimoVoo().getData();

		it++;
		if (it != companhia.passageirosInativos.end())
			line << endl;

		ficheiro << line.str();
		line.str("");
	}

	ficheiro.close();
}

void Menu::escrita_ficheiroVoos(){
	ofstream ficheiro;
	stringstream line;

	ficheiro.open(ficheiroVoos);

	for (size_t i = 0; i < companhia.voos.size(); i++)
	{
		line << companhia.voos.at(i)->getAviao().getCodAviao();
		line << " - ";
		line << companhia.voos.at(i)->getVagas();
		line << " - ";
		line << companhia.voos.at(i)->getDataVoo().getData();
		line << " - ";
		line << companhia.voos.at(i)->getDestino() << endl;
		ficheiro << line.str();
		line.str("");

		line << "Passageiros:";
		ficheiro << line.str();
		line.str("");
		for (size_t k = 0; k < companhia.voos.at(i)->getPassageiros().size(); k++)
		{
			line << endl << companhia.voos.at(i)->getPassageiros().at(k)->getNome();
			line << " - ";
			line << companhia.voos.at(i)->getPassageiros().at(k)->getId();
			ficheiro << line.str();
			line.str("");
		}
		if (i != companhia.voos.size() - 1)
		{
			line << "\n-\n";
			ficheiro << line.str();
			line.str("");
		}
	}

	ficheiro.close();
}

void Menu::escrita_ficheiroTecnicos(){
	ofstream ficheiro;
	stringstream line;
	Tecnico tecnico;

	ficheiro.open(ficheiroTecnicos);

	while (!companhia.tecnicos.empty())
	{
		Tecnico tecnico = companhia.tecnicos.top();
		companhia.tecnicos.pop();
		line << tecnico.getId();
		line << " - ";
		line << tecnico.getAviao().getCodAviao() << endl;
		ficheiro << line.str();
		line.str("");

		line << "Especialidades:";
		ficheiro << line.str();
		line.str("");
		for (size_t k = 0; k < tecnico.getEspecialidades().size(); k++)
		{
			line << endl << tecnico.getEspecialidades().at(k);
			ficheiro << line.str();
			line.str("");
		}
		if (!companhia.tecnicos.empty())
		{
			line << "\n-\n";
			ficheiro << line.str();
			line.str("");
		}
	}

	ficheiro.close();
}
