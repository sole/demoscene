#include "Particles.h"
#include <math.h>

// PARTICLE SYSTEM

// Constructor
ParticleSystem::ParticleSystem() {
	this->ParticleCount=0;
	this->maxParticles=MAXPARTICLES;
	this->oldtick=0;
}

// Destructorrr!
ParticleSystem::~ParticleSystem() {
	//delete(this->ParticleList); // No lo borro dinamicamente pq no lo he creado dinamicamente
	//this->ParticleCount=0;
}

void ParticleSystem::Update(float tick) {
	// imagino que esto recalcula la posición y tal de cada particula, respecto a todas las demas...
	int i,j;
	//float gravobjs,m1,m2,r,anguloxy,anguloxz;
	//Point d;
	float elapsedticks;
	elapsedticks=tick-this->oldtick;
	this->oldtick=tick;
	for(i=0;i<this->ParticleCount;i++) {
		
		// Primero actualizo la energia
		/*printf("p: %d X %f Y %f Z %f energy %f\n",i,this->ParticleList[i].position.x,
		this->ParticleList[i].position.y,this->ParticleList[i].position.z,
		this->ParticleList[i].energy);*/
		
		
		this->ParticleList[i].energy=this->ParticleList[i].energy-0.75;//elapsedticks;
		
		
		if((this->ParticleList[i].energy)<=0) {
			//Si se ha muerto, "creo" una nueva en el origen de este sistema de particulas
			//printf("Muerte!! %d energy %f\n",i,this->ParticleList[i].energy);
			this->ParticleList[i].position.x=this->origin.x;
			this->ParticleList[i].position.y=this->origin.y;
			this->ParticleList[i].position.z=this->origin.z;
			this->ParticleList[i].energy=this->minimumEnergy;
			this->ParticleList[i].mass=this->minimumMass;
			this->ParticleList[i].velocity.x=0;
			this->ParticleList[i].velocity.y=0;
			this->ParticleList[i].velocity.z=0;
			this->ParticleList[i].netforce.x=0;
			this->ParticleList[i].netforce.y=0;
			this->ParticleList[i].netforce.z=0;
			
			
		} else {
			float margen=4;
			//printf("no Muerte!! %d energy %f\n",i,this->ParticleList[i].energy);
			this->ParticleList[i].position.x+=(float(rand())/RAND_MAX)*margen-(float(rand())/RAND_MAX)*margen;
			this->ParticleList[i].position.y+=(float(rand())/RAND_MAX)*margen-(float(rand())/RAND_MAX)*margen;
			//this->ParticleList[i].position.x+=(float(rand())/RAND_MAX)*2
			this->ParticleList[i].mass+=0.61;
			
		} // else 
		  // Fta ver, si aunle queda tiempo de vida, el color... el tamaño ... todo eso
	}
}

void ParticleSystem::Render() {
	int i;
	float x,y,z;
	float tam=10,an,alfa;
	glEnable(GL_BLEND);
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	for(i=0;i<this->ParticleCount;i++) {
		alfa=(this->ParticleList[i].energy)/(float(this->minimumEnergy));//(float(this->minimumEnergy))/(this->ParticleList[i].energy);
																		 //printf("%f\n",alfa);
		x=this->ParticleList[i].position.x;
		y=this->ParticleList[i].position.y;
		z=this->ParticleList[i].position.z;
		glColor4f(1,1,1,alfa); // <<<<<<<<<<<- cambiar eso
		an=this->ParticleList[i].mass;//+this->ParticleList[i].energy;//;
			/*glBegin(GL_QUADS);
		glVertex3f(x,y,z);
		glVertex3f(x+an,y,z);
		glVertex3f(x+an,y+an,z);
		glVertex3f(x,y+an,z);
		glEnd();*/
			
		glBegin(GL_QUADS);
		
		glNormal3f( 0.0f, 0.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y,  z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x+an,y,z);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x+an,y+an,z);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x,y+an,z);
		
		glEnd();
			
			
	}
	glDisable(GL_BLEND);
	
	//exit(0);
}

int ParticleSystem::Set(int max_particles) {
	// No se pq cojones deberia tener este metodo
	//this->ParticleCount=max_particles;
	// supongo que al ejecutarlo, deberia cargarse las particulas que pasen de max
	int i,maximum;
	if(max_particles > this->maxParticles)
	{
		maximum = this->maxParticles;
	}
	else
	{
		maximum = max_particles;
	}

	for(i=0;i<maximum;i++) {
		this->ParticleList[i].position.x=this->origin.x;
		this->ParticleList[i].position.y=this->origin.y;
		this->ParticleList[i].position.z=0;//this->origin.z;
			this->ParticleList[i].energy=(float(rand())/RAND_MAX)*this->minimumEnergy; // pa q no empiecen toas al mismo tiempo
			this->ParticleList[i].mass=this->minimumMass;
			this->ParticleList[i].velocity.x=0;
			this->ParticleList[i].velocity.y=0;
			this->ParticleList[i].velocity.z=0;
			this->ParticleList[i].netforce.x=0;
			this->ParticleList[i].netforce.y=0;
			this->ParticleList[i].netforce.z=0;
			
	}
	this->ParticleCount=maximum;
	return(max_particles);
}


void ParticleSystem::setOrigin(Point neworigin) {
	this->origin.x=neworigin.x;
	this->origin.y=neworigin.y;
	this->origin.z=neworigin.z;
}


void ParticleSystem::setMinimumEnergy(float energy) {
	this->minimumEnergy=energy;
}

void ParticleSystem::setMinimumMass(float mass) {
	this->minimumMass=mass;
}
// SIguiente claseeeeeeeeeeeeeee PARTICLE MANAGER

// Constructor
ParticleManager::ParticleManager() {
	this->maxParticleSystem=MAXPARTICLESYSTEMS;
}

// Destructor
ParticleManager::~ParticleManager() {
	int i;
	for(i=0;i<this->ParticleSystemCount;i++) {
		//this->ParticleSystemList[i].~ParticleSystem();
	}
}

// añadir!
void ParticleManager::Add(ParticleSystem *ps) {
	// A saco. Listas predefinidas de particulas!! XDDD
	if(this->ParticleSystemCount<this->maxParticleSystem) {
		// Copio la referencia
		this->ParticleSystemList[this->ParticleSystemCount]=ps;
		
		// incremento el numero de sistemas de particulas
		this->ParticleSystemCount++;
	}
}

void ParticleManager::Render() {
	int i;
	for(i=0;i<this->ParticleSystemCount;i++) {
		this->ParticleSystemList[i]->Render();
	}
}

void ParticleManager::Update(float tick) {
	int i;
	for(i=0;i<this->ParticleSystemCount;i++) {
		this->ParticleSystemList[i]->Update(tick);
	}
}

void ParticleManager::Set(TextureImage *texture) {
	this->Texture=texture;
}

