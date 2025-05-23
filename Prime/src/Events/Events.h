#pragma once
#include <functional>
#include <thread>
#include <mutex>
#include <string>
#include <vector>
#include <queue>
#include "Core/Core.h"
#define BIT(x) (1 << x)

namespace prm {
	class Window;

	// Events in Prime are currently blocking, meaning when an event occurs it
	// immediately gets dispatched and must be dealt with right then an there.
	// For the future, a better strategy might be to buffer events in an event
	// bus and process them during the "event" part of the update stage.

	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class Event
	{
	public:
		virtual ~Event() = default;

		bool Handled = false;

		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}
	};

	class EventDispatcher
	{
	public:

		EventDispatcher():isDispatcherOnline(true), isDestroyed(false) {

		}
		using EventMap = std::queue<Ref<Event>>;
		void init(const std::function<bool(const Ref<Event>&)>& function);
		bool getIsDispatcherOn() const { return this->isDispatcherOnline; }
		void stopDispatch() {
			this->isDispatcherOnline = false;
		};
		void pushEvent(const Ref<Event>& e) {
			std::lock_guard<std::mutex> guard(m_mut);
			this->m_events.push(e);
		}
		const std::function<bool(const Ref<Event>&)>& getHandler() { return m_handler; }
		EventMap& getEventBuffer() { return m_events; }
		void destroy();
		virtual ~EventDispatcher();
	private:
		bool isDispatcherOnline;
		std::mutex m_mut;
		std::function<bool(const Ref<Event>&)> m_handler;
		Ref<Window> m_window;
		std::thread m_thread;
		EventMap m_events;
		bool isDestroyed;
	};
}
