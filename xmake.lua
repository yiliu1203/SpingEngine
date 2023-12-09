add_rules("mode.debug", "mode.release")
add_defines("SP_PLATFORM_WIN")
set_optimize("none")
set_languages("clatest", "cxx20")
-- add_cxflags("/EHsc")
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


target("001_HelloWorld")
    set_kind("binary")
    add_deps("SPing")
    add_links("SPing")
    add_includedirs("Source/SPing")
    add_includedirs("$(buildir)/config/001_HelloWorld")
    add_files("Source/Samples/001_HelloWorld/*.cpp")
    set_configvar("SP_BUILD_DLL", false)
    set_configdir("$(buildir)/config/001_HelloWorld")
    add_configfiles("Source/SPing/MacroConfig.h.in")
    add_syslinks("User32", "kernel32", "Gdi32", "Shell32", "DXGI", "D3D12", "D3DCompiler")




target("002_Object")
    set_kind("binary")
    add_deps("SPing")
    add_links("SPing")
    add_includedirs("Source/SPing")
    add_includedirs("$(buildir)/config/002_Object")
    add_files("Source/Samples/002_Object/*.cpp")
    set_configvar("SP_BUILD_DLL", false)
    set_configdir("$(buildir)/config/002_Object")
    add_configfiles("Source/SPing/MacroConfig.h.in")
    add_syslinks("User32", "kernel32", "Gdi32", "Shell32", "DXGI", "D3D12", "D3DCompiler")



target("003_RTTI")
    set_kind("binary")
    add_files("Source/Samples/003_RTTI/*.cpp")
    add_syslinks("User32", "kernel32", "Gdi32", "Shell32", "DXGI", "D3D12", "D3DCompiler")


target("004_RTTI_Simple")
    set_kind("binary")
    add_files("Source/Samples/004_RTTI_Simple/*.cpp")
    add_syslinks("User32", "kernel32", "Gdi32", "Shell32", "DXGI", "D3D12", "D3DCompiler")


target("005_Template")
    set_kind("binary")
    add_files("Source/Samples/005_Template/*.cpp")
    add_syslinks("User32", "kernel32", "Gdi32", "Shell32", "DXGI", "D3D12", "D3DCompiler")

target("005_Template_1")
    set_kind("binary")
    add_files("Source/Samples/005_Template_1/*.cpp")
    add_syslinks("User32", "kernel32", "Gdi32", "Shell32", "DXGI", "D3D12", "D3DCompiler")


target("005_Template_2")
    set_kind("binary")
    add_files("Source/Samples/005_Template_2/main.cpp")
    add_syslinks("User32", "kernel32", "Gdi32", "Shell32", "DXGI", "D3D12", "D3DCompiler")

target("005_Template_3")
    set_kind("binary")
    add_files("Source/Samples/005_Template_3/main.cpp")
    add_syslinks("User32", "kernel32", "Gdi32", "Shell32", "DXGI", "D3D12", "D3DCompiler")


target("006_Exception")
    set_kind("binary")
    add_files("Source/Samples/006_Exception/*.cpp")
    add_syslinks("User32", "kernel32", "Gdi32", "Shell32", "DXGI", "D3D12", "D3DCompiler")

target("007_Using")
    set_kind("binary")
    add_files("Source/Samples/007_Using/*.cpp")
    add_syslinks("User32", "kernel32", "Gdi32", "Shell32", "DXGI", "D3D12", "D3DCompiler")

target("008_Dx12_Initial")
    set_kind("binary")
    add_files("Source/Samples/008_Dx12_Initial/*.cpp")
    add_defines("_XM_NO_INTRINSICS_=1", "NOMINMAX", "m128_f32=vector4_f32", "m128_u32=vector4_u32")
    add_syslinks("User32", "kernel32", "Gdi32", "Shell32", "DXGI", "D3D12", "D3DCompiler")

target("009_MemoryManager")
    set_kind("binary")
    add_files("Source/Samples/009_MemoryManager/*.cpp")
    add_defines("_XM_NO_INTRINSICS_=1", "NOMINMAX", "m128_f32=vector4_f32", "m128_u32=vector4_u32")
    add_syslinks("User32", "kernel32", "Gdi32", "Shell32", "DXGI", "D3D12", "D3DCompiler")

target("010_RTTI_MACRO")
    set_kind("binary")
    add_files("Source/Samples/010_RTTI_MACRO/*.cpp")
    add_defines("_XM_NO_INTRINSICS_=1", "NOMINMAX", "m128_f32=vector4_f32", "m128_u32=vector4_u32")
    add_syslinks("User32", "kernel32", "Gdi32", "Shell32", "DXGI", "D3D12", "D3DCompiler")

target("011_Concurrency")
    set_kind("binary")
    add_files("Source/Samples/011_Concurrency/*.cpp")
    add_defines("_XM_NO_INTRINSICS_=1", "NOMINMAX", "m128_f32=vector4_f32", "m128_u32=vector4_u32")
    add_syslinks("User32", "kernel32", "Gdi32", "Shell32", "DXGI", "D3D12", "D3DCompiler")

target("012_ThreadPool")
    set_kind("binary")
    add_files("Source/Samples/012_ThreadPool/*.cpp")
    add_defines("_XM_NO_INTRINSICS_=1", "NOMINMAX", "m128_f32=vector4_f32", "m128_u32=vector4_u32")
    add_syslinks("User32", "kernel32", "Gdi32", "Shell32")
    set_runtimes("MD")

target("013_SIMD")
    set_kind("binary")
    add_files("Source/Samples/013_SIMD/*.cpp")
    add_defines("_XM_NO_INTRINSICS_=1", "NOMINMAX", "m128_f32=vector4_f32", "m128_u32=vector4_u32")
    add_syslinks("User32", "kernel32", "Gdi32", "Shell32")
    set_runtimes("MD")

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

