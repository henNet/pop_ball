#include "jhi_window.h" // -> Esse o arquivo que possui as funções referentes a janela
#include "jhi_font.h"  //-> Esse arquivo é header da estrutura Font
#include "jhi_text.h"  //-> Esse arquivo é header da estrutura Text
#include <string.h>

//****************************************************************************
//*                                                                          *
//*  Exemplo 8: Capturando posição x,y quando o mouse é movido	 	     *
//*                                                                          *
//*  Year: 2014                                                              *
//*  Version:  1.0                                                           *
//*  Author(s): João Gonçalves <joao.goncalves@larces.uece.br>               *
//*             Henrique Neto <henrique.brandao@larces.uece.br>              *
//****************************************************************************/

int main()
{

	int i;

	//essa estrutura contém os campos x,y atual do mouse e captura algum evento ocorrido
	JHI_MouseSt mouse;

	//Estrutura da fonte
	JHI_Font f1;

	//Estrutura de texto
	JHI_Text t1;

	char txt[20];

	//Essa função irá inicializar a janela e todos os outros módulos incluindo som, fonte.
	jhi_initialize_window(800, 600, 32, BLACK);

	//Nessa função escolhemos o nome da janela, que ficará no topo da tela
	jhi_choice_window_name("Exemplo 8");

	//Carregar em f1 a fonte localizada da pasta font, com tamanho de fonte 40
	//essa fonte não contem os caracteres alguns caracteres utilizados no português
	//outras fontes podem conter
	jhi_load_font(&f1, "../fonts/PonyMaker.ttf", 30);

	//inicializar texto
	jhi_init_text(&t1);

	//inicializar mouse
	jhi_init_mouse(&mouse);

	t1.pos.x = 250;
	t1.pos.y = 300;

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


		//Esse for captura todos os eventos de mouse e teclado
		//em cada iteração pegamos um evento
		for (i = 0; i < jhi_get_number_of_events(); i++)
		{
			//Pega o status do mouse no evento i
			mouse = jhi_get_mouse_status(i);

			//se foi clicado botão esquerdo do mouse
			if (mouse.mouse_event == MOUSE_MOTION)
			{
				//zerar a string
				memset(txt, 0, sizeof(char) * 20);

				//printar as informações em txt
				sprintf(txt, "X  %d  Y  %d", mouse.x, mouse.y);

				//Seta o texto t1 com a fonte f1 configurada, com o texto do quarto parâmetro
				jhi_set_text(&f1, &t1, RED, txt);
			}
		}

		//desenha o texto na posição (250,300)
		jhi_draw_text(&t1, t1.pos);

	}

	//desalocar a font que foi carregada
	jhi_free_text(&t1);
	//desalocar o texto que foi carregado
	jhi_free_font(&f1);

	//Limpar alocações feitas pela biblioteca
	jhi_quit_and_free();

	return 0;
}
