workspace "SPing"
	configurations {"Debug", "Release"}
	architecture "x86"

-- 路径 汇总----
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/"
thirdpart = "%{wks.location}/" .. "ThirdPart/"
testdir = "%{wks.location}/" .. "Test/"
exampleDir = "%{wks.location}/" .. "Example/"
projects_Dir = "%{wks.location}/" .. "build/"


spdlog_root = thirdpart .. "spdlog/"
GLFW_root = thirdpart .. "GLFW/"
SPing_root = "%{wks.location}/" .. "SPing/"
SandBox_root = "%{wks.location}/" .. "SandBox/"

thirdpartIncDir = {}
thirdpartIncDir["GLFW"] = thirdpart .. "GLFW/include"
thirdpartIncDir["spdlog"] = thirdpart .. "spdlog/include"

-- 测试项目路径
Test_spdlog_root = testdir .. "Testspdlog/"
Test_memory_pool_root = testdir .. "TestMemoryPool/"
test_others_root = testdir .. "TestOthers/"


binDir = "%{wks.location}/bin/"
tmpBinDir = "%{wks.location}/bin-tmp/"

-- 相对路径--
---
dofile "build/SPing_premake.lua"
--dofile "build/SandBox_premake.lua"
dofile "build/glfw_premake.lua"
dofile "build/spdlog_premake.lua"
dofile "build/testspdlog_premake.lua"
dofile "build/test_memory_pool.lua"
dofile "build/test_others.lua"
