#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
int widthI, heightI, nrChannelsI;
GLuint texture;
unsigned char *img;
const int larguraCampo = 525, alturaCampo = 340, larguraTela = larguraCampo + 60, alturaTela = alturaCampo + 80, UNIT_PIXEL = 5, center_ball[3] = {30 + larguraCampo / 2, 10 + alturaCampo / 2, 0};
int eye[3] = {30, alturaCampo / 2, 100}, center[3] = {30 + larguraCampo / 2, 10 + alturaCampo / 2, 0}, up[3] = {0, 0, 1}, placar[2] = {0, 0}, t_lapse = 500, luz = 1;
int bola_x = center_ball[0], bola_y = center_ball[1];
GLuint textures[3];
GLint especMaterial = 60;

void DefineIluminacao (void)
{
        GLfloat luzAmbiente[4]={0.2,0.2,0.2,1.0}; 
        GLfloat luzDifusa[4]={0.7,0.7,0.7,1.0};          // "cor" 
        GLfloat luzEspecular[4]={1.0, 1.0, 1.0, 1.0};// "brilho" 
        GLfloat posicaoLuz[4]={larguraCampo / 2, alturaCampo / 2, 20.0, 1.0};
 
        // Capacidade de brilho do material
        GLfloat especularidade[4]={1.0,1.0,1.0,1.0}; 
 		if(luz){
		    // Define a refletância do material 
		    glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
		    // Define a concentração do brilho
		    glMateriali(GL_FRONT,GL_SHININESS,especMaterial);
 		}
        // Ativa o uso da luz ambiente 
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);
 
        // Define os parâmetros da luz de número 0
        glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
        if(luz){
		    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
		    glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
		    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );
        }  
}

void update_camera(){
    glMatrixMode(GL_MODELVIEW);
    DefineIluminacao();
    glLoadIdentity();
    gluLookAt(eye[0]   , eye[1]   , eye[2],
              center[0], center[1], center[2],
              up[0]    , up[1]    , up[2]);
}

void init (void){
  /* selecionar cor de fundo (preto) */
  glClearColor (0.0, 0.0, 0.0, 0.0);
  glMatrixMode (GL_PROJECTION); //Projecao 2D
  glEnable(GL_COLOR_MATERIAL);
  gluPerspective(45, 1.0 * larguraTela / alturaTela, 0.1, 1000.);
  glMatrixMode(GL_MODELVIEW);
  
  //Habilita o uso de iluminação
  glEnable(GL_LIGHTING); 
  // Habilita a luz de número 0
  glEnable(GL_LIGHT0);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D); 
  glShadeModel(GL_SMOOTH);
  update_camera();
  glGenTextures(3, textures);
  //glGenTextures(1, &texture);
  //glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, textures[0]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  img = stbi_load("campo.jpeg", &widthI, &heightI, &nrChannelsI, 0);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthI, heightI, 0, GL_RGB,
              GL_UNSIGNED_BYTE, img);
  stbi_image_free(img);

  //glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, textures[1]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  img = stbi_load("arquibancada.jpeg", &widthI, &heightI, &nrChannelsI, 0); 
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthI, heightI, 0, GL_RGB,
              GL_UNSIGNED_BYTE, img);
  stbi_image_free(img);
  //glActiveTexture(GL_TEXTURE2);
  
  glBindTexture(GL_TEXTURE_2D, textures[2]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  img = stbi_load("rede.jpeg", &widthI, &heightI, &nrChannelsI, 0); 
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthI, heightI, 0, GL_RGB,
                GL_UNSIGNED_BYTE, img);
  stbi_image_free(img);
}


void draw0(){
	glBegin(GL_LINE_LOOP);
		glVertex3i(0, 0, 0);
		glVertex3i(0, 0, 12);
		glVertex3i(0, 6, 12);
		glVertex3i(0, 6, 0);
	glEnd();
}

