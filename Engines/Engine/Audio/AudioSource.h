#ifndef AUDIOSOURCE_H
#define AUDIOSOURCE_H
#include "../Components/Component.h"
#include <string>
#include <glm/glm.hpp>
#include "../Rendering/3D/GameObject.h"

class AudioSource : public Component
{
public:
	AudioSource(std::string soundName_, bool loopSound_, bool is3d_, bool howPlay_);
	~AudioSource();

	virtual bool OnCreate(GameObject* parent_) override;
	virtual void Update(const float DeltaTime_) override;
	virtual void OnDestroy();
	virtual void Render() const;

	bool isPlaying();
	void playSound(float volume);

private:
	int channelID;
	std::string audioName;
};

#endif