#pragma once
#include <queue>

class Mouse {

	friend class Window;
public:
	class Event
	{
	public:
		enum class Type
		{
			LPress,
			LRelease,
			RPress,
			RRelease,
			WheelUp,
			WheelDown,
			Move,
			Invalid
		};

	private:
		Type type;
		bool _isLeftPressed;
		bool _isRightPressed;
		int x, y;

	public:
		Event() noexcept
			: type(Event::Type::Invalid), _isLeftPressed(false), _isRightPressed(false), x(0), y(0)
		{
		}

		Event(Type t, const Mouse& parent) noexcept
			:type(t)
		{
			_isLeftPressed = parent.IsLeftPressed();
			_isRightPressed = parent.IsRightPressed();
			auto pos = parent.GetPos();
			x = pos.first;
			y = pos.second;
		}

		Type GetType() const noexcept
		{
			return type;
		}
		bool IsValid() const noexcept
		{
			return type == Type::Invalid;
		}
		bool IsLeftPressed() const noexcept
		{
			return _isLeftPressed;
		}
		bool IsRightPressed() const noexcept
		{
			return _isRightPressed;
		}
		std::pair<int, int> GetPos() const noexcept
		{
			return { x, y };
		}
	};

public:
	Mouse() = default;
	Mouse(const Mouse&) = delete;
	Mouse& operator =(const Mouse&) = delete;
	std::pair<int, int> GetPos() const noexcept;
	bool IsLeftPressed() const noexcept;
	bool IsRightPressed() const noexcept;
	Mouse::Event Read() noexcept;
	bool IsEmpty() const noexcept;
	void Flush() noexcept;

private:
	void OnMouseMove(int x, int y) noexcept;
	void OnLeftPressed(int x, int y) noexcept;
	void OnLeftReleased(int x, int y) noexcept;
	void OnRightPressed(int x, int y) noexcept;
	void OnRightRelease(int x, int y) noexcept;
	void OnWheelUp(int x, int y) noexcept;
	void OnWheelDown(int x, int y) noexcept;
	void OnWheelDelta(int x, int y, int delta) noexcept;
	void TrimBuffer() noexcept;

private:
	static constexpr unsigned int buffSize = 16u;
	int x, y;
	bool isLeftPressed;
	bool isRightPressed;
	int wheelDelta;
	std::queue<Event> buffer;
};