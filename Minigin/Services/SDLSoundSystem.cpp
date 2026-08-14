#include "SDLSoundSystem.h"
/*

#include <SDL3/SDL.h>
#include <SDL3_mixer/SDL_mixer.h>

namespace dae
{
	class SDLSoundSystem::Impl
	{
	public:
		std::unordered_map<std::string, MIX_Audio*> m_SoundCache;
		MIX_Mixer* m_Mixer{ nullptr };
	};

	SDLSoundSystem::SDLSoundSystem()
	{
		m_pImpl = std::make_unique<Impl>();

		MIX_Init();

		m_pImpl->m_Mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);

		m_AudioThread = std::thread(&SDLSoundSystem::AudioThread, this);
	}

	SDLSoundSystem::~SDLSoundSystem()
	{
		{
			std::lock_guard lock(m_Mutex);
			m_Running = false;
		}

		m_CondVar.notify_one();
		m_AudioThread.join();

		for (auto& [path, audio] : m_pImpl->m_SoundCache)
			MIX_DestroyAudio(audio);

		m_pImpl->m_SoundCache.clear();
	}

	void SDLSoundSystem::Play(SoundId SoundID, float volume)
	{
		auto it = m_SoundPaths.find(SoundID);
		if (it == m_SoundPaths.end())
			return;

		SoundRequest request{ it->second, volume };
		{
			std::lock_guard lock(m_Mutex);
			m_RequestQueue.push(request);
		}
		m_CondVar.notify_one();
	}

	void SDLSoundSystem::RegisterSound(SoundId soundID, const std::string& filePath)
	{
		m_SoundPaths.emplace(soundID, filePath);
	}

	void SDLSoundSystem::AudioThread()
	{
		while (true)
		{
			std::unique_lock lock(m_Mutex);
			m_CondVar.wait(lock, [this]
				{
					return !m_RequestQueue.empty() || !m_Running;
				});

			if (!m_Running && m_RequestQueue.empty())
				break;

			std::queue<SoundRequest> localQueue;
			std::swap(localQueue, m_RequestQueue);
			lock.unlock();

			while (!localQueue.empty())
			{
				const auto& request = localQueue.front();
				ProcessRequest(request);
				localQueue.pop();
			}
		}
	}

	void SDLSoundSystem::ProcessRequest(const SoundRequest& request)
	{
		auto it = m_pImpl->m_SoundCache.find(request.filePath);
		if (it == m_pImpl->m_SoundCache.end())
		{
			MIX_Audio* audio = MIX_LoadAudio(m_pImpl->m_Mixer, request.filePath.c_str(), false);

			if (!audio)
				return;

			it = m_pImpl->m_SoundCache.emplace(request.filePath, audio).first;
		}

		MIX_SetMixerGain(m_pImpl->m_Mixer, request.volume);
		MIX_PlayAudio(m_pImpl->m_Mixer, it->second);
	}
}
*/