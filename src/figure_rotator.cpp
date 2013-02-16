#include "figure.h"
#include "figure_rotator.h"

void figure_rotator_t::init(const figure_t& figure_in)
{
  m_source_figure.copy(figure_in);

	FOR_ALL_ENUM(angle)
	{
		m_figure_positions[direction_x][angle] =
			m_source_figure.
				rotate_around_axis(axis_x, (angle_t) angle);

		m_figure_positions[direction_x_inv][angle] =
			m_source_figure.
				rotate_around_axis(axis_x, (angle_t) angle).
					rotate_around_axis(axis_y, angle_180);

		m_figure_positions[direction_y][angle] =
			m_source_figure.
				rotate_around_axis(axis_x, (angle_t) angle).
					rotate_around_axis(axis_z, angle_90);

		m_figure_positions[direction_y_inv][angle] =
			m_source_figure.
				rotate_around_axis(axis_x, (angle_t) angle).
					rotate_around_axis(axis_z, angle_270);

		m_figure_positions[direction_z][angle] =
			m_source_figure.
				rotate_around_axis(axis_x, (angle_t) angle).
					rotate_around_axis(axis_y, angle_90);

		m_figure_positions[direction_z_inv][angle] =
			m_source_figure.
				rotate_around_axis(axis_x, (angle_t) angle).
				rotate_around_axis(axis_y, angle_270);
	}

}

