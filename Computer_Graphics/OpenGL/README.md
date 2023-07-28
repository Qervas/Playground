# OpenGL demo repo

## Dependencies

* glad: build from CMakeLists.txt in `${project_folder}/glad`
* glfw3
* stb library: for Fedora Linux `sudo dnf install stb*", other platforms go check out [stb library](https://github.com/nothings/stb)
* glm(OpenGL Mathematics): for Fedora Linux `sudo dnf install glm-devel" , other platforms go check out [glm library](https://github.com/g-truc/glm)
* CMake

build the program
`chmod +x build.sh clean.sh`
`./build.sh`

execute the program in current folder(OpenGL)
`./build/bin/1_create_window`



* Camera interactive logics(starts at section 4)

| Key                               | Effect                                        |
| --------------------------------- | --------------------------------------------- |
| WSAD                              | Move forward, backward, leftward, rightward   |
| Space                             | Move upward                                   |
| Ctrl                              | Move downward                                 |
| Press mouse left key + drag mouse | Focus on camera and change the angle of  view |



| Section                                           | Screenshots                                                  |
| ------------------------------------------------- | ------------------------------------------------------------ |
| 1: Plain window                                   | <img src="image/README/1690536493495.png" width="70%" height="70%"> |
| 2: Plain triangle                                 | <img src="image/README/1690537053045.png" width="70%" height="70%"> |
| 3: Rotating pyramid                               | <img src="image/README/1690537984593.png" width="70%" height="70%"> |
| 4: Interactive camera                             | <img src="image/README/1690538160761.png" width="70%" height="70%"> |
| 5:Lighting                                        | <img src="image/README/1690538284979.png" width="70%" height="70%"> |
| 6: Specular maps                                  | <img src="image/README/1690538343582.png" width="70%" height="70%"> |
| 7: Types of light                                 | <div style="display: flex; flex-direction: column;"><img src="image/README/1690538548779.png" width="70%" height="70%"><img src="image/README/1690538611967.png" width="70%" height="70%"><img src="image/README/1690539684562.png" width="70%" height="70%"></div> |
| 8: Mesh & Model(glTF)                             | <img src="image/README/1690539750314.png" width="70%" height="70%"> |
| 9: Stencil buffer/ Culling faces/ Post-processing | <div style="display: flex; flex-direction: column;"><img src="image/README/1690539870698.png" width="70%" height="70%"><img src="image/README/1690544534569.png" width="70%" height="70%">          </div> |



