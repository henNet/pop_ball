#include "jhi_shapes.h"


void jhi_draw_point(JHI_Point2d point, JHI_Color col)
{
	jhi_print_pixel(point.x, point.y, col);
}


void jhi_draw_line(JHI_Point2d s_point, JHI_Point2d d_point, JHI_Color col)
{
	double x = d_point.x - s_point.x;
	double y = d_point.y - s_point.y;
	double line_lenght = sqrt( x*x + y*y );
	double factor_x = x / line_lenght;
	double factor_y = y / line_lenght;
	int i;

	x = s_point.x;
	y = s_point.y;

	for(i = 0; i < line_lenght; i+=1)
	{
		jhi_print_pixel(x, y, col);
		x += factor_x;
		y += factor_y;
	}
}

void jhi_draw_rect(JHI_Point2d point, int height, int base, JHI_Color col)
{
	/* Draw four line building the rectangle or square */
	JHI_Point2d s_point, d_point;
	s_point = point;
	d_point.x = point.x + base;
	d_point.y = point.y;
	jhi_draw_line(point, d_point, col);
	d_point.x = point.x;
	d_point.y = point.y + height;
	jhi_draw_line(point, d_point, col);
	s_point.x = point.x + base;
	d_point.x = point.x + base;
	d_point.y = point.y + height;
	jhi_draw_line(s_point, d_point, col);
	s_point.x = point.x;
	s_point.y = point.y + height;
	d_point.x = point.x + base;
	d_point.y = point.y + height;
	jhi_draw_line(s_point, d_point, col);
}

void jhi_draw_fill_rect(JHI_Point2d point, int height, int base, JHI_Color col)
{
	double dy,dx;
	int x_c;
	JHI_Point2d dr_point;
	/* Fill the Rect */
	point.x = point.x + base/2;
	point.y = point.y + height/2;

	for(dy = 0; dy <= height/2; dy += 1.0)
	{
		dx = base/2;
		x_c = point.x - dx;

		for (; x_c <= point.x + dx; x_c++)
		{
			dr_point.x = x_c;
			dr_point.y = point.y + dy;
			jhi_draw_point(dr_point, col);
			dr_point.y = point.y - dy;
			jhi_draw_point(dr_point, col);
		}
	}
}

void jhi_draw_circle(JHI_Point2d center_point, float radius, JHI_Color col)
{
	double error = (double)-radius;
	double x = (double)radius - 0.5;
	double y = (double)0.5;
	double cx = center_point.x - 0.5;
	double cy = center_point.y - 0.5;

	while (x >= y)
	{
		jhi_print_pixel((int)(cx + x), (int)(cy + y), col);
		jhi_print_pixel((int)(cx + y), (int)(cy + x), col);

		if (x != 0)
		{
				jhi_print_pixel((int)(cx - x), (int)(cy + y), col);
				jhi_print_pixel((int)(cx + y), (int)(cy - x), col);
		}

		if (y != 0)
		{
				jhi_print_pixel((int)(cx + x), (int)(cy - y), col);
				jhi_print_pixel((int)(cx - y), (int)(cy + x), col);
		}

		if (x != 0 && y != 0)
		{
				jhi_print_pixel((int)(cx - x), (int)(cy - y), col);
				jhi_print_pixel((int)(cx - y), (int)(cy - x), col);
		}

		error += y;
		++y;
		error += y;

		if (error >= 0)
		{
			--x;
			error -= x;
			error -= x;
		}
	}
}

void jhi_draw_fill_circle(JHI_Point2d center_point, int radius, JHI_Color col)
{
	double r = (double)radius;
	double dy,dx;
	int x;

	for(dy = 0; dy <= r; dy += 1.0)
	{

		dx = floor(sqrt((2.0 * r * dy) - (dy * dy)));
		x = center_point.x - dx;

		for (; x <= center_point.x + dx; x++)
		{
			jhi_print_pixel(x, center_point.y + r - dy, col);
			jhi_print_pixel(x, center_point.y - r + dy, col);

		}
	}
}

