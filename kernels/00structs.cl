typedef struct{
	float3 pos;
	float3 vo;
	float3 vx;
	float3 vy;
} Camera;

typedef struct{
	union{
		uint p;
		struct{
			uchar p1, p2, p3;
			uchar bf;
		};
	};
} OTnode;
