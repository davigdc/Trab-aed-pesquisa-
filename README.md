Membros grupo: Davi G, Diego R, Gilson J, Juan L, Bruno V


	Legenda variaveis:

* --> int
** --> void
*** --> dado (struct)
**** --> bool

//========= Funcoes globais:
	*** dado: usada para armazenamento dos dados do arquivo, usada em todos os tipos de armazenamento, (vetor do tipo dado, dado da celula e No nas listas, arvore e tabela Hash).

	* StartCounter e GetCounter: para analise do tempo da pesquisa em cada tipo de armazenamento.

	*** OpenFile: funcao que le o arquivo, recebe o numeros de linhas a ler e se a variavel op, esta que permite abrir o arquivo original ou ja organizado em ordem crescente (usado em pesquisa binaria).

	** Imprimir_pesquisa: Funcao utilizada no main do codigo apos cada pesquisa, esta que retorna a variavel dado correspondente a room_id procurada. Imprime todos os dados para leitura do usuario.

//========= Pesquisa sequencial 
	*** Pesquisa_sequencial: Recebe um vetor do tipo dado(que contem os dados do arquivo) e uma chave de busca, faz a pesquisa de forma sequencial ate o fim do vetor, caso ache a chave de busca ela retorna o vetor na posicao desejada e diz quantas buscas foram necessarias, caso nao ache ela retorna a variavel "falso" do tipo dado que esta zerada, o reconhecimento esta no main.

//========= Pesquisa binaria 
	*** Pesquisa_binaria: Recebe o vetor do tipo  dado (que contem os dados do arquivo, nesta funcao o vetor passado ja é organizado com o campo room_id de forma crescente), a chave de busca e o fim do vetor, a pesquisa é feita "quebrando o vetor no meio" no estilo MergeSort e retorna como na pesquisa anterior, caso nao ache a chave de busca ela retorna da mesma maneira a "falso" do tipo dado que esta zerada.

//========= Pesquisa arvore
	-->Procedimentos da arvore seguem metodos pelo professor lecionados. O preenchimento dela é passado o vetor do tipo dado, posicao a posicao até o final.
	*** Pesquisar: Recebe a arvore e a chave de busca. Ela comeca pela Raiz caso a chave seja maior ela vai para o lado direito e caso contrario para o esquerdo, até achar a chave de busca, caso nao ache ela retorna a variavel "falso" do tipo dado que esta zerada, o reconhecimento esta no main.

//========= Pesquisa tabela hash
	-->Procedimentos da tabela hash seguem metodos pelo professor lecionados. Sua insercao é feita inserindo os campo do vetor até o fim, o numero primo para uso na funcao *FuncaoHash como sugerido no algoritimo de Sedgewick, onde se prucura o numero potencia de 2 menor e mais proximo do total de elementos, nesse caso foi 65536, e escolhe o primo mais proximo abaixo desse numero, 65521, sendo esse o tamanho das linhas da matriz, caso haja colisao entre as posicoes na insercao o elemento é inserido na lista da posicao definida pela *FuncaoHash.
	*** PesquisarHash: esta funcao recebe como parametro a tabela hash, e a chave de busca, ela usa a *FuncaoHash para definir em qual linha da tabela o elemento esta, definida a linha, a funcao chama uma pesquisa de lista (***PesquisarH), para que caso haja colisao na insercao dos numeros esta procure na lista o elemento procurado, reduzindo bastante o tempo de busca.    

//========= Pesquisa Quantidade de quartos disponiveis nas cidades
	***Contador_de_cidades:		



//========= Pesquisa sequencial preco quarto
	* Pesquisa_sequencial_cidade: recebe o vetor do tipo dado, e faz a comparacao sequencial dos valores (campo price), retornando o valor do menor e maior valor do quarto.
