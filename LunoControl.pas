unit mm;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, Buttons, StdCtrls, IdBaseComponent, IdComponent, IdUDPBase,
  IdUDPClient, ComCtrls;

type
  TForm1 = class(TForm)
    IdUDPClient1: TIdUDPClient;
    Button1: TButton;
    SpeedButton1: TSpeedButton;
    SpeedButton2: TSpeedButton;
    SpeedButton3: TSpeedButton;
    SpeedButton4: TSpeedButton;
    SpeedButton5: TSpeedButton;
    Edit1: TEdit;
    StatusBar1: TStatusBar;
    Label1: TLabel;
    SpeedButton6: TSpeedButton;
    SpeedButton7: TSpeedButton;
    procedure Button1Click(Sender: TObject);
    procedure SpeedButton1Click(Sender: TObject);
    procedure SpeedButton4Click(Sender: TObject);
    procedure SpeedButton2Click(Sender: TObject);
    procedure SpeedButton3Click(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure FormKeyUp(Sender: TObject; var Key: Word;
      Shift: TShiftState);
    procedure SpeedButton5Click(Sender: TObject);
    procedure Edit1KeyPress(Sender: TObject; var Key: Char);
    procedure SpeedButton6Click(Sender: TObject);
    procedure SpeedButton7Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

{$R *.dfm}

procedure TForm1.Button1Click(Sender: TObject);
begin
if IdUDPClient1.Active then
  begin
  IdUDPClient1.Active:= false;
  statusbar1.Panels[0].Text:= 'Disconnected!';
  button1.Caption:='CONNECT';
  end
  else
    begin
      IdUDPClient1.Host:=edit1.Text;
      IdUDPClient1.Active:= true;
      statusbar1.Panels[0].Text:= 'Connect...';
      button1.Caption:='DISCONNECT';
    end;
end;

procedure TForm1.SpeedButton1Click(Sender: TObject);
begin
  if IdUDPClient1.Active then
    begin
      IdUDPClient1.Send('l');
      statusbar1.Panels[0].Text:= 'Send Data... L';
    end;
  statusbar1.Panels[1].Text:= (Sender as TSpeedbutton).Caption;
end;

procedure TForm1.SpeedButton4Click(Sender: TObject);
begin
  if IdUDPClient1.Active then
    begin
      IdUDPClient1.Send('r');
      statusbar1.Panels[0].Text:= 'Send Data... R';
    end;
  statusbar1.Panels[1].Text:= (Sender as TSpeedbutton).Caption;
end;

procedure TForm1.SpeedButton2Click(Sender: TObject);
begin
  if IdUDPClient1.Active then
    begin
      IdUDPClient1.Send('f');
      statusbar1.Panels[0].Text:= 'Send Data... F';
    end;
  statusbar1.Panels[1].Text:= (Sender as TSpeedbutton).Caption;
end;

procedure TForm1.SpeedButton3Click(Sender: TObject);
begin
    if IdUDPClient1.Active then
    begin
      IdUDPClient1.Send('b');
      statusbar1.Panels[0].Text:= 'Send Data... B';
    end;
  statusbar1.Panels[1].Text:= (Sender as TSpeedbutton).Caption;
end;

procedure TForm1.FormClose(Sender: TObject; var Action: TCloseAction);
begin
       IdUDPClient1.Active:= false
end;

procedure TForm1.FormKeyUp(Sender: TObject; var Key: Word;
  Shift: TShiftState);
begin
  if (Key = 38) then SpeedButton2.OnClick(SpeedButton2);
  if (Key = 40) then SpeedButton3.OnClick(SpeedButton3);
  if (Key = 37) then SpeedButton1.OnClick(SpeedButton1);
  if (Key = 39) then SpeedButton4.OnClick(SpeedButton4);
  if (Key = 17) then SpeedButton5.OnClick(SpeedButton5);
  if (Key = 81) then SpeedButton6.OnClick(SpeedButton6);
  if (Key = 87) then SpeedButton7.OnClick(SpeedButton7);
end;

procedure TForm1.SpeedButton5Click(Sender: TObject);
begin
    if IdUDPClient1.Active then
    begin
      IdUDPClient1.Send('s');
      statusbar1.Panels[0].Text:= 'Send Data... S';
    end;
  statusbar1.Panels[1].Text:= (Sender as TSpeedbutton).Caption;
end;

procedure TForm1.Edit1KeyPress(Sender: TObject; var Key: Char);
begin
  if not (Key in [#8, '.', '0'..'9']) then begin
    // Discard the key
    Key := #0;
  end;
end;

procedure TForm1.SpeedButton6Click(Sender: TObject);
begin
    if IdUDPClient1.Active then
    begin
      IdUDPClient1.Send('q');
      statusbar1.Panels[0].Text:= 'Send Data... Q';
    end;
  statusbar1.Panels[1].Text:= (Sender as TSpeedbutton).Caption;
end;

procedure TForm1.SpeedButton7Click(Sender: TObject);
begin
    if IdUDPClient1.Active then
    begin
      IdUDPClient1.Send('w');
      statusbar1.Panels[0].Text:= 'Send Data... W';
    end;
  statusbar1.Panels[1].Text:= (Sender as TSpeedbutton).Caption;
end;

end.
