#include "jhi_window.h" // -> Esse o arquivo que possui as funções referentes a janela, inclusive
#include "jhi_image.h" //-> Esse arquivo é header da estrutura Image
#include "jhi_shapes.h"
//as funções de desenhar

//****************************************************************************
//*                                                                          *
//*  Exemplo 3: Carregando um arquivo de Imagem					     	 	 *
//*                                                                          *
//*  Year: 2014                                                              *
//*  Version:  1.0                                                           *
//*  Author(s): João Gonçalves <joao.goncalves@larces.uece.br>               *
//*             Henrique Neto <henrique.brandao@larces.uece.br>              *
//****************************************************************************/

int main()
{

	//Estrutura de imagem
	JHI_Image img;

	//Essa função irá inicializar a janela e todos os outros módulos incluindo som, fonte.
	jhi_initialize_window(800, 600, 32, WHITE);

	//Nessa função escolhemos o nome da janela, que ficará no topo da tela
	jhi_choice_window_name("Exemplo 3");

	//A função irá carregar a imagem logo_uece
	// é importante colocar o caminho certo do diretório da imagem, o binário fica na pasta bin
	// como a pasta images fica um diretório acima, retrocedemos um diretório, depois entramos na pasta
	//images, o binário deve ser executado a partir da pasta bin/
	jhi_load_image(&img, "../images/uece_logo.bmp");

	//posição da imagem

	img.pos.x = 300;
	img.pos.y = 200;

	//A função get_close_window() retorna se foi clicado no X da janela, dessa forma
	// o retorno é igual a CLOSE, então o loop principal deve ser quebrado, indicando
	//que o programa deve ser fechado
	while (jhi_get_close_window() != JHI_CLOSE)
	{
		//Essas duas funções devem sempre esta no começo do loop
		//update() -> função de atualização das ações feitas dentro do loop
		//clean() -> função para limpar a tela, para desenhar novamente na próxima iteração
		jhi_update();
		jhi_clean();

		//desenha a imagem na posição (300,200)
		jhi_draw_image(&img, img.pos);

	}

	//desalocar a imagem que foi carregada
	jhi_free_image(&img);

	//Limpar alocações feitas pela biblioteca
	jhi_quit_and_free();

	return 0;
}
