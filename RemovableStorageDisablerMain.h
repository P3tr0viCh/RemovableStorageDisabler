// ---------------------------------------------------------------------------

#ifndef RemovableStorageDisablerMainH
#define RemovableStorageDisablerMainH
// ---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>

enum TPolicy {
	pNotConfigured, pDisabled, pEnabled, pNotApplicable
};

// ---------------------------------------------------------------------------
class TMain : public TForm {
__published: // IDE-managed Components

	TButton *btnTogglePolicy;
	TButton *btnClose;
	TLabel *lblPolicySetting;
	TLabel *lblCaptionMain;
	TLabel *lblCaptionSetting;
	TLabel *lblPolicyDescription;
	TStatusBar *StatusBar;

	void __fastcall btnTogglePolicyClick(TObject *Sender);
	void __fastcall btnCloseClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);

private: // User declarations
	void UpdateVersion();
	void UpdateCaptions(TPolicy Policy);

public: // User declarations
	__fastcall TMain(TComponent* Owner);
	__fastcall ~TMain();
	bool __fastcall TMain::hookWindowsMessage(TMessage & msg);
};

// ---------------------------------------------------------------------------
extern PACKAGE TMain *Main;
// ---------------------------------------------------------------------------

#endif
