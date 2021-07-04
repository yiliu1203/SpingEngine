#include "Mouse.h"
#include <Windows.h>

std::pair<int, int> Mouse::GetPos() const noexcept
{
	return { x, y };
}

bool Mouse::IsLeftPressed() const noexcept
{
	return isLeftPressed;
}

bool Mouse::IsRightPressed() const noexcept
{
	return isRightPressed;
}

Mouse::Event Mouse::Read() noexcept
{
	if (buffer.size() > 0)
	{
		auto event = buffer.front();
		buffer.pop();
		return event;
	}
	else
	{
		return Mouse::Event();
	}
}

bool Mouse::IsEmpty() const noexcept
{
	return buffer.empty();
}

void Mouse::Flush() noexcept
{
	buffer = std::queue<Mouse::Event>();
}

void Mouse::OnMouseMove(int x, int y) noexcept
{
	this->x = x;
	this->y = y;
	buffer.push(Mouse::Event(Mouse::Event::Type::Move, *this));
	this->TrimBuffer();
}

void Mouse::OnLeftPressed(int x, int y) noexcept
{
	this->x = x;
	this->y = y;
	buffer.push(Mouse::Event(Mouse::Event::Type::LPress, *this));
	this->TrimBuffer();
}

void Mouse::OnLeftReleased(int x, int y) noexcept
{
	this->x = x;
	this->y = y;
	buffer.push(Mouse::Event(Mouse::Event::Type::LRelease, *this));
	this->TrimBuffer();

}

void Mouse::OnRightPressed(int x, int y) noexcept
{
	this->x = x;
	this->y = y;
	buffer.push(Mouse::Event(Mouse::Event::Type::RPress, *this));
	this->TrimBuffer();
}

void Mouse::OnRightRelease(int x, int y) noexcept
{
	this->x = x;
	this->y = y;
	buffer.push(Mouse::Event(Mouse::Event::Type::RRelease, *this));
	this->TrimBuffer();
}

void Mouse::OnWheelUp(int x, int y) noexcept
{
	this->x = x;
	this->y = y;
	buffer.push(Mouse::Event(Mouse::Event::Type::WheelUp, *this));
	this->TrimBuffer();
}

void Mouse::OnWheelDown(int x, int y) noexcept
{
	this->x = x;
	this->y = y;
	buffer.push(Mouse::Event(Mouse::Event::Type::WheelDown, *this));
	this->TrimBuffer();
}

void Mouse::OnWheelDelta(int x, int y, int delta) noexcept
{
	wheelDelta += delta;
	while (wheelDelta > WHEEL_DELTA)
	{
		wheelDelta -= WHEEL_DELTA;
		OnWheelUp(x, y);
	};
	while (wheelDelta < -WHEEL_DELTA)
	{
		wheelDelta += WHEEL_DELTA;
		OnWheelDown(x, y);
	}

}

void Mouse::TrimBuffer() noexcept
{
	while (buffer.size() > buffSize)
	{
		buffer.pop();
	}
}

