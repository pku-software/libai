add_requires("cpp-httplib", "nlohmann_json", "base-n")

target("libai")
    set_kind("static")
    set_license("GPL-3.0")
    add_packages("cpp-httplib", "nlohmann_json", "base-n")
    add_files("src/*.cpp")
    add_includedirs("includes", {public = true})
    add_defines("SERVER_HOST=$(env SERVER_HOST)", "SERVER_PORT=$(env SERVER_PORT)")
    set_languages("c++20")
    set_targetdir("lib")
    if is_plat("windows") then
        add_cxflags("/utf-8")
    end

target("test")
    set_kind("binary")
    set_license("GPL-3.0")
    add_deps("libai")
    add_files("test/*.cpp")
    set_languages("c++20")
    set_targetdir("bin")
    if is_plat("windows") then
        add_cxflags("/utf-8")
    end
