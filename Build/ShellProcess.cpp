//---------------------------------------------------------------------------
#include "agdx.pch.h"
#include "Build/ShellProcess.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DosCommand"
//---------------------------------------------------------------------------
__fastcall ShellProcess::ShellProcess(BuildMessages& buildMessages, BuildMessageType type, const String& description)
: BuildProcess(buildMessages, type, description)
{
    m_Shell = std::make_unique<TDosCommand>(nullptr);
    m_Shell->OnNewLine = OnNewLineEvent;
    m_Shell->OnExecuteError = OnErrorEvent;
    m_Shell->OnTerminated = OnTerminatedEvent;
}
//---------------------------------------------------------------------------
__fastcall ShellProcess::~ShellProcess()
{
}
//---------------------------------------------------------------------------
bool __fastcall ShellProcess::ShellExecute(const String& path, const String& cmdline, bool wait)
{
    m_Errored = false;
    bool result = true;
    try
    {
        try
        {
            if (m_Shell->IsRunning)
            {
                m_Shell->Stop();
            }
            ChDir(path);
            m_Shell->CurrentDir = path;
            BUILD_LINE(bmOutput, "� " + cmdline);
            m_Shell->CommandLine = cmdline;
            m_Shell->Execute();
            m_ShellDone = false;
            while (wait && !m_ShellDone)
            {
                Application->ProcessMessages();
                Sleep(100);
            }
        }
        catch(Exception&)
        {
            result = false;
        }
    }
    __finally
    {
        if (wait)
        {
            m_Shell->Stop();
        }
    }
    result = result && !m_Errored;
    BUILD_MSG(result ? bmOk : bmFailed);
    return result;
}
//---------------------------------------------------------------------------
void __fastcall ShellProcess::OnNewLineEvent(System::TObject* ASender, const System::UnicodeString ANewLine, TOutputType AOutputType)
{
    if (ANewLine.LowerCase().Pos("error"))
    {
        m_Errored = true;
        BUILD_LINE(bmFailed, "� " + ANewLine);
    }
    else if (ANewLine.LowerCase().Pos("warn"))
    {
        BUILD_LINE(bmWarning, "� " + ANewLine);
    }
    else
    {
        BUILD_LINE(bmOutput, "� " + ANewLine);
    }
}
//---------------------------------------------------------------------------
void __fastcall ShellProcess::OnErrorEvent(System::TObject* ASender, System::Sysutils::Exception* AE, bool &AHandled)
{
    m_Errored = true;
    BUILD_LINE(bmFailed, "Exception: " + AE->ToString());
    AHandled = true;
}
//---------------------------------------------------------------------------
void __fastcall ShellProcess::OnTerminatedEvent(System::TObject* ASender)
{
    m_ShellDone = true;
}
//---------------------------------------------------------------------------

