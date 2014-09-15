
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

SDL_Window* displayWindow;

GLuint LoadTexture(const char *image_path) 
{ 
	SDL_Surface *surface = IMG_Load(image_path); 
	
	GLuint textureID; 
	glGenTextures(1, &textureID); 
	glBindTexture(GL_TEXTURE_2D, textureID); 
 
	glTexImage2D(GL_TEXTURE_2D, 0, 4, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels); 
 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
 
	SDL_FreeSurface(surface); 
	return textureID; 
}

void DrawSprite(GLint texture, float x, float y, float rotation) 
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	glTranslatef(x, y, 0.0);
	glRotatef(rotation, 0.0, 0.0, 1.0);

	GLfloat quad[] = { -0.5f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f };
	glVertexPointer(2, GL_FLOAT, 0, quad);
	glEnableClientState(GL_VERTEX_ARRAY);

	GLfloat quadUVs[] = { 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0 };
	glTexCoordPointer(2, GL_FLOAT, 0, quadUVs);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDrawArrays(GL_QUADS, 0, 4);
	glDisable(GL_TEXTURE_2D);
}


int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_VIDEO);
	displayWindow = SDL_CreateWindow("Gary's Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
	SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
	SDL_GL_MakeCurrent(displayWindow, context);

	bool done = false;
	SDL_Event event;

	glViewport(0, 0, 800, 600);
	glMatrixMode(GL_PROJECTION);
	glOrtho(-1.33, 1.33, -1.0, 1.0, -1.0, 1.0);

	GLuint beige = LoadTexture("alienBeige.png");
	GLuint blue = LoadTexture("alienBlue.png");
	GLuint green = LoadTexture("alienGreen.png");

	float lastFrameTicks = 0.0f;
	float faceRotation = 0.0;
	float pbMove = -1.0;
	float pbWig = 0.0;

	bool caught = false;
	bool doOnce = true;
	bool left = false;

	while (!done) 
	{
		while (SDL_PollEvent(&event)) 
		{
			if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE) 
			{
				done = true;
			}
		}

		float ticks = (float)SDL_GetTicks() / 1000.0f;
		float elapsed = ticks - lastFrameTicks;
		lastFrameTicks = ticks;

		faceRotation += elapsed;
		pbMove += elapsed;
		if (pbWig + elapsed > 0.5 && left == false) 
		{
			pbWig -= elapsed;
			left = true;
		}
		else if (pbWig - elapsed > -0.5 && left == true) 
		{
			pbWig -= elapsed;
		}
		else if (pbWig - elapsed < -0.5 && left == true) 
		{
			left = false;
			pbWig += elapsed;
		}
		else 
		{
			pbWig += elapsed;
		}

		glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		if (pbMove < 0.0f) 
		{
			DrawSprite(beige, 0.5f, 0.3f, 0);
			DrawSprite(blue, pbMove, 0.3f, 45.0f * faceRotation);
		}
		else if (caught == false) 
		{
     		glTranslatef(-0.2f, -0.2f, 0.0f);
			glLoadIdentity();
			glRotatef(-15.0f, 0.0, 0.0, 1.0);
			GLfloat redBeam[] = { 0.25f, 0.25f, -0.25f, 0.25f, -0.25f, 0.1f, 0.25f, 0.1f };
			glVertexPointer(2, GL_FLOAT, 0, redBeam);
			glEnableClientState(GL_VERTEX_ARRAY);

			GLfloat beamColor[] = { 0.8f, 0.0f, 0.0f, 0.8f, 0.0f, 0.0f, 0.8f, 0.0f, 0.0f, 0.8f, 0.0f, 0.0f };
			glColorPointer(3, GL_FLOAT, 0, beamColor);
			glEnableClientState(GL_COLOR_ARRAY);

			glDrawArrays(GL_QUADS, 0, 4);

			glDisableClientState(GL_COLOR_ARRAY);

			DrawSprite(green, 0.6f, 0.0f, 0);
			caught = true;

		}
		else {
			if (doOnce == true) 
			{
				Sleep(1500); 
				doOnce = false;
			}
			DrawSprite(blue, 0.0f, 0.3f, pbWig * 45.0f);
		}
		SDL_GL_SwapWindow(displayWindow);
	}

	SDL_Quit();
	return 0;
}

