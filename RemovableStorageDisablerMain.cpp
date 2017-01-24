// ---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "RemovableStorageDisablerMain.h"
#include "RemovableStorageDisablerStrings.h"

#include "UtilsMisc.h"
#include "UtilsStr.h"

#include <initguid.h>
#include <gpedit.h>

// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMain *Main;

// ---------------------------------------------------------------------------
__fastcall TMain::TMain(TComponent* Owner) : TForm(Owner) {
	Application->HookMainWindow(hookWindowsMessage);
}

__fastcall TMain::~TMain() {
	Application->UnhookMainWindow(hookWindowsMessage);
}

const cPolicyEnabled = 1;
const cPolicyDisabled = 0;

GUID ExtGuid = REGISTRY_EXTENSION_GUID;
GUID SnapGuid = {
	0x3d271cfc, 0x2bc6, 0x4ac2, {0xb6, 0x33, 0x3b, 0xdf, 0xf5, 0xbd, 0xab, 0x2a}
};

const UnicodeString cKeyRemovableStorageDevices =
	"SOFTWARE\\Policies\\Microsoft\\Windows\\RemovableStorageDevices";
const UnicodeString cKeyDenyAll = "Deny_All";

TPolicy GetRemovableStoragePolicy() {
	TPolicy Result = pNotConfigured;

	HKEY Key;

	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, cKeyRemovableStorageDevices.c_str(), 0,
		KEY_READ, &Key) == ERROR_SUCCESS) {

		DWORD Value;
		DWORD ValueSize = sizeof(Value);

		if (RegQueryValueEx(Key, cKeyDenyAll.c_str(), 0, NULL, (LPBYTE) & Value,
			&ValueSize) == ERROR_SUCCESS) {
			switch (Value) {
			case cPolicyDisabled:
				Result = pDisabled;
				break;
			case cPolicyEnabled:
				Result = pEnabled;
				break;
			}
		}

		RegCloseKey(Key);
	}

	return Result;
}

bool SetRemovableStoragePolicy(TPolicy Policy) {
	if (Policy != pEnabled && Policy != pDisabled) {
		return false;
	}

	if (FAILED(CoInitializeEx(NULL, COINIT_APARTMENTTHREADED))) {
		return false;
	}

	IGroupPolicyObject* pLGPO;

	if (FAILED(CoCreateInstance(CLSID_GroupPolicyObject, NULL,
		CLSCTX_INPROC_SERVER, IID_IGroupPolicyObject, (LPVOID*)&pLGPO))) {
		return false;
	}

	bool Result = false;

	if (SUCCEEDED(pLGPO->OpenLocalMachineGPO(GPO_OPEN_LOAD_REGISTRY))) {
		HKEY MachineKey;

		if (SUCCEEDED(pLGPO->GetRegistryKey(GPO_SECTION_MACHINE, &MachineKey)))
		{
			HKEY Key;

			if (RegCreateKeyEx(MachineKey, cKeyRemovableStorageDevices.c_str(),
				0, NULL, 0, KEY_ALL_ACCESS, NULL, &Key, NULL) == ERROR_SUCCESS)
			{
				DWORD Value = Policy == pEnabled ? cPolicyEnabled :
					cPolicyDisabled;
				DWORD ValueSize = sizeof(Value);

				if (RegSetValueEx(Key, cKeyDenyAll.c_str(), 0, REG_DWORD,
					(LPBYTE) & Value, ValueSize) == ERROR_SUCCESS) {
					Result = true;
				}

				RegCloseKey(Key);
			}

			RegCloseKey(MachineKey);
		}
	}

	if (Result) {
		Result = SUCCEEDED(pLGPO->Save(TRUE, TRUE, &ExtGuid, &SnapGuid));
	}

	pLGPO->Release();

	return Result;
}

