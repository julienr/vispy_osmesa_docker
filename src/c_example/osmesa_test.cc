// From http://cs.anu.edu.au/~Hugh.Fisher/mesa3d/memcube.source

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/osmesa.h>

#define Near	 0.1
#define Far 	20.0

static int	winWidth  = 800;
static int	winHeight = 600;
static int	WireFrame = GL_TRUE;
static float	Spin = 30;
static float	CubeColor[4] = { 0, 1, 0, 1 };

static GLfloat Verts[8][3] = {
  { -0.5,  0.5, -0.5 }, /* 0 left top rear */
  {  0.5,  0.5, -0.5 },	/* 1 right top rear */
  {  0.5, -0.5, -0.5 },	/* 2 right bottom rear */
  { -0.5, -0.5, -0.5 },	/* 3 left bottom rear */
  { -0.5,  0.5,  0.5 },	/* 4 left top front */
  {  0.5,  0.5,  0.5 },	/* 5 right top front */
  {  0.5, -0.5,  0.5 },	/* 6 right bottom front */
  { -0.5, -0.5,  0.5 }	/* 7 left bottom front */
};

static int Faces[6][4] = {
  { 4, 5, 6, 7 },	/* front */
  { 5, 1, 2, 6 },	/* right */
  { 0, 4, 7, 3 },	/* left */
  { 4, 0, 1, 5 },	/* top */
  { 7, 6, 2, 3 },	/* bottom */
  { 1, 0, 3, 2 }	/* rear */
};

static GLfloat Normals[6][3] = {
  {  0,  0,  1 },
  { -1,  0,  0 },
  {  1,  0,  0 },
  {  0,  1,  0 },
  {  0, -1,  0 },
  {  0,  0, -1 }
};


static void Fail (const char * message)
{
	fprintf(stderr, "%s", message);
	exit(-1);
}

void CheckGL ()
{
	int err;

	err = glGetError();
	if (err != GL_NO_ERROR)
		Fail((char *)gluErrorString(err));
}

/****		Actual scene rendering	****/

static void drawCube()
{
	int face, vert;

	glBegin(GL_QUADS);
	for (face = 0; face < 6; face++) {
		for (vert = 0; vert < 4; vert ++) {
    			glVertex3fv(Verts[Faces[face][vert]]);
    			glNormal3fv(Normals[face]);
    		}
	}
	glEnd();
}

static void configWireStyle ()
{
	glDisable(GL_LIGHTING);
	glColor4fv(CubeColor);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

static void configLighting ()
{
	static GLfloat ambient[4] = { 0.05, 0.05, 0.05, 1.0 };
	static GLfloat white[4] = { 1, 1, 1, 1 };
	static GLfloat black[4] = { 0, 0, 0, 1 };
	static GLfloat position[4] = { 0, 1, 1, 0 };
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white);
	
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, CubeColor);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, black);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);
}

static void setProjection ()
{
	float aspect;

	aspect = (float)winWidth / (float)winHeight;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, aspect, Near, Far);
	glMatrixMode(GL_MODELVIEW);
}

static void setViewpoint ()
{
	glLoadIdentity();
	gluLookAt(0, 0, 1,
		  0, 0, 0,
		  0, 1, 0);
}

static void drawScene ()
{
	glPushMatrix();
    	glTranslatef(0.0, 0.0, -2.0);
    	glRotatef(Spin, 0.0, 1.0, 0.0);
    	
    	if (WireFrame)
    		configWireStyle();
    	else
    		configLighting();
    	drawCube();
	glPopMatrix();
}

static void redisplay ()
{
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	
	setProjection();
	setViewpoint();
	drawScene();

	CheckGL();
}

// Assumes buffer is RGBA
void writeToBMP(const char* fname, int width, int height, const char* buffer) {
	int filesize = 54 + 3*width*height;
	unsigned char bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0};
	unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0};
	unsigned char bmppad[3] = {0,0,0};

	bmpfileheader[ 2] = (unsigned char)(filesize    );
	bmpfileheader[ 3] = (unsigned char)(filesize>> 8);
	bmpfileheader[ 4] = (unsigned char)(filesize>>16);
	bmpfileheader[ 5] = (unsigned char)(filesize>>24);

	bmpinfoheader[ 4] = (unsigned char)(       width    );
	bmpinfoheader[ 5] = (unsigned char)(       width>> 8);
	bmpinfoheader[ 6] = (unsigned char)(       width>>16);
	bmpinfoheader[ 7] = (unsigned char)(       width>>24);
	bmpinfoheader[ 8] = (unsigned char)(       height    );
	bmpinfoheader[ 9] = (unsigned char)(       height>> 8);
	bmpinfoheader[10] = (unsigned char)(       height>>16);
	bmpinfoheader[11] = (unsigned char)(       height>>24);

	FILE* f = fopen(fname,"wb");
	fwrite(bmpfileheader,1,14,f);
	fwrite(bmpinfoheader,1,40,f);
	for(int i=0; i<height; i++)
	{
	    fwrite(buffer+(width*(height-i-1)*3),3,width,f);
	    fwrite(bmppad,1,(4-(width*3)%4)%4,f);
	}
	fclose(f);
}

// This returns a newly allocated buffer
char* BufferRGBAToRGB(int width, int height, const char* rgba_img) {
	char* rgb_img = (char*)calloc(width * height, 4);
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			rgb_img[(i * width + j)*3 + 0] = rgba_img[(i * width + j)*4 + 0];
			rgb_img[(i * width + j)*3 + 1] = rgba_img[(i * width + j)*4 + 1];
			rgb_img[(i * width + j)*3 + 2] = rgba_img[(i * width + j)*4 + 2];
		}
	}
	return rgb_img;
}


int main (int argc, char * argv[])
{
	OSMesaContext	ctx;
	void *		buffer;
	
	// Seems like osmesa 10.4 only supports RGBA
	ctx = OSMesaCreateContext(OSMESA_RGBA, NULL);
	
	buffer = calloc(winWidth * winHeight, 4);
	if (buffer == NULL)
		Fail("Cannot allocate memory frame buffer");
	
	if (! OSMesaMakeCurrent(ctx, buffer, GL_UNSIGNED_BYTE, winWidth, winHeight))
		Fail("OSMesaMakeCurrent");
		
	printf("GL_VERSION %d\n", GL_VERSION);
	printf("GL_RENDERER %d\n", GL_RENDERER);
	printf("GL vendor : %s version : %s\n", glGetString(GL_VENDOR),
	       glGetString(GL_VERSION));
	printf("GL renderer : %s\n", glGetString(GL_RENDERER));
		
	redisplay();
	glFinish();
	
	const char* rgb_buffer = BufferRGBAToRGB(winWidth, winHeight, (char*)buffer);
	writeToBMP("cube.bmp", winWidth, winHeight, (char*)rgb_buffer);
	//writeToPPM("cube.ppm", GL_RGB, winWidth, winHeight, buffer);
	printf("Created cube.bmp\n");
	
	exit(0);
	return 0;
}
