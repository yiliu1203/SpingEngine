#pragma once
#include <bitset>
#include <queue>

class Keyboard
{
	friend class Window;

public:
	class Event
	{
	public:
		enum class Type
		{
			Press,
			Release,
			Invalid,
		};
	private:
		Type type;
		unsigned char code;

	public:
		Event() : type(Type::Invalid), code(0u)
		{}

		Event(Type type, unsigned char code) : type(type), code(code)
		{
		}

		bool IsPress() const noexcept
		{
			return type == Type::Press;
		}

		bool IsRelease() const noexcept
		{
			return type == Type::Release;
		}

		bool IsValid() const noexcept
		{
			return type != Type::Invalid;
		}
	};

	Keyboard() = default;
	Keyboard(const Keyboard&) = delete;
	Keyboard& operator= (const Keyboard&) = delete;

	bool KeyIsPressed(unsigned char keyCode) const noexcept;
	Event ReadKey() noexcept;
	bool KeyIsEmpty() const noexcept;
	void FlushKey() noexcept;

	char ReadChar() noexcept;
	bool CharIsEmpty() const noexcept;
	void FlushChar() noexcept;
	void Flush() noexcept;

	void EnableAutoRepeat() noexcept;
	void DisableAutoRepeat() noexcept;

private:
	void OnKeyPressed(unsigned char keyCode) noexcept;
	void OnkeyRelease(unsigned char keyCode) noexcept;
	void OnChar(char c) noexcept;
	void ClearState() noexcept;

	template<typename T>
	void TrimBuff(std::queue<T>& buff) noexcept;

private:
	static constexpr unsigned int nKeys = 256u;
	static constexpr unsigned int bufferSize = 16u;
	bool autoRepeatEnabled = false;
	std::bitset<nKeys> keyStates;
	std::queue<Event> keyBuffer;
	std::queue<char> charBuffer;


};