// ---------------------------------------------------------------------------
void __fastcall TMain::btnTogglePolicyClick(TObject * Sender) {
	TPolicy Policy = GetRemovableStoragePolicy();

	if (Policy == pEnabled) {
		Policy = pDisabled;
	}
	else {
		Policy = pEnabled;
	}

	if (!SetRemovableStoragePolicy(Policy)) {
		MsgBoxErr(LoadStr(IDS_ERROR_SET_POLICY));
	}
}

// ---------------------------------------------------------------------------
void __fastcall TMain::btnCloseClick(TObject * Sender) {
	Close();
}

void TMain::UpdateCaptions(TPolicy Policy) {
	TColor PolicyDescriptionColor;
	NativeUInt PolicySetting, PolicyDescription, TogglePolicy;

	btnTogglePolicy->Enabled = Policy != pNotApplicable;
	switch (Policy) {
	case pEnabled:
		PolicySetting = IDS_LBL_POLICY_SETTING_ENABLED;

		PolicyDescriptionColor = clRed;
		PolicyDescription = IDS_LBL_POLICY_DESCRIPTION_ENABLED;

		TogglePolicy = IDS_BTN_TOGGLE_ENABLED;
		break;
	case pDisabled:
		PolicySetting = IDS_LBL_POLICY_SETTING_DISABLED;

		PolicyDescriptionColor = clGreen;
		PolicyDescription = IDS_LBL_POLICY_DESCRIPTION_DISABLED;

		TogglePolicy = IDS_BTN_TOGGLE_DISABLED;
		break;
	case pNotConfigured:
		PolicySetting = IDS_LBL_POLICY_SETTING_NOT_CONFIGURED;

		PolicyDescriptionColor = clGreen;
		PolicyDescription = IDS_LBL_POLICY_DESCRIPTION_DISABLED;

		TogglePolicy = IDS_BTN_TOGGLE_DISABLED;
		break;
	default:
	case pNotApplicable:
		PolicySetting = IDS_LBL_POLICY_SETTING_NOT_APPLICABLE;

		PolicyDescriptionColor = clRed;
		PolicyDescription = IDS_LBL_POLICY_DESCRIPTION_NOT_APPLICABLE;

		TogglePolicy = IDS_BTN_TOGGLE_NOT_APPLICABLE;
	}

	lblPolicySetting->Caption = LoadStr(PolicySetting);
	lblPolicyDescription->Font->Color = PolicyDescriptionColor;
	lblPolicyDescription->Caption = LoadStr(PolicyDescription);
	btnTogglePolicy->Caption = LoadStr(TogglePolicy);
}

void TMain::UpdateVersion() {
	TVSFixedFileInfo FileVersionInfo;

	String CompanyName, FileDescription, FileVersion, InternalName,
		LegalCopyright, OriginalFilename, ProductName, ProductVersion;

	GetFileVerInfo(Application->ExeName, FileVersionInfo, CompanyName,
		FileDescription, FileVersion, InternalName, LegalCopyright,
		OriginalFilename, ProductName, ProductVersion);

	StatusBar->Panels->Items[0]->Text =
		FmtLoadStr(IDS_VERSION, ARRAYOFCONST((SmallFileVersion(FileVersion),
		GetFileVerDate())));
	StatusBar->Panels->Items[1]->Text = LegalCopyright;
}

// ---------------------------------------------------------------------------
void __fastcall TMain::FormCreate(TObject * Sender) {
	UpdateVersion();

	TPolicy Policy;

	if (IsWinVistaOrGreat()) {
		Policy = GetRemovableStoragePolicy();
	}
	else {
		Policy = pNotApplicable;
		MsgBoxErr(LoadStr(IDS_ERROR_NEED_VISTA_OR_GREAT));
	}

	UpdateCaptions(Policy);
}

bool __fastcall TMain::hookWindowsMessage(TMessage & msg) {
	if (msg.Msg == WM_SETTINGCHANGE && msg.WParam) {
		String sLParam((char *)msg.LParam);

		if (sLParam.CompareIC("Policy")) {
			TPolicy Policy = GetRemovableStoragePolicy();
			UpdateCaptions(Policy);
		}
	}

	return false;
}
