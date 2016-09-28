#include "jhi_window.h" // -> Esse o arquivo que possui as funções referentes a janela, inclusive
#include "jhi_image.h" //-> Esse arquivo é header da estrutura Image
#include "jhi_font.h"  //-> Esse arquivo é header da estrutura Font
#include "jhi_text.h"  //-> Esse arquivo é header da estrutura Text
//as funções de desenhar

//****************************************************************************
//*                                                                          *
//*  Exemplo 4: Carregando um arquivo de Imagem e Printando Texto na Tela	 *
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

	//Estrutura da fonte
	JHI_Font f1;

	//Estrutura de texto
	JHI_Text t1;

	//Essa função irá inicializar a janela e todos os outros módulos incluindo som, fonte.
	jhi_initialize_window(800, 600, 32, WHITE);

	//Nessa função escolhemos o nome da janela, que ficará no topo da tela
	jhi_choice_window_name("Exemplo 4");

	//A função irá carregar a imagem logo_uece, a imagem deve ser no formato bmp
	// é importante colocar o caminho certo do diretório da imagem, o binário fica na pasta bin
	// como a pasta images fica um diretório acima, retrocedemos um diretório, depois entramos na pasta
	//images, o binário deve ser executado a partir da pasta bin/
	jhi_load_image(&img, "../images/uece_logo.bmp");

	//Carregar em f1 a fonte localizada da pasta font, com tamanho de fonte 20
	//essa fonte não contem os caracteres alguns caracteres utilizados no português
	//outras fontes podem conter
	jhi_load_font(&f1, "../fonts/PonyMaker.ttf", 20);


	//Inicialiazar a estrutura de texto
	jhi_init_text(&t1);

	//Seta o texto t1 com a fonte f1 configurada, com o texto do quarto parâmetro
	jhi_set_text(&f1, &t1, BLACK, "Curso de Computacao");

	//posição da imagem
	img.pos.x = 300;
	img.pos.y = 200;

	//posição do texto
	t1.pos.x = 250;
	t1.pos.y = 400;

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

		//desenha o texto na posição (250,400)
		jhi_draw_text(&t1, t1.pos);

	}

	//desalocar a imagem que foi carregada
	jhi_free_image(&img);
	//desalocar a font que foi carregada
	jhi_free_text(&t1);
	//desalocar o texto que foi carregado
	jhi_free_font(&f1);

	//Limpar alocações feitas pela biblioteca
	jhi_quit_and_free();

	return 0;
}
