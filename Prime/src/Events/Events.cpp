#include "Events/Events.h"
#include "Core/Window.h"
#include "Core/Log.h"
#include <map>
#include <mutex>

namespace prm {
	void EventDispatcher::init(const std::function<bool(const Ref<Event>&)>& function)
	{
		this->m_handler = function;
		m_thread = std::thread([=]() {
			while (this->getIsDispatcherOn())
			{
				std::lock_guard<std::mutex> guard(m_mut);
				while (!this->getEventBuffer().empty()) {
					auto e = this->getEventBuffer().front();
					if (!e->Handled && e.get() != nullptr) {
						e->Handled |= this->getHandler()(e);
					}
					else {
						this->getEventBuffer().pop();
					}

				}
			}
			PRM_CORE_INFO("dispatcher done");

		});
	}
	void EventDispatcher::destroy()
	{
		this->isDestroyed = true;
		this->stopDispatch();
		this->m_thread.join();
	}
	EventDispatcher::~EventDispatcher()
	{
		if (!this->isDestroyed) {
			this->stopDispatch();
			this->m_thread.join();
		}
	}
}