#include "math3D.h"
#include "textures.h"

#define GRAVCONST 0.000000000667
#define VELCORRECTION 1000
#define MAXPARTICLESYSTEMS 5
#define MAXPARTICLES 100 // Viva el hard coding!

struct Particle {
    Point    position;
    Point    velocity;
	Point	 netforce;
    float       energy;
    float       mass;
};

class ParticleSystem {
public:
	ParticleSystem();	
	virtual ~ParticleSystem();
	//
	//void Add(Particle *p);
	//
	void Update(float tick);
	//
	void Render();
	
	int Set(int max_particles);
	
	void setOrigin(Point neworigin);
	void setMinimumEnergy(float energy);
	void setMinimumMass(float mass);
private:
        int ParticleCount;
	int maxParticles;
	Particle ParticleList[MAXPARTICLES];
	Point origin;
	float oldtick;
	float minimumEnergy;
	float minimumMass;
};

class ParticleManager {
public:
	ParticleManager();
	virtual ~ParticleManager();
	//
	void Add(ParticleSystem *ps);
	//
	virtual void Update(float tick);
	virtual void Render();
	//
	void Set(TextureImage *texture);
	
private:
        int ParticleSystemCount;
	int maxParticleSystem;
	ParticleSystem *ParticleSystemList[MAXPARTICLESYSTEMS];
	TextureImage *Texture;
};




