#ifndef COMPANHIA_H_
#define COMPANHIA_H_

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_set>
#include "BST.h"
#include "voo.h"
#include "tecnico.h"


using namespace std;

/** Class Companhia
 * A classe Companhia é a classe principal do nosso projeto.
 * Contem os vetores de avioes, passageiros com cartao e voos da companhia.
 * Contem tambem as funcoes de gestao da empresa, tal como as funcoes de reservas e devolucoes, as funcoes de adicionar, remover
 * e visualizar avioes, passageiros com cartao e voos.
 */
class Companhia {
public:

	BST<Aviao> avioes; /**< Vetor onde estao armazenados os avioes existentes. */

	vector<PassageiroCartao *> passageirosCartao; /**< Vetor onde estao armazenados os passageiros com cartao. */

	unordered_set<PassageiroCartao *,hstr,eqstr> passageirosInativos; /**< Tabela de dispersao onde estao armazenados os passageiros inativos. */

	vector<Voo *> voos; /**< Vetor onde estao armazenados os voos. */

	priority_queue<Tecnico> tecnicos; /**< Fila de prioridade onde estao aramzenados os tecnicos. */


	/**
	 * @brief Construtor (vazio) da Companhia.
	 */
	Companhia();

	/*	FUNCOES DE AVIOES	*/

	/**
	 * @brief Esta funcao adiciona um novo aviao a BST dos avioes e posteriormente ao ficheiro dos avioes.
	 * E pedido ao utilizador para introduzir o codigo do aviao a adicionar, e verifica se tem 8 digitos (formato do codigo de aviao).
	 * Se o aviao ja existir, pergunta ao utilizador se pretende tentar adicionar outro, ou voltar atras.
	 * Se nao existir, pede as outras informacoes do aviao. No caso do modelo, se ja existir, ele utiliza as informaçoes desse
	 * modelo, se nao pede as informacoes do modelo. Se for adicionado com sucesso, informa o utilizador do sucesso da operacao.
	 */
	void adicionaAviao();

	/**
	 * @brief Esta funcao altera um aviao presente na BST dos avioes.
	 * É pedido ao utilizador o codigo do aviao que deseja alterar e é chamada a funcao de alteracao caso exista. Se nao existir,
	 * pergunta se quer voltar atras ou nao.
	 */
	void alteraAviao();

	/**
	 * @brief Esta funcao remove um aviao da BST dos avioes e posteriormente do ficheiro dos avioes.
	 * E pedido ao utilizador para introduzir o codigo do aviao a remover, e verifica
	 * se o aviao existe na BST dos avioes.
	 * Se o aviao nao existir, pergunta ao utilizador se pretende tentar remover outro, ou voltar atras.
	 * Se for removido com sucesso, informa o utilizador do sucesso da operacao.
	 */
	void removeAviao();

	/**
	 * @brief Esta funcao imprime na consola a lista de avioes, mostrando os seus codigos, lotacao e preco por lugar, periodicidade de manutencao
	 * e a data da proxima manutencao.
	 */
	void visualizaAvioes();

	/**
	 * @brief Esta funcao imprime na consola a lista de avioes, mostrando as datas das proximas
	 * manutencoes respetivas.
	 */
	void visualizaProximasManutencoes();

	/*	FUNCOES DE PASSAGEIROS COM CARTAO	*/

	/**
	 * @brief Esta funcao adiciona um passageiro com cartao a tabela de dispersao de passageiros com cartao inativos pois ainda nao comprou
	 * nenhum bilhete.
	 * Primeiro, verifica se o id do passageiro tem efetivamente 8 digitos,
	 * ou seja, se esta entre 10000000 e 9999999.
	 * Depois verifica se o passageiro ja existe na tabela de dispersao dos passageiros.
	 * Se existir, pergunta se quer tentar introduzir outro id, ou voltar atras.
	 * Se nao existir, adiciona a tabela de dispersao de passageiros com cartao, informando o utilizador
	 * do sucesso da operacao.
	 */
	void adicionaPassageiroCartao();

	/**
	 * @brief Esta funcao altera um passageiro com cartao presente no vetor dos passageiros com cartao.
	 * É pedido ao utilizador o id do passageiro que deseja alterar e é chamada a funcao de alteracao caso exista. Se nao existir,
	 * pergunta se quer voltar atras ou nao.
	 */
	void alteraPassageiroCartao();

