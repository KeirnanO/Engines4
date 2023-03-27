#include "AudioHandler.h"

std::unique_ptr<AudioHandler> AudioHandler::audioInstance = nullptr;
std::map<std::string, FMOD::Sound*> AudioHandler::soundMap = std::map<std::string, FMOD::Sound*>();
std::map<int, FMOD::Channel*> AudioHandler::channelMap = std::map<int, FMOD::Channel*>();

AudioHandler::AudioHandler() {

}

AudioHandler::~AudioHandler() {

}

AudioHandler* AudioHandler::GetInstance() {
	if (audioInstance.get() == nullptr) {
		audioInstance.reset(new AudioHandler);
	}
	return audioInstance.get();
}

bool AudioHandler::Initialize(glm::vec3 pos_ = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 vel_ = glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3 forward_ = glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3 up_ = glm::vec3(0.0f, 1.0f, 0.0f)) 
{
	FMOD::System_Create(&FMODSystem);
	if (!FMODSystem->getNumDrivers(0)) {
		return false;
	}
	else {
		FMODSystem->init(5, FMOD_INIT_NORMAL | FMOD_3D | FMOD_INIT_3D_RIGHTHANDED, nullptr);
		FMOD_VECTOR fmodPos = glmToFmod(pos_);
		FMOD_VECTOR fmodVel = glmToFmod(vel_);
		FMOD_VECTOR fmodForward = glmToFmod(forward_);
		FMOD_VECTOR fmodUp = glmToFmod(up_);
		FMODSystem->set3DListenerAttributes(0, &fmodPos, &fmodVel, &fmodForward, &fmodUp);
		return true;
	}
}

void AudioHandler::OnDestroy() {
	for (auto m : soundMap) {
		m.first.empty();
		m.second->release();
		m.second = nullptr;
		//delete &m
	}
	for (auto m : channelMap) {

		m.second->stop();
		m.second = nullptr;
		//delete &m;
	}

	FMODSystem->release();
	FMODSystem = nullptr;
}

void AudioHandler::Update()
{
	FMODSystem->update();
}

FMOD_VECTOR AudioHandler::glmToFmod(glm::vec3 vector_)
{
	FMOD_VECTOR fmodVec;
	fmodVec.x = vector_.x;
	fmodVec.y = vector_.y;
	fmodVec.z = vector_.z;

	return fmodVec;
}

void AudioHandler::LoadSound(std::string name_, bool loop_, bool is3d_, bool howPlay_) {

	if (GetSound(name_)) {
		return;
	}

	FMOD_MODE mode = FMOD_DEFAULT;
	FMOD_MODE loopMode;
	FMOD_MODE is3d;
	FMOD_MODE streamType;

	if (loop_)
		loopMode = FMOD_LOOP_NORMAL; 
	else
		loopMode = FMOD_LOOP_OFF; 

	if (is3d_)
		is3d = FMOD_3D; 
	else 
		is3d = FMOD_2D; 

	if (howPlay_)
		streamType = FMOD_CREATESTREAM; 
	else 
		streamType = FMOD_CREATECOMPRESSEDSAMPLE; 

	mode = mode | loopMode | is3d | streamType;

	FMOD::Sound* sound = nullptr;
	std::string soundPath = "./Resources/" + name_;
	FMODSystem->createSound(soundPath.c_str(), mode, nullptr, &sound);
	soundMap.emplace(name_, sound);
}

FMOD::Sound* AudioHandler::GetSound(std::string name_) {

	for (auto m : soundMap) {
		if (m.first == name_) {
			return m.second;
		}
	}
	return nullptr;
}

int AudioHandler::playSound(std::string name_, glm::vec3 pos_, glm::vec3 vel_ = glm::vec3(0.0, 0.0, 0.0), float volume_ = 1.0f) {

	int channelID = -1;
	if (!GetSound(name_)) {
		LoadSound(name_, false, true, false);
	}

	FMOD::Channel* audioChannel = nullptr;

	FMODSystem->playSound(soundMap[name_], nullptr, true, &audioChannel);
	FMOD_VECTOR FMODPosition = glmToFmod(pos_);
	FMOD_VECTOR FMODVelocity = glmToFmod(vel_);
	FMOD_MODE is3d = FMOD_3D;

	if (audioChannel->getMode(&is3d) == FMOD_3D)
	{
		audioChannel->set3DAttributes(&FMODPosition, &FMODVelocity);
	}
	audioChannel->setVolume(volume_);

	audioChannel->setPaused(false);
	channelID = channelCount;
	channelCount++;

	channelMap.emplace(channelID, audioChannel);
	return channelID;
}

void AudioHandler::UpdatePosition(int channelID_, glm::vec3 pos_, glm::vec3 vel_ = glm::vec3(0.0f, 0.0f, 0.0f)) {
	if (channelMap[channelID_]) {
		FMOD_VECTOR FMODPos = glmToFmod(pos_);
		FMOD_VECTOR FMODVel = glmToFmod(vel_);
		channelMap[channelID_]->set3DAttributes(&FMODPos, &FMODVel);
	}
}

bool AudioHandler::isPlaying(int channelID_) {
	if (channelMap[channelID_]) {
		bool isPlaying;
		channelMap[channelID_]->isPlaying(&isPlaying);
		return isPlaying;
	}
	return false;
}