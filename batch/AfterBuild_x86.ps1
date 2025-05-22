New-Item -Path ..\Releases -ItemType "directory" -Force
Copy-Item .\Release\Win32\foo_dsp_keepalive.dll -Destination ..\Releases\ -Force
