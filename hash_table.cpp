// Precisamos de uma forma de converter objetos (chaves) em números naturais 

// Usamos uma função de dispersão para converter objetos em números inteiros
// f(k) = k mod |T|

// Quando temos duas ou mais chaves mapeadas em uma mesma posição, dizemos que ocorreu uma colisão
// Devemos portanto, sermos capazes de:
// 1. Tratar as colisões sem perder os objetos envolvidos
// 2. Tentar minimizar a quantidade de colições (A função de dispersão influencia na quantidade de colisões)
// 3. Uma estratégia para aumentar a capacidade da tabela


// Encadeamento aberto:
// Não utiliza memória extra
// (Se na insersão, tentarmos S = <i1, i2, ..., in> e garantirmos que a busca tentará 
//exatamente a mesma sequência , a busca será bem sucedida)
// OBS: Colisão não ocorre em enc. externo
// OBS: Saber se um índice está oculpado ou não é importante para essas técnicas

// Questão: Como facilitar a descoberta de que k não está na tabela sem custar O(n) toda vez?
// A tabela será criada com um valor boleano para cada índice, indicando se o índice já foi ocupado ou não,
// Quando a busca for iniciada, caso o valor não esteja na posição dada pela função de dispersão, a busca
// continuará até que:
// 1. Ache o valor ou
// 2. Pecorra toda a tabela e não encontre o valor, ou
// 3. Caia em um indice que ainda não foi ocupado, onde denominamos de "Buraco"

// Vamos adicionar a informação de que o índice sofreu remoção para auxiliar essa decisão
// caso o índice ainda não tenha recebido nenhum elemento, denominamos de "Lápides"

// ATENÇÃO: Existe a possibilidade de desperdiçarmos tempo de 
// busca se não gerenciarmos os espaços vazios da tabela

// Possibilidade de gestão:
// 1. Usar uma remoção , "reinserir" os elementos que existem após o elemento removido,
// na mesma sequência de tentativas
// 2. Acompanhar a proporção de lápides na tabela e reorganiza-lá completamente após ultrapassar o limite

// A solução mais geral é a 2º:
// 1. Alocar um vetor para fazer a redistribuição
// 2. Descartar o vetor ao final da execução

// INFORMAÇÕES NECESSÁRIAS PARA O ENDEREÇAMENTO ABERTO:
// 1. Acesso à função de dispersão
// 2. Espaço para guardar objetos
// 3. Espaço para o estado das posições da tabela (ocupado, vazio ou lápide)
// 4. Tamanho e capacidade da tabela
// 5. Quantidade de lápides
// 6. Limite de ocupação da tabela e de lápides
// 7. Na inserção precisamos conferir o limite de ocupação e aumentar a capacidade se necessário
// 8. Na remoção, precisamos conferir o limite de lápides e reorganizar se necessário

// OBS: Existem implementações onde o limite são são incluídos nos algoritmos como proporções fixas,
// não passamos como parâmetro da estrutura
// geralmente:
//      ucupação <= 75%
//      lápides <= 50%

#include <iostream>

typedef int (*Dispersao)(int,int);

struct Tabela {
public:
    int *objeto;
    bool *ocupado;
    bool *lapide;
    int capacidade;
    int tamanho;
    int qtd_lapides;
    float limite_ocupacao;


    Tabela(int capacidade, float limite_ocupacao) {
        // Inicializa a tabela com capacidade e limite de ocupação
        this->capacidade = capacidade;
        this->limite_ocupacao = limite_ocupacao;
        this->tamanho = 0;
        this->qtd_lapides = 0;
        this->objeto = new int[capacidade];
        this->ocupado = new bool[capacidade];
        this->lapide = new bool[capacidade];
        for (int i = 0; i < capacidade; i++) {
            this->objeto[i] = 0;
            this->ocupado[i] = false;
            this->lapide[i] = false;
        }
    }

    ~Tabela() {
        // Deleta a tabela
        delete[] this->objeto;
        delete[] this->ocupado;
        delete[] this->lapide;
    }


    static int funcao_dispersao(int chave, int tamanho) {
        // Retorna o índice de acordo com a função de dispersão
        return chave % tamanho;
    }

    // Algoritmo: BuscaTD (T, Dispersão, K)
    // Entrada: Tabela T, Função de Dispersão Dispersão, Chave K
    // Saída: "True" se K está na Tabela T, "False" caso contrário
    // Requisito: Tabela T deve ser uma tabela de encadeamento aberto
    static bool BuscaTD(Tabela T, Dispersao dispersao, int chave) {
        for (int i{0}; i < T.capacidade - 1; i++) {
            int posicao = dispersao(chave, T.capacidade);
            if (T.ocupado[posicao] == true) {
                if (T.objeto[posicao] == chave) {
                    return true;
                }
            }
            else if (T.ocupado[posicao] == false) {
                return false;
            }
        }
        return false;

    }
    

};



