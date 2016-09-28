#include "jhi_window.h" // -> Esse o arquivo que possui as funções referentes a janela
#include "jhi_image.h" //-> Esse arquivo é header da estrutura Image
#include "jhi_font.h"  //-> Esse arquivo é header da estrutura Font
#include "jhi_text.h"  //-> Esse arquivo é header da estrutura Text


//****************************************************************************
//*                                                                          *
//*  Exemplo 5: Carregando um arquivo de Imagem, deixando a cor	 		 	 *
//*  de fundo da imagem transparente e cortando a imagem                     *                                                   *
//*  Year: 2014                                                              *
//*  Version:  1.0                                                           *
//*  Author(s): João Gonçalves <joao.goncalves@larces.uece.br>               *
//*             Henrique Neto <henrique.brandao@larces.uece.br>              *
//****************************************************************************/


//largura e altura de cada pac_man na figura
#define WIDHT_PAC_MAN 32
#define HEIGHT_PAC_MAN 32

int main()
{
	//Cada posição do vetor representa a posição x do pac_man na imagem
	//como são 8 pac_man's são 8 posições (x,y);
	JHI_Point2d vet_pos[]  = {
	{0,0}, {WIDHT_PAC_MAN,0}, {0, HEIGHT_PAC_MAN}, {WIDHT_PAC_MAN, HEIGHT_PAC_MAN},
	{0, HEIGHT_PAC_MAN*2}, {WIDHT_PAC_MAN, HEIGHT_PAC_MAN*2}, {0, HEIGHT_PAC_MAN*3}, {WIDHT_PAC_MAN,HEIGHT_PAC_MAN*3}
	};

	int i;

	//Estrutura de imagem
	JHI_Image img;

	//Essa função irá inicializar a janela e todos os outros módulos incluindo som, fonte.
	jhi_initialize_window(800, 600, 32, BLACK);

	//Nessa função escolhemos o nome da janela, que ficará no topo da tela
	jhi_choice_window_name("Exemplo 5");

	//A cor de fundo do pac_man é o azul de valores (0, 0, 255) do modelo RGB
	// a cor BLUE contém esses valores, logo esse cor de fundo fica transparente
	jhi_load_image_with_transparent_color(&img, "../images/pac_man.png", BLUE);


	//posição de cada clip na tela
	JHI_Point2d point_clip;

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

		for (i = 0; i < 8; i++)
		{
			//desenha os 8 pedaços do pac_man da figura separadamente
			point_clip.x = vet_pos[i].x + 100;
			point_clip.y = vet_pos[i].y + 100;
			jhi_draw_image_with_clip(&img, point_clip, vet_pos[i], WIDHT_PAC_MAN,  HEIGHT_PAC_MAN);
		}


	}

	//desalocar a imagem que foi carregada
	jhi_free_image(&img);

	//Limpar alocações feitas pela biblioteca
	jhi_quit_and_free();

	return 0;
}
