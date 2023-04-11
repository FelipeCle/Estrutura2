#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

class No {
private:
  No *esq, *dir;
  string chave;
  string Cargo_base;
  string Cargo_em_comissao;
  float Remuneracao;
  string Unidade;

public:
  No(string chave, string Cargo_base, string Cargo_em_comissao,
     float Remuneracao, string Unidade) {
    this->chave = chave;
    this->Cargo_base = Cargo_base;
    this->Cargo_em_comissao = Cargo_em_comissao;
    this->Remuneracao = Remuneracao;
    this->Unidade = Unidade;
    esq = NULL;
    dir = NULL;
  }
  string getChave() { return chave; }
  string getCargo_base() { return Cargo_base; }
  string getCargo_em_comissao() { return Cargo_em_comissao; }
  float getRemuneracao() { return Remuneracao; }
  string getUnidade() { return Unidade; }
  No *getEsq() { return esq; }
  No *getDir() { return dir; }
  void setEsq(No *no) { esq = no; }
  void setDir(No *no) { dir = no; }
  void setChave(string k) { chave = k; }
};

class ArvoreBST {
private:
  No *raiz;

public:
  ArvoreBST() { raiz = NULL; }

  void setRaiz(No *root) { raiz = root; }

  void inserir(string chave, string Cargo_base, string Cargo_em_comissao,
               float Remuneracao, string Unidade) {
    if (raiz == NULL)
      raiz = new No(chave, Cargo_base, Cargo_em_comissao, Remuneracao, Unidade);
    else
      inserirAux(raiz, chave, Cargo_base, Cargo_em_comissao, Remuneracao,
                 Unidade);
  }

  void inserirAux(No *no, string chave, string Cargo_base,
                  string Cargo_em_comissao, float Remuneracao, string Unidade) {
    if (chave < no->getChave()) {
      if (no->getEsq() == NULL) {
        No *novo_no =
            new No(chave, Cargo_base, Cargo_em_comissao, Remuneracao, Unidade);
        no->setEsq(novo_no);
      } else {
        inserirAux(no->getEsq(), chave, Cargo_base, Cargo_em_comissao,
                   Remuneracao, Unidade);
      }
    } else if (chave > no->getChave()) {
      if (no->getDir() == NULL) {
        No *novo_no =
            new No(chave, Cargo_base, Cargo_em_comissao, Remuneracao, Unidade);
        no->setDir(novo_no);
      } else {
        inserirAux(no->getDir(), chave, Cargo_base, Cargo_em_comissao,
                   Remuneracao, Unidade);
      }
    }
  }

  No *getRaiz() { return raiz; }

  void emOrdem(No *no) {
    if (no != NULL) {
      emOrdem(no->getEsq());
      cout << "Nome:" << no->getChave() << endl;
      emOrdem(no->getDir());
    }
  }

  void preOrdem(No *no) {
    if (no != NULL) {
      cout << no->getChave() << " ";
      preOrdem(no->getEsq());
      preOrdem(no->getDir());
    }
  }

  void posOrdem(No *no) {
    if (no != NULL) {
      posOrdem(no->getEsq());
      posOrdem(no->getDir());
      cout << no->getChave() << " ";
    }
  }

  // versao iterativa
  No *Pesquisar(string dado, No *no) {
    if (raiz == NULL)
      return NULL;  // arvore vazia
    No *atual = no; // cria ptr aux (atual) e comeca a procurar
    while (atual->getChave() != dado) {
      if (dado < atual->getChave())
        atual = atual->getEsq(); // caminha para esquerda
      else
        atual = atual->getDir(); // caminha para direita
      if (atual == NULL)
        return NULL; // encontrou uma folha e nao encontrou a chave
    }
    return atual; // encontrou o dado
  }

  // versao recursiva
  No *PesquisarRec(No *r, string k) {
    if (r == NULL || r->getChave() == k)
      return r;
    if (r->getChave() > k)
      return PesquisarRec(r->getEsq(), k);
    else
      return PesquisarRec(r->getDir(), k);
  }

  // versao recursiva
  // Uma �rvore n�o vazia tem 1 n� raiz + x n�s na sub-�rvore � esq + y n�s na
  // sub-�rvore � dir
  int contarNos(No *atual) {
    if (atual == NULL)
      return 0;
    else
      return (1 + contarNos(atual->getEsq()) + contarNos(atual->getDir()));
  }

  // versao recursiva
  int altura(No *atual) {
    if (atual == NULL)
      return -1; //�rvore ou sub-�rvore vazia: altura = -1
    else {
      if (atual->getEsq() == NULL && atual->getDir() == NULL)
        return 0; //�vore com apenas 1 n�, altura = 0
      else { // altura da �rvore � a altura da sub-�rvore de maior altura
        if (altura(atual->getEsq()) > altura(atual->getDir()))
          return (1 + altura(atual->getEsq()));
        else
          return (1 + altura(atual->getDir()));
      }
    }
  }

