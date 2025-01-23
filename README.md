# Homework solutions for "Modern C++ for Computer Vision" offered by Ignacio Vizzo and Cyrill Stachniss

## Course Info
All lectures' video recordings, slides and homeworks are available:
https://www.ipb.uni-bonn.de/teaching/cpp-2020/index.html and
https://youtu.be/sZK6ouwREXA?si=rRFiKEFzs0U16gIJ

It is a fantastic course for learning modern c++! Many thanks to Dr. Ignacio Vizzo and Prof. Cyrill Stachniss.


## Note for this repo
As gitlab of Bonn Uni is not publicly accessible, all homework solutions are only locally validated. All homework solutions passed the local tests, except the the validation of kmeans in homework_7, in which multiple solutions exist for the 3 word case, and my solution is also valid in my opinion.

## Requirements

Install required programming environment according to the tutorial 1:
https://youtu.be/PBHNeNSub8A?si=cCqAu9E7DsZ75MfQ

1. git build-essential cmake cppcheck
```
sudo apt install git build-essential cmake cppcheck
```

1. llvm (clangd 10.0) offered in this repo
./install_llvm_toolchain.sh

1. Install vscode
2. Install vscode addons
c/c++, c/c++ Flylint, clangd, cmake, cmake tools helper, cmake format, markdown all in one, markdown lint, markdown preview enhanced, markdown table format, vsliveshare
1. config vscode settings (Ctrl+Comma in vscode and open settings (JSON) icon in the top right corner)
```
{
    "files.autoSave": "afterDelay",
    /* GLOBAL EDITOR CONF */
    "editor.formatOnType": true,
    "editor.formatOnPaste": true,
    "editor.formatOnSave": true,
    /* C++ STUFF */
    "C_Cpp.autocomplete": "disabled",
    "C_Cpp.formatting": "disabled",
    "C_Cpp.errorSquiggles": "disabled",
    "C_Cpp.intelliSenseEngine": "disabled",
    //clang
    "clangd.arguments": [
        "--background-index",
        "--clang-tidy",
        "--header-insertion=iwyu",
        "--suggest-missing-includes",
        "--compile-commands-dir=./build/"
    ],
    //cppcheck
    "c-cpp-flylint.clang.enable": false,
    "c-cpp-flylint.flexelint.enable": false,
    "c-cpp-flylint.cppcheck.enable": true,
    "c-cpp-flylint.cppcheck.inconclusive": true,
    "c-cpp-flylint.cppcheck.verbose": true,
    "cmake.pinnedCommands": [
        "workbench.action.tasks.configureTaskRunner",
        "workbench.action.tasks.runTask"
    ]
}
```

That's pretty much it, enjoy!
