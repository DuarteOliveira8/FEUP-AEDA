#ifndef VOO_H_
#define VOO_H_

#include <iostream>
#include <string>
#include <vector>
#include "aviao.h"

/** Class Voo
 *
 *
 */
class Voo {
	Aviao aviao; /**< Cada voo tem um unico aviao. */
	unsigned int vagas; /**< Lugares que ainda podem ser ocupados no aviao. */
	vector<Passageiro *> passageiros; /**< Vetor que guarda os passageiros de um certo voo. */
	Data dataVoo; /**< Data a que se vai realizar o voo. */
	string destino; /**< Destino do voo. */
public:
	/**
	 * Construtor de um Voo (com passageiros)
	 *
	 * \param aviao em que se vai realizar o voo.
	 * \param vagas no aviao
	 * \param dataVoo - data em que se vai realizar o voo.
	 * \param passageiros do voo
	 * \param destino do voo
	 */
	Voo(Aviao aviao, unsigned int vagas, Data dataVoo, vector<Passageiro *> passageiros, string destino);

	/**
	 * Construtor de um Voo (sem passageiros)
	 *
	 * \param aviao em que se vai realizar o voo.
	 * \param vagas no aviao
	 * \param dataVoo - data em que se vai realizar o voo.
	 * \param passageiros do voo
	 * \param destino do voo
	 */
	Voo(Aviao aviao, unsigned int vagas, Data dataVoo, string destino);
	float getPreco() const; /**< Funcao que retorna o preco do voo. */
	Aviao getAviao() const; /**< Funcao que retorna o aviao correspondente ao voo. */
	unsigned int getVagas() const; /**< Funcao que retorna o numero de vagas do voo. */
	void decrementaVagas(); /**< Funcao que decrementa o numero de vagas por 1. */
	void incrementaVagas(); /**< Funcao que incrementa o numero de vagas por 1. */
	vector<Passageiro *> getPassageiros() const; /**< Funcao que retorna o vetor de passageiros do voo. */
	Data getDataVoo() const; /**< Funcao que retorna a data em que se vai realizar o voo. */
	string getDestino() const; /**< Funcao que retorna o destino do voo. */
	void adicionaPassageiro(Passageiro* p); /**< Funcao que adiciona um passageiro ao vetor de passageiros do voo. */
	void removePassageiro(int id); /**< Funcao que remove um passageiro do vetor de passageiros do voo. */
	void alteraVoo();
};

#endif /*VOO_H_*/
