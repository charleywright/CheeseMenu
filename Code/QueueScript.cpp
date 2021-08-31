#include "QueueScript.hpp"

namespace Cheese
{
	bool QueueScript::IsInitialized()
	{
		return m_Initialized;
	}

	ScriptType QueueScript::GetType()
	{
		return ScriptType::Game;
	}

	void QueueScript::Initialize()
	{
		m_Initialized = true;
	}

	void QueueScript::Destroy()
	{
	}

	void QueueScript::Delay(std::chrono::milliseconds delay) {
		m_DelayStart = std::chrono::steady_clock::now();
		m_DelayLength = delay;
	}

	void QueueScript::Add(std::function<void()> f)
	{
		m_queue.push(f);
	}

	void QueueScript::Tick()
	{
		std::chrono::duration<double, std::milli> delay_passed = std::chrono::high_resolution_clock::now() - m_DelayStart;
		if (delay_passed >= m_DelayLength) {
			if (!m_queue.empty()) {
				m_queue.front()();
				m_queue.pop();
			}
		}
	}
}
