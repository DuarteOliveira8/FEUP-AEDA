#ifndef MENU_H_
#define MENU_H_

#include <iostream>
#include <string>
#include <vector>
#include "companhia.h"

using namespace std;

/** Class Menu
 *
 * Estrutura de todos os menus utilizados no programa.
 *
 */
class Menu {
public:
	Companhia companhia; /**< Objeto Companhia que contem todos os vetores principais que iremos utilizar. */
	Menu(); /**< Construtor vazio do Menu. */

	void leitura_ficheiroAvioes(); /**< Funcao que faz a leitura do ficheiro dos avioes e coloca os dados no vetor dos avioes. */
	void leitura_ficheiroPassageirosCartao(); /**< Funcao que faz a leitura do ficheiro dos passageiros com cartao e coloca os dados no vetor dos passageiros com cartao. */
	void leitura_ficheiroVoos(); /**< Funcao que faz a leitura do ficheiro dos voos e coloca os dados no vetor dos voos. */
	void leitura_ficheiroTecnicos(); /**< Funcao que faz a leitura do ficheiro dos tecnicos e coloca os dados na fila de prioridade dos tecnicos. */

	void menu_principal(); /**< Funcao que faz print do menu principal, mostrando as opcoes e aguarda a escolha do utilizador. */
	void menu_avioes(); /**< Funcao que faz print do menu dos avioes, mostrando as opcoes e aguarda a escolha do utilizador. */
	void menu_visualizacao_avioes(); /**< Funcao que faz print do menu de visualizacao dos avioes, mostrando as opcoes e aguarda a escolha do utilizador. */
	void menu_passageiros(); /**< Funcao que faz print do menu dos passageiros, mostrando as opcoes e aguarda a escolha do utilizador. */
	void menu_passageiros_inativos(); /**< Funcao que faz print do menu dos passageiros inativos, mostrando as opcoes e aguarda a escolha do utilizador. */
	void menu_voos(); /**< Funcao que faz print do menu dos voos, mostrando as opcoes e aguarda a escolha do utilizador. */
	void menu_tecnicos(); /**< Funcao que faz print do menu dos tecnicos, mostrando as opcoes e aguarda a escolha do utilizador. */
	void menu_reservas(); /**< Funcao que faz print do menu das reservas, mostrando as opcoes e aguarda a escolha do utilizador. */

	void escrita_ficheiroAvioes(); /**< Funcao que escreve as alteracoes do vetor dos avioes no ficheiro dos avioes. */
	void escrita_ficheiroPassageirosCartao(); /**< Funcao que escreve as alteracoes do vetor dos passageiros com cartao no ficheiro dos passageiros com cartao. */
	void escrita_ficheiroVoos(); /**< Funcao que escreve as alteracoes do vetor dos voos no ficheiro dos voos. */
	void escrita_ficheiroTecnicos(); /**< Funcao que escreve as alteracoes da fila de prioridade dos tecnicos no ficheiro dos tecnicos. */
};

#endif /*MENU_H_*/
