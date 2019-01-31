#include <Game.h>

static bool flip;

Game::Game() : window(VideoMode(800, 600), "OpenGL Cube Texturing")
{
}

Game::~Game() {}

void Game::run()
{

	initialize();

	Event event;

	while (isRunning) {

#if (DEBUG >= 2)
		DEBUG_MSG("Game running...");
#endif

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				isRunning = false;
			}
		}
		update();
		render();
	}

}

typedef struct
{
	float coordinate[3];
	float color[4];
	float texel[2];
} Vert;

Vert vertex[36];
Vert displacementVerts;
Vert resultVerts[36];
GLubyte triangles[36];

/* Variable to hold the VBO identifier and shader data */
GLuint	index,		//Index to draw
		vsid,		//Vertex Shader ID
		fsid,		//Fragment Shader ID
		progID,		//Program ID
		vao = 0,	//Vertex Array ID
		vbo[1],		// Vertex Buffer ID
		positionID, //Position ID
		colorID,	// Color ID
		to,			// Texture ID 1 to 32
		textureID,	//Texture ID
		texelID;	// Texel ID

//const string filename = "texture.tga";
//const string filename = "cube.tga";

const string filename = "texture.tga";

int width; //width of texture
int height; //height of texture
int comp_count; //Component of texture
const int number = 4; //4 = RGBA

unsigned char* img_data;