	/**
	 * @brief Esta funcao remove um passageiro com cartao do vetor de passageiros com cartao.
	 * Primeiro, verifica se o id do passageiro tem efetivamente 8 digitos,
	 * ou seja, se esta entre 10000000 e 9999999.
	 * Depois verifica se o passageiro existe no vetor dos passageiros.
	 * Se existir, remove o passageiro com cartao do vetor, informando o utilizador
	 * do sucesso da operacao.
	 * Se nao existir, pergunta ao utilizador se pretende tentar introduzir outro id, ou
	 * voltar atras.
	 */
	void removePassageiroCartao();

	/**
	 * @brief Esta funcao imprime na consola a lista de passageiros com cartao, mostrando os seus nomes,
	 * id, profissao, data de nascimento e numero medio de viagens por ano.
	 */
	void visualizaPassageirosCartao();

	/**
	 * @brief Esta funcao altera um passageiro com cartao presente na tabela de dispersao dos passageiros com cartao inativos.
	 * É pedido ao utilizador o id do passageiro que deseja alterar e é chamada a funcao de alteracao caso exista. Se nao existir,
	 * pergunta se quer voltar atras ou nao.
	 */
	void alteraPassageiroInativo();

	/**
	 * @brief Esta funcao imprime na consola a lista de passageiros com cartao inativos, mostrando
	 * os seus nomes, id, profissao, data de nascimento e numero medio de viagens por ano.
	 */
	void visualizaPassageirosInativos();

	/**
	 * @brief Esta funcao remove um passageiro com cartao da tabela de dispersao de passageiros com cartao inativos.
	 * Primeiro, verifica se o id do passageiro tem efetivamente 8 digitos,
	 * ou seja, se esta entre 10000000 e 9999999.
	 * Depois verifica se o passageiro existe na tabela de dispersao de passageiros com cartao inativos.
	 * Se existir, remove o passageiro com cartao da tabela, informando o utilizador do sucesso da operacao.
	 * Se nao existir, pergunta ao utilizador se pretende tentar introduzir outro id, ou voltar atras.
	 */
	void removePassageiroInativo();

	/*	FUNCOES DE VOOS	*/

	/**
	 * @brief Esta funcao adiciona um voo ao vetor de voos.
	 * Primeiro, pede ao utilizador para introduzir a data do voo,
	 * para verificar se e valida,e para mostrar os avioes disponiveis nessa data.
	 * Depois pede o codigo do aviao, para verificar se esta disponivel. Se nao estiver,
	 * informa o utilizador e pergunta se pretende introduzir outro codigo, ou voltar atras.
	 * Se estiver disponivel, adiciona o voo ao vetor de voos, e informa o utilizador do sucesso da operacao.
	 */
	void adicionaVoo();

	/**
	 * @brief Esta funcao altera um voo presente no vetor dos voos.
	 * É pedido ao utilizadorpara introduzir a data do voo, para verificar se e valida, depois pede o codigo do aviao do voo que deseja
	 * alterar e é chamada a funcao de alteracao caso exista. Se nao existir,
	 * pergunta se quer voltar atras ou nao.
	 */
	void alteraVoo();

	/**
	 * @brief Esta funcao remove um voo do vetor de voos.
	 * Primeiro, pede ao utilizador para introduzir a data do voo,
	 * para verificar se e valida. Depois pede o codigo do aviao,
	 * para verificar se existe. Se nao existir, informa o utilizador e
	 * pergunta se pretende introduzir outro codigo, ou voltar atras.
	 * Se existir, remove o voo do vetor de voos, e informa o utilizador do sucesso da operacao.
	 */
	void removeVoo();

	/**
	 * @brief Esta funcao imprime na consola a lista de voos, mostrando os seus codigos,
	 * vagas, datas de voo e destino.
	 */
	void visualizaVoos();

	/*	FUNCOES DE RESERVAS	 */

