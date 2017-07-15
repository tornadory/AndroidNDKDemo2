//----------------------------------------------------------------
#ifndef _GGUIWindowImage_h_
#define _GGUIWindowImage_h_
//----------------------------------------------------------------
#include "GGUIWindowBase.h"
//----------------------------------------------------------------
class GGUIWindowImage : public GGUIWindowBase
{
public:
	//--szImage "ImagesetName:RectName"
	void SetImage(const char* szImage);
	int GetImagesetIndex() const;
	int GetImageRectIndex() const;

protected:
	friend class GGUIWindowFactory;
	GGUIWindowImage();
	virtual ~GGUIWindowImage();
	//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	//re-write parent function
	virtual void ClearWindow();
	virtual void RenderWindow();
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

private:
	int m_nImagesetIndex;
	int m_nImageRectIndex;
};
//----------------------------------------------------------------
inline int GGUIWindowImage::GetImagesetIndex() const
{
	return m_nImagesetIndex;
}
//----------------------------------------------------------------
inline int GGUIWindowImage::GetImageRectIndex() const
{
	return m_nImageRectIndex;
}
//----------------------------------------------------------------
#endif //_GGUIWindowImage_h_
//----------------------------------------------------------------
