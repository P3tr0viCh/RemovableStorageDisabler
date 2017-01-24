object Main: TMain
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = #1057#1098#1105#1084#1085#1099#1077' '#1079#1072#1087#1086#1084#1080#1085#1072#1102#1097#1080#1077' '#1091#1089#1090#1088#1086#1081#1089#1090#1074#1072
  ClientHeight = 287
  ClientWidth = 500
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -16
  Font.Name = 'Segoe UI'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = FormCreate
  DesignSize = (
    500
    287)
  PixelsPerInch = 96
  TextHeight = 21
  object lblPolicySetting: TLabel
    Left = 16
    Top = 107
    Width = 468
    Height = 21
    Anchors = [akLeft, akTop, akRight]
    AutoSize = False
    Caption = 'lblPolicySetting'
  end
  object lblCaptionMain: TLabel
    Left = 16
    Top = 16
    Width = 468
    Height = 48
    Anchors = [akLeft, akTop, akRight]
    AutoSize = False
    Caption = 
      #1053#1072#1089#1090#1088#1086#1081#1082#1072' '#1076#1086#1089#1090#1091#1087#1072' '#1082' '#1089#1098#1105#1084#1085#1099#1084' '#1079#1072#1087#1086#1084#1080#1085#1072#1102#1097#1080#1084' '#1091#1089#1090#1088#1086#1081#1089#1090#1074#1072#1084' '#1074#1089#1077#1093' '#1082#1083#1072#1089#1089#1086 +
      #1074'.'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Segoe UI Semibold'
    Font.Style = [fsBold]
    ParentFont = False
    WordWrap = True
  end
  object lblCaptionSetting: TLabel
    Left = 16
    Top = 77
    Width = 468
    Height = 21
    Anchors = [akLeft, akTop, akRight]
    AutoSize = False
    Caption = #1058#1077#1082#1091#1097#1077#1077' '#1089#1086#1089#1090#1086#1103#1085#1080#1077' '#1087#1086#1083#1080#1090#1080#1082#1080':'
  end
  object lblPolicyDescription: TLabel
    Left = 16
    Top = 144
    Width = 468
    Height = 48
    Anchors = [akLeft, akTop, akRight]
    AutoSize = False
    Caption = 'lblPolicyDescription'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Segoe UI Semibold'
    Font.Style = [fsBold]
    ParentFont = False
    WordWrap = True
  end
  object btnTogglePolicy: TButton
    Left = 16
    Top = 211
    Width = 169
    Height = 40
    Caption = 'btnTogglePolicy'
    TabOrder = 0
    OnClick = btnTogglePolicyClick
  end
  object btnClose: TButton
    Left = 371
    Top = 211
    Width = 113
    Height = 40
    Caption = #1047#1072#1082#1088#1099#1090#1100
    TabOrder = 1
    OnClick = btnCloseClick
  end
  object StatusBar: TStatusBar
    Left = 0
    Top = 268
    Width = 500
    Height = 19
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBtnText
    Font.Height = -12
    Font.Name = 'Segoe UI'
    Font.Style = []
    Panels = <
      item
        Text = 'Version'
        Width = 200
      end
      item
        Text = 'P3tr0viCh'
        Width = 50
      end>
    UseSystemFont = False
    ExplicitLeft = 304
    ExplicitTop = 264
    ExplicitWidth = 0
  end
end
