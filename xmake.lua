add_requires("cpp-httplib", "nlohmann_json", "base-n")

target("rjsjai")
    set_kind("static")
    add_packages("cpp-httplib", "nlohmann_json", "base-n")
    add_files("src/*.cpp")
    add_includedirs("includes", {public = true})
    add_defines("SERVER_HOST=$(env SERVER_HOST)", "SERVER_PORT=$(env SERVER_PORT)")
    set_languages("c++17")
    set_targetdir("lib")
    if is_plat("windows") then
        add_cxflags("/utf-8")
        add_ldflags("/MT")
    else
        add_ldflags("-static")
    end
    if is_os("windows") then
        add_links("Ws2_32")
    end

target("test")
    set_kind("binary")
    add_deps("rjsjai")
    add_files("test/*.cpp")
    set_languages("c++17")
    set_targetdir("bin")
    if is_plat("windows") then
        add_cxflags("/utf-8")
    end
