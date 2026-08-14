#include "SoundService.h"

namespace dae
{
	std::unique_ptr<SoundSystem> SoundLocator::m_Instance = std::make_unique<NullSoundSystem>();
}