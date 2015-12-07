#include "camera.h"
#include <stdio.h>
#include <math.h>

static inline void normalize( double *vec )
{
    const double len = sqrt( vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2] );
    vec[0] /= len;
    vec[1] /= len;
    vec[2] /= len;
}

static inline void mul_cross( double *restrict res, double *restrict v1, double *restrict v2 )
{
    res[0] = v1[1] * v2[2] - v1[2] * v2[1];
    res[1] = v1[2] * v2[0] - v1[0] * v2[2];
    res[2] = v1[0] * v2[1] - v1[1] * v2[0];
}

void camera_normal_fix( Camera *camera )
{
    double side[3];
    mul_cross( side, camera->dir, camera->nor );
    normalize( side );
    mul_cross( camera->nor, side, camera->dir );
    normalize( camera->nor );
}

void camera_lookat( Camera *camera )
{
    double dir[3] = {
        camera->trg[0] - camera->pos[0], camera->trg[1] - camera->pos[1], camera->trg[2] - camera->pos[2],
    };
    normalize( dir );
    camera->dir[0] = dir[0];
    camera->dir[1] = dir[1];
    camera->dir[2] = dir[2];
}

void camera_cl_update( Camera *camera )
{
    double side[3];
    mul_cross( side, camera->dir, camera->nor );

    const double frstC[3] = {
        camera->lens * camera->dir[0], camera->lens * camera->dir[1], camera->lens * camera->dir[2],
    };

    const double frstN[3] = {
        0.5 * camera->nor[0], 0.5 * camera->nor[1], 0.5 * camera->nor[2],
    };

    const double frstS[3] = {
        0.5 * side[0] * camera->aspect, 0.5 * side[1] * camera->aspect, 0.5 * side[2] * camera->aspect,
    };

    const double vo[3] = {
        frstC[0] - frstN[0] - frstS[0], frstC[1] - frstN[1] - frstS[1], frstC[2] - frstN[2] - frstS[2],
    };

    camera->cl.pos[0] = (float)camera->pos[0];
    camera->cl.pos[1] = (float)camera->pos[1];
    camera->cl.pos[2] = (float)camera->pos[2];

    camera->cl.vo[0] = (float)vo[0];
    camera->cl.vo[1] = (float)vo[1];
    camera->cl.vo[2] = (float)vo[2];

    camera->cl.vx[0] = (float)( frstS[0] * 2.0 );
    camera->cl.vx[1] = (float)( frstS[1] * 2.0 );
    camera->cl.vx[2] = (float)( frstS[2] * 2.0 );

    camera->cl.vy[0] = (float)( frstN[0] * 2.0 );
    camera->cl.vy[1] = (float)( frstN[1] * 2.0 );
    camera->cl.vy[2] = (float)( frstN[2] * 2.0 );
}
