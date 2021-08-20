#pragma once
#include "Script.hpp"
#include <queue>
#include <chrono>
#include <functional>
#include <memory>

namespace Big
{
	class QueueScript : public Script
	{
	public:
		explicit QueueScript() = default;
		~QueueScript() noexcept = default;

		bool IsInitialized() override;
		ScriptType GetType() override;
		void Initialize() override;
		void Destroy() override;
		void Tick() override;
		void Add(std::function<void()> f);
		void Delay(std::chrono::milliseconds delay);

	private:
		bool m_Initialized{};
		std::queue<std::function<void()>> m_queue;
		std::chrono::time_point<std::chrono::high_resolution_clock> m_DelayStart;
		std::chrono::duration<double, std::milli> m_DelayLength;
	};

	inline std::shared_ptr<QueueScript> g_QueueScript;
}
