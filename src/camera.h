#pragma once

typedef struct{
	double pos[3];
	double trg[3];
	double dir[3];
	double nor[3];
	double aspect;
	double lens;
	
	struct{
		float pos[4];
		float vo[4];
		float vx[4];
		float vy[4];
	}cl;	
} Camera;

void camera_normal_fix( Camera * camera );
void camera_lookat( Camera * camera );
void camera_cl_update( Camera * camera );
