program pautomake;

{$IFDEF FPC}
{$MODE Delphi}
{$ELSE}
{$APPTYPE CONSOLE}
{$ENDIF}
{$R *.res}

uses
  SysUtils;

{$IFNDEF FPC}
const
  DirectorySeparator = '\';
{$ENDIF FPC}

var
  HighIndex, LowIndex: integer;
  ProgramPath, DestPath: string;

procedure Init();
begin
  Readln(HighIndex);
  Readln(LowIndex);
  ProgramPath := ExtractFilePath(ParamStr(0));
  DestPath := ProgramPath + Format('%d.%d', [HighIndex, LowIndex]);
end;

procedure TouchCMakeFile;
var
  hFile: TextFile;
begin
  AssignFile(hFile, DestPath + DirectorySeparator + 'CMakeLists.txt');
  Rewrite(hFile);
  Writeln(hFile, Format('project(KR_%d.%d)', [HighIndex, LowIndex]));
  Writeln(hFile, 'link_libraries(${DEPS_LIBRARIES} -lm)');
  Writeln(hFile, 'add_definitions(-std=c11 -Wall -O0 -gdwarf-2)');
  Writeln(hFile, 'cmake_minimum_required(VERSION 2.8)');
  Writeln(hFile, 'aux_source_directory(. SRC_LIST)');
  Writeln(hFile, 'add_executable(app ${SRC_LIST})');
  CloseFile(hFile);
end;

procedure TouchMainC;
var
  hFile: TextFile;
begin
  AssignFile(hFile, DestPath + DirectorySeparator + 'main.c');
  Rewrite(hFile);
  Writeln(hFile, 'int main(void) {');
  Writeln(hFile, '    return 0;');
  Writeln(hFile, '}');
  CloseFile(hFile);
end;

begin
  Init;
  Writeln('Создаём директорию проекта: ', DestPath);
  MkDir(DestPath);
  Writeln('Создаём CMakeLists');
  TouchCMakeFile();
  Writeln('Создаём main.c');
  TouchMainC;

end.
