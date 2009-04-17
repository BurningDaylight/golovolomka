#ifndef FIGURE_ROTATOR_H_INCLUDED
#define FIGURE_ROTATOR_H_INCLUDED

#include "figure.h"

struct figure_rotator_t
{
private:
	figure_t m_figure_positions[direction_numof][angle_numof];

public:
	figure_rotator_t() {}
	figure_rotator_t(const figure_t& figure);

	const figure_t& get(const direction_t direction, const angle_t angle) const
	{
		return m_figure_positions[direction][angle];
	}
};

#endif // FIGURE_ROTATOR_H_INCLUDED
