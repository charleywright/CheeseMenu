#include "CustomText.hpp"
#include "cstdint"

namespace Big
{
	void CustomText::AddText(std::uint32_t hash, const char *text)
	{
		auto size = std::strlen(text) + 1;
		auto buffer = std::make_unique<char[]>(size);
		std::copy_n(text, size, buffer.get());

		this->m_TextMap.emplace(hash, std::move(buffer));
	}

	void CustomText::RemoveText(std::uint32_t hash)
	{
		this->m_TextMap.erase(hash);
	}

	const char *CustomText::GetText(std::uint32_t hash)
	{
		if (auto it = this->m_TextMap.find(hash); it != this->m_TextMap.end())
		{
			return it->second.get();
		}
		else
		{
			return nullptr;
		}
	}
}