void Game::initialize()
{
	isRunning = true;
	GLint isCompiled = 0;
	GLint isLinked = 0;

	glewInit();

	DEBUG_MSG(glGetString(GL_VENDOR));
	DEBUG_MSG(glGetString(GL_RENDERER));
	DEBUG_MSG(glGetString(GL_VERSION));

	// initialize (needs to not be 0)
	displacementVerts.coordinate[0] = 0.1;
	displacementVerts.coordinate[1] = 0.1;
	displacementVerts.coordinate[2] = 0.1;

	/* Vertices counter-clockwise winding */
	vertex[0].coordinate[0] = -0.5f;
	vertex[0].coordinate[1] = -0.5f;
	vertex[0].coordinate[2] = -0.5f;

	vertex[1].coordinate[0] = -0.5f;
	vertex[1].coordinate[1] = 0.5f;
	vertex[1].coordinate[2] = -0.5f;

	vertex[2].coordinate[0] = 0.5f;
	vertex[2].coordinate[1] = 0.5f;
	vertex[2].coordinate[2] = -0.5f;

	vertex[3].coordinate[0] = 0.5f;
	vertex[3].coordinate[1] = 0.5f;
	vertex[3].coordinate[2] = -0.5f;

	vertex[4].coordinate[0] = 0.5f;
	vertex[4].coordinate[1] = -0.5f;
	vertex[4].coordinate[2] = -0.5f;

	vertex[5].coordinate[0] = -0.5f;
	vertex[5].coordinate[1] = -0.5f;
	vertex[5].coordinate[2] = -0.5f;

	vertex[6].coordinate[0] = -0.5f;
	vertex[6].coordinate[1] = -0.5f;
	vertex[6].coordinate[2] = 0.5f;

	vertex[7].coordinate[0] = -0.5f;
	vertex[7].coordinate[1] = 0.5f;
	vertex[7].coordinate[2] = 0.5f;

	vertex[8].coordinate[0] = 0.5f;
	vertex[8].coordinate[1] = 0.5f;
	vertex[8].coordinate[2] = 0.5f;

	vertex[9].coordinate[0] = 0.5f;
	vertex[9].coordinate[1] = 0.5f;
	vertex[9].coordinate[2] = 0.5f;

	vertex[10].coordinate[0] = 0.5f;
	vertex[10].coordinate[1] = -0.5f;
	vertex[10].coordinate[2] = 0.5f;

	vertex[11].coordinate[0] = -0.5f;
	vertex[11].coordinate[1] = -0.5f;
	vertex[11].coordinate[2] = 0.5f;
	//=====================================================
	vertex[12].coordinate[0] = -0.5f;
	vertex[12].coordinate[1] = -0.5f;
	vertex[12].coordinate[2] = -0.5f;

	vertex[13].coordinate[0] = -0.5f;
	vertex[13].coordinate[1] = 0.5f;		// left wall
	vertex[13].coordinate[2] = -0.5f;

	vertex[14].coordinate[0] = -0.5f;
	vertex[14].coordinate[1] = 0.5f;
	vertex[14].coordinate[2] = 0.5f;

	vertex[15].coordinate[0] = -0.5f;
	vertex[15].coordinate[1] = 0.5f;
	vertex[15].coordinate[2] = 0.5f;

	vertex[16].coordinate[0] = -0.5f;
	vertex[16].coordinate[1] = -0.5f;
	vertex[16].coordinate[2] = 0.5f;

	vertex[17].coordinate[0] = -0.5f;
	vertex[17].coordinate[1] = -0.5f;
	vertex[17].coordinate[2] = -0.5f;

	vertex[18].coordinate[0] = 0.5f;
	vertex[18].coordinate[1] = -0.5f;
	vertex[18].coordinate[2] = 0.5f;

	vertex[19].coordinate[0] = 0.5f;
	vertex[19].coordinate[1] = 0.5f;
	vertex[19].coordinate[2] = 0.5f;

	vertex[20].coordinate[0] = 0.5f;
	vertex[20].coordinate[1] = 0.5f;
	vertex[20].coordinate[2] = -0.5f;

	vertex[21].coordinate[0] = 0.5f;
	vertex[21].coordinate[1] = 0.5f;
	vertex[21].coordinate[2] = -0.5f;

	vertex[22].coordinate[0] = 0.5f;
	vertex[22].coordinate[1] = -0.5f;
	vertex[22].coordinate[2] = -0.5f;

	vertex[23].coordinate[0] = 0.5f;
	vertex[23].coordinate[1] = -0.5f;
	vertex[23].coordinate[2] = 0.5f;
	//============================================
	vertex[24].coordinate[0] = -0.5f;
	vertex[24].coordinate[1] = -0.5f;
	vertex[24].coordinate[2] = -0.5f;

	vertex[25].coordinate[0] = 0.5f;
	vertex[25].coordinate[1] = -0.5f;		// left wall
	vertex[25].coordinate[2] = -0.5f;

	vertex[26].coordinate[0] = 0.5f;
	vertex[26].coordinate[1] = -0.5f;
	vertex[26].coordinate[2] = 0.5f;

	vertex[27].coordinate[0] = 0.5f;
	vertex[27].coordinate[1] = -0.5f;
	vertex[27].coordinate[2] = 0.5f;

	vertex[28].coordinate[0] = -0.5f;
	vertex[28].coordinate[1] = -0.5f;
	vertex[28].coordinate[2] = 0.5f;

	vertex[29].coordinate[0] = -0.5f;
	vertex[29].coordinate[1] = -0.5f;
	vertex[29].coordinate[2] = -0.5f;
	//
	vertex[30].coordinate[0] = -0.5f;
	vertex[30].coordinate[1] = 0.5f;
	vertex[30].coordinate[2] = 0.5f;

	vertex[31].coordinate[0] = 0.5f;
	vertex[31].coordinate[1] = 0.5f;
	vertex[31].coordinate[2] = 0.5f;

	vertex[32].coordinate[0] = 0.5f;
	vertex[32].coordinate[1] = 0.5f;
	vertex[32].coordinate[2] = -0.5f;

	vertex[33].coordinate[0] = 0.5f;
	vertex[33].coordinate[1] = 0.5f;
	vertex[33].coordinate[2] = -0.5f;

	vertex[34].coordinate[0] = -0.5f;
	vertex[34].coordinate[1] = 0.5f;
	vertex[34].coordinate[2] = -0.5f;

	vertex[35].coordinate[0] = -0.5f;
	vertex[35].coordinate[1] = 0.5f;
	vertex[35].coordinate[2] = 0.5f;

	/*vertex[0].color[0] = 1.0f;
	vertex[0].color[1] = 0.0f;
	vertex[0].color[2] = 0.0f;
	vertex[0].color[3] = 1.0f;

	vertex[1].color[0] = 1.0f;
	vertex[1].color[1] = 0.0f;
	vertex[1].color[2] = 0.0f;
	vertex[1].color[3] = 1.0f;

	vertex[2].color[0] = 1.0f;
	vertex[2].color[1] = 0.0f;
	vertex[2].color[2] = 0.0f;
	vertex[2].color[3] = 0.0f;*/

	vertex[0].texel[0] = 0.5f;
	vertex[0].texel[1] = 0.5f;

	vertex[1].texel[0] = 1.0f;
	vertex[1].texel[1] = 1.0f;

	vertex[2].texel[0] = 1.0f;
	vertex[2].texel[1] = 0.0f;

	/*Index of Poly / Triangle to Draw */
	for (int i = 0; i < sizeof(triangles); i++)
	{
		triangles[i] = i;
	}

	/* Create a new VBO using VBO id */
	glGenBuffers(1, vbo);

	/* Bind the VBO */
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

	/* Upload vertex data to GPU */
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vert) * 9, resultVerts, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * 36, triangles, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	/* Vertex Shader which would normally be loaded from an external file */
	const char* vs_src = "#version 400\n\r"
		"in vec4 sv_position;"
		"in vec4 sv_color;"
		"in vec2 sv_texel;"
		"out vec4 color;"
		"out vec2 texel;"
		"void main() {"
		"	color = sv_color;"
		"	texel = sv_texel;"
		"	gl_Position = sv_position;"
		"}"; //Vertex Shader Src

	DEBUG_MSG("Setting Up Vertex Shader");

	vsid = glCreateShader(GL_VERTEX_SHADER); //Create Shader and set ID
	glShaderSource(vsid, 1, (const GLchar**)&vs_src, NULL); // Set the shaders source
	glCompileShader(vsid); //Check that the shader compiles

	//Check is Shader Compiled
	glGetShaderiv(vsid, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_TRUE) {
		DEBUG_MSG("Vertex Shader Compiled");
		isCompiled = GL_FALSE;
	}
	else
	{
		DEBUG_MSG("ERROR: Vertex Shader Compilation Error");
	}

	/* Fragment Shader which would normally be loaded from an external file */
	const char* fs_src = "#version 400\n\r"
		"uniform sampler2D f_texture;"
		"in vec4 color;"
		"in vec2 texel;"
		"out vec4 fColor;"
		"void main() {"
		//"	fColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);"
		"	fColor = texture(f_texture, texel.st);"
		"}"; //Fragment Shader Src

	DEBUG_MSG("Setting Up Fragment Shader");

	fsid = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fsid, 1, (const GLchar**)&fs_src, NULL);
	glCompileShader(fsid);
	//Check is Shader Compiled
	glGetShaderiv(fsid, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_TRUE) {
		DEBUG_MSG("Fragment Shader Compiled");
		isCompiled = GL_FALSE;
	}
	else
	{
		DEBUG_MSG("ERROR: Fragment Shader Compilation Error");
	}

	DEBUG_MSG("Setting Up and Linking Shader");
	progID = glCreateProgram();	//Create program in GPU
	glAttachShader(progID, vsid); //Attach Vertex Shader to Program
	glAttachShader(progID, fsid); //Attach Fragment Shader to Program
	glLinkProgram(progID);

	//Check is Shader Linked
	glGetProgramiv(progID, GL_LINK_STATUS, &isLinked);

	if (isLinked == 1) {
		DEBUG_MSG("Shader Linked");
	}
	else
	{
		DEBUG_MSG("ERROR: Shader Link Error");
	}

	// Use Progam on GPU
	// https://www.opengl.org/sdk/docs/man/html/glUseProgram.xhtml
	glUseProgram(progID);

	img_data = stbi_load(filename.c_str(), &width, &height, &comp_count, 4);

	if (img_data == NULL)
	{
		DEBUG_MSG("ERROR: Texture not loaded");
	}

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &to);
	glBindTexture(GL_TEXTURE_2D, to);

	//Wrap around
	//https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexParameter.xml
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//Filtering
	//https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexParameter.xml
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//Bind to OpenGL
	//https://www.khronos.org/opengles/sdk/docs/man/xhtml/glTexImage2D.xml
	glTexImage2D(GL_TEXTURE_2D, //2D Texture Image
		0, //Mipmapping Level 
		GL_RGBA, //GL_RED, GL_GREEN, GL_BLUE, GL_ALPHA, GL_RGB, GL_BGR, GL_RGBA 
		width, //Width
		height, //Height
		0, //Border
		GL_RGBA, //Bitmap
		GL_UNSIGNED_BYTE, img_data);

	// Find variables in the shader
	//https://www.khronos.org/opengles/sdk/docs/man/xhtml/glGetAttribLocation.xml
	positionID = glGetAttribLocation(progID, "sv_position");
	colorID = glGetAttribLocation(progID, "sv_color");
	texelID = glGetAttribLocation(progID, "sv_texel");
	textureID = glGetUniformLocation(progID, "f_texture");
}

