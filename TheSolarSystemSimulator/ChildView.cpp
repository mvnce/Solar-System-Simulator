
// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "TheSolarSystemSimulator.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;

// CChildView

void DrawCircle(float cx, float cy, float cz,float r, int num_segments)
{
	glBegin(GL_LINE_LOOP);
	for (int ii = 0; ii < num_segments; ii++)
	{
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle 

		float x = r * cosf(theta);//calculate the x component 
		float z = r * sinf(theta);//calculate the y component 
		cy = 0;

		glVertex3f(x + cx, cy,z + cz);//output vertex 

	}
	glEnd();
}


CChildView::CChildView()
{
	m_camera.Set(20, 10, 50, 0, 0, 0, 0, 1, 0);
	
	m_t_mercury.LoadFile(L"TheSolarSystemSimulator/textures/mercury.bmp");
	m_mercury.SetTexture(&m_t_mercury);

	m_t_venus.LoadFile(L"TheSolarSystemSimulator/textures/venus.bmp");
	m_venus.SetTexture(&m_t_venus);

	m_t_earth.LoadFile(L"TheSolarSystemSimulator/textures/worldmap.bmp");
	m_earth.SetTexture(&m_t_earth);

	m_t_mars.LoadFile(L"TheSolarSystemSimulator/textures/mars.bmp");
	m_mars.SetTexture(&m_t_mars);

	m_t_jupiter.LoadFile(L"TheSolarSystemSimulator/textures/jupiter.bmp");
	m_jupiter.SetTexture(&m_t_jupiter);

	m_t_saturn.LoadFile(L"TheSolarSystemSimulator/textures/saturn.bmp");
	m_saturn.SetTexture(&m_t_saturn);

	m_t_uranus.LoadFile(L"TheSolarSystemSimulator/textures/uranus.bmp");
	m_uranus.SetTexture(&m_t_uranus);

	m_t_neptune.LoadFile(L"TheSolarSystemSimulator/textures/neptune.bmp");
	m_neptune.SetTexture(&m_t_neptune);

	m_t_sun.LoadFile(L"TheSolarSystemSimulator/textures/sun.bmp");
	m_sun.SetTexture(&m_t_sun);

	m_spinTimer = 0;
	m_angleSpd = deque<double> (8, 0); ///< initial angles, default value 0
	m_selfRotSpd = deque<double>(8, 15); ///< initial self rotation speed, default value 100

	m_orbitRot = false;
	m_selfRot = false;

	srand(time(NULL)); ///< initialize random seed

	for (int i = 0; i <= 7; i++)
	{
		m_initialAng.push_back(rand() % 360 + 0);
	}

}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, COpenGLWnd)
	ON_WM_PAINT()
	ON_COMMAND(ID_FILE_SAVE32771, &CChildView::OnFileSave32771)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_OPTION_SPIN, &CChildView::OnOptionSpin)
	ON_WM_TIMER()
	ON_COMMAND(ID_OPTION_SELFROTATION, &CChildView::OnOptionSelfrotation)
END_MESSAGE_MAP()



// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!COpenGLWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}