void draw1(){
	glBegin(GL_LINE_STRIP);
		glVertex3i(0, 0, 0);
		glVertex3i(0, 0, 12);
	glEnd();
}

void draw2(){
	glBegin(GL_LINE_STRIP);
		glVertex3i(0, 0, 0);
		glVertex3i(0, 6, 0);
		glVertex3i(0, 6, 6);
		glVertex3i(0, 0, 6);
		glVertex3i(0, 0, 12);
		glVertex3i(0, 6, 12);
	glEnd();
}

void draw3(){
	glBegin(GL_LINE_STRIP);
		glVertex3i(0, 6, 0);
		glVertex3i(0, 0, 0);
		glVertex3i(0, 0, 6);
		glVertex3i(0, 6, 6);
		glVertex3i(0, 0, 6);
		glVertex3i(0, 0, 12);
		glVertex3i(0, 6, 12);
	glEnd();
}

void draw4(){
	glBegin(GL_LINE_STRIP);
		glVertex3i(0, 0, 0);
		glVertex3i(0, 0, 12);
		glVertex3i(0, 0, 6);
		glVertex3i(0, 6, 6);
		glVertex3i(0, 6, 12);
	glEnd();
}

void draw5(){
	glBegin(GL_LINE_STRIP);
		glVertex3i(0, 6, 0);
		glVertex3i(0, 0, 0);
		glVertex3i(0, 0, 6);
		glVertex3i(0, 6, 6);
		glVertex3i(0, 6, 12);
		glVertex3i(0, 0, 12);
	glEnd();
}

void draw6(){
	glBegin(GL_LINE_STRIP);
		glVertex3i(0, 6, 12);
		glVertex3i(0, 0, 12);
		glVertex3i(0, 0, 0);
		glVertex3i(0, 6, 0);
		glVertex3i(0, 6, 6);
		glVertex3i(0, 0, 6);
	glEnd();
}

void draw7(){
	glBegin(GL_LINE_STRIP);
		glVertex3i(0, 6, 12);
		glVertex3i(0, 0, 12);
		glVertex3i(0, 0, 0);
	glEnd();
}

void draw8(){
	glBegin(GL_LINE_STRIP);
		glVertex3i(0, 0, 6);
		glVertex3i(0, 0, 12);
		glVertex3i(0, 6, 12);
		glVertex3i(0, 6, 0);
		glVertex3i(0, 0, 0);
		glVertex3i(0, 0, 6);
		glVertex3i(0, 6, 6);
	glEnd();
}

void draw9(){
	glBegin(GL_LINE_STRIP);
		glVertex3i(0, 0, 6);
		glVertex3i(0, 6, 6);
		glVertex3i(0, 6, 12);
		glVertex3i(0, 0, 12);
		glVertex3i(0, 0, 0);
	glEnd();
}

void drawPlacar(){
	int player = 2;
	do{
		int p = placar[--player];
		glPushMatrix();
		if(player)
			glTranslatef(30 + larguraCampo, alturaCampo / 2 , 15);
		else{
			glTranslatef(30, 20 + alturaCampo / 2 , 15);
			glRotatef(180, 0, 0, 1);
		}
		do{
			switch(p % 10){
			case 0:
				draw0();
				break;
			case 1:
				draw1();
				break;
			case 2:
				draw2();
				break;
			case 3:
				draw3();
				break;
			case 4:
				draw4();
				break;
			case 5:
				draw5();
				break;
			case 6:
				draw6();
				break;
			case 7:
				draw7();
				break;
			case 8:
				draw8();
				break;
			case 9:
				draw9();
				break;
			}
			glTranslatef(0, 8, 0);
			p /= 10;
		}while(p);
		glPopMatrix();
	}while(player);
}

