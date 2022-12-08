# Traversed

Traversed Engine is a 3D Engine for Game Development, this engine is used to learn game development in the third year of citm-upc.

# Features
- There's a GameObject structure, one for each loaded mesh. Each GameObject could have 4 display components: Transform, Mesh, Texture and Camera.
- Custom File for load&save the scene.
- Serialization
- Frustum Culling for the game camera.
- Mouse Picking in editor view.
- Simple Resource Management.

# Attention
- Street scene is automatically loaded at the start.
- The scene view is black at the start because the initial postion of the editor camera is in the origin point(there's nothing in the view of camera), you should move the camera with camera controls.(Review the instructions below)
- The game view dosen't display nothing  because it dosen't have a Camera object, in order to do that please read the instruction of game panel below.
# Editor Windows
## Scene panel 
Camera Controls:
- While Right clicking, free look around is enabled.
- While Right clicking, “WASD” fps-like movement.()
- holding the "shift" key to duplicate the movement speed.
- Mouse wheel zoom in and out.
- Pressing “f” focus the camera around the selected object.
- Holding SHIFT duplicates movement speed.
- "Alt Left/right" can orbit camera around the selected object.
Mouse picking:
- An object can be selected if you move the cursor on an object and left click the mouse.(The axis of the object displayed)
- When one object is selected in secen panel, click and drag the axis can chage the transform("Q"->Position, "E"->Rotation, "R"->Scale)

## Game panel
- The game view only displays when there is a Camera object.
- In order to do it, u should right click the mouse in the Hierarchy panel and create a camera node.
- The initial position of a camera object is (0,0,0)
- You can change the transform of the camera in Inspector to move game view.

## General menu
File: 
- New Scene: Create a new scene(clear current scene)
- Save Scene: Save current scene to Library folder.
- Load Scene: Pop up the file browser window, u can find and choose the target scene file to load.
- Exit: quit the engine.

View:
- Enable and disable the panels.

Help:
- Visit github page
- About information

## Configuration panel
- A graph for the frames per second.
- Configuration for all variables on each module (window, renderer, input).
- Information of Game and Resources. 
- Information output of memory consumption, hardware detection and software

## About panel
- engine introduction 
- versions (SDL, OpenGL, DevIL......).
- License 

## Hierarchy panel:
- It displays a list with all GameObjects in this window. The user is able to select a GameObject through this window.
- Right click the mouse->Creat a new node.(Empty, spetail, mesh, camera)

## Inspector panel
- It display information about the components of the selected GameObject
- It's allowed to add a new component or delet the component. 
- Transform: change the value of position, rotation and scale for the selected GameObject.
- Mesh: information about the loaded mesh.
- Texture: information about the loaded texture.(support drag&drop from Library panel)
- Camera: information about the loaded camera.

## Console panel
- display the logs messages.
- Clear->Clear the list of logs.
- Log types->filter the different log types.
- Options->extra options.
- Collapse->Collapses all the logs that are exactly the same.
- Time->Shows the time when the log has been registered.

## Library panel
- Display the game library files for the engine.
- All files are displayed in box view.
- You can click the folder file to see the content files.
- It accepts drag&drop of FBX files from the Library panel folder to the scene panel.
- It accepts drag&drop of DDS/PNG files from the Library panel folder(apply the texture to the selected GameObject)(firstly select a gameobject, then drop the file into Material component in inspector).

# Developers
- [Hang Xue](https://github.com/Patronum129)
- [Oriol Via](https://github.com/guerra22)

# Link to GitHub repository
https://github.com/guerra22/Traversed

# Libraries
- [SDL](https://github.com/libsdl-org/SDL)
- [Glew](https://github.com/nigels-com/glew)
- [ImGUI](https://github.com/ocornut/imgui)
- [JSON](https://github.com/nlohmann/json)
- [MathGeoLib](https://github.com/juj/MathGeoLib)
- [Assimp](https://github.com/assimp/assimp)
- [DevIL](https://github.com/DentonW/DevIL)

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
