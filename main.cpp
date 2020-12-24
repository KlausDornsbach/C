// processamento de XML com imagens binárias

#include <iostream>  // ! library for dealing with files
#include <fstream>
#include <queue>
#include <stack>
#include <utility>

using namespace std;

// ! primeiro problema: validação do arquivo

int main() {

    char xmlfilename[100];
    std::cin >> xmlfilename;

    ifstream my_xml("xml");  // ! objeto com suporte a leitura de file

    /*** variaveis usadas em ambos (checa integridade do arquivo e conta figuras) ***/
    //char str[100];  // ! declaring string variable
    size_t pos_atualizada;
    size_t position1;  // ! posicao que '<' foi achada
    size_t position2;  // ! posicao que '>' foi achada
    string line;       // ! armazena linha

    /*** abro pra checar integridade ***/
    my_xml.open(xmlfilename);   // ! abro file
    stack<string> stk;  // ! declaring stack of strings
    string stk_top;    // ! armazena topo
    size_t len;
    int tem_tags;       // ! diz se tem tags na linha 
    int erro = 0;          // ! bool de erro
    
    
    if (my_xml.is_open()) {  // ! line é o buffer pra colocar as linhas da file
        while (getline(my_xml, line)) {  // ! itera pegando cada linha ate n ter mais linhas
            //********* ! adicionar suporte a achar multiplos tags ********   
            tem_tags = 1;
            pos_atualizada = 0;
            while (tem_tags) {
                position1 = line.find("<", pos_atualizada);  // ! procura '<'
                position2 = line.find(">", position1 + 1);  // ! procura '>'
                pos_atualizada = position2 + 1;
                //cout << line.substr(position2 - position1);
                if (position1 < line.size()) {  // ! achou '<'
                    if (!line.compare(position1 + 1, 1, "/")) {  // ! se prox char é '/':
                        //cout<<line.substr(position1 + 2, position2 - position1 - 1); 
                        if (stk.size() == 0) {  // ! checa stack, se vazio:
                            printf("error");  // ! erro
                            erro = 1;
                            break;
                        }  // ! se n cheia:
                        // ! tenho que pegar a string inteira da tag
                        stk_top = stk.top();  // ! elemento de topo
                        len = position2 - position1 - 1;  // ! tamanho da tag
                        //cout<<"len, position1, position2 " << len<<" "<<position1<<" "<<position2 <<"\n";
                        //cout<<"vi agora e o topo "<<line.substr(position1 + 2, len - 1)<<", "<<stk_top<<"\n";
                        //cout<<line.compare(position1 + 2, len - 1, stk_top)<<"\n";
                        //cout<<line.compare(position1 + 2, len - 1, stk_top);
                        if (!line.compare(position1 + 2, len - 1, stk_top)) {  // ! se iguais desempilho
                            // ! tiro elemento de topo
                            stk.pop();
                        } else {
                            printf("error");
                            erro = 1;
                            break;
                        }
                    } else {
                        string s = line.substr(position1 + 1, position2 - position1 - 1);
                        stk.push(s);
                        //cout << "coloquei no stack: " << s << "\n";
                    }
                } else {
                    tem_tags = 0;
                }
            }
            if (erro) {
                break;
            }
        }
        if (erro) {
            // ! só sai
        } else if (stk.size() != 0) {
            printf("error");  // ! sobrou tags no stack
            erro = 1;
        }
        my_xml.close();
        //******** ! checar se está tudo em ordem, adicionando condicoes de pilha ainda com elementos********
    }
    /*** conta figuras ***/
    int flag_achou = 0;  // ! flag setada quando acha "data"
    string name_xml;  // ! armazen. nome
    size_t height;  // ! armazen. height
    size_t width;   // ! armazen. width
    queue<pair<int, int>> fila; // ! fila de cooredenadas

    // ! metodo pra ver quantas figuras tem no arquivo
    
    my_xml.open(xmlfilename);
    if (my_xml.is_open() && erro == 0) {  // ! line é o buffer pra colocar as linhas da file
        while (getline(my_xml, line)) {  // ! itera pegando cada linha ate n ter mais linhas
            //cout << line <<" :next line\n";
            //tratamento do nome
            if (line.find("<name>")!=-1) {  // ! para achar o nome da figura
                position1 = line.find("<name>");
                position2 = line.find("<", position1 + 1);  // ! aqui temos a posicao final
                len = position2 - position1 - 6;  // ! tamanho da string nome.png
                name_xml = line.substr(position1 + 6, len);  // ! armazeno nome
                //cout<<"\nlen, position1, position2 " << len<<" "<<position1<<" "<<position2 <<"\n";
                //cout << "\n\nname: " << name_xml;
                
            }
            //tratamento do height
            if (line.find("<height>")!=-1) {
                position1 = line.find("<height>");
                position2 = line.find("<", position1 + 1);  // ! aqui temos a posicao final
                len = position2 - position1 - 8;  // ! tamanho da string height
                string s = line.substr(position1 + 8, len);  // ! armazeno height
                //cout<<"height: \n"<<s;
                height = stoi(s, nullptr, 10);  // ! armazeno height
                
            }
            //tratamento do width
            if (line.find("<width>")!=-1) {
                position1 = line.find("<width>");
                position2 = line.find("<", position1 + 1);  // ! aqui temos a posicao final
                len = position2 - position1 - 7;  // ! tamanho da string width
                string s = line.substr(position1 + 7, len);  
                //cout<<"width: \n"<<s;
                width = stoi(s, nullptr, 10);  // ! armazeno width
            }
            //tratamento data  
            if (!flag_achou) { // ! n achou tag <data> (na iteracao anterior do while)
                if (line.find("<data>") != -1) {  // ! if found
                    flag_achou = 1;  // ! seta flag
                }
            } else {
                // ! achou e pode começar a tratar do texto
                
                flag_achou = 0;
                
                /*position1 = line.find("</data>");  // ! find data
                if (position1 != -1) {  // ! if found
                    flag_achou = 0;  // ! seta flag
                    continue;  // ! ja vai pra proxima iteracao
                }*/

                //int R[height][width];  // ! matriz resposta
                //int P[height][width];  // ! entrada
                
                int** R = new int*[height];
                int** P = new int*[height];
                for (int i = 0; i < height; ++i) {
                    R[i] = new int[width];
                    P[i] = new int[width];
                }
                
                
                string aux_str;
                int aux_int;
                for (int i = 0; i < height; i++) {
                    for(int j = 0; j < width; j++) {  // ! inicia matrizes
                        aux_str = line[j];
                        aux_int = stoi(aux_str, nullptr, 10);
                        P[i][j] = aux_int;
                        R[i][j] = 0;
                        // ! printf("%d ", P[i][j]);
                    }
                    getline(my_xml, line);
                }
                pair<int, int> left;  // ! armazena vizinhos temporariamente
                pair<int, int> right;
                pair<int, int> up;
                pair<int, int> down;
                
                int rotulo = 0;
                for (int i = 0; i < height; i++) {
                    for (int j = 0; j < width; j++) {
                        if (P[i][j] == 1 && R[i][j] == 0) {
                            rotulo++;
                            pair<int, int> p;
                            p.first = i;
                            p.second = j;
                            fila.push(p);  // ! se é 1 adiciona na fila
                            R[i][j] = rotulo;
                        }

                        while (fila.size() != 0) {
                            pair<int, int> aux = fila.front();  // ! elemento na frente da fila
                             
                            left.first = aux.first;         // ! definindo posicoes
                            left.second = aux.second - 1;
                            right.first = aux.first;
                            right.second = aux.second + 1;
                            up.first = aux.first - 1;
                            up.second = aux.second;
                            down.first = aux.first + 1;
                            down.second = aux.second;
                            
                            fila.pop();  // ! tiro da fila
                            if (aux.first == 0) {  // --
                                if (P[down.first][down.second] == 1 && R[down.first][down.second] == 0) {
                                    fila.push(down);
                                    R[down.first][down.second] = rotulo;
                                }
                                if (aux.second == 0) {  // |--
                                    //fila.push(right);
                                    if (P[right.first][right.second] == 1 && R[right.first][right.second] == 0) {
                                        fila.push(right);
                                        R[right.first][right.second] = rotulo;
                                    }
                                } else if (aux.second == width - 1) {  // --|
                                    //fila.push(left);
                                    if (P[left.first][left.second] == 1 && R[left.first][left.second] == 0) {
                                        fila.push(left);
                                        R[left.first][left.second] = rotulo;
                                    }
                                } else {
                                    //fila.push(right);
                                    if (P[right.first][right.second] == 1 && R[right.first][right.second] == 0) {
                                        fila.push(right);
                                        R[right.first][right.second] = rotulo;
                                    }
                                    //fila.push(left);
                                    if (P[left.first][left.second] == 1 && R[left.first][left.second] == 0) {
                                        fila.push(left);
                                        R[left.first][left.second] = rotulo;
                                    }    
                                }
                            } else if (aux.first == height - 1) {  // __
                                //fila.push(up);
                                if (P[up.first][up.second] == 1 && R[up.first][up.second] == 0) {
                                    fila.push(up);
                                    R[up.first][up.second] = rotulo;
                                }
                                if (aux.second == 0) {  // |__
                                    //fila.push(right);
                                    if (P[right.first][right.second] == 1 && R[right.first][right.second] == 0) {
                                        fila.push(right);
                                        R[right.first][right.second] = rotulo;
                                    }
                                } else if (aux.second == width - 1) {  // __| 
                                    //fila.push(left);
                                    if (P[left.first][left.second] == 1 && R[left.first][left.second] == 0) {
                                        fila.push(left);
                                        R[left.first][left.second] = rotulo;
                                    }
                                } else {  // ___
                                     if (P[left.first][left.second] == 1 && R[left.first][left.second] == 0) {
                                        fila.push(left);
                                        R[left.first][left.second] = rotulo;
                                    }
                                    //fila.push(right);
                                    if (P[right.first][right.second] == 1 && R[right.first][right.second] == 0) {
                                        fila.push(right);
                                        R[right.first][right.second] = rotulo;
                                    }
                                }
                            } else if (aux.second == 0) {  // |<-
                                //fila.push(right);
                                if (P[right.first][right.second] == 1 && R[right.first][right.second] == 0) {    
                                    fila.push(right);
                                    R[right.first][right.second] = rotulo;
                                }
                                //fila.push(down);
                                if (P[down.first][down.second] == 1 && R[down.first][down.second] == 0) {
                                    fila.push(down);
                                    R[down.first][down.second] = rotulo;
                                }
                                //fila.push(up);
                                if (P[up.first][up.second] == 1 && R[up.first][up.second] == 0) {
                                    fila.push(up);
                                    R[up.first][up.second] = rotulo;
                                }
                            } else if (aux.second == width - 1) {  // ->|
                                //fila.push(left);
                                if (P[left.first][left.second] == 1 && R[left.first][left.second] == 0) {
                                    fila.push(left);
                                    R[left.first][left.second] = rotulo;
                                }
                                //fila.push(down);
                                if (P[down.first][down.second] == 1 && R[down.first][down.second] == 0) {
                                    fila.push(down);
                                    R[down.first][down.second] = rotulo;
                                }
                                //fila.push(up);
                                if (P[up.first][up.second] == 1 && R[up.first][up.second] == 0) {
                                    fila.push(up);
                                    R[up.first][up.second] = rotulo;
                                }
                            } else {
                                //fila.push(left);
                                if (P[left.first][left.second] == 1 && R[left.first][left.second] == 0) {
                                    fila.push(left);
                                    R[left.first][left.second] = rotulo;
                                }
                                //fila.push(right);
                                if (P[right.first][right.second] == 1 && R[right.first][right.second] == 0) {    
                                    fila.push(right);
                                    R[right.first][right.second] = rotulo;
                                }
                                //fila.push(down);
                                if (P[down.first][down.second] == 1 && R[down.first][down.second] == 0) {
                                    fila.push(down);
                                    R[down.first][down.second] = rotulo;
                                }
                                //fila.push(up);
                                if (P[up.first][up.second] == 1 && R[up.first][up.second] == 0) {
                                    fila.push(up);
                                    R[up.first][up.second] = rotulo;
                                }
                            }
                        }  // ! aqui acaba o while da fila
                    }  // ! aqui acabam os fila.push()
                }  // ! aqui acabam os fors (deve estar tudo completo)
                /*for(int i=0; i<height; i++){
                    for(int j = 0; j<width; j++) {
                        cout<<R[i][j]<<" ";
                    }
                    cout<<"\n";
                }*/
                cout << name_xml << " " << rotulo << "\n\n";
            }
        }
    }
    my_xml.close();
    //printf("%s", name_xml);
    return 0;
}
// possiveis erros de empilhamento de tags:
//      tag que "desempilha" (<\exemplo>) pode ter conteudo diferente do topo
//      pode sobrar tags na pilha
//      pode tentar fechar com a pilha vazia

// loop:
// string.find() primeiro elemento '<' (testar e ver se é "nome" e guardar [além de no stack] numa variavel de nome pro output)
// testo se proximo elemento é '/'
//          se é, testo se pilha está vazia e se proximos caracteres batem com o topo 
// se não, acho proximo '>'
// goto loop
