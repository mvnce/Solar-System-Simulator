
// ChildView.h : interface of the CChildView class
//

#include <deque>
#include <stdlib.h>
#include <time.h>
#include "graphics/OpenGLWnd.h"
#include "graphics/GrTexture.h"
#include "graphics/GrCamera.h"
#include "Sphere.h"

#pragma once


// CChildView window

class CChildView : public COpenGLWnd
{
// Construction
public:
	CChildView();

// Attributes
public:

// Operations
public:

// Overrides
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildView();

	// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	void OnGLDraw(CDC* pDC);
	afx_msg void OnFileSave32771();
private:
	CGrCamera m_camera;
//	int m_scene;
	CSphere m_mercury;
	CGrTexture m_t_mercury;

	CSphere m_venus;
	CGrTexture m_t_venus;

	CSphere m_earth;
	CGrTexture m_t_earth;

	CSphere m_mars;
	CGrTexture m_t_mars;

	CSphere m_jupiter;
	CGrTexture m_t_jupiter;

	CSphere m_saturn;
	CGrTexture m_t_saturn;

	CSphere m_uranus;
	CGrTexture m_t_uranus;

	CSphere m_neptune;
	CGrTexture m_t_neptune;

	CSphere m_sun;
	CGrTexture m_t_sun;

	UINT_PTR m_spinTimer; ///< for timer counter
	std::deque<double> m_angleSpd; ///< angle list for 8 planets, index from 0 to 7
	std::deque<double> m_selfRotSpd; ///< self rotation speed for 8 planets, index from 0 to 7
	std::deque<double> m_initialAng; ///< randomerize the initial angle for each planet
	bool m_orbitRot; ///< rotate around the sun
	bool m_selfRot; ///< self spinning

public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnOptionSpin();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnOptionSelfrotation();
};