  No *findMin(No *t) {
    if (t == NULL)
      return NULL;
    else if (t->getEsq() == NULL)
      return t;
    else
      return findMin(t->getEsq());
  }

  No *excluir(No *t, string key) {

    // Arvore t � vazia
    if (t == NULL)
      return t;

    if (key < t->getChave())
      t->setEsq(excluir(t->getEsq(), key));
    else if (key > t->getChave())
      t->setDir(excluir(t->getDir(), key));

    // encontramos o n� a ser removido
    else {
      // Caso1: o no a ser excluido nao tem filhos
      if (t->getEsq() == NULL and t->getDir() == NULL) {
        delete (t);
        return NULL; // faz o pai apontar para NULL e o n� n�o faz mais parte da
                     // BST
      } else
        // Caso2: tem apenas um filho, a esquerda ou a direita
        if (t->getEsq() == NULL) {
          No *temp = t->getDir();
          delete (t);
          return temp; // Faz o pai apontar para o �nico filho do n�
        } else if (t->getDir() == NULL) {
          No *temp = t->getEsq();
          delete (t);
          return temp; // Faz o pai apontar para o �nico filho do n�
        }

      // Caso3: o no a ser excluido tem 2 filhos. Vamos escolher o menor dos
      // maiores para substituir o no que sera removido. Sucessor = menor no na
      // sub-arvore da direita

      No *temp = findMin(t->getDir());

      // Copia a chave do sucessor para o no que esta sendo removido
      t->setChave(temp->getChave());

      // Remove da arvore o sucessor!
      t->setDir(excluir(t->getDir(), temp->getChave()));
    }

    // retorna a raiz da arvore
    return t;
  }

  int folhas(No *atual) {
    if (atual == NULL)
      return 0;
    if (atual->getEsq() == NULL && atual->getDir() == NULL)
      return 1;
    return folhas(atual->getEsq()) + folhas(atual->getDir());
  }

  void print() { print(raiz, 0); }

  void print(No *no, int space) {
    if (no != NULL) {
      print(no->getDir(), space + 5);
      for (int k = 0; k < space; ++k)
        cout << " ";
      cout << no->getChave() << "RS:" << no->getRemuneracao() << "\n";
      print(no->getEsq(), space + 5);
    }
  }

  // Funções novas

  // Adaptação do método pós-ordem
  // Encontra a maior remuneração bruta.
  No *encontrarMaiorRemuneracao() {
    No *maior = raiz;
    maiorRemuneracao(raiz, maior);
    return maior;
  }

  void maiorRemuneracao(No *no, No *&maior) {
    if (no == NULL)
      return;
    if (no->getRemuneracao() > maior->getRemuneracao()) {
      maior = no;
    }
    maiorRemuneracao(no->getEsq(), maior);
    maiorRemuneracao(no->getDir(), maior);
  }

  // Encontra a menor remuneração bruta.
  No *encontrarMenorRemuneracao() {
    No *menor = raiz;
    menorRemuneracao(raiz, menor);
    return menor;
  }

  void menorRemuneracao(No *no, No *&menor) {
    if (no == NULL)
      return;
    if (no->getRemuneracao() < menor->getRemuneracao()) {
      menor = no;
    }
    menorRemuneracao(no->getEsq(), menor);
    menorRemuneracao(no->getDir(), menor);
  }
  //*****************************************
  // Pesquisar por Unidade

  void pesquisar_Unidade(No *no, string unidade) {
    if (no == NULL)
      return;
    if (no->getUnidade() == unidade) {
      cout << "Nome: " << no->getChave() << "\tUnidade: " << no->getUnidade()
           << endl;
    }
    pesquisar_Unidade(no->getEsq(), unidade);
    pesquisar_Unidade(no->getDir(), unidade);
  }

  // Salvar dados em um arquivo

  void salvarArvoreBST(No *no, ofstream &arquivo) {
    if (no == NULL) {
      return;
    }
    salvarArvoreBST(no->getEsq(), arquivo);
    arquivo << no->getChave() << ";" << no->getCargo_base() << ";"
            << no->getCargo_em_comissao() << ";" << no->getRemuneracao() << ";"
            << no->getUnidade() << endl;
    salvarArvoreBST(no->getDir(), arquivo);
  }

  void salvarDadosArvoreBST(ArvoreBST *arvore, string nomeArquivo) {
    ofstream arquivo(nomeArquivo);
    salvarArvoreBST(arvore->getRaiz(), arquivo);
    arquivo.close();
  }
  //**********************************
  // Calcula Remuneracao Media por tipo de Unidade
  void calcularMediaRemuneracaoPorUnidade(ArvoreBST arvore) {
    vector<string> unidades;
    vector<float> somas;
    vector<int> contagens;

    calcularSomaRemuneracaoPorUnidade(arvore.raiz, unidades, somas, contagens);
    cout << left << setw(60) << "Unidade" << left << setw(15) << "Media"
         << endl;
    for (int i = 0; i < unidades.size(); i++) {
      float media = somas[i] / contagens[i];
      cout << left << setw(60) << unidades[i] << left << setw(15) << media
           << endl;
      // cout << "Média de remuneração para a unidade " << unidades[i] << ": "
      // << media << endl;
    }
  }

