#include "StdAfx.h"
#include "Sphere.h"
#include <cmath>

const double GR_PI = 3.1415926535897932384626433832795;

inline void Normalize3(GLdouble *v)
{
   GLdouble len = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
   v[0] /= len;
   v[1] /= len;
   v[2] /= len;
}


CSphere::CSphere(void)
{
    m_radius = 5;
	m_texture = NULL;
}


CSphere::~CSphere(void)
{
}


void CSphere::Draw(int recurse)
{
	if (m_texture != NULL)
	{
		glEnable(GL_TEXTURE_2D);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glBindTexture(GL_TEXTURE_2D, m_texture->TexName());
	}

   GLdouble a[] = {1, 0, 0};
   GLdouble b[] = {0, 0, -1};
   GLdouble c[] = {-1, 0, 0};
   GLdouble d[] = {0, 0, 1};
   GLdouble e[] = {0, 1, 0};
   GLdouble f[] = {0, -1, 0};

   SphereFace(recurse, m_radius, d, a, e);
   SphereFace(recurse, m_radius, a, b, e);
   SphereFace(recurse, m_radius, b, c, e);
   SphereFace(recurse, m_radius, c, d, e);
   SphereFace(recurse, m_radius, a, d, f);
   SphereFace(recurse, m_radius, b, a, f);
   SphereFace(recurse, m_radius, c, b, f);
   SphereFace(recurse, m_radius, d, c, f);

   glDisable(GL_TEXTURE_2D);
}



void CSphere::SphereFace(int p_recurse, double p_radius, double *a,
	double *b, double *c)
{
	if (p_recurse > 1)
	{
		// Compute vectors halfway between the passed vectors?
		GLdouble d[3] = { a[0] + b[0], a[1] + b[1], a[2] + b[2] };
		GLdouble e[3] = { b[0] + c[0], b[1] + c[1], b[2] + c[2] };
		GLdouble f[3] = { c[0] + a[0], c[1] + a[1], c[2] + a[2] };

		Normalize3(d);
		Normalize3(e);
		Normalize3(f);

		SphereFace(p_recurse - 1, m_radius, a, d, f);
		SphereFace(p_recurse - 1, m_radius, d, b, e);
		SphereFace(p_recurse - 1, m_radius, f, e, c);
		SphereFace(p_recurse - 1, m_radius, f, d, e);
	}
	else
	{
		glBegin(GL_TRIANGLES);
		// What's the texture coordinate for this normal?

		// The first vertex
		double u1 = atan2(a[0], a[2]) / (2. * GR_PI) + 0.5;
		double v1 = asin(a[1]) / GR_PI + .5;
		// The second vertex
		double u2 = atan2(b[0], b[2]) / (2. * GR_PI) + 0.5;
		double v2 = asin(b[1]) / GR_PI + .5;
		// The third vertex
		double u3 = atan2(c[0], c[2]) / (2. * GR_PI) + 0.5;
		double v3 = asin(c[1]) / GR_PI + .5;

		// Test for this coordinate on the other side of the
		// texture from the first coordinate.

		if (u2 < 0.75 && u1 > 0.75)
			u2 += 1.0;
		else if (u2 > 0.75 && u1 < 0.75)
			u2 -= 1.0;

		if (u3 < 0.75 && u1 > 0.75)
			u3 += 1.0;
		else if (u3 > 0.75 && u1 < 0.75)
			u3 -= 1.0;

		glNormal3dv(a);
		glTexCoord2f(u1, v1);
		glVertex3d(a[0] * m_radius, a[1] * m_radius, a[2] * m_radius);
		glNormal3dv(b);
		glTexCoord2d(u2, v2);
		glVertex3d(b[0] * m_radius, b[1] * m_radius, b[2] * m_radius);
		glNormal3dv(c);
		glTexCoord2d(u3, v3);
		glVertex3d(c[0] * m_radius, c[1] * m_radius, c[2] * m_radius);
		glEnd();
	}
}