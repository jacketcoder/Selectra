#pragma once
#include"Error.h"
#include"SDL\SDL_mixer.h"
#include<string>
#include<map>
namespace Bengine{
	class SoundEffect{
	public:
		friend class AudioEngine;
		void play(int loops=0);
	private:
			Mix_Chunk* m_chunk = nullptr;
	};
	class Music{
		//palys audio file
		//1 play it time
		Mix_Music* m_music = nullptr;
	public:
		friend class AudioEngine;
		void play(int loops=1);
		static void pause();
		static void stop();
		static void resume();

	};
	class AudioEngine
	{
	public:
		AudioEngine();
		~AudioEngine();
		void init();
		void destroy();
		//only 8 byte 
		SoundEffect loadSoundEffect(const std::string& filePath);
		Music loadMusic(const std::string&filePath);
	private:
		std::map<std::string, Mix_Chunk*>m_effectMap;
		std::map<std::string, Mix_Music*>m_musicMap;
		bool m_isInitialized = false;


	};
}
