//--------------------------------------------------------------------------------------------------
#include "GLShaderGGUI.h"
#include "SoFileHelp.h"
#include "GLCameraUI.h"
//--------------------------------------------------------------------------------------------------
GLShaderGGUI::GLShaderGGUI()
:m_uiProgramID(0)
,m_uiVertexID(0)
,m_uiUVID(0)
,m_uiColorID(0)
,m_uiMatProjectViewID(0)
,m_uiTexSamplerID(0)
{

}
//--------------------------------------------------------------------------------------------------
GLShaderGGUI::~GLShaderGGUI()
{
    if (m_uiProgramID)
    {
        glDeleteProgram(m_uiProgramID);
        m_uiProgramID = 0;
    }
}
//--------------------------------------------------------------------------------------------------
void GLShaderGGUI::ReCreateGLResource()
{
    m_uiProgramID = 0;
    m_uiVertexID = 0;
    m_uiUVID = 0;
    m_uiColorID = 0;
    m_uiMatProjectViewID = 0;
    m_uiTexSamplerID = 0;

    const char* VertexShader = "";
    SoFile* pVSFile = SoFileHelp::CreateFileAsset("shader/ggui_vs.txt");
    if (pVSFile)
    {
        VertexShader = (char*)pVSFile->GetFileData();
    }

    const char* FragmentShader = "";
    SoFile* pPSFile = SoFileHelp::CreateFileAsset("shader/ggui_ps.txt");
    if (pPSFile)
    {
        FragmentShader = (char*)pPSFile->GetFileData();
    }

    m_uiProgramID = CreateProgram(VertexShader, FragmentShader);

    if (pVSFile)
    {
        SoFileHelp::DeleteFile(pVSFile);
    }
    if (pPSFile)
    {
        SoFileHelp::DeleteFile(pPSFile);
    }

    if (m_uiProgramID)
    {
        m_uiVertexID = (GLuint)glGetAttribLocation(m_uiProgramID, "myVertex");
        m_uiUVID = (GLuint)glGetAttribLocation(m_uiProgramID, "myUV_TexIndex");
        m_uiColorID = (GLuint)glGetAttribLocation(m_uiProgramID, "myColor");
        m_uiMatProjectViewID = (GLuint)glGetUniformLocation(m_uiProgramID, "g_matProjectView");
        m_uiTexSamplerID = (GLuint)glGetUniformLocation(m_uiProgramID, "g_TextureList");
    }

    for (int i = 0; i < GLShaderGGUI_MaxTexSamplerCount; ++i)
    {
        m_kSamplerUnitList[i] = i;
    }
}
//--------------------------------------------------------------------------------------------------
void GLShaderGGUI::ProcessRender(void* pParam) const
{
    if (m_uiProgramID == 0)
    {
        return;
    }

    GLShaderGGUIParam* pGGUIParam = (GLShaderGGUIParam*)pParam;
    const SoMathMatrix4& kMatProjView = GLCameraUI::Get()->GetMatProjView();

    glUseProgram(m_uiProgramID);

    glVertexAttribPointer(m_uiVertexID, 3, GL_FLOAT, GL_FALSE, pGGUIParam->nSizeofVertexStruct, pGGUIParam->pVertexArray+pGGUIParam->nVertexOffset);
    glEnableVertexAttribArray(m_uiVertexID);
    glVertexAttribPointer(m_uiUVID, 3, GL_FLOAT, GL_FALSE, pGGUIParam->nSizeofVertexStruct, pGGUIParam->pVertexArray+pGGUIParam->nUVOffset);
    glEnableVertexAttribArray(m_uiUVID);
    glVertexAttribPointer(m_uiColorID, 4, GL_FLOAT, GL_FALSE, pGGUIParam->nSizeofVertexStruct, pGGUIParam->pVertexArray+pGGUIParam->nColorOffset);
    glEnableVertexAttribArray(m_uiColorID);

    glUniformMatrix4fv(m_uiMatProjectViewID, 1, GL_FALSE, (float*)(kMatProjView.m));

    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    for (int i = 0; i < pGGUIParam->nTexIDCount; ++i)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, pGGUIParam->pTexIDList[i]);
    }
    glUniform1iv(m_uiTexSamplerID, GLShaderGGUI_MaxTexSamplerCount, m_kSamplerUnitList);
    //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

    glDrawElements(GL_TRIANGLES, pGGUIParam->nIndexCount, GL_UNSIGNED_SHORT, pGGUIParam->pIndexArray);
}
//--------------------------------------------------------------------------------------------------
