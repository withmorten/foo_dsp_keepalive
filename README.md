# Keep Alive

## What is this?
A DSP component for foobar2000 which keeps audio devices alive by adding an inaudible sound at a very high frequency.

Largely adapted from https://github.com/h1data/foo_dsp_width.

## Installation
1. download the zip file started with "foo_dsp_keepalive" from [Releases](https://github.com/withmorten/foo_dsp_keepalive/releases/latest) section 
2. open foobar2000 > File > Preferences > Components
3. click Install and select the zip file and restart foobar2000
4. open File > Preferences > Playback > DSP Manager
5. add "Keep Alive" to "Active DSPs" and adjust amplitude
6. enjoy!

## Build dependencies
- Visual Studio Community 2022
- foobar2000-SDK-2025-03-07 https://www.foobar2000.org/SDK
- Windows Template Library https://sourceforge.net/projects/wtl/

## Build Procedure
1. Clone this
2. Get foobar2000 SDK and put `lib\foobar2000_SDK\` folder.
<pre>
lib\foobar2000_SDK\
 +- foobar2000\
 +- libPPUI\
 +- pfc\
src\
foo_dsp_keepalive.sln
</pre>
3. Recovery WTL package from NuGet library.
4. Install WTL package from NuGet package to `foobar2000_sdk_helpers` and `libPPUI` project.
5. The dll files will be created in `Releases` folder. You have to compress to zip archive to use in foobar2000.

Referred from https://github.com/Chocobo1/fb2k_example for folder arrangement.