void keyboard_handler(unsigned char key, int x, int y){

    switch(key){
    case 'w':
        eye[2]-=UNIT_PIXEL;
		break;
    case 's':
        eye[2]+=UNIT_PIXEL;
		break;
    case 'd':
        eye[0]+=UNIT_PIXEL;
		break;
    case 'a':
        eye[0]-=UNIT_PIXEL;
        break;
    case 'q':
        eye[1]+=UNIT_PIXEL;
		break;
    case 'e':
        eye[1]-=UNIT_PIXEL;
        break;  
	case 'i':
        center[2]-=UNIT_PIXEL;
		break;
	case 'k':
        center[2]+=UNIT_PIXEL;
		break;
    case 'l':
        center[0]+=UNIT_PIXEL;
		break;
    case 'j':
        center[0]-=UNIT_PIXEL;
        break;
    case 'u':
        center[1]+=UNIT_PIXEL;
        break;
	case 'o':
        center[1]-=UNIT_PIXEL;
        break;
	case 'n':
        especMaterial = especMaterial + 5;
        break;
	case 'm':
        especMaterial = especMaterial - 5;
        break;
    case 'f':
        if(up[0] == 0){
        	up[1] *= -1;
        	up[2] *= -1;
        }else{
        	up[1] = 1;
        	up[2] = 1;
        }
        up[0] = 0;
        break;
    case 'g':
        if(up[1] == 0){
        	up[0] *= -1;
        	up[2] *= -1;
        }else{
        	up[0] = 1;
        	up[2] = 1;
        }
        up[1] = 0;
        break;
    case 'h':
        if(up[2] == 0){
        	up[1] *= -1;
        	up[0] *= -1;
        }else{
        	up[1] = 1;
        	up[0] = 1;
        }
        up[2] = 0;
        break;
    case 'z':
        luz = !luz;
        break;
	case '8':
		bola_x += UNIT_PIXEL;
		break;
	case '5':
		bola_x -= UNIT_PIXEL;
		break;
	case '4':
		bola_y += UNIT_PIXEL;
		break;
	case '6':
		bola_y -= UNIT_PIXEL;
		break;
	}
	if(bola_x > 30 + larguraCampo){
		if(bola_y >= 162 && bola_y <= 199){
			placar[0]++;
			bola_x = center_ball[0];
			bola_y = center_ball[1];
		}
	}
	if(bola_x < 30){
		if(bola_y >= 162 && bola_y <= 199){
			placar[1]++;
			bola_x = center_ball[0];
			bola_y = center_ball[1];
		}
	}
	update_camera();
    glutPostRedisplay();
}

void swap(int *a, int *b){
	int aux = *a;
	*a = *b;
	*b = aux;
}

void inc_line(int x1, int y1, int x2, int y2){
	int dx = x2 - x1;
	int dy = y2 - y1;
	int mult = 1, s = 0;
	int d, incE, incNE, x, y;
	if(abs(dx) < abs(dy)){
		swap(&x1, &y1);
		swap(&x2, &y2);
		swap(&dx, &dy);
		s = 1;
	}
	if(dx < 0){
		swap(&x1, &x2);
		swap(&y1, &y2);
		dx *= -1;
		dy *= -1;
	}
	if(dy < 0){
		mult = -1;
		y1 *= -1;
		y2 *= -1;
		dy *= -1;
	}
	d = 2 * dy - dx;
	incE = 2 * dy;
	incNE = 2 * (dy - dx);
	x = x1;
	y = y1;
	do{
		if(s)
			glVertex3i(mult * y, x, 0);
		else
			glVertex3i(x, mult * y, 0);
		if(d <= 0){
			d += incE;
		}else{
			d += incNE;
			y++;
		}
		x++;
	}while(x <= x2);
}

void inc_circ_o(int x_c, int y_c, int r, int o){
	int x = 0, y = r, mx, my, s;
	if(((o&1)^((o&2)>>1))&1)
		s = 0;
	else
		s = 1;
	if(o&4)
		mx = -1;
	else
		mx = 1;
	if(((o&2)^((o&4)>>1))&2)
		my = -1;
	else
		my = 1;
	int d = 5 - 4 * r;
	while(y >= x){
		if(d < 0){
			d += 8 * x + 12;
			x++;
		}else{
			d += 8 * (x - y) + 20;
			x++;
			y--;
		}
		if(s)
			glVertex3i(x_c + mx * x, y_c + my * y, 0);
		else
			glVertex3i(x_c + mx * y, y_c + my * x, 0);
	}
}

