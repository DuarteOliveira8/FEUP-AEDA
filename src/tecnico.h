#ifndef TECNICO_H_
#define TECNICO_H_

#include <iostream>
#include <string>
#include <vector>
#include "auxiliares.h"
#include "aviao.h"

using namespace std;

/** Class Tecnico
 *
 * Estrutura de um tecnico, os seus atributos e funcoes.
 *
 */
class Tecnico {
	vector<string> especialidades; /**< vetor de especialidades do tecnico**/
	int id; /**< id do tecnico**/
	Aviao aviao; /**< aviao atribuido ao tecnico**/
public:
	/**
	 * @brief Construtor vazio da classe tecnico
	 */
	Tecnico();

	/**
	 * @brief Construtor da classe tecnico
	 *
	 * @param vetor de especialidades
	 * @param id do tecnico
	 * @param aviao associado ao tecnico
	 */
	Tecnico(vector<string> especialidades, int id, Aviao aviao);

	vector<string> getEspecialidades() const;
	int getId() const;
	Data getProxManutencao() const;
	Aviao getAviao() const;

	/**
	 * @brief Funcao de alteracao de um tecnico
	 */
	void alteraTecnico(BST<Aviao> avioes, vector<Tecnico> tecnicosTemp);
	bool operator < (const Tecnico t) const;
	void operator = (Tecnico t);
};

#endif /*TECNICO_H_*/
