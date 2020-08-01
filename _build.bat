em++^
 src/c_code/main.cpp src/c_code/src/renderer/Renderer.cpp^
 src/c_code/src/mesh/material/Material.cpp src/c_code/src/mesh/material/ColorMaterial.cpp^
 src/c_code/src/mesh/material/shaders/BaseShader.cpp src/c_code/src/mesh/material/shaders/ColorShader.cpp^
 src/c_code/src/io/FileManager.cpp^
 src/c_code/src/camera/BaseCamera.cpp src/c_code/src/camera/PerspectiveCamera.cpp src/c_code/src/camera/FreeCamera.cpp^
 src/c_code/src/mesh/Mesh.cpp src/c_code/src/mesh/QuadMesh.cpp src/c_code/src/mesh/CubeMesh.cpp^
 src/c_code/src/mesh/geometry/Geometry.cpp src/c_code/src/mesh/geometry/CubeGeometry.cpp src/c_code/src/mesh/geometry/QuadGeometry.cpp^
 src/c_code/src/mesh/geometry/buffers/IndexBuffer.cpp src/c_code/src/mesh/geometry/buffers/VertexBuffer.cpp^
 src/c_code/src/scene/Scene.cpp src/c_code/src/scene/SceneManager.cpp src/c_code/src/scene/SceneObject.cpp^
 src/c_code/src/component/TransformComponent.cpp^
 src/c_code/src/commands/CameraSetViewCommand.cpp^
 -s USE_WEBGL2=1 -s USE_SDL=2 -s MAX_WEBGL_VERSION=2 -s MIN_WEBGL_VERSION=2^
 -s WASM=1 -s FETCH=1 -s NO_EXIT_RUNTIME=1 -s DISABLE_EXCEPTION_CATCHING=0 -s SAFE_HEAP=1 -s WARN_UNALIGNED=1^
 -s EXPORTED_FUNCTIONS="['_main', '_clear_color', '_create_shader_material', '_test', '_load_indices_data', '_load_attribute_data', '_geometry_color', '_read_file']"^
 -s EXPORTED_RUNTIME_METHODS="['ccall', 'cwrap']"^
 -std=c++17^
 --bind^
 --shell-file shell_files/index_shell.html^
 --preload-file src/shaders/uniform-color.shader --preload-file src/shaders/no-transform-color.shader --preload-file src/shaders/phong-light.shader^
 -g^
 -o index.html