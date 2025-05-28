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

private:
    static inline ISoundSystem* m_SoundSystem = nullptr;
};
