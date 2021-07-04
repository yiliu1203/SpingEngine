#include "Keyboard.h"
#include "Window.h"

bool Keyboard::KeyIsPressed(unsigned char keyCode) const noexcept
{
	return keyStates[keyCode];
}

Keyboard::Event Keyboard::ReadKey() noexcept
{
	if (keyBuffer.size() > 0)
	{
		auto keyEvent = keyBuffer.front();
		keyBuffer.pop();
		return keyEvent;
	}
	else
	{
		return Keyboard::Event();
	}
}

bool Keyboard::KeyIsEmpty() const noexcept
{
	return keyBuffer.size() == 0;
}

void Keyboard::FlushKey() noexcept
{
	keyBuffer = std::queue<Event>();
}

char Keyboard::ReadChar() noexcept
{
	if (charBuffer.size() > 0)
	{
		char c = charBuffer.front();
		charBuffer.pop();
		return c;
	}
	else
	{
		return 0;
	}
}

bool Keyboard::CharIsEmpty() const noexcept
{
	return charBuffer.size() == 0;
}

void Keyboard::FlushChar() noexcept
{
	charBuffer = std::queue<char>();
}

void Keyboard::Flush() noexcept
{
	FlushKey();
	FlushChar();
}

void Keyboard::EnableAutoRepeat() noexcept
{
	autoRepeatEnabled = true;
}

void Keyboard::DisableAutoRepeat() noexcept
{
	autoRepeatEnabled = false;
}

// private:
void Keyboard::OnKeyPressed(unsigned char keyCode) noexcept
{
	keyStates[keyCode] = true;
	keyBuffer.push(Event(Event::Type::Press, keyCode));
	TrimBuff(keyBuffer);
}

void Keyboard::OnkeyRelease(unsigned char keyCode) noexcept
{
	keyStates[keyCode] = false;
	keyBuffer.push(Event(Event::Type::Release, keyCode));
	TrimBuff(keyBuffer);
}

void Keyboard::OnChar(char c) noexcept
{
	charBuffer.push(c);
	TrimBuff(charBuffer);
}

void Keyboard::ClearState() noexcept
{
	keyStates.reset();
}

template<typename T>
void Keyboard::TrimBuff(std::queue<T>& buff) noexcept
{
	while (buff.size() > bufferSize)
	{
		OutputDebugString("TrimBufffffffffffffffffffffffffffffffff\n");
		buff.pop();
	}
}

