#pragma once
#include "Script.hpp"
#include <memory>

namespace Big
{
	class FeaturesScript : public Script
	{
	public:
		explicit FeaturesScript() = default;
		~FeaturesScript() noexcept = default;

		bool IsInitialized() override;
		ScriptType GetType() override;
		void Initialize() override;
		void Destroy() override;
		void Tick() override;
	private:
		bool m_Initialized{};
		int tickCount = 0;
	};

	inline std::shared_ptr<FeaturesScript> g_FeaturesScript;
}
