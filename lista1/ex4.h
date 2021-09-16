#ifndef EX4_H
#define EX4_H

using namespace std;



class No;

class No
{
    private:
        // quem que joga nesse momento
        int Jogador;
        // pontuacao atrelada a esse momento
        int pont;
        // pai do nó atual
        No * Pai;
        // todos os filhos do nó
        vector<No*> Filhos;
        // linha em que foi feita a jogada no nó
        int i;
        // coluna em que foi feita a jogada no nó
        int j;
        
        void set_jogador(int jogador);
        int get_jogador();
        void set_pontuacao(int pontuacao);
        int get_pontuacao();
        void set_pai(No * no);
        No * get_pai();
        void set_filho(No * no);
        vector<No*> get_filhos();
        void set_linha(int i);
        int get_linha();
        void set_coluna(int j);
        int get_coluna();
        
        
    public:
        No();
        void coloca_jogador(int jogador);
        int jogador();
        void coloca_pontuacao(int pontuacao);
        int pontuacao();
        void adiciona_filho(No * filho);
        void coloca_linha(int i);
        int linha();
        void coloca_coluna(int j);
        int coluna();
        vector<No*> filhos();
};


No::No()
{
    Jogador = 0;
    pont = 0;
    Pai = nullptr;
    //Filhos = nullptr;
};

// metodos privados

void No::set_jogador(int jogador)
{
    this->Jogador = jogador;
}

int No::get_jogador()
{
    return this->Jogador;
}

void No::set_pontuacao(int pontuacao)
{
    this->pont = pontuacao;
}

int No::get_pontuacao()
{
    return pont;
}

void No::set_pai(No * no)
{
    this->Pai = no;
}

No * No::get_pai()
{
    return this->Pai;
}

void No::set_filho(No * no)
{
    no->set_pai(this);
    (this->Filhos).push_back(no);
}

vector<No*> No::get_filhos()
{
    return this->Filhos;
}

void No::set_linha(int i)
{
    this->i = i;
}

int No::get_linha()
{
    return this->i;
}

void No::set_coluna(int j)
{
    this->j = j;
}

int No::get_coluna()
{
    return this->j;
}


// metodos publicos

void No::coloca_jogador(int jogador)
{
    this->set_jogador(jogador);
}

int No::jogador()
{
    return this->get_jogador();
}

void No::coloca_pontuacao(int pontuacao)
{
    this->set_pontuacao(pontuacao);
}

int No::pontuacao()
{
    return this->get_pontuacao();
}

void No::adiciona_filho(No * filho)
{
    this->set_filho(filho);
}

vector<No*> No::filhos()
{
    return this->get_filhos();
}

void No::coloca_linha(int i)
{
    this->set_linha(i);
}

int No::linha()
{
    return this->get_linha();
}

void No::coloca_coluna(int j)
{
    this->set_coluna(j);
}

int No::coluna()
{
    return this->get_coluna();
}

// fim

int verifica_pontuacao(vector<vector<int>> tabuleiro);
No * minmax(No * no, int jogador);
void mostra_tabuleiro(vector<vector<int>> tabuleiro);
int constroi_arvore_minimax(No * no, int jogador);
void constroi_arvore(No * raiz, vector<vector<int>> tabuleiro, int vez);

#endif