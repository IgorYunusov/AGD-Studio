object frmNewImage: TfrmNewImage
  Left = 0
  Top = 0
  ActiveControl = edtName
  BorderStyle = bsDialog
  Caption = 'New Image'
  ClientHeight = 175
  ClientWidth = 349
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  ScreenSnap = True
  OnCreate = FormCreate
  DesignSize = (
    349
    175)
  PixelsPerInch = 96
  TextHeight = 16
  object Label1: TLabel
    Left = 16
    Top = 24
    Width = 33
    Height = 16
    Caption = 'Name'
  end
  object lblWidth: TLabel
    Left = 16
    Top = 96
    Width = 33
    Height = 16
    Caption = 'Width'
    Enabled = False
  end
  object lblHeight: TLabel
    Left = 212
    Top = 96
    Width = 36
    Height = 16
    Anchors = [akTop, akRight]
    Caption = 'Height'
    Enabled = False
    ExplicitLeft = 239
  end
  object Panel1: TPanel
    Left = 0
    Top = 138
    Width = 349
    Height = 37
    Align = alBottom
    BevelOuter = bvNone
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    DesignSize = (
      349
      37)
    object btnOk: TButton
      Left = 182
      Top = 6
      Width = 75
      Height = 25
      Anchors = [akTop, akRight]
      Caption = 'OK'
      Default = True
      Enabled = False
      ModalResult = 1
      TabOrder = 0
    end
    object btnCancel: TButton
      Left = 266
      Top = 6
      Width = 75
      Height = 25
      Anchors = [akTop, akRight]
      Cancel = True
      Caption = 'Cancel'
      ModalResult = 2
      TabOrder = 1
    end
  end
  object edtName: TEdit
    Left = 72
    Top = 21
    Width = 269
    Height = 24
    Anchors = [akLeft, akTop, akRight]
    TabOrder = 5
    OnChange = edtNameChange
  end
  object radObject: TRadioButton
    Left = 72
    Top = 64
    Width = 57
    Height = 17
    Caption = 'Object'
    Checked = True
    TabOrder = 1
    TabStop = True
    OnClick = radObjectClick
  end
  object radSprite: TRadioButton
    Tag = 1
    Left = 148
    Top = 64
    Width = 58
    Height = 17
    Caption = 'Sprite'
    TabOrder = 2
    OnClick = radObjectClick
  end
  object radTile: TRadioButton
    Tag = 2
    Left = 217
    Top = 64
    Width = 40
    Height = 17
    Caption = 'Tile'
    TabOrder = 3
    OnClick = radObjectClick
  end
  object radChrSet: TRadioButton
    Tag = 3
    Left = 274
    Top = 64
    Width = 67
    Height = 17
    Caption = 'Char Set'
    TabOrder = 4
    OnClick = radObjectClick
  end
  object edtWidth: TLMDSpinEdit
    Left = 72
    Top = 92
    Width = 76
    Height = 25
    Hint = ''
    Bevel.Mode = bmWindows
    Caret.BlinkRate = 530
    TabOrder = 6
    OnExit = edtWidthExit
    AutoSelect = True
    CustomButtons = <>
    Value = 0
  end
  object edtHeight: TLMDSpinEdit
    Left = 265
    Top = 92
    Width = 76
    Height = 25
    Hint = ''
    Bevel.Mode = bmWindows
    Caret.BlinkRate = 530
    Flat = True
    TabOrder = 7
    OnExit = edtHeightExit
    AutoSelect = True
    CustomButtons = <>
    Value = 0
  end
end