  void calcularSomaRemuneracaoPorUnidade(No *no, vector<string> &unidades,
                                         vector<float> &somas,
                                         vector<int> &contagens) {
    if (no != NULL) {
      int indice = encontrarUnidade(unidades, no->getUnidade());
      if (indice == -1) {
        unidades.push_back(no->getUnidade());
        somas.push_back(no->getRemuneracao());
        contagens.push_back(1);
      } else {
        somas[indice] += no->getRemuneracao();
        contagens[indice]++;
      }
      calcularSomaRemuneracaoPorUnidade(no->getEsq(), unidades, somas,
                                        contagens);
      calcularSomaRemuneracaoPorUnidade(no->getDir(), unidades, somas,
                                        contagens);
    }
  }

  int encontrarUnidade(vector<string> unidades, string unidade) {
    for (int i = 0; i < unidades.size(); i++) {
      if (unidades[i] == unidade) {
        return i;
      }
    }
    return -1;
  }
  //*****************************************************

  // Dado um cargo base realiza a contagem de quantos funcionaros ele possui
  void quantidadeFuncionariosPorCargoBase(No *no, string cargoBase,
                                          int &contador) {
    if (no != NULL) {
      quantidadeFuncionariosPorCargoBase(no->getEsq(), cargoBase, contador);
      if (no->getCargo_base() == cargoBase) {
        contador++;
      }
      quantidadeFuncionariosPorCargoBase(no->getDir(), cargoBase, contador);
    }
  }

  // Função auxiliar para a quantidadeFuncionariosPorCargoBase , possui o
  // endereço do contador
  int quantidadeFuncionariosPorCargoBase(string cargoBase) {
    int contador = 0;
    quantidadeFuncionariosPorCargoBase(raiz, cargoBase, contador);
    return contador;
  }

  // Adiciona no vetor ocorrencias unicas de cada cargo
  void cargos(No *no, vector<string> &cargos_base) {
    if (no != NULL) {
      cargos(no->getEsq(), cargos_base);
      if (find(cargos_base.begin(), cargos_base.end(), no->getCargo_base()) ==
          cargos_base.end()) {
        cargos_base.push_back(no->getCargo_base());
      }
      cargos(no->getDir(), cargos_base);
    }
  }
  // Vetor que possui cada ocorrencia
  void criarVetorCargosBase(ArvoreBST &arvore) {
    vector<string> cargos_base;
    cargos(arvore.raiz, cargos_base);
    cout << left << setw(60) << "Cargo Base" << left << setw(5) << "Quantidade"
         << endl;
    for (int i = 0; i < cargos_base.size(); i++) {
      int quantidade = quantidadeFuncionariosPorCargoBase(cargos_base[i]);
      string cargo = cargos_base[i];
      if (cargo == " ") {
        cargo = "*SEM CARGO BASE";
      }
      cout << left << setw(60) << cargo << left << setw(5) << quantidade
           << endl;

    }
  }
  //*******************************************************
  //Mesmo funcionamento para os cargos em comissao
  void quantidadeFuncionariosPorCargoComissao(No* no, string cargoComissao, int& contador) {
      if (no != NULL) {
          quantidadeFuncionariosPorCargoComissao(no->getEsq(), cargoComissao, contador);
          if (no->getCargo_em_comissao() == cargoComissao) {
              contador++;
          }
          quantidadeFuncionariosPorCargoComissao(no->getDir(), cargoComissao, contador);
      }
  }

  int quantidadeFuncionariosPorCargoComissao(string cargoComissao) {
      int contador = 0;
      quantidadeFuncionariosPorCargoComissao(raiz, cargoComissao, contador);
      return contador;
  }

  void cargosComissao(No* no, vector<string>& cargos_comissao) {
      if (no != NULL) {
          cargosComissao(no->getEsq(), cargos_comissao);
          if (find(cargos_comissao.begin(), cargos_comissao.end(), no->getCargo_em_comissao()) == cargos_comissao.end()) {
              cargos_comissao.push_back(no->getCargo_em_comissao());
          }
          cargosComissao(no->getDir(), cargos_comissao);
      }
  }

  void criarVetorCargosComissao(ArvoreBST& arvore) {
      vector<string> cargos_comissao;
      cargosComissao(arvore.raiz, cargos_comissao);
      cout << left << setw(60) << "Cargo em Comissão" << left << setw(5) << "Quantidade"
          << endl;
      for (int i = 0; i < cargos_comissao.size(); i++) {
          int quantidade = quantidadeFuncionariosPorCargoComissao(cargos_comissao[i]);
          string cargo = cargos_comissao[i];
          if (cargo=="") {
              cargo = "*SEM CARGO EM COMISSÃO";
          }
          cout << left << setw(60) << cargo << left << setw(5) << quantidade << endl;
      }
  }

  //*******************************************************************************************************************
};