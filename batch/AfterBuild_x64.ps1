New-Item -Path ..\Releases\x64\ -ItemType "directory" -Force
Copy-Item .\Release\x64\foo_dsp_keepalive.dll -Destination ..\Releases\x64\ -Force
