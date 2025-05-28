#pragma once
#include "SoundSystem.h"

class ServiceLocator {
public:
    static void Provide(ISoundSystem* service) {
        m_SoundSystem = service;
    }

    static ISoundSystem& GetSoundSystem() {
        return *m_SoundSystem;
    }

    static void DestroyAll() {
		if (m_SoundSystem != nullptr)
            delete m_SoundSystem;
    }
private:
    static inline ISoundSystem* m_SoundSystem = nullptr;
};