void jhi_draw_polygon(JHI_Point2d *points, int num_points, JHI_Color col)
{
	int i;

	for(i = 0; i < num_points - 1; i++)
	{
		jhi_draw_line(points[i], points[i + 1], col);
	}

	jhi_draw_line(points[i], points[0], col);
}

void jhi_draw_fill_polygon(JHI_Point2d *points, int n, JHI_Color color, Uint8 alpha)
{
	Sint16 x[n];
	Sint16 y[n];
	int i;
	for (i = 0; i < n; i++)
	{
		x[i] = points[i].x;
		y[i] = points[i].y;
	}

	filledPolygonRGBA(jhi_get_window_screen(), x, y, n, colors[color].r,
			colors[color].g, colors[color].b, alpha);

}

int jhi_is_colid(JHI_Point2d p1, int h1, int w1, JHI_Point2d p2, int h2, int w2)
{
	if (p1.y >= p2.y + h2 || p2.y >= p1.y + h1)
	{
		return 0;
	}

	if (p2.x + w2 <= p1.x || p1.x + w1 <= p2.x )
	{
		return 0;
	}

	return 1;
}

JHI_Point2d jhi_get_central_pos(int win_w, int win_h, int obj_w, int obj_h)
{
	JHI_Point2d pos;

	pos.x = (win_w - obj_w) / 2;
	pos.y = (win_h - obj_h) / 2;

	return pos;
}

JHI_Point2d jhi_get_point(int x, int y)
{
	JHI_Point2d pos;

	pos.x = x;
	pos.y = y;

	return pos;
}

int jhi_dist_normal(double v, int max, double lambda)
{

	double f = 1.0 / (2 * PI) * pow(E, (- (v*v)/2));

	f *= max;

	return (int)f;
}

int jhi_dist_expo(double v, int max, double lambda)
{
	v = lambda * pow(E, lambda * -v);

	v *= max;

	return (int)v;
}

int jhi_dist_default(double v, int max, double lambda)
{
	v *= max;
	return (int)v;
}

void jhi_transition_square_color(JHI_Color color, DistFunction dist, int length, double lambda)
{
	JHI_List list;
	JHI_Point2d p,*pp;
	int x,y,index;

	jhi_list_init(&list, sizeof(JHI_Point2d));

	for (x = 0; x <= jhi_get_width_window(); x+=length)
	{
		for (y = 0; y <= jhi_get_height_window(); y+=length)
		{
			p = jhi_get_point(x, y);
			jhi_list_insert_element(&list, &p);
		}
	}


	while(!jhi_list_is_empty(&list))
	{
		index = dist_funcs[dist].f(RAND_01, jhi_list_get_size(&list), lambda) % jhi_list_get_size(&list);

		pp = jhi_list_node_get_data_by_index(&list, index);

		jhi_draw_fill_rect(*pp, length, length, color);

		jhi_list_remove_element(&list, pp);

		jhi_update();
	}


}

void jhi_transition_circle_color(JHI_Color color, DistFunction dist, int length, double lambda)
{
	JHI_List list;
	JHI_Point2d p,*pp;
	int x,y,index;

	jhi_list_init(&list, sizeof(JHI_Point2d));

	for (x = 0; x <= jhi_get_width_window(); x+=length)
	{
		for (y = 0; y <= jhi_get_height_window(); y+=length)
		{
			p = jhi_get_point(x, y);
			jhi_list_insert_element(&list, &p);
		}
	}


	while(!jhi_list_is_empty(&list))
	{
		index = dist_funcs[dist].f(RAND_01, jhi_list_get_size(&list), lambda) % jhi_list_get_size(&list);

		pp = jhi_list_node_get_data_by_index(&list, index);

		jhi_draw_fill_circle(*pp, length, color);

		jhi_list_remove_element(&list, pp);

		jhi_update();
	}


}


