# Traversed

Traversed Engine is a 3D Engine for Game Development, this engine is used to learn game development in the third year of citm-upc.

# Features:

- Baker_house is automatically loaded at the start.
- It accepts drag&drop of FBX files from the assests folder of current project.
- It accepts drag&drop of DDS/PNG files (apply the texture to the selected GameObject)(firstly select a gameobject, then drop the file into inspector).
- There's a GameObject structure, one for each loaded mesh. Each GameObject has 3 display-only components: Transform, Mesh and Texture.

# Camera Controls:
- While Right clicking, free look around is enabled.
- “WASD” fps-like movement.
- Mouse wheel zoom in and out.
- Pressing “f” focus the camera around the center point(0,0,0).
- Holding SHIFT duplicates movement speed.
- Alt+Left click can orbit the object.

# Editor Windows:
General menu:
- File: save and load the configuration, quit engine.
- Windows: It's able to turn on/off editor windows.
- Create Object: load some basic shapes.
- help: visit the github page and get info about the engine. 

Configuration:
- A graph for the frames per second.
- Configuration for all variables on each module (window, renderer, input).
- Information output of memory consumption, hardware detection and software

About:
- engine introduction 
- versions (SDL, OpenGL, DevIL).
- License 

Hierarchy: 
- It displays a list with all GameObjects in this window. The user is able to select a GameObject through this window.

Inspector: 
- It display information about the components of the selected GameObject
- Transform: only for display purposes. Show position, rotation and scale for the selected GameObject.
- Mesh: information about the loaded mesh.
- Texture: display texture size. 

# Link to GitHub repository:
https://github.com/guerra22/Traversed

# Developers:

# Libraries:

# License 
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
