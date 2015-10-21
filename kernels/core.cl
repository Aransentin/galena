float boxdist( float3 ray, float3 pos, float size )
{
	float delta = 0.0005;
	float t0 = ( -delta - pos.x )*ray.x;
	float t1 = ( size + delta - pos.x )*ray.x;
	float tmax = max( t0, t1 );
	
	float t2 = ( -delta - pos.y )*ray.y;
	float t3 = ( size + delta - pos.y )*ray.y;
	tmax = min( tmax, max( t2, t3 ) );
	
	float t4 = ( -delta - pos.z )*ray.z;
	float t5 = ( size + delta - pos.z )*ray.z;
	tmax = min( tmax, max( t4, t5 ) );
	
	return tmax;
}

kernel void core( write_only image2d_t tex, Camera cam, const global OTnode * tree )
{
	/* Calculate camera ray */
	const int u = get_global_id( 0 );
	const int v = get_global_id( 1 );
	float3 pos = cam.pos;
	float3 dir = normalize( cam.vo + cam.vx*(u/(float)DIM_X) + cam.vy*(v/(float)DIM_Y) );
	float3 invdir = 1.0f/dir;
	
	for( int dlp=0; dlp<1024; dlp++ )
	{
		/* Current voxel position of ray */
		const int vx = convert_int_rtn( pos.x );
		const int vy = convert_int_rtn( pos.y );
		const int vz = convert_int_rtn( pos.z );
		
		/* If we are outside the world, bail */
		if( as_uint(vx) >= WDIM || as_uint(vy) >= WDIM || as_uint(vz) >= WDIM )
		{
			write_imagef( tex, (int2)(u,v), (float4)( 0.0, 0.0, 0.0, 1.0 ) );
			return;
		}
		
		/* Delve into the world tree */
		const global OTnode * cnode = tree;
		for( int i=0; i<WDEPTH; i++ )
		{
			/* Find offset bit */
			int obit = 0;
			obit += 1*(( vx >> (WDEPTH-i-1) ) & 1);
			obit += 2*(( vy >> (WDEPTH-i-1) ) & 1);
			obit += 4*(( vz >> (WDEPTH-i-1) ) & 1);
			
			/* Is our bit set? If so, delve deeper. */
			if( cnode->bf & (1u << obit) )
			{
				if( i != WDEPTH-1 )
				{
					const uint base = (cnode->p & 0x00ffffffu);
					const uchar mask = ~(0xffu>>obit);
					cnode = tree + ( base + popcount( cnode->bf & mask ) );
				}
				else
				{
					/* Last iteration, so we have collided with a voxel */
					write_imagef( tex, (int2)(u,v), (float4)( 0.4, 0.6, 0.9, 1.0 ) );
					return;
				}
			}
			else
			{
				/* Our bit was not set, trace onwards */
				const float blockw = convert_float( WDIM >> (i+1) );
				const float3 blockoffs = fmod( pos, blockw );
				const float raylen = boxdist( invdir, blockoffs, blockw );
				pos += dir*raylen;
				break;
			}
		}
	}
}
