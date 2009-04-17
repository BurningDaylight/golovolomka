#include "figure.h"
#include "figure_rotator.h"

figure_rotator_t::figure_rotator_t(const figure_t& figure)
{
	FOR_ALL_ENUM(angle)
	{
		m_figure_positions[direction_x][angle] = 
			figure.
				rotate_around_axis(axis_x, (angle_t) angle);
			
		m_figure_positions[direction_x_inv][angle] = 
			figure.
				rotate_around_axis(axis_x, (angle_t) angle).
					rotate_around_axis(axis_y, angle_180);
					
		m_figure_positions[direction_y][angle] = 
			figure.
				rotate_around_axis(axis_x, (angle_t) angle).
					rotate_around_axis(axis_z, angle_90);
			
		m_figure_positions[direction_y_inv][angle] = 
			figure.
				rotate_around_axis(axis_x, (angle_t) angle).
					rotate_around_axis(axis_z, angle_270);
					
		m_figure_positions[direction_z][angle] = 
			figure.
				rotate_around_axis(axis_x, (angle_t) angle).
					rotate_around_axis(axis_y, angle_90);
			
		m_figure_positions[direction_z_inv][angle] = 
			figure.
				rotate_around_axis(axis_x, (angle_t) angle).
				rotate_around_axis(axis_y, angle_270);
	}
}

