//--------------------------------------------------------------------------------------------------
#include "GLShaderManager.h"
//--------------------------------------------------------------------------------------------------
GLShaderManager* GLShaderManager::ms_pInstance = 0;
//--------------------------------------------------------------------------------------------------
bool GLShaderManager::CreateShaderManager()
{
    bool br = true;
    if (ms_pInstance == 0)
    {
        ms_pInstance = new GLShaderManager;
        if (ms_pInstance && ms_pInstance->InitShaderManager())
        {
            br = true;
        }
        else
        {
            ReleaseShaderManager();
            br = false;
        }
    }
    else
    {
        ms_pInstance->ReCreateGLResource();
    }
    return br;
}
//--------------------------------------------------------------------------------------------------
void GLShaderManager::ReleaseShaderManager()
{
    if (ms_pInstance)
    {
        delete ms_pInstance;
        ms_pInstance = 0;
    }
}
//--------------------------------------------------------------------------------------------------
GLShaderManager::GLShaderManager()
{
    for (int i = 0; i < GLShader_Max; ++i)
    {
        m_pShaderList[i] = 0;
    }
}
//--------------------------------------------------------------------------------------------------
GLShaderManager::~GLShaderManager()
{
    ClearShaderManager();
}
//--------------------------------------------------------------------------------------------------
bool GLShaderManager::InitShaderManager()
{
    m_pShaderList[GLShader_Standard] = new GLShaderStandard;
    m_pShaderList[GLShader_Standard]->ReCreateGLResource();
    m_pShaderList[GLShader_GGUI] = new GLShaderGGUI;
    m_pShaderList[GLShader_GGUI]->ReCreateGLResource();
    return true;
}
//--------------------------------------------------------------------------------------------------
void GLShaderManager::ClearShaderManager()
{
    for (int i = 0; i < GLShader_Max; ++i)
    {
        if (m_pShaderList[i])
        {
            delete m_pShaderList[i];
            m_pShaderList[i] = 0;
        }
    }
}
//--------------------------------------------------------------------------------------------------
void GLShaderManager::ReCreateGLResource()
{
    for (int i = 0; i < GLShader_Max; ++i)
    {
        if (m_pShaderList[i])
        {
            m_pShaderList[i]->ReCreateGLResource();
        }
    }
}
//--------------------------------------------------------------------------------------------------
const GLShaderBase* GLShaderManager::GetShader(GLShaderType eType)
{
    return m_pShaderList[eType];
}
//--------------------------------------------------------------------------------------------------