void inc_circ(int x_c, int y_c, int r, int octs){
	int o = 0;
	while(octs){
		if(octs&1){
			inc_circ_o(x_c, y_c, r, o);
		}
		octs >>= 1;
		o++;
	}
}

void desenharCampo(){
   glBegin (GL_POINTS);
   inc_line(30, 10, 30 + larguraCampo, 10);
   inc_line(30, 10, 30 + larguraCampo, 10);
   inc_line(30, 10, 30 + larguraCampo, 10);
   inc_line(30, 10, 30 + larguraCampo, 10);
   inc_line(30, 10, 30 + larguraCampo, 10);
   inc_line(30 + larguraCampo, 10, 30 + larguraCampo, 10 + alturaCampo);
   inc_line(30 + larguraCampo, 10 + alturaCampo, 30, 10 + alturaCampo);
   inc_line(30, 10 + alturaCampo, 30, 10);
   inc_line(30 + larguraCampo / 2, 10, 30 +larguraCampo / 2, 10 + alturaCampo);
   inc_line(30, 10 + 69, 30 + 82, 10 + 69);
   inc_line(30 + 82, 10 + 69, 30 + 82, 10 + 271);
   inc_line(30 + 82, 10 + 271, 30, 10 + 271);
   inc_line(30 + larguraCampo, 10 + 69, 30 + larguraCampo - 82, 10 + 69);
   inc_line(30 + larguraCampo - 82, 10 + 69, 30 + larguraCampo - 82, 10 + 271);
   inc_line(30 + larguraCampo - 82, 10 + 271, 30 + larguraCampo, 10 + 271);
   inc_line(30, 10 + 124, 30 + 27, 10 + 124);
   inc_line(30 + 27, 10 + 124, 30 + 27, 10 + 216);
   inc_line(30 + 27, 10 + 216, 30, 10 + 216);
   inc_line(30 + larguraCampo, 10 + 124, 30 + larguraCampo - 27, 10 + 124);
   inc_line(30 + larguraCampo - 27, 10 + 124, 30 + larguraCampo - 27, 10 + 216);
   inc_line(30 + larguraCampo - 27, 10 + 216, 30 + larguraCampo, 10 + 216);
   inc_circ(30 + larguraCampo / 2, 10 + alturaCampo / 2, 46, (1<<9) - 1);
   inc_circ(30 , 10, 5, 3);
   inc_circ(30, 10 + alturaCampo, 5, 12);
   inc_circ(30 + larguraCampo, 10 + alturaCampo, 5, 48);
   inc_circ(30 + larguraCampo, 10, 5, 192);
   inc_circ(30 + 50, 10 + alturaCampo / 2, 46, 6);
   inc_circ(30 + larguraCampo - 50, 10 + alturaCampo / 2, 46, 96);
   glEnd();
   //glActiveTexture(GL_TEXTURE0);
   glBindTexture(GL_TEXTURE_2D, textures[0]);
   glBegin (GL_QUADS);
   		glTexCoord2f(0.0, 0.0); glVertex3i(30, 10, 0);
   		glTexCoord2f(1.0, 0.0); glVertex3i(30 + larguraCampo, 10, 0);
   		glTexCoord2f(1.0, 1.0); glVertex3i(30 + larguraCampo, 10 + alturaCampo, 0);
   		glTexCoord2f(0.0, 1.0); glVertex3i(30, 10 + alturaCampo, 0);
   glEnd();
   glBindTexture(GL_TEXTURE_2D, textures[1]);
   glBegin (GL_QUADS);
   		glTexCoord2f(0.0, 0.0); glVertex3i(30, 162, 0);
   		glTexCoord2f(0.0, 1.0); glVertex3i(30, 162, 12);
   		glTexCoord2f(1.0, 1.0); glVertex3i(22, 162, 12);
   		glTexCoord2f(1.0, 0.0); glVertex3i(22, 162, 0);
   		glTexCoord2f(0.0, 0.0); glVertex3i(30, 162, 12);
   		glTexCoord2f(0.0, 1.0); glVertex3i(30, 199, 12);
   		glTexCoord2f(1.0, 1.0); glVertex3i(22, 199, 12);
   		glTexCoord2f(1.0, 0.0); glVertex3i(22, 162, 12);
   		glTexCoord2f(0.0, 0.0); glVertex3i(30, 199, 12);
   		glTexCoord2f(0.0, 1.0); glVertex3i(30, 199, 0);
   		glTexCoord2f(1.0, 1.0); glVertex3i(22, 199, 0);
   		glTexCoord2f(1.0, 0.0); glVertex3i(22, 199, 12);
   		glTexCoord2f(0.0, 0.0); glVertex3i(22, 162, 12);
   		glTexCoord2f(0.0, 1.0); glVertex3i(22, 199, 12);
   		glTexCoord2f(1.0, 1.0); glVertex3i(22, 199, 0);
   		glTexCoord2f(1.0, 0.0); glVertex3i(22, 162, 0);
   glEnd();
   glBegin (GL_QUADS);
   		glTexCoord2f(0.0, 0.0); glVertex3i(30 + larguraCampo, 162, 0);
   		glTexCoord2f(0.0, 1.0); glVertex3i(30 + larguraCampo, 162, 12);
   		glTexCoord2f(1.0, 1.0); glVertex3i(38 + larguraCampo, 162, 12);
   		glTexCoord2f(1.0, 0.0); glVertex3i(38 + larguraCampo, 162, 0);
   		glTexCoord2f(0.0, 0.0); glVertex3i(30 + larguraCampo, 162, 12);
   		glTexCoord2f(0.0, 1.0); glVertex3i(30 + larguraCampo, 199, 12);
   		glTexCoord2f(1.0, 1.0); glVertex3i(38 + larguraCampo, 199, 12);
   		glTexCoord2f(1.0, 0.0); glVertex3i(38 + larguraCampo, 162, 12);
   		glTexCoord2f(0.0, 0.0); glVertex3i(30 + larguraCampo, 199, 12);
   		glTexCoord2f(0.0, 1.0); glVertex3i(30 + larguraCampo, 199, 0);
   		glTexCoord2f(1.0, 1.0); glVertex3i(38 + larguraCampo, 199, 0);
   		glTexCoord2f(1.0, 0.0); glVertex3i(38 + larguraCampo, 199, 12);
   		glTexCoord2f(0.0, 0.0); glVertex3i(38 + larguraCampo, 162, 12);
   		glTexCoord2f(0.0, 1.0); glVertex3i(38 + larguraCampo, 199, 12);
   		glTexCoord2f(1.0, 1.0); glVertex3i(38 + larguraCampo, 199, 0);
   		glTexCoord2f(1.0, 0.0); glVertex3i(38 + larguraCampo, 162, 0);
   glEnd();
   //glActiveTexture(GL_TEXTURE0);
   glBindTexture(GL_TEXTURE_2D, textures[2]);
   glBegin (GL_QUADS);
   		glTexCoord2f(0.0, 0.0); glVertex3i(30 , 0, 0);
   		glTexCoord2f(0.0, 1.0); glVertex3i(30 + larguraCampo, 0, 0);
   		glTexCoord2f(1.0, 1.0); glVertex3i(30 + larguraCampo, 0, 5);
   		glTexCoord2f(1.0, 0.0); glVertex3i(30, 0, 5);
   		glTexCoord2f(0.0, 0.0); glVertex3i(30 , 0, 5);
   		glTexCoord2f(0.0, 1.0); glVertex3i(30 + larguraCampo, 0, 5);
   		glTexCoord2f(1.0, 1.0); glVertex3i(30 + larguraCampo, -5, 5);
   		glTexCoord2f(1.0, 0.0); glVertex3i(30, -5, 5);
   		glTexCoord2f(0.0, 0.0); glVertex3i(30 , -5, 5);
   		glTexCoord2f(0.0, 1.0); glVertex3i(30 + larguraCampo, -5, 5);
   		glTexCoord2f(1.0, 1.0); glVertex3i(30 + larguraCampo, -5, 10);
   		glTexCoord2f(1.0, 0.0); glVertex3i(30, -5, 10);
   		glTexCoord2f(0.0, 0.0); glVertex3i(30 , -5, 10);
   		glTexCoord2f(0.0, 1.0); glVertex3i(30 + larguraCampo, -5, 10);
   		glTexCoord2f(1.0, 1.0); glVertex3i(30 + larguraCampo, -10, 10);
   		glTexCoord2f(1.0, 0.0); glVertex3i(30, -10, 10);
   		glTexCoord2f(0.0, 0.0); glVertex3i(30 , -10, 10);
   		glTexCoord2f(0.0, 1.0); glVertex3i(30 + larguraCampo, -10, 10);
   		glTexCoord2f(1.0, 1.0); glVertex3i(30 + larguraCampo, -10, 15);
   		glTexCoord2f(1.0, 0.0); glVertex3i(30, -10, 15);
   		glTexCoord2f(0.0, 0.0); glVertex3i(30 , -10, 15);
   		glTexCoord2f(0.0, 1.0); glVertex3i(30 + larguraCampo, -10, 15);
   		glTexCoord2f(1.0, 1.0); glVertex3i(30 + larguraCampo, -15, 15);
   		glTexCoord2f(1.0, 0.0); glVertex3i(30, -15, 15);
   		glTexCoord2f(0.0, 0.0); glVertex3i(30 , -15, 15);
   		glTexCoord2f(0.0, 1.0); glVertex3i(30 + larguraCampo, -15, 15);
   		glTexCoord2f(1.0, 1.0); glVertex3i(30 + larguraCampo, -15, 20);
   		glTexCoord2f(1.0, 0.0); glVertex3i(30, -15, 20);
   		glTexCoord2f(0.0, 0.0); glVertex3i(30 , -15, 20);
   		glTexCoord2f(0.0, 1.0); glVertex3i(30 + larguraCampo, -15, 20);
   		glTexCoord2f(1.0, 1.0); glVertex3i(30 + larguraCampo, -20, 20);
   		glTexCoord2f(1.0, 0.0); glVertex3i(30, -20, 20);
   		
   		glTexCoord2f(0.0, 0.0); glVertex3i(30 , 20 + alturaCampo, 0);
   		glTexCoord2f(0.0, 1.0); glVertex3i(30 + larguraCampo, 20 + alturaCampo, 0);
   		glTexCoord2f(1.0, 1.0); glVertex3i(30 + larguraCampo, 20 + alturaCampo, 5);
   		glTexCoord2f(1.0, 0.0); glVertex3i(30, 20 + alturaCampo, 5);
   		glTexCoord2f(0.0, 0.0); glVertex3i(30 , 20 + alturaCampo, 5);
   		glTexCoord2f(0.0, 1.0); glVertex3i(30 + larguraCampo, 20 + alturaCampo, 5);
   		glTexCoord2f(1.0, 1.0); glVertex3i(30 + larguraCampo, 25 + alturaCampo, 5);
   		glTexCoord2f(1.0, 0.0); glVertex3i(30, 25 + alturaCampo, 5);
   		glTexCoord2f(0.0, 0.0); glVertex3i(30 , 25 + alturaCampo, 5);
   		glTexCoord2f(0.0, 1.0); glVertex3i(30 + larguraCampo, 25 + alturaCampo, 5);
   		glTexCoord2f(1.0, 1.0); glVertex3i(30 + larguraCampo, 25 + alturaCampo, 10);
   		glTexCoord2f(1.0, 0.0); glVertex3i(30, 25 + alturaCampo, 10);
   		glTexCoord2f(0.0, 0.0); glVertex3i(30 , 25 + alturaCampo, 10);
   		glTexCoord2f(0.0, 1.0); glVertex3i(30 + larguraCampo, 25 + alturaCampo, 10);
   		glTexCoord2f(1.0, 1.0); glVertex3i(30 + larguraCampo, 30 + alturaCampo, 10);
   		glTexCoord2f(1.0, 0.0); glVertex3i(30, 30 + alturaCampo, 10);
   		glTexCoord2f(0.0, 0.0); glVertex3i(30 , 30 + alturaCampo, 10);
   		glTexCoord2f(0.0, 1.0); glVertex3i(30 + larguraCampo, 30 + alturaCampo, 10);
   		glTexCoord2f(1.0, 1.0); glVertex3i(30 + larguraCampo, 30 + alturaCampo, 15);
   		glTexCoord2f(1.0, 0.0); glVertex3i(30, 30 + alturaCampo, 15);
   		glTexCoord2f(0.0, 0.0); glVertex3i(30 , 30 + alturaCampo, 15);
   		glTexCoord2f(0.0, 1.0); glVertex3i(30 + larguraCampo, 30 + alturaCampo, 15);
   		glTexCoord2f(1.0, 1.0); glVertex3i(30 + larguraCampo, 35 + alturaCampo, 15);
   		glTexCoord2f(1.0, 0.0); glVertex3i(30, 35 + alturaCampo, 15);
   		glTexCoord2f(0.0, 0.0); glVertex3i(30 , 35 + alturaCampo, 15);
   		glTexCoord2f(0.0, 1.0); glVertex3i(30 + larguraCampo, 35 + alturaCampo, 15);
   		glTexCoord2f(1.0, 1.0); glVertex3i(30 + larguraCampo, 35 + alturaCampo, 20);
   		glTexCoord2f(1.0, 0.0); glVertex3i(30, 35 + alturaCampo, 20);
   		glTexCoord2f(0.0, 0.0); glVertex3i(30 , 35 + alturaCampo, 20);
   		glTexCoord2f(0.0, 1.0); glVertex3i(30 + larguraCampo, 35 + alturaCampo, 20);
   		glTexCoord2f(1.0, 1.0); glVertex3i(30 + larguraCampo, 40 + alturaCampo, 20);
   		glTexCoord2f(1.0, 0.0); glVertex3i(30, 40 + alturaCampo, 20);
   glEnd();
}

