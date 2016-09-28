#include "jhi_window.h" // -> Esse o arquivo que possui as funções referentes a janela
#include "jhi_image.h"
#include "jhi_timer.h"
#include "jhi_list.h"
#include "jhi_rand.h"
#include "jhi_shapes.h"

//****************************************************************************
//*                                                                          *
//*  Exemplo 14: Tela de Transição					     			 		 *
//*                                                                          *
//*  Year: 2014                                                              *
//*  Version:  1.0                                                           *
//*  Author(s): João Gonçalves <joao.goncalves@larces.uece.br>               *
//*             Henrique Neto <henrique.brandao@larces.uece.br>              *
//****************************************************************************/



int main()
{
		JHI_Image img;

		srand(time(0));

		//Essa função irá inicializar a janela e todos os outros módulos incluindo som, fonte.
		jhi_initialize_window(800, 600, 32, BLACK);

		//Nessa função escolhemos o nome da janela, que ficará no topo da tela
		jhi_choice_window_name("Exemplo 14");

		//A função get_close_window() retorna se foi clicado no X da janela, dessa forma
		// o retorno é igual a CLOSE, então o loop principal deve ser quebrado, indicando
		//que o programa deve ser fechado

		jhi_load_image(&img, "../images/game_cenario.png");

		img.pos.x = 0;
		img.pos.y = 0;

		while (jhi_get_close_window() != JHI_CLOSE)
		{
			//Essas duas funções devem sempre esta no começo do loop
			//update() -> função de atualização das ações feitas dentro do loop
			//clean() -> função para limpar a tela, para desenhar novamente na próxima iteração
			jhi_update();
			jhi_clean();

			jhi_draw_image(&img, img.pos);

			jhi_transition_circle_color(BLACK, DEFAULT_DIST, 30, 0.1);

			jhi_delay_seconds(5);
		}

		//Limpar alocações feitas pela biblioteca
		jhi_quit_and_free();

	return 0;
}
