#include "jhi_window.h" // -> Esse o arquivo que possui as funções referentes a janela
#include "jhi_shapes.h"


//****************************************************************************
//*                                                                          *
//*  Exemplo 2: Denhando formas básicas na janela					     	 *
//*                                                                          *
//*  Year: 2014                                                              *
//*  Version:  1.0                                                           *
//*  Author(s): João Gonçalves <joao.goncalves@larces.uece.br>               *
//*             Henrique Neto <henrique.brandao@larces.uece.br>              *
//****************************************************************************/

int main()
{

	//Definir 5 pontos para desenhar um poligono
	JHI_Point2d points[5] ={
		{.x = 300, .y = 400}, {.x = 450, .y = 450},
		{.x = 500, .y = 550}, {.x = 400, .y = 570},
		{.x = 300, .y = 500}
	};


	//Essa função irá inicializar a janela e todos os outros módulos incluindo som, fonte.
	jhi_initialize_window(800, 600, 32, WHITE);

	//Nessa função escolhemos o nome da janela, que ficará no topo da tela
	jhi_choice_window_name("Exemplo 2");

	//A função get_close_window() retorna se foi clicado no X da janela, dessa forma
	// o retorno é igual a CLOSE, então o loop principal deve ser quebrado, indicando
	//que o programa deve ser fechado

	//ponto para desenhar
	JHI_Point2d point;

	while (jhi_get_close_window() != JHI_CLOSE)
	{
		//Essas duas funções devem sempre esta no começo do loop
		//update() -> função de atualização das ações feitas dentro do loop
		//clean() -> função para limpar a tela, para desenhar novamente na próxima iteração
		jhi_update();
		jhi_clean();

		/* Desenhar Retangulos*/
		jhi_draw_rect(jhi_get_point(50, 50), 50, 150, BLACK);
		
		/* Desenhar Retangulos Preenchidos*/
		jhi_draw_fill_rect(jhi_get_point(250, 50), 50, 150, RED);
		jhi_draw_fill_rect(jhi_get_point(50, 150), 50, 150, BLACK);
		jhi_draw_fill_rect(jhi_get_point(250, 150), 50, 150, YELLOW);
		

		/* Desenhar Quadrados Preenchidos*/
		jhi_draw_fill_rect(jhi_get_point(50, 250), 100, 100, BLACK);
		jhi_draw_fill_rect(jhi_get_point(50, 400), 100, 100, ORANGE);
		jhi_draw_fill_rect(jhi_get_point(200, 250), 100, 100, BLUE);


		/* Desenhar Quadrados*/
		jhi_draw_rect(jhi_get_point(50, 400), 100, 100, BLACK);
		jhi_draw_rect(jhi_get_point(200, 250), 100, 100, BLACK);
		jhi_draw_rect(jhi_get_point(400, 250), 100, 100, RED);


		/* Desenha Circulo*/
		jhi_draw_circle(jhi_get_point(650, 550), 30, BLACK);

		/*Desenha o Pacman*/
		jhi_draw_fill_circle(jhi_get_point(650, 50), 50, RED);
		jhi_draw_fill_rect(jhi_get_point(690, 60), 30, 50, WHITE);
		jhi_draw_fill_circle(jhi_get_point(660, 20), 5, WHITE);

		/* Desenhar Circulos Preenchidos */
		jhi_draw_fill_circle(jhi_get_point(650, 200), 50, GREEN);
		jhi_draw_fill_circle(jhi_get_point(650, 350), 50, BLACK);
		jhi_draw_fill_circle(jhi_get_point(500, 400), 50, ORANGE);


		/* Poligono */
		jhi_draw_polygon(points, 5, RED);


	}

	//Limpar alocações feitas pela biblioteca
	jhi_quit_and_free();

	return 0;
}
