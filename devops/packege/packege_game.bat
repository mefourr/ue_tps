@echo off

call "%~dp0..\config.bat"

"%RunUATPath%" BuildCookRun ^
 -project="%ProjectPath%" ^
 -platform="%Platform%" ^
 -clientconfig="%Configuration%" ^
 -archivedirectory="%ArchivePath%" ^
 -build -cook -package -archive -stage -pac -allmaps
PAUSE