void Game::update()
{
	elapsed = clock.getElapsedTime();

	if (elapsed.asSeconds() >= 1.0f)
	{
		clock.restart();

		if (!flip)
		{
			flip = true;
		}
		else
			flip = false;
	}

	if (flip)
	{
		rotationAngle += 0.005f;

		if (rotationAngle > 360.0f)
		{
			rotationAngle -= 360.0f;
		}
	}

	//Change vertex data
	checkKeyInput();
	updateResultVerts();

#if (DEBUG >= 2)
	DEBUG_MSG("Update up...");
#endif

}

void Game::render()
{

#if (DEBUG >= 2)
	DEBUG_MSG("Drawing...");
#endif

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);

	/*	As the data positions will be updated by the this program on the
		CPU bind the updated data to the GPU for drawing	*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vert) * 36, resultVerts, GL_STATIC_DRAW);

	/*	Draw Triangle from VBO	(set where to start from as VBO can contain
		model components that 'are' and 'are not' to be drawn )	*/

	//Set Active Texture .... 32
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(textureID, 0);

	// Set pointers for each parameter
	// https://www.opengl.org/sdk/docs/man4/html/glVertexAttribPointer.xhtml
	glVertexAttribPointer(positionID, 3, GL_FLOAT, GL_FALSE, sizeof(Vert), 0);
	glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, sizeof(Vert), 0);
	glVertexAttribPointer(texelID, 2, GL_FLOAT, GL_FALSE, sizeof(Vert), 0);

	//Enable Arrays
	glEnableVertexAttribArray(positionID);
	glEnableVertexAttribArray(colorID);
	glEnableVertexAttribArray(texelID);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, (char*)NULL + 0);

	window.display();

}

