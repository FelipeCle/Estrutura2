#include "arvore.cpp"
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string.h>

using namespace std;

bool sair = false;
int escolha;
int main() {
    string arquivo_escolhido;
    string arquivo_backup;
    cout <<"Digite o nome do arquivo a ser aberto:";
    cin >> arquivo_escolhido;
    ArvoreBST Dados;
    No* resp;
    string nome;
    string unidadeProcurada;
    ifstream arquivo(arquivo_escolhido);
    string linha = "";
    while (sair == false) {
        cout << "\nMENU\n\n";
        cout << "1 -> Carregar dados\n";
        cout << "2 -> Salvar dados em backup\n";
        cout << "3 -> Imprimir em ordem\n";
        cout << "4 -> Remove funcionário\n";
        cout << "5 -> Quantidade de funcionarios lidos\n";
        cout << "6 -> Apresentar funcionário com o maior e menor salário\n";
        cout << "7 -> Apresentar funcionários de determinada unidade\n";
        cout << "8 -> Apresentar média de remuneração dos funcionários por unidades\n";
        cout << "9 -> Apresentar quantidade de funcionarios por cargo base\n";
        cout << "10-> Apresentar quantidade de funcionarios por cargo em comissão\n";
        cout << "0 -> Para sair\n";
        cout << "\nDigite uma opção: ";
        cin >> escolha;
        switch (escolha) {
        case 0:
            sair = true;
            break;
        case 1:
            getline(arquivo, linha);
            while (getline(arquivo, linha)) {
                stringstream s(linha);
                string chave;
                string Cargo_base;
                string Cargo_em_comissao;
                float Remuneracao;
                string Unidade;
                getline(s, chave, ';');
                getline(s, Cargo_base, ';');
                getline(s, Cargo_em_comissao, ';');
                getline(s, linha, ';');
                Remuneracao = atof(linha.c_str());
                getline(s, Unidade, ';');
                Dados.inserir(chave, Cargo_base, Cargo_em_comissao, Remuneracao, Unidade);
            }
            cout << "\n Dados carregados!\n";
            break;
        case 2:
            cout <<"De um nome para o arquivo de backup\n";
            cin >> arquivo_backup;
            Dados.salvarDadosArvoreBST(&Dados, arquivo_backup);
            cout << "Dados salvos com sucesso";
            break;
        case 3:
            cout << "Percorrendo em ordem...\n";
            Dados.emOrdem(Dados.getRaiz());
            break;
        case 4:
            cout << "\n Informe o nome  ->  ";
            cin.ignore();
            getline(cin, nome);
            for (auto& c : nome)
                c = toupper(c);
            resp = Dados.excluir(Dados.getRaiz(), nome);
            Dados.setRaiz(resp);
            if (resp != NULL)
                cout << "\n  Funcionário removido com sucesso!\n";
            else
                cout << "A arvore esta vazia!" << endl;
            break;
        case 5:
            cout << "\nQuantidade de funcionários lidos :"<< Dados.contarNos(Dados.getRaiz())<<endl;
            break;
        case 6:
            resp = Dados.encontrarMaiorRemuneracao();
            cout << "\n-Maior:";
            cout << "\nFuncionário(a):"  << resp->getChave() << "\t\tRemuneração:\tRS " << resp->getRemuneracao() << endl;
            resp = Dados.encontrarMenorRemuneracao();
            cout << "\n-Menor:";
            cout << "\nFuncionário(a):" << resp->getChave() << "\t\tRemuneração:\tRS " << resp->getRemuneracao() << endl;
            break;
        case 7:
            cout << "\n Informe a unidade  ->  ";
            cin.ignore();
            getline(cin, unidadeProcurada);
            for (auto& c : unidadeProcurada)
                c = toupper(c);
            Dados.pesquisar_Unidade(Dados.getRaiz(), unidadeProcurada);
            break;
        case 8:
            cout << "\n Apresentando médias : \n";
            Dados.calcularMediaRemuneracaoPorUnidade(Dados);
            break;
        case 9:
            Dados.criarVetorCargosBase(Dados);
            break;
        case 10:
            Dados.criarVetorCargosComissao(Dados);
            break;
        default:
            cout << "\nOpção inválida !!!\n";
            break;
        }
    }
}
