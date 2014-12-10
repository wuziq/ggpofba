#	Main Makefile for FB Alpha, execute an appropriate system-specific makefile

export

#
#	Declare variables
#

# Make a special build, pass the quoted text as comment (use FORCE_UPDATE declaration below to force recompilation of resources)
# SPECIALBUILD = "This text will appear in the property sheet of the .exe file"



#
#	Flags. Uncomment any of these declarations to enable their function.
#

# Inluclude Unicode support
# UNICODE = 1

# Include symbols and other debug information in the executable
# SYMBOL = 1

# Include features for debugging drivers
# DEBUG	= 1

# Include rom set verifying features (comment this for release builds)
#ROM_VERIFY = 1

# Force recompilation of files that need it (i.e. use __TIME__, __DATE__, SPECIALBUILD).
#FORCE_UPDATE = 1

# Use the __fastcall calling convention when interfacing with A68K/Musashi/Doze
FASTCALL = 1

# Compress executable with upx (the DEBUG option ignores this)
# COMPRESS = 1

# Perl is available
PERL = 1

#
#	execute an appropriate system-specific makefile
#

mingw: FORCE
	@$(MAKE) -s -f makefile.mingw

sdl: FORCE
	@$(MAKE) -s -f makefile.sdl

vc: FORCE
	@$(MAKE) -s -f makefile.vc

FORCE: