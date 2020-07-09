#pragma once

struct NotVec2
{
	int m_x;
	int m_y;
	NotVec2(const int& x, const int& y) : m_x(x), m_y(y) {}
	NotVec2(NotVec2& second)
	{
		this->m_x = second.m_x;
		this->m_y = second.m_y;
	}
	inline NotVec2& operator+(NotVec2& second)
	{
		return NotVec2(this->m_x + second.m_x, this->m_y + second.m_y);
	}
};