void drawBola(){
    int radius = 5;
	glPushMatrix();
    glTranslatef(bola_x, bola_y, center_ball[2]+radius);
    glColor4f(0.35, 0.71, 0.94, 0);
    glutSolidSphere(radius, 15, 15);
    glPopMatrix();
}

void displayFcn(void){
   /* Limpar todos os pixels  */

   glClear (GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
   DefineIluminacao();
   //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
   drawBola();
   glEnable(GL_DEPTH_TEST);
   glMatrixMode(GL_MODELVIEW);
   
   glColor3f (1.0, 1.0, 1.0); //Pontos em branco
   glPointSize (1.0); //Tamanho do Ponto
   drawPlacar();
   desenharCampo();
   /* Não esperar! */
   glutSwapBuffers();
}

void Timer(int value)
{
	placar[0]++;
	placar[1]++;
    // Redesenha o quadrado com as novas coordenadas 
    glutPostRedisplay();
    glutTimerFunc(t_lapse,Timer, 1);
}

int main(int argc, char** argv){
	glutInit (&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (larguraTela, alturaTela);
	glutInitWindowPosition (200, 200);
	glutCreateWindow ("Futebol");
	init();
	glutDisplayFunc(displayFcn);
	//glutTimerFunc(t_lapse, Timer, 1);
	glutKeyboardFunc(keyboard_handler);
	glutMainLoop();
	return 0;
}
