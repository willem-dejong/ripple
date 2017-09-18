#Willem DeJong
#include <stdlib.h>
#include <stdio.h>
#include "glut.h"
#include <math.h>
#define PI 3.14159265
float globalAmbient = 0.2;
int quadrant = 1;
float lightX = 100, lightY = 100, lightZ = 50; 
int matSpecChoice = 1;
int matColChoice = 1;
int shapeChoice = 1;
float matSpecR = 1, matSpecG = 0, matSpecB = 0;
float matAmbientR = 0.2, matAmbientG = 0, matAmbientB = 0;
float matDiffuseR = 0.8, matDiffuseG = 0, matDiffuseB = 0;
float matShini = 0;  
float lightDiffuse = 0.8;
float x[201];
float dx[201][201];
float dy[201][201];
float Z[201][201];
float RR[201][201];
float ex[201][201];
float t=0;
int on=0;
void setMaterials(void) 
{
   switch (matColChoice)
   {
	   case 1: matAmbientR = .2; matAmbientG = 0; matAmbientB = 0;
		       matDiffuseR = .8; matDiffuseG = 0; matDiffuseB = 0;  
			   matShini    = 0.5; break;
   }

   switch (matSpecChoice)
   {
	   case 1: matSpecR = 1; matSpecG = 0; matSpecB = 0;  break;
   }

   GLfloat mat_ambient[]   = { matAmbientR, matAmbientG, matAmbientB, 1 };
   GLfloat mat_diffuse[]   = { matDiffuseR, matDiffuseR, matDiffuseR, 1 };
   GLfloat mat_specular[]  = { matSpecR, matSpecG, matSpecB, 1 };
   GLfloat mat_shininess[] = { matShini };

   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
   glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);
}

void setLighting(void) 
{
   const GLfloat DIRECTIONAL = 1.0;

   switch (quadrant)
   {
	   case 1: lightX =  200;  lightY =  200;  lightZ =  100;  break;
   }

   GLfloat lmodel_ambient[] = { globalAmbient, globalAmbient, globalAmbient, 1 }; 
   glLightModelfv( GL_LIGHT_MODEL_AMBIENT, lmodel_ambient );

   GLfloat light_position[] = { lightX, lightY, lightZ, DIRECTIONAL };  
   GLfloat light_ambient[] = { .2, .2, .2, 1 };
   GLfloat light_diffuse[] = { lightDiffuse, lightDiffuse, lightDiffuse, 1 };
   GLfloat light_specular[] = { 1, 1, 1, 1 };

   glLightfv(GL_LIGHT0, GL_POSITION, light_position);
   glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
   glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
   glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

	   glEnable(GL_LIGHT0);

}


void init(void) 
{
   glClearColor (1, 0, 0, 1);
   glEnable(GL_LIGHTING);
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_NORMALIZE);
}

