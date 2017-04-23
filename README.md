
Low level C++ multimedia engine.

Supported Platforms / Toolchains:
	- Windows / Visual C++ 2015
	- Windows / MinGW-w64
	- Linux / GCC
	- Linux / clang
	- Android / GCC
	- Web / emscripten

- Test-Driven development 
- Support for Windows, Linux, Web and Android.


Features:

Core
	- Buffer Abstraction
	
	- Stream Abstration
		- Memory Stream.
		- Memory Reference Stream.
		- Buffer Stream
		- File Stream.
		
	- Archive Abstraction
		- Folder Archive
		- Zipped Archive
		
Math 
	- n-dimensional Vector operations.
		- Addition and Subtraction.
		- Multiplication and Division by Scalar.
		- Multiplication and Division component wise.
		- Dot Product.
		- Cross Product.
		- Length.
		- Normalize
		- Clamp.
		- Triple Dot Product.
		- Triple Vector Product.
		- Projection
		
	- Quaternion operations.
		- Addition and Subtraction.
		- Multiplication and Division.
		- Multiplication and Division by Scalar.
		- Length.
		- Inverse. 
		- Normalize.
		- Conjugate.
		
	- nxm- dimensional Matrix operations.
		- Addition and Subtraction.
		- Multiplication and Division.
		- Multiplication and Division by Scalar.
		- Transpose
		- Determinant
		- Inverse
	
Geometry 
	- Plane 
	- Triangle 
	- Ray
	- Segment
	- Bounding Volumes
		- Sphere
		- Ellipsoid
		- Axis-Aligned Bouding Box
		
	- Operations
		 - Plane - Ray Intersection
		 - Sphere - Ray Intersection
		 - Ellipsoid - Ray Intersection
		 - AABBox - Ray Intersection
		 
		 - Plane - Segment Intersection
		 - Sphere - Segment Intersection
		 - Ellipsoid - Segment Intersection
		 - AABBox - Segment Intersection
		 
Input
	- Support for Mouse
		- Mouse Button Press and Release
		- Mouse Move
		- Mouse Bidirectional Wheel
	
	- Support for Keyboard
		- Key Press
		- Key Release
		
	- Suppport for Joypad 
		- Pad Press and Release
		- Joypad Button Press and Release
		- Joypad Handle Move.
	
	- Support for Touch (investigate more)
	
Graphics
	- 3D Raster rendering.
	- 3D Ray Tracing rendering
	- 3D Rasterization Abstraction
		- Raster Device
		- Texture
		- Buffer
		
	- Flexible vertex formats
	- Extensible interface for additional image formats
	- Extensible interface for additional mesh formats 
	
Audio
	- Simple 2D Play
		- Volume Control
		- Pitch Control 
		
	- Listener Model 3D 
		- Volume Control
		- Pitch Control
		
	- Audio Buffers
	- Audio Buffer Queues
	- Extensible interface for loading Audio Samples 
	- Extensible inteface for sound effects
	
Scene Graph 
	- Scene - Based rendering 
	