void CChildView::OnGLDraw(CDC* pDC)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//
	// Set up the camera
	//

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Determine the screen size so we can determine the aspect ratio
	int width, height;
	GetSize(width, height);
	GLdouble aspectratio = GLdouble(width) / GLdouble(height);

	// Set the camera parameters
	gluPerspective(25.,         // Vertical FOV degrees.
		aspectratio, // The aspect ratio.
		10.,         // Near clipping 40/130
		200.);       // Far clipping

	// Set the camera location
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//
	// Set up the camera
	//
	GetSize(width, height);
	m_camera.Apply(width, height);

	//
	// Some standard parameters
	//

	// Enable depth test
	glEnable(GL_DEPTH_TEST);

	// Cull backfacing polygons
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	// Enable lighting
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);

	GLfloat lightpos[] = { 0.00001, 0.00001, 0.00001, 1. };

	// emitting light mat
	GLfloat mat_emission[] = { 1., 1., 1., 1.0 };

	///glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

	glPushMatrix();
	DrawCircle(0, 0, 0, 2, 50);
	DrawCircle(0, 0, 0, 3.5, 50);
	DrawCircle(0, 0, 0, 5, 50);
	DrawCircle(0, 0, 0, 7.5, 50);
	DrawCircle(0, 0, 0, 26, 50);
	DrawCircle(0, 0, 0, 47.5, 50);
	DrawCircle(0, 0, 0, 96, 50);
	DrawCircle(0, 0, 0, 150.5, 50);
	glPopMatrix();

	glPushMatrix();
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_emission);
	m_sun.SetRadius(0.2);
	m_sun.Draw();
	glPopMatrix();

	glPushMatrix();
	glRotated(m_angleSpd[0] / 3 + m_initialAng[0], 0, 1, 0);
	glTranslated(0, 0, 2);
	glRotated(m_selfRotSpd[4], 0, 1, 0);
	m_mercury.SetRadius(0.19);
	m_mercury.Draw();
	glPopMatrix();

	glPushMatrix();
	glRotated(m_angleSpd[1] / 3 + m_initialAng[1], 0, 1, 0);
	glTranslated(0, 0, 3.5);
	glRotated(m_selfRotSpd[4], 0, 1, 0);
	m_venus.SetRadius(0.475);
	m_venus.Draw();
	glPopMatrix();

	glPushMatrix();
	glRotated(m_angleSpd[2] / 3 + m_initialAng[2], 0, 1, 0);
	glTranslated(0, 0, 5);
	glRotated(m_selfRotSpd[4], 0, 1, 0);
	m_earth.SetRadius(0.5);
	m_earth.Draw();
	glPopMatrix();

	glPushMatrix();
	glRotated(m_angleSpd[3] / 3 + m_initialAng[3], 0, 1, 0);
	glTranslated(0, 0, 7.5);
	glRotated(m_selfRotSpd[4], 0, 1, 0);
	m_mars.SetRadius(0.26);
	m_mars.Draw();
	glPopMatrix();

	glPushMatrix();
	glRotated(m_angleSpd[4] / 3 + m_initialAng[4], 0, 1, 0);
	glTranslated(0, 0, 26);
	glRotated(m_selfRotSpd[4], 0, 1, 0);
	m_jupiter.SetRadius(5.49);
	m_jupiter.Draw();
	glPopMatrix();

	glPushMatrix();
	glRotated(m_angleSpd[5] / 3 + m_initialAng[5], 0, 1, 0);
	glTranslated(0, 0, 47.5);
	glRotated(m_selfRotSpd[4], 0, 1, 0);
	m_saturn.SetRadius(4.60);
	m_saturn.Draw();
	glPopMatrix();

	glPushMatrix();
	glRotated(m_angleSpd[6] / 3 + m_initialAng[6], 0, 1, 0);
	glTranslated(0, 0, 96);
	glRotated(m_selfRotSpd[4], 0, 1, 0);
	m_uranus.SetRadius(1.99);
	m_uranus.Draw();
	glPopMatrix();

	glPushMatrix();
	glRotated(m_angleSpd[7] / 3 + m_initialAng[7], 0, 1, 0);
	glTranslated(0, 0, 150.5);
	glRotated(m_selfRotSpd[4], 0, 1, 0);
	m_neptune.SetRadius(1.93);
	m_neptune.Draw();
	glPopMatrix();
}


void CChildView::OnFileSave32771()
{
	OnSaveImage();
}


void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_camera.MouseDown(point.x, point.y);

	COpenGLWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_camera.MouseMove(point.x, point.y, nFlags))
		Invalidate();

	COpenGLWnd::OnMouseMove(nFlags, point);
}


void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
	m_camera.MouseDown(point.x, point.y, 2);

	COpenGLWnd::OnRButtonDown(nFlags, point);
}


void CChildView::OnOptionSpin()
{
	if (!m_orbitRot)
		m_orbitRot = true;
	else
		m_orbitRot = false;


	if (m_spinTimer == 0)
	{
		// Create the timer
		m_spinTimer = SetTimer(1, 30, NULL);
	}

	if (!m_selfRot && !m_orbitRot)
	{
		// Destroy the timer
		KillTimer(m_spinTimer);
		m_spinTimer = 0;
	}
}


void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	if (m_orbitRot)
	{
		m_angleSpd[0] += 4.147727 * 5;
		m_angleSpd[1] += 1.622222 * 5;
		m_angleSpd[2] += 1.000000 * 5;
		m_angleSpd[3] += 0.531915 * 5;
		m_angleSpd[4] += 0.084034 * 5;
		m_angleSpd[5] += 0.033696 * 5;
		m_angleSpd[6] += 0.011905 * 5;
		m_angleSpd[7] += 0.006098 * 5;
	}

	if (m_selfRot)
	{
		m_selfRotSpd[0] += 15;
		m_selfRotSpd[1] += 10;
		m_selfRotSpd[2] += 15;
		m_selfRotSpd[3] += 10;
		m_selfRotSpd[4] += 15;
		m_selfRotSpd[5] += 10;
		m_selfRotSpd[6] += 15;
		m_selfRotSpd[7] += 10;
	}

	Invalidate();

	COpenGLWnd::OnTimer(nIDEvent);
}


void CChildView::OnOptionSelfrotation()
{
	if (!m_selfRot)
		m_selfRot = true;
	else
		m_selfRot = false;


	if (m_spinTimer == 0)
	{
		// Create the timer
		m_spinTimer = SetTimer(1, 30, NULL);
	}

	if (!m_selfRot && !m_orbitRot)
	{
		// Destroy the timer
		KillTimer(m_spinTimer);
		m_spinTimer = 0;
	}
}