void Game::unload()
{
#if (DEBUG >= 2)
	DEBUG_MSG("Cleaning up...");
#endif
	glDeleteProgram(progID);
	glDeleteBuffers(1, vbo);
	stbi_image_free(img_data); //Free image
}

void Game::checkKeyInput()
{
	// rotations...
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		for (int i = 0; i < 36; i++)
		{
			tempVector.x = vertex[i].coordinate[0];
			tempVector.y = vertex[i].coordinate[1];
			tempVector.z = vertex[i].coordinate[2];

			tempVector = (MyMatrix3::rotationX(0.001) * tempVector);

			vertex[i].coordinate[0] = tempVector.x;
			vertex[i].coordinate[1] = tempVector.y;
			vertex[i].coordinate[2] = tempVector.z;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		for (int i = 0; i < 36; i++)
		{
			tempVector.x = vertex[i].coordinate[0];
			tempVector.y = vertex[i].coordinate[1];
			tempVector.z = vertex[i].coordinate[2];

			tempVector = (MyMatrix3::rotationX(-0.001) * tempVector);

			vertex[i].coordinate[0] = tempVector.x;
			vertex[i].coordinate[1] = tempVector.y;
			vertex[i].coordinate[2] = tempVector.z;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		for (int i = 0; i < 36; i++)
		{
			tempVector.x = vertex[i].coordinate[0];
			tempVector.y = vertex[i].coordinate[1];
			tempVector.z = vertex[i].coordinate[2];

			tempVector = (MyMatrix3::rotationZ(0.001) * tempVector);

			vertex[i].coordinate[0] = tempVector.x;
			vertex[i].coordinate[1] = tempVector.y;
			vertex[i].coordinate[2] = tempVector.z;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		for (int i = 0; i < 36; i++)
		{
			tempVector.x = vertex[i].coordinate[0];
			tempVector.y = vertex[i].coordinate[1];
			tempVector.z = vertex[i].coordinate[2];

			tempVector = (MyMatrix3::rotationZ(-0.001) * tempVector);

			vertex[i].coordinate[0] = tempVector.x;
			vertex[i].coordinate[1] = tempVector.y;
			vertex[i].coordinate[2] = tempVector.z;
		}
	}
	// SCALE...
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		for (int i = 0; i < 36; i++)
		{
			tempVector.x = vertex[i].coordinate[0];
			tempVector.y = vertex[i].coordinate[1];
			tempVector.z = vertex[i].coordinate[2];

			tempVector = (MyMatrix3::scale(0.99) * tempVector);

			vertex[i].coordinate[0] = tempVector.x;
			vertex[i].coordinate[1] = tempVector.y;
			vertex[i].coordinate[2] = tempVector.z;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		for (int i = 0; i < 36; i++)
		{
			tempVector.x = vertex[i].coordinate[0];
			tempVector.y = vertex[i].coordinate[1];
			tempVector.z = vertex[i].coordinate[2];

			tempVector = (MyMatrix3::scale(1.01) * tempVector);

			vertex[i].coordinate[0] = tempVector.x;
			vertex[i].coordinate[1] = tempVector.y;
			vertex[i].coordinate[2] = tempVector.z;
		}
	}
	// TRANSLATION...
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		for (int i = 0; i < 36; i++)
		{
			// vector addition way..
			/*displacementVectors[i] = displacementVectors[i] + MyVector3(0,0.01,0);*/

			// Matrix Translation way..
			if (displacementVerts.coordinate[2] >= 0)// if z < 0 the translation will be opposite
			{
				tempVector.x = displacementVerts.coordinate[0];
				tempVector.y = displacementVerts.coordinate[1];
				tempVector.z = displacementVerts.coordinate[2];

				tempVector = MyMatrix3::translation(MyVector3(0, 0.0001, 0)) * tempVector;

				displacementVerts.coordinate[0] = tempVector.x;
				displacementVerts.coordinate[1] = tempVector.y;
				displacementVerts.coordinate[2] = tempVector.z;
			}
			else
			{
				tempVector.x = displacementVerts.coordinate[0];
				tempVector.y = displacementVerts.coordinate[1];
				tempVector.z = displacementVerts.coordinate[2];

				tempVector = MyMatrix3::translation(MyVector3(0, -0.0001, 0)) * tempVector;

				displacementVerts.coordinate[0] = tempVector.x;
				displacementVerts.coordinate[1] = tempVector.y;
				displacementVerts.coordinate[2] = tempVector.z;
			}
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		for (int i = 0; i < 36; i++)
		{
			if (displacementVerts.coordinate[2] >= 0)// if z < 0 the translation will be opposite
			{
				tempVector.x = displacementVerts.coordinate[0];
				tempVector.y = displacementVerts.coordinate[1];
				tempVector.z = displacementVerts.coordinate[2];

				tempVector = MyMatrix3::translation(MyVector3(0, -0.0001, 0)) * tempVector;

				displacementVerts.coordinate[0] = tempVector.x;
				displacementVerts.coordinate[1] = tempVector.y;
				displacementVerts.coordinate[2] = tempVector.z;
			}
			else
			{
				tempVector.x = displacementVerts.coordinate[0];
				tempVector.y = displacementVerts.coordinate[1];
				tempVector.z = displacementVerts.coordinate[2];

				tempVector = MyMatrix3::translation(MyVector3(0, 0.0001, 0)) * tempVector;

				displacementVerts.coordinate[0] = tempVector.x;
				displacementVerts.coordinate[1] = tempVector.y;
				displacementVerts.coordinate[2] = tempVector.z;
			}
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		for (int i = 0; i < 36; i++)
		{
			if (displacementVerts.coordinate[2] >= 0)// if z < 0 the translation will be opposite
			{
				tempVector.x = displacementVerts.coordinate[0];
				tempVector.y = displacementVerts.coordinate[1];
				tempVector.z = displacementVerts.coordinate[2];

				tempVector = MyMatrix3::translation(MyVector3(0.0001, 0, 0)) * tempVector;

				displacementVerts.coordinate[0] = tempVector.x;
				displacementVerts.coordinate[1] = tempVector.y;
				displacementVerts.coordinate[2] = tempVector.z;
			}
			else
			{
				tempVector.x = displacementVerts.coordinate[0];
				tempVector.y = displacementVerts.coordinate[1];
				tempVector.z = displacementVerts.coordinate[2];

				tempVector = MyMatrix3::translation(MyVector3(-0.0001, 0, 0)) * tempVector;

				displacementVerts.coordinate[0] = tempVector.x;
				displacementVerts.coordinate[1] = tempVector.y;
				displacementVerts.coordinate[2] = tempVector.z;
			}
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		for (int i = 0; i < 36; i++)
		{
			if (displacementVerts.coordinate[2] >= 0)// if z < 0 the translation will be opposite
			{
				tempVector.x = displacementVerts.coordinate[0];
				tempVector.y = displacementVerts.coordinate[1];
				tempVector.z = displacementVerts.coordinate[2];

				tempVector = MyMatrix3::translation(MyVector3(-0.0001, 0, 0)) * tempVector;

				displacementVerts.coordinate[0] = tempVector.x;
				displacementVerts.coordinate[1] = tempVector.y;
				displacementVerts.coordinate[2] = tempVector.z;
			}
			else
			{
				tempVector.x = displacementVerts.coordinate[0];
				tempVector.y = displacementVerts.coordinate[1];
				tempVector.z = displacementVerts.coordinate[2];

				tempVector = MyMatrix3::translation(MyVector3(0.0001, 0, 0)) * tempVector;

				displacementVerts.coordinate[0] = tempVector.x;
				displacementVerts.coordinate[1] = tempVector.y;
				displacementVerts.coordinate[2] = tempVector.z;
			}
		}
	}
}

void Game::updateResultVerts()
{
	for (int i = 0; i < 36; i++)
	{
		resultVerts[i] = vertex[i];

		resultVerts[i].coordinate[0] = vertex[i].coordinate[0] + displacementVerts.coordinate[0];
		resultVerts[i].coordinate[1] = vertex[i].coordinate[1] + displacementVerts.coordinate[1];
		resultVerts[i].coordinate[2] = vertex[i].coordinate[2] + displacementVerts.coordinate[2];
	}
}

