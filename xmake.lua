add_rules("mode.debug", "mode.release")
add_defines("SP_PLATFORM_WIN")
set_optimize("none")
set_languages("clatest", "cxx17")
add_cxflags("/EHsc")
-- add_defines( "UNICODE", "_UNICODE")
-- add_cxflags("/utf-8")
-- add_cxflags("/source-charset:utf-8")
-- add_cxflags("/execution-charset:utf-8")

target("SPing")
    set_kind("static")
    add_includedirs("Source/SPing")
    add_includedirs("$(buildir)/config/SPing")
    add_files("Source/SPing/**/*.cpp")
    add_defines("SP_BUILD_DLL")
    set_configvar("SP_BUILD_DLL", true)
    set_configdir("$(buildir)/config/SPing")
    add_configfiles("Source/SPing/MacroConfig.h.in")


target("01_HelloWorld")
    set_kind("binary")
    add_deps("SPing")
    add_links("SPing")
    add_includedirs("Source/SPing")
    add_includedirs("$(buildir)/config/01_HelloWorld")
    add_files("Source/Samples/01_HelloWorld/*.cpp")
    set_configvar("SP_BUILD_DLL", false)
    set_configdir("$(buildir)/config/01_HelloWorld")
    add_configfiles("Source/SPing/MacroConfig.h.in")
    add_syslinks("User32", "kernel32", "Gdi32", "Shell32", "DXGI", "D3D12", "D3DCompiler")




target("02_Object")
    set_kind("binary")
    add_deps("SPing")
    add_links("SPing")
    add_includedirs("Source/SPing")
    add_includedirs("$(buildir)/config/02_Object")
    add_files("Source/Samples/02_Object/*.cpp")
    set_configvar("SP_BUILD_DLL", false)
    set_configdir("$(buildir)/config/02_Object")
    add_configfiles("Source/SPing/MacroConfig.h.in")
    add_syslinks("User32", "kernel32", "Gdi32", "Shell32", "DXGI", "D3D12", "D3DCompiler")



target("03_RTTI")
    set_kind("binary")
    add_files("Source/Samples/03_RTTI/*.cpp")
    add_syslinks("User32", "kernel32", "Gdi32", "Shell32", "DXGI", "D3D12", "D3DCompiler")


target("04_RTTI_Simple")
    set_kind("binary")
    add_files("Source/Samples/04_RTTI_Simple/*.cpp")
    add_syslinks("User32", "kernel32", "Gdi32", "Shell32", "DXGI", "D3D12", "D3DCompiler")


target("05_Template")
    set_kind("binary")
    add_files("Source/Samples/05_Template/*.cpp")
    add_syslinks("User32", "kernel32", "Gdi32", "Shell32", "DXGI", "D3D12", "D3DCompiler")


target("06_Exception")
    set_kind("binary")
    add_files("Source/Samples/06_Exception/*.cpp")
    add_syslinks("User32", "kernel32", "Gdi32", "Shell32", "DXGI", "D3D12", "D3DCompiler")

target("07_Using")
    set_kind("binary")
    add_files("Source/Samples/07_Using/*.cpp")
    add_syslinks("User32", "kernel32", "Gdi32", "Shell32", "DXGI", "D3D12", "D3DCompiler")

target("08_Dx12_Initial")
    set_kind("binary")
    add_files("Source/Samples/08_Dx12_Initial/*.cpp")
    add_defines("_XM_NO_INTRINSICS_=1", "NOMINMAX", "m128_f32=vector4_f32", "m128_u32=vector4_u32")
    add_syslinks("User32", "kernel32", "Gdi32", "Shell32", "DXGI", "D3D12", "D3DCompiler")

target("09_MemoryManager")
    set_kind("binary")
    add_files("Source/Samples/09_MemoryManager/*.cpp")
    add_defines("_XM_NO_INTRINSICS_=1", "NOMINMAX", "m128_f32=vector4_f32", "m128_u32=vector4_u32")
    add_syslinks("User32", "kernel32", "Gdi32", "Shell32", "DXGI", "D3D12", "D3DCompiler")

--
-- If you want to known more usage about xmake, please see https://xmake.io
--
-- ## FAQ
--
-- You can enter the project directory firstly before building project.
--
--   $ cd projectdir
--
-- 1. How to build project?
--
--   $ xmake
--
-- 2. How to configure project?
--
--   $ xmake f -p [macosx|linux|iphoneos ..] -a [x86_64|i386|arm64 ..] -m [debug|release]
--
-- 3. Where is the build output directory?
--
--   The default output directory is `./build` and you can configure the output directory.
--
--   $ xmake f -o outputdir
--   $ xmake
--
-- 4. How to run and debug target after building project?
--
--   $ xmake run [targetname]
--   $ xmake run -d [targetname]
--
-- 5. How to install target to the system directory or other output directory?
--
--   $ xmake install
--   $ xmake install -o installdir
--
-- 6. Add some frequently-used compilation flags in xmake.lua
--
-- @code
--    -- add debug and release modes
--    add_rules("mode.debug", "mode.release")
--
--    -- add macro defination
--    add_defines("NDEBUG", "_GNU_SOURCE=1")
--
--    -- set warning all as error
--    set_warnings("all", "error")
--
--    -- set language: c99, c++11
--    set_languages("c99", "c++11")
--
--    -- set optimization: none, faster, fastest, smallest
--    set_optimize("fastest")
--
--    -- add include search directories
--    add_includedirs("/usr/include", "/usr/local/include")
--
--    -- add link libraries and search directories
--    add_links("tbox")
--    add_linkdirs("/usr/local/lib", "/usr/lib")
--
--    -- add system link libraries
--    add_syslinks("z", "pthread")
--
--    -- add compilation and link flags
--    add_cxflags("-stdnolib", "-fno-strict-aliasing")
--    add_ldflags("-L/usr/local/lib", "-lpthread", {force = true})
--
-- @endcode
--

