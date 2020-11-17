// OpenClient.cpp: COpenClientApp 和 DLL 注册的实现。

#include "stdafx.h"
#include "OpenClient.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


COpenClientApp theApp;

const GUID CDECL _tlid = {0xa477ac36,0x5df8,0x4fad,{0x8c,0xa6,0x61,0x3a,0xf8,0xa2,0xe4,0x50}};
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;



// COpenClientApp::InitInstance - DLL 初始化

BOOL COpenClientApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO:  在此添加您自己的模块初始化代码。
	}

	return bInit;
}



// COpenClientApp::ExitInstance - DLL 终止

int COpenClientApp::ExitInstance()
{
	// TODO:  在此添加您自己的模块终止代码。

	return COleControlModule::ExitInstance();
}



// DllRegisterServer - 将项添加到系统注册表

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}



// DllUnregisterServer - 将项从系统注册表中移除

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
