program LunoControl;

uses
  Forms,
  LunoControl in 'LunoControl.pas' {Form1};

{$R *.res}

begin
  Application.Initialize;
  Application.Title := 'LunoControl';
  Application.CreateForm(TForm1, Form1);
  Application.Run;
end.