	/**
	 * @brief Esta funcao permite ao utilizador de reservar um lugar num voo especifico.
	 * Começa por escolher no vetor de voos os voos que ainda tem vagas disponiveis e imprimi-los no ecra.
	 * De seguida pede ao utilizador para indicar o destino e a data do voo em que deseja viajar.
	 * Se o voo nao pertencer a lista de voos disponiveis, o programa pergunta se o utilizador quer voltar a tras ou introduzir
	 * um novo destino e data.
	 * Se pertencer, pede nome e id do passageiro. Se o id ja fizer parte da lista de passageiros, o programa avisa o utilizador
	 * e pergunta se ele quer voltar atras ou introduzir um novo id e nome.
	 * Se nao, procura no vetor de passageiros com cartao pelo id. Se encontrar, verifica se o nome e igual ao da base de dados. Se
	 * nao for, pergunta se quer substituir. Se nao quiser pergunta se quer voltar atras ou voltar a introduzir a informacao. Se
	 * quiser, adiciona o passageiro ao voo, incrementa o numero medio de voos por ano do passageiro e mostra o valor a pagar
	 * no ecra em funcao do numero medio de voos.
	 * Se o passageiro pertencer a tabela de dispersao dos passageiros inativos é retirado de la e adicionado ao vetor de passageiros ativos.
	 * Se nao encontrar, cria um novo passageiro normal, adiciona ao vetor de passageiros e mostra o valor a pagar no ecra.
	 */
	void reservaComercial();

	/**
	 * @brief Esta funcao permite ao de alugar um aviao.
	 * No inicio, o programa pede ao utilizador a data do voo que pretende efetuar o aluguer.
	 * E depois o programa escolhe no vetor de avioes, os avioes que estao disponiveis naquele dia e imprime-os no ecra.
	 * Se nao houver, volta atras. Se nao, pede ao utilizador um codigo de um aviao da lista de avioes disponiveis.
	 * Se este nao existir pergunta se quer voltar atras ou voltar a introduzir um codigo de um aviao.
	 * Se nao, pede ao utilizador o nome e o id do passageiro e pesquisa se o id existe no vetor de passageiros cartao.
	 * Se existir mas o nome esta errado, pergunta se quer substituir. Se nao quiser pergunta se quer voltar atras ou
	 * voltar a introduzir a informacao. Se quiser, cria um novo voo com um unico passageiro e 0 vagas, adicionando ao vetor de
	 * voos.
	 * Se o passageiro pertencer a tabela de dispersao dos passageiros inativos é retirado de la e adicionado ao vetor de passageiros ativos.
	 * Se nao existir, cria um novo passageiro com os dados fornecidos e um voo novo com 0 vagas e um unico passageiro.
	 */
	void alugaVoo();

	/**
	 * @brief Esta funcao permite ao utilizador de devolver uma reserva.
	 * Se o vetor de voos estiver vazio, volta atras, se nao, imprime no ecra todos os voos.
	 * De seguida, pede ao utilizador a data e destino do voo a que pretende efetuar a devolucao.
	 * Depois pede ao utilizador o id do passageiro.
	 * E pesquisa no vetor de voos se esses dados equivalem a algum voo dos vetores de voos. Se nao encontrar nenhum voo com esses
	 * dados, pergunta se quer voltar atras ou inserir novos dados.
	 * Se encontrar, verifica se o id faz parte desse voo. Se nao fizer, continua a procurar por outros voos com a mesma data e
	 * destino. Se nenhum dos voos com os dados especificados conter o passageiro com o id introduzido, o programa pergunta se
	 * quer voltar atras ou introduzir um novo.
	 * Se o id corresponder a algum dos passageiros tem dois casos. caso do voo alugado ou caso do voo comercial. No alugado,
	 * retira o voo da lista de voos e no caso do voo comercial retira o passageiro da lista. Se for um passageiro com cartao,
	 * tem de decrementar o numero medio de voos por ano.
	 * Se o passageiro tiver uma data do ultimo voo de ha um ano, é retirado do vetor de passageiros ativos e posto na tabela de dispersao.
	 */
	void devolucao();

	/**
	 * @brief Esta funcao pede todas as informacoes necessarias para criar um tecnico,
	 * verifica se estas informacoes ja sao repetidas ou nao, e se nao, adiciona um
	 * novo tecnico.
	 */
	void adicionaTecnico();

	/**
	 * @brief Esta funcao pede um ID de um tecnico e chama a funcao de alteracao.
	 */
	void alteraTecnico();

	/**
	 * @brief Esta funcao pede um ID de um tecnico, verifica se ele existe,
	 * e se existir, remove o tecnico da fila de prioridade.
	 */
	void removeTecnico();

	/**
	 * @brief Esta funcao imprime no ecra todos os tecnicos.
	 */
	void visualizaTecnicos();
};

#endif /*COMPANHIA_H_*/
