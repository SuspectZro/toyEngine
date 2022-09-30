
add_rules("mode.debug", "mode.release")
add_requires("glfw")
add_requires("spdlog")
add_requires("soloud")
add_requires("glm")
--add_requires("stb")

includes("external/xmake_soloud.lua")

target("toyEngine")
    set_kind("static")
    set_languages("cxx17")
    
    -- Declare packages we want to use.
    add_packages("glfw", {public = true})
    add_packages("spdlog")
    add_packages("soloud", {public = true})
    add_packages("glm", {public = true})
    --add_packages("stb", {public = true})

    -- Declare our engine's header path.
    -- This allows targets that depend on the engine to #include them.
    add_includedirs("src", {public = true})
    
    -- Add all .cpp files in the `src` directory.
    add_files("src/*.cpp")


target("helloworld")
    set_kind("binary")
    set_languages("cxx17")
    
    add_deps("toyEngine")
    
    add_files("demo/helloworld.cpp")

    -- Copy assets
    after_build(function (target)
        cprint("Copying assets")
        os.cp("$(projectdir)/assets", path.directory(target:targetfile()))
    end)