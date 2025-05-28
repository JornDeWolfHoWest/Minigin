#pragma once
#include <string>

// ISoundSystem.h
class ISoundSystem {
public:
    virtual ~ISoundSystem() = default;
    virtual void PlaySound(const std::string& soundID) = 0;
    virtual void LoadSound(const std::string& soundID, const std::string& path) = 0;
};

// SDLSoundSystem.h
class SDLSoundSystem : public ISoundSystem {
public:
    SDLSoundSystem(std::string& audioBasePath);
    ~SDLSoundSystem() override;

    void PlaySound(const std::string& soundID) override;
    void LoadSound(const std::string& soundID, const std::string& path) override;

private:
    struct Impl;
    Impl* m_pImpl;
};

// SDLSoundSystem.cpp
#include <map>
#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <memory>
#include <functional>
#include "SDL_Mixer.h"


struct SDLSoundSystem::Impl {
    std::map<std::string, Mix_Chunk*> m_Sounds;
    std::mutex m_QueueMutex;
    std::condition_variable m_CondVar;
    std::queue<std::function<void()>> m_EventQueue;
    bool m_Running = true;
    std::thread m_Thread;
	std::string& m_AudioBasePath;

    Impl(std::string& audioBasePath) : m_AudioBasePath(audioBasePath)
    {
        Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
        m_Thread = std::thread([this] {
            while (m_Running) {
                std::function<void()> task;
                {
                    std::unique_lock lock(m_QueueMutex);
                    m_CondVar.wait(lock, [this] { return !m_EventQueue.empty() || !m_Running; });
                    if (!m_Running) break;
                    task = std::move(m_EventQueue.front());
                    m_EventQueue.pop();
                }
                task();
            }
            });
    }

    ~Impl() {
        m_Running = false;
        m_CondVar.notify_all();
        if (m_Thread.joinable()) m_Thread.join();

        for (auto& [_, chunk] : m_Sounds)
            Mix_FreeChunk(chunk);

        Mix_CloseAudio();
    }

    void Load(const std::string& id, const std::string& path) {
        printf("Attempting to load: %s\n", path.c_str());
        Mix_Chunk* chunk = Mix_LoadWAV((m_AudioBasePath + path).c_str());
        if (chunk) {
            m_Sounds[id] = chunk;
		}
        else {
            printf("Failed to load sound: %s, Error: %s\n", path.c_str(), Mix_GetError());
        }
    }

    void Play(const std::string& id) {
        auto it = m_Sounds.find(id);
        if (it != m_Sounds.end()) {
            Mix_PlayChannel(-1, it->second, 0);
        }
    }

    void Enqueue(std::function<void()> task) {
        {
            std::scoped_lock lock(m_QueueMutex);
            m_EventQueue.push(std::move(task));
        }
        m_CondVar.notify_one();
    }
};

SDLSoundSystem::SDLSoundSystem(std::string& audioBasePath) : m_pImpl(new Impl(audioBasePath)) {}
SDLSoundSystem::~SDLSoundSystem() = default;

void SDLSoundSystem::LoadSound(const std::string& id, const std::string& path) {
    // Lambda to use multithreading sucesfully
    m_pImpl->Enqueue([=] { m_pImpl->Load(id, path); });
}

void SDLSoundSystem::PlaySound(const std::string& id) {
    // Lambda to use multithreading succesfully
    m_pImpl->Enqueue([=] { m_pImpl->Play(id); });
}
