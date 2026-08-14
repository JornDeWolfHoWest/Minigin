#include "SoundService.h"
#include <string>
#include <thread>
#include <mutex>
#include <queue>
#include <unordered_map>
/*

namespace dae
{
	class SDLSoundSystem final : public SoundSystem
	{
	public:
		SDLSoundSystem();
		~SDLSoundSystem() override;

		SDLSoundSystem(const SDLSoundSystem& other) = delete;
		SDLSoundSystem(SDLSoundSystem&& other) = delete;
		SDLSoundSystem& operator=(const SDLSoundSystem& other) = delete;
		SDLSoundSystem& operator=(SDLSoundSystem&& other) = delete;

		void Play(SoundId soundID, float volume) override;
		void RegisterSound(SoundId soundID, const std::string& filePath) override;

	private:

		struct SoundRequest
		{
			std::string filePath;
			float volume;
		};

		void AudioThread();
		void ProcessRequest(const SoundRequest& request);

		std::thread m_AudioThread;
		std::mutex m_Mutex;
		std::condition_variable m_CondVar;
		std::queue<SoundRequest> m_RequestQueue;
		std::unordered_map<SoundId, std::string> m_SoundPaths;
		bool m_Running{ true };

		class Impl;
		std::unique_ptr<Impl> m_pImpl;
	};
}

*/