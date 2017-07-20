//--------------------------------------------------------------------------------------------------
#ifndef _GGUIActionMove_h_
#define _GGUIActionMove_h_
//--------------------------------------------------------------------------------------------------
#include "GGUIActionBase.h"
//--------------------------------------------------------------------------------------------------
class GGUIActionMove : public GGUIActionBase
{
	friend class GGUIActionFactory;
public:
	virtual void UpdateAction(float fDeltaTime);
	virtual bool IsActionFinished() const;

	void InitActionMove(float fDeltaX, float fDeltaY, float fTime);

protected:
    GGUIActionMove();
    virtual ~GGUIActionMove();
    virtual void ClearAction();

protected:
	float m_fSpeedX;
	float m_fSpeedY;
	float m_fRemainTime;
};
//--------------------------------------------------------------------------------------------------
inline bool GGUIActionMove::IsActionFinished() const
{
	return (m_fRemainTime < 0.0f);
}
//--------------------------------------------------------------------------------------------------
#endif //_GGUIActionMove_h_
//--------------------------------------------------------------------------------------------------
