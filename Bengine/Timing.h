namespace Bengine{
	class FpsLimiter{
	public:
		FpsLimiter();
		void init(float _maxFPS);
		void setMaxFPS(float _maxFPS);
		void begin();
		//returns current fps
		float end();
	private:
		void calculateFPS();
		float _maxFPS;
		float _fps;
		float _frameTime;
		unsigned int _startTicks;
	};
}