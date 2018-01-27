object Form1: TForm1
  Left = 360
  Top = 225
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'LunoControl v2'
  ClientHeight = 146
  ClientWidth = 252
  Color = clBtnFace
  DefaultMonitor = dmMainForm
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnClose = FormClose
  OnKeyUp = FormKeyUp
  PixelsPerInch = 96
  TextHeight = 13
  object SpeedButton1: TSpeedButton
    Left = 104
    Top = 48
    Width = 45
    Height = 33
    Caption = 'Left'
    OnClick = SpeedButton1Click
  end
  object SpeedButton2: TSpeedButton
    Left = 152
    Top = 8
    Width = 45
    Height = 33
    Caption = 'Up'
    OnClick = SpeedButton2Click
  end
  object SpeedButton3: TSpeedButton
    Left = 152
    Top = 88
    Width = 45
    Height = 33
    Caption = 'Down'
    OnClick = SpeedButton3Click
  end
  object SpeedButton4: TSpeedButton
    Left = 200
    Top = 48
    Width = 45
    Height = 33
    Caption = 'Right'
    OnClick = SpeedButton4Click
  end
  object SpeedButton5: TSpeedButton
    Left = 152
    Top = 48
    Width = 45
    Height = 33
    Caption = 'STOP'
    OnClick = SpeedButton5Click
  end
  object Label1: TLabel
    Left = 8
    Top = 99
    Width = 17
    Height = 13
    Caption = 'IP:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object SpeedButton6: TSpeedButton
    Left = 200
    Top = 8
    Width = 45
    Height = 33
    Caption = 'Light'
    OnClick = SpeedButton6Click
  end
  object SpeedButton7: TSpeedButton
    Left = 199
    Top = 88
    Width = 45
    Height = 33
    Caption = 'Action'
    OnClick = SpeedButton7Click
  end
  object Button1: TButton
    Left = 8
    Top = 8
    Width = 89
    Height = 73
    Caption = 'CONNECT'
    TabOrder = 0
    OnClick = Button1Click
    OnKeyUp = FormKeyUp
  end
  object Edit1: TEdit
    Left = 28
    Top = 96
    Width = 117
    Height = 21
    TabStop = False
    AutoSelect = False
    TabOrder = 1
    Text = '192.168.4.1'
    OnKeyPress = Edit1KeyPress
    OnKeyUp = FormKeyUp
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 127
    Width = 252
    Height = 19
    Panels = <
      item
        Text = 'Please, check IP and CONNECT!'
        Width = 195
      end
      item
        Alignment = taCenter
        Width = 57
      end>
    SizeGrip = False
  end
  object IdUDPClient1: TIdUDPClient
    Host = '192.168.4.1'
    Port = 4210
    Left = 104
    Top = 16
  end
end
