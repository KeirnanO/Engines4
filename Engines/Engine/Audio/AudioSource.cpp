#include "AudioSource.h"
#include "AudioHandler.h"

AudioSource::AudioSource(std::string soundName_, bool loopSound_, bool is3d_, bool howPlay_) : Component() {
	channelID = -1;
	audioName = soundName_;
	AudioHandler::GetInstance()->LoadSound(soundName_, loopSound_, is3d_, howPlay_);
}

AudioSource::~AudioSource() {

}

bool AudioSource::OnCreate(class GameObject* parent_) {
	parent = parent_;
	return true;
}

void AudioSource::Update(float DeltaTime_) {
	if (channelID != -1) {
		AudioHandler::GetInstance()->UpdatePosition(channelID, parent->GetPosition(), glm::vec3());
	}
}

void AudioSource::Render() const
{
}

void AudioSource::OnDestroy()
{
}

bool AudioSource::isPlaying() {
	return AudioHandler::GetInstance()->isPlaying(channelID);
}

void AudioSource::playSound(float volume_) {
	channelID = AudioHandler::GetInstance()->playSound(audioName, parent->GetPosition(), glm::vec3(), volume_);
}