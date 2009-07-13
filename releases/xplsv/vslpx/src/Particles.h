#ifndef __PARTICLES__
#define __PARTICLES__

#include "math3D.h"
#include "textures.h"

#define GRAVCONST 0.000000000667
#define VELCORRECTION 1000
#define MAXPARTICLESYSTEMS 5
#define MAXPARTICLES 800 // Viva el hard coding!

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
        void Update(float _time);
        //
		void Render();

        int Set(int max_particles);
		
		void setOrigin(Point neworigin);
		void setMinimumEnergy(float energy);
		void setMinimumMass(float mass);
		void setMassInc(float _massInc);
		void setMargin(float _margin);
		void setGravity(float x, float y, float z);
		void setTTL(float _ttl);
    private:
        int ParticleCount;
		int maxParticles;
        Particle ParticleList[MAXPARTICLES];
		Point origin;
		Point gravity;
		float oldtick;
		float minimumEnergy;
		float minimumMass;
		float massInc;
		float margin;
		float ttl;
};

class ParticleManager {
    public:
        ParticleManager();
        virtual ~ParticleManager();
        //
        void Add(ParticleSystem *ps);
        //
        virtual void Update(float _time);
        virtual void Render();
        //
        void Set(TextureImage *texture);
		
    private:
        int ParticleSystemCount;
		int maxParticleSystem;
        ParticleSystem *ParticleSystemList[MAXPARTICLESYSTEMS];
        TextureImage *Texture;
};




#endif
