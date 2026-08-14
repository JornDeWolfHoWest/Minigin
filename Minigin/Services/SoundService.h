#pragma once
#include <vector>
#include <memory>
#include <string>


namespace dae
{
	using SoundId = unsigned short;
	class SoundSystem
	{
	public:
		virtual ~SoundSystem() = default;
		virtual void Play(SoundId SoundID, float volume) = 0;
		virtual void RegisterSound(SoundId soundID, const std::string& filePath) = 0;
	};

	class NullSoundSystem final : public SoundSystem
	{
	public:
		void Play(SoundId, float) override {};
		void RegisterSound(SoundId, const std::string&) override {};
	};

	class SoundLocator final
	{
	public:
		static SoundSystem& GetAudio()
		{
			return *m_Instance;
		}

		static void RegisterAudio(std::unique_ptr<SoundSystem>&& service)
		{
			if (service)
				m_Instance = std::move(service);
			else
				m_Instance = std::make_unique<NullSoundSystem>();
		}

	private:
		static std::unique_ptr<SoundSystem> m_Instance;
	};
}
