//--------------------------------------------------------------------------------------------------
#ifndef _GLShaderStandard_h_
#define _GLShaderStandard_h_
//--------------------------------------------------------------------------------------------------
#include "GLShaderBase.h"
//--------------------------------------------------------------------------------------------------
struct GLShaderStandardParam
{
    const float* pVertexArray;
    const unsigned short* pIndexArray;
    SoMathMatrix4* pMatWorld;
    int nSizeofVertexStruct;
    int nVertexOffset;
    int nUVOffset;
    int nIndexCount;
    GLuint uiTextureID;
};
//--------------------------------------------------------------------------------------------------
class GLShaderStandard : public GLShaderBase
{
public:
    GLShaderStandard();
    ~GLShaderStandard();
    void ReCreateGLResource();
    void ProcessRender(void* pParam) const;

private:
    GLuint m_uiProgramID;
    GLuint m_uiVertexID;
    GLuint m_uiUVID;
    GLuint m_uiMatWorldID;
    GLuint m_uiMatProjectViewID;
    GLuint m_uiTexSamplerID;
};
//--------------------------------------------------------------------------------------------------
#endif //_GLShaderStandard_h_
//--------------------------------------------------------------------------------------------------