void display(void)//still need to change to my new more effiecent double loop
{
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   gluLookAt (10, 10, 10, 0, 0, 0, 0.0, 0.0, 1.0);
   setMaterials();
   setLighting();
   glColor3f(1,0,0);
	float R;
	float RT;
	float dzdr;
	float coss;
	float expp;
     glShadeModel (GL_SMOOTH);
   int zz;
		for(int z=0;z<200;z++)
		{
			glBegin(GL_TRIANGLE_STRIP);
				R=sqrt(pow(x[0],2)+pow(x[z],2));
				RT=PI*R-t;
				coss=cos(RT);
				expp=exp(-0.5*R);
				dzdr=PI*sin(RT)*expp+0.5*coss*expp;
				glNormal3f(dzdr*x[0],dzdr*x[z],R);
				glVertex3f(x[0],x[z],coss*expp);
			for(zz=0;zz<200;zz++)
			{
					R=sqrt(pow(x[zz],2)+pow(x[z+1],2));
					RT=PI*R-t;
					coss=cos(RT);
					expp=exp(-0.5*R);
					dzdr=PI*sin(RT)*expp+0.5*coss*expp;
					glNormal3f(dzdr*x[zz],dzdr*x[z+1],R);
					glVertex3f(x[zz],x[z+1],coss*expp);
					R=sqrt(pow(x[zz+1],2)+pow(x[z],2));
					RT=PI*R-t;
					coss=cos(RT);
					expp=exp(-0.5*R);
					dzdr=PI*sin(RT)*expp+0.5*coss*expp;
					glNormal3f(dzdr*x[zz+1],dzdr*x[z],R);
					glVertex3f(x[zz+1],x[z],coss*expp);
			}
					R=sqrt(pow(x[200],2)+pow(x[z+1],2));
					RT=PI*R-t;
					coss=cos(RT);
					expp=exp(-0.5*R);
					dzdr=PI*sin(RT)*expp+0.5*coss*expp;
					glNormal3f(dzdr*x[200],dzdr*x[z+1],R);
				glVertex3f(x[200],x[z+1],coss*expp);
			glEnd();
		}
		glFlush(); 
}
void idle()
{
	on++;
	if(on%350000==0)
	{
		t+=.075*PI;
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	   setMaterials();
	   setLighting();
	   glMatrixMode(GL_MODELVIEW);
	   int i=0;
	   int ii=0;
	   float R;
		float RT;
		float dzdr;
		float coss;
		float expp;
		 glShadeModel (GL_SMOOTH);
	   int zz;
		RT=PI*RR[0][0]-t;
		coss=cos(RT);
		expp=1/(2*RR[0][0]+1);
		dzdr=PI*sin(RT)*expp+2*coss*expp/(2*RR[0][0]+1);
		dx[0][0]=dzdr*x[0];
		dy[0][0]=dx[0][0];
		Z[0][0]=coss*expp;//[0][0];
	   for(int z=0;z<200;z++)
	   {
		   i=z+1;
		RT=PI*RR[i][0]-t;
		coss=cos(RT);
		expp=1/(2*RR[i][0]+1);
		dzdr=PI*sin(RT)*expp+2*coss*expp/(2*RR[i][0]+1);
		dx[i][0]=dzdr*x[0];
		dy[i][0]=dzdr*x[i];
		Z[i][0]=coss*expp;//[0][0];
			//RT=PI*RR[i][0]-t;
			//coss=cos(RT);
			//dzdr=PI*sin(RT)*ex[i][0]+0.5*coss*ex[i][0];
			//dx[i][0]=dzdr*x[0];
			//dy[i][0]=dzdr*x[i];
			//Z[i][0]=coss*ex[i][0];
		   for(zz=0;zz<200;zz++)
		   {
				ii=zz+1;
				if(z==0)
				{
					RT=PI*RR[0][ii]-t;
					coss=cos(RT);
					expp=1/(2*RR[0][ii]+1);
					dzdr=PI*sin(RT)*expp+2*coss*expp/(2*RR[0][ii]+1);
					dx[0][ii]=dzdr*x[ii];
					dy[0][ii]=dzdr*x[0];
					Z[0][ii]=coss*expp;//[0][0];
				}
					RT=PI*RR[i][ii]-t;
					coss=cos(RT);
					expp=1/(2*RR[i][ii]+1);
					dzdr=PI*sin(RT)*expp+2*coss*expp/(2*RR[i][ii]+1);
					dx[i][ii]=dzdr*x[ii];
					dy[i][ii]=dzdr*x[i];
					Z[i][ii]=coss*expp;//[0][0];
				glBegin(GL_TRIANGLES);
					glNormal3f(dx[z][zz],dy[z][zz],RR[z][zz]);
					glVertex3f(x[zz],x[z],Z[z][zz]);
					glNormal3f(dx[z][ii],dy[z][ii],RR[z][ii]);
					glVertex3f(x[ii],x[z],Z[z][ii]);
					glNormal3f(dx[i][zz],dy[i][zz],RR[i][zz]);
					glVertex3f(x[zz],x[i],Z[i][zz]);
					glNormal3f(dx[i][zz],dy[i][zz],RR[i][zz]);
					glVertex3f(x[zz],x[i],Z[i][zz]);
					glNormal3f(dx[z][ii],dy[z][ii],RR[z][ii]);
					glVertex3f(x[ii],x[z],Z[z][ii]);
					glNormal3f(dx[i][ii],dy[i][ii],RR[i][ii]);
					glVertex3f(x[ii],x[i],Z[i][ii]);
				glEnd();
		   }
	   }
	//	 int zz;
	//	for(int z=0;z<200;z++)
	//	{
	//		i=z+1;
	//		glBegin(GL_TRIANGLE_STRIP);
	//			//R=sqrt(pow(x[0],2)+pow(x[z],2));
	//			RT=PI*RR[z][0]-t;
	//			coss=cos(RT);
	//			//expp=exp(-0.5*RR[z][0]);
	//			dzdr=PI*sin(RT)*ex[z][0]+0.5*coss*ex[z][0];
	//			glNormal3f(dzdr*x[0],dzdr*x[z],RR[z][0]);
	//			glVertex3f(x[0],x[z],coss*ex[z][0]);
	//		for(zz=0;zz<200;zz++)
	//		{
	//			ii=zz+1;
	//				//R=sqrt(pow(x[zz],2)+pow(x[i],2));
	//				RT=PI*RR[i][zz]-t;
	//				coss=cos(RT);
	//				//expp=exp(-0.5*RR[i][zz]);
	//				dzdr=PI*sin(RT)*ex[i][zz]+0.5*coss*ex[i][zz];
	//				glNormal3f(dzdr*x[zz],dzdr*x[i],RR[i][zz]);
	//				glVertex3f(x[zz],x[i],coss*ex[i][zz]);
	//				//R=sqrt(pow(x[ii],2)+pow(x[z],2));
	//				RT=PI*RR[z][ii]-t;
	//				coss=cos(RT);
	//				//expp=exp(-0.5*RR[z][ii]);
	//				dzdr=PI*sin(RT)*ex[z][ii]+0.5*coss*ex[z][ii];
	//				glNormal3f(dzdr*x[ii],dzdr*x[z],RR[z][ii]);
	//				glVertex3f(x[ii],x[z],coss*ex[z][ii]);
	//		}
	//				//R=sqrt(pow(x[200],2)+pow(x[i],2));
	//				RT=PI*RR[i][200]-t;
	//				coss=cos(RT);
	//				//expp=exp(-0.5*RR[i][200]);
	//				dzdr=PI*sin(RT)*ex[i][200]+0.5*coss*ex[i][200];
	//				glNormal3f(dzdr*x[200],dzdr*x[i],RR[i][200]);
	//			glVertex3f(x[200],x[i],coss*ex[i][200]);
	//		glEnd();
	//	}
		glFlush();
	}
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity();
   if (w <= h)
      glOrtho (-2.5, 2.5, -2.5*(GLfloat)h/(GLfloat)w,
         2.5*(GLfloat)h/(GLfloat)w, -200.0, 200.0);
   else
      glOrtho (-2.5*(GLfloat)w/(GLfloat)h,
         2.5*(GLfloat)w/(GLfloat)h, -2.5, 2.5, -200, 200);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

int main(int argc, char** argv)
{
	int ff=-100;
	for(int xx=0;xx<201;xx++)
	{
		x[xx]=ff/20.0;
		ff++;
	}
	for(int z=0;z<201;z++)
	{
		for(int zz=0;zz<201;zz++)
		{
			RR[z][zz]=sqrt(pow(x[zz],2)+pow(x[z],2));
			ex[z][zz]=exp(-0.5*RR[z][zz]);
		}
	}
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (500, 500); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   init();
   glutDisplayFunc(display);
   glutIdleFunc(idle);
   glutReshapeFunc(reshape);
   glutMainLoop();
   return 0;
}
