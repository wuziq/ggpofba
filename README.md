ggpofba

These instructions are derived from vctoolkit.txt under **src**.

## Prerequisites
* Windows (I've tested on XP and 7)
* [cygwin](https://www.cygwin.com/)
* [DirectX SDK (August 2007)](http://www.microsoft.com/en-us/download/confirmation.aspx?id=13287)
* [Microsoft Platform SDK](http://www.microsoft.com/en-us/download/details.aspx?id=6510)
* [Visual C++ 2003 Toolkit](http://xona.com/2004/06/29.html)
  * When clicking through to the uploading.com link, be sure to uncheck "Use Download Accelerator", then click "Download for free"
  * Since this probably isn't a high-quality link, you can probably use Visual C++ 2005 Express, which is free from Microsoft

## Build instructions
1.  Install all the prerequisites.  Use defaults for everything **except for cygwin**, where you should also install **perl**, **nasm**, and **make**.
2.  Search your system for a file called **cvtres.exe**.
  * The version that works is **8.00.50727.4940**
  * It might be located here:  **C:\Windows\Microsoft.NET\Framework\v2.0.50727**
  * Copy it to **%VCToolkitInstallDir%\bin\**
3.  Add `C:\cygwin\bin` to your PATH.
4.  Open up a regular command prompt and navigate to wherever you've cloned the source.
5.  Run `environment.bat`, which will set up some environment variables for your current session.
6.  Execute `make vc`

You should have an **fbaa.exe** when it's all done.

## FAQ
* Where is CPS3 support?
  * I don't know.  I've emailed Tony Cannon (creator of GGPO) about it.  I'll update this when I learn more.
* Why do I have to use such an old version of the SDK/compiler/whatever?
  * Newer versions of the compiler and Platform SDK might work; I haven't tried.  But the older DirectX SDK is needed because it has ddraw.h and d3d.h, which are needed for the build.  See [here](http://blogs.msdn.com/b/chuckw/archive/2010/06/16/wither-directdraw.aspx) and [here](http://blogs.msdn.com/b/chuckw/archive/2012/08/22/directx-sdk-s-of-a-certain-age.aspx) for more info.