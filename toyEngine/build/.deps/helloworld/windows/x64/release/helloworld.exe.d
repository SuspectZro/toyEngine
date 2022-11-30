{
    files = {
        [[build\.objs\helloworld\windows\x64\release\demo\helloworld.cpp.obj]],
        [[build\windows\x64\release\toyEngine.lib]]
    },
    values = {
        [[C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.33.31629\bin\HostX64\x64\link.exe]],
        {
            "-nologo",
            "-dynamicbase",
            "-nxcompat",
            "-machine:x64",
            [[-libpath:build\windows\x64\release]],
            [[-libpath:C:\Users\Alex\AppData\Local\.xmake\packages\g\glfw\3.3.8\d12e591897c9472fb7d3725fa5811388\lib]],
            [[-libpath:C:\Users\Alex\AppData\Local\.xmake\packages\s\soloud\20200207\df7d2de22c464928871173041a5f621f\lib]],
            [[-libpath:C:\Users\Alex\AppData\Local\.xmake\packages\l\lua\v5.4.4\200aae53e3a8489bb9f8fd764de1b658\lib]],
            "/opt:ref",
            "/opt:icf",
            "toyEngine.lib",
            "glfw3.lib",
            "opengl32.lib",
            "soloud.lib",
            "lua.lib",
            "user32.lib",
            "shell32.lib",
            "gdi32.lib"
        }
    }
}