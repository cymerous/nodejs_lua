{
  "targets": [
    {
      "target_name": "NodejsLua",
      "conditions": [
        [
          "OS=='win'",
          {
            "include_dirs": [
              "./win64luajit"
            ],
            "library_dirs": [
              "./win64luajit"
            ],
            "libraries": [
              "lua51.lib"
            ],
            "copies":[
              { 
                'destination': './build/Release',
                'files':[
                  "./win64luajit/lua51.dll"
                ]
              },
            ]
          }
        ],
        [
          'OS=="mac"',
          {
            "include_dirs": [
              "./maclualib/include"
            ],
            "libraries": [
              "../maclualib/lib/liblua.a"
            ],
            "actions": [],
            "cflags": [
              "-std=c++11",
              "-stdlib=libc++"
            ],
            "xcode_settings": {
              "CLANG_CXX_LANGUAGE_STANDARD": "c++0x",
              "CLANG_CXX_LIBRARY": "libc++"
            }
          }
        ],
        [
          'OS=="linux"',
          {
            "include_dirs": [
              "/usr/local/include/luajit-2.1"
            ],
            "library_dirs": [
              "/usr/local/lib"
            ],
            "libraries": [
              "/usr/local/lib/libluajit-5.1.so"
            ],
            "actions": []
          }
        ]
      ],
      "sources": [
        "src/NodejsLua.cc",
      ],
      'include_dirs': ["<!(node -p \"require('node-addon-api').include_dir\")"],
      'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ]
    }
  ]
}
