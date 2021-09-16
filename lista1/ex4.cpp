#include <iostream>
#include <vector>
#include "ex4.h" /* usa a classe No e todos o métodos nela contidos */

using namespace std;

/*
*
*/
char traduz(int x)
{
    if (x == -1)
    {
        return 'R';
    }
    else if(x == 0)
    {
        return ' ';
    }
    else
    {
        return 'H';
    }
    
    
}

/*
*   faz a verificação do tabuleiro para saber se já existe um vencedor
*/
int verifica_pontuacao(vector<vector<int>> tabuleiro)
{
    // inicia é uma tentativa de otimização
    // onde se tabuleiro[0][0] == 0 então não haverá necessidade de verificar nem a primeira coluna nem a primeira linha
    // fim tem a mesma finalidade
    int inicia = 0, fim = 3;

    if (tabuleiro[2][2] == 0)
    {
        fim = 2;
    }
    

    if (tabuleiro[0][0] != 0)
    {
        if (tabuleiro[0][0] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][2])
        {
            return tabuleiro[0][0];
        }
    }
    else
    {
        inicia = 1;
    }
    
    
    
    if (tabuleiro[2][0] != 0)
    {
        if (tabuleiro[2][0] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[0][2])
        {
            return tabuleiro[2][0];
        }
    }

    for (int i = inicia; i < fim; i++)
    {
        if (tabuleiro[0][i] != 0)
        {
            if (tabuleiro[0][i] == tabuleiro[1][i] && tabuleiro[1][i] == tabuleiro[2][i])
            {
                return tabuleiro[0][i];
            }
        }
        
        
    }

    for (int i = inicia; i < fim; i++)
    {
        if (tabuleiro[i][0] != 0)
        {
            if (tabuleiro[i][0] == tabuleiro[i][1] && tabuleiro[i][1] == tabuleiro[i][2])
            {
                return tabuleiro[i][0];
            }
        }
    }
    
    return 0;
}

/*
*   constrói a arvore para se verificar o minimax pode utilizar
*/
void constroi_arvore(No * raiz, vector<vector<int>> tabuleiro, int vez)
{
    No * p = raiz;
    No * q;
    int pontuacao;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            // se a casa estiver livre
            if (tabuleiro[i][j] == 0)
            {
                tabuleiro[i][j] = vez;

                q = new No;

                q->coloca_jogador(vez);
                q->coloca_linha(i);
                q->coloca_coluna(j);

                p->adiciona_filho(q);

                // verifica se já há um vencedor
                pontuacao = verifica_pontuacao(tabuleiro);

                if (pontuacao != 0) // já tem um vencedor
                {
                    q->coloca_pontuacao(pontuacao);
                }
                else // ainda não teve um vencedor
                {
                    constroi_arvore(q, tabuleiro, vez*(-1));
                }
                
                // retorna ao valor inicial da roda para não afetar os passos seguintes
                tabuleiro[i][j] = 0;
            }
        }
    }
}

/*
*   Constrói as pontuaçãoes gerais da arvore já que ao construi-la temos apenas a pontuação das folhas.
*   A arvore construída funciona uníca e exclusivamente para o robo.
*   Recebe como parametro: Nó que é o nó atual da arvore, de quem é a vez que está jogando e para que jogador estamos rodando o algoritmo.
*/
int constroi_arvore_minimax(No * no, int jogador)
{
    // se nó é uma folha
    if (no->filhos().size() == 0)
    {
        return no->pontuacao();
    }
    else // caso não seja
    {
        int alpha = 0;

        // caso seja a vez do jogador
        if (no->jogador() == jogador)
        {
            // define um alpha menor que as pontuações possiveis
            alpha = -2;
            // roda para cada um dos filhos
            for (int i = 0; i < no->filhos().size(); i++)
            {
                alpha = max(alpha, constroi_arvore_minimax(no->filhos()[i], jogador));
                //alpha = alpha + constroi_arvore_minimax(no->filhos()[i], jogador);
            }
            
            no->coloca_pontuacao(alpha);
        }// caso em que é a vez do oponente
        else
        {
            // define um alpha maior
            alpha = 2;
            // roda para cada um dos filhos
            for (int i = 0; i < no->filhos().size(); i++)
            {
                alpha = min(alpha, constroi_arvore_minimax(no->filhos()[i], jogador));
                //alpha = alpha + constroi_arvore_minimax(no->filhos()[i], jogador);
            }
            
            no->coloca_pontuacao(alpha);
        }
    }

    return 1;
}

/*
*   aplica o algotimo minimax
*/
No * minmax(No * no, int jogador)
{
    No * no_maximo;

    for (int i = 0; i < no->filhos().size(); i++)
    {
        if (no->filhos()[i]->pontuacao() > no_maximo->pontuacao())
        {
            no_maximo = no->filhos()[i];
        }
    }
    
    return no_maximo;
}

void mostra_tabuleiro(vector<vector<int>> tabuleiro)
{
    cout << "    |0-1-2|" << endl;
    cout << "    -------" << endl;
    cout << "0 - |" << traduz(tabuleiro[0][0]) << "|" << traduz(tabuleiro[0][1]) << "|" << traduz(tabuleiro[0][2]) << "|" << endl;
    cout << "1 - |" << traduz(tabuleiro[1][0]) << "|" << traduz(tabuleiro[1][1]) << "|" << traduz(tabuleiro[1][2]) << "|" << endl;
    cout << "2 - |" << traduz(tabuleiro[2][0]) << "|" << traduz(tabuleiro[2][1]) << "|" << traduz(tabuleiro[2][2]) << "|" << endl;
    cout << "    -------" << endl;
}

int main()
{
    int comeca, joga_agora, i, j;
    vector<vector<int>> tabuleiro(3, vector<int> (3, 0));
    No * raiz = new No;
    No * p;
    No * q;
    
    cout << "Digite 1 para começar a jogada ou -1 para que a maquina comece" << endl;
    cin >> comeca;

    constroi_arvore(raiz, tabuleiro, comeca);
    constroi_arvore_minimax(raiz, comeca);

    p = raiz;

    joga_agora = comeca;

    while(verifica_pontuacao(tabuleiro) == 0)
    {
        mostra_tabuleiro(tabuleiro);

        // Verifica se quem joga agora é o humano ou jogador
        if (joga_agora == 1)
        {
            cout << "Vez do humano!" << endl;
            cout << "Digite o número da linha e o número da coluna: " << endl;
            cin >> i >> j;

            while(tabuleiro[i][j] != 0)
            {
                cout << "A posição que você escreveu já está ocupada!" << endl;
                cout << "Digite o número da linha e o número da coluna: " << endl;
                cin >> i >> j;
            }

            cout << "Numero de filhos: " << p->filhos().size() << endl;

            for (int k = 0; k < p->filhos().size(); k++)
            {
                if(p->filhos()[k]->linha() == i && p->filhos()[k]->coluna() == j)
                {
                    p = p->filhos()[k];
                }
            }
            
            tabuleiro[i][j] = joga_agora;

            joga_agora = joga_agora * (-1);
        }
        else
        {
            cout << endl << "Vez do robô!" << endl;

            p = minmax(p, joga_agora);

            cout << p->linha() << endl;

            tabuleiro[p->linha()][p->coluna()] = joga_agora;

            joga_agora = joga_agora * (-1);
        }
        
    }

    mostra_tabuleiro(tabuleiro);
}