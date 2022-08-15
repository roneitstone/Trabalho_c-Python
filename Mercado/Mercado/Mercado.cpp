// Mercado.cpp : Arquivo que mostra o menu e chama as funcoes auxiliares em Python.
// Autor: Eduardo Bruno Martins Esperança
// Descrição: arquivo que chama as funcoes em python;

#include "Mercado.h"

using namespace std;
namespace py = pybind11;
int max = 10;
vector<vector<string>> produtos = { {"camisa polo", "20"}, {"bone da Havan", "50"} };



bool verify(string verif) { // verifica entradas maliciosas

    for (unsigned int i = 0; i < verif.length(); i++) {
        if (verif[i] != '1' && verif[i] != '2' && verif[i] != '3' && verif[i] != '4' && verif[i] != '5' && verif[i] != '6' && verif[i] != '7' && verif[i] != '8' && verif[i] != '9' && verif[i] != '0' && verif[i] != '.') {


            return false;


        }
    }
    if (verif.length() > 4) {
        return false;
    }
    return true;
}

int main()
{
    int escolha;
    string verificador;
    bool verificar = false;
    
    
    while(verificar == false)
    {
        cout << "           Bem vindo ao estoque Americanas  !" << endl;
        cout << "      digite o numero das seguintes opcoes:   \n\n" << endl;
        cout << " 1 -       Estoque presente na loja :" << endl;
        cout << " 2 - Verificar disponibilidade de um produto na loja :" << endl;
        cout << " 3 -       Adicionar produto ao estoque : " << endl;
        cout << " 4 -       Retirar produto do estoque : " << endl;
        cout << " 5 -       Produtos em falta na loja :" << endl;
        cout << " 6 -            Fecha o programa" << endl;

        if (produtos.size() > 10) {
            produtos.erase(produtos.begin());
        }

        cin >> verificador;
        cin.ignore();

        if (verify(verificador) == false) {
            cout << " \n\n\n      Escolha nao reconhecida!     \n\n\n" << endl;
            return main();
        }
        else {

            istringstream(verificador) >> escolha;

        }



        if (escolha == 1) { // mostra os produtos que estao no vector
            system("CLS");
            cout << " \n Estes sao os produtos listados no cache da loja no momento : " << endl;

            for (unsigned int i = 0; i < produtos.size(); i++) {
                cout << i + 1 << " : " << produtos[i][0] << endl;
            }

        }
        if (escolha == 2) { // verifica se o produto esta no vector ou chama uma funcao auxiliar em python para ler o estoque e retornar disponibilidade e quantidade
            string produto;
            string result;
            int guarda = 0;
            bool achou = false;
            system("CLS");



            cout << " \n Escolha um produto : " << endl;
            getline(cin, produto);
            cout << endl;

            system("CLS");


            for (unsigned int i = 0; i < produtos.size(); i++) { //verifica o vector
                if (produtos[i][0] == produto) {
                    achou = true;
                    guarda = i;
                }
            }
            if (achou == false) // nao achou
            {


                py::scoped_interpreter guard{}; // chama o interpretador de python
                try { // fica dentro de um try para evitar crash caso ocoram erros no código em python
                    auto modulo = py::module::import("scripts.StockManager");  // importa arquivo com funcoes em python
                    auto func = modulo.attr("LeitorEstoque"); // cria um objeto com a funcao do python
                    result = func(produto).cast <string>();   // executamos a funcao do objeto e pegamos o retorno
                    
                    if (result == "Erro") {   // Se retornou Erro, algo deu errado
                        cout << " \n\n " << " Nao encontramos esse produto no estoque! \n\n" << endl;
                        return main();
                    }
                    else { //Deu certo

                        cout << "\n\n Estoque presente - " << result << "\n" << endl;
                        
                        string delimitador = "-";
                        size_t pos = 0;
                        string prod;

                        while ((pos = result.find(delimitador)) != string::npos)
                        {
                            prod = result.substr(0, pos);

                            result.erase(0, pos + delimitador.length());
                        }
                        // colocamos o que foi pego no estoque e adicionamos o produto ao vector    
                        vector<string> valida;
                        valida.push_back(prod);
                        valida.push_back(result);
                        produtos.push_back(valida);

                    }

                }
                catch (py::error_already_set& erro) // alerta o erro que ocorreu
                {
                    cout << erro.what() << endl;
                }
            }
            else { // Produto dentro do cache
                cout << "\n\n Temos no estoque " << produtos[guarda][1] << " do " << produtos[guarda][0] << "\n\n" << endl;
            }
        }

        if (escolha == 3) { // adiciona produto e quantidades

            string produto;
            string result;
            int guarda = 0;
            bool achou = false;
            
            cout << " \n Escolha um produto para adicionar : " << endl;
            getline(cin, produto);
            cout << endl;
            
            for (unsigned int i = 0; i < produtos.size(); i++) {
                if (produtos[i][0] == produto) {
                    achou = true;
                    guarda = i;
                }
            }


            system("CLS");

            py::scoped_interpreter guard{};
            try {

                auto modulo = py::module::import("scripts.StockManager"); // importa arquivo com funcoes em python
                auto func = modulo.attr("AdicionaEstoque"); // cria objeto para a funcao em python
                result = func(produto).cast <string>();  // executa funcao e pega o retornado


            }
            catch (py::error_already_set& erro) // caso ocorram erros
            {
                cout << erro.what() << endl;
            }

            if (result == "Erro") { // caso algo tenha ido errado nos valores
                cout << " \n\n " << " Ocorreu um erro interno ! \n\n" << endl;
                return main();
            }
            else { // deu certo
                cout << "\n Guardado com sucesso, estoque presente - " << result << endl;
            }
            if (achou == false && result != "Erro") { // muda a quantidade do produto no vector
                vector<string> valida;
                valida.push_back(produto);
                valida.push_back(result);
                produtos.push_back(valida);
            }
            else {
                if (result != "Erro") // poe novo produto no vector
                {
                    int novo;
                    stringstream ss;

                    istringstream(result) >> novo;
                    novo = novo;
                    ss << novo;
                    produtos[guarda][1] = ss.str();
                }
            }
        }
        if (escolha == 4) { // retira quantidade de um produto
            string produto;
            string result;
            int guarda = 0;
            bool achou = false;


            cout << " \n Escolha um produto para retirar : " << endl;
            getline(cin, produto);
            cout << endl;
            
            for (unsigned int i = 0; i < produtos.size(); i++) {
                if (produtos[i][0] == produto) {
                    achou = true;
                    guarda = i;
                }
            }



            system("CLS");
            py::scoped_interpreter guard{};
            try {
                auto modulo = py::module::import("scripts.StockManager"); // importa codigo com funcoes em python
                auto func = modulo.attr("RetiradoEstoque"); // cria objeto de funcao em python
                result = func(produto).cast <string>(); // executa e recebe retornado

            }
            catch (py::error_already_set& erro) // detecta erros
            {
                cout << erro.what() << endl;

            }
            if (result == "Erro") { // ocorreu erro humano
                cout << " \n\n" << result << " produto nao encontrado\n" << endl;
            }
            else { // deu certo
                cout << "\n\n Nova quantidade do produto " << produto << " - " << result << " \n" << endl;
            }

            if (achou == false && result != "Erro") { // mudando valores do produto no vector
                vector<string> valida;
                valida.push_back(produto);
                valida.push_back(result);
                produtos.push_back(valida);
            }
            else {
                if (result != "Erro") // adiciona novo produto ao vector
                {
                    int novo;
                    stringstream ss;
                    istringstream(result) >> novo;
                    novo = novo;
                    ss << novo;
                    produtos[guarda][1] = ss.str();
                }
            }
        }
        if (escolha == 5) { //busca produto em falta
            string produto;
            string result;
            
            system("CLS");
            cout << " \n Os seguintes produtos estao em falta: \n" << endl;
            
            py::scoped_interpreter guard{};
            try { 
                auto modulo = py::module::import("scripts.StockManager"); // importa arquivo com as funcoes python
                auto func = modulo.attr("EmFalta"); // cria objeto da funcao em python
                result = func(produto).cast <string>(); // executa funcao e recebe retornado
                cout << "\n" << result << " \n\n " << endl;
            }
            catch (py::error_already_set& erro) //verifica erros
            {
                cout << erro.what() << endl;
            }
        }


        if (escolha == 6) {
            cout << "                   Adeus...                        " << endl;

            verificar = true;
        }

        if (escolha > 6 || escolha <= 0) {
            cout << "            Escolha desconhecida !!                " << endl;

        }
    }
	return 0;
}
